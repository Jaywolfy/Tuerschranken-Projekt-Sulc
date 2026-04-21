# 02 — HARDWARE-KOMPONENTEN

> Liste **jedes einzelne Bauteil** auf das du verwendest. Sei so genau wie möglich.
> Füge für jedes Bauteil den genauen Typ, Modell, Hersteller, und technische Daten an.

---

## 2.1 Hauptplatine / Board

| Feld | Wert |
|---|---|
| Board-Name | Arduino Uno |
| Board-Hersteller | ELEGOO |
| Microcontroller-Chip | ATmega328P |
| Taktfrequenz | 16 MHz |
| Betriebsspannung | 5V |
| Eingangsspannung (empfohlen) | Weiß ich nicht |
| Digitale I/O Pins (gesamt) | 14 |
| Analoge Input Pins (gesamt) | 6 |
| PWM-Pins | 3, 5, 6, 9, 10, 11 |
| Flash Speicher | 32 KB |
| SRAM | 2 KB |
| USB-Anschluss | USB-B auf USB-A |

---

## 2.2 Zusatzboard / Shield (falls vorhanden)

| Feld | Wert |
|---|---|
| Wird ein Shield/Zusatzboard verwendet? | _Ja / Nein_ |
| Name / Modell | _z.B. Velleman_ |
| Wozu dient es? | _z.B. Erweiterung der Pins, Breadboard-Ersatz_ |
| Beeinflusst es die Pin-Belegung? | _Ja (welche Pins?) / Nein_ |
| Sind Pins dadurch blockiert? | _Ja (welche?) / Nein_ |

---

## 2.3 RFID-Sensor

| Feld | Wert |
|---|---|
| Modell | _z.B. RFID-RC522_ |
| Hersteller / Set | _z.B. ELEGOO_ |
| Kommunikationsprotokoll | _z.B. SPI_ |
| Betriebsspannung | _z.B. 3.3V_ |
| Frequenz | _z.B. 13.56 MHz_ |
| Unterstützte Kartentypen | _z.B. MIFARE 1K, MIFARE Classic_ |
| UID-Länge der Karten | _z.B. 4 Bytes_ |
| Maximale Leseentfernung | _z.B. ca. 5 cm_ |
| Anzahl mitgelieferte Karten | _z.B. 2 (1x Chipkarte, 1x Schlüsselanhänger)_ |

---

## 2.4 RFID-Karten / Chips

| Nr. | Kartentyp | Form | Farbe/Markierung | Beschreibung |
|---|---|---|---|---|
| 1 | _z.B. MIFARE Classic 1K_ | _Chipkarte / Schlüsselanhänger_ | _z.B. weiß_ | _z.B. "Person 1"_ |
| 2 | _z.B. MIFARE Classic 1K_ | _Chipkarte / Schlüsselanhänger_ | _z.B. blau_ | _z.B. "Person 2"_ |
| _3?_ | | | | |

---

## 2.5 LCD-Display

| Feld | Wert |
|---|---|
| Modell | LCD1602 [BESTÄTIGT] |
| Kommunikation | I2C (mit Backpack) [BESTÄTIGT] |
| I2C-Backpack Chip | PCF8574 [BESTÄTIGT] |
| I2C-Adresse | 0x27 [BESTÄTIGT] |
| Spalten | 16 [BESTÄTIGT] |
| Zeilen | 2 [BESTÄTIGT] |
| Hintergrundbeleuchtung | _Ja / Nein — Welche Farbe?_ |
| Betriebsspannung | _z.B. 5V_ |
| Kontrast einstellbar? | _Ja (Potentiometer) / Nein_ |
| Kann Umlaute anzeigen? | _Ja / Nein_ |
| Kann Sonderzeichen anzeigen? | _Ja (welche?) / Nein_ |

---

## 2.6 LEDs (NeoPixel)

| Feld | Wert |
|---|---|
| LED-Typ | Adafruit NeoPixel [BESTÄTIGT] |
| Genauer Produktname | _z.B. NeoPixel Stick, NeoPixel Ring, einzelne WS2812B_ |
| Hersteller | _z.B. Adafruit / generischer WS2812B-Klon_ |
| Anzahl LEDs | 3 [BESTÄTIGT] |
| Bauform | _z.B. Einzelne LEDs / Stick mit 8 LEDs / Ring_ |
| LED-Chip | WS2812B [BESTÄTIGT] |
| Farbordnung | GRB [BESTÄTIGT] |
| Betriebsspannung | 5V [BESTÄTIGT] |
| Max. Strom pro LED | _z.B. 60 mA (bei voller Helligkeit weiß)_ |
| Sind die LEDs in Reihe geschaltet (Daisy Chain)? | _Ja / Nein_ |
| Kabelfarben (falls bekannt) | _z.B. Rot=VCC, Schwarz=GND, Grün=Data_ |

