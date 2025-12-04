#define IR1_PIN 18 //ENTRY INFRARED PIN
#define SM1_PIN 19 //ENTRY SERVOMOTOR PIN
// #define IR2_PIN ? //EXIT INFRARED PIN
// #define SM2_PIN ? //EXIT SERVOMOTOR PIN

#include <ESP32Servo.h>
#include <TimeLib.h>

int carCount=0;
int carCapacity=20;
bool FULL=0;

bool B1=0;
bool B2=0; // STATE OF BARRIERS (maybe not a good idea)

int lastStateIR1=HIGH;
int lastStateIR2=HIGH;
time_t thresholdTime = 5;

void setup() {
  Serial.begin(115200);

  pinMode(IR1_PIN, INPUT);
  SM1.attach(SM1_PIN);

  // pinMode(IR2_PIN, INPUT);
  // servoMotor.attach(SM2_PIN);
}

void loop() {
  
  int IR1RisingTime; // rise lower like clock
  int IR2LoweringTime;
  int IR2RisingTime;

  int StateIR1 = digitalRead(IR1_PIN); // LOW->object ; HIGH->NO object
  int StateIR2 = digitalRead(IR2_PIN);

  // DISPLAY CAR COUNT -----------------------------------------------

  if(carCount >= carCapacity) FULL=1;
  if(FULL){
    //display PARKING LOT FULL
  }
  else{
    // display CAR COUNT
  }

  // B1 operation ----------------------------------------------------

  if( !B1 and !FULL and CARD_INPUT and IRState == LOW ){
    SM1.write(120);
    delay(850);
    SM1.write(100); //rotate speed 120 for 850ms, then stop at "speed" 100

    B1=1;
  }

  if( B1 and lastStateIR1 == LOW and stateIR1 == HIGH) IR1RisingTime = now();

  if( B1 and stateIR1 == LOW and now() - IR1RisingTime > thresholdTime){
    SM1.write(70);
    delay(900);
    SM1.write(100);

    carCount++;
    B1=0;
  }

  // B2 operation ----------------------------------------------------

  if( !B2 and lastStateIR2 == HIGH and stateIR2 == LOW) IR2LoweringTime = now();

  if( !B2 and stateIR2 == LOW and now() - IR2LoweringTime > thresholdTime){
    SM1.write(120);
    delay(850);
    SM1.write(100);

    B2=1;
  }


  if( B2 and lastStateIR2 == LOW and stateIR2 == HIGH) IR2RisingTime = now();

  if( B2 and stateIR2 == LOW and now() - IR2RisingTime > thresholdTime){
    SM1.write(70);
    delay(900);
    SM1.write(100);

    carCount--;
    B2=0;
  }


  delay(100);
  lastStateIR1=StateIR1;
  lastStateIR2=StateIR2;
}