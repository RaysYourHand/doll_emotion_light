  const int n_red = 3;
  const int n_green = 5;
  const int n_blue = 6;

  const int blue_led = 2;
  const int yellow_led = 4;

  const int btn = 8;
  const int photoPin = A0;

  int buttonState = 0;
  int ledcolor = 0;

  int heart_interval = 2500;
  const int normalHeart = 2500;
  const int fastHeart = 1000;
  unsigned long previousMillis = 0;

  int buttonState = 0;
  int mood = 0;
  const int neutraMood = 10;

  unsigned long lastPetMillis = 0;
  const unsigned long moodInterval = 3000;

  int lastButtonState = HIGH;

  void setup() {
    mood = 10;
    pinMode(blue_led, OUTPUT);
    pinMode(yellow_led, OUTPUT);

    pinMode(n_red, OUTPUT);
    pinMode(n_green, OUTPUT);
    pinMode(n_blue, OUTPUT);


    pinMode(btn, INPUT);
    Serial.begin(9600);
  }


  void loop() {
    lightValue = analogRead(photoPin);


    if (lightValue < darkThreshold) {
      heart_interval = fastHeart;
    } else {
      heart_interval = normalHeart;
    }
    
    if (millis() - previousMillis >= heart_interval) {
      previousMillis = millis();
      HeartBeats();
    }

    buttonState = digitalRead(btn);

  if (buttonState == LOW && lastButtonState == HIGH) {
    mood++;

  if (buttonState == LOW && lastButtonState == HIGH) {
    if (mood < neutraMood) {
      mood++;
    }

    lastPetMillis = millis();

    Serial.print("Mood: ");
    Serial.println(mood);
  }

  lastButtonState = buttonState;

    if (millis() - lastPetMillis >= 000) {
      if (mood > 0) {
        mood--;
      }

      lastPetMillis = millis();
    }
    ShowLedState(mood);
}
void HeartBeats() {
  digitalWrite(blue_led, HIGH);
  delay(100);
  digitalWrite(blue_led, LOW);
  delay(100);
  digitalWrite(yellow_led, HIGH);
  delay(100);
  digitalWrite(yellow_led, LOW);
  delay(100);
}
void ShowLedState(int state) {
  state = constrain(state, 0, 10);

  int redValue = 0;
  int greenValue = 0;
  int blueValue = 255;

  if (state >= 5) {
    float t = (state - 5) / 5.0;

    redValue = 0;
    greenValue = 255 * t;
    blueValue = 255;
  }
  else {
    float t = (5 - state) / 5.0;

    redValue = 128 * t;
    greenValue = 0;
    blueValue = 255;
  }

  analogWrite(n_red, redValue);
  analogWrite(n_green, greenValue);
  analogWrite(n_blue, blueValue);
}
