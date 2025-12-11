#include <Servo.h>
#include <Time.h>

#define IR1_PIN 2 //ENTRY INFRARED PIN
#define SME_PIN 8 //ENTRY SERVOMOTOR PIN
#define IR2_PIN 3 //EXIT INFRARED PIN
#define SMX_PIN 9 //EXIT SERVOMOTOR PIN

int carCount=0;
int carCapacity=20;
bool FULL= false;
bool BE=false;
bool BX=false; // STATE OF BARRIERS (maybe not a good idea)
Servo SME;
Servo SMX;

int lastStateIR1=HIGH;
int lastStateIR2=HIGH;

void setup() {
  Serial.begin(115200);

  pinMode(IR1_PIN, INPUT);
  SME.attach(SME_PIN);

  pinMode(IR2_PIN, INPUT);
  SMX.attach(SMX_PIN);
}

void loop() {

  int stateIR1 = digitalRead(IR1_PIN); // LOW->object ; HIGH->NO object
  int stateIR2 = digitalRead(IR2_PIN);

  // DISPLAY CAR COUNT -----------------------------------------------

  if(carCount >= carCapacity) FULL=1;
  if(FULL){
    Serial.println("Parking lot full!");
  }
  else{
    Serial.println(carCount);
  }

  // B1 operation ----------------------------------------------------

  if( !BE and !FULL /*and CARD_INPUT*/ and stateIR1 == LOW ){
    SME.write(120);
    delay(850); 
    SME.write(100);

    BE=1;
  }

  if( BE and lastStateIR1 == LOW and stateIR1 == HIGH){
    delay(3000);
    SME.write(70);
    delay(900);
    SME.write(100);

    carCount++;
    BE=0;
  }

  // B2 operation ----------------------------------------------------

  if( !BX and lastStateIR2 == HIGH and stateIR2 == LOW){
    SMX.write(120);
    delay(850);
    SMX.write(100);

    BX=1;
  }

  if( BX and lastStateIR2 == LOW and stateIR2 == HIGH){
    delay(3000);
    SMX.write(70);
    delay(900);
    SMX.write(100);

    carCount--;
    BX=0;
  }

  delay(100);
  lastStateIR1=stateIR1;
  lastStateIR2=stateIR2;
}