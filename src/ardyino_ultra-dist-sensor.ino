const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 3;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 30000);

  distance = duration * 0.0343 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 10) {
    tone(buzzerPin, 2000);
    delay(50);
  }
  else if (distance < 20) {
    tone(buzzerPin, 1500);
    delay(100);
  }
  else if (distance < 50) {
    tone(buzzerPin, 1000);
    delay(300);
  }
  else {
    noTone(buzzerPin);
    delay(100);
  }
}