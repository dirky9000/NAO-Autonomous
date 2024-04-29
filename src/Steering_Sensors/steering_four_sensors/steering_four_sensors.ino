// No sensor 6 and also added code to be parallel 
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

#define desiredMeasurementSensor5 25
#define tolerance 10
#define infLoop 50

int stepCount = 0; // Keeps track of steps taken 
bool isTurningLeft = false; // Specifies if wheel is currently turning
bool hasTurnedLeft = false;  // Variable to track whether the wheel has already turned
bool isTurningRight = false; // Specifies if wheel is currently turning
bool hasTurnedRight = false;  // Variable to track whether the wheel has already turned
bool makeRight = false; 
bool madeRight = false;
bool nowReallign = false;
bool goBackMiddle = false;
bool started = false;
bool running = true;

// Motor  connections
int enA = 12;
int in1 = 52;
int in2 = 53;

void setSpeed(int speed){
  analogWrite(enA, speed);
}

// Allows car to drive forward 
void driveForward() {
  setSpeed(255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

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
  //pinMode(trigPin6, OUTPUT);
  //pinMode(echoPin6, INPUT);

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
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  float distanceCM = duration * 0.0343 / 2;

  return distanceCM;
}

// Allows car to make turn and drive 
void makeTurn() {
  delay(HALFPERIODTIME);
  digitalWrite(PUL, HIGH);
  delay(HALFPERIODTIME);
  digitalWrite(PUL, LOW);
  driveForward();
}

void aroundObstacle(float distance2, float distance3, float distance5) {

  // If an object is in front of the car, then it makes a left around it (Sensor 2: Front)
  if ((distance2 < 150) && (!isTurningLeft && !hasTurnedLeft)) { // 150
    isTurningLeft = true; 

    stepCount = 0;

    digitalWrite(DIR, HIGH); // Set direction to go left

    // higher the number = higher the angle 
    while (stepCount <= 260) {
        makeTurn();
        stepCount++;
    }

    hasTurnedLeft = true;
    isTurningLeft = false;
  }

  // After the car has made a left turn, it goes back middle (Sensor 2: Front)
  if ((distance2 > 150) && hasTurnedLeft) {    
    isTurningLeft = true;

    digitalWrite(DIR, LOW); // Set direction to go back to middle after left turn 

    // Begin loop until it reaches the middle
    for (int i = 0; i <= stepCount; i++) {
      makeTurn();
    }

    hasTurnedLeft = false;
    isTurningLeft = false;
    makeRight = true;
    stepCount = 0;
  }

  // Once the car goes middle, it needs to make right to go down the hallway again (Sensor 2: Front)
  if (makeRight) {
    stepCount = 0;

    digitalWrite(DIR, LOW); // Set direction to go right

    // makes the angle go back middle of hallway 
    while (stepCount <= 250) { 
        makeTurn();
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

  // After the car has made a right turn, it goes back middle (Sensor 2: Front)
  if (madeRight) {
      digitalWrite(DIR, HIGH); // Set direction to go back to middle after right turn 

    // Begin loop until it reaches the middle
    for (int i = 0; i <= stepCount; i++) {
      makeTurn();
    }

      madeRight = false;
      nowReallign = true;
  }
}

void intoHallway(float distance2, float distance3, float distance5) {
  // Allows car to make right turns into hallways (Sensor 3: Front Right)
  if (distance3 > 600) { 
    stepCount = 0;
    driveForward();

    digitalWrite(DIR, LOW); // Set direction to go right

    // higher the number = higher the angle
    while (stepCount <= 500) { 
        makeTurn();
        driveForward();
        stepCount++;
    }

    driveForward();
    delay(1000);
    driveForward(); 

    digitalWrite(DIR, HIGH); // Set direction to go back to middle after right turn 

    // Begin loop until it reaches the middle
    for (int i = 0; i <= stepCount; i++) {
      makeTurn();
      driveForward();
    }
    driveForward();
    stepCount = 0;
  }
}

// Main loop function runs repeatedly
void loop() {  
  
  // Program starts once NAO sends 'b' to arduino
  if (!started) {
    while (!Serial.available() || Serial.read() != 'b') {
      delay(100);  
    }
    started = true; 
  }

  // Check if a 'g' is received to stop the program
  if (Serial.available() > 0) {
    if (Serial.read() == 'g') {
      running = false;  // Set running to false when 'g' is received
    }
  }
  
  // If the program is not supposed to be running, skip the rest of the loop
  if (!running) {
    return;
  }
  
  // Added a delay on when the sensors start working because without, the wheel turns automatically for some reason
  static bool sensorsStart = false;
  if (!sensorsStart) {
    delay(500);
    sensorsStart = true;
  }
  
  // Continuously measures the distance of sensors
  float distance1 = measureDistance(trigPin1, echoPin1);
  float distance2 = measureDistance(trigPin2, echoPin2);
  float distance3 = measureDistance(trigPin3, echoPin3);
  float distance4 = measureDistance(trigPin4, echoPin4);
  float distance5 = measureDistance(trigPin5, echoPin5);
  //float distance6 = measureDistance(trigPin6, echoPin6);

  // Reads distances onto the serial monitor 
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
  /*
  Serial.print("Sensor 6: ");
  Serial.print(distance6);
  Serial.println(" cm");
  */
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  aroundObstacle(distance2, distance3, distance5);
  intoHallway(distance2, distance3, distance5);
  // Makes the car swerve right if it sways too much to the left
  if (distance5 > (desiredMeasurementSensor5 + tolerance)) {
    int stepCount = 0;

    aroundObstacle(distance2, distance3, distance5);
    intoHallway(distance2, distance3, distance5);
    digitalWrite(DIR, LOW); // Set direction to go right

    // Gradually turn the wheel until it is back in the desired range for sensor
    while (distance5 > (desiredMeasurementSensor5 + tolerance)) {
      aroundObstacle(distance2, distance3, distance5);
      intoHallway(distance2, distance3, distance5);
      makeTurn();
      
      distance2 = measureDistance(trigPin2, echoPin2);
      distance3 = measureDistance(trigPin3, echoPin3); // Update sensor 3 readings
      distance5 = measureDistance(trigPin5, echoPin5); // Update sensor 5 readings
      
      stepCount++;
      
      // Stop turning if the sensor is within the desired range
      if (distance5 <= (desiredMeasurementSensor5 + tolerance)) {
        break;
      }

      // Prevent infinite looping
      if (stepCount > infLoop) {
        aroundObstacle(distance2, distance3, distance5);
        intoHallway(distance2, distance3, distance5);
        break;
      }
    }

    digitalWrite(DIR, HIGH); // Set direction to go left (back to the middle)
    // Gradually turn the wheel right until it reaches the middle
    for (int i = 0; i <= stepCount; i++) {
      aroundObstacle(distance2, distance3, distance5);
      intoHallway(distance2, distance3, distance5);
      makeTurn();
    }
  }

  // Makes the car swerve left if it sways too much to the right
  if (distance5 < (desiredMeasurementSensor5 - tolerance)) {
    int stepCount = 0;
    
    aroundObstacle(distance2, distance3, distance5);
    intoHallway(distance2, distance3, distance5);
    digitalWrite(DIR, HIGH); // Set direction to go left

    // Gradually turn the wheel until it is back in the desired range for sensor
    while (distance5 < (desiredMeasurementSensor5 - tolerance)) {
      aroundObstacle(distance2, distance3, distance5);
      intoHallway(distance2, distance3, distance5);
      makeTurn();

      distance2 = measureDistance(trigPin2, echoPin2);
      distance3 = measureDistance(trigPin3, echoPin3);
      distance5 = measureDistance(trigPin5, echoPin5); // Update distance readings
      
      stepCount++;

      // Stop turning if the sensor is within the desired range
      if (distance5 >= (desiredMeasurementSensor5 - tolerance)) {
        break;
      }

      // Prevent infinite looping
      if (stepCount > infLoop) {
        aroundObstacle(distance2, distance3, distance5);
        intoHallway(distance2, distance3, distance5);
        break;
      }
    }

    digitalWrite(DIR, LOW); // Set direction to go right (back to the middle)
    // Gradually turn the wheel right until it reaches the middle
    for (int i = 0; i <= stepCount; i++) {
      aroundObstacle(distance2, distance3, distance5);
      intoHallway(distance2, distance3, distance5);
      makeTurn();
    }
  }
  
  driveForward();
  delay(250);
}