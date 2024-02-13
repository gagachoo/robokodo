int tonePin = 3;// пин пищалки

void setup() {
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
    
void loop() {

}