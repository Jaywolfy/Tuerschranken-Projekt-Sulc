/******************************************************************************
 * Projektname:    Tuerschranke
 * Datei:          Source_Code.ino
 *
 * Autor:          Jason Thomas Wolf
 * Team:           Jason Thomas Wolf, Jaehun Chung, Semin Ju
 * Datum:          03.02.2026
 * Version:        1.0
 * Zuletzt geändert: 08.03.2026
 *
 * Beschreibung:
 * Der Programmcode beschreibt eine automatische Tuerschranke welche mit dem
 * ELEGOO-Set bedient wird. Man kommt mit einem RFID-Chip und man drueckt einer
 * der 5 Tasten. Taste 1 ist zum starten des Programms (System online). 
 * Taste 2 schaltet das System offline. Taste 3: Raum betreten. 
 * Taste 4: Raum verlassen. Taste 5: System zuruecksetzen/neustarten.
 * Nur eine Person gleichzeitig im Raum!
 *
 * LEDs (Adafruit NeoPixel an Pin 7):
 * - LED 1: System ist online (Gruen)
 * - LED 2: Jemand betritt den Raum (Blau)
 * - LED 3: Jemand verlaesst den Raum (Rot)
 *
 * Hardware:
 * - Board: Arduino Uno
 * - Board: Velleman
 * - Microcontroller: ATmega328P
 * - Taktfrequenz: 16 MHz
 *
 * Pin-Belegung:
 * - Pin 10: RFID_SS_PIN
 * - Pin  9: RFID_RST_PIN
 * - Pin 11: RFID MOSI
 * - Pin 12: RFID MISO
 * - Pin 13: RFID SCK
 * - Pin  8: Servo PWM
 * - Pin  2: Adafruit NeoPixel Data Pin
 * - Pin A0: Alle Taster, als Analogwerte eingelesen
 *
 * Angeschlossene Komponenten:
 * - [Bauteil 1]: 1x ELEGOO RFID-RC522 (2x RFID-Chipkarten)
 * - [Bauteil 2]: 1x ELEGOO LCD1602 I2C
 * - [Bauteil 3]: 3x Adafruit NeoPixel LED 
 * - [Bauteil 4]: 5x Taster ueber Widerstandsnetzwerk an A0
 * - [Bauteil 5]: 1x Servo Motor
 *
 * Bibliotheken:
 * - SPI.h
 * - MFRC522.h
 * - Servo.h
 * - LiquidCrystal_I2C.h
 * - Adafruit_NeoPixel.h
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
#include <Adafruit_NeoPixel.h>

// ============================================================
// PIN-DEFINITIONEN
// ============================================================

// RFID RC522 (SPI)
#define RFID_SS_PIN     10
#define RFID_RST_PIN     9 // (Falls nicht anders in Dokumentation)

// LEDs (NeoPixel)
#define LED_PIN          2   // Alle LEDs auf Pin 2 (NeoPixel Data Pin)
#define NUM_LEDS         3   // 3 LEDs

// Taster
#define BTN_ANALOG_PIN  A0   // Alle 5 Taster an A0

// Servo
#define SERVO_PIN        8   // Servo an Pin 8 (PWM-faehig)

// ============================================================
// SERVO-WINKEL
// ============================================================
#define SERVO_CLOSED     0   // Schranke geschlossen (Grad)
#define SERVO_OPEN      90   // Schranke offen (Grad)

// ============================================================
// RFID - REGISTRIERTE KARTEN
// ============================================================
const byte KARTE_1_UID[4] = {0xDE, 0xAD, 0xBE, 0xEF}; // Karten-UID ersetzen
const byte KARTE_2_UID[4] = {0x12, 0x34, 0x56, 0x78}; // Karten-UID ersetzen
const char* KARTE_1_NAME  = "Person 1";               
const char* KARTE_2_NAME  = "Person 2";               

#define ANZAHL_KARTEN    2

// ============================================================
// OBJEKTE
// ============================================================
MFRC522 rfid(RFID_SS_PIN, RFID_RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo schranke;

// NeoPixel Objekt (3 LEDs, Pin 7)
Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// ============================================================
// GLOBALE ZUSTANDSVARIABLEN
// ============================================================
bool systemOnline           = false;
bool inRaum[ANZAHL_KARTEN]  = {false, false};

// Entprellung fuer analoge Button-Erkennung
unsigned long tDebounce     = 0;
#define ENTPRELLZEIT        200   // Millisekunden

// ============================================================
// HILFSFUNKTIONEN ANALOGE TASTER
// ============================================================

/**
 * Liest den Analog-Wert auf A0 und bestimmt den gedrueckten Button.
 * Schwellenwerte muessen je nach verwendetem Widerstandsnetzwerk kalibriert werden!
 * 0: Start, 1: Stop, 2: Enter, 3: Leave, 4: Reset, -1: Keiner
 */
