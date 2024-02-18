    #include <LedControl.h>

int tonePin = 11;// пин пищалки
int trigPin = 9; // назначаем имя для Pin8
int echoPin = 8; // назначаем имя для Pin9

int duration, cm; // назначаем переменную "cm" и "duration" для показаний датчика


LedControl lclm=LedControl(0,2,1,1);




void setup()
{
  pinMode(trigPin, OUTPUT); // назначаем trigPin (Pin8), как выход
  pinMode(echoPin, INPUT); // назначаем echoPin (Pin9), как вход
  // Serial.begin (9600);

}


void loop() {
distance ();
cat();
}






void cat() {
  if(cm>70)
sleep();
else
{
  for(int i=0;i<50;i++)
  {
    distance ();
    while(cm<70)
    {
      happy();
      distance ();
    }
    sleep();      
    }
}
}


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


void sound () {
    tone(tonePin, 261.63, 200);
    delay(200);
    tone(tonePin, 293.66, 200);
    delay(200);
    tone(tonePin, 329.63, 200);
    delay(200);
    tone(tonePin, 349.23, 200);
    delay(400);
    tone(tonePin, 550.00, 200);
    delay(200);
    }




void sleep () {


    lclm.setIntensity(0,15);
     lclm.shutdown(0,false);
    lclm.setRow(0,0,B00000000);lclm.setRow(0,1,B01000010);lclm.setRow(0,2,B10100101);
    lclm.setRow(0,3,B00000000);lclm.setRow(0,4,B00011000);lclm.setRow(0,5,B00111100);
    lclm.setRow(0,6,B00111100);lclm.setRow(0,7,B00011000);


}





void happy () {

    lclm.setIntensity(0,15);
     lclm.shutdown(0,false);
    lclm.setRow(0,0,B00000000);lclm.setRow(0,1,B01000010);lclm.setRow(0,2,B10100101);
    lclm.setRow(0,3,B00000000);lclm.setRow(0,4,B00111100);lclm.setRow(0,5,B00000000);
    lclm.setRow(0,6,B00000000);lclm.setRow(0,7,B00000000);
delay (400);
     lclm.shutdown(0,false);
    lclm.setRow(0,0,B00000000);lclm.setRow(0,1,B00000000);lclm.setRow(0,2,B01000010);
    lclm.setRow(0,3,B10100101);lclm.setRow(0,4,B00000000);lclm.setRow(0,5,B00111100);
    lclm.setRow(0,6,B00000000);lclm.setRow(0,7,B00000000);
delay(400);

sound();
}
