//Auto Fahr Mechanik
int drehdauer = 1000000;
int drehunglinks = 5;
int drehungrechts = 5;
int anhalten;

void setup() {

pinMode(3,OUTPUT);
pinMode(5,OUTPUT);

}

void loop() {
for(int i = 0; i < drehdauer; i++)
{
analogWrite(3, 210);
analogWrite(5, 255);
delay(500);

  
}
for(int i = 0; i < drehunglinks; i++)
{
  analogWrite(3,255);
  analogWrite(5,127);
  delay(500);
}
for(int i = 0; i < drehungrechts; i++)
{
  analogWrite(3,127);
  analogWrite(5,255);
  delay(500);
}

}
