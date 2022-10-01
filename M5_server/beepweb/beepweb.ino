/*
 WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 5.

 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * WiFi shield attached
 * LED attached to pin 5

 created for arduino 25 Nov 2012
 by Tom Igoe

ported for sparkfun esp32 
31.01.2017 by Jan Hendrik Berlin
 
 */

#include <WiFi.h>
#include <M5Stack.h>

File logfile;

const char* ssid     = "nyago";
const char* password = "88888888";

int port = 80;

const IPAddress ip(192,168,101,4);
const IPAddress subnet(255,255,255,0);

WiFiServer server(port);

void setup()
{


    M5.begin();
    pinMode(22, OUTPUT);
    
    Serial.begin(115200);
    pinMode(5, OUTPUT);      // set the LED pin mode

    delay(10);

    // We start by connecting to a WiFi network

    M5.Lcd.println();
    M5.Lcd.println();
    M5.Lcd.print("Connecting to ");
    M5.Lcd.println(ssid);

    if (!WiFi.config(ip,ip,subnet)){
       Serial.println("Failed to configure");
    }

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    M5.Lcd.println("");
    M5.Lcd.println("WiFi connected.");
    M5.Lcd.print("IP address: ");
    M5.Lcd.println(WiFi.localIP());
    M5.Lcd.print("port: ");
    M5.Lcd.println(port);
    
    server.begin();

    for(int i=0; i<2; i++){
      M5.Speaker.beep();
      digitalWrite(22, 1);
      delay(10);
      M5.Speaker.mute();
      digitalWrite(22, 0);
      delay(100);
    }
}

int value = 0;

void loop(){
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("<h1>hi!</h1>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:

             M5.Lcd.println("New Client.");           // print a message out the serial port
    
            
            M5.Speaker.setBeep(1000,10000);
            M5.Speaker.setVolume(10);
            for(int i=0; i<7; i++){
              M5.Speaker.beep();
              digitalWrite(22, 1);
              delay(10);
              M5.Speaker.mute();
              digitalWrite(22, 0);
              delay(100);
              Serial.println("sound");
            }
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
          
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
//        if (currentLine.endsWith("GET /H")) {
//           M5.Speaker.setBeep(1000,10000);
//           M5.Speaker.setVolume(10);
//           for(int i=0; i<3; i++){
//              M5.Speaker.beep();
//              digitalWrite(22, 1);
//              delay(200);
//              M5.Speaker.mute();
//              digitalWrite(22, 0);
//              delay(10);
//            }
//        }
      }
    }
    // close the connection:
    client.stop();
    M5.Lcd.println("Client Disconnected.");
  }
}
