#define SENSOR_PIN 18
#define SENSOR_PINS 19

#include <ESP32Servo.h>
#include <TimeLib.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT);
  servoMotor.attach(SERVO_PINS);
}

void loop() {
  // put your main code here, to run repeatedly:

  for (int pos = 0; pos <= 90; pos += 1) {
    // in steps of 1 degree
    servoMotor.write(pos);
    delay(15); // waits 15ms to reach the position
  }

  int state = digitalRead(SENSOR_PIN);
  if(state == LOW){
    Serial.println("GET DOWN MR PRESIDENT!"); // obstacle present
    // open barrier 
  }
  else{
    Serial.println("The obstacle is not present");
    
  }
  delay(100);

  /* time_t threshholdTime = 5;
  int signalTime;

  int lastState=HIGH;
  int currentState;

  if(lastState=HIGH and currentState = 


  if(trece signal= high->low) set signal_time=current_time;
  if(signal=low && current_time - signal_time > threshold_time) ridica bariera*/

}


