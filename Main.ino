/******************************************************************************
 * Projektname:    Tuerschranke
 * Datei:          Source_Code.ino
 *
 * Autor:          Jason Thomas Wolf
 * Datum:          03.02.2026
 * Version:        1.0
 * Zuletzt geändert: 24.02.2026
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

void setup() {
  // Pin belegung für die LEDs
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  // Pin belegung für die Taster
  pinMode(10, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
}
