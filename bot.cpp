#include <iostream>
#include <string>
#include <curl/curl.h>

void sendMessage(const std::string& token, const std::string& chat_id, const std::string& message) {
    CURL* curl;
    CURLcode res;

    // Формируем URL для отправки сообщения
    std::string url = "https://api.telegram.org/bot" + token + "/sendMessage?chat_id=" + chat_id + "&text=" + curl_easy_escape(curl, message.c_str(), message.length());

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // Выполняем запрос
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Освобождаем ресурсы
        curl_easy_cleanup(curl);
    }
}

int main() {
    std::string token = "8030132455:AAHczm5xWQwU55T2-t7AscQmVwxx4nUc3fE"; // Ваш токен
    std::string chat_id = "1002449527367"; // Замените на ваш chat_id
    std::string message = "Hello, Telegram!"; // Сообщение для отправки

    sendMessage(token, chat_id, message);

    return 0;
}