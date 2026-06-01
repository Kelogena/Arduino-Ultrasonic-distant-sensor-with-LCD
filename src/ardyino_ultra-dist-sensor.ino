#include <LiquidCrystal.h>

// ВИПРАВЛЕНО: Піни ініціалізуються згідно з наданою таблицею:
// RS=12, E=11, D4=7, D5=6, D6=5, D7=4
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

  // Стартове вітання
  lcd.print("Ultrasonic");
  lcd.setCursor(0, 1);
  lcd.print("Detector");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Очищення тригера перед вимірюванням
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Генеруємо імпульс 10 мікросекунд
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Зчитуємо зворотний імпульс (таймаут 30мс)
  duration = pulseIn(echoPin, HIGH, 30000);

  // Перевірка на відсутність сигналу (якщо об'єкт занадто далеко)
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

  // Розрахунок відстані в см
  distance = duration * 0.0343 / 2;

  // Виведення результатів на дисплей
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");

  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm");

  // Логіка роботи зумера (частота та затримка залежать від відстані)
  if (distance < 10) {
    tone(buzzerPin, 2000); // Високий писк без пауз (небезпека)
    delay(50);
  }
  else if (distance < 20) {
    tone(buzzerPin, 1500); 
    delay(100);
  }
  else if (distance < 50) {
    tone(buzzerPin, 1000); // Рідкісний писк
    delay(300);
  }
  else {
    noTone(buzzerPin);     // Без звуку, якщо перешкода далеко
    delay(100);
  }
}