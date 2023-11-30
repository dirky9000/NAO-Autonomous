//1st define some constants if needed #define CNAME value
//2nd setup your programm, if you want serial plot, use Serial.begin(9600). Configuring pins with pinMode(Pin,Mode)
//3rd Loop logic always loops through the programm, if you want a loop with conditions, use while or for loops
//4th To control the pins, use digitalWrite(Pin,state), digitalRead(Pin)

// Assign pins to enable, direction, pulse
#define DIR 9
#define PUL 10
#define STEPS 400
#define HALFPERIODTIME 1.25
#define BTNR 2
#define BTNL 3

void setup() {
Serial.begin(9600);

 //Pin mode: Input, output, alternate function
 //Pin mode for mototr control
 pinMode(DIR, OUTPUT);
 pinMode(PUL, OUTPUT);

  //Pin mode for button control
 pinMode(BTNR, INPUT);
 pinMode(BTNL, INPUT);

}

void loop() {

  //Check if button right is pushed
  if(digitalRead(BTNR)==HIGH){
    delay(10);
    // define deirection after button pushed
    digitalWrite(DIR, LOW);
    while(digitalRead(BTNR)==HIGH){
      // do one revolution counterclockwise (LOW)
      delay(HALFPERIODTIME);
      digitalWrite(PUL, HIGH);
      delay(HALFPERIODTIME);
      digitalWrite(PUL, LOW);
    }
    delay(10);
  }

//Check if button left is pushed
 if(digitalRead(BTNL)==HIGH){
  delay(10);
  // define deirection after button pushed
  digitalWrite(DIR, HIGH);
  while(digitalRead(BTNL)==HIGH){
    // do one revolution counterclockwise (LOW)
    delay(HALFPERIODTIME);
    digitalWrite(PUL, HIGH);
    delay(HALFPERIODTIME);
    digitalWrite(PUL, LOW);
  }
    delay(10);
  }
}