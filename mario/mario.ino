#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     8 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define H 11
#define W 16

#define UP 2
#define DOWN 3
#define LEFT 4
#define RIGHT 5
#define FUNC1 6 //left function btn
#define FUNC2 7 //right function btn
bool serialenabled = false;
const uint8_t  PROGMEM mario[] = {
  0B00000000, 0B00111100,
  0B00000000, 0B01111110,
  0B00000000, 0B10001010,
  0B00000000, 0B10000011,
  0B00000000, 0B01111100,
  0B00000000, 0B11000110,
  0B00000001, 0B01000101,
  0B00000001, 0B01000101,
  0B00000000, 0B01111100,
  0B00000000, 0B11001100,
  0B00000000, 0B11101110
};
const uint8_t PROGMEM ground[] = {
  0B11111111,   
  0B11111111,   
  0B11111001,   
  0B00010000,   
  0B00000000,   
  0B00000000,   
  0B00000000,   
  0B00000000
};
const uint8_t PROGMEM enemy[] = {
  0B00000000,   
  0B01111110,   
  0B01000010,   
  0B01111110,   
  0B11000011,   
  0B11000011,   
  0B01111110,  
  0B01100110, 
  0B01100110  
};
const uint8_t PROGMEM enemy1[] = {
  0B00000000,   
  0B01111110,   
  0B01111110,   
  0B11000011,  
  0B01100110
};
const uint8_t PROGMEM cloud[]{
  0B01110111, 0B01110110,
  0B10001000, 0B10001001,
  0B10000000, 0B00000001,
  0B01000000, 0B00000010,
  0B10000000, 0B00000001,
  0B10000000, 0B00000001,
  0B10010001, 0B00010001,
  0B01101110, 0B11101110
};
int x=30;
int y=45;
int scrl=0;
int jl=0;
bool jumping=false;
bool good=true;
int jumpmight=5;
int lives = 5;
int ex = 128;
int od = 0;
int c = 0;
int ms = 50;
unsigned long klik = 0;
int score = 0;
int m=1;
int ey=51;
int ods[10];
int record;
void setup() {
  record=EEPROM.read(0);
  if(record==255){
    EEPROM.write(0,0);
    record=0;
  }
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    if(serialenabled)
      Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  for(int i=0; i<10; i++){
    ods[i]=random(-10,10);
  }
  display.clearDisplay();
  pinMode(UP, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
}
void loop() {
  if(serialenabled)
    Serial.println(String(scrl));
  c++;
  //Serial.println(x);
  if(m==2){
    ey++;
  }else{
    ey=51;
  }
  if(jumping==true){ex-=2;}else{ex--;}
  if(jumping==true){
    jump();
  }
  if(ex>=37 && ex<=40 && jumping==false && c==3){
    good=false;
  }else if(ex>=34 && ex<=40 && c==3 && jumping==true){
    m=2;
  }
  if(good==true && (ex<=-20)){
    score++;
  }
  if(good==false && (ex==-20 || ex==-21)){
    lives--;
    good=true;
  }
  if(ex<=-20 || ey>=128){
    ex=110;
    m=1;
  }
  if(c==3){
    c=0;
  }
  if(lives<=0){
    lose();
  }
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("LIVES: "+leftalign(String(lives), 1)+" SCORE: "+String(score));  
  display.drawBitmap(x,y,mario,W,H,1);
  if(m==1){
    display.drawBitmap(ex,47,enemy,8,9,1);
  }else if(m==2){
    display.drawBitmap(ex,ey,enemy1,8,5,1);
  }
  for(int i=0; i<20; i++){
    display.drawBitmap(8*i-(scrl%8)-16,56,ground,8,8,1);
  }
  for(int i=0; i<10; i++){
    display.drawBitmap((50+ods[i])*i-scrl-30,16+random(0,1),cloud,16,8,1);
  }
//  for(int i=0; i<n; i++){
//    display.drawBitmap(8*i-scrl+8*5,24,block,8,8,1);
//  }
  display.display();
  if(digitalRead(UP)==HIGH && jumping==false && (millis()-klik)>1000){
    klik=0;
    jump();
  }
  if(digitalRead(LEFT)==HIGH){
    scrl--;
  }
  if(digitalRead(RIGHT)==HIGH){
    scrl++;
  }
  display.clearDisplay();
}
String leftalign(String txt, int szer){
    String ret;
    for(int i=0; i<szer-txt.length(); i++){
        ret = ret + " ";
    }
    ret = ret + txt;
    return ret;
}
void jump(){
  klik = millis();
  if(jl==0){
  jumping=true;
  y-=jumpmight;
  delay(ms);
  display.clearDisplay();
  display.drawBitmap(x,y,mario,W,H,1);
  jl+=1;}
  else if(jl==1){
  y-=jumpmight;
  delay(ms);
  display.clearDisplay();
  display.drawBitmap(x,y,mario,W,H,1);jl++;}
  else if(jl==2){
  y-=jumpmight;
  delay(ms);
  display.clearDisplay();
  display.drawBitmap(x,y,mario,W,H,1);jl++;}
  else if(jl==3){
  y-=jumpmight;
  delay(ms);
  display.clearDisplay();
  display.drawBitmap(x,y,mario,W,H,1);jl++;}
  else if(jl==4){
  y+=jumpmight;
  delay(ms);
  display.clearDisplay();
  display.drawBitmap(x,y,mario,W, H,1);jl++;}
  else if(jl==5){
  y+=jumpmight;
  delay(ms);
  display.clearDisplay();
  display.drawBitmap(x,y,mario,W,H,1);jl++;}
  else if(jl==6){
  y+=jumpmight;
  delay(ms);
  display.clearDisplay();
  display.drawBitmap(x,y,mario,W,H,1);jl++;}
  else if(jl==7){
  y+=jumpmight;
  delay(ms);
  display.clearDisplay();
  display.drawBitmap(x,y,mario,W,H,1);jl=0;
  delay(100);
  jumping=false;}
}
void lose(){
  if(score>record){
    record=score;
    EEPROM.write(0,record);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,2);
  display.println("SCORE:"+String(score)+" RECORD:"+String(record));  
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(28,20);
  display.println("LOSE!");  
  display.display();
  for(;;);
}
