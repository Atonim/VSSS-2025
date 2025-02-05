#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <atomic>
#include <cstring>
#include <chrono>
#include <curl/curl.h>

class Server
{
public:
    Server(short port)
        : acceptor_(io_service_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
          highest_value_(0)
    {
        start_accept();
    }

    void run()
    {
        std::thread hello_thread(&Server::print_hello, this); // Запускаем поток для вывода "Привет, мир"
        // io_service_.run();
        hello_thread.join(); // Ждем завершения потока
    }

private:
    void start_accept()
    {
        socket_ = std::make_shared<boost::asio::ip::tcp::socket>(io_service_);
        acceptor_.async_accept(*socket_,
                               [this](const boost::system::error_code &error)
                               {
                                   handle_accept(error);
                               });
    }

    void handle_accept(const boost::system::error_code &error)
    {
        if (!error)
        {
            std::thread(&Server::read_data, this, socket_).detach();
        }
        start_accept();
    }

    void read_data(std::shared_ptr<boost::asio::ip::tcp::socket> socket)
    {
        char buffer[256];
        while (true)
        {
            std::memset(buffer, 0, sizeof(buffer)); // Очистка буфера
            boost::system::error_code error;
            size_t len = socket->read_some(boost::asio::buffer(buffer), error);
            if (error)
            {
                std::cerr << "Error: " << error.message() << std::endl;
                break;
            }
            int received_value = std::atoi(buffer);
            highest_value_.store(received_value);
            std::cout << "Received value: " << received_value << std::endl;
        }
    }

    void sendMessage(const std::string &token, const std::string &chat_id, const std::string &message)
    {
        CURL *curl;
        CURLcode res;

        // Формируем URL для отправки сообщения
        std::string url = "https://api.telegram.org/bot" + token + "/sendMessage?chat_id=" + chat_id + "&text=" + curl_easy_escape(curl, message.c_str(), message.length());

        curl = curl_easy_init();
        if (curl)
        {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

            // Выполняем запрос
            res = curl_easy_perform(curl);
            if (res != CURLE_OK)
            {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            }

            // Освобождаем ресурсы
            curl_easy_cleanup(curl);
        }
    }

    void print_hello()
    {
        int temp = 100;
        int pres = 300;
        int time = 10;
        std::string token = "8030132455:AAHczm5xWQwU55T2-t7AscQmVwxx4nUc3fE"; // Ваш токен
        std::string chat_id = "-1002449527367";                               // Замените на ваш chat_id
        std::string temperatureAlert = "Превышение температуры - " + std::to_string(temp) + "℃. Возможно возгорание!";
        std::string pressureAlert = "Превышение давления - " + std::to_string(pres) + ". Возможно возгорание или утечка бытового газа!";
        std::string soundAlert = "Обнаружен посторонний шум. Возможно проникновение!";
        std::string distanceAlert = "Обнаружен посторонний объект. Возможно проникновение!";
        std::string testMessage = "Проверка";

        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(time));
            sendMessage(token, chat_id, testMessage);
        }
    }

    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::shared_ptr<boost::asio::ip::tcp::socket> socket_;
    std::atomic<int> highest_value_;
};

int main()
{
    try
    {
        Server server(12345); // Порт сервера
        server.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}