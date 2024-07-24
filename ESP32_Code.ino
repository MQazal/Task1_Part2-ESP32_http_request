#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Define LED pins and thier transitions
const int LED1 = 2;
const int LED2 = 4;
void loop() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  delay(500);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(500);
}

const char* serverUrl1 = "https://s-m.com.sa/f.html";
const char* serverUrl2 = "https://s-m.com.sa/s.html";

void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, LOW); // Ensure LED1 is off initially
  digitalWrite(LED2, LOW); // Ensure LED2 is off initially

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.println(WiFi.localIP());

  if (WiFi.status() == WL_CONNECTED) {
    // Check first server
    HTTPClient http1;
    http1.begin(serverUrl1);
    int httpResponseCode1 = http1.GET();
    
    Serial.println(httpResponseCode1);
    
    if (httpResponseCode1 > 0) {
      String payload1 = http1.getString();
      Serial.println("Response from first webpage: " + payload1);
      
      if (payload1.indexOf("forward") != -1) {
        digitalWrite(LED1, HIGH); // Turn on LED1
        Serial.println("LED1 ON");
      } else {
        digitalWrite(LED1, LOW); // Turn off LED1
        Serial.println("LED1 OFF");
      }
    } else {
      Serial.print("Error on first HTTP request: ");
      Serial.println(httpResponseCode1);
    }

    http1.end();

    // Check second server
    HTTPClient http2;
    http2.begin(serverUrl2);
    int httpResponseCode2 = http2.GET();
    
    Serial.println(httpResponseCode2);
    
    if (httpResponseCode2 > 0) {
      String payload2 = http2.getString();
      Serial.println("Response from second webpage: " + payload2);
      
      if (payload2.indexOf("stop") != -1) {
        digitalWrite(LED2, HIGH); // Turn on LED2
        Serial.println("LED2 ON");
      } else {
        digitalWrite(LED2, LOW); // Turn off LED2
        Serial.println("LED2 OFF");
      }
    } else {
      Serial.print("Error on second HTTP request: ");
      Serial.println(httpResponseCode2);
    }

    http2.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
}