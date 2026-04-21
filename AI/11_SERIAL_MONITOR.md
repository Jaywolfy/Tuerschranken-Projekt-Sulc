# 11 — SERIAL MONITOR AUSGABEN

> Dokumentiere **jede einzelne** Ausgabe die im Serial Monitor erscheint.
> Gib den **exakten Text** an — Zeichen für Zeichen!

---

## 11.1 Serial-Konfiguration

| Feld | Wert |
|---|---|
| Baudrate | _z.B. 9600 — [BESTÄTIGT]_ |
| Wird `Serial.begin()` im Setup aufgerufen? | _Ja / Nein_ |
| Verwendet `F()` Macro (Flash-Speicher)? | _Ja / Nein_ |

---

## 11.2 Alle Serial-Ausgaben (vollständige Liste)

> Gib den **exakten Wortlaut** jeder Ausgabe an. Achte auf Leerzeichen, Satzzeichen und Zeilenumbrüche!

### Startup-Ausgaben

| Nr. | Wann? | Funktion | Exakter Text | Zeilenende | Bestätigt? |
|---|---|---|---|---|---|
| 1 | Startup | `startupTest()` | `=============================` | println | [BESTÄTIGT] |
| 2 | Startup | `startupTest()` | `   TUERSCHRANKE - STARTUP    ` | println | [BESTÄTIGT] |
| 3 | Startup | `startupTest()` | `=============================` | println | [BESTÄTIGT] |
| 4 | Startup | `startupTest()` | `Servo-Kalibrierung...` | println | [BESTÄTIGT] |
| 5 | Startup | `startupTest()` | `RFID-Reader initialisiert.` | println | [BESTÄTIGT] |
| 6 | Startup | `startupTest()` | `Tipp: Karte scannen zum Auslesen der UID.` | println | [BESTÄTIGT] |
| 7 | Startup | `startupTest()` | `Warte auf Taste 1 (Start)...` | println | [BESTÄTIGT] |

### System-Status Ausgaben

| Nr. | Wann? | Funktion | Exakter Text | Zeilenende | Bestätigt? |
|---|---|---|---|---|---|
| 8 | System Online | `systemStarten()` | `>> System ist ONLINE.` | println | [BESTÄTIGT] |
| 9 | System Offline | `systemStoppen()` | `>> System ist OFFLINE.` | println | [BESTÄTIGT] |
| 10 | System Reset | `systemReset()` | `>> SYSTEM RESET <<` | println | [BESTÄTIGT] |

### RFID-Ausgaben

| Nr. | Wann? | Funktion | Exakter Text | Zeilenende | Bestätigt? |
|---|---|---|---|---|---|
| 11 | Karte gescannt | `uidAusgeben()` | `Gescannte UID: XX XX XX XX` | println | [BESTÄTIGT] |
| 12 | Karte erkannt | `loop()` | `Erkannte Person: {Name}` | println | [BESTÄTIGT] |
| 13 | Karte unbekannt | `loop()` | `FEHLER: Karte nicht registriert.` | println | [BESTÄTIGT] |

### Aktions-Ausgaben

| Nr. | Wann? | Funktion | Exakter Text | Zeilenende | Bestätigt? |
|---|---|---|---|---|---|
| 14 | Betreten | `loop()` | `EINTRETEN: {Name}` | println | [BESTÄTIGT] |
| 15 | Verlassen | `loop()` | `VERLASSEN: {Name}` | println | [BESTÄTIGT] |

### Fehler-Ausgaben

| Nr. | Wann? | Funktion | Exakter Text | Zeilenende | Bestätigt? |
|---|---|---|---|---|---|
| 16 | Bereits im Raum | `loop()` | `{Name} ist bereits im Raum!` | println | [BESTÄTIGT] |
| 17 | Nicht im Raum | `loop()` | `{Name} ist nicht im Raum!` | println | [BESTÄTIGT] |
| 18 | Raum besetzt | `loop()` | `FEHLER: Der Raum ist bereits von einer anderen Person besetzt! (Max: 1)` | println | [BESTÄTIGT] |
| 19 | Timeout | `loop()` | `Timeout: Keine Taste gedrueckt.` | println | [BESTÄTIGT] |

---

## 11.3 UID-Ausgabeformat

| Frage | Antwort |
|---|---|
| Format | _z.B. Hex, Großbuchstaben, mit Leerzeichen getrennt_ |
| Beispiel | _z.B. `DE AD BE EF`_ |
| Werden führende Nullen angezeigt? | _Ja (z.B. `0A` statt `A`) / Nein_ |
| Trennzeichen zwischen Bytes | _z.B. Leerzeichen_ |
| Bestätigt? | _[BESTÄTIGT]_ |

---

## 11.4 Sollen Serial-Ausgaben geändert werden?

| Frage | Antwort |
|---|---|
| Sollen Texte geändert werden? | _Ja (welche?) / Nein_ |
| Sollen zusätzliche Ausgaben hinzugefügt werden? | _Ja (welche?) / Nein_ |
| Sollen Ausgaben entfernt werden? | _Ja (welche?) / Nein_ |
| Soll ein Zeitstempel bei jeder Ausgabe stehen? | _Ja / Nein_ |
| Soll der aktuelle Systemstatus regelmäßig ausgegeben werden? | _Ja (wie oft?) / Nein_ |
