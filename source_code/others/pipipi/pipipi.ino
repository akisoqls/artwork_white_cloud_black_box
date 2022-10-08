#include <FastLED.h>

int melo =60;
int spIn = 22;
int gnd = 21;
int vout = 19;


#define NUM_LEDS 1
#define DATA_PIN 27

CRGB leds[NUM_LEDS];

void setup() {
  pinMode(spIn, OUTPUT);
  pinMode(vout, OUTPUT);
  pinMode(gnd, OUTPUT);
  digitalWrite(vout, HIGH);
  digitalWrite(gnd, LOW);

  FastLED.addLeds<SK6812, DATA_PIN, RGB>(leds, NUM_LEDS);

  int LEDcolors[] = {0x000000, 0x0000f0};

  
}
  
void loop() {
  digitalWrite(vout, HIGH);
  for(int j = 0; j<9; j++){
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
  delay(4000);
}
