#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 8;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);

  lcd.begin(16, 2);

  lcd.print("Ultrasonic");
  lcd.setCursor(0, 1);
  lcd.print("Detector");
  delay(2000);
  lcd.clear();
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Out of range /");
    lcd.setCursor(0, 1);
    lcd.print("No Echo");
    noTone(buzzerPin);
    delay(200);
    return;
  }


  distance = duration * 0.0343 / 2;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");

  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm");

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
