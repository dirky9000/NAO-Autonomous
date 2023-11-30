//1st define some constants if needed #define CNAME value
//2nd setup your programm, if you want serial plot, use Serial.begin(9600). Configuring pins with pinMode(Pin,Mode)
//3rd Loop logic always loops through the programm, if you want a loop with conditions, use while or for loops
//4th To control the pins, use digitalWrite(Pin,state), digitalRead(Pin)

// Assign pins to enable, direction, pulse
#define DIR 9
#define PUL 10
#define STEPS 400
// Changes speed of wheel turning
#define HALFPERIODTIME 1.5
#define BTNR 2
#define BTNL 3

int stepCount = 0;

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
    stepCount = 0;
    // define deirection after button pushed
    digitalWrite(DIR, LOW);
    // stepCount limits turning right
    while(digitalRead(BTNR)==HIGH){
      // Limit right turning distance
      // do one revolution counterclockwise (LOW)
      // if stepCount is less than or equal to 100 turn right
      if(stepCount <= 400){
        // do one revolution counterclockwise (LOW)
        delay(HALFPERIODTIME);
        digitalWrite(PUL, HIGH);
        delay(HALFPERIODTIME);
        digitalWrite(PUL, LOW);
        stepCount++;
      }
    }
    // once button is released turn back to center
    digitalWrite(DIR, HIGH);
    for(int i=0; i <= stepCount; i++){
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
  stepCount = 0;
  // define deirection after button pushed
  digitalWrite(DIR, HIGH);
  // stepCount limits turning left
  while(digitalRead(BTNL)==HIGH){
    // if stepCount is less than or equal to 100 turn left
    if(stepCount <= 400){
      // do one revolution counterclockwise (LOW)
      delay(HALFPERIODTIME);
      digitalWrite(PUL, HIGH);
      delay(HALFPERIODTIME);
      digitalWrite(PUL, LOW);
      stepCount++;
    }
  }
  // once button is released turn back to center
  digitalWrite(DIR, LOW);
    for(int i=0; i <= stepCount; i++){
      delay(HALFPERIODTIME);
      digitalWrite(PUL, HIGH);
      delay(HALFPERIODTIME);
      digitalWrite(PUL, LOW);
    }
    delay(10);

  }
}
