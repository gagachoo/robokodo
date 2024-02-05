// 1. подключите пины драйвера L298N к цифровым пинам Arduino

// первый двигатель
int enA = 7;
int in1 = 6;
int in2 = 5;

// второй двигатель
int enB = 2;
int in3 = 3;
int in4 = 4;


void setup()
{
  // инициализируем все пины для управления двигателями как outputs
  pinMode(enA, OUTPUT);  
  pinMode(enB, OUTPUT);  
  pinMode(in1, OUTPUT);  
  pinMode(in2, OUTPUT);  
  pinMode(in3, OUTPUT);  
  pinMode(in4, OUTPUT);
}

void loop() {


    forward();
    delay(2000); // пауза 2сек
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

    back();
    delay(2000);
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
}

// остановка
void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  }
