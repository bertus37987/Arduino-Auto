// Zusätzliche Variablen am Anfang
int triggerPin = 11;
int echoPin = 10;
long dauer;
int entfernung;

void setup() {
  // Bestehender Setup-Code...
  pinMode(triggerPin, OUTPUT); // Trigger-Pin als Ausgang
  pinMode(echoPin, INPUT);     // Echo-Pin als Eingang
}

void loop() {
  // Abstand messen
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH); // 10µs Trigger-Signal senden
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  dauer = pulseIn(echoPin, HIGH); // Zeit messen bis Echo zurückkommt
  entfernung = (dauer / 2) / 29.1; // In Zentimeter umrechnen
  
  Serial.print("Abstand: ");
  Serial.print(entfernung);
  Serial.println(" cm");
  
  // Bumper-Logik: Stopp bei Abstand < 15 cm
  if (entfernung < 15 && entfernung > 0) {
    analogWrite(3, 0); // Beide Motoren stoppen
    analogWrite(5, 0);
    Serial.println("HINDERNIS! STOPP!");
    return; // Linienfolger-Code überspringen
  }
  
  // Hier kommt dein normaler Linienfolger-Code...
}
