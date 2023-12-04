# ScrollTextBox - ESP8266
![alt tag](https://github.com/DIYDave/ScrollText-ESP8266/blob/V2.0/06_Doc/photos/Picture_Cut.jpg)
<br>

## [This version is outdated please check version 2.2 on this page: ](https://github.com/DIYDave/Scroll-Box-Verion-2/tree/main)

### [Watch on Youtube](https://www.youtube.com/watch?v=k4Ux_I4Gl30)     
### [Deutsche Version dieses Textes](https://github.com/DIYDave/ScrollText-ESP8266/blob/V2.0/Deutsch.md)

## 🔥 New version 2.0 "easy to use"! 
✔ Simple configuration to function as a web server or client.

✔ Automatically generates QR codes for the current web address and displays them. -> No more tedious creation of QR code images!

## Features:
- Automatically connects to a known access point
- If no known access point is found, the ESP automatically creates an AP (configuration mode)
- With the help of the WiFi manager, a network and the password can then be entered.
- Either connects to a web server and reads the contents of a text file.
- OR makes itself a web server to receive a text over a website.
- This text is then displayed on the 8 x 64 LED matrix
- Display of several consistent texts in various types of animation
- Shows information and QR code on a 128 x 64 OLED display
- Allows program upload "over the air" (OTA) without a USB cable

### Material:

- ESP8266 12E D1 mini pro: https://s.click.aliexpress.com/e/_Ao1z9n
- MAX7219 Dot Matrix Display 2x: http://s.click.aliexpress.com/e/b5pQfgZw
  - (Use exactly these types otherwise the program has to be changed)
- 1.3 "OLED display SPI: http://s.click.aliexpress.com/e/NrO6VzW
  - (Use exactly these types otherwise the program has to be changed)
- Real wood veneer: 2 x A4: https://cutt.ly/NtdbuPj (www.atlasholz.ch Type: "Sample Veneers Fineline Oak 06")
  - Any light veneer with approx. 0.5mm will work. The above is laminated so it is easier to work with.

Useful:

- Inexpensive but good Fluke multimeter: https://s.click.aliexpress.com/e/_9Q278J
- Very good cable set for this: Multimeter: http://s.click.aliexpress.com/e/s7EqNMre

## Why only as a Visual Studio Code / platformIO project?
I struggled a lot with the Arduino IDE and external libraries.
If the project is opened again after a while, there are error messages when compiling because the core or the libraries are newer.
Most of the questions I read in the YouTube comments concern exactly this problem.
That's why I decided in 2018 to only work with Visual Studio Code and PlatformIO. And have never regretted it!
All libraries can (but do not have to) be integrated into the project. In addition, the version of the ESP core can be fixed.
Such a project can easily be compiled on other computers even years later.

In addition, any other resources such as links or data sheets can be stored in the project.
It remains to be mentioned that this is a real IDE and not a better text editor.😉

Arduino sketches can also be imported. With new projects you can continue with .ino files or correctly with .h and .cpp files.
Here is one (of many) good overview and how-to for VSC with PlatformIO: https://docs.platformio.org/en/latest/integration/ide/vscode.html

## configuration
First of all it has to be determined whether the box should work as a web server or client.
### web server
- advantage:
  - No external web server / hoster required
- disadvantage:
  - The IP address can change at any time. (DHCP) It is therefore necessary to scan the QR code to access the website
  - When switching on, the standard text is always displayed
### web client
- advantage:
  - Can be reached worldwide at the same address. E.g. MyWebhoster.com/scroll
  - The last text used is reloaded when the device is switched on. 
- disadvantage:
  - Needs a web server (Rasberry Pi, NAS, Hoster) on which PHP can be run and the authorization to generate a text file.

This configuration can be made at this point in the "Wifi_Matrix_OLED.h" file. Comment out the line // or not.
`` C ++
#define IamTheServer // Enabled: act as web server; Disabled: act as client and needs a server
``

### Further required settings if configured as a client:
`` C ++
    const String pathToServer = "myHoster.com/scroll"; // For QR code
    const char * host = "myHoster.com"; // host address
    const String url = "/scroll/MeinText.txt"; // Path to the txt file
``
All fixed texts and the animations used can be adapted directly in the program.

## Installation
After the configuration has been made and the project has been loaded into the ESP, it continues as follows:
Since no WiFi data has yet been saved, the ESP automatically switches to AP mode.
A QR code is now displayed with which the settings for the AP are automatically adopted from the smartphone. (iOs and Android)
If you are then connected to the AP "Scrollbox" and have the WiFi settings open on the smartphone, the WiFi Manager's website should open automatically. If not, enter the address 192.168.4.1 in the browser. A WLAN can now be selected here and the password entered. If the log-in is correct, the ESP connects to the WiFi and starts displaying texts.

From now on, a QR code is displayed with which you can go directly to the website of the box or the remote host. As simple as that!

### Hidden commands:
- The brightness of the LED can be set with the text "Lumos = 0" to "Lumos = 15". (Without "") This value is saved.
- The WiFiManager can be reset with the text "WiFiReset". However, this is only necessary for test purposes.
   - Caution: In client mode, the text must be changed immediately after the reset, otherwise a reset will be made every time the system is started. 😒

### One last thing:
If someone can use this code for their own project, I would be happy to receive a picture of the finished object. The email address is in the code. 

