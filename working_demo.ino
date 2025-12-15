#include <Servo.h>
#include <Time.h>

// NFC
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
  String tagId1 = "FA 5F 99 1A";
  String tagId2= "39 0B B6 B0";
String tagId = "None";
byte nuidPICC[4];

// SSD
int digit[10] = {0b0111111, 0b0000110, 0b1011011, 0b1001111, 0b1100110, 0b1101101, 0b1111101, 0b0000111, 0b1111111, 0b1101111};

#define IR1_PIN A2 //ENTRY INFRARED PIN
#define SME_PIN 13 //ENTRY SERVOMOTOR PIN
#define IR2_PIN A0 //EXIT INFRARED PIN
#define SMX_PIN 10 //EXIT SERVOMOTOR PIN

int carCount=0;
int carCapacity=3;
bool FULL= false;
bool empty=false;
bool BE=false;
bool BX=false; // STATE OF BARRIERS (maybe not a good idea)
Servo SME;
Servo SMX;

int lastStateIR1=HIGH;
int lastStateIR2=HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN,OUTPUT); //nfc

  pinMode(IR1_PIN, INPUT);
  SME.attach(SME_PIN);

  pinMode(IR2_PIN, INPUT);
  SMX.attach(SMX_PIN);

  nfc.begin();
  digitalWrite(LED_BUILTIN, LOW); //nfc

  for (int i = 2; i < 9; i++) //ssd
  {
    pinMode(i, OUTPUT); 
  }
  pinMode(12, OUTPUT); //declare 7 seg Digit1 pin as output
  pinMode(11, OUTPUT); //declare 7 seg Digit2 pin as output
}

void loop() {

  int stateIR1 = digitalRead(IR1_PIN); // LOW->object ; HIGH->NO object
  int stateIR2 = digitalRead(IR2_PIN);
  readNFC();

  // NFC -------------------------------------------------------------

  if (tagId == tagId1 || tagId == tagId2) {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  tagId = "";
  }
  // if(tagId==tagId1)
  // {
  //   if( digitalRead(LED_BUILTIN) == 0)
  //   {
  //     digitalWrite(LED_BUILTIN, HIGH);
  //     tagId = "";
  //     delay(100);
  //   }
  // }

  // if(tagId==tagId1)
  // {
  //   if( digitalRead(LED_BUILTIN) == 1)
  //   {
  //     digitalWrite(LED_BUILTIN, LOW);
  //     tagId = "";
  //     delay(100);
  //   }
  // }

  // if(tagId==tagId2)
  // {
  //   if( digitalRead(LED_BUILTIN) == 0)
  //   {
  //     digitalWrite(LED_BUILTIN, HIGH);
  //     tagId = "";
  //     delay(100);
      
  //   }
  // }

  // if(tagId==tagId2)
  // {
  //   if( digitalRead(LED_BUILTIN) == 1)
  //   {
  //     digitalWrite(LED_BUILTIN, LOW);
  //     tagId = "";
  //     delay(100); //1000
  //   }
  // }

  // DISPLAY CAR COUNT -----------------------------------------------

  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  dis(carCount/10);
  delay(10);
  digitalWrite(12, HIGH);
  digitalWrite(11, LOW);
  dis(carCount%10);
  delay(10);

  // B1 operation ----------------------------------------------------

  if( !FULL and !BE and !FULL and nfc.tagPresent() and stateIR1 == LOW ){ //
    SME.write(120);
    delay(850); 
    SME.write(100);

    BE=1;
  }

  if( BE and lastStateIR1 == LOW and stateIR1 == HIGH){
    delay(400);
    SME.write(70);
    delay(800);
    SME.write(100);

    if(empty) empty=0;
    carCount++;
    if(carCount >= carCapacity) FULL=1;
    BE=0;
  }

  // B2 operation ----------------------------------------------------

  if( !empty and !BX and lastStateIR2 == HIGH and stateIR2 == LOW){
    SMX.write(120);
    delay(800);
    SMX.write(100);

    BX=1;
  }

  if( !empty and BX and lastStateIR2 == LOW and stateIR2 == HIGH){
    delay(400);
    SMX.write(70);
    delay(800);
    SMX.write(100);

    if(FULL) FULL=0;
    carCount--;
    if(carCount==0) empty=1;
    BX=0;
  }

  lastStateIR1=stateIR1;
  lastStateIR2=stateIR2;
}

// void readNFC() {
//   if (nfc.tagPresent())
//   {
//     NfcTag tag = nfc.read();
//     tag.print();
//     tagId = tag.getUidString();
//     Serial.println("Tag id");
//     Serial.println(tagId);
//   }
//   delay(100);
// }

void readNFC() {
  static unsigned long lastRead = 0;
  if (millis() - lastRead < 300) return;

  if (nfc.tagPresent()) {
    NfcTag tag = nfc.read();
    tagId = tag.getUidString();
    lastRead = millis();
  }
}

void dis(int num)
{
  for (int i = 2; i < 9; i++)
  {
    digitalWrite(i, bitRead(digit[num], i - 2));
  }
}
