#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>


#define ONE_WIRE_BUS D1

unsigned long myChannelNumber = 167909;
String myWriteAPIKey = "PNXQ5IK2NE34JQCY";

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
ESP8266WiFiMulti WiFiMulti;
WiFiClient client;


void setup() {
  Serial.begin(115200);
  sensors.begin();

  // We start by connecting to a WiFi network
  WiFiMulti.addAP("BjeOrvGet", "TreskoenTreskoen");

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while(WiFiMulti.run() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);
}


float getTemperature() {
  float temp;
  do {
    sensors.requestTemperatures(); 
    temp = sensors.getTempCByIndex(0);
    delay(100);
  } while (temp == 85.0 || temp == (-127.0));
  return temp;
}


void loop() {
  Serial.println("READ");


  float temp;
  temp = getTemperature();

  Serial.println(temp);



  if (client.connect("api.thingspeak.com",80)) {  //   "184.106.153.149" or api.thingspeak.com
    String postStr = myWriteAPIKey;
           postStr +="&field1=";
           postStr += String(temp);
           postStr += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n"); 
     client.print("Host: api.thingspeak.com\n"); 
     client.print("Connection: close\n"); 
     client.print("X-THINGSPEAKAPIKEY: "+myWriteAPIKey+"\n"); 
     client.print("Content-Type: application/x-www-form-urlencoded\n"); 
     client.print("Content-Length: "); 
     client.print(postStr.length()); 
     client.print("\n\n"); 
     client.print(postStr);
           
 
     Serial.print("SUCCESS"); 
  }
  
  client.stop();


  
  delay(30000);
}

