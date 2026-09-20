// TT DC Motor + Ultrasonic + Morse "HI" Example

// Motor pins
const int motorENA = 5; // PWM (speed)
const int motorIN1 = 6; // direction
const int motorIN2 = 10; // direction

// Ultrasonic pins
const int trigPin = 7;
const int echoPin = 8;

// Speaker
const int speakerPin = 9;

// Timing for Morse
const int dotDuration = 40; // 1 dit
const int dashDuration = dotDuration * 3;
const int intraCharPause = dotDuration;
const int interLetterPause = dotDuration * 3;
const int wordPause = dotDuration * 7;
const int toneFreq = 600; // Hz

void setup() {
  Serial.begin(9600);

  // Motor setup
  pinMode(motorENA, OUTPUT);
  pinMode(motorIN1, OUTPUT);
  pinMode(motorIN2, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(speakerPin, OUTPUT);
}

void motorStop() {
  digitalWrite(motorIN1, LOW);
  digitalWrite(motorIN2, LOW);
  analogWrite(motorENA, 0);
}

void motorForward(int speed) {
  digitalWrite(motorIN1, HIGH);
  digitalWrite(motorIN2, LOW);
  analogWrite(motorENA, speed); // 0-255
}

void motorReverse(int speed) {
  digitalWrite(motorIN1, LOW);
  digitalWrite(motorIN2, HIGH);
  analogWrite(motorENA, speed);
}

// ===== Morse Functions =====
void playDot() {
  tone(speakerPin, toneFreq);
  delay(dotDuration);
  noTone(speakerPin);
  delay(intraCharPause);
}

void playHi() {
  // H -> ....
  playDot(); playDot(); playDot(); playDot();
  delay(interLetterPause);
  // I -> ..
  playDot(); playDot();
  delay(wordPause);
}

// ===== Distance Functions =====
long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

// ===== Main Loop =====
void loop() {
  long duration, inches, cm;

  // Trigger ultrasonic
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout

  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  // Motor logic based on distance
  if (cm > 50) {
    motorForward(200); // fast
  } else if (cm > 30) {
    motorForward(120); // slow
  } else {
    motorStop();       // stop close
    playHi();
    delay(1000);
  }

  delay(100);
}
