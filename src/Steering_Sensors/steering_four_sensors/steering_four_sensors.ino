// Assign pins to enable, direction, pulse
#define DIR 9 // Direction pin for the motor
#define PUL 10 // Pulse pin for the motor 
#define STEPS 400 // Number of steps for a full revolution
// Changes speed of wheel turning
#define HALFPERIODTIME 1.5 // Time for each half period of the pulse
#define BTNR 2 // Pin for the right button
#define BTNL 3 // Pin for the left button

// Sensor pins
#define trigPin1 50 // Sensor 1 trig pin
#define echoPin1 51 // Sensor 1 echo pin
#define trigPin2 44 // Sensor 2 trig pin
#define echoPin2 45 // Sensor 2 echo pin
#define trigPin3 38 // Sensor 3 trig pin
#define echoPin3 39 // Sensor 3 echo pin
#define trigPin4 32 // Sensor 4 trig pin
#define echoPin4 33 // Sensor 4 echo pin
#define trigPin5 26 // Sensor 5 trig pin
#define echoPin5 27 // Sensor 5 echo pin
#define trigPin6 22 // Sensor 6 trig pin
#define echoPin6 23 // Sensor 6 echo pin

#define desiredMeasurementSensor1 39
#define desiredMeasurementSensor4 35
#define desiredMeasurementSensor3 39
#define desiredMeasurementSensor5 35
#define tolerance 5

int stepCount = 0; // Keeps track of steps taken 
bool isTurningLeft = false; // Specifies if wheel is currently turning
bool hasTurnedLeft = false;  // Variable to track whether the wheel has already turned
bool isTurningRight = false; // Specifies if wheel is currently turning
bool hasTurnedRight = false;  // Variable to track whether the wheel has already turned
bool makeRight = false; 
bool madeRight = false;
bool someWait = false;
bool nowReallign = false;

// Motor  connections
int enA = 7;
int in1 = 52;
int in2 = 53;
// out1 -> purple connection on motor
// out2 -> orange connection on motor
// Switching the outputs will cause the car to move in reverse

// Setup function when the program starts 
void setup() {
  Serial.begin(9600); // Serial communication

  // Pin modes for motor, button, and sensors 
  pinMode(DIR, OUTPUT);
  pinMode(PUL, OUTPUT);
  pinMode(BTNR, INPUT);
  pinMode(BTNL, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  pinMode(trigPin5, OUTPUT);
  pinMode(echoPin5, INPUT);
  pinMode(trigPin6, OUTPUT);
  pinMode(echoPin6, INPUT);

  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

// Function to measure distance using sensor
float measureDistance(int trigPin, int echoPin) {
  // Measure the distance
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  float distanceCM = duration * 0.0343 / 2;

  return distanceCM;
}

void turnLeft() {
  delay(HALFPERIODTIME);
  digitalWrite(PUL, HIGH);
  delay(HALFPERIODTIME);
  digitalWrite(PUL, LOW);
  driveForward();
}

void turnRight() {
  delay(HALFPERIODTIME);
  digitalWrite(PUL, HIGH);
  delay(HALFPERIODTIME);
  digitalWrite(PUL, LOW);
  driveForward();
}

// This function lets you control spinning direction of motors
void driveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 255);
}

