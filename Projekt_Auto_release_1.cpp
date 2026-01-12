int angespasstegeschwindikeit; //Neu Geschwindikeit 
// T1 = A1; //Rechts (zum merken)
// T2 = A3;//Links
// regler = A0; //Regler Der Geschwindikeit
int starter = 12; //Digitaler Eingang des Starters
int geradeaus_3; // Map für Geraudaus von Motor 3
int geradeaus_5; //Map von Geradeaus von Motor 5
int messung;
int an = 0;
int ledlinienfolge = 7; //Led der Lineinfolge
int entfernung;

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
// Abstand messen
int irRohwert = analogRead(A2); // Erster Wert vom infrarot sensor wird gemessen
float voltage = irRohwert * (5.0 / 1023.0); //Offiziele formel für die spannung

if (voltage > 0.4) {  //Code für die Umrechnung von: https://arduinointro.com/articles/projects/comprehensive-guide-to-using-sharp-ir-infrared-distance-sensor-gp2y0a21yk0f-with-arduino
  entfernung = 27.86 / pow(voltage, 1.15);
} else {
  entfernung = 80;
}

// Begrenzung auf Messbereich (10-80 cm)
if (entfernung < 10) entfernung = 10;
if (entfernung > 80) entfernung = 80;



//Aktionen wegen dem Abstand
  // Logik LED
  if (entfernung < 10 && entfernung > 0) { // Rote LED als Warnung auf pin 6
    analogWrite(8, 255);//Rot
    analogWrite(9, 0);
    analogWrite(9, 0);
  }
  else if (entfernung < 20 && entfernung > 0) { // GELBE LED auf pin 9
    analogWrite(6, 0);
    analogWrite(9, 255);//Gelb
    analogWrite(9, 0);
  }
  else { // Grüne LED auf pin 10
    analogWrite(8, 0);
    analogWrite(9,0);
    analogWrite(10,255);//Grün
  }
 // Bumper-Logik: Stopp bei Abstand < 15 cm, 
  if (entfernung < 15 && entfernung > 0) {
    analogWrite(3, 0); // Beide Motoren stoppen
    analogWrite(5, 0);
    Serial.println("Ein Hindernis wurde Erkannt, Motoren Werden Gestoppt");
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
int startgeschwindikeit = analogRead(A0); // Orginal Max Geschwindikeit, am potenzometer eingesstellt

if (entfernung < 30 && entfernung > 0){ // änderung der Geschwindikeit
    angespasstegeschwindikeit = map(entfernung, 0, 30, 0, startgeschwindikeit);//Logik Für die Anpassung der Geschwindikeit
}
else{
    angespasstegeschwindikeit = startgeschwindikeit; // rückehr zur orginal ausgelsenen geschwinikeit
}

//Logik Entscheidung ob links oder Rechts Fahren und potenzomenter
if (links >= 550 && rechts >= 550) { //Logik Gerade aus Fahren

    
   
    Serial.println(" |||||DAS AUTO FÄHRT GERADEAUS||||");

    geradeaus_3 = map(angespasstegeschwindikeit, 0, 1023, 0, 112);
    geradeaus_5 = map(angespasstegeschwindikeit, 0, 1023, 0, 127);
    Serial.println(geradeaus_3);
    Serial.println(geradeaus_5);
    analogWrite(3, geradeaus_3);
    analogWrite(5, geradeaus_5);
    
  }
  else if (links < 550) { //Logik Rechts Fahren Trigger wenn T2 niedrig T2 = links
    analogWrite(3, 150);//Max 225 geteilt durch 1.5
    analogWrite(5, 84);// ehmalige hälfte 127
    Serial.println("|||DAS AUTO FÄHRT RECHTS|||");
   
  }
  else if (rechts < 550) { //Logik Links Fahren Trigger wenn T1 niedrig T1 = Rechts
    analogWrite(3, 74);//112 durch 1.2
    analogWrite(5, 170);//255
    Serial.println("|||DAS AUTO FÄHRT LINKS|||");
    
  }

  else { //Fehler
    Serial.println("Fehler mit der Linienfolge");
  }

}
}
