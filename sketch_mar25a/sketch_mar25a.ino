void setup() {
  // Инициализируем пин встроенного светодиода как выход
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);   // Включить светодиод (на Wemos LOW — это ВКЛ)
  delay(500);                       // Подождать 0.5 секунды
  digitalWrite(LED_BUILTIN, HIGH);  // Выключить светодиод
  delay(500);                       // Подождать 0.5 секунды
}