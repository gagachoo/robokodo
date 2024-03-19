// **** ОБЛАСТЬ ПОДКЛЮЧЕНИЯ БИБЛИОТЕК ****
#include <Servo.h>
#include <WiFi.h>
#include <WebServer.h>

// **** WIFI ****


 
  const char* ssid = "ROBOKODO";
  const char* password = "12345678";
  IPAddress local_ip(192,168,1,1);
  IPAddress gateway(192,168,1,1);
  IPAddress subnet(255,255,255,0);
  WebServer server(80);
  int a = 0;

  void handle_led1off() {
  a = 1;
    server.send(200, "text/html", SendHTML(false,0));
  }
  void handle_led2off() {
  a = 2;
    server.send(200, "text/html", SendHTML(false,0));
  }
  void handle_led3off() {
  a = 3;
    server.send(200, "text/html", SendHTML(false,0));
  }
  void handle_led4off() {
  a = 4;
    server.send(200, "text/html", SendHTML(false,0));
  }
  void handle_led5off() {
  a = 5;
    server.send(200, "text/html", SendHTML(false,0));
  }
  void handle_led6off() {
  a = 6;
    server.send(200, "text/html", SendHTML(false,0));
  }
  void handle_led7off() {
  a = 7;
    server.send(200, "text/html", SendHTML(false,0));
  }
  void handle_led8off() {
  a = 8;
    server.send(200, "text/html", SendHTML(false,0));
  }
  void handle_led9off() {
  a = 9;
    server.send(200, "text/html", SendHTML(false,0));
  }
  void handle_led10off() {
  a = 10;
    server.send(200, "text/html", SendHTML(false,0));
  }
  void handle_NotFound(){
    server.send(404, "text/plain", "Not found 404");
  }
  void handle_OnConnect() {
    server.send(200, "text/html", SendHTML(false,0));
  }
   String SendHTML(uint8_t led1stat,uint8_t led2stat){
    String ptr = "<!DOCTYPE html> <html>";
    ptr +="<meta http-equiv=\"Content-type\" content=\"text/html; charset=utf-8\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">";
    ptr +="<title>РОБОКОДО</title>";
    ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
    ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}";
    ptr +=".button {display: block;width: 80px;background-color: #ffffff;border: none;color: #777777 ;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border: 1px solid #777777;}";
    ptr +=".button-off {background-color: #ffffff;}";
    ptr +=".button-off:active {background-color: #ffffff;}";
    ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}";
    ptr +="</style>";
    ptr +="<script>        ";
    ptr +="function send(led_sts)      ";
    ptr +="{        ";
    ptr +="  var xhttp = new XMLHttpRequest();     ";
    ptr +="  xhttp.onreadystatechange = function() {      ";
    ptr +="    if (this.readyState == 4 && this.status == 200) {      ";
    ptr +="      document.getElementById(\"state\").innerHTML = this.responseText;    ";
    ptr +="    }        ";
    ptr +="  };        ";
    ptr +="  xhttp.open(\"GET\", \"led\"+led_sts, true);   ";
    ptr +="  xhttp.send();        ";
    ptr +=" } ";
    ptr +="setInterval(function()       ";
    ptr +="{        ";
    ptr +="  getData();    ";
    ptr +="}, 2000);       ";
    ptr +="function getData() {   ";
    ptr +="  var xhttp = new XMLHttpRequest();       ";
    ptr +="  xhttp.onreadystatechange = function() {        ";
    ptr +="    if (this.readyState == 4 && this.status == 200) {        ";
    ptr +="      document.getElementById(\"adc_val\").innerHTML = this.responseText;    ";
    ptr +="    }        ";
    ptr +="  };        ";
    ptr +="  xhttp.open(\"GET\", \"adcread\", true);    ";
    ptr +="  xhttp.send();     ";
    ptr +="}        ";
    ptr +="</script>   ";
    ptr +="</head>";
    ptr +="<body>";

    // КНОПКИ
    ptr +="<a class=\"button button-off\"  onclick=\"send(1)\">LED ON</a>";
     if (a == 1) {
        pinMode(2, OUTPUT);
     digitalWrite(2, 1);

     }
    ptr +="<a class=\"button button-off\"  onclick=\"send(2)\">LED OFF</a>";
     if (a == 2) {
        pinMode(2, OUTPUT);
     digitalWrite(2, 0);

     }
    ptr +="<a class=\"button button-off\"  onclick=\"send(3)\">FORWARD</a>";
     if (a == 3) {
        pinMode(4, OUTPUT);
     digitalWrite(4, 0);
    pinMode(5, OUTPUT);
     digitalWrite(5, speed);

     }
    ptr +="<a class=\"button button-off\"  onclick=\"send(4)\">STOP</a>";
     if (a == 4) {
        pinMode(4, OUTPUT);
     digitalWrite(4, 0);
    pinMode(5, OUTPUT);
     digitalWrite(5, 0);

     }
    ptr +="<a class=\"button button-off\"  onclick=\"send(5)\">BACK</a>";
     if (a == 5) {
        pinMode(13, OUTPUT);
     digitalWrite(13, 1);
    pinMode(13, OUTPUT);
     digitalWrite(13, 1);

     }
    ptr +="<a class=\"button button-off\"  onclick=\"send(6)\">LEFT</a>";
     if (a == 6) {
        pinMode(13, OUTPUT);
     digitalWrite(13, 1);
    pinMode(13, OUTPUT);
     digitalWrite(13, 1);

     }
    ptr +="<a class=\"button button-off\"  onclick=\"send(7)\">RIGHT</a>";
     if (a == 7) {
        pinMode(13, OUTPUT);
     digitalWrite(13, 1);
    pinMode(13, OUTPUT);
     digitalWrite(13, 1);

     }


        ptr +="</body>";
    ptr +="</html>";
    return ptr;
  }






