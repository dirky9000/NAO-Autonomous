// COM to arduino GND 
// NO to arduino digital pin 2
// POS LED to arduino 5V 
// NEG LED to arduino digital pin 3

const int switchPinRed = 2;                    // Digital pin connected to the red microswitch
const int externalLEDPinRed = 3;               // Digital pin connected to the external red LED

// COM to arduino GND 
// NO to arduino digital pin 4
// POS LED to arduino 5V 
// NEG LED to arduino digital pin 5

const int switchPinBlue = 4;                    // Digital pin connected to the blue microswitch
const int externalLEDPinBlue = 5;               // Digital pin connected to the external blue LED

// COM to arduino GND 
// NO to arduino digital pin 6
// POS LED to arduino 5V t
// NEG LED to arduino digital pin 7

const int switchPinGreen = 6;                   // Digital pin connected to the green microswitch
const int externalLEDPinGreen = 7;              // Digital pin connected to the external green LED

// COM to arduino GND 
// NO to arduino digital pin 8
// POS LED to arduino 5V 
// NEG LED to arduino digital pin 9

const int switchPinYellow = 8;                  // Digital pin connected to the yellow microswitch
const int externalLEDPinYellow = 9;             // Digital pin connected to the external yellow LED

void setup() 
{
  pinMode(switchPinRed, INPUT_PULLUP);          // Enable internal pull-up resistor on the red switch pin
  pinMode(externalLEDPinRed, OUTPUT);           // Set the external red LED pin as an output

  pinMode(switchPinBlue, INPUT_PULLUP);         // Enable internal pull-up resistor on the blue switch pin
  pinMode(externalLEDPinBlue, OUTPUT);          // Set the external blue LED pin as an output

  pinMode(switchPinGreen, INPUT_PULLUP);        // Enable internal pull-up resistor on the green switch pin
  pinMode(externalLEDPinGreen, OUTPUT);         // Set the external green LED pin as an output

  pinMode(switchPinYellow, INPUT_PULLUP);       // Enable internal pull-up resistor on the yellow switch pin
  pinMode(externalLEDPinYellow, OUTPUT);        // Set the external yellow LED pin as an output

  pinMode(LED_BUILTIN, OUTPUT);                 // Set the onboard LED as an output

  digitalWrite(LED_BUILTIN, HIGH);              // Turn off the onboard LED initially
  digitalWrite(externalLEDPinRed, LOW);         // Turn off the external red LED initially
  digitalWrite(externalLEDPinBlue, LOW);        // Turn off the external blue LED initially
  digitalWrite(externalLEDPinGreen, LOW);       // Turn off the external green LED initially
  digitalWrite(externalLEDPinYellow, LOW);      // Turn off the external yellow LED initially
}

void loop() 
{
  int switchStateRed = digitalRead(switchPinRed);
  int switchStateBlue = digitalRead(switchPinBlue);
  int switchStateGreen = digitalRead(switchPinGreen);
  int switchStateYellow = digitalRead(switchPinYellow);

  if (switchStateRed == HIGH && switchStateBlue == HIGH && switchStateGreen == HIGH && switchStateYellow == HIGH) 
  {
    // No switch is pressed
    digitalWrite(LED_BUILTIN, LOW);             
    digitalWrite(externalLEDPinRed, HIGH);      
    digitalWrite(externalLEDPinBlue, HIGH);     
    digitalWrite(externalLEDPinGreen, HIGH);    
    digitalWrite(externalLEDPinYellow, HIGH);   
  } 
  else if (switchStateRed == HIGH) 
  {
    // Red switch is pressed
    digitalWrite(LED_BUILTIN, HIGH);            
    digitalWrite(externalLEDPinRed, HIGH);      
    digitalWrite(externalLEDPinBlue, LOW);      
    digitalWrite(externalLEDPinGreen, LOW);
    digitalWrite(externalLEDPinYellow, LOW);
  } 
  else if (switchStateBlue == HIGH) 
  {
    // Blue switch is pressed
    digitalWrite(LED_BUILTIN, HIGH);           
    digitalWrite(externalLEDPinRed, LOW);      
    digitalWrite(externalLEDPinBlue, HIGH);   
    digitalWrite(externalLEDPinGreen, LOW);
    digitalWrite(externalLEDPinYellow, LOW);
  } 
  else if (switchStateGreen == HIGH) 
  {
    // Green switch is pressed
    digitalWrite(LED_BUILTIN, HIGH);            
    digitalWrite(externalLEDPinRed, LOW);       
    digitalWrite(externalLEDPinBlue, LOW);      
    digitalWrite(externalLEDPinGreen, HIGH);
    digitalWrite(externalLEDPinYellow, LOW);
  } 
  else if (switchStateYellow == HIGH) 
  {
    // Yellow switch is pressed
    digitalWrite(LED_BUILTIN, HIGH);            
    digitalWrite(externalLEDPinRed, LOW);      
    digitalWrite(externalLEDPinBlue, LOW);    
    digitalWrite(externalLEDPinGreen, LOW);
    digitalWrite(externalLEDPinYellow, HIGH);
  }
}
