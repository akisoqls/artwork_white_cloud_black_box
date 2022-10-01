/*
 * 74HC595
 * SER : 2
 * OE : GND
 * RCLK : 3
 * SRCLK : 4
 * SRCLR : 5
 */

int const SER = 2;
int const RCLK = 3;
int const SRCLK = 4;
int const SRCLR = 5;

int spIn = 11;

void setup() {
  pinMode(SER, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);
  pinMode(SRCLR, OUTPUT);  

  pinMode(spIn, OUTPUT);

  //初期化
  digitalWrite(SRCLR, LOW);
  digitalWrite(SRCLR, HIGH);

  Serial.begin(9600);
}

void loop() {

    //光らせるLEDの選択
//    int i = B01000111;
    int leds[7] = {
      B01000000,
      B00100000,
      B00010000,
      B00001000,
      B00000100,
      B00000010,
      B00000001,
    };

    //初期化
    digitalWrite(SRCLR, LOW);  
    digitalWrite(SRCLR, HIGH);  


//    for(int j=0; j < 7; j++){
      for(int i=0; i<7; i++){
        digitalWrite(RCLK, LOW);
        shiftOut(SER, SRCLK, LSBFIRST, leds[i]);
        digitalWrite(RCLK, HIGH);
        Serial.println(leds[i % sizeof leds]);
        for(uint16_t count=0; count<30; count++){
          digitalWrite(spIn, HIGH);
          delayMicroseconds(460);
          digitalWrite(spIn, LOW);
          delayMicroseconds(460);
        }
        delay(50);
      }
      digitalWrite(RCLK, LOW);
      shiftOut(SER, SRCLK, LSBFIRST, B00000000);
      digitalWrite(RCLK, HIGH);
      delay(100);
//    }
    delay(1900);



//    for(int i=0; i<7; i++){
//      for(uint16_t count=0; count<30; count++){
//        digitalWrite(spIn, HIGH);
//        delayMicroseconds(460);
//        digitalWrite(spIn, LOW);
//        delayMicroseconds(460);
//      }
//      delay(50);
//    }

}
