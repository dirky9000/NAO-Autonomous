// 1st define some constants if needed #define CNAME value
// 2nd setup your program, if you want serial plot, use Serial.begin(9600). Configuring pins with pinMode(Pin,Mode)
// 3rd Loop logic always loops through the program, if you want a loop with conditions, use while or for loops
// 4th To control the pins, use digitalWrite(Pin,state), digitalRead(Pin)

// Assign pins to enable, direction, pulse
#define DIR 9
#define PUL 10
#define STEPS 400
// Changes speed of wheel turning
#define HALFPERIODTIME 1.5
#define BTNR 2
#define BTNL 3

// Sensor pins
#define trigPin 4
#define echoPin 5

int stepCount = 0;

void setup() {
  Serial.begin(9600);

  // Pin mode: Input, output, alternate function
  // Pin mode for motor control
  pinMode(DIR, OUTPUT);
  pinMode(PUL, OUTPUT);

  // Pin mode for button control
  pinMode(BTNR, INPUT);
  pinMode(BTNL, INPUT);

  // For sensors
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {

  // Continuously measure the distance
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  // Speed of sound in air at 20°C is approximately 343 meters per second
  // Divide by 2 because the sound travels to the object and back
  float distanceCM = duration * 0.0343 / 2;

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distanceCM);
  Serial.println(" cm");

  // checks if measured distance is above 39cm 
  if(distanceCM > 39){
    delay(10); 
    stepCount = 0; // resets step count for turning 
    digitalWrite(DIR, HIGH); // sets direction to go left 
    
    // begin loop to turn left when distance is aboce 39cm
    while(distanceCM > 39){
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
  }
  // delay between measurements 
  delay(500);

  // Check if button right is pushed
  if (digitalRead(BTNR) == HIGH) {
    delay(10);
    stepCount = 0;
    // define direction after button pushed
    digitalWrite(DIR, LOW);
    // stepCount limits turning right
    while (digitalRead(BTNR) == HIGH) {
      // Limit right turning distance
      // do one revolution counterclockwise (LOW)
      // if stepCount is less than or equal to 100 turn right
      if (stepCount <= 400) {
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
    for (int i = 0; i <= stepCount; i++) {
      delay(HALFPERIODTIME);
      digitalWrite(PUL, HIGH);
      delay(HALFPERIODTIME);
      digitalWrite(PUL, LOW);
    }
    delay(10);
  }

  // Check if button left is pushed
  if (digitalRead(BTNL) == HIGH) {
    delay(10);
    stepCount = 0;
    // define direction after button pushed
    digitalWrite(DIR, HIGH);
    // stepCount limits turning left
    while (digitalRead(BTNL) == HIGH) {
      // if stepCount is less than or equal to 100 turn left
      if (stepCount <= 400) {
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
    for (int i = 0; i <= stepCount; i++) {
      delay(HALFPERIODTIME);
      digitalWrite(PUL, HIGH);
      delay(HALFPERIODTIME);
      digitalWrite(PUL, LOW);
    }
    delay(10);
  }
}
