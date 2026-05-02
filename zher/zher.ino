#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

// Пины (проверь соответствие со своим набором)
#define DHTPIN_BOKASHI D3
#define DHTPIN_WORMS D4
#define MQ135_PIN A0
#define SERVO_PIN D5
#define BUZZER_PIN D6
#define DHTTYPE DHT22

// Настройки OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

DHT dhtBokashi(DHTPIN_BOKASHI, DHTTYPE);
DHT dhtWorms(DHTPIN_WORMS, DHTTYPE);
Servo trapdoor;

// Пороговые значения из твоего описания
float bokashiTempMin = 20.0, bokashiTempMax = 35.0;
float wormsTempMin = 15.0, wormsTempMax = 25.0;
int gasThreshold = 600; // Условное значение для MQ-135

void setup() {
  Serial.begin(115200);
  dhtBokashi.begin();
  dhtWorms.begin();
  trapdoor.attach(SERVO_PIN);
  trapdoor.write(0); // Заслонка закрыта [cite: 14]
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("OLED fail"));
    for(;;);
  }
  display.clearDisplay();
}

void loop() {
  float tB = dhtBokashi.readTemperature();
  float hB = dhtBokashi.readHumidity();
  float tW = dhtWorms.readTemperature();
  float hW = dhtWorms.readHumidity();
  int gasLevel = analogRead(MQ135_PIN);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  // ПРОВЕРКА КРИТИЧЕСКИХ ЗНАЧЕНИЙ
  bool alert = false;

  // Проверка червей (самая чувствительная часть)
  if (tW > wormsTempMax || tW < wormsTempMin) {
    showAlert("TEMP WORMS CRITICAL!");
    alert = true;
  }
  
  if (gasLevel > gasThreshold) {
    showAlert("TOXIC GAS ALERT!");
    alert = true;
  }

  // Если всё в норме, выводим текущие данные
  if (!alert) {
    display.println("BIOBOX STATUS: OK");
    display.printf("Bokashi: %.1fC | %.0f%%\n", tB, hB);
    display.printf("Worms: %.1fC | %.0f%%\n", tW, hW);
    display.printf("Gas Level: %d\n", gasLevel);
  }

  display.display();
  
  // Логика нейтрализации (имитация перехода на 10-й день)
  // В реальном коде здесь должна быть проверка времени через RTC модуль DS3231 [cite: 53]
  checkAndOpenTrapdoor();

  delay(2000); 
}

void showAlert(String message) {
  display.clearDisplay();
  display.setCursor(0, 10);
  display.setTextSize(2);
  display.println("!! ALERT !!");
  display.setTextSize(1);
  display.println(message);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(500);
  digitalWrite(BUZZER_PIN, LOW);
}

void checkAndOpenTrapdoor() {
  // 1. Проверяем, прошел ли цикл Бокаши (10-14 дней) [cite: 5]
  // 2. Перед открытием выводим сообщение о нейтрализации
  /* display.clearDisplay();
     display.println("PH NEUTRALIZATION...");
     display.println("ADD EGGSHELLS NOW!");
     display.display();
     delay(5000); // Даем время пользователю
  */
  
  // 3. Команда сервоприводу на 60 секунд 
  // trapdoor.write(90); // Открыть
  // delay(60000);
  // trapdoor.write(0);  // Закрыть
}