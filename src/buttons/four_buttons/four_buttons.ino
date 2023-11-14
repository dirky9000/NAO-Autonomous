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

void loop() {
  
  if (digitalRead(white_button) == HIGH) {
    delay(10);
    Serial.println("White Button Pressed");
    digitalWrite(LED_BUILTIN,HIGH);
    while (digitalRead(white_button) == HIGH){}
    delay(10);
    digitalWrite(LED_BUILTIN,LOW);
  }
  if (digitalRead(blue_button) == HIGH) {
    delay(10);
    Serial.println("Blue Button Pressed");
    digitalWrite(LED_BUILTIN,HIGH);
    while (digitalRead(blue_button) == HIGH){}
    delay(10);
    digitalWrite(LED_BUILTIN,LOW);
  }
  if (digitalRead(red_button) == HIGH) {
    delay(10);
    Serial.println("Red Button Pressed");
    digitalWrite(LED_BUILTIN,HIGH);
    while (digitalRead(red_button) == HIGH){}
    delay(10);
    digitalWrite(LED_BUILTIN,LOW);
  }
  if (digitalRead(green_button) == HIGH) {
    delay(10);
    Serial.println("Green Button Pressed");
    digitalWrite(LED_BUILTIN,HIGH);
    while (digitalRead(green_button) == HIGH){}
    delay(10);
    digitalWrite(LED_BUILTIN,LOW);
  }
}
