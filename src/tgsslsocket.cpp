#include <openssl/err.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/ioctl.h>

#include "tgsslsocket.h"
#include "tgtools.h"

namespace spcTelega {

TGSSLSocket::TGSSLSocket(const std::string& host, const int port) : host(host), port(port) {
    SSL_library_init();
    SSLeay_add_ssl_algorithms();
    SSL_load_error_strings();
}

TGSSLSocket::~TGSSLSocket() {
}

std::string TGSSLSocket::sendRequest(const std::string& message) {
    openedSocket = connectToServer(host, port);

    if (openedSocket < 0) {
        return "";
    }
    ssl = enableSSL(openedSocket);

    int err = SSL_write(ssl, message.c_str(), message.length());
    if (!err) {
        TGTools::vidyaInfo("TGSSLSocket: error while sending\n");
    }
    
    int bufferSize = 8 * BUFSIZ;
    char *buffer = new char[bufferSize];
    std::string response = "";
    ssize_t bytes = 1;
    while (bytes > 0) {
        memset(buffer, 0, bufferSize);
        bytes = SSL_read(ssl, buffer, bufferSize);
        response += buffer;
    }
    delete [] buffer;
    
    SSL_shutdown(ssl);
    close(openedSocket);
    SSL_CTX *ctx = SSL_get_SSL_CTX(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);

    return response;
}

int TGSSLSocket::connectToServer(const std::string host, const int port) {
    int newSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (newSocket < 0) {
        TGTools::vidyaInfo("TGSSLSocket: error creating socket.\n");
        return -1;
    }
    
    struct timeval tv = {0};
    tv.tv_sec = 30;
    if (setsockopt(newSocket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(tv)) < 0) {
        printf("errror <%i>\n", errno);
    }

    struct sockaddr_in socketAddress;
    memset(&socketAddress, 0, sizeof(socketAddress));
    socketAddress.sin_family = AF_INET;
    struct hostent *he;
    if ((he = gethostbyname(host.c_str())) == NULL) {
        TGTools::vidyaInfo("TGSSLSocket: host address is not defined\n");
        return -1;
    }
    socketAddress.sin_addr.s_addr = *((unsigned long*)he->h_addr);
    socketAddress.sin_port = htons(port);
    if (connect(newSocket, (struct sockaddr *)&socketAddress, sizeof(socketAddress))) {
        TGTools::vidyaInfo("TGSSLSocket: error connecting to server.\n");
        return -1;
    }
    
    return newSocket;
}

SSL *TGSSLSocket::enableSSL(const int socket) {
    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
    SSL* newSSL = SSL_new(ctx);
    if (!newSSL) {
        TGTools::vidyaInfo("TGSSLSocket: error creating SSL.\n");
        return NULL;
    }
    
    SSL_set_fd(newSSL, socket);
    int err = SSL_connect(newSSL);
    if (err <= 0) {
        TGTools::vidyaInfo("TGSSLSocket: error creating SSL connection\n");
        return NULL;
    }

    return newSSL;
}

};
