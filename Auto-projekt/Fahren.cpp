//Auto Fahr Mechanik
int drehdauer = 5;


void setup() {

pinMode(3,OUTPUT);
pinMode(5,OUTPUT);

}

void loop() {
for(int i = 0; i < drehdauer; i++)
{
analogWrite(3, 255);
analogWrite(5, 255);
delay(1500);
analogWrite(3,127);
analogWrite(5,127);
delay(1500);
analogWrite(5, 0);
analogWrite(5, 0);
delay(1500);
  
}

