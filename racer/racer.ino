#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     8 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define UP 2
#define DOWN 3
#define LEFT 4
#define RIGHT 5
#define FUNC1 6 //left function btn
const uint8_t PROGMEM car[]={
  0B10000001,
  0B11111111,
  0B00111100,
  0B01111110,
  0B01100110,
  0B01100110,
  0B01111110,
  0B00011000,
  0B00011000,
  0B01011010,
  0B00111100
};
int x=60;
int y=1;
int w = 8;
int h = 11;
int v = 1;
int t = 0;
int s;
int dlug = 1000;
long scrl = 0;
int near=25;
int lives=10;
int st;
int score=0;
int record=0;
int vp=1;
int cycle=0;
bool f =false;
void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  if(EEPROM.read(1022)==255){
    EEPROM.write(1022,0);
  }
  record=EEPROM.read(1022);
  display.clearDisplay();
  pinMode(UP, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(FUNC1, INPUT);
  randomSeed(random()*analogRead(A0));
  generate();
}
int cz=52;
int minn=15;
void generate(){
  scrl=0;
  for(int i=0; i<dlug; i++){
      if(cz<=15){randomSeed(random()*(analogRead(A0)+1));cz+=1;minn++;}
      if(cz>=30){minn=15;}
      cz = cz + random(-3,3);
      EEPROM.write(i,cz);
  }
  x=EEPROM.read(5)+5;
}
void loop() {
  Serial.println(String(score));
  cycle++;
  if(scrl>=dlug-65){
    generate();
    scrl=0;
  }
  display.clearDisplay();
  display.drawBitmap(x,y,car,w,h,1);
  for(int j=0; j<64; j++){
    display.fillRect(0, j, EEPROM.read(scrl+j), 1,SSD1306_WHITE);
    display.fillRect(EEPROM.read(scrl+j)+near, j, 128-(EEPROM.read(scrl+j)+25), 1,SSD1306_WHITE);
  }
  if(scrl%(15*vp)==0){
    score++;
  }
  display.setTextSize(1);
  display.setCursor(70,0); 
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.println(String(lives)+" LIVES");
  display.setCursor(70,10); 
  display.println(String(score)+" SCORE");
  display.display();
  scrl+=vp;
  if(score%30==0 &&cycle>=15){
    vp++;
    cycle=0;
  }
  //_________________________________
  //-----------LOSE------------------
  //---------------------------------
  if(x<=EEPROM.read(scrl+y) && ((int)millis()/1000)-st>=1){
    lives--;
    st=(int)millis()/1000;
  }
  if(x>=EEPROM.read(scrl+y)+near-11 && ((int)millis()/1000)-st>=1){
    lives--;
    st=(int)millis()/1000;
  }
  if(lives<=0){
    loseScreen();
  }
  //_________________________________
  //----------Controls---------------
  //---------------------------------
  if(digitalRead(LEFT)==HIGH && x>1){
    x-=v;
    if(f==false){
      s=millis()/1000;
    }
    if(millis()/1000-s>2){
      v=2;
    }
  }else if(digitalRead(RIGHT)!=HIGH){
    v=1;
    f=false;
  }
  if(digitalRead(RIGHT)==HIGH && x<127){
    x+=v;
    if(f==false){
      s=millis()/1000;
    }
    if(millis()/1000-s>2){
      v=2;
    }
  }else if(digitalRead(LEFT)!=HIGH){
    v=1;
    f=false;
  }
  delay(50);
}
void loseScreen(){
  if(score>record){
    record=score;
    EEPROM.write(1022,record);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,2);
  display.println("SCORE:"+String(score)+" RECORD:"+String(record));  
  display.setTextSize(3);
  display.setCursor(28,20);
  display.println("LOSE!");  
  display.display();
  for(int i=0; i<dlug; i++){
      EEPROM.write(i,255);
  }
  for(;;);
}
