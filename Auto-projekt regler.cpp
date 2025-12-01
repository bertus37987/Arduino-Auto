int regler = A0;
int drehdauer = 100;
int drehunglinks = 5;
int drehungrechts = 5;

int geradeaus_3;
int geradeaus_5;
void setup() {
Serial.begin(9600);
pinMode(3,OUTPUT);
pinMode(5,OUTPUT);  
}

void loop() {


for(int i = 0; i < drehdauer; i++)
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

