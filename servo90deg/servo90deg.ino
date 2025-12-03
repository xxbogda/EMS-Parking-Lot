#include <ESP32Servo.h>

Servo myServo;
int servopin = 18;

void setup() {
  myServo.attach(servopin);  // attaches the servo on pin 9 to the Servo object
  //myServo.write(0);
  Serial.begin(115200);
}

void loop() {
  myServo.write(120);
  delay(850);
  myServo.write(70);
  delay(900);


  /*for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }*/
}
