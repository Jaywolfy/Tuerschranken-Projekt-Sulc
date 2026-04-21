# 07 — SERVO-MOTOR (SCHRANKE)

> Dokumentiere das **komplette** mechanische und zeitliche Verhalten des Servo-Motors.

---

## 7.1 Servo-Grundkonfiguration

| Feld | Wert |
|---|---|
| PWM-Pin | 8 [BESTÄTIGT] |
| Servo-Modell | _z.B. SG90 / MG996R_ |
| Wird `schranke.attach(PIN)` im Setup aufgerufen? | Ja [BESTÄTIGT] |
| Wird `schranke.write(0)` als Startposition gesetzt? | Ja (SERVO_CLOSED) [BESTÄTIGT] |

---

## 7.2 Winkel-Einstellungen

| Feld | Wert | Bestätigt? |
|---|---|---|
| Geschlossen (SERVO_CLOSED) | 0° | [BESTÄTIGT] |
| Offen (SERVO_OPEN) | 90° | [BESTÄTIGT] |
| Dreht der Servo in die richtige Richtung? | _Ja / Nein_ | |
| Ist 0° wirklich ganz geschlossen? | _Ja / Nein_ | |
| Ist 90° wirklich ganz offen? | _Ja / Nein_ | |

> **Test:** Hast du die Winkel am echten Servo getestet? _Ja / Nein_

---

## 7.3 Timing-Einstellungen

| Situation | Öffnungszeit (ms) | Wartezeit nach Schließen (ms) | Bestätigt? |
|---|---|---|---|
| Betreten (Person geht rein) | 2000 ms | 300 ms | [BESTÄTIGT] |
| Verlassen (Person geht raus) | 2000 ms | 300 ms | [BESTÄTIGT] |
| Startup-Test / Kalibrierung | 800 ms | 300 ms | [BESTÄTIGT] |
| System Reset | N/A | 300 ms | [BESTÄTIGT] |

> Ist die Öffnungszeit lang genug damit eine Person durchgehen kann? _Ja / Nein (länger: ??? ms)_
> Ist die Öffnungszeit zu lang? _Ja (kürzer: ??? ms) / Nein_

---

## 7.4 Schranken-Ablauf (Detail)

> Beschreibe den **exakten** Ablauf wenn die Schranke sich öffnet und schließt:

### Beim Betreten / Verlassen:

| Schritt | Aktion | Dauer | Bestätigt? |
|---|---|---|---|
| 1 | `schranke.write(SERVO_OPEN)` | sofort | [BESTÄTIGT] |
| 2 | `delay(offenMs)` | 2000 ms | [BESTÄTIGT] |
| 3 | `schranke.write(SERVO_CLOSED)` | sofort | [BESTÄTIGT] |
| 4 | `delay(300)` | 300 ms | [BESTÄTIGT] |

### Beim Startup-Test:

| Schritt | Aktion | Dauer | Bestätigt? |
|---|---|---|---|
| 1 | `schranke.write(SERVO_OPEN)` | sofort | [BESTÄTIGT] |
| 2 | `delay(800)` | 800 ms | [BESTÄTIGT] |
| 3 | `schranke.write(SERVO_CLOSED)` | sofort | [BESTÄTIGT] |
| 4 | `delay(300)` | 300 ms | [BESTÄTIGT] |

### Beim System Reset:

| Schritt | Aktion | Bestätigt? |
|---|---|---|
| 2 | `delay(300)` — Wartezeit | _[BESTÄTIGT]_ |
| 3 | Danach: Startup-Test (inkl. Servo-Test) | _[BESTÄTIGT]_ |

---

## 7.5 Mechanische Details

| Frage | Antwort |
|---|---|
| Was ist physisch an dem Servo befestigt? | _z.B. Pappschranke / Holzbalken / 3D-Druck-Arm_ |
| Länge der Schranke | _z.B. ca. 15 cm_ |
| Material der Schranke | _z.B. Pappe / Holz / Kunststoff_ |
| Kann der Servo die Schranke problemlos bewegen? | _Ja / Nein (zu schwer?)_ |
| Gibt es mechanisches Spiel / Wackeln? | _Ja / Nein_ |
| Macht der Servo Geräusche im Ruhezustand? | _Ja (Brummen?) / Nein_ |

---

## 7.6 Sicherheit

| Frage | Antwort |
|---|---|
| Was passiert bei Stromausfall? | _z.B. Schranke bleibt in letzter Position_ |
| Kann sich jemand an der Schranke verletzen? | _Ja / Nein_ |
| Gibt es einen Einklemmschutz? | _Ja (wie?) / Nein_ |
| Soll sich die Schranke bei Blockierung stoppen? | _Ja / Nein (nicht implementiert?)_ |
