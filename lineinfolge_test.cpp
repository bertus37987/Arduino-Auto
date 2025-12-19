//Purer Code Linienfolge und geschwindikeitsanspassung
int T1 = A1; //Rechts
int T2 = A3;//Links
int ledlinienfolge = 7;
int geradeaus_3; // Map für Geraudaus von Motor 3
int geradeaus_5;
int regler = A0; //Regler Der Geschwindikeit


void setup() {
pinMode(3,OUTPUT);//5,3 Motoren
pinMode(5,OUTPUT);
pinMode(ledlinienfolge, OUTPUT); //Led linienfolge auf output
digitalWrite(ledlinienfolge, HIGH); //Led der linienfolge permanent an
Serial.begin(9600);//Serieler Monitor wird angeschaltet

}

void loop() {
int rechts = analogRead(T1); //Linienfolge Sensor Rechts wird gelesen
  Serial.print(rechts);
  Serial.print(" | Rechts ");
  Serial.println();
  
  
  int links = analogRead(T2);  //Linienfolge Sensor Links wird gelesen
  Serial.print(links);
  Serial.print(" | Links ");
  Serial.println();

//Logik Entscheidung ob links oder Rechts Fahren und potenzomenter

  if (links >= 550 && rechts >= 550) { //Logik Gerade aus Fahren

    int ubergabe_regler = analogRead(regler); //Geschwindikeits Regler
    Serial.println("ubergabe_regler");
    Serial.println(ubergabe_regler);
    Serial.println(" |||||DAS AUTO FÄHRT GERADEAUS||||");

    geradeaus_3 = map(ubergabe_regler, 0, 1023, 0, 112);
    geradeaus_5 = map(ubergabe_regler, 0, 1023, 0, 127);
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
