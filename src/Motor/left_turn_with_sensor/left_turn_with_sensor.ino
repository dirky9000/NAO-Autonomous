// Assign pins to enable, direction, pulse
#define DIR 9 // Direction pin for the motor
#define PUL 10 // Pulse pin for the motor 
#define STEPS 400 // Number of steps for a full revolution
// Changes speed of wheel turning
#define HALFPERIODTIME 1.5 // Time for each half period of the pulse
#define BTNR 2 // Pin for the right button
#define BTNL 3 // Pin for the left button

// Sensor pins
#define trigPin 4 // Pin for sensor trigger
#define echoPin 5 // Pin for sensor echo

int stepCount = 0; // Keeps track of steps taken 
float distanceCM;  // Declare distanceCM as a global variable
bool isTurning = false; // Specifies if wheel is currently turning
bool hasTurned = false;  // Variable to track whether the wheel has already turned


// Function to measure distance using sensor
void measureDistance() {
  // Measure the distance
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  distanceCM = duration * 0.0343 / 2;

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distanceCM);
  Serial.println(" cm");
}

// Setup function when the program starts 
void setup() {
  Serial.begin(9600); // Serial communication

  // Pin modes for motor, button, and sensors 
  pinMode(DIR, OUTPUT);
  pinMode(PUL, OUTPUT);
  pinMode(BTNR, INPUT);
  pinMode(BTNL, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

// Main loop function runs repeatedly
void loop() {
  // Function continuously measure the distance
  measureDistance();

  // Check if the wheel needs to turn and hasn't turned yet
  if (distanceCM < 39 && !isTurning && !hasTurned) {
    isTurning = true;  // Set the flag to indicate turning

    // Reset step count for turning
    stepCount = 0;

    // Set direction to go left
    digitalWrite(DIR, HIGH);

    // Begin loop to turn left when distance is above 39cm
    while (stepCount <= 400) {
      // Do one revolution counterclockwise (LOW)
      delay(HALFPERIODTIME);
      digitalWrite(PUL, HIGH);
      delay(HALFPERIODTIME);
      digitalWrite(PUL, LOW);
      stepCount++;
    }

    hasTurned = true; // Set the flag to indicate that the wheel has turned
    isTurning = false;  // Reset the flag after turning is complete
  }

  // Check if the wheel needs to go back to the middle and has turned left
  if (distanceCM > 39 && hasTurned) {
    isTurning = true;  // Set the flag to indicate turning

    // Set direction to go right (back to the middle)
    digitalWrite(DIR, LOW);

    // Begin loop to turn right until it reaches the middle
    for (int i = 0; i <= stepCount; i++) {
      delay(HALFPERIODTIME);
      digitalWrite(PUL, HIGH);
      delay(HALFPERIODTIME);
      digitalWrite(PUL, LOW);
    }

    // Reset the flags and step count after returning to the middle
    hasTurned = false;
    isTurning = false;
    stepCount = 0;
  }

  // Delay between measurements
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