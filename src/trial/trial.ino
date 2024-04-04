/*
#define inputButton1 2

void setup() {
  pinMode(inputButton1, INPUT);
  Serial.begin(9600);
}

void handleButton(int buttonPin, const char* buttonName) {
  if (digitalRead(buttonPin) == HIGH) {
    Serial.print(buttonName);
    Serial.println(" Button Pressed");
    while (digitalRead(buttonPin) == HIGH) {
      delay(10); // Wait for button release
    }
  }
}

void loop() {
  handleButton(inputButton1, "Button A");

  if (Serial.available() > 0) {
    int command = Serial.read();
    if (command == 'b') {
      // Blue LED control code removed
    }
    else if (command == 'r') {
      // Red LED control code removed
    }
  }
}
*/

// POS LED to arduino 5V 
// NEG LED to arduino digital pin 3
// COM to arduino GND 
// NO to arduino digital pin 2
/*
const int switchPin = 2;      // Digital pin connected to the microswitch
const int externalLEDPin = 3; // Digital pin connected to the external LED

void setup() {
  pinMode(switchPin, INPUT_PULLUP);   // Enable internal pull-up resistor on the switch pin
  pinMode(externalLEDPin, OUTPUT);    // Set the external LED pin as an output
  digitalWrite(externalLEDPin, LOW);  // Turn off the external LED initially

  Serial.begin(9600); // Start the serial communication with the baud rate of 9600
}

void loop() {
  int switchState = digitalRead(switchPin);

  if (switchState == HIGH) {  // The microswitch is not pressed (Normally closed state)
    digitalWrite(externalLEDPin, HIGH); // Turn on the external LED
  } else {  // The microswitch is pressed (Normally open state)
    digitalWrite(externalLEDPin, LOW);  // Turn off the external LED
    Serial.println("r"); // Print "r" to the serial monitor
  }
}
*/
/*
const int switchPin = 2;      // Digital pin connected to the microswitch
const int externalLEDPin = 3; // Digital pin connected to the external LED
int lastSwitchState = HIGH;   // Last state of the switch

void setup() {
  pinMode(switchPin, INPUT_PULLUP);   // Enable internal pull-up resistor on the switch pin
  pinMode(externalLEDPin, OUTPUT);    // Set the external LED pin as an output
  digitalWrite(externalLEDPin, LOW);  // Turn off the external LED initially

  Serial.begin(9600); // Start the serial communication with the baud rate of 9600
}

void loop() {
  int switchState = digitalRead(switchPin);

  if (switchState == HIGH) {  // The microswitch is not pressed (Normally closed state)
    digitalWrite(externalLEDPin, HIGH); // Turn on the external LED
  } else if (switchState == LOW && lastSwitchState == HIGH) {  // The microswitch is pressed (Normally open state)
    digitalWrite(externalLEDPin, LOW);  // Turn off the external LED
    Serial.println("r"); // Print "r" to the serial monitor
  }

  lastSwitchState = switchState; // Save the current state of the switch

  int command = Serial.read();

  if (command == 114) {
    // Add the functionality you want when 'r' is received
    if (switchState == HIGH) {  // The microswitch is not pressed (Normally closed state)
      digitalWrite(externalLEDPin, HIGH); // Turn on the external LED
    } 
    else if (switchState == LOW && lastSwitchState == HIGH) {  // The microswitch is pressed (Normally open state)
      digitalWrite(externalLEDPin, LOW);  // Turn off the external LED
    }
  }
}
*/
#define blueLedPin 6 // green
#define redLedPin 3 // red 

void setup() {
  pinMode(blueLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  Serial.begin(9600);  
}
void loop() {

  // This is for the NAO to understand from the arduino
  int command = Serial.read();
  if (command == 98) { // 'b'
    for ( int i = 0; i < 5; ++i ) {
      analogWrite( blueLedPin, 200 );
      delay(500);
      analogWrite( blueLedPin, 0 );
      delay(500);
    }
  }

  if (command == 114) { // 'r'
    for ( int i = 0; i < 5; ++i ) {
      analogWrite( redLedPin, 200 );
      delay(500);
      analogWrite( redLedPin, 0 );
      delay(500);
    }
  }
}