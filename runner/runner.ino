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
const unsigned char runner0 [] PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x38, 0x00, 0x00, 0x30, 0x00, 0x00, 0x20, 0x00, 0x01, 0xe0, 0x00, 0x07, 0xf0, 0x00, 0x07, 0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x0d, 0xf1, 0x00, 0x0d, 0xf9, 0x00, 0x01, 0xff, 0x00, 0x01, 0xc2, 0x00, 0x03, 0x80, 0x00, 0x07, 0x80, 0x00, 0x07, 0x80, 0x00, 0x07, 0x80, 0x00, 0x07, 0xc0, 0x00, 0x07, 0xc0, 0x00, 0x0f, 0xe0, 0x00, 0x0c, 0x70, 0x00, 0x0c, 0x70, 0x00, 0x0c, 0x38, 0x00, 0x08, 0x38, 0x00, 0x38, 0x60, 0x00, 0x30, 0xc0, 0x00, 0x21, 0x00, 0x00, 0x43, 0x00, 0x00, 0x41, 0x00, 0x00, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00};
const unsigned char runner1 [] PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x38, 0x00, 0x00, 0x30, 0x00, 0x00, 0x20, 0x00, 0x01, 0xe0, 0x00, 0x07, 0xf0, 0x00, 0x07, 0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x0d, 0xf1, 0x00, 0x0d, 0xf9, 0x00, 0x09, 0xff, 0x00, 0x09, 0xc2, 0x00, 0x03, 0x80, 0x00, 0x03, 0x80, 0x00, 0x07, 0x80, 0x00, 0x07, 0x80, 0x00, 0x07, 0xc0, 0x00, 0x03, 0xc0, 0x00, 0x03, 0xe0, 0x00, 0x03, 0xc0, 0x00, 0x03, 0xc0, 0x00, 0x07, 0xe0, 0x00, 0x07, 0x60, 0x00, 0x07, 0x40, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00};
const unsigned char runner2 [] PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x38, 0x00, 0x00, 0x30, 0x00, 0x00, 0x20, 0x00, 0x01, 0xe0, 0x00, 0x07, 0xf0, 0x00, 0x07, 0xf0, 0x00, 0x0f, 0xf0, 0x00, 0x0d, 0xf1, 0x00, 0x0d, 0xf9, 0x00, 0x01, 0xff, 0x00, 0x01, 0xc2, 0x00, 0x03, 0x80, 0x00, 0x07, 0x80, 0x00, 0x07, 0x80, 0x00, 0x07, 0x80, 0x00, 0x07, 0xc0, 0x00, 0x07, 0xc0, 0x00, 0x0f, 0xe0, 0x00, 0x0e, 0x60, 0x00, 0x0e, 0x60, 0x00, 0x07, 0x60, 0x00, 0x07, 0x20, 0x00, 0x0c, 0x38, 0x00, 0x18, 0x18, 0x00, 0x20, 0x08, 0x00, 0x60, 0x04, 0x00, 0x20, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x02, 0x00, 0x00, 0x02, 0x00};
bool jump=false;
int a=0;
unsigned long t=0;
unsigned long x=0;
int xd=0;
int y=0;
bool b=false;
bool lvl[512];
int szer=10;
void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  pinMode(UP, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(FUNC1, INPUT);
  for(int i=0; i<512; i++){
    if(random(0,5)<=2){
      lvl[i]=true;
    }else{
      lvl[i]=false;
    }
  }
}
void loop() {
  x+=1;
  if(x%szer==0){
    xd++;
  }
  display.clearDisplay();
  display.setCursor(0,17);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  //display.println("hello world");
  display.drawLine(0,48,128,48,WHITE);
  if(a==0){
    display.drawBitmap(20,16-y,runner0,21,32,1);
  }else if(a==1){
    display.drawBitmap(20,16-y,runner1,21,32,1);
  }else if(a==2){
    display.drawBitmap(20,16-y,runner2,21,32,1);
  }else if(a==3){
    display.drawBitmap(20,16-y,runner1,21,32,1);
  }
  draw();
  display.display();
  if(millis()-t>70){
    if(a<3){
    a++;
    }else{
      a=0;
    }
    t=millis();
  }
  if(digitalRead(UP)){
    jump=true;
  }
  if(jump==true){
    if(y<15 && !b){
      y+=2;
    }else if(y>=15){
      b=true;
    }
    if(b){
      y-=2;
    }
    if(y<1){
      y=0;
      jump=false;
      b=false;
    }
  }
}
void draw(){
  for(int i=0; i<int(128/szer); i++){
    if(lvl[xd+i]){
      int eax=i*szer-(x%szer);
      display.fillRect(eax,38,szer,10,WHITE);
    }
  }
}
