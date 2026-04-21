# 03 — PIN-BELEGUNG

> Dokumentiere **jeden einzelnen Pin** der verwendet wird. Kein Pin darf fehlen.
> Schreibe `[BESTÄTIGT]` hinter korrekte Werte oder ändere sie.

---

## 3.1 Gesamt-Pinübersicht Arduino Uno

> Markiere jeden verwendeten Pin. Schreibe die Funktion daneben.

### Digitale Pins

| Pin | Verwendet? | Funktion | Modus | Bauteil |
|---|---|---|---|---|
| 0 (RX) | Nein | - | - | - |
| 1 (TX) | Nein | - | - | - |
| 2 | Nein | - | - | - |
| 3 (PWM) | Nein | - | - | - |
| 4 | Nein | - | - | - |
| 5 (PWM) | Nein | - | - | - |
| 6 (PWM) | Nein | - | - | - |
| 7 | Ja | NeoPixel Data Pin | OUTPUT | NeoPixel [BESTÄTIGT] |
| 8 | Ja | Servo PWM | OUTPUT | Servo [BESTÄTIGT] |
| 9 (PWM) | Ja | RFID RST | OUTPUT | RFID-RC522 [BESTÄTIGT] |
| 10 (PWM/SS) | Ja | RFID SDA/SS | OUTPUT | RFID-RC522 [BESTÄTIGT] |
| 11 (PWM/MOSI) | Ja | SPI MOSI | SPI | RFID-RC522 [BESTÄTIGT] |
| 12 (MISO) | Ja | SPI MISO | SPI | RFID-RC522 [BESTÄTIGT] |
| 13 (SCK/LED) | Ja | SPI SCK | SPI | RFID-RC522 [BESTÄTIGT] |

### Analoge Pins

| Pin | Verwendet? | Funktion | Modus | Bauteil |
|---|---|---|---|---|
| A0 | Ja | Taster Analog-Eingang | INPUT | 5x Taster [BESTÄTIGT] |
| A1 | Nein | - | - | - |
| A2 | Nein | - | - | - |
| A3 | Nein | - | - | - |
| A4 (SDA) | Ja | I2C SDA | I2C | LCD1602 [BESTÄTIGT] |
| A5 (SCL) | Ja | I2C SCL | I2C | LCD1602 [BESTÄTIGT] |

### Stromversorgung

| Pin | Verwendet? | Wofür? | Bauteil |
|---|---|---|---|
| 5V | Ja | Logik & Aktoren | Servo, LCD, NeoPixel |
| 3.3V | Ja | Logik | RFID-RC522 |
| GND | Ja | Gemeinsame Masse | Alle Bauteile |
| VIN | Nein | - | - |

---

## 3.2 RFID-RC522 Verdrahtung (Detail)

| RFID-Modul Pin | Arduino Pin | Kabelfarbe (falls bekannt) | Bestätigt? |
|---|---|---|---|
| SDA (SS) | 10 | _Farbe?_ | [BESTÄTIGT] |
| SCK | 13 | _Farbe?_ | [BESTÄTIGT] |
| MOSI | 11 | _Farbe?_ | [BESTÄTIGT] |
| MISO | 12 | _Farbe?_ | [BESTÄTIGT] |
| IRQ | _Nicht angeschlossen_ | — | _[BESTÄTIGT]_ |
| GND | GND | _Farbe?_ | [BESTÄTIGT] |
| RST | 9 | _Farbe?_ | [BESTÄTIGT] |
| 3.3V | 3.3V | _Farbe?_ | [BESTÄTIGT] |

> **WARNUNG:** Der RFID-RC522 arbeitet mit **3.3V**! Er darf **NICHT** an 5V angeschlossen werden!
> Ist der RFID an 3.3V angeschlossen? _Ja / Nein_

---

## 3.3 NeoPixel Verdrahtung (Detail)

| NeoPixel Pin | Arduino Pin | Kabelfarbe (falls bekannt) | Bestätigt? |
|---|---|---|---|
| Data In (DIN) | 7 | _Farbe?_ | [BESTÄTIGT] |
| VCC / 5V | 5V | _Farbe?_ | [BESTÄTIGT] |
| GND | GND | _Farbe?_ | [BESTÄTIGT] |

> Ist ein **Vorwiderstand** (z.B. 330 Ohm) zwischen Arduino-Pin und Data-In? _Ja (Wert?) / Nein_
> Ist ein **Kondensator** (z.B. 1000 µF) parallel zur Stromversorgung? _Ja (Wert?) / Nein_

---

## 3.4 Taster Verdrahtung (Detail)

| Verbindung | Von → Nach | Bestätigt? |
|---|---|---|
| Analogeingang | Widerstandsnetzwerk → _A0_ | _[BESTÄTIGT]_ |
| Stromversorgung | _5V_ → Widerstandskette | _[BESTÄTIGT]_ |
| Masse | Widerstandskette → _GND_ | _[BESTÄTIGT]_ |

> Zeichne oder beschreibe den Schaltplan des Widerstandsnetzwerks:
> 
> _Hier den Schaltplan beschreiben oder als Bild einfügen_
> _z.B.: 5V → R1 → Taster1 → R2 → Taster2 → ... → GND, Abgriff zwischen Rx und Tastery geht an A0_

---

## 3.5 Servo Verdrahtung (Detail)

| Servo-Kabel | Arduino Pin | Kabelfarbe | Bestätigt? |
|---|---|---|---|
| Signal (PWM) | _8_ | _z.B. Orange/Gelb_ | _[BESTÄTIGT]_ |
| VCC | _5V_ | _z.B. Rot_ | _[BESTÄTIGT]_ |
| GND | _GND_ | _z.B. Braun/Schwarz_ | _[BESTÄTIGT]_ |

> Wird der Servo direkt vom Arduino mit Strom versorgt? _Ja / Nein (externes Netzteil?)_

---

## 3.6 LCD I2C Verdrahtung (Detail)

| LCD Pin | Arduino Pin | Kabelfarbe (falls bekannt) | Bestätigt? |
|---|---|---|---|
| SDA | _A4_ | _Farbe?_ | _[BESTÄTIGT]_ |
| SCL | _A5_ | _Farbe?_ | _[BESTÄTIGT]_ |
| VCC | _5V_ | _Farbe?_ | _[BESTÄTIGT]_ |
| GND | _GND_ | _Farbe?_ | _[BESTÄTIGT]_ |

---

## 3.7 Pin-Konflikte

> Gibt es Pin-Konflikte? Prüfe ob zwei Bauteile denselben Pin verwenden:

| Möglicher Konflikt | Status |
|---|---|
| Pin 13 wird für SPI (SCK) UND die eingebaute LED verwendet | _Problem? Ja / Nein_ |
| Pin 10 wird für SPI (SS) UND evtl. für Servo (PWM) verwendet | _Problem? Ja / Nein_ |
| Weitere Konflikte? | _Beschreibe_ |

> Sind alle Pins **eindeutig** zugewiesen (kein Pin doppelt belegt)? _Ja / Nein_
