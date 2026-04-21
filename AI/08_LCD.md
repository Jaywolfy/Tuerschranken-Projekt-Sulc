# 08 — LCD-DISPLAY

> Dokumentiere **jede einzelne Nachricht** die auf dem LCD angezeigt wird.
> Max. **16 Zeichen pro Zeile**, **2 Zeilen** insgesamt. Zähle die Zeichen!

---

## 8.1 LCD-Grundkonfiguration

| Feld | Wert |
|---|---|
| Display-Typ | LCD1602 [BESTÄTIGT] |
| Kommunikation | I2C [BESTÄTIGT] |
| I2C-Adresse | 0x27 [BESTÄTIGT] |
| Spalten | 16 [BESTÄTIGT] |
| Zeilen | 2 [BESTÄTIGT] |
| Hintergrundbeleuchtung | Ein [BESTÄTIGT] |
| Wird `lcd.init()` aufgerufen? | Ja [BESTÄTIGT] |
| Wird `lcd.backlight()` aufgerufen? | Ja [BESTÄTIGT] |

> **Wie wurde die I2C-Adresse ermittelt?**
> _z.B. I2C-Scanner Sketch / Datenblatt / Trial-and-Error / Nicht getestet_

---

## 8.2 Alle LCD-Nachrichten (vollständige Liste)

> **ACHTUNG:** Zähle die Zeichen jeder Zeile! Maximum ist **16 Zeichen**.
> Zeichen über 16 werden abgeschnitten und sind nicht sichtbar!

### Startup-Nachrichten

| Nr. | Situation | Zeile 1 | Zeichenzahl | Zeile 2 | Zeichenzahl | Dauer | Bestätigt? |
|---|---|---|---|---|---|---|---|
| 1 | System startet | `System wird` | 11 | `gestartet...` | 12 | Bis Startup fertig | [BESTÄTIGT] |
| 2 | Servo-Test | `Schranken-Test` | 14 | `laeuft...` | 9 | Während Servo-Test | [BESTÄTIGT] |
| 3 | Bereit (offline) | `Bereit!` | 7 | `Taste 1: Start` | 14 | Dauerhaft | [BESTÄTIGT] |

### System-Status Nachrichten

| Nr. | Situation | Zeile 1 | Zeichenzahl | Zeile 2 | Zeichenzahl | Dauer | Bestätigt? |
|---|---|---|---|---|---|---|---|
| 4 | System Online | `System Online` | 13 | `Karte scannen...` | 16 | Dauerhaft | [BESTÄTIGT] |
| 5 | System Offline | `System Offline` | 14 | `Taste 1: Start` | 14 | Dauerhaft | [BESTÄTIGT] |

### Karten-Nachrichten

| Nr. | Situation | Zeile 1 | Zeichenzahl | Zeile 2 | Zeichenzahl | Dauer | Bestätigt? |
|---|---|---|---|---|---|---|---|
| 6 | Karte erkannt | `{Personenname}` | - | `3=Rein  4=Raus` | 15 | Bis Aktion/Timeout | [BESTÄTIGT] |
| 7 | Zugang verweigert | `Zugang` | 6 | `verweigert!` | 11 | 2000 ms | [BESTÄTIGT] |

### Aktions-Nachrichten

| Nr. | Situation | Zeile 1 | Zeichenzahl | Zeile 2 | Zeichenzahl | Dauer | Bestätigt? |
|---|---|---|---|---|---|---|---|
| 8 | Willkommen | `Willkommen,` | 11 | `{Personenname}` | - | Während Schranke offen | [BESTÄTIGT] |
| 9 | Auf Wiedersehen | `Auf Wiedersehen` | 15 | `{Personenname}` | - | Während Schranke offen | [BESTÄTIGT] |

### Fehler-Nachrichten

| Nr. | Situation | Zeile 1 | Zeichenzahl | Zeile 2 | Zeichenzahl | Dauer | Bestätigt? |
|---|---|---|---|---|---|---|---|
| 10 | Bereits im Raum | `Fehler:` | 7 | `Bereits im Raum!` | 16 | 2500 ms | [BESTÄTIGT] |
| 11 | Nicht im Raum | `Fehler:` | 7 | `Nicht im Raum!` | 14 | 2500 ms | [BESTÄTIGT] |
| 12 | Raum besetzt | `Raum besetzt!` | 13 | `Max. 1 Person` | 14 | 2500 ms | [BESTÄTIGT] |

### Timeout-Nachricht

| Nr. | Situation | Zeile 1 | Zeichenzahl | Zeile 2 | Zeichenzahl | Dauer | Bestätigt? |
|---|---|---|---|---|---|---|---|
| 13 | Timeout | `Timeout!` | 8 | `Erneut scannen.` | 15 | 2000 ms | [BESTÄTIGT] |

---

## 8.3 Personennamen-Länge

> **WICHTIG:** Personennamen erscheinen auf dem LCD! Sind sie kürzer als 16 Zeichen?

| Name im Code | Zeichenzahl | Passt auf LCD? |
|---|---|---|
| `"Person 1"` | _8 ✅_ | _Ja_ |
| `"Person 2"` | _8 ✅_ | _Ja_ |
| _Echter Name 1?_ | _??? Zeichen_ | _Ja / Nein — Kürzen auf?_ |
| _Echter Name 2?_ | _??? Zeichen_ | _Ja / Nein — Kürzen auf?_ |

---

## 8.4 Zeichensatz / Sonderzeichen

| Frage | Antwort |
|---|---|
| Werden Umlaute (ä, ö, ü) verwendet? | _Ja / Nein (aktuell: ae, oe, ue)_ |
| Sollen Umlaute angezeigt werden? | _Ja (Custom Characters nötig!) / Nein_ |
| Werden andere Sonderzeichen benötigt? | _Ja (welche?) / Nein_ |
| Wird `lcd.clear()` vor jeder neuen Nachricht aufgerufen? | _Ja / Nein_ |

---

## 8.5 LCD-Verhalten

| Frage | Antwort |
|---|---|
| Hintergrundbeleuchtung immer an? | _Ja / Nein (wann aus?)_ |
| Flackert das Display? | _Ja (Problem!) / Nein_ |
| Ist der Kontrast gut lesbar? | _Ja / Nein (Poti justieren)_ |
| Scrollt Text der zu lang ist? | _Ja / Nein_ |
| Bleibt alte Text-Reste stehen wenn neue Nachricht kürzer ist? | _Ja (Problem: `lcd.clear()` fehlt?) / Nein_ |

---

## 8.6 Zusätzliche LCD-Nachrichten (falls gewünscht)

| Situation | Zeile 1 | Zeile 2 | Wann? |
|---|---|---|---|
| _z.B. Wartungsmodus_ | _Text_ | _Text_ | _Wann soll das angezeigt werden?_ |
| _z.B. Personen-Zähler_ | _Text_ | _Text_ | |
| | | | |

> Falls keine zusätzlichen Nachrichten nötig: Schreibe "Keine weiteren Nachrichten."
