int T1 = A1; //Rechts
int T2 = A3; //Links

void setup() {
pinMode(7,OUTPUT);
digitalWrite(7,HIGH);
}

void loop() {
int rechts = digitalRead(T1);
int links = digitalRead(T2);

if (rechts >= 600){
//Logik rechts fahren
}
else if (links >= 600){
//Logik links fahren
}
else if (links <= 600 && rechts <= 600){
//Logik gerade aus fahren
}
else {
serial.println("Fehler mit der Linienfolge");
}



}
