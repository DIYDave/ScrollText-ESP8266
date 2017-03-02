//
// Sketch for ESP8266 MCU. d.waldesbuehl@hispeed.ch Feb. 2017
// Connect to a defined WiFi. If no known Wifi is found, AP mode will start
// Get a Textfile from Web server.
// Display various texts on the dot matrix display include the text from Web server.
// Display status information and QR-Code for de Web server path on the small OLED display.
// Upload sketch over the Air (OTA) (Needs installed Python 2.7x)
//

// Include librarys
#include <ESP8266WiFi.h>      // ESP library for all WiFi functions
#include <ArduinoOTA.h>       // Library for uploading sketch over the air (OTA)
#include <SPI.h>              // Library for hardware or software driven SPI
#include <EEPROM.h>           // Library for handle teh EEPROM
#include <MD_Parola.h>        // Parola library to scroll and display text on the display (needs MD_MAX72xx library)  https://github.com/MajicDesigns/MD_Parola
#include <MD_MAX72xx.h>       // Library to control the Maxim MAX7219 chip on the dot matrix module   https://github.com/MajicDesigns/MD_MAX72XX
#include <U8g2lib.h>          // Library to control the 128x64 Pixel OLED display with SH1106 chip  https://github.com/olikraus/u8g2
#include <DNSServer.h>        // used in AP mode (config mode) to connect direct to the web page 
#include <ESP8266WebServer.h> // used in AP mode (config mode)
#include <WiFiManager.h>      // Manage auto connect to WiFi an fall back to AP   //https://github.com/tzapu/WiFiManager
#include "pictures.h"         // Picture resources in the sketch directory

// Define global variables and const
char oledTxt[25]      = "";
uint8_t frameDelay    = 25;  // default frame delay value
uint8_t nStatus       = 0;
char curMessage[80]   = "Willkommen bei Omni Ray AG";

// Define the number of 8x8 dot matrix devices and the hardware SPI interface
#define  MAX_DEVICES 8
#define CS_PIN  D6 // or SS (CLK_PIN  D5 // or SCK ; DATA_PIN  D7 // or MOSI)

// build Instances
textEffect_t scrollEffect = PA_SCROLL_LEFT;
WiFiManager wifiManager;
MD_Parola Parola = MD_Parola(CS_PIN, MAX_DEVICES);  // HARDWARE SPI for dot matrix display
// SSoftware SPI for OLED display !CS-pin unused (connected direct to ground on OLED)
U8G2_SH1106_128X64_VCOMH0_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ D1, /* data=*/ D2, /* cs=*/ D8, /* dc=*/ D4, /* reset=*/ D3);   


void setup() // ********************* Begin of Setup
{
  Serial.begin(115200);
  EEPROM.begin(100);   
 
  // Setup and start OLED display
  u8g2.begin();   
  u8g2.clearBuffer();          // clear the internal memory
  OLED_Screen1();              // Wellcome screen
  
  // Setup and start Dot matrix display
  Parola.begin(); 
  Parola.displayClear();
  Parola.displaySuspend(false);
  byte i = EEPROM.read(0);
  Parola.setIntensity(i);       // Values from 0 to 15
  scrollEffect = (PA_SCROLL_LEFT);
  Parola.setTextEffect(scrollEffect, scrollEffect);

  // Setup and start WiFi-Manager
  wifiManager.setAPCallback(configModeCallback);   // Call routine to show infos when in Config Mode
  wifiManager.autoConnect("ScrollText");          // Name of the buil-in accesspoint
  // Loop here until connection with Wifi
  OLED_Screen2();             // Connected Screen

  // Setup and start OTA service
  ArduinoOTA.begin(); 
  
}  // ******************************  End of Setup


void loop() 
{
    ArduinoOTA.handle();
  if (Parola.displayAnimate()) // True if animation ended
  {
    switch (nStatus) {
      if (nStatus >7){nStatus ==0;}
    case 0:
      ConnectToServer();   // Get text from server
      Parola.displayText   ("Willkommen", PA_CENTER, 25, 1200, PA_OPENING_CURSOR  , PA_OPENING_CURSOR );    
      break;
    case 1:
      Parola.displayText   ("bei", PA_CENTER, 25, 1000, PA_OPENING_CURSOR  , PA_OPENING_CURSOR );
      break;    
    case 2:
      OLED_Screen3();      // Show "Scan Now" text
      Parola.displayText   ("Omni Ray AG", PA_CENTER, 25, 1500, PA_OPENING_CURSOR  , PA_OPENING_CURSOR );
      break; 
    case 3:
      Parola.displayText   ("freundlich", PA_CENTER, 40, 1200, PA_SCROLL_UP_LEFT  , PA_SCROLL_UP_RIGHT  );
      break; 
    case 4:
      drawPic();          //Show QR-Code
      Parola.displayText   ("kompetent", PA_CENTER, 50, 1200, PA_MESH  , PA_MESH );
      break; 
    case 5:
      Parola.displayText   ("dynamisch", PA_CENTER, 2, 100, PA_SLICE , PA_SLICE);
      break; 
    case 6:                // Show server text
      Parola.displayScroll(curMessage, PA_LEFT, scrollEffect, frameDelay); 
      break;     
    case 7:                // Show server text
      Parola.displayScroll(curMessage, PA_LEFT, scrollEffect, frameDelay); 
      break;     
    }
    nStatus ++;
  }
}

