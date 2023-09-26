// Define the pins for the four HC-SR04 sensors
const int sensor1TrigPin = 2;
const int sensor1EchoPin = 3;
const int sensor2TrigPin = 4;
const int sensor2EchoPin = 5;
const int sensor3TrigPin = 6;
const int sensor3EchoPin = 7;
const int sensor4TrigPin = 8;
const int sensor4EchoPin = 9;

void setup() {
  Serial.begin(9600);
  
  // Initialize pins as needed
  pinMode(sensor1TrigPin, OUTPUT);
  pinMode(sensor1EchoPin, INPUT);
  pinMode(sensor2TrigPin, OUTPUT);
  pinMode(sensor2EchoPin, INPUT);
  pinMode(sensor3TrigPin, OUTPUT);
  pinMode(sensor3EchoPin, INPUT);
  pinMode(sensor4TrigPin, OUTPUT);
  pinMode(sensor4EchoPin, INPUT);
}

void loop() {
  // Measure distance from sensor 1
  long distance1 = measureDistance(sensor1TrigPin, sensor1EchoPin);
  // Measure distance from sensor 2
  long distance2 = measureDistance(sensor2TrigPin, sensor2EchoPin);
  // Measure distance from sensor 3
  long distance3 = measureDistance(sensor3TrigPin, sensor3EchoPin);
  // Measure distance from sensor 4
  long distance4 = measureDistance(sensor4TrigPin, sensor4EchoPin);

  // Print the distance measurements to the serial monitor
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

  // Add a delay between measurements
  delay(1000); // Adjust the delay as needed
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
