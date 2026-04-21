# 05 — RFID-KONFIGURATION

> Dokumentiere alles rund um den RFID-Sensor, die Karten, und das Erkennungsverhalten.

---

## 5.1 RFID-Sensor Konfiguration

| Feld | Wert |
|---|---|
| Sensor-Modell | MFRC522 / RC522 [BESTÄTIGT] |
| SPI SS-Pin im Code | 10 [BESTÄTIGT] |
| SPI RST-Pin im Code | 9 [BESTÄTIGT] |
| Wird `PCD_Init()` aufgerufen? | Ja [BESTÄTIGT] |
| Delay nach Init | 50 ms [BESTÄTIGT] |
| Wird der IRQ-Pin verwendet? | Nein [BESTÄTIGT] |

---

## 5.2 Registrierte Karten

> **KRITISCH:** Trage hier die **echten UIDs** deiner Karten ein!
> 
> **So liest du die UID aus:**
> 1. System starten
> 2. Karte an den Sensor halten
> 3. Im Serial Monitor erscheint: "Gescannte UID: XX XX XX XX"
> 4. Diese Werte hier eintragen

### Karte 1

| Feld | Wert |
|---|---|
| UID (Hex) | DE AD BE EF [PLATZHALTER] |
| UID im Code-Format | {0xDE, 0xAD, 0xBE, 0xEF} [BESTÄTIGT] |
| Name / Bezeichnung | Person 1 [BESTÄTIGT] |
| Kartentyp | _z.B. Chipkarte / Schlüsselanhänger_ |
| Aktuell im Code | {0xDE, 0xAD, 0xBE, 0xEF} → "Person 1" |
| Stimmt der aktuelle Wert? | _Ja / Nein — Richtiger Wert?_ |

### Karte 2

| Feld | Wert |
|---|---|
| UID (Hex) | 12 34 56 78 [PLATZHALTER] |
| UID im Code-Format | {0x12, 0x34, 0x56, 0x78} [BESTÄTIGT] |
| Name / Bezeichnung | Person 2 [BESTÄTIGT] |
| Kartentyp | _z.B. Chipkarte / Schlüsselanhänger_ |
| Aktuell im Code | {0x12, 0x34, 0x56, 0x78} → "Person 2" |
| Stimmt der aktuelle Wert? | _Ja / Nein — Richtiger Wert?_ |

### Weitere Karten?

| Frage | Antwort |
|---|---|
| Werden mehr als 2 Karten benötigt? | _Ja (wie viele?) / Nein_ |
| Falls ja, UIDs und Namen: | |

| Karte | UID (Hex) | Name |
|---|---|---|
| Karte 3 | _UID_ | _Name_ |
| Karte 4 | _UID_ | _Name_ |

---

## 5.3 UID-Erkennung

| Feld | Wert |
|---|---|
| UID-Länge | _z.B. 4 Bytes — [BESTÄTIGT] oder andere_ |
| Vergleichsmethode | _z.B. Byte-für-Byte Vergleich_ |
| Was passiert bei 7-Byte UIDs? | _z.B. Wird nicht unterstützt / Wird unterstützt_ |

---

## 5.4 Verhalten bei Kartenscan

### Bekannte Karte

| Schritt | Was passiert genau? | Bestätigt? |
|---|---|---|
| 1 | _UID wird auf Serial ausgegeben_ | _[BESTÄTIGT]_ |
| 2 | _Karte wird mit gespeicherten UIDs verglichen_ | _[BESTÄTIGT]_ |
| 3 | _Name wird auf Serial ausgegeben_ | _[BESTÄTIGT]_ |
| 4 | _LCD zeigt: Name + "3=Rein 4=Raus"_ | _[BESTÄTIGT]_ |
| 5 | _System wartet auf Tastendruck (max. 10s)_ | _[BESTÄTIGT]_ |

### Unbekannte Karte

| Schritt | Was passiert genau? | Bestätigt? |
|---|---|---|
| 1 | _UID wird auf Serial ausgegeben_ | _[BESTÄTIGT]_ |
| 2 | _Karte wird nicht erkannt_ | _[BESTÄTIGT]_ |
| 3 | _LCD zeigt: "Zugang" / "verweigert!"_ | _[BESTÄTIGT]_ |
| 4 | _Serial: "FEHLER: Karte nicht registriert."_ | _[BESTÄTIGT]_ |
| 5 | _2000ms warten_ | _[BESTÄTIGT]_ |
| 6 | _LCD zurück auf: "System Online" / "Karte scannen..."_ | _[BESTÄTIGT]_ |
| 7 | _RFID wird mit `PICC_HaltA()` gestoppt_ | _[BESTÄTIGT]_ |

---

## 5.5 RFID-Kommunikation beenden

| Frage | Antwort |
|---|---|
| Wird `PICC_HaltA()` nach jedem Scan aufgerufen? | _Ja / Nein_ |
| Wird `PCD_StopCrypto1()` aufgerufen? | _Ja (wann?) / Nein_ |
| Wann genau wird die Kommunikation beendet? | _z.B. Am Ende der loop-Funktion, nach Reset, nach Stop_ |

---

## 5.6 Mehrfach-Scan Verhinderung

| Frage | Antwort |
|---|---|
| Kann dieselbe Karte sofort nochmal gescannt werden? | _Ja / Nein_ |
| Gibt es eine Wartezeit zwischen Scans? | _Ja (wie lange?) / Nein_ |
| Muss die Karte erst entfernt werden? | _Ja / Nein_ |
