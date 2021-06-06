# ScrollTextBox - ESP8266
![alt tag](https://github.com/DIYDave/ScrollText-ESP8266/blob/V2.0/06_Doc/photos/Picture_Cut.jpg)
<br>
### [Auf Youtube anschauen](https://www.youtube.com/watch?v=k4Ux_I4Gl30)     
### [English version of this text](https://github.com/DIYDave/ScrollText-ESP8266/blob/V2.0/README.md)

## 🔥 Neue Version 2.0 "easy to use"!
✔ Einfache Konfiguration um als Webserver oder Client zu funktionieren.

✔ Generiert automatisch QR-Codes für die aktuelle Webadresse und zeigt diese an. -> Kein mühsames erstellen von QR-Code Bildern mehr!

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
- MAX7219 Dot Matrix Display 2x:       http://s.click.aliexpress.com/e/b5pQfgZw 
  - (Genau diese Typen verwenden sonst muss das Programm geändert werden)
- 1,3" OLED Display SPI:      http://s.click.aliexpress.com/e/NrO6VzW
  - (Genau diese Typen verwenden sonst muss das Programm geändert werden)
- Echtholz Furnier: 2 x A4 :    https://cutt.ly/NtdbuPj  (www.atlasholz.ch Typ: "Muster Furniere Fineline Eiche 06")
  - Es wird jedes helle Furnier mit ca. 0.5mm gehen. Das obige ist laminiert und daher einfacher zu bearbeiten.

Nützliches:

Günstiges aber gutes Fluke Multimeter: https://s.click.aliexpress.com/e/_9Q278J
<br>
Sehr gutes Kabelset dazu: Multimeter: http://s.click.aliexpress.com/e/s7EqNMre
<br>

## Warum nur noch als Visual Studio Code / platformIO Projekt?
Ich habe mich viel herumgeplagt mit der Arduino IDE und externen Bibliotheken.
Wenn das Projekt nach einiger Zeit wieder geöffnet wird, gibt es Fehlermeldungen beim kompilieren, weil der Core oder die Bibliotheken neuer sind.
Die meisten Fragen die ich in den Youtube Kommentaren lese, betreffen genau diese Problematik.
Deshalb habe ich mich 2018 entschieden nur noch mit Visual Studio Code und PlatformIO zu arbeiten. Und habe es nie bereut!
Da können (müssen aber nicht) alle Bibliotheken in das Projekt integriert werden. Zudem kann die Version des ESP-Core fixiert werden.
Ein solches Projekt kann problemlos auch nach Jahren auf anderen Rechnern kompiliert werden.

Zudem können beliebige andere Resourcen wie Links oder Datenblätter im Projekt abgelegt werden.
Bleibt zu erwähnen, dass das eine richtige IDE ist und nicht ein besserer Texteditor.😉

Es können auch Arduino Sketches importiert werden. Bei neuen Projekten kann mann mit .ino Dateien weitermachen oder richtig mit .h und .cpp Dateien.
Hier eine (von vielen) gute Übersicht und Anleitung zu VSC mit PlatformIO: https://devdrik.de/arduino-in-vs-code/

## Konfiguration
Als erstes muss bestimmt werden ob die Box als Webserver oder Client arbeiten soll.
### Webserver
- Vorteil:
  - Kein externer Webserver / Hoster benötigt
- Nachteil:
  - Die IP-Adresse kann jederzeit ändern.(DHCP) Daher ist es notwendig den QR-Code zu scannen um auf die Webseite zu gelangen
  - Beim Einschalten wird immer der Standard Text angezeigt

### Webclient
- Vorteil:
  - Weltweit unter der gleichen Adresse erreichbar. Z.B. MeinHoster.com/esp
  - Der letzte verwendete Text wird beim einschalten wieder geladen.
- Nachteil:
  - Braucht ein Webserver (NAS, Hoster) auf dem PHP ausgeführt werden kann und die Berechtigung eine text Datei zu generieren.

Diese Konfiguration kann in der Datei "Wifi_Matrix_OLED.h" an dieser Stelle vorgenommen werden. Dazu die Zeile auskommentueren // oder nicht.
```C++
#define IamTheServer          // Enabled: act as web server; Disabled: act als client and needs a server
```

### Weitere benötigte Einstellungen wenn als Client konfiguriert:
```C++
    const String pathToServer   = "myHoster.com/esp";     // For QR-Code
    const char* host            = "myHoster.com";         // Host adress
    const String url            = "/esp/MeinText.txt";    // Path to the txt file
```
Alle fixen Texte und die verwendeten Animationen können direkt im Programm angepasst werden.

## Inbetriebnahme
Nachdem die Konfiguration gemacht ist und das Projekt in den ESP geladen geht es so weiter:
Da noch keine WiFi Daten gespeichert sind, wechselt der ESP automatisch in den AP mode.
Nun wird ein QR-Code angezeigt mit dem automatisch die Settings für den AP vom Smartphone übernommen werden. (iOs und Android)
Ist man mit dem AP "Scrollbox" verbunden und in den WLAN Einstellunegn im Smartphone, sollte automatisch die Website des WiFi-Manager aufgehen. Wenn nicht, im Browser die Adresse 192.168.4.1 eingeben. Hier kann nun ein WLAN ausgewählt und das Passwort eingegeben werden. Stimmt das Log-In, verbindet sich der ESP mit dem WiFi und fängt an Texte anzuzeigen.

Ab jetzt wir ein QR-Code angezeigt mit dem man direkt auf die Webseite der Box oder des entfernten Host/Webservers gelangt. So Einfach ist das!

### Versteckte Befehle:
- Die Helligkeit der LED kann mit dem Text "Lumos=0" bis "Lumos=15" eingestellt werden. (Ohne "") Dieser Wert wird gespeichert.
- Der WiFiManager kann mit dem Text "WiFiReset" zurückgesetzt werden. Dies ist aber nur zu Testzwecken nötig.
  - Achtung: Bei Client Betrieb muss der Text direkt nach dem Reset geändert werden, da sonst jedesmal beim Start ein Reset gemacht wird. 😒

### Ein letztes Ding:
Wenn jemand diesen Code für sein eigenes Projekt verwenden kann, würde ich mich freuen ein Bild des fertigen Objektes zu erhalten. Die Email-Adresse steht im Programm.

