#include "tgtelegrambotapi.h"

namespace spcTelega {

TGTelegramBotAPI::TGTelegramBotAPI(const std::string& botID) : httpService("api.telegram.org"), botID(botID) {
    
}

TGTelegramBotAPI::~TGTelegramBotAPI() {
    
}

std::string TGTelegramBotAPI::sendMessage(const std::string& message) {
    std::string link = "/bot" + botID + "/sendMessage";
    std::string response = httpService.sendGETRequest(link, {
        {"chat_id", "@adityaloka"},
        {"text", message}
                                                        },
                                                       {
        {"accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8"},
        {"connection", "close"}
                                                        });
    return response;
}

}
