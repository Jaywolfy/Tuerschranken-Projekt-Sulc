# 12 — BIBLIOTHEKEN & SOFTWARE

> Dokumentiere **jede** verwendete Bibliothek und Software-Konfiguration.

---

## 12.1 Arduino IDE / Entwicklungsumgebung

| Feld | Wert |
|---|---|
| IDE | _z.B. Arduino IDE / Arduino IDE 2.x / PlatformIO / VS Code_ |
| IDE-Version | _z.B. 2.3.2_ |
| Board-Paket | _z.B. Arduino AVR Boards_ |
| Board-Paket Version | _z.B. 1.8.6_ |
| Ausgewähltes Board | _z.B. Arduino Uno_ |
| Ausgewählter Port | _z.B. COM3 / COM4_ |
| Compiler-Warnungen aktiv? | _Ja (Stufe?) / Nein_ |

---

## 12.2 Verwendete Bibliotheken

### SPI.h

| Feld | Wert |
|---|---|
| Bibliothek | `SPI.h` |
| Typ | _Standard Arduino Library (vorinstalliert)_ |
| Version | _Standardversion (keine separate Installation nötig)_ |
| Wofür verwendet? | _SPI-Kommunikation mit RFID-RC522_ |
| Muss manuell installiert werden? | _Nein_ |
| Bestätigt? | _[BESTÄTIGT]_ |

### MFRC522.h

| Feld | Wert |
|---|---|
| Bibliothek | `MFRC522.h` |
| Installationsname | _z.B. "MFRC522" von GithubCommunity_ |
| Version | _z.B. 1.4.10 — Welche Version genau?_ |
| Installiert über | _z.B. Arduino Library Manager / manuell_ |
| Wofür verwendet? | _Ansteuerung des RFID-RC522 Sensors_ |
| GitHub-Link | _z.B. https://github.com/miguelbalboa/rfid_ |
| Bestätigt? | _[BESTÄTIGT]_ |

### Servo.h

| Feld | Wert |
|---|---|
| Bibliothek | `Servo.h` |
| Typ | _Standard Arduino Library (vorinstalliert)_ |
| Version | _Standardversion_ |
| Wofür verwendet? | _Ansteuerung des Servo-Motors_ |
| Muss manuell installiert werden? | _Nein_ |
| Bestätigt? | _[BESTÄTIGT]_ |

### LiquidCrystal_I2C.h

| Feld | Wert |
|---|---|
| Bibliothek | `LiquidCrystal_I2C.h` |
| Installationsname | _z.B. "LiquidCrystal I2C" von Frank de Brabander_ |
| Version | _z.B. 1.1.2 — Welche Version genau?_ |
| Installiert über | _z.B. Arduino Library Manager / manuell_ |
| Wofür verwendet? | _Ansteuerung des LCD1602 über I2C_ |
| Bestätigt? | _[BESTÄTIGT]_ |

| Bibliothek | Version (falls bekannt) | Bestätigt? |
|---|---|---|
| SPI.h | (Standard Arduino) | [BESTÄTIGT] |
| MFRC522.h | - | [BESTÄTIGT] |
| Servo.h | (Standard Arduino) | [BESTÄTIGT] |
| LiquidCrystal_I2C.h | - | [BESTÄTIGT] |
| Adafruit_NeoPixel.h | - | [BESTÄTIGT] |

---

## 12.3 Weitere Bibliotheken?

| Frage | Antwort |
|---|---|
| Werden weitere Bibliotheken verwendet? | Nein [BESTÄTIGT] |
| Sollen Bibliotheken hinzugefügt werden? | _Ja (welche?) / Nein_ |
| Gibt es Bibliotheks-Konflikte? | _Ja (welche?) / Nein / Unbekannt_ |

---

## 12.4 Kompilierung

| Frage | Antwort |
|---|---|
| Kompiliert der Code fehlerfrei? | _Ja / Nein (Fehlermeldung?)_ |
| Gibt es Compiler-Warnungen? | _Ja (welche?) / Nein_ |
| Sketch-Größe (Bytes) | _z.B. ca. 15000 von 32256_ |
| Globale Variablen (Bytes) | _z.B. ca. 800 von 2048_ |
| Ist genug Speicher übrig? | _Ja / Nein (knapp?)_ |

---

## 12.5 Upload

| Frage | Antwort |
|---|---|
| Lässt sich der Code erfolgreich hochladen? | _Ja / Nein (Fehlermeldung?)_ |
| Upload-Fehler aufgetreten? | _Ja (beschreibe) / Nein_ |
| Muss der Serial Monitor vor dem Upload geschlossen werden? | _Ja / Nein_ |
