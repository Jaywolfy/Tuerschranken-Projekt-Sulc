/******************************************************************************
 * Projektname:    Tuerschranke
 * Datei:          Source_Code.ino
 *
 * Autor:          Jason Thomas Wolf
 * Datum:          03.02.2026
 * Version:        1.0
 * Zuletzt geändert: 03.03.2026
 *
 * Beschreibung:
 * Der Programmcode beschreibt eine automatische Tuerschranke welche mit dem
 * ELEGOO-Set bedient wird. Man kommt mit einem RFID-Chip und man drückt einer
 * der 5 Tasten. Taste 1 ist zum starten des Programms, so dass das System
 * online ist. Taste 2 ist um zum ausschalten des Programm, so dass das System
 * offline ist. Taste 3 ist um dem System zu sagen, dass wenn man die
 * RFID-Cipkarte an den Sensor hält, dass man den Raum betreten will. Taste 4
 * ist um den System zu sagen, dass wenn man die RFID-Chipkarte an den Sensor
 * hält, dass man den Raum verlassen will. Taste 5 ist um das System
 * zurückzusetzten das alles nochmal neustartet.
 *
 * Es beginnt so, man startet das System und man hält eine der 2 RFID-Chipkarten
 * vor den Sensor, die IDs sind fest in dem Programm Code geschrieben. Man
 * drückt einer der Tasten um dem System zu sagen, ob man rein oder raus möchte
 * und je nachdem was ausgewählt ist wird das Programm am Bildschirm eine
 * Nachricht sagen (z.b. Willkommen...). Man kann logischerweise nur einmal
 * einen raum betreten also wenn man zweimal die Taste 3 zum betreten drückt für
 * die selbe ID dann geht das nicht. Erst nach verlassen des Raums kann man
 * wieder betreten, genauso andersrum.
 *
 * Ebenfalls sind aber auch 3 LEDs angeschlossen welche den Status der Software
 * zeigen. Ob das System eingeschaltet ist, oder ob jemand den Raum verlässt
 * oder betritt. LED 1: System ist online LED 2: Jemand betritt den Raum LED 3:
 * Jemand verlässt den Raum
 *
 * Das System soll beim start der Software alle Komponenten einmal testen,
 * Schranke einmal öffnen und schließen, alle LED sollen einmal eingeschaltet
 * werden. Ebenfalls soll das Programm am Bildschirm eine Nachricht sagen (z.b.
 * System wird gestartet...).
 *
 * Hardware:
 * - Board: Arduino Uno
 * - Board: Velleman
 * - Microcontroller: ATmega328P
 * - Taktfrequenz: 16 MHz
 *
 * Pin-Belegung:
 * - Pin 13: OUTPUT (LED ? - Zuordnung unklar)
 * - Pin 12: OUTPUT (LED ? - Zuordnung unklar)
 * - Pin 11: OUTPUT (LED ? - Zuordnung unklar)
 * - Pin 10: INPUT_PULLUP (Taster ? - Zuordnung unklar)
 * - Pin 9:  INPUT_PULLUP (Taster ? - Zuordnung unklar)
 * - Pin 8:  INPUT_PULLUP (Taster ? - Zuordnung unklar)
 * - Noch offen: Pins für Taster 4 & 5, Servo, RFID, LCD1602
 *
 * Angeschlossene Komponenten:
 * - [Bauteil 1]: 1x ELEGOO RFID-RC522 (2x RFID-Chipkarten)
 * - [Bauteil 2]: 1x ELEGOO LCD1602
 * - [Bauteil 3]: 3x LED
 * - [Bauteil 4]: 5x Taster
 * - [Bauteil 5]: 1x Servo Motor
 *
 * Bibliotheken:
 * - SPI.h - (Für RFID Kommunikation)
 * - MFRC522.h - (Für den RFID-RC522 Sensor)
 * - Servo.h - (Für die Steuerung der Schranke/Servo)
 * - LiquidCrystal_I2C.h / LiquidCrystal.h - (Für das LCD Display - genaue
 * Variante noch offen)
 *
 * Inputs:
 * - RFID-RC522 Sensor: Liest die ID der Chipkarten ein
 * - Taster 1: Startet das Programm (System online)
 * - Taster 2: Schaltet das Programm aus (System offline)
 * - Taster 3: Modus "Raum betreten" aktivieren
 * - Taster 4: Modus "Raum verlassen" aktivieren
 * - Taster 5: System zurücksetzen (Neustart)
 *
 * Outputs:
 * - LCD1602 Display: Zeigt Statusnachrichten (z.B. "Willkommen...", "System
 * wird gestartet...")
 * - Servo Motor: Öffnet und schließt die Türschranke
 * - LED 1: Zeigt an, ob das System online ist
 * - LED 2: Zeigt an, dass jemand den Raum betritt
 * - LED 3: Zeigt an, dass jemand den Raum verlässt
 *
 * Serielle Kommunikation:
 * - Baudrate: 9600 (Standard für Debugging - falls benötigt)
 * - Format: Statusmeldungen und RFID-UID Ausgaben
 *
 * Funktionsweise:
 * 1. Systemstart: Komponenten-Test (Schranke auf/zu, alle LEDs an), LCD zeigt
 * "System wird gestartet...".
 * 2. Warten auf Taster 1, um das System "online" zu schalten.
 * 3. Einlesen der RFID-Chipkarte am Sensor.
 * 4. Eingabe über Taster 3 (Betreten) oder Taster 4 (Verlassen).
 * 5. Logikprüfung: Betreten nur möglich, wenn nicht bereits im Raum (und
 * umgekehrt).
 * 6. Aktion: Entsprechende Nachricht auf dem LCD, passende LED leuchtet, Servo
 * öffnet Schranke.
 * 7. Das System kann jederzeit mit Taster 5 zurückgesetzt/neugestartet werden.
 *
 * Bekannte Probleme/Bugs:
 * - [Noch keine bekannt]
 *
 * ToDo:
 * - [ ] Genaue Pin-Vergabe für alle Komponenten klären (Servo, LCD, RFID,
 * restliche Taster)
 * - [ ] LCD-Typ klären (I2C oder nicht)
 * - [ ] Hauptlogik implementieren
 *
 * Kontakt:
 * E-Mail: wolf-jason@outlook.com
 * GitHub: https://github.com/Jaywolfy
 *
 *****************************************************************************/

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

