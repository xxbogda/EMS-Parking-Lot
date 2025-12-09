// --- COMMON CATHODE CONFIGURATION ---
// In Common Cathode: 
// Segments are HIGH to turn ON.
// Digit Common pins are LOW to activate the digit.

// Pin Definitions
const int segA = 13;
const int segB = 12;
const int segC = 14;
const int segD = 27;
const int segE = 26;
const int segF = 25;
const int segG = 33;

const int digit1_Common = 19; // Controls Left Digit
const int digit2_Common = 18; // Controls Right Digit

// Store segment pins in an array
const int segmentPins[] = {segA, segB, segC, segD, segE, segF, segG};

// Bitmap for numbers 0-9 (Common Cathode: 1 = ON, 0 = OFF)
const byte numbers[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

int counter = 0;
unsigned long lastUpdate = 0;

void setup() {
  // Set all segment pins to OUTPUT
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], LOW); // Turn off initially
  }
  
  // Set digit control pins to OUTPUT
  pinMode(digit1_Common, OUTPUT);
  pinMode(digit2_Common, OUTPUT);
  
  // Turn off both digits initially (HIGH = OFF for Common Cathode Commons)
  digitalWrite(digit1_Common, HIGH); 
  digitalWrite(digit2_Common, HIGH);
}

void loop() {
  // 1. Logic to change the number every second
  if (millis() - lastUpdate > 1000) {
    counter++;
    if (counter > 99) counter = 0;
    lastUpdate = millis();
  }

  // 2. Multiplexing Loop (Must run constantly)
  displayNumber(counter);
}

void displayNumber(int num) {
  int tens = num / 10;
  int units = num % 10;

  // -- Display Tens Digit --
  turnOffDigits();         // Turn off previous
  setSegments(tens);       // Prepare segments for number
  digitalWrite(digit1_Common, LOW); // Turn ON Digit 1 (LOW is ON for CC)
  delay(5);                // Wait 5ms

  // -- Display Units Digit --
  turnOffDigits();         // Turn off previous
  setSegments(units);      // Prepare segments for number
  digitalWrite(digit2_Common, LOW); // Turn ON Digit 2
  delay(5);                // Wait 5ms
}

void turnOffDigits() {
  // Pull Common pins HIGH to turn them OFF
  digitalWrite(digit1_Common, HIGH);
  digitalWrite(digit2_Common, HIGH);
}

void setSegments(int num) {
  for (int i = 0; i < 7; i++) {
    // Write HIGH to light up the segment
    digitalWrite(segmentPins[i], numbers[num][i]);
  }
}
