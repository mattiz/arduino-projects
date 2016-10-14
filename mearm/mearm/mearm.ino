#include <Servo.h>
#include <Arduino.h>


Servo myservo1, myservo2, myservo3, myservo4;


void setup() {
  Serial.begin(9600);
  
  myservo1.attach(11);
  myservo2.attach(10);
  myservo3.attach(9);
  myservo4.attach(8);
}


void loop() {
  //myservo1.write(90);
  //myservo2.write(180);
  //myservo3.write(60);
  //myservo4.write(90);


  // Servo 1: 15 til 55
  myservo1.write(40);


  // Servo 3: 0 - 160
  myservo3.write(90);
  //int i;
  //for( i = 160; i > 0; i -= 1 ) {
  //  myservo3.write(i);
  //  delay(10);
  //}



  //int step = 1;
  //int wait = 10;

  //int i;
  //for( i = 20; i <= 160; i += step ) {
  //  myservo4.write(i);
  //  delay(wait);
  //}

  //for( i = 160; i > 20; i -= step ) {
    //myservo4.write(i);
    //delay(wait);
  //}

  
  

  delay(1000);

  myservo1.detach();
  myservo2.detach();
  myservo3.detach();
  myservo4.detach();

  while(1);
}
