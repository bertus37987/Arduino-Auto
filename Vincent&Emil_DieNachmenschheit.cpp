int starter = 12; // Pin für den Startknopf
int ledlinienfolge = 7; // Led der Linienfolge

void setup() {
 pinMode(3, OUTPUT);  // Motor
 pinMode(5, OUTPUT);  // Motor
 digitalWrite(ledlinienfolge, HIGH); // Die Led der Linienfolge wird permanent angeschaltet, da sonst probleme entsetehen können !

}

void loop() {
    // Beginn der Auto Logik mit dem Starter
 int an = 0;

 if (digitalRead(starter) == 1) {
  an = !an;                  // Wenn an nicht gleich an ist dann ->
  while (digitalRead(starter) == 1) {
  }                          // warten bis losgelassen
   delay(50);                 // gegen Prellen
 }
  
  
  
  
  // Linienfolge Sensoren Auslesen A1 = Rechts
  int rechts = analogRead(A1); // Linienfolge Sensor Rechts wird gelesen
  Serial.print(rechts);
  Serial.print(" | Rechts ");
  Serial.println();
  // A2 = Links
  int links = analogRead(A3); // Linienfolge Sensor Links wird gelesen
  Serial.print(links);
  Serial.print(" | Links ");
  Serial.println();

  // Logik Entscheidung ob links oder Rechts Fahren
  if (links >= 550 && rechts >= 550) { // Logik Geradeaus Fahren
    Serial.println("DAS AUTO FÄHRT GERADEAUS");
    analogWrite(3, //Beispielwert
    );
    analogWrite(5, //Beispielwert
    );
  }
  else if (links < 550) { // Logik Rechts Fahren (wenn T2 niedrig, T2 = links)
    analogWrite(3, //Beispielwert
    );
    analogWrite(5, //Beispielwert
    );
    Serial.println("DAS AUTO FÄHRT RECHTS");
  }
  else if (rechts < 550) { // Logik Links Fahren (wenn T1 niedrig, T1 = Rechts)
    analogWrite(3, //Beispielwert
    );
    analogWrite(5, //Beispielwert
    );
    Serial.println("DAS AUTO FÄHRT LINKS");
  }
  else { // Fehler sollte nie passiere, gut für tests !
    Serial.println("Fehler mit der Linienfolge");
  }
}