// ============================================================
// PIN-DEFINITIONEN
// ============================================================

// RFID RC522 (SPI)
#define RFID_SS_PIN    10
#define RFID_RST_PIN    9

// LEDs (neu zugewiesen - Konflikt mit SPI behoben)
#define LED_ONLINE      8   // LED 1: System Online  (grün)
#define LED_ENTRY       7   // LED 2: Betreten       (blau)
#define LED_EXIT        6   // LED 3: Verlassen      (rot)

// Taster (INPUT_PULLUP → LOW = gedrückt)
#define BTN_START       5   // Taster 1: System Online schalten
#define BTN_STOP        4   // Taster 2: System Offline schalten
#define BTN_ENTER       2   // Taster 3: Betreten-Modus
#define BTN_LEAVE      A0   // Taster 4: Verlassen-Modus
#define BTN_RESET      A1   // Taster 5: System-Reset

// Servo
#define SERVO_PIN       3   // PWM-fähiger Pin

// ============================================================
// SERVO-WINKEL
// ============================================================
#define SERVO_CLOSED    0   // Schranke geschlossen (Grad)
#define SERVO_OPEN     90   // Schranke offen (Grad) – ggf. anpassen

// ============================================================
// RFID – REGISTRIERTE KARTEN
// ============================================================
// *** WICHTIG: Eigene UIDs eintragen! ***
// Anleitung: Serial Monitor öffnen (9600 Baud), Karte scannen,
// die angezeigte UID (z.B. "DE AD BE EF") hier eintragen.