int readAnalogButton() {
  int val = analogRead(BTN_ANALOG_PIN);
  
  // BEISPIEL-Schwellenwerte (Thresholds):
  // Muss an die echten Widerstandswerte angepasst werden.
  if (val < 50) return 0;       // Taster 1 (Start)
  if (val < 200) return 1;      // Taster 2 (Stop)
  if (val < 400) return 2;      // Taster 3 (Enter)
  if (val < 600) return 3;      // Taster 4 (Leave)
  if (val < 800) return 4;      // Taster 5 (Reset)
  return -1; // Keiner gedrueckt (Wert nahe 1023)
}

/**
 * Entprellter Tastencheck ueber den analogen Pin.
 * btnIndex: 0=Start, 1=Stop, 2=Enter, 3=Leave, 4=Reset
 */
bool tasteGedrueckt(int btnIndex) {
  int actBtn = readAnalogButton();
  if (actBtn == btnIndex) {
    if (millis() - tDebounce > ENTPRELLZEIT) {
      tDebounce = millis();
      return true;
    }
  }
  return false;
}

// ============================================================
// HILFSFUNKTIONEN ALLGEMEIN
// ============================================================

bool uidGleich(const byte* uid, const byte* gespeichert, byte laenge) {
  for (byte i = 0; i < laenge; i++) {
    if (uid[i] != gespeichert[i]) return false;
  }
  return true;
}

int karteErkennen() {
  if (rfid.uid.size != 4) return -1;
  if (uidGleich(rfid.uid.uidByte, KARTE_1_UID, 4)) return 0;
  if (uidGleich(rfid.uid.uidByte, KARTE_2_UID, 4)) return 1;
  return -1;
}

const char* karteName(int index) {
  if (index == 0) return KARTE_1_NAME;
  if (index == 1) return KARTE_2_NAME;
  return "Unbekannt";
}

void lcdZeigen(const char* zeile1, const char* zeile2 = "") {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(zeile1);
  lcd.setCursor(0, 1);
  lcd.print(zeile2);
}

void schrankeAktion(int offenMs = 2000) {
  schranke.write(SERVO_OPEN);
  delay(offenMs);
  schranke.write(SERVO_CLOSED);
  delay(300);
}

/**
 * Steuert die 3 NeoPixel-LEDs ueber die Adafruit_NeoPixel Library
 */
void setzeLEDs(bool online, bool entry, bool exit) {
  pixels.clear();
  // LED_ONLINE (Gruen), LED_ENTRY (Blau), LED_EXIT (Rot)
  if (online) pixels.setPixelColor(0, pixels.Color(0, 255, 0)); 
  if (entry)  pixels.setPixelColor(1, pixels.Color(0, 0, 255)); 
  if (exit)   pixels.setPixelColor(2, pixels.Color(255, 0, 0)); 
  pixels.show();
}

void alleLEDsAus() {
  setzeLEDs(false, false, false);
}

void uidAusgeben() {
  Serial.print(F("Gescannte UID: "));
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) Serial.print(F("0"));
    Serial.print(rfid.uid.uidByte[i], HEX);
    if (i < rfid.uid.size - 1) Serial.print(F(" "));
  }
  Serial.println();
}

/**
 * Zaehlt wie viele Personen aktuell im Raum sind
 */
int anzahlPersonenImRaum() {
  int count = 0;
  for (int i = 0; i < ANZAHL_KARTEN; i++) {
    if (inRaum[i]) count++;
  }
  return count;
}

// ============================================================
// SYSTEMFUNKTIONEN
// ============================================================

