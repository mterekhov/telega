#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "tgtelegrambotapi.h"

TEST_CASE("Testing Telegram bot API") {
    spcTelega::TGTelegramBotAPI telegramBot("6356062369:AAHGg0paAAwIaWX8sC-4S1LQECjskaesHb0");
    const std::string response = telegramBot.sendMessage("test message");
	CHECK(!response.empty());
}
