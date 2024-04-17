/* Neural network import */
#include "ArduinoSTL.h"
#include "arduino_random_forest.h"

/* Pin macros */
// Stepper Motor
#define STEPPER_MOTOR_DIRECTION_PIN 9
#define STEPPER_MOTOR_PULSE_PIN 10

// Driver Motor / H Bridge
#define H_BRIDGE_ENA 7
#define H_BRIDGE_IN1 52
#define H_BRIDGE_IN2 53
// out1 -> purple motor connection
// out2 -> orange motor connection
// Switching out1 and out2 will cause the car to go in reverse

// Buttons
#define TURN_RIGHT_BUTTON_PIN 2
#define TURN_LEFT_BUTTON_PIN 3

/* Sensor pin macros */
// Sensor 1
#define FRONT_LEFT_TRIG_PIN 50
#define FRONT_LEFT_ECHO_PIN 51 

// Sensor 2
#define PURE_FRONT_TRIG_PIN 44
#define PURE_FRONT_ECHO_PIN 45

// Sensor 3
#define FRONT_RIGHT_TRIG_PIN 38
#define FRONT_RIGHT_ECHO_PIN 39

// Sensor 4
#define PURE_LEFT_TRIG_PIN 32
#define PURE_LEFT_ECHO_PIN 33

// Sensor 5
#define PURE_RIGHT_TRIG_PIN 26
#define PURE_RIGHT_ECHO_PIN 27

/* Other macros */
#define STEERING_MOTOR_STEPS 400
#define HALF_PERIOD_TIME 1.5
#define DESIRED_MEASUREMENT_SENSOR_5 55
#define TOLERANCE 20
#define INF_LOOP 140
#define STEPPER_MOTOR_DIR_LEFT LOW
#define STEPPER_MOTOR_DIR_RIGHT HIGH
#define MAX_SPEED 255

/* Global variable defintions */
int stepCount = 0;
int driverMotorSpeed = 0;
bool isTurningLeft = false;
bool hasTurnedLeft = false;
bool isTurningRight = false;
bool hasTurnedRight = false;
bool makeRight = false;
bool madeRight = false;
bool nowReallign = false;
bool goBackMiddle = false;

/* Helper function declarations */
float getSensorReadingCM(int trigPin, int echoPin);
void driveForwards();
void turnLeftTenDegrees();
void turnRightTenDegrees();
void emergencyStop();

/* Initialization code for the Arduino */
void setup() 
{
  /* Setup serial communication */
  Serial.begin(9600);

  /* Setup pins for stepper motor */
  pinMode(STEPPER_MOTOR_DIRECTION_PIN, OUTPUT);
  pinMode(STEPPER_MOTOR_PULSE_PIN, OUTPUT);

  /* Set stepper to not move */
  analogWrite(STEPPER_MOTOR_PULSE_PIN, 0);

  /* Setup pins for driver motor */
  pinMode(H_BRIDGE_ENA, OUTPUT);
  pinMode(H_BRIDGE_IN1, OUTPUT);
  pinMode(H_BRIDGE_IN2, OUTPUT);

  /* Initialize to 0 speed and driver motor off */
  analogWrite(H_BRIDGE_ENA, 0);
  digitalWrite(H_BRIDGE_IN1, LOW);
  digitalWrite(H_BRIDGE_IN2, LOW);

  /* Setup pins for buttons */
  pinMode(TURN_RIGHT_BUTTON_PIN, INPUT);
  pinMode(TURN_LEFT_BUTTON_PIN, INPUT);

  /* Setup pins for sensors */
  pinMode(FRONT_LEFT_TRIG_PIN, OUTPUT);
  pinMode(FRONT_LEFT_ECHO_PIN, INPUT);
  
  pinMode(PURE_FRONT_TRIG_PIN, OUTPUT);
  pinMode(PURE_FRONT_ECHO_PIN, INPUT);
  
  pinMode(FRONT_RIGHT_TRIG_PIN, OUTPUT);
  pinMode(FRONT_RIGHT_ECHO_PIN, INPUT);
  
  pinMode(PURE_LEFT_TRIG_PIN, OUTPUT);
  pinMode(PURE_LEFT_ECHO_PIN, INPUT);

  pinMode(PURE_RIGHT_TRIG_PIN, OUTPUT);
  pinMode(PURE_RIGHT_ECHO_PIN, INPUT);

  /* Turn off trig pins */
  digitalWrite(FRONT_LEFT_TRIG_PIN, LOW);
  digitalWrite(PURE_FRONT_TRIG_PIN, LOW);
  digitalWrite(FRONT_RIGHT_TRIG_PIN, LOW);
  digitalWrite(PURE_LEFT_TRIG_PIN, LOW);
  digitalWrite(PURE_RIGHT_TRIG_PIN, LOW);

  /* Initial delay to keep sensors synced on startup */
  delay(500);
}

/* Code for the main control loop */
void loop() 
{
  /* Declare array for neural network inputs */
  float neural_network_inputs[5];

  /* Fill neural network inputs. 
   * [pure_left, front_left, pure_front, front_right, pure_right] */
  neural_network_inputs[0] = getSensorReadingCM(
    PURE_LEFT_TRIG_PIN, PURE_LEFT_ECHO_PIN);
    
  neural_network_inputs[1] = getSensorReadingCM(
    FRONT_LEFT_TRIG_PIN, FRONT_LEFT_ECHO_PIN);

  neural_network_inputs[2] = getSensorReadingCM(
    PURE_FRONT_TRIG_PIN, PURE_FRONT_ECHO_PIN);

  neural_network_inputs[3] = getSensorReadingCM(
    FRONT_RIGHT_TRIG_PIN, FRONT_RIGHT_ECHO_PIN);
    
  neural_network_inputs[4] = getSensorReadingCM(
    PURE_RIGHT_TRIG_PIN, PURE_RIGHT_ECHO_PIN);

  for (int i = 0; i < sizeof(neural_network_inputs); i++)
  {
    Serial.print("Input ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(neural_network_inputs[i], 3);
  }

  if (neural_network_inputs[2] < 30)
  {
    emergencyStop()
  }

  float prediction = classifier.predictLabel(neural_network_inputs)

  Serial.print("Predicted class: ");
  Serial.println(prediction);

  switch (prediction)
  {
    case 0: turnLeftTenDegrees();
            break;
    case 1: turnRightTenDegrees();
            break;
    case 2: driveForwards();
            break;
    default: driveForwards();
  }

  delay(10)
}

/* Function to get a sensor reading in CM */
float getSensorReadingCM(int trigPin, int echoPin)
{
  // Send out a trigger signal
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //  Measure the duration of the echo pulse
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in CM
  float distanceCM = duration * 0.0343 / 2;

  return distanceCM;
}

void driveForwards()
{
  digitalWrite(H_BRIDGE_IN1, HIGH);
  digitalWrite(H_BRIDGE_IN2, LOW);

  for (driverMotorSpeed; driverMotorSpeed < MAX_SPEED; driverMotorSpeed++)
  {
    analogWrite(H_BRIDGE_ENA, driverMotorSpeed)
    delay(10)
  }
}

void emergencyStop()
{
  analogWrite(H_BRIDGE_ENA, 0);
  digitalWrite(H_BRIDGE_IN1, LOW);
  digitalWrite(H_BRIDGE_IN2, LOW);
}
