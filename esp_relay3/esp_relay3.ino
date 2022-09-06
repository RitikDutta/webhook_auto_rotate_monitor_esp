#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#else
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>

#endif
#include <ESPAsyncWebServer.h>


const char* ssid = "Airtel_9587411733";
const char* password = "air72055";
String url = "https://trigger.macrodroid.com/fcf1e78c-093a-4a05-9f8a-9ad36e2554c5/link1";
const char* serverName = "http://192.168.1.10:8090/helloesp";

const int output = 0;
const int output2 = 2;
int button = 3;
int button2 = 1;
String sensorReadings;

int count_l = 0;
int count_r = 0;
int count_n = 0;


// HTML web page
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
 <head>
  <title>ESP Pushbutton Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
 </head>
 <body>
  <h1>ESP Pushbutton Web Server</h1>
  <button class="button" onmousedown="toggleCheckbox('on');" ontouchstart="toggleCheckbox('on');" onmouseup="toggleCheckbox('off');" ontouchend="toggleCheckbox('off');">LED PUSHBUTTON</button>
  <br>
  <button class="button" onmousedown="toggleCheckbox('on2');" ontouchstart="toggleCheckbox('on2');" onmouseup="toggleCheckbox('off2');" ontouchend="toggleCheckbox('off2');">LED PUSHBUTTON2</button>
  <br>
  <button class="button" onmousedown="toggleCheckbox('on3');" ontouchstart="toggleCheckbox('on3');" onmouseup="toggleCheckbox('off3');" ontouchend="toggleCheckbox('off3');">LED PUSHBUTTON2</button>
  <br>
  <button class="button" onmousedown="toggleCheckbox('on4');" ontouchstart="toggleCheckbox('on4');" onmouseup="toggleCheckbox('off4');" ontouchend="toggleCheckbox('off4');">LED PUSHBUTTON2</button>
  
  <script>
    function toggleCheckbox(x) {
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/" + x, true);
      xhr.send();
    }
  </script>
 </body>
</html>)rawliteral";


void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

AsyncWebServer server(80);

void setup() {
  pinMode(output, OUTPUT);
  pinMode(output2, OUTPUT);
  digitalWrite(button, LOW);
  digitalWrite(button2, LOW);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    return;

  }

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);

  });

  server.on("/on", HTTP_GET, [] (AsyncWebServerRequest * request) {
    digitalWrite(output, HIGH);
    request->send(200, "text/plain", "ok");

  });

  server.on("/off", HTTP_GET, [] (AsyncWebServerRequest * request) {
    digitalWrite(output, LOW);
    request->send(200, "text/plain", "ok");

  });

  server.on("/on2", HTTP_GET, [] (AsyncWebServerRequest * request) {
    digitalWrite(output2, HIGH);
    request->send(200, "text/plain", "ok");

  });

  server.on("/off2", HTTP_GET, [] (AsyncWebServerRequest * request) {
    digitalWrite(output2, LOW);
    request->send(200, "text/plain", "ok");

  });

  server.onNotFound(notFound);
  server.begin();
}




void loop() {

  digitalWrite(button, LOW);
  digitalWrite(button2, LOW);
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient https;
    if (digitalRead(button) == HIGH) {
      if (count_l == 2) {
        if (WiFi.status() == WL_CONNECTED) {
          sensorReadings = httpGETRequest("http://192.168.1.10:8090/left");
          Serial.println(sensorReadings);
          JSONVar myObject = JSON.parse(sensorReadings);
          count_r = 0;
          count_n = 0;
        }
      }
      count_l += 1;
    }
    else if (digitalRead(button2) == HIGH) {

      if (count_r == 2) {
        if (WiFi.status() == WL_CONNECTED) {
          sensorReadings = httpGETRequest("http://192.168.1.10:8090/right");
          Serial.println(sensorReadings);
          JSONVar myObject = JSON.parse(sensorReadings);
          count_l = 0;
          count_n = 0;
        }
      }
      count_r += 1;
    }
    else {
      if (count_n == 2) {
        if (WiFi.status() == WL_CONNECTED) {
          sensorReadings = httpGETRequest("http://192.168.1.10:8090/normal");
          Serial.println(sensorReadings);
          JSONVar myObject = JSON.parse(sensorReadings);
          count_l = 0;
          count_r = 0;
        }
      }
      count_n += 1;
    }
  }
  delay(200);
}


String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;

  // Your IP address with path or Domain name with URL path
  http.begin(client, serverName);

  // Send HTTP POST request
  int httpResponseCode = http.GET();

  String payload = "{}";

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
  delay(1000);
}
