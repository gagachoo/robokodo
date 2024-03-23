/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-websocket-server-arduino/
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/


#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define AP_SSID "ESP"
#define AP_PSW "ESP2103"


const int PinA1 = 4;  // (ШИМ) вывод 5 соединен с выводом А1
const int PinA2 = 5;  // (ШИМ) вывод 6 соединен с выводом А2
const int PinB1 = 18; // (ШИМ) вывод 10 соединен с выводом (pin) B1
const int PinB2 = 19;  //(ШИМ) вывод 11 соединен с выводом (pin)B2
byte speed = 250;  // измените это значение (0-255), 


// // 2. подключите пины драйвера HC-SR04 к цифровым пинам Arduino

// int trigPin = 1; // назначаем имя для Pin3
// int echoPin = 3; // назначаем имя для Pin1

// int duration, cm; // назначаем переменную "cm" и "duration" для показаний датчика

// переменная для хранения HTTP-запроса:
String header;

// переменные для расшифровки HTTP-запроса GET:
String valueString = String(5);

String state; //сюда будет писаться состояние, т.е. куда едет машинка в данный момент

//------- переменные для отслеживания связи и остановки двигателей ------------
unsigned long pingTime = 0;
int periodTime = 1000; //период проверки связи в миллисек
unsigned long pongTime = 0; // должен быть не более времени периода проверки пингов, иначе стопим машину
bool connected = false; // наличие соединения
//client methods
AsyncWebSocketClient *client_global;



//-------------------БЛОК РАБОТЫ С WEBSOCKET И ОТОБРАЖЕНИЯ ВЕБ-СТРАНИЦЫ----------------------------------------

bool ledState = 0;
const int ledPin = 2;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
  html {
    font-family: Arial, Helvetica, sans-serif;
    text-align: center;
  }
  h1 {
    font-size: 1.8rem;
    color: white;
  }
  h2{
    font-size: 1.5rem;
    font-weight: bold;
    color: #143642;
  }
  .topnav {
    overflow: hidden;
    background-color: #143642;
  }
  body {
    margin: 0;
  }
  .content {
    padding:  5 px; //30px;
    display: flex;
    justify-content: center;
    //    margin: 0 auto;
    text-align: center;
    //    margin-left: auto;
    //    margin-right: auto;
  }

    .content2 {
    padding:  5 px; //30px;
    display: flex;
    justify-content: space-between;
    //   // padding:  px; //30px;
    //     max-width: 400px;
    //    margin: 0 auto;
  }

    .content3 {
       padding: 40 px; //30px;
       display: flex;
       justify-content: center;
  }



  .button1 {
    
    padding: 15px 50px;
    font-size: 24px;
    text-align: center;
    outline: none;
    color: #fff;
    background-color: #0f8b8d;
    border: none;
    border-radius: 5px;
    width: 670px;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
   }

  .button2 {
    padding: 15px 5px;
    font-size: 24px;
    text-align: center;
    outline: none;
    color: #fff;
    background-color: #0f8b8d;
    border: none;
    border-radius: 5px;
    width: 140px;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
   }

   /*.button:hover {background-color: #0f8b8d}*/
   .button:active {
     background-color: #0f8b8d;
     box-shadow: 2 2px #CDCDCD;
     transform: translateY(2px);
   }
     
  </style>
<title>ESP Web Server</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
</head>


<body>

   
   <div class="content">
      <p><button id="button" class="button1">forward</button></p>
   </div>

   <div class="content2">
      <p><button id="button2" class="button2"><<< left</button></p>
      <p><button id="button3" class="button2">right >>></button></p>
      </div>
      
   <div class="content3">    
      <p><button id="button4" class="button1">reverse</button></p>
  </div>

<script>
  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
  window.addEventListener('load', onLoad);
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage; 
  }
  function onOpen(event) {
    console.log('Connection opened');
  }
  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }
  function onMessage(event) {
    var state;
    if (event.data == "1"){
      state = "ON";
    }
    else{
      state = "OFF";
    }
    document.getElementById('state').innerHTML = state;
  }
  function onLoad(event) {
    initWebSocket();
    initButton();
    initButton2();
    initButton3();
    initButton4();
  }
  function initButton() {
      document.getElementById('button').addEventListener('touchstart', forward, false);
      document.getElementById('button').addEventListener('touchend', stopper, false);
  }
  function forward(){
    websocket.send('forward');
  }


   function initButton2() {
      document.getElementById('button2').addEventListener('touchstart', left, false);
      document.getElementById('button2').addEventListener('touchend', stopper, false);
  }
  function left(){
    websocket.send('left');
  }


  function initButton3() {
      document.getElementById('button3').addEventListener('touchstart', right, false);
      document.getElementById('button3').addEventListener('touchend', stopper, false);
  }
  function right(){
    websocket.send('right');
  }  


   function initButton4() {
        document.getElementById('button4').addEventListener('touchstart', reverse, false);
        document.getElementById('button4').addEventListener('touchend', stopper, false);
    }
    function reverse(){
      websocket.send('reverse');
    }  

 function stopper(){
    websocket.send('stop');
  }
  
