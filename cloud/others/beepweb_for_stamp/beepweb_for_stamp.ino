
#include <WiFi.h>
#include <FastLED.h>

int melo =60;
int spIn = 25;
int gnd = 22;
int vout = 21;

#define NUM_LEDS 1
#define DATA_PIN 27

CRGB leds[NUM_LEDS];


const char* ssid     = "nyago";
const char* password = "88888888";

int port = 80;


const IPAddress ip(192,168,101,4);
const IPAddress subnet(255,255,255,0);

WiFiServer server(port);

void setup()
{

    pinMode(spIn, OUTPUT);
    pinMode(vout, OUTPUT);
    pinMode(gnd, OUTPUT);
    digitalWrite(vout, HIGH);
    digitalWrite(gnd, LOW);

    FastLED.addLeds<SK6812, DATA_PIN, RGB>(leds, NUM_LEDS);
    
    Serial.begin(115200);
    delay(10);

    if (!WiFi.config(ip,ip,subnet)){
       Serial.println("Failed to configure");
    }

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("port: ");
    Serial.println(port);
    
    server.begin();

    for(int i=0; i<2; i++){
      for(uint16_t count=0; count<30; count++){
        digitalWrite(spIn, HIGH);
        delayMicroseconds(460);
        digitalWrite(spIn, LOW);
        delayMicroseconds(460);
      }
      leds[0] = 0xff0000;
      FastLED.show();
      delay(50);
      leds[0] = 0x000000;
      FastLED.show();
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
            client.print(R"(<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>server</title>
</head>
<body>
  <p>サーバーはここにあります。</p>
  <iframe src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d810.9185258902014!2d139.3506306292486!3d35.61110478906517!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x0%3A0x9d08cbbc65f82e69!2zMzXCsDM2JzQwLjAiTiAxMznCsDIxJzA0LjIiRQ!5e0!3m2!1sja!2sjp!4v1662511592676!5m2!1sja!2sjp" width="400" height="300" style="border:0;" allowfullscreen="" loading="lazy" referrerpolicy="no-referrer-when-downgrade"></iframe>
</body>
</html>)");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:

            Serial.println("New Client.");           // print a message out the serial port
            for(int i=0; i<7; i++){
              for(uint16_t count=0; count<30; count++){
                digitalWrite(spIn, HIGH);
                delayMicroseconds(460);
                digitalWrite(spIn, LOW);
                delayMicroseconds(460);
              }
              leds[0] = 0x88ff00;
              FastLED.show();
              delay(50);
              leds[0] = 0x000000;
              FastLED.show();
            }
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
          
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /is-existence")) {
           M5.Speaker.setBeep(1000,10000);
           M5.Speaker.setVolume(10);
           for(int i=0; i<3; i++){
              M5.Speaker.beep();
              digitalWrite(22, 1);
              delay(200);
              M5.Speaker.mute();
              digitalWrite(22, 0);
              delay(10);
            }
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
