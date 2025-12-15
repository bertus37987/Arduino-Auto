int T1 = A1; //Rechts
int T2 = A3;//Links
int regler = A0; //Regler Der Geschwindikeit
int starter = 12; //Digitaler Eingang des Starters
int geradeaus_3; // Map für Geraudaus von Motor 3
int geradeaus_5; //Map von Geradeaus von Motor 5
int messung;
int an = 0;
int ledlinienfolge = 7; //Led der Lineinfolge

void setup() {
  pinMode(ledlinienfolge, OUTPUT); //Led linienfolge auf output
  digitalWrite(ledlinienfolge, HIGH); //Led der linienfolge permanent an
  Serial.begin(9600);
  pinMode(starter, INPUT); // Starter-Pin als Eingang konfigurieren
}

void loop() {
  while (an == 0) {
    if (digitalRead(starter) == 1)
    {
      an = 1;
      Serial.println(an);
      Serial.print("  an ");
    }
  }

  int rechts = analogRead(T1); //Linienfolge Sensor Rechts wird gelesen
  Serial.print(rechts);
  Serial.print(" | Rechts ");
  Serial.println();
  
  
  int links = analogRead(T2);  //Linienfolge Sensor Links wird gelesen
  Serial.print(links);
  Serial.print(" | Links ");
  Serial.println();

  delay(300);
  
    if (links <= 700 && rechts <= 700) { //Logik Gerade aus Fahren

    int ubergabe_regler = analogRead(regler); //Geschwindikeits Regler
    Serial.println("ubergabe_regler");
    Serial.println(ubergabe_regler);
    Serial.println(" |||||DAS AUTO FÄHRT GERADEAUS||||");

    geradeaus_3 = map(ubergabe_regler, 0, 1023, 0, 225);
    geradeaus_5 = map(ubergabe_regler, 0, 1023, 0, 255);
    Serial.println(geradeaus_3);
    Serial.println(geradeaus_5);
    analogWrite(3, geradeaus_3);
    analogWrite(5, geradeaus_5);
  }
  else if (links < 700) { //Logik Rechts Fahren Trigger wenn T2 niedrig T2 = links
    analogWrite(3, 225);
    analogWrite(5, 127);
    Serial.println("|||DAS AUTO FÄHRT LINKS|||");
  }
  else if (rechts < 700) { //Logik Links Fahren Trigger wenn T1 niedrig T1 = Rechts
    analogWrite(3, 112);
    analogWrite(5, 255);
    Serial.println("|||DAS AUTO FÄHRT RECHTS|||");
  }

  else { //Fehler
    Serial.println("Fehler mit der Linienfolge");
  }



}
