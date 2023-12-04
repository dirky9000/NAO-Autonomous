// Define the pins for the HC-SR04 sensor
const int trigPin = 4;
const int echoPin = 5;
const int ledPin = 13;  // The onboard LED (pin 13)

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Define the trigger and echo pins as OUTPUT and INPUT
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set the LED pin as an OUTPUT
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Trigger a pulse by setting the trigger pin HIGH for 10 microseconds
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

  // Check if the distance is greater than 60cm
  if (distanceCM > 114) {
    // Turn on the LED
    digitalWrite(ledPin, HIGH);
  } else {
    // Turn off the LED
    digitalWrite(ledPin, LOW);
  }

  // Delay for a moment before the next measurement
  delay(500);  // 1-second delay between measurements
}
