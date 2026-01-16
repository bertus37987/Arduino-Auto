/*
Arduino Auto Tom & Willy
Enthaltene funktionen:
-Linienfolge
-Geschwindikeitsregler
-Starter/ Stop durch reset
-Abstandswarner
-Bumper
-Automatische Geschwindikeits anpassung

Informationen:
 T1 = A1 Rechts (zum merken, weil variablen dürfen keine buchstaben enthalten.)
 T2 = A3 Links.
 regler = A0 Regler für die Stargeschwindikeit.
*/
int startgeschwindikeit;//Varibalen für den Regler und die automatische anpassung der geschwindikeit.
int startgeschwindikeit1;
int startgeschwindikeit2;
int angespasstegeschwindikeit;
int angespasstegeschwindikeit1;
int angespasstegeschwindikeit2;
int starter = 12; //Digitaler Eingang des Starters
int geradeaus_3; // Map für Geraudaus von Motor 3
int geradeaus_5; //Map von Geradeaus von Motor 5
int messung;
int an = 0;
int ledlinienfolge = 7; //Led der Lineinfolge
int entfernung;
int triggerPin = 11;
int echoPin = 2;
long dauer; //In der Lage doppelt so viel zu storen




void setup(){
    pinMode(3,OUTPUT);//5,3 Motoren
    pinMode(5,OUTPUT);
    pinMode(8, OUTPUT);  // Rote LED
  pinMode(9,OUTPUT);  // Gelbe LED
  pinMode(10,OUTPUT); // Grüne LED
    pinMode(ledlinienfolge, OUTPUT); //Led linienfolge auf output
    digitalWrite(ledlinienfolge, HIGH); //Led der linienfolge permanent an
    Serial.begin(9600);//Serieler Monitor wird angeschaltet
  pinMode(starter, INPUT); // Starter-Pin als Eingang konfigurieren, zussamenhang startknopf

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
 digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH); // Trigger-Signal senden
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  dauer = pulseIn(echoPin, HIGH); // Zeit messen bis Echo zurückkommt
  entfernung = (dauer/2) * 0.03432;  // In Zentimeter umrechnen
  
  Serial.print("Abstand: ");
  Serial.print(entfernung);
  Serial.println(" cm");




//Aktionen wegen dem Abstand
  // Logik LED
  if (entfernung < 10 && entfernung > 0) { // Rote LED als Warnung auf pin 6
    analogWrite(8, 255);//Rot
    analogWrite(9, 0);
    analogWrite(10, 0);
  }
  else if (entfernung < 20 && entfernung > 0) { // GELBE LED auf pin 9
    analogWrite(8, 0);
    analogWrite(9, 255);//Gelb
    analogWrite(10, 0);
  }
  else { // Grüne LED auf pin 10
    analogWrite(8, 0);
    analogWrite(9,0);
    analogWrite(10,255);//Grün
  }
 // Bumper-Logik: Stopp bei Abstand < 5 cm, 
  if (entfernung < 5 && entfernung > 0) {
    analogWrite(3, 0); // Beide Motoren stoppen
    analogWrite(5, 0);
    Serial.println("Ein Hindernis wurde Erkannt, Motoren Werden Gestoppt");
    analogWrite(8, 255);//Rot
    return; // Linienfolger-Code überspringen, kann problematisch für Tests Sein
  }else {



//Linienfolge Sensoren Auslesen
 int rechts = analogRead(A1); //Linienfolge Sensor Rechts wird gelesen
  Serial.print(rechts);
  Serial.print(" | Rechts ");
  Serial.println();
  
  
  int links = analogRead(A3);  //Linienfolge Sensor Links wird gelesen
  Serial.print(links);
  Serial.print(" | Links ");
  Serial.println();
//Anpassung der Geschwindikeit
 startgeschwindikeit = analogRead(A0); // Orginal Max Geschwindikeit, am potenzometer eingesstellt
 startgeschwindikeit1 = map(startgeschwindikeit, 0, 1023, 0, 111);
 startgeschwindikeit2 = map(startgeschwindikeit, 0, 1023, 0, 127);

if (entfernung < 30 && entfernung > 0){ // änderung der Geschwindikeit
     angespasstegeschwindikeit1 = map(entfernung, 0, 30, 0, startgeschwindikeit1);//Logik Für die Anpassung der Geschwindikeit
     angespasstegeschwindikeit2 = map(entfernung, 0, 30, 0, startgeschwindikeit2);//Logik Für die Anpassung der Geschwindikeit
}

else{
    angespasstegeschwindikeit1 = startgeschwindikeit1; // rückehr zur orginal ausgelsenen geschwinikeit
    angespasstegeschwindikeit2 = startgeschwindikeit2;
}

//Logik Entscheidung ob links oder Rechts Fahren und potenzomenter
if (links >= 550 && rechts >= 550) { //Logik Gerade aus Fahren

     
   
    Serial.println(" ---DAS AUTO FÄHRT GERADEAUS--- ");

    geradeaus_3 = map(angespasstegeschwindikeit1, 0, 1023, 0, 111);
    geradeaus_5 = map(angespasstegeschwindikeit2, 0, 1023, 0, 127);
    Serial.println(geradeaus_3);
    Serial.println(geradeaus_5);
    analogWrite(3, geradeaus_3);
    analogWrite(5, geradeaus_5);
    
  }
  else if (links < 550) { //Logik Rechts Fahren Trigger wenn T2 niedrig T2 = links
    analogWrite(3, 111);//Max 225 geteilt durch 1.5
    analogWrite(5, 63);// ehmalige hälfte 127
    Serial.println("|||DAS AUTO FÄHRT RECHTS|||");//Hinweis: Kurven werden gewollt nicht angepasst, da die werte auf diese kurven spezialiesiert wurden.
   
  }
  else if (rechts < 550) { //Logik Links Fahren Trigger wenn T1 niedrig T1 = Rechts
    analogWrite(3, 56);//112 durch 1.2
    analogWrite(5, 127);//255
    Serial.println("|||DAS AUTO FÄHRT LINKS|||");//Hinweis: Kurven werden gewollt nicht angepasst, da die werte auf diese kurven spezialiesiert wurden.
    
  }

  else { //Fehler
    Serial.println("Fehler mit der Linienfolge");//Sollte nicht passieren nur für tests !
  }

}
}
