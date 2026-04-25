# Lasten- und Pflichtenheft: Türschranken-Projekt-Sulc

**Projekttitel:** intelligentes Türschranken-System
**Autor:** Jason Thomas Wolf (Team: Jason Thomas Wolf, Jaehun Chung, Semin Ju)
**Stand / Version:** 1.0 (Februar / März 2026)
**Dokumentart:** Kombiniertes Lasten- und Pflichtenheft

---

## 1. Einleitung und Zielsetzung
Dieses Dokument definiert die Anforderungen (Lastenheft) und die konkrete technische Umsetzung (Pflichtenheft) für das **Türschranken-Projekt-Sulc**. 
Das Ziel des Projekts ist die Entwicklung eines automatisierten Zugangskontrollsystems auf Basis eines Arduino Uno. Das System reguliert den physischen Zugang zu einem separierten Raum. Die Identifikation berechtigter Personen erfolgt über kontaktlose RFID-Chipkarten, während die Modus-Wahl und Steuerung über ein analoges Tastenfeld realisiert werden. Ein wesentliches Merkmal des Projekts ist die strikte Zugangsbeschränkung auf **maximal eine Person** gleichzeitig im Raum.

---

## TEIL A: LASTENHEFT (Anforderungen des Auftraggebers)

### 2. Ist-Zustand
Bisher gibt es keine automatische Zugangskontrolle zum betreffenden Raum. Berechtigungen müssen manuell geprüft werden, und es existiert keine systemgestützte Kapazitätsprüfung, die sicherstellt, dass sich maximal eine Person im Raum befindet. Visuelles Feedback über den Belegungsstatus fehlt.

### 3. Soll-Zustand (Grobkonzept)
Es soll ein mechatronisches Schrankensystem entwickelt werden, das folgende Kernaufgaben erfüllt:
*   **Identitätsprüfung:** Nur Inhaber registrierter RFID-Karten können das System bedienen.
*   **Zutrittssteuerung:** Eine mechanische Schranke öffnet sich nur bei gültiger Identifikation und plausibler Aktion (Betreten/Verlassen).
*   **Kapazitätslimit:** Das System muss zwingend blockieren, wenn eine zweite Person den Raum betreten möchte, während sich bereits jemand darin aufhält.
*   **Fehlerprävention (State Tracking):** Eine Person kann den Raum nicht zweimal betreten, ohne ihn vorher verlassen zu haben. Ebenso kann eine Person den Raum nicht verlassen, wenn sie nicht zuvor als "eingetreten" registriert wurde.
*   **Benutzerkommunikation:** Das System muss klare Handlungsanweisungen und Statusmeldungen in Echtzeit ausgeben.

### 4. Funktionale Anforderungen (FA)
*   **FA-10 (Systemstatusverwaltung):** Das System muss über Taster gezielt in einen "Online"-Modus (Betriebsbereitschaft) und "Offline"-Modus versetzt werden können.
*   **FA-20 (RFID-Validierung):** Validierung gescannter Karten gegen eine interne Liste berechtigter UIDs.
*   **FA-30 (Aktionsauswahl):** Nach erfolgreichem Scan muss der Nutzer über Tasten wählen können, ob er den Raum betreten oder verlassen möchte.
*   **FA-40 (Aktorik):** Steuerung eines Servo-Motors, der eine Schranke für einen definierten Zeitraum (ca. 2 Sekunden) um 90° öffnet und anschließend automatisch wieder schließt.
*   **FA-50 (Benutzerführung via Display):** Ein LCD-Display muss zur Kommunikation genutzt werden (Anzeige von Begrüßungen, Fehlermeldungen, Handlungsaufforderungen).
*   **FA-60 (Visuelles Signal):** Ein LED-System muss den Betriebsstatus (Online) sowie die aktuellen Aktionen (Eintreten/Verlassen) durch unterschiedliche Farben signalisieren.
*   **FA-70 (Hardware-Reset):** Jederzeitige Möglichkeit, das System physisch auf den Auslieferungszustand (Offline, Raum leer) zurückzusetzen.
*   **FA-80 (Selbsttest):** Bei Systemstart müssen mechanische (Schranke) und optische (LEDs) Bauteile automatisch auf Funktionalität kalibriert/getestet werden.

### 5. Nicht-funktionale Anforderungen (NFA)
*   **NFA-10 (Sicherheit):** Physischer Zugang ohne gültige RFID-Karte muss blockiert werden.
*   **NFA-20 (Usability):** Handlungsanweisungen (z. B. "Karte scannen", "3=Rein 4=Raus") müssen selbsterklärend sein.
*   **NFA-30 (Robustheit):** Das System muss über eine Entprellung (Debouncing) beim Tasten-Input verfügen, um unbeabsichtigte Doppelbuchungen zu vermeiden.
*   **NFA-40 (Timeouts):** Erfolgt nach einem RFID-Scan nach einer gewissen Zeit (10 Sekunden) keine Tasten-Eingabe, muss der Vorgang aus Sicherheitsgründen abgebrochen werden.

---

## TEIL B: PFLICHTENHEFT (Technische Umsetzung des Auftragnehmers)

