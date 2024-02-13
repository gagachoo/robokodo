void setup() {
  pinMode(3, OUTPUT);
}
void loop() {
  digitalWrite(3, 1);
  delay(500);
  digitalWrite(3, 0);
  delay(500);
}