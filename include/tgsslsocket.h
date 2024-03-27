#ifndef TGSSLSocket_h
#define TGSSLSocket_h

#include <stdio.h>
#include <string>
#include <openssl/ssl.h>

namespace spcTelega {

class TGSSLSocket {
public:
    TGSSLSocket(const std::string& host, const int port);
    ~TGSSLSocket();
    std::string sendRequest(const std::string& request);

private:
    const std::string host;
    const int port;
    SSL *ssl;
    int openedSocket;

    int connectToServer(const std::string host, const int port);
    SSL *enableSSL(const int socket);
};

};


#endif /* TGSSLSocket_h */