### 6. Systemarchitektur & Hardware-Komponenten
Die Umsetzung der im Lastenheft definierten Anforderungen erfolgt auf der **Arduino-Plattform (ATmega328P)**. 
Folgende Hardware-Komponenten werden exakt spezifiziert:
1.  **Microcontroller:** Arduino Uno (Taktfrequenz: 16 MHz) – Velleman Board.
2.  **RFID-Reader:** ELEGOO RFID-RC522 (Kommunikation über SPI-Bus).
3.  **Anzeige:** ELEGOO LCD1602 mit I2C-Modul.
4.  **Aktor:** Micro Servo Motor (PWM-gesteuert).
5.  **Indikatoren:** 3x einzeln adressierbare Adafruit NeoPixel (WS2812B) LEDs.
6.  **Eingabeeinheit:** 5 Taster, die über ein Widerstandsnetzwerk an einem einzigen analogen Pin als Spannungsteiler eingelesen werden.

### 7. Spezifikation der Schnittstellen & Pin-Belegung
Die physische Pin-Belegung am Arduino Uno ist unveränderlich wie folgt definiert:

| Komponente | Anschluss / Pin | Protokoll / Typ |
| :--- | :--- | :--- |
| **RFID SDA (SS)** | Pin 10 | SPI |
| **RFID SCK** | Pin 13 | SPI |
| **RFID MOSI** | Pin 11 | SPI |
| **RFID MISO** | Pin 12 | SPI |
| **RFID RST** | Pin 9 | Digital Out |
| **Servo Motor** | Pin 8 | PWM |
| **NeoPixel (3x LEDs)** | Pin 2 | Digital Out (Adafruit NeoPixel) |
| **Taster-Netzwerk (5x)** | Pin A0 | Analog In |
| **LCD 1602** | I2C (SDA/SCL) | I2C (Adresse: 0x27) |

### 8. Umsetzung der Logik & Softwarearchitektur
Zur Umsetzung werden spezifische C/C++-Bibliotheken verwendet: `SPI.h`, `MFRC522.h` (RFID), `Servo.h` (Aktorik), `LiquidCrystal_I2C.h` (Display) und `Adafruit_NeoPixel.h` (LEDs).

#### 8.1. LED-Steuerung (NeoPixel)
Die LEDs sind in Serie geschaltet und werden über Pin 2 adressiert:
*   `LED 0 (Grün)`: Leuchtet dauerhaft, wenn das System **Online** ist.
*   `LED 1 (Blau)`: Leuchtet beim **Betreten** des Raumes.
*   `LED 2 (Rot)`: Leuchtet beim **Verlassen** des Raumes.

#### 8.2. Analoge Taster-Logik
Die 5 Taster teilen sich den Pin `A0`. Die Unterscheidung erfolgt über Spannungsschwellenwerte (Thresholds), die im `readAnalogButton()` ausgewertet werden. Zusätzliche Entprellzeiten (`ENTPRELLZEIT = 200 ms`) verhindern falsche Signale.
*   **Taste 1:** System Starten (Online-Modus aktivieren)
*   **Taste 2:** System Stoppen (Offline-Modus aktivieren)
*   **Taste 3:** Aktion: Raum betreten
*   **Taste 4:** Aktion: Raum verlassen
*   **Taste 5:** System Hardware-Reset (Reboot / Initialisierung)

#### 8.3. Kapazitäts- und Zustandskontrolle
Die Überwachung erfolgt über ein Boolean-Array `inRaum[ANZAHL_KARTEN]`.
1.  **Maximal allowed:** Die Funktion `anzahlPersonenImRaum()` prüft die Kapazität. Ist diese `>= 1`, blockiert das System weitere Eintritte.
2.  **Fehler "Bereits im Raum":** Versuch, Taste 3 zu drücken, obwohl das Array für die erkannte UID auf `true` steht.
3.  **Fehler "Nicht im Raum":** Versuch, Taste 4 zu drücken, obwohl das Array für die erkannte UID auf `false` steht.

#### 8.4. Schrankenmechanik (Servo)
Die mechanischen Zustände des Servos an Pin 8 sind präzise als Winkel definiert:
*   `SERVO_CLOSED` = 0° (Grundzustand)
*   `SERVO_OPEN` = 90° (Geöffnet für den Durchgang)
Die Öffnungsdauer (`offenMs`) ist standardmäßig auf 2000 Millisekunden parametrisiert.

### 9. Abnahmekriterien & Tests
Um das Projekt erfolgreich abzuschließen, müssen folgende Tests bestanden werden:
*   [ ] **Test 1:** Das System wechselt nur nach Drücken von *Taste 1* in den aktiven Betriebsmodus.
*   [ ] **Test 2:** Ein nicht registrierter RFID-Chip führt zur sofortigen Anzeige von "Zugang verweigert!".
*   [ ] **Test 3:** Das Betreten mit einem gültigen Chip lässt die Schranke öffnen, auf dem LCD erscheint die korrekte Begrüßung und die blaue NeoPixel-LED leuchtet auf.
*   [ ] **Test 4:** Eine zweite, gültige Person scannt ihren Chip während die erste Person im Raum ist. Das System MUSS das Betreten mit Hinweis "Raum besetzt! Max. 1 Person" blockieren.
*   [ ] **Test 5:** Die erste Person verlässt den Raum ordnungsgemäß (Taste 4). Die Schranke öffnet sich, die rote NeoPixel-LED leuchtet auf, und der Platz im Raum wird systemseitig wieder freigegeben.

### 10. Entwicklungs- und Betriebsumgebung
*   Entwicklungsumgebung: Arduino IDE.
*   Spannungsversorgung: 5V DC via USB oder externes Netzteil (empfohlen zur Absicherung der Spannungsspitzen des Servomotors).
