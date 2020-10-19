#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     8 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define UP 2
#define DOWN 3
#define LEFT 4
#define RIGHT 5
#define FUNC1 6 //left function btn
#define FUNC2 7 //right function btn

const uint8_t PROGMEM tank1[]={
   0B00000111, 0B11000110,
   0B00001000, 0B00111000,
   0B00010000, 0B00010000,
   0B11111111, 0B11111110,
   0B10000000, 0B00000001,
   0B11111111, 0B11111111,
   0B01000000, 0B00000010,
   0B00111111, 0B11111100
};
const uint8_t PROGMEM  tank2[]={
  0B01100011, 0B11100000,
  0B00011100, 0B00010000,
  0B00001000, 0B00001000,
  0B01111111, 0B11111111,
  0B10000000, 0B00000001,
  0B11111111, 0B11111111,
  0B01000000, 0B00000010,
  0B00111111, 0B11111100
};
const uint8_t PROGMEM bullet1[]={
  0B11111100,
  0B10000010,
  0B10000001,
  0B10000010,
  0B11111100
};
const uint8_t PROGMEM bullet2[]={
  0B00111111,
  0B01000001,
  0B10000001,
  0B01000001,
  0B00111111
};
int x1,x2,y1,y2;
bool hit1=false;
bool hit2=false;
bool bact1=false;
bool bact2=false;
int bx1,by1,bx2,by2;
int l1=5,l2=5;
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
  pinMode(FUNC2, INPUT);
  x1=0;
  x2=112;
  y1=16;
  y2=16;
}
int vb=4;
int rm=4;
int rp=8;
void loop() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(String(l1)+"  |  "+String(l2));
  display.drawBitmap(x1,y1,tank1,16,8,1);
  display.drawBitmap(x2,y2,tank2,16,8,1);
  if(bact1){
    display.drawBitmap(bx1,by1,bullet1,8,4,1);
    bx1+=vb;
    if(bx1>=111){
      if(!hit1 && by1<=y2+rp && by1>=y2-rm){
        l2--;
      }
      hit1=true;
      bact1=false;
    }
  }
  if(bact2){
    display.drawBitmap(bx2,by2,bullet2,8,4,1);
    bx2-=vb;
    if(bx2<=15){
      if(!hit2 && by2<=y1+rp && by2>=y1-rm){
        l1--;
      }
      hit2=true;
      bact2=false;
    }
  }
  if(digitalRead(UP)==HIGH && y1>16){
    y1--;
  }
  if(digitalRead(DOWN)==HIGH && y1<56){
    y1++;
  }
  if(digitalRead(RIGHT)==HIGH && y2>16){
    if(digitalRead(FUNC1)==HIGH){
      strzal(2);
    }else{
  	  y2--;
    }
  }
  else if(digitalRead(FUNC1)==HIGH && y2<56){
    y2++;
  }
  if(digitalRead(LEFT)==HIGH){
    strzal(1);
  }
  if(l1<=0){
    display.clearDisplay();
    display.setCursor(0,16);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.println("LEFT LOSED!");
    display.display();
    for(;;);
  }
  if(l2<=0){
    display.clearDisplay();
    display.setCursor(0,16);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.println("RIGHT LOSED!");
    display.display();
    for(;;);
  }
  display.display();
}
void strzal(int n){
  if(n==1){
    hit1=false;
    bact1=true;
    by1=y1;
    bx1=17;
  }else if(n==2){
    hit2=false;
    bact2=true;
    by2=y2;
    bx2=111;
  }  
}
