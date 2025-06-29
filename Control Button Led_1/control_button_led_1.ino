void setup() {
  // put your setup code here, to run once:
  pinMode(27, OUTPUT);
  pinMode(4, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(4) == HIGH) {
    digitalWrite(27, HIGH);
  } else {
    digitalWrite(27, LOW);
  }
}
