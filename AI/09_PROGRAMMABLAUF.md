# 09 — PROGRAMMABLAUF

> Beschreibe den **kompletten** Programmablauf. Jeder einzelne Schritt, jede Bedingung, jeder Übergang.
> Beschreibe den **kompletten** Programmablauf. Jeder einzelne Schritt, jeder Bedingung, jeder Übergang.
> Das ist die wichtigste Datei für die Code-Prüfung!

---

## 9.1 Systemzustände (State Machine)

> Das Programm hat verschiedene Zustände. Liste hier **alle** Zustände auf:

| Nr. | Zustand | Beschreibung | Wie kommt man hierher? | Was passiert hier? |
|---|---|---|---|---|
| 1 | STARTUP | System wird initialisiert | Einschalten / Reset | Selbsttest, dann warten auf Taste 1 [BESTÄTIGT] |
| 2 | OFFLINE | System wartet auf Start | Nach Startup / Stopp | Warten auf Taste 1 oder Taste 5 [BESTÄTIGT] |
| 3 | ONLINE_WARTEND | System bereit für Karten | Nach Start / Aktion | RFID scannen, Taste 2, Taste 5 [BESTÄTIGT] |
| 4 | KARTE_ERKANNT | Person identifiziert | Bekannte Karte gescannt | Warte auf Taste 3/4 [BESTÄTIGT] |
| 5 | BETRETEN | Schranke für Eintritt offen | Taste 3 nach Karte | Servo auf, Delay, Servo zu [BESTÄTIGT] |
| 6 | VERLASSEN | Schranke für Austritt offen | Taste 4 nach Karte | Servo auf, Delay, Servo zu [BESTÄTIGT] |

> Stimmen diese Zustände? _[BESTÄTIGT] oder Änderungen eintragen_
> Fehlen Zustände? _Ja (welche?) / Nein_

---

## 9.2 Setup-Funktion (`setup()`)

> Was passiert **exakt** beim Hochfahren des Arduino?

| Schritt | Code-Aktion | Beschreibung | Reihenfolge korrekt? |
|---|---|---|---|
| 1 | `Serial.begin(9600)` | Serial Monitor starten | [BESTÄTIGT] |
| 2 | `schranke.attach(SERVO_PIN)` | Servo an Pin 8 | [BESTÄTIGT] |
| 3 | `schranke.write(SERVO_CLOSED)` | Schranke schließen | [BESTÄTIGT] |
| 4 | `lcd.init()` | LCD initialisieren | [BESTÄTIGT] |
| 5 | `lcd.backlight()` | Licht an | [BESTÄTIGT] |
| 6 | `SPI.begin()` | SPI-Bus für RFID | [BESTÄTIGT] |
| 7 | `rfid.PCD_Init()` | RFID-Reader starten | [BESTÄTIGT] |
| 8 | `delay(50)` | Kurze Pause | [BESTÄTIGT] |
| 9 | `startupTest()` | Selbsttest-Funktion | [BESTÄTIGT] |

> Fehlen Schritte? _Ja (welche?) / Nein_
> Ist die Reihenfolge korrekt? _Ja / Nein (richtige Reihenfolge?)_

---

## 9.3 Startup-Test (`startupTest()`)

> Was passiert **exakt** im Startup-Selbsttest?

| Schritt | Aktion | Detail | Timing | Bestätigt? |
|---|---|---|---|---|
| 1 | Serial Banner | Projektname & Startup | — | [BESTÄTIGT] |
| 2 | LCD Start | "System wird gestartet" | — | [BESTÄTIGT] |
| 3 | LED Init | pixels.begin() & brightness | — | [BESTÄTIGT] |
| 4 | Alle LEDs | Alle 3 NeoPixel AN | 600 ms | [BESTÄTIGT] |
| 5 | Alle LEDs AUS | Kurze Pause | 200 ms | [BESTÄTIGT] |
| 6 | Lauflicht | Grün -> Blau -> Rot nacheinander | je 250 ms | [BESTÄTIGT] |
| 7 | Servo Test | LCD meldet Schrankentest | 800 ms offen | [BESTÄTIGT] |
| 8 | RFID Info | Serial Meldung "Reader init" | — | [BESTÄTIGT] |
| 9 | Bereit-Status | LCD: Taste 1: Start | — | [BESTÄTIGT] |

> Stimmt die Reihenfolge? _[BESTÄTIGT] oder Änderungen_

---

## 9.4 Hauptschleife (`loop()`) — Schritt für Schritt

### Phase 1: Immer prüfen

| Schritt | Bedingung | Aktion | Bestätigt? |
|---|---|---|---|
| 1.1 | Taste 5 gedrückt? | systemReset() | [BESTÄTIGT] |

### Phase 2: Offline-Modus

| Schritt | Bedingung | Aktion | Bestätigt? |
|---|---|---|---|
| 2.1 | `!systemOnline`? | Ja, warte auf Start | [BESTÄTIGT] |
| 2.2 | Taste 1 gedrückt? | systemStarten() | [BESTÄTIGT] |

### Phase 3: Online-Modus — Taster & RFID

| Schritt | Bedingung | Aktion | Bestätigt? |
|---|---|---|---|
| 3.1 | Taste 2 gedrückt? | systemStoppen() | [BESTÄTIGT] |
| 3.2 | Karte da & gelesen? | RFID Protokoll prüfen | [BESTÄTIGT] |