### LED-Zuordnung (physisch)

| LED-Position (auf dem NeoPixel-Streifen) | Index im Code | Funktion |
|---|---|---|
| Erste LED | 0 | _z.B. System Online_ |
| Zweite LED | 1 | _z.B. Betreten_ |
| Dritte LED | 2 | _z.B. Verlassen_ |

---

## 2.7 Taster

| Feld | Wert |
|---|---|
| Anzahl Taster gesamt | 5 [BESTÄTIGT] |
| Taster-Typ | _z.B. Kurzhubtaster / Taktschalter_ |
| Anschlussart | Alle über Widerstandsnetzwerk an einem Analog-Pin [BESTÄTIGT] |
| Pin | A0 [BESTÄTIGT] |
| Warum ein Analog-Pin? | _z.B. Nicht genug digitale Pins / Designentscheidung_ |

### Widerstandsnetzwerk

| Feld | Wert |
|---|---|
| Schaltungstyp | _z.B. Spannungsteiler-Kette / R-2R-Netzwerk_ |
| Referenzspannung | _z.B. 5V_ |

| Taster | Widerstandswert (Ohm) | Erwarteter Analogwert (0-1023) | Gemessen? |
|---|---|---|---|
| Taster 1 | _z.B. 0 Ohm (direkt an GND)_ | _z.B. 0_ | _Ja (Wert?) / Nein_ |
| Taster 2 | _z.B. 1 kOhm_ | _z.B. ~100_ | _Ja (Wert?) / Nein_ |
| Taster 3 | _z.B. 2.2 kOhm_ | _z.B. ~300_ | _Ja (Wert?) / Nein_ |
| Taster 4 | _z.B. 3.3 kOhm_ | _z.B. ~500_ | _Ja (Wert?) / Nein_ |
| Taster 5 | _z.B. 4.7 kOhm_ | _z.B. ~700_ | _Ja (Wert?) / Nein_ |
| Kein Taster | _Pull-Up z.B. 10 kOhm_ | _z.B. ~1023_ | _Ja (Wert?) / Nein_ |

> **WICHTIG:** Hast du die Analogwerte mit dem Serial Monitor ausgemessen? _Ja / Nein_
> Falls nein: Die Schwellenwerte im Code sind möglicherweise falsch!

---

## 2.8 Servo Motor

| Feld | Wert |
|---|---|
| Modell | _z.B. SG90 Micro Servo / MG996R_ |
| Hersteller | _z.B. Tower Pro / ELEGOO-Set_ |
| Typ | _z.B. Micro Servo / Standard Servo_ |
| Betriebsspannung | _z.B. 4.8V - 6V_ |
| Drehbereich | _z.B. 0° - 180°_ |
| Drehgeschwindigkeit | _z.B. 0.1s/60° bei 4.8V_ |
| Drehmoment | _z.B. 1.8 kg/cm_ |
| Signaltyp | _z.B. PWM_ |
| Kabelfarben | _z.B. Braun=GND, Rot=VCC, Orange=Signal_ |
| Stromversorgung | _z.B. Direkt vom Arduino / Externes Netzteil_ |

---

## 2.9 Stromversorgung

| Feld | Wert |
|---|---|
| Hauptstromquelle | _z.B. USB vom PC / Externes Netzteil / Batterie_ |
| Spannung | _z.B. 5V über USB_ |
| Reicht die USB-Stromversorgung für alle Komponenten? | _Ja / Nein / Unbekannt_ |
| Wird ein externer Spannungsregler verwendet? | _Ja (Modell?) / Nein_ |
| Wird der 3.3V-Pin des Arduino für den RFID verwendet? | _Ja / Nein_ |

---

## 2.10 Verkabelung / Verbindungen

| Feld | Wert |
|---|---|
| Breadboard verwendet? | _Ja / Nein_ |
| Breadboard-Typ | _z.B. Halbes Breadboard / Volles Breadboard_ |
| Kabeltyp | _z.B. Jumper Wires (M-M, M-F, F-F)_ |
| Gelötet? | _Ja (was?) / Nein_ |
| Gehäuse vorhanden? | _Ja (beschreibe) / Nein_ |

---

## 2.11 Sonstige Bauteile

> Gibt es noch weitere Bauteile die oben nicht aufgeführt sind?

| Bauteil | Typ | Funktion | Pin(s) |
|---|---|---|---|
| _z.B. Buzzer_ | _z.B. aktiver Piezo_ | _z.B. akustisches Feedback_ | _z.B. Pin 6_ |
| _z.B. Zusätzliche Widerstände_ | _z.B. 220 Ohm_ | _z.B. Vorwiderstände_ | |
| | | | |

> Falls keine weiteren Bauteile: Schreibe "Keine weiteren Bauteile."
