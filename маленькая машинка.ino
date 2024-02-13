// **** ОБЛАСТЬ ПОДКЛЮЧЕНИЯ БИБЛИОТЕК ****
#include <Servo.h>

// **** Область объявления ПЕРЕМЕННЫХ и номеров подключаемых PIN'ов ****

// 1. подключите пины драйвера L298N к цифровым пинам Arduino

// первый двигатель
int enA = 7;
int in1 = 6;
int in2 = 5;

// второй двигатель
int enB = 2;
int in3 = 3;
int in4 = 4;

// сервопривод
int servoPin = 10;

// звук
int tonePin = 11;


// 2. подключите пины драйвера HC-SR04 к цифровым пинам Arduino

int trigPin = 9; // назначаем имя для Pin8
int echoPin = 8; // назначаем имя для Pin9

int duration, cm; // назначаем переменную "cm" и "duration" для показаний датчика

// **** ИНИЦИАЛИЗАЦИЯ ****


void setup()
{
// приветствие
  sound();
  test_system();
 
  // инициализируем все пины для управления двигателями как outputs
  pinMode(enA, OUTPUT);  
  pinMode(enB, OUTPUT);  
  pinMode(in1, OUTPUT);  
  pinMode(in2, OUTPUT);  
  pinMode(in3, OUTPUT);  
  pinMode(in4, OUTPUT);

  pinMode(trigPin, OUTPUT); // назначаем trigPin (Pin8), как выход
  pinMode(echoPin, INPUT); // назначаем echoPin (Pin9), как вход

  Serial.begin (9600);

}





void loop() {

// скрипт ультразвукового датчика
distance ();
}
// теста систем






// **** МОДУЛИ ****


// ТЕСТ ВСЕХ СИСТЕМ

void test() {

// СКРИПТ ОСТАНОВКИ ДВИГАТЕЛЕЙ ПРИ МАЛОЙ ДИСТАНЦИИ

if(cm<70)
stop();
else
{
  for(int i=0;i<50;i++)
  {
    distance ();
    while(cm<70)
    {
      stop();
      distance ();
    }
    forward();      
    }
    
    stop();
    delay(6000);

    left();
    delay(2000);
    stop();
    delay(6000);

    right();
    delay(2000);
    stop();
    delay(6000);

  }

}



void test_system() {

// ТЕСТ СИСТЕМЫ

    left();
    delay(2000);
    stop();
    delay(200);

    right();
    delay(2000);
    stop();
    delay(200);


  }



// движение вперед
void forward() { 
    // выставляем 100% мощность на моторе А - 255 из 255
    analogWrite( enA, 255 );
    analogWrite( enB, 255 );
    // режим мотора
    digitalWrite( in1, HIGH );
    digitalWrite( in2, LOW );
    digitalWrite( in3, LOW );
    digitalWrite( in4, HIGH );
        Serial.println("Движение вперед");
}

// движение назад
void back() { 
    // выставляем мощность на мотора А - 150 из 255
    analogWrite( enA, 255 );
    analogWrite( enB, 255 );
    // режим мотора
    digitalWrite( in1, LOW );
    digitalWrite( in2, HIGH );
    digitalWrite( in3, HIGH );
    digitalWrite( in4, LOW );
        Serial.println("Движение назад");
}



// движение вправо
void left() { 
    // выставляем мощность на мотора А - 150 из 255
    analogWrite( enA, 150 );
    analogWrite( enB, 150 );
    // режим мотора
    digitalWrite( in1, LOW );
    digitalWrite( in2, HIGH );
    digitalWrite( in3, LOW );
    digitalWrite( in4, HIGH );
        Serial.println("Поворот вправо");
}

// движение вправо
void right() { 
    // выставляем мощность на мотора А - 150 из 255
    analogWrite( enA, 150 );
    analogWrite( enB, 150 );
    // режим мотора
    digitalWrite( in1, HIGH );
    digitalWrite( in2, LOW );
    digitalWrite( in3, HIGH );
    digitalWrite( in4, LOW );
        Serial.println("Поворот влево");
}

// остановка
void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
      Serial.println("Остановка");
  }


// СКРИПТ ДЛЯ УЛЬТРАЗВУКОВОГО ДАЛЬНОМЕРА HC-SR04

void distance () { 
  digitalWrite(trigPin, LOW); // изначально датчик не посылает сигнал
  delayMicroseconds(5); // ставим задержку в 2 ммикросекунд

  digitalWrite(trigPin, HIGH); // посылаем сигнал
  delayMicroseconds(20); // ставим задержку в 10 микросекунд
  digitalWrite(trigPin, LOW); // выключаем сигнал

  duration = pulseIn(echoPin, HIGH); // включаем прием сигнала

  cm = duration / 58; // вычисляем расстояние в сантиметрах

  Serial.print(cm); // выводим расстояние в сантиметрах
  Serial.println(" cm");
  }

int timer=0;

 void sound () {
    
    if (millis()-timer>200) {
      
        tone(tonePin, 261.63, 200);
      timer=millis();
    }
    
    if (millis()-timer>200) {
      
      tone(tonePin, 293.66, 200);
      timer=millis();
    }

    if (millis()-timer>200) {
      
      tone(tonePin, 329.63, 200);
      timer=millis();
    }
    if (millis()-timer>200) {
      
      tone(tonePin, 349.23, 200);
      timer=millis();
    }
if (millis()-timer>200) {
      
      tone(tonePin, 550.00, 200);
      timer=millis();
    }

 }