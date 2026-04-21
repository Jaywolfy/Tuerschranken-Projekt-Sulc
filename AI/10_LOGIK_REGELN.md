# 10 — LOGIK-REGELN & GESCHÄFTSLOGIK

> Definiere **jede einzelne Regel** die das System befolgen muss.
> Für jede Regel: Was genau passiert, und was passiert wenn die Regel verletzt wird?

---

## 10.1 Zugangsregeln

| Nr. | Regel | Detail | Bestätigt? |
|---|---|---|---|
| Z1 | Nur registrierte Karten haben Zugang | Unbekannte Karten werden abgewiesen | [BESTÄTIGT] |
| Z2 | Nur **1 Person** gleichzeitig im Raum | Wenn jemand drin ist, kann niemand anders rein | [BESTÄTIGT] |
| Z3 | Eine Person kann nicht zweimal betreten | Wer schon drin ist, kann nicht nochmal rein | [BESTÄTIGT] |
| Z4 | Eine Person kann nicht verlassen wenn sie nicht drin ist | Wer nicht drin ist, kann nicht raus | [BESTÄTIGT] |

---

## 10.2 Systemregeln

| Nr. | Regel | Detail | Bestätigt? |
|---|---|---|---|
| S1 | Reset ist immer möglich | Taste 5 funktioniert in jedem Zustand | [BESTÄTIGT] |
| S2 | Stop ist im Online-Modus und während der Kartenwartezeit möglich | Taste 2 schaltet System offline | [BESTÄTIGT] |
| S3 | Start ist nur im Offline-Modus möglich | Taste 1 schaltet System online | [BESTÄTIGT] |
| S4 | Nach Reset werden alle Räume geleert | Alle `inRaum` Flags auf `false` | [BESTÄTIGT] |
| S5 | Nach Reset läuft der Startup-Test erneut | Kompletter Selbsttest | [BESTÄTIGT] |

---

## 10.3 Fehlerszenarien

| Nr. | Szenario | Erwartetes Verhalten | LCD | Serial | LEDs | Bestätigt? |
|---|---|---|---|---|---|---|
| F1 | Unbekannte Karte | Zugang verweigern, 2s warten | "Zugang" / "verweigert!" | Fehlermeldung | Keine Änderung | [BESTÄTIGT] |
| F2 | Schon im Raum | Fehler anzeigen, 2.5s warten | "Fehler:" / "Bereits im Raum!" | Name + " ist bereits im Raum!" | Keine Änderung | [BESTÄTIGT] |
| F3 | Raum besetzt | Fehler anzeigen, 2.5s warten | "Raum besetzt!" / "Max. 1 Person" | Fehlermeldung | Keine Änderung | [BESTÄTIGT] |
| F4 | Nicht im Raum | Fehler anzeigen, 2.5s warten | "Fehler:" / "Nicht im Raum!" | Name + " ist nicht im Raum!" | Keine Änderung | [BESTÄTIGT] |
| F5 | Timeout Wahl | Timeout anzeigen, 2s warten | "Timeout!" / "Erneut scannen." | Fehlermeldung | Keine Änderung | [BESTÄTIGT] |
| F6 | Karte bei Offline | Wird ignoriert | Keine Änderung | Keine Ausgabe | Keine Änderung | [BESTÄTIGT] |

> Fehlen Fehlerszenarien? _Ja (welche?) / Nein_

---

## 10.4 Grenzfälle (Edge Cases)

> Denke an ungewöhnliche Situationen:

| Nr. | Grenzfall | Was soll passieren? | Aktuell im Code? | Bestätigt? |
|---|---|---|---|---|
| G1 | 2 Karten werden gleichzeitig gescannt | _z.B. Nur die erste wird gelesen_ | _Ja (RFID liest nur eine)_ | _[BESTÄTIGT]_ |
| G2 | Karte wird während Schranke offen gescannt | _z.B. Wird ignoriert (blockiert durch delay)_ | _Ja (delay blockiert)_ | _[BESTÄTIGT]_ |
| G3 | Taste wird während Servo-Bewegung gedrückt | _z.B. Wird ignoriert (blockiert durch delay)_ | _Ja (delay blockiert)_ | _[BESTÄTIGT]_ |
| G4 | Reset während Schranke offen ist | _z.B. Schranke schließt sofort_ | _Nein (delay blockiert Reset)_ | _Ist das OK? Ja / Nein_ |
| G5 | Stromausfall während Person im Raum | _z.B. Status geht verloren_ | _Ja (RAM wird gelöscht)_ | _Ist das OK? Ja / Nein_ |
| G6 | Arduino wird neugestartet während Person im Raum | _z.B. system denkt niemand ist drin_ | _Ja (Reset löscht Status)_ | _Ist das OK? Ja / Nein_ |
| G7 | Karte wird sehr schnell hintereinander gescannt | _z.B. PICC_HaltA verhindert doppelten Scan_ | _Ja_ | _[BESTÄTIGT]_ |
| G8 | Taster 3 und 4 gleichzeitig gedrückt | _z.B. Taster 3 gewinnt (wird zuerst geprüft)_ | _Ja (if-Reihenfolge)_ | _Ist das OK? Ja / Nein_ |

> Weitere Grenzfälle? _Beschreibe oder "Keine weiteren."_

---

## 10.5 Reihenfolge der Prüfungen

> Die Reihenfolge in der Taster und Aktionen geprüft werden ist **wichtig**!

### In der Hauptschleife (loop):

| Priorität | Prüfung | Warum diese Reihenfolge? | Bestätigt? |
|---|---|---|---|
| 1 (höchste) | Reset (Taste 5) | _Soll immer funktionieren_ | _[BESTÄTIGT]_ |
| 2 | Offline-Check | _Wenn offline: nur Start erlauben_ | _[BESTÄTIGT]_ |
| 3 | Stop (Taste 2) | _Ermöglicht Abschaltung_ | _[BESTÄTIGT]_ |
| 4 | RFID-Scan | _Karte erkennen_ | _[BESTÄTIGT]_ |

### In der Warte-Schleife:

| Priorität | Prüfung | Warum diese Reihenfolge? | Bestätigt? |
|---|---|---|---|
| 1 (höchste) | Reset (Taste 5) | _Soll immer funktionieren_ | _[BESTÄTIGT]_ |
| 2 | Stop (Taste 2) | _Ermöglicht Abschaltung_ | _[BESTÄTIGT]_ |
| 3 | Betreten (Taste 3) | _Aktion_ | _[BESTÄTIGT]_ |
| 4 | Verlassen (Taste 4) | _Aktion_ | _[BESTÄTIGT]_ |

> Ist diese Prioritätsreihenfolge korrekt? _[BESTÄTIGT] oder Änderungen_
