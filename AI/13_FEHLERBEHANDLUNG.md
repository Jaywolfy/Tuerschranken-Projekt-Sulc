# 13 — FEHLERBEHANDLUNG & EDGE CASES

> Dokumentiere **alle** möglichen Fehlersituationen und wie das System darauf reagieren soll.

---

## 13.1 Hardware-Fehler

> Was soll passieren wenn eine Hardware-Komponente ausfällt oder nicht funktioniert?

| Nr. | Fehlersituation | Wie erkennt man den Fehler? | Was soll das System tun? | Aktuell implementiert? | Bestätigt? |
|---|---|---|---|---|---|
| H1 | RFID-Sensor antwortet nicht | _z.B. PCD_Init schlägt fehl_ | _z.B. Fehlermeldung auf LCD + Serial_ | _Ja / Nein_ | _[BESTÄTIGT]_ |
| H2 | LCD reagiert nicht / falsche I2C-Adresse | _z.B. Kein Text sichtbar_ | _z.B. Nur Serial nutzen_ | _Ja / Nein_ | _[BESTÄTIGT]_ |
| H3 | Servo bewegt sich nicht | _z.B. Mechanische Blockade_ | _z.B. Timeout?_ | _Ja / Nein_ | _[BESTÄTIGT]_ |
| H4 | NeoPixel leuchtet nicht | _z.B. Kabel lose_ | _z.B. System läuft weiter ohne LED_ | _Ja / Nein_ | _[BESTÄTIGT]_ |
| H5 | Taster gibt falschen Wert | _z.B. Wackler im Kabel_ | _z.B. Entprellung filtert_ | _Ja / Nein_ | _[BESTÄTIGT]_ |
| H6 | Stromausfall / Brown-out | _z.B. Arduino startet neu_ | _z.B. System startet frisch (Status verloren)_ | _Ja_ | _[BESTÄTIGT]_ |

> Sollen Hardware-Fehler besser behandelt werden? _Ja (wie?) / Nein (aktueller Stand reicht)_

---

## 13.2 Software-Fehler / Logik-Fehler

| Nr. | Fehlersituation | Was soll passieren? | Aktuell implementiert? | Bestätigt? |
|---|---|---|---|---|
| SW1 | `karteErkennen()` gibt -1 zurück | Zugang verweigern, Meldung anzeigen | Ja | [BESTÄTIGT] |
| SW2 | Person versucht doppelt zu betreten | Fehler: "Bereits im Raum" | Ja | [BESTÄTIGT] |
| SW3 | Person versucht zu verlassen ohne drin zu sein | Fehler: "Nicht im Raum" | Ja | [BESTÄTIGT] |
| SW4 | Raum voll (1 Person max.) | Fehler: "Raum besetzt" | Ja | [BESTÄTIGT] |
| SW5 | Timeout nach Kartenscan (10s) | "Timeout" anzeigen | Ja | [BESTÄTIGT] |
| SW6 | `millis()` Overflow | Keine Probleme erwartet | Ja | [BESTÄTIGT] |

---

## 13.3 Benutzer-Fehler

| Nr. | Fehlersituation | Was soll passieren? | Bestätigt? |
|---|---|---|---|
| B1 | Falsche Karte | "Zugang verweigert" | [BESTÄTIGT] |
| B2 | Karte zu schnell weggenommen | Wird ignoriert | [BESTÄTIGT] |
| B3 | Falsche Taste gewählt | Logikprüfung zeigt Fehler | [BESTÄTIGT] |
| B4 | Keine Taste gewählt | Timeout nach 10s | [BESTÄTIGT] |
| B5 | Reset während Vorgang | Sofortiger System-Neustart | [BESTÄTIGT] |
| B6 | Mehrere Tasten gleichzeitig | Priorität im Code (if-Reihenfolge) | [BESTÄTIGT] |

---

## 13.4 Timing-Probleme

| Nr. | Problem | Wie wird es gelöst? | Bestätigt? |
|---|---|---|---|
| T1 | Taster prellen | Entprellung via millis() (200ms) | [BESTÄTIGT] |
| T2 | RFID liest Karte mehrfach | PICC_HaltA() nach Scan | [BESTÄTIGT] |
| T3 | Delay blockiert Tasterprüfung | Akzeptiertes Verhalten (Servo/Fehler) | [BESTÄTIGT] |
| T4 | Schranken-Bewegung | Delay wartet ab | [BESTÄTIGT] |

> Gibt es Timing-Probleme die du beobachtet hast? _Ja (beschreibe) / Nein_

---

## 13.5 Speicher-Probleme

| Nr. | Problem | Status | Bestätigt? |
|---|---|---|---|
| M1 | Flash-Speicher zu voll? | _z.B. Nein, genug Platz_ | _[BESTÄTIGT]_ |
| M2 | SRAM zu voll (String-Literale)? | _z.B. F() Macro wird verwendet_ | _[BESTÄTIGT]_ |
| M3 | Stack Overflow durch tiefe Rekursion? | _z.B. Keine Rekursion vorhanden_ | _[BESTÄTIGT]_ |
| M4 | Memory Leaks? | _z.B. Keine dynamische Allokation_ | _[BESTÄTIGT]_ |

---

## 13.6 Sicherheitsbedenken

| Nr. | Sicherheitsaspekt | Status | Maßnahme? | Bestätigt? |
|---|---|---|---|---|
| SEC1 | RFID-UIDs können geklont werden | _Bekannt / Nicht relevant für Schulprojekt?_ | _Keine Maßnahme_ | _[BESTÄTIGT]_ |
| SEC2 | Kein Passwortschutz | _Nur Karte nötig_ | _Akzeptabel?_ | _[BESTÄTIGT]_ |
| SEC3 | Status geht bei Stromausfall verloren | _Person "im Raum" wird vergessen_ | _Akzeptabel?_ | _[BESTÄTIGT]_ |
| SEC4 | Serial Monitor zeigt alle Daten | _UIDs, Namen lesbar_ | _Akzeptabel für Demo?_ | _[BESTÄTIGT]_ |

---

## 13.7 Robustheit

| Frage | Antwort |
|---|---|
| Wie lange kann das System ununterbrochen laufen? | _z.B. Stunden / Tage / unbegrenzt_ |
| Gibt es bekannte Abstürze? | _Ja (wann?) / Nein_ |
| Wurde das System über längere Zeit getestet? | _Ja (wie lange?) / Nein_ |
| Startet das System nach einem Stromausfall korrekt neu? | _Ja / Nein / Nicht getestet_ |