// Main loop function runs repeatedly
void loop() {
  ////////////////////////////////////////////////////////////////////////
  
  
  // added a delay on when the sensors start working because without, the wheel turns automatically for some reason
  static bool sensorsStart = false;

  if (!sensorsStart) {
    delay(1000);
    sensorsStart = true;
  }
  
  // Function continuously measure the distance
  float distance1 = measureDistance(trigPin1, echoPin1);
  float distance2 = measureDistance(trigPin2, echoPin2);
  float distance3 = measureDistance(trigPin3, echoPin3);
  float distance4 = measureDistance(trigPin4, echoPin4);
  float distance5 = measureDistance(trigPin5, echoPin5);
  float distance6 = measureDistance(trigPin6, echoPin6);

  // Reads distnaces onto the serial monitor 
  Serial.print("Sensor 1: ");
  Serial.print(distance1);
  Serial.println(" cm");

  Serial.print("Sensor 2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  Serial.print("Sensor 3: ");
  Serial.print(distance3);
  Serial.println(" cm");

  Serial.print("Sensor 4: ");
  Serial.print(distance4);
  Serial.println(" cm");

  Serial.print("Sensor 5: ");
  Serial.print(distance5);
  Serial.println(" cm");

  Serial.print("Sensor 6: ");
  Serial.print(distance6);
  Serial.println(" cm");
  
  ////////////////////////////////////////////////////////////////////////
  
  // Check all conditions
  bool condition1 = (distance3 > (desiredMeasurementSensor3 + tolerance)) && (distance5 > (desiredMeasurementSensor5 + tolerance));
  bool condition2 = (distance2 < 110 || distance6 < 20);
  bool condition3 = (distance2 > 110 && distance6 > 20);
  
  if (condition2 && !isTurningLeft && !hasTurnedLeft) {
    // Code to turn left
    isTurningLeft = true;  // Set the flag to indicate turning

    // Reset step count for turning
    stepCount = 0;

    // Set direction to go left
    digitalWrite(DIR, HIGH);

    // Do one full turn (250 steps) counterclockwise (LOW)
    while (stepCount <= 320) {
        turnLeft();
        stepCount++;
    }

    // Set the flag to indicate that the wheel has turned
    hasTurnedLeft = true;

    // Reset the flag after turning is complete
    isTurningLeft = false;
  }

  if (condition3 && hasTurnedLeft) {    
    // Code to return to the middle
    isTurningLeft = true;  // Set the flag to indicate turning

    // Set direction to go right (back to the middle)
    digitalWrite(DIR, LOW);

    // Begin loop to turn right until it reaches the middle
    for (int i = 0; i <= stepCount; i++) {
      turnRight();
    }

    // Reset the flags and step count after returning to the middle
    hasTurnedLeft = false;
    isTurningLeft = false;
    makeRight = true;
    stepCount = 0;
  }

// Check if the specified conditions are met for making a right turn of 330 steps
if (makeRight) {
    // Code to turn right

    // Reset step count for turning
    stepCount = 0;

    // Set direction to go right
    digitalWrite(DIR, LOW);

    // Do one full turn (330 steps) clockwise (HIGH)
    while (stepCount <= 330) {
        turnRight();
        stepCount++;
    }

    // Get the current time
    unsigned long startTime = millis();

    // Wait for 1 second
    while (millis() - startTime < 1000) {
        // Keep the motors running during this time
        driveForward();
    }

    makeRight = false;
    madeRight = true;
}

  // Check if the specified conditions are met for making a right turn of 330 steps
  if (madeRight) {
      // Code to turn right

      // Set direction to go right
      digitalWrite(DIR, HIGH);

    // Begin loop to turn right until it reaches the middle
    for (int i = 0; i <= stepCount; i++) {
      turnLeft();
    }

      madeRight = false;
      nowReallign = true;
  }

  if (condition1 && nowReallign) {
    // If both conditions are met, turn the wheel left
    // Reset step count for turning
    int stepCount = 0;

    // Set direction to go right
    digitalWrite(DIR, LOW);

    // Gradually turn the wheel until it is back in the desired range for both sensors
    while (distance3 > (desiredMeasurementSensor3 + tolerance) && distance5 > (desiredMeasurementSensor5 + tolerance)) {
      digitalWrite(PUL, HIGH); // Step
      delay(HALFPERIODTIME);
      digitalWrite(PUL, LOW);
      delay(HALFPERIODTIME);
      
      // Update distance readings
      distance3 = measureDistance(trigPin3, echoPin3);
      distance5 = measureDistance(trigPin5, echoPin5);
      
      stepCount++;
      
      // Prevent infinite looping
      if (stepCount > 100) {
        break;
      }
    }

    // Reset the flags after turning is complete
    // Set direction to go right (back to the middle)
    digitalWrite(DIR, HIGH);
    // Gradually turn the wheel right until it reaches the middle
    for (int i = 0; i <= stepCount; i++) {
      digitalWrite(PUL, HIGH); // Step
      delay(HALFPERIODTIME);
      digitalWrite(PUL, LOW);
      delay(HALFPERIODTIME);
    }
    nowReallign = false;
  }

  ////////////////////////////////////////////////////////////////////////
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
        turnRight();
        stepCount++;
      }
    }
    // once button is released turn back to center
    digitalWrite(DIR, HIGH);
    for (int i = 0; i <= stepCount; i++) {
      turnLeft();
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
        turnLeft();
        stepCount++;
      }
    }
    // once button is released turn back to center
    digitalWrite(DIR, LOW);
    for (int i = 0; i <= stepCount; i++) {
      turnRight();
    }
    delay(10);
  }

  analogWrite(enA, 1);
  // Drive forward unless the car has been running for more than 20 seconds
  static unsigned long startTime = millis();
  unsigned long currentTime = millis();
  if (currentTime - startTime < 100000) {
    driveForward();
  } else {
    // Stop the car after selected ^ seconds
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }

  delay(250);
}