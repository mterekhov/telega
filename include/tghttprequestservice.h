#ifndef TGHTTPRequestService_h
#define TGHTTPRequestService_h

#include <stdio.h>
#include <string>
#include <map>
#include <list>
#include <openssl/ssl.h>

namespace spcTelega {

class YVHTTPPar {
public:
    std::string key;
    std::string value;
};

using HTTPParsType = std::list<YVHTTPPar>;
using HTTPHeadersType = std::list<YVHTTPPar>;

class TGHTTPRequestService {
public:
    
    TGHTTPRequestService(const std::string& host);
    ~TGHTTPRequestService();
    
    std::string sendGETRequest(const std::string& link, const HTTPParsType& pars = HTTPParsType(), const HTTPHeadersType& additionalHeaders = HTTPHeadersType());
    std::string sendPOSTRequest(const std::string& link, const HTTPParsType& pars = HTTPParsType(), const HTTPHeadersType& additionalHeaders = HTTPHeadersType());

private:
    const std::string hostName;
    std::string csrfToken;
    
    std::string generateHeaders(const HTTPHeadersType& additionalHeaders);
    std::string generatePOSTBody(const HTTPParsType& parsList, const HTTPHeadersType& additionalHeaders);
    std::string generateGETParsString(const HTTPParsType& parsList);
    int connectToServer(const std::string hostAddress);
    SSL *enableSSL(const int socket);
    std::string sendHTTPSRequest(const std::string& method,
                                 const std::string& link,
                                 const HTTPParsType& pars,
                                 const HTTPHeadersType& additionalHeaders);
};

};

#endif
