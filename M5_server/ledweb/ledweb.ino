/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with STAMP-PICO sample source code
*                          配套  STAMP-PICO 示例源代码
* Visit the website for more information：https://docs.m5stack.com/en/core/stamp_pico
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/core/stamp_pico
*
* describe: FastLED.
* date：2021/9/19
*******************************************************************************
*/
#include "Arduino.h"
#include <FastLED.h>
#include <WiFi.h>

// How many leds in your strip?
#define NUM_LEDS 1
#define DATA_PIN 27

const char* ssid = "Buffalo-G-AC60";
const char* password = "cdexkwbkmpv43";

WiFiServer server(80);
// Define the array of leds
CRGB leds[NUM_LEDS];

/* After STAMP-PICO is started or reset
  the program in the setUp () function will be run, and this part will only be run once.
  在 STAMP-PICO 启动或者复位后，即会开始执行setup()函数中的程序，该部分只会执行一次。 */
void setup() {
  FastLED.addLeds<SK6812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical

  delay(10);

  WiFi.begin(ssid, password);
  Serial.begin(115200);
  int LEDcolors[] = {0xf00000, 0x0000f0};
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    leds[0] = LEDcolors[i%2];
    FastLED.show();
    i++;
  }

  Serial.println(WiFi.localIP());

  server.begin();
}

/* After the program in setup() runs, it runs the program in loop()
The loop() function is an infinite loop in which the program runs repeatedly
在setup()函数中的程序执行完后，会接着执行loop()函数中的程序
loop()函数是一个死循环，其中的程序会不断的重复运行 */
void loop() {

  WiFiClient client = server.available();  // listen for incoming clients

  if (client) {  // if you get a client,
    for (int i = 0; i < 7; i++) {
      leds[0] = 0xf08000;
      FastLED.show();
      delay(100);
      leds[0] = 0x00f080;
      FastLED.show();
      delay(100);
    }
    String currentLine = "";      // make a String to hold incoming data from the client
    while (client.connected()) {  // loop while the client's connected

      if (client.available()) {  // if there's bytes to read from the client,
        char c = client.read();  // read a byte, then
        Serial.write(c);         // print it out the serial monitor
        if (c == '\n') {
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("<h1><a href=\"/H\">click here</a></h1>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {  // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // close the connection:
    client.stop();
  }
}
