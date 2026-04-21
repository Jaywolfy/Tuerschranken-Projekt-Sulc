# 04 — TASTER-KONFIGURATION

> Dokumentiere die **komplette** Taster-Logik: Belegung, Schwellenwerte, Entprellung, Verhalten.

---

## 4.1 Übersicht Tastenbelegung

| Taster-Nr. | Funktion | Kurzname im Code | Beschreibung (was passiert genau?) |
|---|---|---|---|
| Taster 1 | Start | btnIndex 0 | System geht online [BESTÄTIGT] |
| Taster 2 | Stop | btnIndex 1 | System geht offline [BESTÄTIGT] |
| Taster 3 | Betreten | btnIndex 2 | Person betritt den Raum [BESTÄTIGT] |
| Taster 4 | Verlassen | btnIndex 3 | Person verlässt den Raum [BESTÄTIGT] |
| Taster 5 | Reset | btnIndex 4 | System komplett neustarten [BESTÄTIGT] |

---

## 4.2 Analog-Schwellenwerte (KRITISCH!)

> **Diese Werte sind entscheidend!** Falsche Schwellenwerte = Taster funktionieren nicht.
> 
> **So misst du die Werte aus:**
> 1. Lade einen Sketch hoch der `analogRead(A0)` im Serial Monitor ausgibt
> 2. Drücke jeden Taster einzeln und notiere den Wert
> 3. Trage die Werte unten ein

### Gemessene Rohwerte

| Taster | Gemessener Analogwert | Mehrfach gemessen? | Schwankungsbereich |
|---|---|---|---|
| Kein Taster gedrückt | _z.B. 1023_ | _Ja / Nein_ | _z.B. 1020-1023_ |
| Taster 1 | _z.B. 0_ | _Ja / Nein_ | _z.B. 0-5_ |
| Taster 2 | _z.B. 130_ | _Ja / Nein_ | _z.B. 125-135_ |
| Taster 3 | _z.B. 310_ | _Ja / Nein_ | _z.B. 305-315_ |
| Taster 4 | _z.B. 490_ | _Ja / Nein_ | _z.B. 485-495_ |
| Taster 5 | _z.B. 680_ | _Ja / Nein_ | _z.B. 675-685_ |

### Schwellenwerte im Code

> Basierend auf den gemessenen Werten: Welche Schwellenwerte sollen im Code verwendet werden?

| Bedingung im Code | Bedeutung | Aktueller Wert | Richtiger Wert? |
|---|---|---|---|
| `val < 50` | Taster 1 erkannt | < 50 | [BESTÄTIGT] |
| `val < 200` | Taster 2 erkannt | < 200 | [BESTÄTIGT] |
| `val < 400` | Taster 3 erkannt | < 400 | [BESTÄTIGT] |
| `val < 600` | Taster 4 erkannt | < 600 | [BESTÄTIGT] |
| `val < 800` | Taster 5 erkannt | < 800 | [BESTÄTIGT] |
| `val >= 800` | Kein Taster | >= 800 | [BESTÄTIGT] |

> **Wurden die Schwellenwerte mit echten Messungen verifiziert?** _Ja / Nein_

---

## 4.3 Entprellung (Debouncing)

| Feld | Wert |
|---|---|
| Entprellmethode | Zeitbasiert (millis) [BESTÄTIGT] |
| Entprellzeit | 200 ms [BESTÄTIGT] |
| Ist die Entprellzeit ausreichend? | _Ja / Nein (Taster prellen noch?)_ |
| Soll die Entprellzeit geändert werden? | _Ja (neuer Wert?) / Nein_ |

---

## 4.4 Tasterverhalten in verschiedenen Zuständen

> Welche Taster funktionieren in welchem Systemzustand?

| Taster | System OFFLINE | System ONLINE | Während Karten-Wartezeit | Während Startup |
|---|---|---|---|---|
| Taster 1 (Start) | _Aktiv / Inaktiv_ | _Aktiv / Inaktiv_ | _Aktiv / Inaktiv_ | _Aktiv / Inaktiv_ |
| Taster 2 (Stop) | _Aktiv / Inaktiv_ | _Aktiv / Inaktiv_ | _Aktiv / Inaktiv_ | _Aktiv / Inaktiv_ |
| Taster 3 (Enter) | _Aktiv / Inaktiv_ | _Aktiv / Inaktiv_ | _Aktiv / Inaktiv_ | _Aktiv / Inaktiv_ |
| Taster 4 (Leave) | _Aktiv / Inaktiv_ | _Aktiv / Inaktiv_ | _Aktiv / Inaktiv_ | _Aktiv / Inaktiv_ |
| Taster 5 (Reset) | _Aktiv / Inaktiv_ | _Aktiv / Inaktiv_ | _Aktiv / Inaktiv_ | _Aktiv / Inaktiv_ |

---

## 4.5 Gleichzeitiges Drücken

| Frage | Antwort |
|---|---|
| Was passiert wenn 2 Taster gleichzeitig gedrückt werden? | _z.B. Der mit dem niedrigeren Analogwert gewinnt_ |
| Ist das ein Problem? | _Ja / Nein_ |
| Muss das im Code behandelt werden? | _Ja (wie?) / Nein_ |

---

## 4.6 Physische Anordnung

> Wie sind die Taster physisch angeordnet?

| Frage | Antwort |
|---|---|
| Anordnung | _z.B. Reihe nebeneinander / Matrix / verteilt_ |
| Beschriftung vorhanden? | _Ja (welche?) / Nein_ |
| Farbcodierung? | _Ja (welche Farben?) / Nein_ |
| Abstand zwischen Tastern | _z.B. ca. 2 cm_ |

> Skizze der Taster-Anordnung (optional):
> ```
> [T1: Start] [T2: Stop] [T3: Enter] [T4: Leave] [T5: Reset]
> ```
