#define greenLedPin 6 // green
#define redLedPin 3 // red 
int inputButton1 = 22;
int bLastButtonVal1 = 0 == 1;
int bPushed = 0;
int numberPresses = 0;

void setup() {
  pinMode(inputButton1, INPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  Serial.begin(9600);  
}
void loop() {
  bPushed = digitalRead(inputButton1);
  if (bPushed == HIGH) {
    if (bLastButtonVal1 != bPushed) {
      Serial.println("Y");
      bLastButtonVal1 = HIGH;
    }
  }
  else {
    bLastButtonVal1 = LOW;
  }
 
  int command = Serial.read();
  if (command == 103) { // 'g'
    for ( int i = 0; i < 5; ++i ) {
      analogWrite( greenLedPin, 200 );
      delay(500);
      analogWrite( greenLedPin, 0 );
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