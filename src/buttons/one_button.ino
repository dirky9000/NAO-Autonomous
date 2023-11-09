// POS LED to arduino 5V 
// NEG LED to arduino digital pin 3
// COM to arduino GND 
// NO to arduino digital pin 2

const int switchPin = 2;      // Digital pin connected to the microswitch
const int externalLEDPin = 3; // Digital pin connected to the external LED

void setup() {
  pinMode(switchPin, INPUT_PULLUP);   // Enable internal pull-up resistor on the switch pin
  pinMode(externalLEDPin, OUTPUT);    // Set the external LED pin as an output
  pinMode(LED_BUILTIN, OUTPUT);       // Set the onboard LED as an output

  digitalWrite(LED_BUILTIN, HIGH);    // Turn on the onboard LED initially
  digitalWrite(externalLEDPin, LOW);  // Turn off the external LED initially
}

void loop() {
  int switchState = digitalRead(switchPin);

  if (switchState == HIGH) {  // The microswitch is not pressed (Normally closed state)
    digitalWrite(LED_BUILTIN, LOW);  // Turn off the onboard LED
    digitalWrite(externalLEDPin, HIGH); // Turn on the external LED
  } else {  // The microswitch is not pressed (Normally open state)
    digitalWrite(LED_BUILTIN, HIGH);   // Turn on the onboard LED
    digitalWrite(externalLEDPin, LOW);  // Turn off the external LED
  }
}