const byte KARTE_1_UID[4] = {0xDE, 0xAD, 0xBE, 0xEF}; // ← Karte 1 UID ersetzen!
const byte KARTE_2_UID[4] = {0x12, 0x34, 0x56, 0x78}; // ← Karte 2 UID ersetzen!
const char* KARTE_1_NAME  = "Person 1";                // ← Name anpassen
const char* KARTE_2_NAME  = "Person 2";                // ← Name anpassen

#define ANZAHL_KARTEN   2

// ============================================================
// OBJEKTE
// ============================================================
MFRC522          rfid(RFID_SS_PIN, RFID_RST_PIN);

// LCD I2C Adresse: 0x27 (Standard ohne Lötbrücken)
// Falls Display leer bleibt → 0x3F versuchen
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo schranke;

// ============================================================
// GLOBALE ZUSTANDSVARIABLEN
// ============================================================
bool systemOnline           = false;
bool inRaum[ANZAHL_KARTEN]  = {false, false};

// Entprellungs-Zeitstempel (ein Wert pro Taster)
unsigned long tDebounce[5]  = {0, 0, 0, 0, 0};
#define ENTPRELLZEIT         200   // Millisekunden

// ============================================================
// HILFSFUNKTIONEN
// ============================================================

/**
 * Vergleicht zwei UIDs (byteweise).
 * Gibt true zurück bei Übereinstimmung.
 */
bool uidGleich(const byte* uid, const byte* gespeichert, byte laenge) {
  for (byte i = 0; i < laenge; i++) {
    if (uid[i] != gespeichert[i]) return false;
  }
  return true;
}

/**
 * Erkennt die Karte anhand der UID.
 * Rückgabe: Kartenindex (0 oder 1), oder -1 wenn unbekannt.
 */
int karteErkennen() {
  if (rfid.uid.size != 4) return -1;
  if (uidGleich(rfid.uid.uidByte, KARTE_1_UID, 4)) return 0;
  if (uidGleich(rfid.uid.uidByte, KARTE_2_UID, 4)) return 1;
  return -1;
}

/**
 * Gibt den Namen einer Karte zurück.
 */
const char* karteName(int index) {
  if (index == 0) return KARTE_1_NAME;
  if (index == 1) return KARTE_2_NAME;
  return "Unbekannt";
}

/**
 * Zeigt eine zweizeilige Nachricht auf dem LCD an.
 * Zeile 2 ist optional (Standard: leer).
 */
void lcdZeigen(const char* zeile1, const char* zeile2 = "") {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(zeile1);
  lcd.setCursor(0, 1);
  lcd.print(zeile2);
}

/**
 * Öffnet die Schranke für eine definierte Zeit, schließt sie dann.
 */
void schrankeAktion(int offenMs = 2000) {
  schranke.write(SERVO_OPEN);
  delay(offenMs);
  schranke.write(SERVO_CLOSED);
  delay(300);
}

/**
 * Entprellter Tastencheck.
 * btnIndex: 0=Start, 1=Stop, 2=Enter, 3=Leave, 4=Reset
 * Rückgabe: true wenn Taste frisch gedrückt (und entprellt).
 */
bool tasteGedrueckt(int pin, int btnIndex) {
  if (digitalRead(pin) == LOW) {
    if (millis() - tDebounce[btnIndex] > ENTPRELLZEIT) {
      tDebounce[btnIndex] = millis();
      return true;
    }
  }
  return false;
}

/**
 * Schaltet alle drei Status-LEDs aus.
 */
void alleLEDsAus() {
  digitalWrite(LED_ONLINE, LOW);
  digitalWrite(LED_ENTRY,  LOW);
  digitalWrite(LED_EXIT,   LOW);
}

/**
 * Gibt die UID der gescannten Karte auf dem Serial Monitor aus.
 * Nützlich zum Auslesen neuer Karten-UIDs.
 */
void uidAusgeben() {
  Serial.print(F("Gescannte UID: "));
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) Serial.print(F("0"));
    Serial.print(rfid.uid.uidByte[i], HEX);
    if (i < rfid.uid.size - 1) Serial.print(F(" "));
  }
  Serial.println();
}

