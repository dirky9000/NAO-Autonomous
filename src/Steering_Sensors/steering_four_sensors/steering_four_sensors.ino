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

int stepCount = 0; // Keeps track of steps taken 
bool isTurningLeft = false; // Specifies if wheel is currently turning
bool hasTurnedLeft = false;  // Variable to track whether the wheel has already turned
bool isTurningRight = false; // Specifies if wheel is currently turning
bool hasTurnedRight = false;  // Variable to track whether the wheel has already turned

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
}

void turnRight() {
  delay(HALFPERIODTIME);
  digitalWrite(PUL, HIGH);
  delay(HALFPERIODTIME);
  digitalWrite(PUL, LOW);
}

// Main loop function runs repeatedly
void loop() {
  ////////////////////////////////////////////////////////////////////////
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
  // Check if the wheel needs to turn and hasn't turned yet
  if ((distance2 < 20 || distance6 < 20) && (!isTurningLeft && !hasTurnedLeft)) {
    // Code to turn left
    isTurningLeft = true;  // Set the flag to indicate turning

    // Reset step count for turning
    stepCount = 0;

    // Set direction to go left
    digitalWrite(DIR, HIGH);

    // Begin loop to turn left when distance is above 39cm
    while (stepCount <= 400) {
      // Do one revolution counterclockwise (LOW)
      turnLeft();
      stepCount++;
    }

    hasTurnedLeft = true; // Set the flag to indicate that the wheel has turned
    isTurningLeft = false;  // Reset the flag after turning is complete
  }

  // Check if the wheel needs to go back to the middle and has turned left
  if ((distance2 > 20 && distance6 > 20) && (hasTurnedLeft)) {
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
    stepCount = 0;
  }


  /*
  ////////////////////////////////////////////////////////////////////////
  // Check if the wheel needs to turn and hasn't turned yet
  if (distance2 < 20 && !isTurningLeft && !hasTurnedLeft) {
    isTurningLeft = true;  // Set the flag to indicate turning

    // Reset step count for turning
    stepCount = 0;

    // Set direction to go left
    digitalWrite(DIR, HIGH);

    // Begin loop to turn left when distance is above 39cm
    while (stepCount <= 400) {
      // Do one revolution counterclockwise (LOW)
      turnLeft();
      stepCount++;
    }

    hasTurnedLeft = true; // Set the flag to indicate that the wheel has turned
    isTurningLeft = false;  // Reset the flag after turning is complete
  }

  // Check if the wheel needs to go back to the middle and has turned left
  if (distance2 > 20 && hasTurnedLeft) {
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
    stepCount = 0;
  }
  /*
  // If something is behind the car 
  if (distance6 < 20 && !isTurningLeft && !hasTurnedLeft) {
    isTurningLeft = true;  // Set the flag to indicate turning

    // Reset step count for turning
    stepCount = 0;

    // Set direction to go left
    digitalWrite(DIR, HIGH);

    // Begin loop to turn left when distance is above 39cm
    while (stepCount <= 400) {
      // Do one revolution counterclockwise (LOW)
      turnLeft();
      stepCount++;
    }

    hasTurnedLeft = true; // Set the flag to indicate that the wheel has turned
    isTurningLeft = false;  // Reset the flag after turning is complete
  }

  // Check if the wheel needs to go back to the middle and has turned left
  if (distance6 > 20 && hasTurnedLeft) {
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
    stepCount = 0;
  }
  */
  // Check if the wheel needs to turn and hasn't turned yet
  if (distance3 > 10000 && !isTurningRight && !hasTurnedRight) {
    isTurningRight = true;  // Set the flag to indicate turning

    // Reset step count for turning
    stepCount = 0;

    // Set direction to go right
    digitalWrite(DIR, LOW);

    // Begin loop to turn left when distance is above 39cm
    while (stepCount <= 400) {
      // Do one revolution counterclockwise (LOW)
      turnRight();
      stepCount++;
    }

    hasTurnedRight = true; // Set the flag to indicate that the wheel has turned
    isTurningRight = false;  // Reset the flag after turning is complete
  }

  // Check if the wheel needs to go back to the middle and has turned left
  if (distance3 < 50 && hasTurnedRight) {
    isTurningRight = true;  // Set the flag to indicate turning

    // Set direction to go right (back to the middle)
    digitalWrite(DIR, HIGH);

    // Begin loop to turn right until it reaches the middle
    for (int i = 0; i <= stepCount; i++) {
      turnLeft();
    }

    // Reset the flags and step count after returning to the middle
    hasTurnedRight = false;
    isTurningRight = false;
    stepCount = 0;
  }
  
  // Delay between measurements
  delay(500);

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
}