// POS LED to arduino 5V 
// NEG LED to arduino digital pin 3
// COM to arduino GND 
// NO to arduino digital pin 2

const int switchPinRed = 2;      // Digital pin connected to the red microswitch
const int externalLEDPinRed = 3; // Digital pin connected to the external red LED

// POS LED to arduino 5V 
// NEG LED to arduino digital pin 5
// COM to arduino GND 
// NO to arduino digital pin 4

const int switchPinBlue = 4;      // Digital pin connected to the blue microswitch
const int externalLEDPinBlue = 5; // Digital pin connected to the external blue LED

void setup() {
  pinMode(switchPinRed, INPUT_PULLUP);      // Enable internal pull-up resistor on the red switch pin
  pinMode(externalLEDPinRed, OUTPUT);       // Set the external red LED pin as an output

  pinMode(switchPinBlue, INPUT_PULLUP);     // Enable internal pull-up resistor on the blue switch pin
  pinMode(externalLEDPinBlue, OUTPUT);      // Set the external blue LED pin as an output

  pinMode(LED_BUILTIN, OUTPUT);              // Set the onboard LED as an output

  digitalWrite(LED_BUILTIN, HIGH);          // Turn on the onboard LED initially
  digitalWrite(externalLEDPinRed, LOW);    // Turn off the external red LED initially
  digitalWrite(externalLEDPinBlue, LOW);   // Turn off the external blue LED initially
}

void loop() {
  int switchStateRed = digitalRead(switchPinRed);
  int switchStateBlue = digitalRead(switchPinBlue);

  if (switchStateRed == HIGH && switchStateBlue == HIGH) {
    // No switch is pressed
    digitalWrite(LED_BUILTIN, LOW);          // Turn off the onboard LED
    digitalWrite(externalLEDPinRed, HIGH);    // Turn off the external red LED
    digitalWrite(externalLEDPinBlue, HIGH);   // Turn off the external blue LED
  } else if (switchStateRed == HIGH) {
    // Red switch is pressed
    digitalWrite(LED_BUILTIN, HIGH);           // Turn on the onboard LED
    digitalWrite(externalLEDPinRed, HIGH);   // Turn on the external red LED
    digitalWrite(externalLEDPinBlue, LOW);   // Turn off the external blue LED
  } else if (switchStateBlue == HIGH) {
    // Blue switch is pressed
    digitalWrite(LED_BUILTIN, HIGH);           // Turn on the onboard LED
    digitalWrite(externalLEDPinRed, LOW);    // Turn off the external red LED
    digitalWrite(externalLEDPinBlue, HIGH);  // Turn on the external blue LED
  }
}
