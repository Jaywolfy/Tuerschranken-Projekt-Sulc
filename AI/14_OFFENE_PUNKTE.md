# 14 — OFFENE PUNKTE, TODOS & README

> Sammle hier **alles** was noch zu tun ist, bekannte Probleme, und geplante Änderungen.

---

## 14.1 Bekannte Probleme / Bugs

> Liste alle bekannten Probleme auf die du beobachtet hast:

---

## 14.3 Geplante Verbesserungen / Erweiterungen

> Gibt es Features die du noch einbauen willst?

| Nr. | Feature | Beschreibung | Priorität (Hoch/Mittel/Niedrig) | Deadline? |
|---|---|---|---|---|
| 1 | _z.B. Buzzer für akustisches Feedback_ | _Piepton bei Zugang verweigert_ | _Niedrig_ | |
| 2 | _z.B. Mehr Karten unterstützen_ | _Array erweitern_ | _Mittel_ | |
| 3 | _z.B. Zeitstempel im Serial Monitor_ | _millis() Ausgabe_ | _Niedrig_ | |
| 4 | _z.B. Mehrere Personen gleichzeitig_ | _Max-Personen-Anzahl konfigurierbar_ | | |
| 5 | | | | |

---

## 14.4 README.md Aktualisierung

> Die README.md enthält **veraltete** Informationen. Was muss aktualisiert werden?

### Pin-Belegung in der README

| In der README steht: | Richtig wäre: | Ändern? |
|---|---|---|
| LED 1 (Online) → Pin 13, OUTPUT | _z.B. NeoPixel Index 0 → Pin 7 (NeoPixel)_ | _Ja / Nein_ |
| LED 2 (Entry) → Pin 12, OUTPUT | _z.B. NeoPixel Index 1 → Pin 7 (NeoPixel)_ | _Ja / Nein_ |
| LED 3 (Exit) → Pin 11, OUTPUT | _z.B. NeoPixel Index 2 → Pin 7 (NeoPixel)_ | _Ja / Nein_ |
| Taster 1 (Start) → Pin 10, INPUT_PULLUP | _z.B. Analog A0_ | _Ja / Nein_ |
| Taster 2 (Stop) → Pin 9, INPUT_PULLUP | _z.B. Analog A0_ | _Ja / Nein_ |
| Taster 3 (Enter) → Pin 8, INPUT_PULLUP | _z.B. Analog A0_ | _Ja / Nein_ |
| Servo / RFID / LCD → *TBD* | _z.B. Servo=8, RFID=SPI, LCD=I2C_ | _Ja / Nein_ |

### Bibliotheken in der README

| In der README steht: | Fehlt: | Ändern? |
|---|---|---|
| MFRC522, Servo, LiquidCrystal (_I2C) | _Adafruit NeoPixel fehlt!_ | _Ja / Nein_ |

### Sonstige README-Änderungen

| Was soll geändert werden? | Beschreibung |
|---|---|
| _z.B. Hardware-Tabelle aktualisieren_ | _NeoPixel statt einzelne LEDs_ |
| _z.B. Funktionsweise aktualisieren_ | _"Nur 1 Person" erwähnen_ |
| _z.B. Status-Badge ändern_ | _Von "In-Development" auf ???_ |
| | |

---

## 14.5 DOKUMENTATION.md

| Frage | Antwort |
|---|---|
| Soll die DOKUMENTATION.md nach der Code-Prüfung gelöscht werden? | _Ja / Nein_ |
| Soll die DOKUMENTATION.md mit den neuen Spezifikationen aktualisiert werden? | _Ja / Nein_ |
| Soll die DOKUMENTATION.md als historische Referenz behalten werden? | _Ja / Nein_ |

---

## 14.6 Abgabe-Checkliste

> Für die finale Abgabe an den Lehrer / Schulprojekt:

- [ ] Code kompiliert fehlerfrei
- [ ] Code wurde auf den Arduino hochgeladen
- [ ] Alle Taster funktionieren
- [ ] RFID erkennt alle Karten
- [ ] LCD zeigt alle Nachrichten korrekt an
- [ ] Alle 3 LEDs leuchten in den richtigen Farben
- [ ] Servo öffnet und schließt korrekt
- [ ] Logik-Regeln funktionieren (nur 1 Person, kein doppelt betreten, etc.)
- [ ] Serial Monitor zeigt alle erwarteten Ausgaben
- [ ] README.md ist aktuell
- [ ] Code ist kommentiert und lesbar
- [ ] Karten-UIDs sind eingetragen (nicht mehr Platzhalter)
- [ ] Schwellenwerte sind kalibriert

---

## 14.7 Sonstige Anmerkungen

> Alles was sonst noch wichtig ist und in keine andere Datei passt:

_Hier schreiben..._
