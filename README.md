# Arduino Uno R4 Wifi

Basierend auf dem Tutorial von

- <https://docs.sunfounder.com/projects/elite-explorer-kit/de/latest/video_lesson/lesson01.html>

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

1. [Arduino_Unio_R4_Wifi_LESSON1.ino](./Arduino_Unio_R4_Wifi_LESSON1/Arduino_Unio_R4_Wifi_LESSON1.ino) in Arduino IDE öffnen
2. Datei kompilieren
3. Datei hochladen

### Steckplatine mit dem Arduino verbinden

Ziel ist es eine Blinkschaltung auf der Steckplatine, die mit dem Arduino verbunden ist.

Referenz: <https://youtu.be/_kpiHFGB_ys?si=myoUIhc59wrmGooN>, <https://youtu.be/_kpiHFGB_ys?si=__zJkqFcaxGlXYV4>

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

- [Arduino_Unio_R4_Wifi_LESSON2.ino](./Arduino_Unio_R4_Wifi_LESSON2/Arduino_Unio_R4_Wifi_LESSON2.ino)

Schaltplan:

```text
Arduino PIN 13 -> (+, langes Bein) rote LED (-, kurzes Bein) -> 1k Widerstand -> Arduino GND
```

Anmerkung: Der Widerstand kann auch vor die rote LED geschaltet werden.

### 4 PINs benutzen: 13 - 10

Zugehöriges Video: <https://youtu.be/JUptf53Ni0A?si=sSWQqmXG1j4_0hRr>

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

- [Arduino_Unio_R4_Wifi_LESSON3.ino](./Arduino_Unio_R4_Wifi_LESSON3/Arduino_Unio_R4_Wifi_LESSON3.ino)

ASCII-Circuits:

- <https://www.tech-chat.de/ascii-circuits.php>
- <https://github.com/Andy1978/AACircuit>
- <https://github.com/Blokkendoos/AACircuit>

### Binärer Zähler

Videos:

- <https://youtu.be/KEtut8pzXZA?si=hlFt_9b_BrLcxyQj>
- <https://youtu.be/w1C3OT1V3xA?si=hFxf-0Q9d3Ii40JJ>

Code:

- [Arduino_Uno_R4_Wifi_LESSON5.ino](./Arduino_Uno_R4_Wifi_LESSON5/Arduino_Uno_R4_Wifi_LESSON5.ino)

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

=== Variablen benutzen: SOS

Video:

- [Arduino Uno R4 WiFi LESSON 8: Using Variables in Arduino](https://youtu.be/Ucvwq5hFc3U?si=VgtfJ7HHdaJ_xMnJ)

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

- [Arduino_Uno_R4_Wifi_LESSON8.ino](./Arduino_Uno_R4_Wifi_LESSON8/Arduino_Uno_R4_Wifi_LESSON8.ino)

==== Hausaufgabe: grüne und rote LED

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

- [Arduino_Uno_R4_Wifi_LESSON8_HomeWork.ino](./Arduino_Uno_R4_Wifi_LESSON8_HomeWork/Arduino_Uno_R4_Wifi_LESSON8_HomeWork.ino)

### Text über die serielle Schnittstelle auf dem seriellen Monitor übertragen

Video: [Arduino Uno R4 WiFi LESSON 9: Using the Serial Port to Print to the Serial Monitor](https://youtu.be/4N-Q28lTzqE?si=YJxdhXsV4UTK8-D0)

Code:

- [Arduino_Uno_R4_Wifi_LESSON9.ino](./Arduino_Uno_R4_Wifi_LESSON9/Arduino_Uno_R4_Wifi_LESSON9.ino)

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

Video: [Arduino Uno R4 WiFi LESSON 10: Writing Analog Voltages With the Arduino](https://youtu.be/lTzOvBYNo3U?si=bL3abccMDxWuQA5c)

Code: [Arduino_Uno_R4_Wifi_LESSON10.ino](./Arduino_Uno_R4_Wifi_LESSON10/Arduino_Uno_R4_Wifi_LESSON10.ino)