</script>
</body>



</html>
)rawliteral";


void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) { // обрабатываем получаемые сообщения
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    if (strcmp((char*)data, "forward") == 0) {
      ledState = !ledState;


      Serial.println("Forward");  //  "Вперед"
  
      state = "Forward";
      //сюда вписать обработку для движения вперед;
      forward32();
      SvetUp();
    }
    else if (strcmp((char*)data, "left") == 0) {
      ledState = !ledState;


      Serial.println("Left");  //  "Влево"

      state = "Left";
      //сюда вписать обработку для движения влево;
      left32();
      SvetUp();
    }
    else if (strcmp((char*)data, "right") == 0) {
      ledState = !ledState;

      Serial.println("Right");  //  "Вправо"

      state = "Right";
      //сюда вписать обработку для движения вправо;
      right32();
      SvetUp();
    }
    else if (strcmp((char*)data, "reverse") == 0) {
      ledState = !ledState;

      Serial.println("Reverse");  //  "Назад"

      state = "Reverse";
      //сюда вписать обработку для движения назад;
      back32();
      SvetUp();
    }
    else if (strcmp((char*)data, "stop") == 0) {
      ledState = !ledState;

      Serial.println("Stop");  //  "Стоп"

      state = "Stop";
      //сюда вписать обработку для остановки;
      stop32();
      SvetDown();
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      client->ping();
      connected = true;
      client_global = client;
      break;
    case WS_EVT_DISCONNECT:
      stop32();
      connected = false;
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
      pongTime = millis();
      break;
    case WS_EVT_ERROR:
      stop32();
      connected = false;
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if (ledState){
      return "ON";
    }
    else{
      return "OFF";
    }
  }
}

// движение вперед
void forward32() { 
  analogWrite(PinA1, speed);
  analogWrite(PinA2, 0);
  analogWrite(PinB1, speed);
  analogWrite(PinB2, 0);
  Serial.println("Движение вперед");
}

// движение назад
void back32() { 
  analogWrite(PinA1, 0);
  analogWrite(PinA2, speed);
  analogWrite(PinB1, 0);
  analogWrite(PinB2, speed);
  Serial.println("Движение назад");
}



// движение вправо
void left32() { 
  analogWrite(PinA1, speed);
  analogWrite(PinA2, 0);
  analogWrite(PinB1, 0);
  analogWrite(PinB2, speed);
  Serial.println("Поворот вправо");
}

// движение вправо
void right32() { 
  analogWrite(PinA1, 0);
  analogWrite(PinA2, speed);
  analogWrite(PinB1, speed);
  analogWrite(PinB2, 0);
  Serial.println("Поворот влево");
}

// остановка
void stop32() {
  analogWrite(PinA1, 0);
  analogWrite(PinA2, 0);
  analogWrite(PinB1, 0);
  analogWrite(PinB2, 0);
  Serial.println("Остановка");
}

// // СКРИПТ ДЛЯ УЛЬТРАЗВУКОВОГО ДАЛЬНОМЕРА HC-SR04
// void distance () { 
//   digitalWrite(trigPin, LOW); // изначально датчик не посылает сигнал
//   delayMicroseconds(5); // ставим задержку в 2 ммикросекунд

//   digitalWrite(trigPin, HIGH); // посылаем сигнал
//   delayMicroseconds(20); // ставим задержку в 10 микросекунд
//   digitalWrite(trigPin, LOW); // выключаем сигнал

//   duration = pulseIn(echoPin, HIGH); // включаем прием сигнала

//   cm = duration / 58; // вычисляем расстояние в сантиметрах

//   Serial.print(cm); // выводим расстояние в сантиметрах
//   Serial.println(" cm");
//   }

void SvetUp()
{
  pinMode(4, OUTPUT);
  digitalWrite(4, 1);
}

void SvetDown()
{
  digitalWrite(4, 0);
}

//-------------------------------------------------------------------------------------------------------








void setup() {
  Serial.begin(9600);
//  SvetUp();
//  //зажигаем подсветку на 1 сек для демонстрации включения
//  delay(1000);
//  SvetDown();

  pinMode(PinA1, OUTPUT); // установите контакты на выход
  pinMode(PinA2, OUTPUT);
  pinMode(PinB1, OUTPUT);
  pinMode(PinB2, OUTPUT);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PSW);
  // Connect to Wi-Fi
  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.println("Connecting to WiFi..");
  // }

// Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  initWebSocket();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Start server
  server.begin();


  
}//setup

  



void loop(){

  ws.cleanupClients();
  if (pingTime + periodTime < millis()){
    if (connected) {
      client_global->ping();
      Serial.printf("pingTime = [%u], pongTime = [%u]", pingTime, pongTime);
      if ((pingTime > pongTime)&&((pingTime - pongTime) > (periodTime*2))){
        stop32();
        connected = false;
      }
    }
    pingTime = millis();
  }
    
}
