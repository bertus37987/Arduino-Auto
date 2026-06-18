
/*
Notiz:
Ihr geht davon aus das eure Motoren gleich stark sind ?
Ich gehe davon aus 3 = links also der Motor
Ich gehe davon aus 5 = Rechts also der Motor 
*/

int starter = 12; // Pin für den Startknopf
int ledlinienfolge = 7; // Led der Linienfolge
int standartmotorrechts = 240;
int standartmotorlinks = 220; // <----------------------------------------- Kann alle Motor werte ändern
int an = 0;
void setup() {
 pinMode(3, OUTPUT);  // Motor = links
 pinMode(5, OUTPUT);  // Motor = rechts
 digitalWrite(ledlinienfolge, HIGH); // Die Led der Linienfolge wird permanent angeschaltet, da sonst probleme entsetehen können !
 Serial.begin(9600);
 pinMode(starter, INPUT_PULLUP);

}

void loop() {
    // Beginn der Auto Logik mit dem Starter

  // Beginn der Auto Logik mit dem Starter, reset stopt das auto
  while (an == 0) {
    if (digitalRead(starter) == 1) {
      an = 1;
      Serial.println(an);
      Serial.print("  an ");
    }
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
    analogWrite(3,standartmotorlinks);
    analogWrite(5,standartmotorrechts);
  }
  else if (links < 550) { // Logik Rechts Fahren (wenn T2 niedrig, T2 = links), um nach rechts zu fahren muss links stärker sein
    float links_staerke = standartmotorrechts / 2; 
    analogWrite(3,standartmotorlinks);
    analogWrite(5,links_staerke);
    Serial.println("DAS AUTO FÄHRT RECHTS");
  }
  else if (rechts < 550) { // Logik Links Fahren (wenn T1 niedrig, T1 = Rechts)
    float rechts_staerke = standartmotorlinks / 2;
    analogWrite(3,rechts_staerke);
    analogWrite(5,standartmotorrechts);
    Serial.println("DAS AUTO FÄHRT LINKS");
  }
  else { // Fehler sollte nie passiere, gut für tests !
    Serial.println("Fehler mit der Linienfolge");
  }
}
