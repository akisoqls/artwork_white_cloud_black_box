int leds[]={2,3,4,5,6,7,8};

void setup() {
  for(int j = 0; j < 7; j++){
    pinMode(leds[j], OUTPUT);
  }
  Serial.begin(115200);
}

void loop() {
  while(Serial.available()){
    for(int j = 0; j < 7; j++){
      digitalWrite(leds[j], LOW);
    }
    int ledNo = Serial.read();
    Serial.println(ledNo);
    digitalWrite(leds[ledNo], HIGH);
    delay(50);
    for(int j = 0; j < 7; j++){
      digitalWrite(leds[j], LOW);
    }
  }
}
