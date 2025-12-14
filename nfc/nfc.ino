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
 
void setup(void) {
  Serial.begin(115200);
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.println("System initialized");
 
  nfc.begin();
   digitalWrite(LED_BUILTIN, LOW);
}
 
void loop() {
  readNFC();
  if(tagId==tagId1)
  {
    if( digitalRead(LED_BUILTIN) == 0)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      tagId = "";
      delay(1000);
      
    }
 
  }
 
      if(tagId==tagId1)
  {
             if( digitalRead(LED_BUILTIN) == 1)
    {
      digitalWrite(LED_BUILTIN, LOW);
      tagId = "";
      delay(1000);
    }
 
  }
      
      if(tagId==tagId2)
  {
    if( digitalRead(LED_BUILTIN) == 0)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      tagId = "";
      delay(1000);
      
    }
 
  }
 
      if(tagId==tagId2)
  {
             if( digitalRead(LED_BUILTIN) == 1)
    {
      digitalWrite(LED_BUILTIN, LOW);
      tagId = "";
      delay(1000);
    }
 
  }
 
}
 
void readNFC() {
  if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read();
    tag.print();
    tagId = tag.getUidString();
    Serial.println("Tag id");
    Serial.println(tagId);
  }
  delay(1000);
}