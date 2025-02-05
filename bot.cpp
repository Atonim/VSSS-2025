#include <iostream>
#include <string>

int main()
{
    std::string token = "8030132455:AAHczm5xWQwU55T2-t7AscQmVwxx4nUc3fE"; // Ваш токен
    std::string chat_id = "-1002449527367";                               // Замените на ваш chat_id
    int temp = 100;
    int pres = 300;
    std::string temperatureAlert = "Превышение температуры - " + std::to_string(temp) + "℃. Возможно возгорание!";
    std::string pressureAlert = "Превышение давления - " + std::to_string(pres) + ". Возможно возгорание или утечка бытового газа!";
    std::string soundAlert = "Обнаружен посторонний шум. Возможно проникновение!";
    std::string distanceAlert = "Обнаружен посторонний объект. Возможно проникновение!";
    std::string testMessage = "Проверка";

    sendMessage(token, chat_id, testMessage);

    return 0;
}