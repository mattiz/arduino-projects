

#include <XBee.h>
#include <SoftwareSerial.h>



// Define SoftSerial TX/RX pins
// Connect Arduino pin 8 to TX of usb-serial device
uint8_t ssRX = 8;
// Connect Arduino pin 9 to RX of usb-serial device
uint8_t ssTX = 9;
// Remember to connect all devices to a common Ground: XBee, Arduino and USB-Serial device
SoftwareSerial nss(ssRX, ssTX);

XBee xbee = XBee();



// Set DIO0 (pin 20) to Analog Input
uint8_t cmd[] = { 'D', '4' };
uint8_t value[] = { 0x4 };

// SH + SL of your remote radio
XBeeAddress64 remoteAddress = XBeeAddress64(0x00000000, 0x00000001);
// Create a remote AT request with the IR command
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(remoteAddress, cmd, value, sizeof(value));
  
// Create a Remote AT response object
RemoteAtCommandResponse remoteAtResponse = RemoteAtCommandResponse();


uint8_t payload[] = { 'H', 'e', 'l', 'l', 'o' };
// ZBTxRequest zbTx = ZBTxRequest(remoteAddress, payload, sizeof(payload));
Tx16Request tx = Tx16Request(0x0001, payload, sizeof(payload));


void setup() { 
  Serial.begin(9600);
  xbee.begin(Serial);
  // start soft serial
  nss.begin(9600);
  
 delay(5000);
 Serial.println("Sending request");	
 xbee.send(remoteAtRequest);
 



}

void loop() {
  delay(1000);
  Serial.println("Sending text");	
  xbee.send(tx);
  //while (1) {};
}