// **** Область объявления ПЕРЕМЕННЫХ и номеров подключаемых PIN'ов ****

// 1. подключите пины драйвера L298N к цифровым пинам Arduino


// первый двигатель
// int enA = 7;
// int in1 = 6;
// int in2 = 5;

// второй двигатель
// int enB = 2;
// int in3 = 3;
// int in4 = 4;

// 1.1 подключение маленького драйвера

const int PinA1 = 4;  // (ШИМ) вывод 5 соединен с выводом А1
const int PinA2 = 5;  // (ШИМ) вывод 6 соединен с выводом А2
const int PinB1 = 18; // (ШИМ) вывод 10 соединен с выводом (pin) B1
const int PinB2 = 19;  //(ШИМ) вывод 11 соединен с выводом (pin)B2
byte speed = 250;  // измените это значение (0-255), 





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

// WIFI

// Serial.begin(9600);
    delay(100);
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    delay(100);
   server.on("/", handle_OnConnect);
    server.on("/led1", handle_led1off);
    server.on("/led2", handle_led2off);
    server.on("/led3", handle_led3off);
    server.on("/led4", handle_led4off);
    server.on("/led5", handle_led5off);
    server.on("/led6", handle_led6off);
    server.on("/led7", handle_led7off);
    server.on("/led8", handle_led8off);
    server.on("/led9", handle_led9off);
    server.on("/led10", handle_led10off);

    server.onNotFound(handle_NotFound);
    server.begin();
    Serial.println("HTTP server started");


}



void loop() {

// скрипт ультразвукового датчика
distance ();
}

    server.handleClient();
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


void back() 
{
  analogWrite(PinA1, 0);
  analogWrite(PinA2, speed);
  analogWrite(PinB1, 0);
  analogWrite(PinB2, speed);
}
void forward() 
{
  analogWrite(PinA1, speed);
  analogWrite(PinA2, 0);
  analogWrite(PinB1, speed);
  analogWrite(PinB2, 0);
}
void left() // В левую сторону
{
  analogWrite(PinA1, speed);
  analogWrite(PinA2, 0);
  analogWrite(PinB1, 0);
  analogWrite(PinB2, speed);
}
void right() //В правую сторону
{
  analogWrite(PinA1, 0);
  analogWrite(PinA2, speed);
  analogWrite(PinB1, speed);
  analogWrite(PinB2, 0);
}
void stop() //Стоп
{
  analogWrite(PinA1, 0);
  analogWrite(PinA2, 0);
  analogWrite(PinB1, 0);
  analogWrite(PinB2, 0);
  delay (2000);
}






// ПРОЦЕДУРЫ БОЛЬШОГО ДВИГАТЕЛЯ

// // движение вперед
// void forward() { 
//     // выставляем 100% мощность на моторе А - 255 из 255
//     analogWrite( enA, 255 );
//     analogWrite( enB, 255 );
//     // режим мотора
//     digitalWrite( in1, HIGH );
//     digitalWrite( in2, LOW );
//     digitalWrite( in3, LOW );
//     digitalWrite( in4, HIGH );
//         Serial.println("Движение вперед");
// }

// // движение назад
// void back() { 
//     // выставляем мощность на мотора А - 150 из 255
//     analogWrite( enA, 255 );
//     analogWrite( enB, 255 );
//     // режим мотора
//     digitalWrite( in1, LOW );
//     digitalWrite( in2, HIGH );
//     digitalWrite( in3, HIGH );
//     digitalWrite( in4, LOW );
//         Serial.println("Движение назад");
// }



// // движение вправо
// void left() { 
//     // выставляем мощность на мотора А - 150 из 255
//     analogWrite( enA, 150 );
//     analogWrite( enB, 150 );
//     // режим мотора
//     digitalWrite( in1, LOW );
//     digitalWrite( in2, HIGH );
//     digitalWrite( in3, LOW );
//     digitalWrite( in4, HIGH );
//         Serial.println("Поворот вправо");
// }

// // движение вправо
// void right() { 
//     // выставляем мощность на мотора А - 150 из 255
//     analogWrite( enA, 150 );
//     analogWrite( enB, 150 );
//     // режим мотора
//     digitalWrite( in1, HIGH );
//     digitalWrite( in2, LOW );
//     digitalWrite( in3, HIGH );
//     digitalWrite( in4, LOW );
//         Serial.println("Поворот влево");
// }

// // остановка
// void stop() {
//   digitalWrite(in1, LOW);
//   digitalWrite(in2, LOW);
//   digitalWrite(in3, LOW);
//   digitalWrite(in4, LOW);
//       Serial.println("Остановка");
//   }


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