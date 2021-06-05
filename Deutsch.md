# ScrollText-ESP8266
![alt tag](https://github.com/DIYDave/ScrollText-ESP8266/blob/master/photos/Picture_Cut.jpg)
<br>
Auf Youtube: https://www.youtube.com/watch?v=k4Ux_I4Gl30

## Neue Version 2.0 "easy to use"!
+ Einfache Konfiguration um als Webserver oder Client zu funktionieren.
+ Generiert automatisch QR-code für die aktuelle Webadresse und zeigt diese an.

## Features:
- Verbindet sich automatisch mit bekannten Accesspoints
- Wenn kein bekannter Accesspoints gefunden wird, erstellt der ESP automatisch einen AP (Konfigurationsmodus )
- Mit Hilfe des Wifimanagers kann dann ein Netzwerk und das Passwort eingegeben werden.
- Verbindet sich entweder mit einem Webserver und liest da den Innhalt eine Textdatei.
- ODER macht sich selbst zum Webserver um einen Text zu empfangen.
- Dieser Text wird dann auf der 8 x 64 LED Matrix angezeigt
- Anzeige mehrerer gleichbleibender Texte in diversen Animationsarten
- Zeigt Infos und QR-Code auf einem 128 x 64 OLED Display
- Erlaubt Programmupload "over the air" (OTA) ohne USB Kabel

### Material:

- ESP8266 12E D1 mini pro:   https://s.click.aliexpress.com/e/_Ao1z9n
- Dot Matrix Display 2x:       http://s.click.aliexpress.com/e/b5pQfgZw
- 1,3" OLED Display SPI:       http://s.click.aliexpress.com/e/NrO6VzW
- Echtholz Furnier: 2 x A4 :    https://cutt.ly/NtdbuPj  (www.atlasholz.ch Typ: "Muster Furniere Fineline Eiche 06")

Nützliches:

Günstiges aber gutes Fluke Multimeter: https://s.click.aliexpress.com/e/_9Q278J
<br>
Sehr gutes Kabelset dazu: Multimeter: http://s.click.aliexpress.com/e/s7EqNMre
<br>

## Warum nur noch als Visual Studio Code Projekt?
Ich habe mich viel herumgeplagt mit der Arduino IDE und externen Bibliotheken.
Wenn das Projekt nach einiger Zeit wieder geöffnet wird, gibt es Fehlermeldungen beim kompilieren, weil der Core oder die Bibliotheken neuer sind.
Die meisten Fragen die ich in den Youtube Kommentaren lese, betreffen genau diese Problematik.
Deshalb gabe ich mich 2018 entschieden nur noch mit Visual Studio Code und PlatformIO zu arbeiten.
Da können (müssen aber nicht) alle Bibliotheken in das Projekt integriert werden. Zudem kann die Version des ESP-Core fixiert werden.
Ein solches Projekt kann problemlos auch nach Jahren auf anderen Rechnern kompiliert werden.

Zudem können beliebige andere Resourcen wie Links oder Datenblätter im Projekt abgelegt werden.
Bleibt zu erwähnen, dass das eine richtige IDE ist und nicht ein besserer Texteditor.😉

Es können auch Arduino Sketches importiert werden. Beim erstellen kann mann mit den .ino Dateien weitermachen oder richtig mit .h und .cpp Dateien.
Hier eine (von vielen) gute Übersicht und Anleitung zu VSC mit PlatformIO: https://devdrik.de/arduino-in-vs-code/

## Konfiguration
Als erstes muss bestimmt werden ob die Box als Webserver oder Client arbeiten soll.
### Webserver
Vorteile:
- Kein externer Webserver / Hoster benötigt
Nachteil:
- Die IP-Adresse kann jederzeit ändern.(DHCP) Daher ist es notwendig den QR-Code zu scannen um auf die Webseite zu gelangen

### Webclient
Vorteile:
- Weltweit unter der gleichen Adresse erreichbar. Z.B. MeinHoster.com/esp
Nachteil:
- Braucht ein Webserver (NAS, Hoster) auf dem PHP ausgeführt werden kann und die Berechtigung eine text Datei zu generieren.

Diese Konfiguration kann in der Datei "Wifi_Matrix_OLED.h" an dieser Stelle vorgenommen werden.

```C++
#define IamTheServer          // Enabled: act as web server; Disabled: act als client and needs a server
```
