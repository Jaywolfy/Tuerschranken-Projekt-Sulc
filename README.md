# 🚪 Tuerschranken-Projekt-Sulc

[![Status](https://img.shields.io/badge/Status-In--Development-yellowgreen?style=for-the-badge)](https://github.com/Jaywolfy)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)
[![Hardware](https://img.shields.io/badge/Hardware-Arduino--Uno-blue?style=for-the-badge&logo=arduino)](https://www.arduino.cc/)

Ein intelligentes Türschranken-System basierend auf der Arduino-Plattform. Dieses Projekt ermöglicht eine automatisierte Zugangskontrolle mittels RFID-Identifikation und manueller Modus-Wahl über ein Tastenfeld. Ideal für die Verwaltung von Personenströmen in abgeschlossenen Räumen.

---

## 📖 Inhaltsverzeichnis
- [Über das Projekt](#-über-das-projekt)
- [Kernfunktionen](#-kernfunktionen)
- [Hardware-Komponenten](#-hardware-komponenten)
- [Funktionsweise](#-funktionsweise)
- [Pin-Belegung](#-pin-belegung)
- [Installation](#-installation)
- [Autor](#-autor)

---

## 🎯 Über das Projekt

Das **Tuerschranken-Projekt** ist ein Zugangskontrollsystem, das Sicherheit und Übersichtlichkeit kombiniert. Es nutzt RFID-Technologie, um Personen zu identifizieren, und ein 5-Tasten-Interface, um den gewünschten Vorgang (Eintreten/Verlassen) zu steuern. Ein Servo-Motor fungiert als physische Schranke, während ein LCD1602-Display und Status-LEDs dem Benutzer jederzeit Feedback geben.

### Warum dieses System?
- **Sicherheit:** Identifikation durch eindeutige RFID-IDs.
- **Logikprüfung:** Verhindert falsche Buchungen (z. B. den Raum zweimal betreten, ohne ihn zu verlassen).
- **Benutzerfreundlichkeit:** Sofortiges Feedback über Display und LEDs.
- **Transparenz:** Klarer Systemstatus (Online/Offline/Aktion).

---

## ✨ Kernfunktionen

- **RFID-Validierung:** Erkennt registrierte Chipkarten und gewährt nur autorisierten IDs Zutritt.
- **Status-Monitoring:**
    - `LED 1`: System ist online.
    - `LED 2`: Raum wird gerade betreten.
    - `LED 3`: Raum wird gerade verlassen.
- **LCD-Interface:** Zeigt Begrüßungen ("Willkommen...") und Systemanweisungen in Echtzeit an.
- **Manueller Override:** Start, Stopp und Reset über dedizierte Tasten.
- **Startup-Selbsttest:** Bei Systemstart werden alle Komponenten (Servo, LEDs, Display) automatisch geprüft.

---

## 🛠 Hardware-Komponenten

| Bauteil | Typ / Modell | Funktion |
| :--- | :--- | :--- |
| **Microcontroller** | Arduino Uno (ATmega328P) | Zentrale Steuereinheit |
| **RFID-Sensor** | ELEGOO RC522 | Einlesen der Zugangskarten |
| **Display** | LCD1602 (I2C/Standard) | Text-Ausgabe für Benutzer |
| **Aktuator** | Micro Servo Motor | Mechanische Schranke |
| **Indikatoren** | 3x LEDs (verschiedene Farben) | Visuelles Status-Feedback |
| **Eingabe** | 5x Drucktaster | Steuerung des Systemmodus |

---

## 🕹 Funktionsweise

Das System folgt einer klaren Logik, um Fehlbedienungen auszuschließen:

1. **Systemstart:** Alle LEDs leuchten kurz auf, die Schranke öffnet und schließt sich einmalig zur Kalibrierung. Das Display meldet "System wird gestartet...".
2. **Online-Modus:** Durch Drücken von **Taste 1** geht das System online. 
3. **Identifikation:** Die RFID-Karte wird an den Sensor gehalten.
4. **Modus-Wahl:**
    - **Taste 3 (Betreten):** Schranke öffnet sich, wenn die ID noch nicht "im Raum" ist.
    - **Taste 4 (Verlassen):** Schranke öffnet sich, wenn die ID zuvor "eingeloggt" war.
5. **Abschluss:** Nach dem Durchgang schließt sich die Schranke automatisch und der Status wird für die ID aktualisiert.
6. **Reset:** Mit **Taste 5** kann das System jederzeit neu gestartet werden.

---

## 📌 Pin-Belegung (Aktueller Stand)

> **Hinweis:** Einige Zuweisungen befinden sich noch in der Entwicklung.

| Komponente | Pin | Modus |
| :--- | :--- | :--- |
| **LED 1 (Online)** | Pin 13 | OUTPUT |
| **LED 2 (Entry)** | Pin 12 | OUTPUT |
| **LED 3 (Exit)** | Pin 11 | OUTPUT |
| **Taster 1 (Start)** | Pin 10 | INPUT_PULLUP |
| **Taster 2 (Stop)** | Pin 9 | INPUT_PULLUP |
| **Taster 3 (Enter)** | Pin 8 | INPUT_PULLUP |
| **Servo / RFID / LCD** | *TBD* | *In Bearbeitung* |

---

## 🚀 Installation

1. **Repository klonen:**
   ```bash
   git clone https://github.com/Jaywolfy/Tuerschranken-Projekt-Sulc.git
   ```
2. **Bibliotheken installieren:**
   Stelle sicher, dass folgende Libraries in deiner Arduino IDE installiert sind:
   - `MFRC522`
   - `Servo`
   - `LiquidCrystal` (bzw. `LiquidCrystal_I2C`)
3. **Hardware-Setup:** Verbinde die Komponenten gemäß der Pin-Belegung oben.
4. **Upload:** Öffne die `Main.ino` und lade sie auf deinen Arduino Uno hoch.

---

## 👤 Autor

**Jason Thomas Wolf**
- GitHub: [@Jaywolfy](https://github.com/Jaywolfy)
- LinkedIn: [Jason Wolf](https://www.linkedin.com/in/jason--wolf/)

---

## 📄 Lizenz

Dieses Projekt ist unter der **MIT Lizenz** lizenziert - siehe die [LICENSE](LICENSE) Datei für Details.

---
*Erstellt für das Schulprojekt bei Herrn Sulc | Stand: Februar 2026
Klasse: 12FOI1*
