#ifndef TGTelegramBotAPI_h
#define TGTelegramBotAPI_h

#include <stdio.h>
#include <string>

#include "tghttprequestservice.h"

namespace spcTelega {

class TGTelegramBotAPI {
private:
    const std::string botID;
    TGHTTPRequestService httpService;
    
public:
    TGTelegramBotAPI(const std::string& botID);
    ~TGTelegramBotAPI();
    
    void sendMessage(const std::string& message);
};

};

#endif /* TGTelegramBotAPI_hpp */
