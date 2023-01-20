void TR() {
  Serial.println("Turn Right");
  digitalWrite(FM1, HIGH);
  digitalWrite(FM2, LOW);
  digitalWrite(FM3, LOW);
  digitalWrite(FM4, LOW);

  digitalWrite(BM1, HIGH);
  digitalWrite(BM2, LOW);
  digitalWrite(BM3, LOW);
  digitalWrite(BM4, LOW);
}

void TL() {
  Serial.println("Turn Left");
  digitalWrite(FM1, LOW);
  digitalWrite(FM2, LOW);
  digitalWrite(FM3, HIGH);
  digitalWrite(FM4, LOW);

  digitalWrite(BM1, LOW);
  digitalWrite(BM2, LOW);
  digitalWrite(BM3, HIGH);
  digitalWrite(BM4, LOW);
}

void UP() {
  Serial.println("Up");

  digitalWrite(FM1, HIGH);
  digitalWrite(FM2, LOW);
  digitalWrite(FM3, HIGH);
  digitalWrite(FM4, LOW);

  digitalWrite(BM1, HIGH);
  digitalWrite(BM2, LOW);
  digitalWrite(BM3, HIGH);
  digitalWrite(BM4, LOW);
}

void DOWN() {
  Serial.println("Down");

  digitalWrite(FM1, LOW);
  digitalWrite(FM2, HIGH);
  digitalWrite(FM3, LOW);
  digitalWrite(FM4, HIGH);

  digitalWrite(BM1, LOW);
  digitalWrite(BM2, HIGH);
  digitalWrite(BM3, LOW);
  digitalWrite(BM4, HIGH);
}

void STOP() {
  Serial.println("Stop");

  digitalWrite(FM1, LOW);
  digitalWrite(FM2, LOW);
  digitalWrite(FM3, LOW);
  digitalWrite(FM4, LOW);

  digitalWrite(BM1, LOW);
  digitalWrite(BM2, LOW);
  digitalWrite(BM3, LOW);
  digitalWrite(BM4, LOW);

}

void RL() {
  Serial.println("Reverse left");
}

void RR() {
  Serial.println("Reverse left");
}
