# 06 — LED-VERHALTEN (NeoPixel)

> Dokumentiere **jeden** LED-Zustand, jede Farbe, jede Animation und jedes Timing.

---

## 6.1 NeoPixel-Grundkonfiguration

| Feld | Wert |
|---|---|
| Anzahl LEDs | 3 [BESTÄTIGT] |
| Data-Pin | 7 [BESTÄTIGT] |
| NeoPixel-Typ im Code | NEO_GRB + NEO_KHZ800 [BESTÄTIGT] |
| Helligkeit (0-255) | 50 [BESTÄTIGT] |
| Wird `pixels.begin()` aufgerufen? | Ja (in startupTest) [BESTÄTIGT] |
| Wird `pixels.show()` nach jeder Änderung aufgerufen? | Ja [BESTÄTIGT] |

---

## 6.2 LED-Zuordnung

| NeoPixel-Index | Physische Position | Funktion | Standardfarbe | RGB-Wert |
|---|---|---|---|---|
| 0 | Erste | System Online | Grün | (0, 255, 0) [BESTÄTIGT] |
| 1 | Mitte | Betreten | Blau | (0, 0, 255) [BESTÄTIGT] |
| 2 | Letzte | Verlassen | Rot | (255, 0, 0) [BESTÄTIGT] |

> Stimmt die Reihenfolge der LEDs (Index 0, 1, 2) mit der physischen Anordnung überein? _Ja / Nein_

---

## 6.3 LED-Zustände pro Systemsituation

> Für **jede** Situation im Programm: Welche LEDs sollen an/aus sein?

| Nr. | Situation | LED 0 (Online) | LED 1 (Entry) | LED 2 (Exit) |
|---|---|---|---|---|
| 1 | System aus (vor Startup) | AUS | AUS | AUS |
| 2 | Startup: Alle LEDs Test | GRÜN | BLAU | ROT |
| 3 | Startup: Einzeltest LED 0 | GRÜN | AUS | AUS |
| 4 | Startup: Einzeltest LED 1 | AUS | BLAU | AUS |
| 5 | Startup: Einzeltest LED 2 | AUS | AUS | ROT |
| 6 | Startup: Nach Test | AUS | AUS | AUS |
| 7 | System OFFLINE (wartend) | AUS | AUS | AUS |
| 8 | System ONLINE (wartend) | GRÜN | AUS | AUS |
| 9 | Person betritt Raum (Schranke offen) | GRÜN | BLAU | AUS |
| 10 | Nach Betreten (Schranke zu) | GRÜN | AUS | AUS |
| 11 | Person verlässt Raum (Schranke offen) | GRÜN | AUS | ROT |
| 12 | Nach Verlassen (Schranke zu) | GRÜN | AUS | AUS |
| 13 | Fehler: Karte unbekannt | GRÜN bleibt | AUS | AUS |
| 14 | Fehler: Bereits im Raum | GRÜN bleibt | AUS | AUS |
| 15 | Fehler: Raum besetzt | GRÜN bleibt | AUS | AUS |
| 16 | Fehler: Nicht im Raum | GRÜN bleibt | AUS | AUS |
| 17 | Timeout | GRÜN bleibt | AUS | AUS |
| 18 | System Reset | AUS | AUS | AUS |

> Stimmen alle Zustände? _[BESTÄTIGT] oder Änderungen eintragen_

> **Frage:** Sollen bei Fehlern spezielle LED-Muster angezeigt werden?
> _z.B. Rot blinken bei Zugang verweigert? → Ja / Nein_

---

## 6.4 Startup-Animation (Detail)

> Beschreibe die **exakte** Reihenfolge der LED-Animation beim Systemstart:

| Schritt | LED 0 | LED 1 | LED 2 | Dauer (ms) | Bestätigt? |
|---|---|---|---|---|---|
| 1. Alle AN | GRÜN | BLAU | ROT | 600 ms | [BESTÄTIGT] |
| 2. Alle AUS | AUS | AUS | AUS | 200 ms | [BESTÄTIGT] |
| 3. Nur LED 0 | GRÜN | AUS | AUS | 250 ms | [BESTÄTIGT] |
| 4. Nur LED 1 | AUS | BLAU | AUS | 250 ms | [BESTÄTIGT] |
| 5. Nur LED 2 | AUS | AUS | ROT | 250 ms | [BESTÄTIGT] |
| 6. Alle AUS | AUS | AUS | AUS | 200 ms | [BESTÄTIGT] |

> Soll die Animation geändert werden? _Ja (wie?) / Nein_
> Soll die Animation schneller/langsamer sein? _Aktuelle Geschwindigkeit OK / Ändern auf ??? ms_

---

## 6.5 Helligkeit

| Frage | Antwort |
|---|---|
| Aktuelle Helligkeit | 50 (von 255) |
| Ist the Helligkeit ausreichend? | _Ja / Zu hell / Zu dunkel_ |
| Gewünschte Helligkeit | 50 [BESTÄTIGT] |
| Soll die Helligkeit je nach Situation variieren? | _Ja (wie?) / Nein_ |

---

## 6.6 Zusätzliche LED-Effekte (optional)

| Frage | Antwort |
|---|---|
| Sollen LEDs blinken können? | _Ja (wann?) / Nein_ |
| Sollen LEDs faden/pulsieren können? | _Ja (wann?) / Nein_ |
| Soll es einen "Alarm"-Modus geben? | _Ja (beschreibe) / Nein_ |
| Soll die Online-LED pulsieren statt dauerhaft leuchten? | _Ja / Nein_ |
| Weitere Effekte gewünscht? | _Beschreibe_ |