void ConnectToServer(){
  // Use WiFiClient class to create TCP connections
  const char* host      = "myHost.com";                 // Here coms your Webserver / Host adress
  String url            = "/myPath/myText.txt";         // The Path and Filename
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }   
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  // Read all the lines of the reply from server
  while(client.available()){
    String line = client.readStringUntil('\r');
    //Serial.print(line);                             // Diag, Show's all the lines from HTTP answere
    if(line.endsWith("EOT")){                         // line with EOT at the end? (adding in PHP-Script to the end of text)
      line = line.substring(1,line.length() -3);      // Shortens the string by by 3 characters "EOT"
      if (line == "WiFiReset"){                       // Secret phrase to reset WiFi settings. Next start in config Mode
        wifiManager.resetSettings();
      }
      if(line.startsWith("Lumos=")){                  // Secret phrase to set intensity of dot matrix
        line = line.substring(6,line.length());
        SetIntensity(line);
        return;
      }
      line.toCharArray(curMessage, sizeof(curMessage));  
    }
  }
}


void SetIntensity(String lumos ){           // Set the intensity of dot matrix. Text for Website: "Lumos=0" to "Lumos=15"
  long l = lumos.toInt();
  byte i = (byte) l;
  if ((i>=0) && (i<=15)){  //&& (i!= i2) geht nicht, Schreibt immer weil i2 von Eeprom immer 0 ?? // Values from 0 to 15
    EEPROM.write(0, i);       // Write the new value to EEPROM
    EEPROM.commit();
    Parola.setIntensity(i);   
  } 
}
  
void configModeCallback (WiFiManager *myWiFiManager) {      // Show infos to log in with build in accesspoint. (Config Mode) When not possible to connect to WiFi 
  u8g2.clearBuffer();   u8g2.drawStr(0,11,"Config Mode");   
  u8g2.drawStr(0,27,"AP: "); 
  myWiFiManager->getConfigPortalSSID().toCharArray(oledTxt, sizeof(oledTxt));
  u8g2.drawStr(28,27,oledTxt);  
  u8g2.drawStr(0,43,"IP address: ");    
  sprintf(oledTxt, "%03d.%03d.%03d.%03d", WiFi.softAPIP()[0], WiFi.softAPIP()[1], WiFi.softAPIP()[2], WiFi.softAPIP()[3]);
  u8g2.drawStr(0,59, oledTxt);  u8g2.sendBuffer(); 
}

void OLED_Screen1(){                        // Wellcome screen
  u8g2.setFont(u8g2_font_7x14B_tr);         // choose a small font for status dispay 
  u8g2.clearBuffer(); 
  u8g2.drawStr(0,11,"    Wellcome to"); 
  u8g2.setFont(u8g2_font_profont22_tf);  
  u8g2.drawStr(6,32, "ScrollText");  
  u8g2.setFont(u8g2_font_7x14B_tr); 
  u8g2.drawStr(0,48,"    Connecting.."); 
  u8g2.setFont(u8g2_font_6x10_tf); 
  u8g2.drawStr(0,64,"v1.3");  u8g2.sendBuffer(); 
}

void OLED_Screen2(){                      // Connected screen
  u8g2.setFont(u8g2_font_7x14B_tr);       // choose a small font for status dispay 
  u8g2.clearBuffer();
  u8g2.drawStr(0,11,"WiFi connected");   
  u8g2.drawStr(0,27,"SSID: ");  
  WiFi.SSID().toCharArray(oledTxt, sizeof(oledTxt));
  u8g2.drawStr(37,27,oledTxt);  
  u8g2.drawStr(0,43,"IP address: ");    
  sprintf(oledTxt, "%03d.%03d.%03d.%03d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
  u8g2.drawStr(0,59, oledTxt);  u8g2.sendBuffer();
}

void OLED_Screen3(){                        // Scan now screen
   u8g2.setFont(u8g2_font_profont22_tf);    // choose a big font for "Scan Now" text
   u8g2.clearBuffer();
   u8g2.drawStr(4,15,"QR scannen");   
   u8g2.drawStr(5,35,"-> eigener");   
   u8g2.drawStr(35,55,"Text!"); u8g2.sendBuffer();
}

void drawPic() {                          // show QR-Code
  // picture loop
  u8g2.clearBuffer();
  u8g2.firstPage();  
  do {
      u8g2.drawXBM( 0, 0, qr_code_width, qr_code_height, qr_code_bits);
  } while( u8g2.nextPage() );
}

