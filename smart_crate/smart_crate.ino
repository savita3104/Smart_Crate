#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Savita";
const char* password = "12345678";

String serverName = "http://10.46.161.196:5000/update";

void setup() {
  Serial.begin(115200);
  delay(3000);

  Serial.println("Smart Crate Starting...");

  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.println(WiFi.localIP());
}

void loop() {

  float temperature = random(20, 35);
  float humidity = random(60, 95);
  int gas = random(300, 700);

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String jsonData = "{\"temperature\":" + String(temperature) +
                      ",\"humidity\":" + String(humidity) +
                      ",\"gas\":" + String(gas) + "}";

    int httpResponseCode = http.POST(jsonData);

    Serial.print("HTTP Response: ");
    Serial.println(httpResponseCode);

    http.end();
  }

  delay(5000);
}