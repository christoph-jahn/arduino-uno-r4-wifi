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
