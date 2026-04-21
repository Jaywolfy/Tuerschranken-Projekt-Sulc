# Anschlusstabelle: Türschranken-Projekt-Sulc

Diese Datei dient als Referenz für die physische Verkabelung der Komponenten am Arduino Uno.

## 1. Übersicht der Pin-Belegung (Arduino Uno)

| Pin | Komponente | Funktion |
| :--- | :--- | :--- |
| **0** | -- | (Serial RX) |
| **1** | -- | (Serial TX) |
| **2** | **NeoPixel LEDs** | **Datenleitung (Data In)** |
| **3** | -- | -- |
| **4** | -- | -- |
| **5** | -- | -- |
| **6** | -- | -- |
| **7** | -- | -- |
| **8** | **Servo Motor** | **Steuersignal (PWM)** |
| **9** | **RFID RC522** | **RST (Reset)** |
| **10** | **RFID RC522** | **SDA / SS (Chip Select)** |
| **11** | **RFID RC522** | **MOSI** |
| **12** | **RFID RC522** | **MISO** |
| **13** | **RFID RC522** | **SCK (Clock)** |
| **A0** | **Taster-Netzwerk** | **Analog-In (Alle 5 Taster)** |
| **A4** | **LCD (I2C)** | **SDA** |
| **A5** | **LCD (I2C)** | **SCL** |

---

## 2. Einzelverbindungen Detail

### A. RFID-RC522 Sensor
| Pin am Sensor | Ziel am Arduino | Info |
| :--- | :--- | :--- |
| **3.3V** | **3.3V** | **NICHT AN 5V ANSCHLIESSEN!** |
| **RST** | **Pin 9** | Orange Leitung |
| **GND** | **GND** | Masse (Schwarz) |
| **IRQ** | -- | *Nicht belegt* |
| **MISO** | **Pin 12** | Weiß |
| **MOSI** | **Pin 11** | Grün |
| **SCK** | **Pin 13** | Blau |
| **SDA (SS)** | **Pin 10** | Gelb |

### B. LCD Display (1602 I2C)
| Pin am Modul | Ziel am Arduino | Info |
| :--- | :--- | :--- |
| **GND** | **GND** | Masse |
| **VCC** | **5V** | Stromversorgung |
| **SDA** | **Pin A4 / SDA** | Seriell Data |
| **SCL** | **Pin A5 / SCL** | Seriell Clock |

### C. NeoPixel LEDs (3 Stück)
| Pin am Stripe | Ziel am Arduino | Info |
| :--- | :--- | :--- |
| **GND / -** | **GND** | Masse |
| **DI / DIN** | **Pin 2** | Daten (deine Konfiguration) |
| **+5V / +** | **5V** | Stromversorgung |

### D. Servo Motor (Schranke)
| Kabel am Servo | Ziel am Arduino | Info |
| :--- | :--- | :--- |
| **Schwarz / Braun** | **GND** | Masse |
| **Rot** | **5V** | Stromversorgung |
| **Gelb / Orange** | **Pin 8** | Signal |

---

## 3. Stromversorgungshinweise
- Der **Arduino** kann via USB betrieben werden.
- Bei Betrieb von **Servo + LEDs** wird ein externes Netzteil (9V oder 12V an die Hohlbuchse) empfohlen, um Spannungsabfälle (und damit ungewollte Neustarts) zu verhindern.
- Der **RFID-Sensor** ist sehr empfindlich: Prüfe doppelt, dass er an **3.3V** hängt.

---

## 4. Taster-Netzwerk (Pin A0)
Die 5 Taster müssen über ein Widerstandsnetzwerk als Spannungsteiler an den Pin **A0** angeschlossen werden. Wenn der Pin offen bleibt (nichts angeschlossen), kann es zu Geister-Drücken und Fehl-Resets kommen.
