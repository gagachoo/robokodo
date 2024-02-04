// Этот блок команд выполняется один раз для инициализации на устройстве
void setup() {
  Serial.begin(9600); // Простушиваем порт на скорости 9600 кбс
}

// Этот блок команд выполняется постоянно (цикл)
void loop() { 
  digitalWrite(2, HIGH); // Включение синего светодиода
    Serial.println("Включился светодиод"); // выводим на монитор порта сообщение о включении
  delay(1000);            // Задержка 1 сек.
  digitalWrite(2, LOW);  // Выключение синего светодиода
    Serial.println("Выключился светодиод"); // выводим на монитор порта сообщение о выключении
  delay(1000);            // Задержка 1 сек.

}