const int white_button = 2;
const int blue_button = 3;
const int red_button = 4;
const int green_button = 5;

void setup() {
  Serial.begin(9600);

  pinMode(white_button, INPUT);
  pinMode(blue_button, INPUT);
  pinMode(red_button, INPUT);
  pinMode(green_button, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void handleButton(int buttonPin, const char* buttonName) {
  if (digitalRead(buttonPin) == HIGH) {
    delay(10);
    Serial.print(buttonName);
    Serial.println(" Button Pressed");
    while (digitalRead(buttonPin) == HIGH) {}
    delay(10);
    digitalWrite(LED_BUILTIN,LOW);
  }
}

void loop() {
  handleButton(white_button, "White");
  handleButton(blue_button, "Blue");
  handleButton(red_button, "Red");
  handleButton(green_button, "Green");
}
