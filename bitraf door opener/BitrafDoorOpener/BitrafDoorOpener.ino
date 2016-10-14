#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

const int buttonPin = 4;
int buttonState = HIGH;
int lastState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();

  for(uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFiMulti.addAP("bitraf", "grimbadgerassault");
  WiFiMulti.addAP("bitraf24", "grimbadgerassault");

}


void openDoor() {
  HTTPClient http;

  Serial.print("[HTTP] begin...\n");
  http.begin("http://mattis.io/bitraf.php?key=fn3uht8g945hgerhg98rehyoi3hretu3438ttjjggr");

  Serial.print("[HTTP] GET...\n");
  
  int httpCode = http.GET();

  if(httpCode > 0) {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      if(httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println(payload);
      }
  } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}


void loop() {
  if((WiFiMulti.run() == WL_CONNECTED)) {
    digitalWrite(LED_BUILTIN, LOW);
  
    buttonState = digitalRead(buttonPin);

    if( lastState != buttonState ) {
      if( buttonState == LOW ) {
        Serial.println( "ON" );
        openDoor();
      }
      
      lastState = buttonState;
    }
  
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(900);
  }

  
  
  
  
  delay(100);
}




