//1st define some constants if needed #define CNAME value
//2nd setup your programm, if you want serial plot, use Serial.begin(9600). Configuring pins with pinMode(Pin,Mode)
//3rd Loop logic always loops through the programm, if you want a loop with conditions, use while or for loops
//4th To control the pins, use digitalWrite(Pin,state), digitalRead(Pin)

// Assign pins to enable, direction, pulse
#define DIR 9
#define PUL 10
#define STEPS 400
#define HALFPERIODTIME 1.25

void setup() {
Serial.begin(9600);

 //Pin mode: Input, output, alternate function
 pinMode(DIR, OUTPUT);
 pinMode(PUL, OUTPUT);
}

void loop() {
  // implement output logic
    // do one revolution counterclockwise (LOW)
  digitalWrite(DIR, LOW);
  for(int n = 0; n<=STEPS; n++){
    delay(HALFPERIODTIME);
    digitalWrite(PUL, HIGH);
    delay(HALFPERIODTIME);
    digitalWrite(PUL, LOW);
  }
  //wait 1 second after 1 revolution
  delay(1000);

  // do one revolution clockwise (HIGH)
  digitalWrite(DIR, HIGH);
  for(int n = 0; n<=STEPS; n++){
    delay(HALFPERIODTIME);
    digitalWrite(PUL, HIGH);
    delay(HALFPERIODTIME);
    digitalWrite(PUL, LOW);
  }
  //wait 1 second after 1 revolution
  delay(1000);
}