### Phase 4: Karte erkannt — Identifikation

| Schritt | Aktion | Bestätigt? |
|---|---|---|
| 4.1 | UID ausgeben | [BESTÄTIGT] |
| 4.2 | karteErkennen() | [BESTÄTIGT] |

### Phase 5a: Unbekannte Karte

| Schritt | Bedingung | Aktion | Bestätigt? |
|---|---|---|---|
| 5a.1 | Index == -1 | Zugang verweigert (LCD/Serial) | [BESTÄTIGT] |

### Phase 5b: Bekannte Karte — Auswahlmenü

| Schritt | Aktion | Bestätigt? |
|---|---|---|
| 5b.1 | Name LCD/Serial anzeigen | [BESTÄTIGT] |
| 5b.2 | Wartezeit (while 10s) | [BESTÄTIGT] |

### Phase 6: Warte-Schleife (10 Sekunden Timeout)

| Schritt | Prüfung | Aktion | Bestätigt? |
|---|---|---|---|
| 6.1 | Taste 5 (Reset)? | Zurück zum Anfang | [BESTÄTIGT] |
| 6.2 | Taste 2 (Stop)? | System aus | [BESTÄTIGT] |
| 6.3 | Taste 3 (Rein)? | Betreten-Logik | [BESTÄTIGT] |
| 6.4 | Taste 4 (Raus)? | Verlassen-Logik | [BESTÄTIGT] |

### Phase 7: Betreten

| Schritt | Bedingung | Aktion | Bestätigt? |
|---|---|---|---|
| 7.1 | Schon drin? | Fehlermeldung | [BESTÄTIGT] |
| 7.2 | Raum voll? | Fehlermeldung | [BESTÄTIGT] |
| 7.3 | Frei | Status setzen, Servo auf, LEDs | [BESTÄTIGT] |

### Phase 8: Verlassen

| Schritt | Bedingung | Aktion | Bestätigt? |
|---|---|---|---|
| 8.1 | Nicht drin? | Fehlermeldung | [BESTÄTIGT] |
| 8.2 | Drin | Status setzen, Servo auf, LEDs | [BESTÄTIGT] |
| 8.5 | — | Serial: `"VERLASSEN: " + Name` | [BESTÄTIGT] |
| 8.6 | — | Schranke öffnen (2000ms) → schließen | [BESTÄTIGT] |
| 8.7 | — | LEDs: Nur Online AN | [BESTÄTIGT] |
| 8.8 | — | `break` (Warte-Schleife verlassen) | [BESTÄTIGT] |

### Phase 9: Timeout / Abschluss

| Schritt | Bedingung | Aktion | Bestätigt? |
|---|---|---|---|
| 9.1 | Keine Taste in 10s? | LCD: `"Timeout!" / "Erneut scannen."` → 2000ms | _[BESTÄTIGT]_ |
| 9.2 | — | LCD: `"System Online" / "Karte scannen..."` | _[BESTÄTIGT]_ |
| 9.3 | — | `rfid.PICC_HaltA()` | _[BESTÄTIGT]_ |
| 9.4 | — | `rfid.PCD_StopCrypto1()` | _[BESTÄTIGT]_ |

---

## 9.5 Hilfsfunktionen

> Werden diese Hilfsfunktionen korrekt verwendet?

| Funktion | Beschreibung | Korrekt? |
|---|---|---|
| `readAnalogButton()` | _Liest Analogwert und gibt Taster-Nummer zurück_ | _[BESTÄTIGT]_ |
| `tasteGedrueckt(int)` | _Prüft ob bestimmter Taster mit Entprellung gedrückt_ | _[BESTÄTIGT]_ |
| `uidGleich(...)` | _Vergleicht zwei UIDs Byte für Byte_ | _[BESTÄTIGT]_ |
| `karteErkennen()` | _Identifiziert gescannte Karte_ | _[BESTÄTIGT]_ |
| `karteName(int)` | _Gibt den Namen zur Karten-ID zurück_ | _[BESTÄTIGT]_ |
| `lcdZeigen(...)` | _Zeigt 2 Zeilen auf dem LCD an_ | _[BESTÄTIGT]_ |
| `schrankeAktion(int)` | _Öffnet und schließt die Schranke_ | _[BESTÄTIGT]_ |
| `setzeLEDs(...)` | _Steuert die 3 NeoPixel LEDs_ | _[BESTÄTIGT]_ |
| `alleLEDsAus()` | _Schaltet alle LEDs aus_ | _[BESTÄTIGT]_ |
| `uidAusgeben()` | _Gibt die UID auf Serial aus_ | _[BESTÄTIGT]_ |
| `anzahlPersonenImRaum()` | _Zählt wie viele Personen im Raum sind_ | _[BESTÄTIGT]_ |
| `systemStarten()` | _Schaltet System online_ | _[BESTÄTIGT]_ |
| `systemStoppen()` | _Schaltet System offline_ | _[BESTÄTIGT]_ |
| `systemReset()` | _Setzt alles zurück und startet neu_ | _[BESTÄTIGT]_ |

> Fehlen Funktionen? _Ja (welche?) / Nein_
> Sollen Funktionen umbenannt werden? _Ja (welche?) / Nein_

---

## 9.6 Zusätzlicher Programmablauf (falls gewünscht)

> Soll das Programm noch etwas anderes tun, das oben nicht beschrieben ist?

_Hier beschreiben oder "Nein, der Ablauf ist vollständig."_
