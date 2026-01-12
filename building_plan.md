Arduino Verdrahtungsplan - Aufbauanleitung
Analoge Pins (A0-A5)
Pin	Komponente	Beschreibung
A0	Potentiometer	Geschwindigkeitsregler
A1	Linienfolger-Sensor Rechts	T1 (TCRT5000 o.ä.)
A2	Sharp GP2Y0A21YK	IR-Distanzsensor
A3	Linienfolger-Sensor Links	T2 (TCRT5000 o.ä.)
Digitale Pins - Outputs (Aktoren)
Pin	Komponente	Beschreibung
Pin 3	Motor Rechts	Motor 3 (PWM-fähig)
Pin 5	Motor Links	Motor 5 (PWM-fähig)
Pin 7	LED Linienfolge	Status-LED (immer an)
Pin 8	Rote LED	Warnung: Hindernis <10 cm
Pin 9	Gelbe LED	Vorsicht: Hindernis <20 cm
Pin 10	Grüne LED	Freie Fahrt: >20 cm
Digitale Pins - Inputs (Sensoren/Taster)
Pin	Komponente	Beschreibung
Pin 12	Starter-Taster	Startknopf (digital)
Gesamtübersicht

text
ARDUINO UNO
┌─────────────────────┐
│                     │
│  A0 ← Potentiometer │ (Geschwindigkeitsregler)
│  A1 ← Sensor Rechts │ (Linienfolger)
│  A2 ← Sharp IR      │ (Distanzmessung)
│  A3 ← Sensor Links  │ (Linienfolger)
│                     │
│  D3 → Motor Rechts  │ (PWM)
│  D5 → Motor Links   │ (PWM)
│  D7 → LED Status    │
│  D8 → LED Rot       │
│  D9 → LED Gelb      │
│ D10 → LED Grün      │
│ D12 ← Taster Start  │
│                     │
└─────────────────────┘

Wichtige Hinweise für den Aufbau

⚠️ Motoren benötigen Motortreiber (z.B. L298N oder L293D)
⚠️ LEDs benötigen Vorwiderstände (220Ω empfohlen)
⚠️ Sharp IR-Sensor: VCC = 5V, GND = GND, OUT = A2
⚠️ Taster: Ein Pin an D12, anderer an GND (Pull-Down nötig)
