#include <iostream>

#include "tgtelegrambotapi.h"

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        return 0;
    }
    spcTelega::TGTelegramBotAPI telegramBot("6356062369:AAHGg0paAAwIaWX8sC-4S1LQECjskaesHb0");
    
    telegramBot.sendMessage(argv[1]);

    return 0;
}
