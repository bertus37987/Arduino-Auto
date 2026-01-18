/*
Arduino Auto Tom & Willy
Enthaltene funktionen:
-Linienfolge
-Geschwindigkeitsregler
-Starter/ Stop durch reset
-Abstandswarner
-Bumper
-Automatische Geschwindigkeitsanpassung

Informationen:
 T1 = A1 Rechts (zum merken, weil variablen dürfen keine buchstaben enthalten.)
 T2 = A3 Links.
 regler = A0 Regler für die Startgeschwindigkeit.
*/

// Variablen für den Regler und die automatische Anpassung der Geschwindigkeit
int startgeschwindikeit;
int startgeschwindikeit1;
int startgeschwindikeit2;
int angespasstegeschwindikeit;
int angespasstegeschwindikeit1;
int angespasstegeschwindikeit2;
int starter = 12; // Digitaler Eingang des Starters
int geradeaus_3; // Map für Geradeaus von Motor 3
int geradeaus_5; // Map von Geradeaus von Motor 5
int messung;
int an = 0;
int ledlinienfolge = 7; // Led der Linienfolge
int entfernung;
int triggerPin = 11;
int echoPin = 2;
long dauer; // In der Lage doppelt so viel zu speichern

void setup() {
  pinMode(3, OUTPUT);  // Motor
  pinMode(5, OUTPUT);  // Motor
  pinMode(8, OUTPUT);  // Rote LED
  pinMode(9, OUTPUT);  // Gelbe LED
  pinMode(10, OUTPUT); // Grüne LED
  pinMode(ledlinienfolge, OUTPUT); // Led linienfolge auf output
  pinMode(starter, INPUT); // Starter-Pin als Eingang konfigurieren
  pinMode(triggerPin, OUTPUT); // Trigger-Pin für Ultraschallsensor
  pinMode(echoPin, INPUT);     // Echo-Pin für Ultraschallsensor
  
  digitalWrite(ledlinienfolge, HIGH); // Led der Linienfolge permanent an
  Serial.begin(9600); // Serieller Monitor wird angeschaltet
}

void loop() {
  // Beginn der Auto Logik mit dem Starter
  while (an == 0) {
    if (digitalRead(starter) == 1) {
      an = 1;
      Serial.println(an);
      Serial.print("  an ");
    }
  }
  
  // Ultraschallsensor auslesen
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH); // Trigger-Signal senden
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  dauer = pulseIn(echoPin, HIGH); // Zeit messen bis Echo zurückkommt
  entfernung = dauer * 0.034 / 2; // In Zentimeter umrechnen
  
  Serial.print("Abstand: ");
  Serial.print(entfernung);
  Serial.println(" cm");

  // Aktionen wegen dem Abstand - LED Logik
  if (entfernung < 10 && entfernung > 0) { // Rote LED als Warnung
    digitalWrite(8, HIGH); // Rot
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
  }
  else if (entfernung < 20 && entfernung > 0) { // Gelbe LED
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH); // Gelb
    digitalWrite(10, LOW);
  }
  else { // Grüne LED
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH); // Grün
  }
  
  // Bumper-Logik: Stopp bei Abstand < 5 cm
  if (entfernung < 5 && entfernung > 0) {
    analogWrite(3, 0); // Beide Motoren stoppen
    analogWrite(5, 0);
    Serial.println("Ein Hindernis wurde Erkannt, Motoren Werden Gestoppt");
    digitalWrite(8, HIGH); // Rot
    return; // Linienfolger-Code überspringen
  }
  else {
    // Linienfolge Sensoren Auslesen
    int rechts = analogRead(A1); // Linienfolge Sensor Rechts wird gelesen
    Serial.print(rechts);
    Serial.print(" | Rechts ");
    Serial.println();
    
    int links = analogRead(A3); // Linienfolge Sensor Links wird gelesen
    Serial.print(links);
    Serial.print(" | Links ");
    Serial.println();
    
    // Anpassung der Geschwindigkeit
    startgeschwindikeit = analogRead(A0); // Original Max Geschwindigkeit am Potentiometer eingestellt
    startgeschwindikeit1 = map(startgeschwindikeit, 0, 1023, 0, 111);
    startgeschwindikeit2 = map(startgeschwindikeit, 0, 1023, 0, 127);
    
    if (entfernung < 30 && entfernung > 0) { // Änderung der Geschwindigkeit
      angespasstegeschwindikeit1 = map(entfernung, 0, 30, 0, startgeschwindikeit1);
      angespasstegeschwindikeit2 = map(entfernung, 0, 30, 0, startgeschwindikeit2);
    }
    else {
      angespasstegeschwindikeit1 = startgeschwindikeit1; // Rückkehr zur original ausgelesenen Geschwindigkeit
      angespasstegeschwindikeit2 = startgeschwindikeit2;
    }
    
    // Logik Entscheidung ob links oder Rechts Fahren
    if (links >= 550 && rechts >= 550) { // Logik Geradeaus Fahren
      Serial.println(" ---DAS AUTO FÄHRT GERADEAUS--- ");
      
      analogWrite(3, angespasstegeschwindikeit1);
      analogWrite(5, angespasstegeschwindikeit2);
      Serial.println(angespasstegeschwindikeit1);
      Serial.println(angespasstegeschwindikeit2);
    }
    else if (links < 550) { // Logik Rechts Fahren (wenn T2 niedrig, T2 = links)
      analogWrite(3, 111); // Max 225 geteilt durch 1.5
      analogWrite(5, 63);  // ehemalige Hälfte 127
      Serial.println("|||DAS AUTO FÄHRT RECHTS|||");
    }
    else if (rechts < 550) { // Logik Links Fahren (wenn T1 niedrig, T1 = Rechts)
      analogWrite(3, 56);  // 112 durch 1.2
      analogWrite(5, 127); // 255
      Serial.println("|||DAS AUTO FÄHRT LINKS|||");
    }
    else { // Fehler
      Serial.println("Fehler mit der Linienfolge"); // Sollte nicht passieren, nur für Tests!
    }
  }
}
