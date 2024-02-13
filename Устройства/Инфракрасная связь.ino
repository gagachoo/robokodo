#include <IRremote.hpp>         // Подключаем библиотеку
#define IR_RECEIVE_PIN 2        // Сигнальный вывод, подключенный к Ардуино
void setup()
{
  Serial.begin(9600); 
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Инициализация приемника
}
void loop() {
  if (IrReceiver.decode()) {        // // Проверяем, пришли ли данные
      switch(IrReceiver.decodedIRData.decodedRawData){
          case 0xF20DFF00:
          Serial.println("#");
          break;
          case 0xE916FF00:
          Serial.println("*");
          break;
          case 0xE718FF00:
          Serial.println("UP");
          break;  
          case 0xAD52FF00:
          Serial.println("DOWN");
          break;               
          case 0xF708FF00:
          Serial.println("LEFT");
          break;  
          case 0xA55AFF00:
          Serial.println("RIGHT");
          break;  
          case 0xE31CFF00:
          Serial.println("OK");
          break;  
          case 0xE619FF00:
          Serial.println("0");
          break;  
          case 0xBA45FF00:
          Serial.println("1");
          break;
          case 0xB946FF00:
          Serial.println("2");
          break;
          case 0xB847FF00:
          Serial.println("3");
          break;
          case 0xBB44FF00:
          Serial.println("4");
          break;
          case 0xBF40FF00:
          Serial.println("5");
          break;
          case 0xBC43FF00:
          Serial.println("6");
          break;
          case 0xF807FF00:
          Serial.println("7");
          break;
          case 0xEA15FF00:
          Serial.println("8");
          break;
          case 0xF609FF00:
          Serial.println("9");
          break;      
        }
        light();
      IrReceiver.resume(); // Включение приема следующего значения
  }
}

void light() {
  if ( IrReceiver.decode( &results )) { // если данные пришли
    switch ( results.value ) {
    case 0xBA45FF00:
        digitalWrite( 13, HIGH );
            Serial.println("Включился светодиод"); // выводим на монитор порта сообщение о включении
        break;
    case 0xE31CFF00:
        digitalWrite( 13, LOW );
            Serial.println("Выключился светодиод"); // выводим на монитор порта сообщение о выключении
        break;
    }    
    irrecv.resume(); // принимаем следующую команду
}

if (results.value==0xBA45FF00){
digitalWrite( 13, HIGH );
            Serial.println("Включился светодиод"); // выводим на монитор порта сообщение о включении}

}
