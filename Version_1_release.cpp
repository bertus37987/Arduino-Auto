int angespasstegeschwindikeit; //Neu Geschwindikeit 
int T1 = A1; //Rechts
int T2 = A3;//Links
int regler = A0; //Regler Der Geschwindikeit
int starter = 12; //Digitaler Eingang des Starters
int geradeaus_3; // Map für Geraudaus von Motor 3
int geradeaus_5; //Map von Geradeaus von Motor 5
int messung;
int an = 0;
int ledlinienfolge = 7; //Led der Lineinfolge
int triggerPin = 11;
int echoPin = 10;
long dauer; //In der Lage doppelt so viel zu storen
int entfernung;

void setup(){
    pinMode(3,OUTPUT);//5,3 Motoren
    pinMode(5,OUTPUT);
    pinMode(6, OUTPUT);  // Rote LED
  pinMode(8,OUTPUT);  // Gelbe LED
  pinMode(9,OUTPUT); // Grüne LED
    pinMode(ledlinienfolge, OUTPUT); //Led linienfolge auf output
    digitalWrite(ledlinienfolge, HIGH); //Led der linienfolge permanent an
    Serial.begin(9600);//Serieler Monitor wird angeschaltet
  pinMode(starter, INPUT); // Starter-Pin als Eingang konfigurieren, zussamenhang startknopf
  pinMode(triggerPin, OUTPUT);//Input und Output Für die Geschwindikeites Messung
  pinMode(echoPin, INPUT);
}
void loop(){
 while (an == 0) {                      //Beginn der Auto Logik mit dem Starter
    if (digitalRead(starter) == 1)
    {
      an = 1;
      Serial.println(an);
      Serial.print("  an ");
    }
  }
// Abstand messen
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH); // Trigger-Signal senden
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  dauer = pulseIn(echoPin, HIGH); // Zeit messen bis Echo zurückkommt
  entfernung = (dauer / 2) / 29.1; // In Zentimeter umrechnen
  
  Serial.print("Abstand: ");
  Serial.print(entfernung);
  Serial.println(" cm");
//Aktionen wegen dem Abstand
  // Logik LED
  if (entfernung < 10 && entfernung > 0) { // Rote LED als Warnung auf pin 6
    analogWrite(6, 255);
    analogWrite(8, 0);
    analogWrite(9, 0);
  }
  else if (entfernung < 20 && entfernung > 0) { // GELBE LED auf pin 9
    analogWrite(6, 0);
    analogWrite(8, 255);
    analogWrite(9, 0);
  }
  else { // Grüne LED auf pin 10
    analogWrite(6, 0);
    analogWrite(8,0);
    analogWrite(9,255);
  }
 // Bumper-Logik: Stopp bei Abstand < 15 cm, 
  if (entfernung < 15 && entfernung > 0) {
    analogWrite(3, 0); // Beide Motoren stoppen
    analogWrite(5, 0);
    Serial.println("Ein Hindernis wurde Erkannt, Motoren Werden Gestoppt");
    return; // Linienfolger-Code überspringen, kann problematisch für Tests Sein
  }




//Linienfolge Sensoren Auslesen
 int rechts = analogRead(T1); //Linienfolge Sensor Rechts wird gelesen
  Serial.print(rechts);
  Serial.print(" | Rechts ");
  Serial.println();
  
  
  int links = analogRead(T2);  //Linienfolge Sensor Links wird gelesen
  Serial.print(links);
  Serial.print(" | Links ");
  Serial.println();
//Anpassung der Geschwindikeit
int startgeschwindikeit = analogRead(regler); // Orginal Max Geschwindikeit 

if (entfernung < 30 && entfernung > 0){ // änderung der Geschwindikeit
    angespasstegeschwindikeit = map(entfernung, 0, 30, 0, startgeschwindikeit);//Logik Für die Anpassung der Geschwindikeit
}
else{
    angepasstegeschwindikeit = startgeschwindikeit; // rückehr zur orginal ausgelsenen geschwinikeit
}

//Logik Entscheidung ob links oder Rechts Fahren und potenzomenter

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
    Serial.println("|||DAS AUTO FÄHRT RECHTS|||");
  }
  else if (rechts < 700) { //Logik Links Fahren Trigger wenn T1 niedrig T1 = Rechts
    analogWrite(3, 112);
    analogWrite(5, 255);
    Serial.println("|||DAS AUTO FÄHRT LINKS|||");
  }

  else { //Fehler
    Serial.println("Fehler mit der Linienfolge");
  }

}

//Es fehlen noch implimentierungen der geschwindikeitsänderung Bezogen auf die linienfolge.













