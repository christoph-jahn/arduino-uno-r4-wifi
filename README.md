# Arduino Uno R4 Wifi

Basierend auf dem Tutorial von

- [**SunFounder:** Arduino Video-Lektionen für absolute
  Anfänger](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/video_lesson.html)
- [**github.com:** sunfounder / elite-explorer-kit](https://github.com/sunfounder/elite-explorer-kit/tree/docs-de)
- [**YouTube.com:** Playlist - All New Arduino R4 WiFi LESSONS for Absolute Beginners](https://youtube.com/playlist?list=PLGs0VKk2DiYyn0wN335MXpbi3PRJTMmex&si=e0M1TxBktZBGgxzf)

Table of Contents

1. [System](#system)
2. [Installation](#installation)
3. [Beispiele](#beispiele)
   1. [LED an PIN 13 zum Blinken bringen](#led-an-pin-13-zum-blinken-bringen)
   2. [Steckplatine mit dem Arduino verbinden](#steckplatine-mit-dem-arduino-verbinden)
   3. [4 PINs benutzen: 13 - 10](#4-pins-benutzen-13---10)
   4. [Binärer Zähler](#binärer-zähler)
   5. [Variablen benutzen: SOS](#variablen-benutzen-sos)
      1. [Hausaufgabe: grüne und rote LED](#hausaufgabe-grüne-und-rote-led)
   6. [Text über die serielle Schnittstelle auf dem seriellen Monitor übertragen](#text-über-die-serielle-schnittstelle-auf-dem-seriellen-monitor-übertragen)
   7. [Analoge PINs](#analoge-pins)
   8. [Potentiometerwerte verarbeiten](#potentiometerwerte-verarbeiten)
   9. [Benutzereingabe im Serial Monitor](#benutzereingabe-im-serial-monitor)
   10. [If-Anweisungen und Bedingungen](#if-anweisungen-und-bedingungen)
   11. [Steuerung einer RGB-LED](#steuerung-einer-rgb-led)
   12. [Steuerung eines Servomotors (SG90)](#steuerung-eines-servomotors-sg90)
   13. [Ein Schalter mit Pullup-Widerstand bauen](#ein-schalter-mit-pullup-widerstand-bauen)
   14. [Steuerung der RGB-LED mit Drucktaster](#steuerung-der-rgb-led-mit-drucktaster)
   15. [Interne Pullup-Widerstände verwenden](#interne-pullup-widerstände-verwenden)
   16. [LED-Matrix](#led-matrix)
   17. [LED-Matrix: Springendes Pixel](#led-matrix-springendes-pixel)
   18. [LED-Matrix: Ein-Spieler-Pong](#led-matrix-ein-spieler-pong)
   19. [DHT11: Temperatur und Luftfeuchtigkeit messen](#dht11-temperatur-und-luftfeuchtigkeit-messen)
   20. [Fotowiderstand](#fotowiderstand)

## System

- Lenovo Yoga Duet 7 13/ITL6
- Ubuntu 22.04.4 LTS

## Installation

```bash
# erstelle das Verzeichnis Arduino und wechsle dahin
mkdir -p ~/Arduino
cd ~/Arduino

# lade Arduino IDE 2.3.2 herunter
wget https://downloads.arduino.cc/arduino-ide/arduino-ide_2.3.2_Linux_64bit.AppImage

# mache App ausführbar
chmod +x arduino-ide_2.3.2_Linux_64bit.AppImage

# ermögliche die Ausführung von AppImage Programmen
sudo apt install libfuse2
```

Mit dieser Konfiguration sollte es möglich sein Arduino IDE zu starten.

Installiere als nächstes unter "Board Manager" das Board "Arduino UNO R4 Boards".

Schließe das Arduino Board mit einem USB-Kabel an den Laptop an.

Danach sollte im Menü unter dem Menüpunkt Tools > Board: ...

1. Board: ... > Arduino Uno R4 Boards, dann "Arduino Uno R4 Wifi", und
2. Port: ... > /dev/ttyACM0 (Arduino Uno R4 Wifi)

selektiert sein.

Als nächstes muss der aktuelle Benutzer Rechte für die Übertragung von Daten über den USB-Port erhalten:

```bash
# füge aktuellen Benutzer zur Gruppe dialout hinzu
sudo usermod -a -G dialout $USER

# udev Regeln (https://support.arduino.cc/hc/en-us/articles/9005041052444-Fix-udev-rules-on-Linux#renesas)
# https://github.com/arduino/ArduinoCore-renesas/blob/main/post_install.sh
sudo ./post_install.sh
```

Um `.ino`-Dateien direkt mit der IDE zu öffnen, wie folgt in Ubuntu vorgehen:

1. neuen Mimetype for `.ino` hinzufügen:

   ```bash
   cat >/tmp/mime-ino.xml <<EOF
   <?xml version="1.0" encoding="UTF-8"?>
   <mime-info xmlns="http://www.freedesktop.org/standards/shared-mime-info">
   <mime-type type="application/extension-ino">
           <comment xml:lang="en">.ino file</comment>
           <glob pattern="*.ino"/>
   </mime-type>
   </mime-info>
   EOF

   xdg-mime install /tmp/mime-ino.xml

   killall nautilus
   ```

2. Arduino `AppImage` als Anwendung in Ubuntu sichtbar machen

   ```bash
   cat >~/.local/share/applications/arduinoIDE.desktop <<EOF
   [Desktop Entry]
   Encoding=UTF-8
   Name=Arduino IDE
   Comment=Arudino IDE
   Exec=/home/${USER}/Arduino/arduino-ide_2.3.2_Linux_64bit.AppImage %F
   Type=Application
   Icon=[
   Categories=IDE;
   MimeType=application/extension-ino;
   EOF
   ```

3. das Öffnen einer `.ino` Datei im Dateimanager (Nautilus) sollte sie dann direkt in Arduino IDE öffnen

## Beispiele

### LED an PIN 13 zum Blinken bringen

Video:

- [LEKTION 1: Erste Schritte für absolute Anfänger](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson01.html)

Schritte:

1. [01_LED_Blinken.ino](./01_LED_Blinken/01_LED_Blinken.ino) in Arduino IDE öffnen
2. Datei kompilieren
3. Datei hochladen

### Steckplatine mit dem Arduino verbinden

Ziel ist es eine Blinkschaltung auf der Steckplatine, die mit dem Arduino verbunden ist.

Video:

- [LEKTION 2: Wie man Schaltungen mit einem Breadboard aufbaut](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson02.html)

Bauteile:

1. LED
2. Widerstand
3. Steckplatine

Einschränkungen:

1. Arduino R4 und LED können max. 8mA Strom aufnehmen und müssen mit einem Widerstand geschützt werden
2. lange Bein der LED muss an den positiven Pol angeschlossen werden
3. PIN 13 dient als positiver Pol
4. GND schließt den Stromkreis

Der Wert des benötigten Widerstands ergibt sich aus dem Ohmschen Gesetz:

- V = I * R

also bei einer Spannung von 5V:

- R = 5 V / 8 mA = 625 Ohm

Wir können den Widerstand 1K verwenden, obwohl er etwas größer ist, um mehr Strom zu begrenzen.

Die Spannung von 5 V ist eine obere Abschätzung. Die LED selbst verbraucht etwas
Spannung (zum Beispiel 2 V), aber der Widerstand ist dafür da, die Schaltung vor
Worst-Case-Szenarien zu schützen, zum Beispiel, dass die Diode kurzgeschlossen
ist. Er begrenzt die Stromstärke auf 8 mA.

Das Testprogramm für das SOS Signal auf der Steckplatine ist

- [02_LED_SOS.ino](./02_LED_SOS/02_LED_SOS.ino)

Schaltplan:

```text
Arduino PIN 13 -> (+, langes Bein) rote LED (-, kurzes Bein) -> 1k Widerstand -> Arduino GND
```

Anmerkung: Der Widerstand kann auch vor die rote LED geschaltet werden.

### 4 PINs benutzen: 13 - 10

Zugehöriges Video:

- [LEKTION 3: Eine LED mit dem Arduino blinken lassen](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson03.html)
- [LEKTION 4: Saubere und ordentliche Schaltungen auf einem Breadboard aufbauen](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson04.html)

Schaltplan:

```plain
  .---------.
  |         |13     //       ___
  | Arduino |------->|------|___|------.
  | Uno R4  |                 1k       |
  | Wifi    |12     //       ___       |
  |         |------->|------|___|------o
  |         |                 1k       |
  |         |11     //       ___       |
  |         |------->|------|___|------o
  |         |                 1k       |
  |         |10     //       ___       |
  |         |------->|------|___|------o
  |         |                 1k       |
  |         |GND                       |
  |         |--------------------------'
  '---------'


  .-----------------------------------.
  |                                   |
  |        Arduino Uno R4 Wifi        |
  |                                   |
  '-----------------------------------'
   GND|   13|     12|     11|     10|
      |     |       |       |       |
      | LED V   LED V   LED V   LED V
      |     -       -       -       -
      |     |       |       |       |
      |    .-.     .-.     .-.     .-.
      | 1k | |   1k| |  1k | |  1k | |
      |    | |     | |     | |     | |
      |    '-'     '-'     '-'     '-'
      |     |       |       |       |
      '-----o-------o-------o-------'


                           .---------.
                           |         |
                        GND|         |
 .-------------------------|         |
 |                         |         |
 |       ___       \\    13|         |
 o------|___|------|<------|         |
 |        1k               | Arduion |
 |       ___       \\    12| Uno R4  |
 o------|___|------|<------| Wifi    |
 |        1k               |         |
 |       ___       \\    11|         |
 o------|___|------|<------|         |
 |        1k               |         |
 |       ___       \\    10|         |
 '------|___|------|<------|         |
          1k               |         |
                           '---------'
```

Der dazugehörige Code

- [03_LED_Sequenz.ino](./03_LED_Sequenz/03_LED_Sequenz.ino)

ASCII-Circuits:

- <https://www.tech-chat.de/ascii-circuits.php>
- <https://github.com/Andy1978/AACircuit>
- <https://github.com/Blokkendoos/AACircuit>
- <https://hackaday.com/2021/04/29/ascii-schematic-diagrams/>
- <https://monodraw.helftone.com/>
- <https://busyducks.com/ascii-art-arduino-pinouts/index.html>

Arduino UNO R3 ():

```text
                             +-----+
+----[PWR]-------------------| USB |--+
|                            +-----+  |
|         GND/RST2  [ ][ ]            |
|       MOSI2/SCK2  [ ][ ]  A5/SCL[ ] |   C5
|          5V/MISO2 [ ][ ]  A4/SDA[ ] |   C4
|                             AREF[ ] |
|                              GND[ ] |
| [ ]N/C                    SCK/13[ ] |   B5
| [ ]IOREF                 MISO/12[ ] |   .
| [ ]RST                   MOSI/11[ ]~|   .
| [ ]3V3    +---+               10[ ]~|   .
| [ ]5v    -| A |-               9[ ]~|   .
| [ ]GND   -| R |-               8[ ] |   B0
| [ ]GND   -| D |-                    |
| [ ]Vin   -| U |-               7[ ] |   D7
|          -| I |-               6[ ]~|   .
| [ ]A0    -| N |-               5[ ]~|   .
| [ ]A1    -| O |-               4[ ] |   .
| [ ]A2     +---+           INT1/3[ ]~|   .
| [ ]A3                     INT0/2[ ] |   .
| [ ]A4/SDA  RST SCK MISO     TX>1[ ] |   .
| [ ]A5/SCL  [ ] [ ] [ ]      RX<0[ ] |   D0
|            [ ] [ ] [ ]              |
|  UNO_R3    GND MOSI 5V  ____________/
\_______________________/

http://busyducks.com/ascii-art-arduinos
```

### Binärer Zähler

Videos:

- [LEKTION 5: Erklärung, wie Computer auf Basis von Binärzahlen funktionieren](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson05.html)
- [LEKTION 6: Erstelle einen Binärzähler mit Arduino](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson06.html)
- [LEKTION 7: Rechnen mit Binärzahlen](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson07.html)

Code:

- [05_LED_4-Bit_Anzeige.ino](./05_LED_4-Bit_Anzeige/05_LED_4-Bit_Anzeige.ino)

Quellen:

- [for](https://www.arduino.cc/reference/en/language/structure/control-structure/for/)
- [bit shift right >>](https://www.arduino.cc/reference/en/language/structure/bitwise-operators/bitshiftright/)
- [remainder %](https://www.arduino.cc/reference/en/language/structure/arithmetic-operators/remainder/)
- [if](https://www.arduino.cc/reference/en/language/structure/control-structure/if/)
- [== (equal to)](https://www.arduino.cc/reference/en/language/structure/comparison-operators/equalto/)

Den Zähler um ein Bit erweitern, um bis 31 zählen zu können:

```plain
  .---------.
  |         |13     //       ___
  | Arduino |------->|------|___|------.
  | Uno R4  |                 1k       |
  | Wifi    |12     //       ___       |
  |         |------->|------|___|------o
  |         |                 1k       |
  |         |11     //       ___       |
  |         |------->|------|___|------o
  |         |                 1k       |
  |         |10     //       ___       |
  |         |------->|------|___|------o
  |         |                 1k       |
  |         |9      //       ___       |
  |         |------->|------|___|------o
  |         |                 1k       |
  |         |GND                       |
  |         |--------------------------'
  '---------'
```

### Variablen benutzen: SOS

Video:

- [LEKTION 8: Verwendung von Variablen in Arduino](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson08.html)

Schaltplan:

```plain
  .---------.
  |         |8      //       ___
  | Arduino |------->|------|___|------.
  | Uno R4  |                 1k       |
  | Wifi    |GND                       |
  |         |--------------------------'
  '---------'
```

Code:

- [08_LED_SOS_mit_Variablen.ino](./08_LED_SOS_mit_Variablen/08_LED_SOS_mit_Variablen.ino)

#### Hausaufgabe: grüne und rote LED

Schaltplan:

```plain
  .---------.
  |         |8      // (red)   ___
  | Arduino |------->|--------|___|------.
  | Uno R4  |                   1k       |
  | Wifi    |7      // (green) ___       |
  |         |------->|--------|___|------o
  |         |                   1k       |
  |         |GND                         |
  |         |----------------------------'
  '---------'
```

Code:

- [08H_LEDs_Blinken.ino](./08H_LEDs_Blinken/08H_LEDs_Blinken.ino)

### Text über die serielle Schnittstelle auf dem seriellen Monitor übertragen

Video:

- [LEKTION 9: Verwendung des seriellen Ports zum Ausgeben auf den seriellen Monitor](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson09.html)

Code:

- [09_Serial_Monitor_Ausgabe.ino](./09_Serial_Monitor_Ausgabe/09_Serial_Monitor_Ausgabe.ino)

Vorgehen:

1. code kompilieren
2. hochladen und ausführen
3. "Seriellen Monitor" mit Baudrate 9600 öffnen (Symbol in der IDE rechts oben)

Das Programm wird direkt nach dem Hochladen ausgeführt. Man kann es aber auch
über den Reset-Taster auf der Arduino-Platine neu starten.

Schaltplan für die Funktion `blinkingLedAndPrintingToSerialMonitor`:

```text
  .---------.
  |         |10     //         ___
  | Arduino |------->|--------|___|------.
  | Uno R4  |                   1k       |
  | Wifi    |GND                         |
  |         |----------------------------'
  '---------'
```

### Analoge PINs

Einige der digitalen PINs auf der Arduino-Platine können auch analog angesteuert
werden. Dazu gehören die mit dem Prefix "~", also 11, 10, 9, 6, 5 und 3.

Videos:

- [LEKTION 10: Schreiben von analogen Spannungen mit dem Arduino](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson10.html)
- [LEKTION 11: Pulsweitenmodulation (PWM) zur Simulation von Analogspannungen](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson11.html)

Code: [10_LED_Dimmen.ino](./10_LED_Dimmen/10_LED_Dimmen.ino)

Der Arduino simuliert Spannung zwischen 5V und 0V mittels Pulse Width Modulation
(PWM), d.h. es wird zwischen 0V und 5V innerhalb von 2 ms entsprechend an- und
ausgeschaltet, um eine gewünschte Spannung zu erhalten.

Beispielsweise entspricht der Wert 126 in etwa 2,5V, weil `(126 / 255) * 5V = 49% * 5V = 2,5V`, d.h. mittels PWM ist die Spannung 1ms (= 50% * 2ms) lang 5V und dann 1ms lang 0V.

Für den Wert 25 erhalten wir in etwa `(25 / 255) * 5V = 10% * 5V = 0,5V`, d.h. mittels PWM ist die Spannung 200 µs (= 10% * 2ms) lang 5V und 1800µs lang 0V.

### Potentiometerwerte verarbeiten

Videos:

- [LEKTION 12: Analoge Spannungen mit dem Arduino messen](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson12.html)
- [LEKTION 13: Dimmbares LED gesteuert von einem Potentiometer](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson13.html)

Code: [12_Potentiometer.ino](./12_Potentiometer/12_Potentiometer.ino)

Der eingelesene (digitale) Wert ist 10 bit lang (0..1023) und entspricht 0V bis 5V.

### Benutzereingabe im Serial Monitor

Video:

- [LEKTION 14: Benutzereingaben über den seriellen Monitor lesen](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson14.html)
- [LEKTION 15: Steuerung einer LED basierend auf Benutzereingaben vom seriellen Monitor](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson15.html)

Code:

- [14_Serial_Monitor_Eingabe.ino](./14_Serial_Monitor_Eingabe/14_Serial_Monitor_Eingabe.ino)
- [14H_LED_Helligkeit_per_Eingabe.ino](./14H_LED_Helligkeit_per_Eingabe/14H_LED_Helligkeit_per_Eingabe.ino)

### If-Anweisungen und Bedingungen

Video:

- [LEKTION 16: Verständnis von If-Anweisungen und Bedingungsschleifen](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson16.html)
- [LEKTION 17: Steuerung mehrerer LEDs über den seriellen Monitor](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson17.html)

Code:

- [16_Serial_Monitor_Bedingte_Eingabe.ino](./16_Serial_Monitor_Bedingte_Eingabe/16_Serial_Monitor_Bedingte_Eingabe.ino)
- [16H_LED_Einschalten_per_Eingabe.ino](./16H_LEDs_Einschalten_per_Eingabe/16H_LED_Einschalten_per_Eingabe.ino)

### Steuerung einer RGB-LED

Videos:

- [LEKTION 18: Steuerung einer RGB-LED mit einem Arduino](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson18.html)
- [LEKTION 19: Farbmischung mit einer RGB-LED](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson19.html)
- [LEKTION 20: For-Schleifen in Arduino](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson20.html)
- [LEKTION 21: Verständnis von While-Schleifen](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson21.html)

Die RGB-LED hat 4 PINs, die unterschiedlich lang sind:

```text
   __________________
  |      RGB LED     |
  '------------------'
   R|  M|   G|    B|
    |   |    |     |
    |   |    |
        |
    Rot GND  Grün  Blau
```

Der längste PIN ist Masse (GND).

Code:

- [18_RGB_LED.ino](./18_RGB_LED/18_RGB_LED.ino)
- [19H_RGB_Sequenz.ino](./19H_RGB_Sequenz/19H_RGB_Sequenz.ino)

### Steuerung eines Servomotors (SG90)

Videos:

- [LEKTION 22: Steuerung eines Servomotors mit Ihrem Arduino](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson22.html)
- [LEKTION 23: Steuerung eines Servomotors mit einem Potentiometer](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson23.html)

Neues Bauteil:

- Micro Servo 95 (SG90)
- oder ein stärkeren Servo, der dann aber an eine externe Stromquelle
  angeschlossen werden muss. Dabei sollte Masse des Arduinos und Masse der
  externen 5V-Stromquelle mit einander verbunden sein.

Arduino IDE:

- Library Manager > [Servo](https://www.arduino.cc/reference/en/libraries/servo/) by Michael Margolis (v1.2.2)

Code:

- [22_Servo_SG90.ino](./22_Servo_SG90/22_Servo_SG90.ino)
- [22H_Servo_SG90_steuern_per_Eingabe.ino](./22H_Servo_SG90_steuern_per_Eingabe/22H_Servo_SG90_steuern_per_Eingabe.ino)

### Ein Schalter mit Pullup-Widerstand bauen

Videos:

- [LEKTION 24: Ein Schalter mit Pullup-Widerstand bauen](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson24.html)
- [LEKTION 25: Einen Kippschalter mit einem Taster bauen](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson25.html)

Neue Bauteile:

- Taster
- Pullup-Widerstand

Code:

- [24_Schalter_mit_Pullup-Widerstand.ino](./24_Schalter_mit_Pullup-Widerstand/24_Schalter_mit_Pullup-Widerstand.ino)

### Steuerung der RGB-LED mit Drucktaster

Videos:

- [LEKTION 26: Steuerung der RGB-LED-Farbe mit Drucktasten](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson26.html)

Code:

- [25H_RGB-LED_mit_Kippschalter.ino](./25H_RGB-LED_mit_Kippschalter/25H_RGB-LED_mit_Kippschalter.ino)
- [26_RGB-LED_mit_Drucktasten.ino](./26_RGB-LED_mit_Drucktasten/26_RGB-LED_mit_Drucktasten.ino)

### Interne Pullup-Widerstände verwenden

Video:

- [LEKTION 27: Verwendung interner Pullup-Widerstände am Arduino](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson27.html)

Code:

- [27_Interner_Pullup-Widerstand.ino](./27_Interner_Pullup-Widerstand/27_Interner_Pullup-Widerstand.ino)
- [27H_RGB-LED_mit_internen_Pullup-Widerständen.ino](./27H_RGB-LED_mit_internen_Pullup-Widerständen/27H_RGB-LED_mit_internen_Pullup-Widerständen.ino)

### LED-Matrix

Video:

- [LEKTION 28: Verwendung der LED-Matrix auf dem Arduino R4 WiFi](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson28.html)

Code:

- [28_LED-Matrix_Pixel_und_Text.ino](./28_LED-Matrix_Pixel_und_Text/28_LED-Matrix_Pixel_und_Text.ino)

### LED-Matrix: Springendes Pixel

Video:

- [LEKTION 29: Erstellen Sie ein springendes Pixel auf der R4 WiFi LED-Matrix](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson29.html)

Code:

- [28H_LED-Matrix_springendes_Pixel.ino](./28H_LED-Matrix_springendes_Pixel/28H_LED-Matrix_springendes_Pixel.ino)
- [29_LED-Matrix_springendes_Pixel.ino](./29_LED-Matrix_springendes_Pixel/29_LED-Matrix_springendes_Pixel.ino)

### LED-Matrix: Ein-Spieler-Pong

Video:

- [LEKTION 30: Erstellen Sie ein Ein-Spieler-Pong-Spiel auf der R4 WiFi Matrix](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson30.html)

Code:

- [29H_Spiel_Pong.ino](./29H_Spiel_Pong/29H_Spiel_Pong.ino)
- [30_Spiel_Pong.ino](./30_Spiel_Pong/30_Spiel_Pong.ino)

Links:

- [Create a Bouncing Pixel on the Arduino Uno R4 WiFi LED Matrix](https://toptechboy.com/create-a-bouncing-pixel-on-the-arduino-no-r4-wifi-led-matrix/)

### DHT11: Temperatur und Luftfeuchtigkeit messen

Video:

- [LEKTION 31: Temperatur und Luftfeuchtigkeit mit dem DHT11 messen](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson31.html)
- [LEKTION 32: Temperatur und Luftfeuchtigkeit auf der LED-Matrix anzeigen](https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson32.html)

Code:

- [31_DHT11_Temperatur_und_Feuchtigkeit_messen.ino](./31_DHT11_Temperatur_und_Feuchtigkeit_messen/31_DHT11_Temperatur_und_Feuchtigkeit_messen.ino)
- [31H_Temperaturanzeige_auf_Knopfdruck.ino](./31H_Temperaturanzeige_auf_Knopfdruck/31H_Temperaturanzeige_auf_Knopfdruck.ino)
- [32_Temperaturanzeige_auf_Knopfdruck.ino](./32_Temperaturanzeige_auf_Knopfdruck/32_Temperaturanzeige_auf_Knopfdruck.ino)

Links:

- [Using the Arduino Uno R4 Wifi to Measure Temperature and Humidity With the DHT11](https://toptechboy.com/using-the-arduino-uno-r4-wifi-to-measure-temperature-and-humidity-with-the-dht11/)

### Fotowiderstand

Eine Erhöhung der Anzahl an Photonen bei einem Fotowiderstand resultiert in einer Zunahme der Anzahl an Elektronen im Leitungsband, einer Zunahme der Anzahl an Löchern im Valenzband sowie einer Zunahme der Leitfähigkeit. Gleichzeitig nimmt der elektrische Widerstand ab.

Der Widerstandsbereich erstreckt sich von 100 kΩ (dunkel) bis 500 Ω (sehr hell).

Formeln:

```text
V = I R
5 = I (R_F + R_1)
5 = I (R_F + 10.000)
I = 5 / (R_F + 10.000)

V_AUS = I R_1

V_AUS = (10.000 x 5) / (R_F + 10.000)
```

- Der Strom, der durch die Schaltung fließt, beträgt `5 / (R_F + 10.000) A`.
- Die an dem Fotowiderstand gemessene Ausgangsspannung beträgt `(10.000 x 5) / (R_F + 10.000)`, d.h.
  - bei sehr hellem Licht höchstens `R_F = 0 Ω` -> `V_AUS = 5 V`
  - bei absoluter Dunkelheit etwa `R_F = 100.000 Ω`-> `V_AUS = 0,45 V`

Video:

- [Arduino Uno R4 WiFi LESSON 33: Using a Photoresistor in a Project](https://www.youtube.com/watch?v=AEJ-j7EDyZ4)
- [Arduino Uno R4 WiFi LESSON 34: Controlling Servo with Photo Resistor](https://www.youtube.com/watch?v=rP0Go2EV358)

Code:

- [33_Fotowiderstand.ino](./33_Fotowiderstand/33_Fotowiderstand.ino)
- [33H_Lichstaerkeanzeige.ino](./33H_Lichstaerkeanzeige/33H_Lichstaerkeanzeige.ino)
