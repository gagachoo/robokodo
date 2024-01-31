#define PIN_RECV  13 // Вывод, к которому подключен ИК-приёмник
#define PIN_IN1   7   // Вывод управления правого колеса
#define PIN_IN2   6   // Вывод управления правого колеса
#define PIN_IN3   5   // Вывод управления левого колеса
#define PIN_IN4   4   // Вывод управления левого колеса
#define PIN_ENA   9   // Вывод управления скоростью правого колеса
#define PIN_ENB   3   // Вывод управления скоростью левого колеса
#define SPEED 255     // Скорость бобо-машинки (0-255)
// Коды с пульта управления (необходимо вставить свои!!!)
#define BUTTON_FORWARD  0xB4B4E21D // Код кнопки ВПЕРЁД
#define BUTTON_LEFT     0xB4B49A65 // Код кнопки ВЛЕВО
#define BUTTON_RIGHT    0xB4B45AA5 // Код кнопки ВПРАВО
#define BUTTON_BACK     0xB4B412ED // Код кнопки НАЗАД

#include <IRremote.h> // Библиотека для работы с ИК-приёмником
IRrecv irrecv(PIN_RECV); // Создание объекта работы с ИК-приёмником
decode_results results; // Переменная для хранения результата декодирования

void setup() {
  irrecv.enableIRIn();  // Инициализация ИК-приёмника
  // Настройка на выход всех управляющих пинов Arduino
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);
  pinMode(PIN_ENA, OUTPUT);
  pinMode(PIN_ENB, OUTPUT);
  // Остановка моторов
  digitalWrite(PIN_IN1, LOW);
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, LOW);
  analogWrite(PIN_ENA, SPEED);
  analogWrite(PIN_ENB, SPEED);
}
void loop() {
  // Ждём поступления сигнала с пульта ДУ
  if (irrecv.decode(&results)) {
    // Анализируем полученный результат
    switch(results.value) {
        case BUTTON_FORWARD: // Движение ВПЕРЁД
          digitalWrite(PIN_IN1, HIGH);
          digitalWrite(PIN_IN2, LOW);
          digitalWrite(PIN_IN3, LOW);
          digitalWrite(PIN_IN2, HIGH);
        break;
        case BUTTON_LEFT: // Поворот ВЛЕВО
          digitalWrite(PIN_IN1, HIGH);
          digitalWrite(PIN_IN2, LOW);
          digitalWrite(PIN_IN3, LOW);
          digitalWrite(PIN_IN2, LOW);
        break;
        case BUTTON_RIGHT: // Поворот ВПРАВО
          digitalWrite(PIN_IN1, LOW);
          digitalWrite(PIN_IN2, LOW);
          digitalWrite(PIN_IN3, LOW);
          digitalWrite(PIN_IN2, HIGH);
        break;
        case BUTTON_BACK: // Движение НАЗАД
          digitalWrite(PIN_IN1, LOW);
          digitalWrite(PIN_IN2, HIGH);
          digitalWrite(PIN_IN3, HIGH);
          digitalWrite(PIN_IN2, LOW);
        break;
    }
    irrecv.resume();
  }
}