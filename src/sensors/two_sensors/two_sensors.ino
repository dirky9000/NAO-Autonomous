// Define the pins for the two HC-SR04 sensors
const int sensor1TrigPin = 2;
const int sensor1EchoPin = 3;
const int sensor2TrigPin = 4;
const int sensor2EchoPin = 5;

void setup() {
  Serial.begin(9600);

  // Initialize pins as needed
  pinMode(sensor1TrigPin, OUTPUT);
  pinMode(sensor1EchoPin, INPUT);
  pinMode(sensor2TrigPin, OUTPUT);
  pinMode(sensor2EchoPin, INPUT);
}

long measureDistance(int trigPin, int echoPin) {
  // Trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the echo duration
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  // Speed of sound in air at 20°C is approximately 343 meters per second
  // Divide by 2 because the sound travels to the object and back
  long distanceCM = duration * 0.0343 / 2;

  return distanceCM;
}

void loop() {
  // Measure distance from sensor 1
  long distance1 = measureDistance(sensor1TrigPin, sensor1EchoPin);
  // Measure distance from sensor 2
  long distance2 = measureDistance(sensor2TrigPin, sensor2EchoPin);

  // Print the distance measurements to the serial monitor
  Serial.print("Sensor 1: ");
  Serial.print(distance1);
  Serial.println(" cm");

  Serial.print("Sensor 2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  // Add a delay between measurements
  delay(1000); // Adjust the delay as needed
}

