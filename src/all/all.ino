// Button Configuration
const int white_button = 2;
const int blue_button = 3;
const int red_button = 4;
const int green_button = 5;

// Ultrasonic Sensor Configuration
const int sensor1TrigPin = 6;
const int sensor1EchoPin = 7;
const int sensor2TrigPin = 8;
const int sensor2EchoPin = 9;
const int sensor3TrigPin = 10;
const int sensor3EchoPin = 11;
const int sensor4TrigPin = 12;
const int sensor4EchoPin = 13;

void setup() {
  Serial.begin(9600);

  // Button Setup
  pinMode(white_button, INPUT);
  pinMode(blue_button, INPUT);
  pinMode(red_button, INPUT);
  pinMode(green_button, INPUT);

  // Ultrasonic Sensor Setup
  pinMode(sensor1TrigPin, OUTPUT);
  pinMode(sensor1EchoPin, INPUT);
  pinMode(sensor2TrigPin, OUTPUT);
  pinMode(sensor2EchoPin, INPUT);
  pinMode(sensor3TrigPin, OUTPUT);
  pinMode(sensor3EchoPin, INPUT);
  pinMode(sensor4TrigPin, OUTPUT);
  pinMode(sensor4EchoPin, INPUT);
}

void handleButton(int buttonPin, const char* buttonName) {
  if (digitalRead(buttonPin) == HIGH) {
    delay(10);
    Serial.print(buttonName);
    Serial.println(" Button Pressed");
    while (digitalRead(buttonPin) == HIGH) {}
    delay(10);
  }
}

void loop() {
  // Button Handling
  handleButton(white_button, "White");
  handleButton(blue_button, "Blue");
  handleButton(red_button, "Red");
  handleButton(green_button, "Green");

  // Ultrasonic Sensor Measurements
  long distance1 = measureDistance(sensor1TrigPin, sensor1EchoPin);
  long distance2 = measureDistance(sensor2TrigPin, sensor2EchoPin);
  long distance3 = measureDistance(sensor3TrigPin, sensor3EchoPin);
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
  // Ultrasonic Sensor Measurement Function (unchanged)
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distanceCM = duration * 0.0343 / 2;

  return distanceCM;
}
