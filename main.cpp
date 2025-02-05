#include <WiFi.h>
#include <HTTPClient.h>

// Замените на ваши данные Wi-Fi
const char *ssid = "YOUR_SSID";
const char *password = "YOUR_PASSWORD";

// Ваш токен и chat_id
String token = "YOUR_TELEGRAM_BOT_TOKEN";
String chat_id = "YOUR_CHAT_ID";

// Функция для отправки сообщения в Telegram
void sendMessage(String message)
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    String url = "https://api.telegram.org/bot" + token + "/sendMessage?chat_id=" + chat_id + "&text=" + message;

    http.begin(url);                   // Начинаем HTTP-запрос
    int httpResponseCode = http.GET(); // Отправляем GET-запрос

    if (httpResponseCode > 0)
    {
      String response = http.getString(); // Получаем ответ
      Serial.println(httpResponseCode);   // Код ответа
      Serial.println(response);           // Ответ от сервера
    }
    else
    {
      Serial.print("Ошибка при отправке сообщения: ");
      Serial.println(httpResponseCode);
    }
    http.end(); // Завершаем HTTP-запрос
  }
  else
  {
    Serial.println("WiFi не подключен");
  }
}

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Ожидание подключения к Wi-Fi
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Подключение к WiFi...");
  }
  Serial.println("Подключено к WiFi");
}

void loop()
{
  // Здесь вы можете считывать данные с вашего датчика
  // Например, считываем температуру (замените на ваш код)
  int temperature = 25; // Пример значения температуры

  // Формируем сообщение
  String message = "Температура: " + String(temperature) + "°C";

  // Отправляем сообщение в Telegram
  sendMessage(message);

  delay(10000); // Задержка между отправками
}