// ============================================================
// SYSTEMFUNKTIONEN
// ============================================================

/**
 * Startup-Selbsttest:
 * - LCD zeigt Startmeldung
 * - Alle LEDs blinken einmal auf
 * - LEDs laufen einzeln durch
 * - Schranke öffnet und schließt einmal zur Kalibrierung
 * - System wartet auf Taste 1
 */
void startupTest() {
  Serial.println(F("============================="));
  Serial.println(F("   TUERSCHRANKE - STARTUP    "));
  Serial.println(F("============================="));

  lcdZeigen("System wird", "gestartet...");

  // Alle LEDs gleichzeitig an
  digitalWrite(LED_ONLINE, HIGH);
  digitalWrite(LED_ENTRY,  HIGH);
  digitalWrite(LED_EXIT,   HIGH);
  delay(600);
  alleLEDsAus();
  delay(200);

  // LEDs einzeln nacheinander (8 → 7 → 6)
  for (int led = LED_ONLINE; led >= LED_EXIT; led--) {
    digitalWrite(led, HIGH);
    delay(250);
    digitalWrite(led, LOW);
  }
  delay(200);

  // Servo-Kalibrierung
  lcdZeigen("Schranken-Test", "laeuft...");
  Serial.println(F("Servo-Kalibrierung..."));
  schrankeAktion(800);

  // RFID-Test-Meldung
  Serial.println(F("RFID-Reader initialisiert."));
  Serial.println(F("Tipp: Karte scannen zum Auslesen der UID."));
  lcdZeigen("Bereit!", "Taste 1: Start");
  Serial.println(F("Warte auf Taste 1 (Start)..."));
}

/**
 * Schaltet das System in den Online-Modus.
 */
void systemStarten() {
  systemOnline = true;
  digitalWrite(LED_ONLINE, HIGH);
  lcdZeigen("System Online", "Karte scannen...");
  Serial.println(F(">> System ist ONLINE."));
}

/**
 * Schaltet das System in den Offline-Modus.
 */
void systemStoppen() {
  systemOnline = false;
  alleLEDsAus();
  lcdZeigen("System Offline", "Taste 1: Start");
  Serial.println(F(">> System ist OFFLINE."));
}

/**
 * Vollständiger System-Reset:
 * Alle Zustände werden zurückgesetzt, Startup-Test wird erneut ausgeführt.
 */
void systemReset() {
  Serial.println(F(">> SYSTEM RESET <<"));
  systemOnline = false;
  for (int i = 0; i < ANZAHL_KARTEN; i++) inRaum[i] = false;
  alleLEDsAus();
  schranke.write(SERVO_CLOSED);
  delay(300);
  startupTest();
}

// ============================================================
// SETUP
// ============================================================
void setup() {
  Serial.begin(9600);

  // Pin-Modi setzen
  pinMode(LED_ONLINE, OUTPUT);
  pinMode(LED_ENTRY,  OUTPUT);
  pinMode(LED_EXIT,   OUTPUT);
  pinMode(BTN_START,  INPUT_PULLUP);
  pinMode(BTN_STOP,   INPUT_PULLUP);
  pinMode(BTN_ENTER,  INPUT_PULLUP);
  pinMode(BTN_LEAVE,  INPUT_PULLUP);
  pinMode(BTN_RESET,  INPUT_PULLUP);

  // Servo initialisieren und schließen
  schranke.attach(SERVO_PIN);
  schranke.write(SERVO_CLOSED);

  // LCD initialisieren
  lcd.init();
  lcd.backlight();

  // SPI und RFID initialisieren
  SPI.begin();
  rfid.PCD_Init();
  delay(50);

  // Startup-Selbsttest
  startupTest();
}

