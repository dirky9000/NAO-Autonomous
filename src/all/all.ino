//const int white_button = 2;
//const int blue_button = 3;
//const int red_button = 4;
const int green_button = 5;

const int sensor1TrigPin = 23;
const int sensor1EchoPin = 22;
const int sensor2TrigPin = 33;
const int sensor2EchoPin = 32;
const int sensor3TrigPin = 43;
const int sensor3EchoPin = 42;
const int sensor4TrigPin = 53;
const int sensor4EchoPin = 52;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);  // Use Serial1 for Serial Plotter

  //pinMode(white_button, INPUT);
  //pinMode(blue_button, INPUT);
  //pinMode(red_button, INPUT);
  pinMode(green_button, INPUT);

  pinMode(sensor1TrigPin, OUTPUT);
  pinMode(sensor1EchoPin, INPUT);
  pinMode(sensor2TrigPin, OUTPUT);
  pinMode(sensor2EchoPin, INPUT);
  pinMode(sensor3TrigPin, OUTPUT);
  pinMode(sensor3EchoPin, INPUT);
  pinMode(sensor4TrigPin, OUTPUT);
  pinMode(sensor4EchoPin, INPUT);

  digitalWrite(sensor1TrigPin, LOW);
  digitalWrite(sensor2TrigPin, LOW);
  digitalWrite(sensor3TrigPin, LOW);
  digitalWrite(sensor4TrigPin, LOW);
}

void handleButton(int buttonPin, const char* buttonName) {
  static bool buttonState = LOW;         // Current button state
  static bool lastButtonState = LOW;     // Previous button state
  static unsigned long lastDebounceTime = 0;  // Last time the button state changed
  static unsigned long debounceDelay = 50;    // Debounce time (adjust as needed)

  // Read the current state of the button
  bool reading = digitalRead(buttonPin);

  // Check if the button state has changed
  if (reading != lastButtonState) {
    // Reset the debounce timer
    lastDebounceTime = millis();
  }

  // Check if the debounce delay has passed
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Update the button state only if it has been stable for the debounce delay
    if (reading != buttonState) {
      buttonState = reading;

      // Handle the button press
      if (buttonState == HIGH) {
        Serial.print(buttonName);
        Serial.println(" Button Pressed");
        Serial.flush(); // Ensure all data is sent to the serial plotter
      }
    }
  }

  // Save the current button state for the next iteration
  lastButtonState = reading;
}

void loop() {
  //handleButton(white_button, "White");
  //handleButton(blue_button, "Blue");
  //handleButton(red_button, "Red");
  //handleButton(green_button, "Green");

  long distance1 = measureDistance(sensor1TrigPin, sensor1EchoPin);
  long distance2 = measureDistance(sensor2TrigPin, sensor2EchoPin);
  long distance3 = measureDistance(sensor3TrigPin, sensor3EchoPin);
  long distance4 = measureDistance(sensor4TrigPin, sensor4EchoPin);

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

  delay(1000);
}

long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distanceCM = duration * 0.0343 / 2;

  return distanceCM;
}
