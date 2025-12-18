int startgeschwindikeit = analogRead(regler); // Orginal Max Geschwindikeit 

if (entfernung < 30 && entfernung > 0){ // änderung der Geschwindikeit
    angespasstegeschwindikeit = map(entfernung, 0, 30, 0, startgeschwindikeit) //Logik Für die Anpassung der Geschwindikeit
}
else{
    angepasstegeschwindikeit = startgeschwindikeit; // Kann zur orginal poti einstellung zurück
}
}