void startupTest() {
  Serial.println(F("============================="));
  Serial.println(F("   TUERSCHRANKE - STARTUP    "));
  Serial.println(F("============================="));

  lcdZeigen("System wird", "gestartet...");

  // Alle LEDs initialisieren 
  pixels.begin();
  pixels.setBrightness(50); // Helligkeit ggf. anpassen
  pixels.show();

  // Alle LEDs ausgabe kurz testen (alle an)
  setzeLEDs(true, true, true);
  delay(600);
  alleLEDsAus();
  delay(200);

  // LEDs einzeln nacheinander durchlaufen
  setzeLEDs(true, false, false); delay(250);
  setzeLEDs(false, true, false); delay(250);
  setzeLEDs(false, false, true); delay(250);
  alleLEDsAus();
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

void systemStarten() {
  systemOnline = true;
  setzeLEDs(true, false, false); // LED 1 Online (Gruen)
  lcdZeigen("System Online", "Karte scannen...");
  Serial.println(F(">> System ist ONLINE."));
}

void systemStoppen() {
  systemOnline = false;
  alleLEDsAus();
  lcdZeigen("System Offline", "Taste 1: Start");
  Serial.println(F(">> System ist OFFLINE."));
}

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

  // Servo initialisieren und schliessen
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

  // --- Taster 5 (Reset) - immer verfuegbar ---
  if (tasteGedrueckt(4)) {
    systemReset();
    return;
  }

  // -------------------------------------------------------
  // OFFLINE-MODUS: Nur auf Taste 1 (Start) warten
  // -------------------------------------------------------
  if (!systemOnline) {
    if (tasteGedrueckt(0)) {
      systemStarten();
    }
    return;
  }

  // -------------------------------------------------------
  // ONLINE-MODUS
  // -------------------------------------------------------

  // Taster 2 (Stop): System offline schalten
  if (tasteGedrueckt(1)) {
    systemStoppen();
    return;
  }

  // RFID-Scan: Auf neue Karte warten
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Karte erkannt -> UID auf Serial ausgeben
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

    // Reset immer pruefen (auch waehrend Wartezeit)
    if (tasteGedrueckt(4)) {
      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();
      systemReset();
      return;
    }

    // Stop waehrend Wartezeit
    if (tasteGedrueckt(1)) {
      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();
      systemStoppen();
      return;
    }

    // --- Taste 3: Betreten (Index 2) ---
    if (tasteGedrueckt(2)) {
      aktionAusgefuehrt = true;

      if (inRaum[kartenIndex]) {
        // Logikfehler: bereits im Raum
        lcdZeigen("Fehler:", "Bereits im Raum!");
        Serial.print(name);
        Serial.println(F(" ist bereits im Raum!"));
        delay(2500);

      } else if (anzahlPersonenImRaum() >= 1) {
        // NEU: Logikfehler: Es darf nur eine Person im Raum sein!
        lcdZeigen("Raum besetzt!", "Max. 1 Person");
        Serial.println(F("FEHLER: Der Raum ist bereits von einer anderen Person besetzt! (Max: 1)"));
        delay(2500);

      } else {
        // Eintreten erlaubt
        inRaum[kartenIndex] = true;
        setzeLEDs(true, true, false); // Online & Entry
        lcdZeigen("Willkommen,", name);
        Serial.print(F("EINTRETEN: "));
        Serial.println(name);
        schrankeAktion(2000);
        setzeLEDs(true, false, false); // Nur noch Online an
      }
      break;
    }

    // --- Taste 4: Verlassen (Index 3) ---
    if (tasteGedrueckt(3)) {
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
        setzeLEDs(true, false, true); // Online & Exit
        lcdZeigen("Auf Wiedersehen", name);
        Serial.print(F("VERLASSEN: "));
        Serial.println(name);
        schrankeAktion(2000);
        setzeLEDs(true, false, false); // Wieder zurueck auf Online
      }
      break;
    }

  } // Ende while

  // Timeout: Keine Taste gedrueckt
  if (!aktionAusgefuehrt) {
    lcdZeigen("Timeout!", "Erneut scannen.");
    Serial.println(F("Timeout: Keine Taste gedrueckt."));
    delay(2000);
  }

  // Zurueck zur Hauptanzeige
  lcdZeigen("System Online", "Karte scannen...");

  // RFID-Kommunikation sauber beenden
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}