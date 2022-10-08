#include <M5Stack.h>

void setup()
{
    M5.begin();
    M5.Speaker.setVolume(10);
    for(int i=0; i<2; i++){
      M5.Speaker.beep();
      digitalWrite(22, 1);
      delay(10);
      M5.Speaker.mute();
      digitalWrite(22, 0);
      delay(100);
    }
}

void loop(){
  delay(1000);
  for(int i=0; i<7; i++){
    M5.Speaker.beep();
    digitalWrite(22, 1);
    delay(10);
    M5.Speaker.mute();
    digitalWrite(22, 0);
    delay(100);
    Serial.println("sound");
  }
}
