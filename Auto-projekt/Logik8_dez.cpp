int regler = A0;
int drehdauer = 1;
int drehunglinks = 5;
int drehungrechts = 5;
int starter = 12;
int geradeaus_3;
int geradeaus_5;
int messung;
int an = 0;
void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(12, INPUT);
  //Heute gemacht Geschwindikeit Geradeaus Fahren kurven, 1 dez starter //heute gemacht 8 dez starter vollstänig start mit linienfolge
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

  for (int i = 0; i < drehdauer; i++)
  {
    int ubergabe_regler = analogRead(regler);

    geradeaus_3 = map(ubergabe_regler, 0, 1023, 0, 225);
    geradeaus_5 = map(ubergabe_regler, 0, 1023, 0, 255);
    Serial.println(geradeaus_3);
    Serial.println(geradeaus_5);
    analogWrite(3, geradeaus_3);
    analogWrite(5, geradeaus_5);
    delay(500);
  }



}