// ============================================================
// HAUPTSCHLEIFE
// ============================================================
void loop() {

  // --- Taster 5 (Reset) – immer verfügbar ---
  if (tasteGedrueckt(BTN_RESET, 4)) {
    systemReset();
    return;
  }

  // -------------------------------------------------------
  // OFFLINE-MODUS: Nur auf Taste 1 (Start) warten
  // -------------------------------------------------------
  if (!systemOnline) {
    if (tasteGedrueckt(BTN_START, 0)) {
      systemStarten();
    }
    return;
  }

  // -------------------------------------------------------
  // ONLINE-MODUS
  // -------------------------------------------------------

  // Taster 2 (Stop): System offline schalten
  if (tasteGedrueckt(BTN_STOP, 1)) {
    systemStoppen();
    return;
  }

  // RFID-Scan: Auf neue Karte warten
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Karte erkannt → UID auf Serial ausgeben
  uidAusgeben();

  int kartenIndex = karteErkennen();

  // Unbekannte Karte
  if (kartenIndex == -1) {
    lcdZeigen("Zugang", "verweigert!");
    Serial.println(F("FEHLER: Karte nicht registriert."));
    delay(2000);
    lcdZeigen("System Online", "Karte scannen...");
    rfid.PICC_HaltA();
    return;
  }

  // Bekannte Karte: Anzeige + Aktionswahl
  const char* name = karteName(kartenIndex);
  Serial.print(F("Erkannte Person: "));
  Serial.println(name);
  lcdZeigen(name, "3=Rein  4=Raus");

  // -------------------------------------------------------
  // Auf Taste 3 (Betreten) oder Taste 4 (Verlassen) warten
  // Timeout: 10 Sekunden
  // -------------------------------------------------------
  unsigned long warteStart  = millis();
  bool aktionAusgefuehrt    = false;

  while (millis() - warteStart < 10000UL) {

    // Reset immer prüfen (auch während Wartezeit)
    if (tasteGedrueckt(BTN_RESET, 4)) {
      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();
      systemReset();
      return;
    }

    // Stop während Wartezeit
    if (tasteGedrueckt(BTN_STOP, 1)) {
      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();
      systemStoppen();
      return;
    }

    // --- Taste 3: Betreten ---
    if (tasteGedrueckt(BTN_ENTER, 2)) {
      aktionAusgefuehrt = true;

      if (inRaum[kartenIndex]) {
        // Logikfehler: bereits im Raum
        lcdZeigen("Fehler:", "Bereits im Raum!");
        Serial.print(name);
        Serial.println(F(" ist bereits im Raum!"));
        delay(2500);

      } else {
        // Eintreten erlaubt
        inRaum[kartenIndex] = true;
        digitalWrite(LED_ENTRY, HIGH);
        lcdZeigen("Willkommen,", name);
        Serial.print(F("EINTRETEN: "));
        Serial.println(name);
        schrankeAktion(2000);
        digitalWrite(LED_ENTRY, LOW);
      }
      break;
    }

    // --- Taste 4: Verlassen ---
    if (tasteGedrueckt(BTN_LEAVE, 3)) {
      aktionAusgefuehrt = true;

      if (!inRaum[kartenIndex]) {
        // Logikfehler: nicht im Raum
        lcdZeigen("Fehler:", "Nicht im Raum!");
        Serial.print(name);
        Serial.println(F(" ist nicht im Raum!"));
        delay(2500);

      } else {
        // Verlassen erlaubt
        inRaum[kartenIndex] = false;
        digitalWrite(LED_EXIT, HIGH);
        lcdZeigen("Auf Wiedersehen", name);
        Serial.print(F("VERLASSEN: "));
        Serial.println(name);
        schrankeAktion(2000);
        digitalWrite(LED_EXIT, LOW);
      }
      break;
    }

  } // Ende while

  // Timeout: Keine Taste gedrückt
  if (!aktionAusgefuehrt) {
    lcdZeigen("Timeout!", "Erneut scannen.");
    Serial.println(F("Timeout: Keine Taste gedrückt."));
    delay(2000);
  }

  // Zurück zur Hauptanzeige
  lcdZeigen("System Online", "Karte scannen...");

  // RFID-Kommunikation sauber beenden
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}