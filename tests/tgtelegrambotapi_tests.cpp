#include "tgtelegrambotapi.h"

int main(int argc, const char *argv[]) {
    spcTelega::TGTelegramBotAPI telegramBot("6356062369:AAHGg0paAAwIaWX8sC-4S1LQECjskaesHb0");
    const std::string response = telegramBot.sendMessage("test message");
    

	return 0;
}