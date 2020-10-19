#include <EEPROM.h>
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
//bitmaps
// 'tree', 16x20px
#define width 16
#define height 20
#define player0width 7
#define player0height 8
#define itemwidth 12
#define itemheight 8
#define enemywidth 10
#define enemyheight 15
const unsigned char logo [] PROGMEM =   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x52, 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0xa8, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0xaa, 0xb4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0xaa, 0xb4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x8a, 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x8a, 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0xc1, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00,  0x00, 0x00, 0xe8, 0x00, 0xc0, 0x1e, 0x67, 0xb3, 0xcf, 0x3e, 0x3e, 0x79, 0xe0, 0x18, 0x00, 0x00,  0x00, 0x00, 0xf8, 0x00, 0xc0, 0x1e, 0x67, 0xb3, 0xcf, 0x3e, 0x3e, 0x79, 0xe0, 0x18, 0x00, 0x00,  0x00, 0x00, 0xf8, 0x00, 0xc0, 0x1e, 0x67, 0xb3, 0xcf, 0x3e, 0x3e, 0x79, 0xe0, 0x18, 0x00, 0x00,  0x00, 0x00, 0xc0, 0x30, 0x7f, 0x1e, 0x67, 0xf9, 0xce, 0x3e, 0x0e, 0x61, 0xf0, 0x18, 0x00, 0x00,  0x00, 0x00, 0xc0, 0x7c, 0x7f, 0x1e, 0x67, 0xf9, 0xce, 0x3e, 0x0e, 0x61, 0xf0, 0x18, 0x00, 0x00,  0x00, 0x0f, 0xfe, 0x7e, 0x3f, 0x9e, 0x67, 0xdd, 0xde, 0x0e, 0x0e, 0x60, 0x10, 0x18, 0x00, 0x00,  0x00, 0x0f, 0xfe, 0x3e, 0x3f, 0x9e, 0x67, 0xdd, 0xde, 0x0e, 0x0e, 0x60, 0x10, 0x18, 0x00, 0x00, 0x00, 0x33, 0xf9, 0xe4, 0x01, 0xde, 0x67, 0x81, 0xf8, 0x0e, 0x0f, 0x41, 0xf0, 0x18, 0x00, 0x00,  0x00, 0x33, 0xf9, 0xc0, 0x01, 0xde, 0x67, 0x81, 0xf8, 0x0e, 0x0f, 0x41, 0xf0, 0x18, 0x00, 0x00,  0x00, 0x03, 0xf9, 0x80, 0x41, 0xde, 0xe7, 0x80, 0x78, 0x0e, 0x07, 0x43, 0x10, 0x18, 0x00, 0x00, 0x00, 0x03, 0xf8, 0x00, 0x41, 0xde, 0xe7, 0x80, 0x78, 0x0e, 0x07, 0x43, 0x10, 0x18, 0x00, 0x00,  0x00, 0x03, 0x38, 0x00, 0x7f, 0x9f, 0xe7, 0x80, 0x70, 0x3f, 0x87, 0x83, 0xf0, 0x7e, 0x00, 0x00,  0x00, 0x03, 0x38, 0x00, 0x7f, 0x9f, 0xe7, 0x80, 0x70, 0x3f, 0x87, 0x83, 0xf0, 0x7e, 0x00, 0x00,  0x00, 0x03, 0x38, 0x00, 0x3f, 0x07, 0xe7, 0x80, 0x30, 0x3f, 0x81, 0x80, 0xe0, 0x7e, 0x00, 0x00,  0x00, 0x03, 0x38, 0x00, 0x3f, 0x07, 0xe7, 0x80, 0x30, 0x3f, 0x81, 0x80, 0xe0, 0x7e, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0x3f, 0x07, 0xe7, 0x80, 0x30, 0x3f, 0x81, 0x80, 0xe0, 0x7e, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x08, 0x4b, 0xa2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x08, 0x63, 0x30, 0x00,  0x00, 0x08, 0x6a, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x88, 0x94, 0xa8, 0x00,  0x00, 0x2a, 0x5b, 0xa2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x48, 0x97, 0xa8, 0x00, 0x00, 0x1c, 0x4a, 0x2a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x08, 0x94, 0xa8, 0x00,0x00, 0x08, 0x4b, 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0e, 0x64, 0xb0, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const unsigned char foodbmp [] PROGMEM ={0xc4, 0x8a, 0xca, 0x84, 0x4c, 0xaa, 0xaa, 0x4c};
const unsigned char tree0 [] PROGMEM =  {0x03, 0xe0, 0x0c, 0x18, 0x10, 0x08, 0x30, 0x4c, 0x20, 0x04, 0x25, 0x04, 0x20, 0x04, 0x23, 0x24, 0x33, 0x04, 0x18, 0x0c, 0x0c, 0x58, 0x0d, 0x30, 0x07, 0xe0, 0x0c, 0x40, 0x08, 0x80, 0x08, 0x80, 0x08, 0x80, 0x08, 0x80, 0x10, 0xc0, 0x30, 0x60};
const unsigned char player0 [] PROGMEM ={0x18, 0x18, 0x10, 0x7c, 0xba, 0x38, 0x28, 0x28};
const unsigned char player1 [] PROGMEM ={0x18, 0x1a, 0x12, 0x7e, 0xba, 0x3a, 0x28, 0x28};
const unsigned char rock0 [] PROGMEM =  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x02, 0x40, 0x06, 0x60, 0x04, 0x2c, 0x0c, 0x34, 0x18, 0x0c, 0x16, 0x5c, 0x16, 0x44, 0x10, 0xc4, 0x30, 0x04, 0x20, 0x06, 0x7f, 0xe3};
const unsigned char grass0 [] PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x01, 0x90, 0x11, 0x30, 0x19, 0x24, 0x09, 0x24, 0x4b, 0x2c, 0x6a, 0x28, 0x2a, 0x28, 0x2a, 0x68, 0x2a, 0x48, 0x1a, 0x48, 0x1a, 0x58, 0x1a, 0x50, 0x16, 0xd0, 0x16, 0xb0, 0x17, 0xa0, 0x1f, 0xe0};
const unsigned char bush0 [] PROGMEM =  {0x00, 0x00, 0x03, 0xf8, 0x0c, 0x0c, 0x18, 0x06, 0x30, 0x02, 0x26, 0x03, 0x24, 0x01, 0x20, 0x01, 0x60, 0x01, 0x40, 0x01, 0x40, 0x01, 0x40, 0x01, 0x40, 0x03, 0x40, 0x02, 0x40, 0x02, 0x60, 0x02, 0x20, 0x02, 0x20, 0x02, 0x20, 0x02, 0x30, 0x06};
const unsigned char bush1 [] PROGMEM =  {0x00, 0x00, 0x03, 0xf8, 0x0c, 0x0c, 0x18, 0x06, 0x30, 0x62, 0x20, 0x63, 0x23, 0x01, 0x23, 0x01, 0x60, 0x31, 0x40, 0x31, 0x40, 0x01, 0x4c, 0x01, 0x4c, 0x03, 0x40, 0xc2, 0x40, 0xc2, 0x60, 0x32, 0x26, 0x32, 0x26, 0x02, 0x20, 0x02, 0x30, 0x06};
const unsigned char loading [] PROGMEM ={0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0xe3, 0x8e, 0x00, 0x00, 0xe0, 0x0e, 0x00, 0x00, 0xe0, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x1c, 0x70, 0x00, 0x00, 0x1c, 0x70, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x00, 0x03, 0x80, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x4c, 0xa4, 0xc0, 0x8a, 0xaa, 0x35, 0x00, 0x8a, 0xea, 0xad, 0x60, 0x8a, 0xaa, 0xa5, 0x20, 0xe4, 0xac, 0xa4, 0xd5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const unsigned char hand0 [] PROGMEM =  {0x1f, 0x00, 0x30, 0x80, 0xe3, 0xc0, 0x00, 0x20, 0x03, 0xc0, 0xe0, 0x20, 0x1f, 0xc0, 0x00, 0x00};
const unsigned char axe0 [] PROGMEM =   {0x02, 0x00, 0x0f, 0xe0, 0x06, 0x20, 0x0e, 0x40, 0x1a, 0x80, 0x33, 0x00, 0x60, 0x00, 0x40, 0x00};
const unsigned char sword0 [] PROGMEM = {0x00, 0x00, 0x30, 0x00, 0x10, 0x00, 0x9f, 0xe0, 0xff, 0xf0, 0x9f, 0xe0, 0x10, 0x00, 0x30, 0x00};
const unsigned char pick0 [] PROGMEM =  {0x1f, 0xc0, 0x0c, 0xc0, 0x03, 0x40, 0x07, 0x40, 0x0c, 0xc0, 0x18, 0xc0, 0x30, 0x40, 0x30, 0x00};
const unsigned char berry0 [] PROGMEM = {0x00, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x12, 0x00, 0x27, 0x00, 0x77, 0x00, 0x77, 0x00, 0x70, 0x00};
const unsigned char stone0 [] PROGMEM = {0x04, 0x00, 0x0e, 0x00, 0x3a, 0x00, 0x63, 0x80, 0xc0, 0x80, 0x92, 0xc0, 0x80, 0x40, 0xff, 0xc0};
const unsigned char stick0 [] PROGMEM = {0x00, 0xe0, 0x01, 0xc0, 0x03, 0x80, 0x07, 0x00, 0x0e, 0x00, 0x1c, 0x00, 0x38, 0x00, 0x70, 0x00};
const unsigned char apple0 [] PROGMEM = {0x02, 0x00, 0x04, 0x00, 0x7f, 0xc0, 0x84, 0x20, 0x80, 0x20, 0x40, 0x40, 0x20, 0x80, 0x1f, 0x00};
const unsigned char seedling0[] PROGMEM={0x00, 0x00, 0x0f, 0x00, 0x11, 0x80, 0x14, 0x80, 0x09, 0x00, 0x06, 0x00, 0x06, 0x00, 0x0f, 0x00};
const unsigned char wheat0 [] PROGMEM = {0x59, 0x20, 0x49, 0x60, 0x6d, 0x40, 0x25, 0x40, 0x15, 0x60, 0x3f, 0xe0, 0x15, 0x40, 0x15, 0x40};
const unsigned char iron0 [] PROGMEM =  {0x59, 0x20, 0x56, 0xb0, 0x5a, 0xa0, 0x55, 0x20, 0x00, 0x00, 0x3f, 0xc0, 0x20, 0x40, 0x3f, 0xc0};
const unsigned char gold0 [] PROGMEM =  {0x4a, 0xc0, 0x96, 0xa0, 0xb6, 0xa0, 0x4b, 0xc0, 0x00, 0x00, 0x3f, 0xc0, 0x3f, 0xc0, 0x3f, 0xc0};
const unsigned char meat0 [] PROGMEM =  {0x45, 0x80, 0x6d, 0x00, 0x55, 0x80, 0x45, 0x00, 0x21, 0x80, 0x57, 0x00, 0x72, 0x00, 0x52, 0x00};
const unsigned char enemy0 [] PROGMEM = {0x41, 0x00, 0x41, 0x00, 0x7f, 0x00, 0x7f, 0x00, 0x5d, 0x00, 0x7f, 0x00, 0x36, 0x00, 0x14, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x1c, 0x00, 0x1c, 0x00, 0x14, 0x00, 0x14, 0x00};
const unsigned char enemy1 [] PROGMEM = {0x41, 0x00, 0x41, 0x00, 0x7f, 0x00, 0x7f, 0x00, 0x5d, 0x00, 0x7f, 0x00, 0x36, 0x00, 0x14, 0x80, 0x9c, 0xc0, 0xc1, 0x80, 0x7f, 0xc0, 0x1c, 0x00, 0x1c, 0x00, 0x14, 0x00, 0x14, 0x00};

#define BERRY    1021
#define STONE    1020
#define STICK    1019
#define APPLE    1018
#define SEEDLING 1017
#define WHEAT    1016
#define MEAT     1015
#define IRON     1014
#define GOLD     1013
#define AXE      1010
#define SWORD    1009
#define PICK     1008
int8_t x;
int8_t y;
int8_t lives;
int8_t food;
unsigned long times=0;
unsigned long times1=0;
unsigned long times2=0;
unsigned long times3=0;
unsigned long times4=0;
unsigned long times5=0;
struct Enemy{
  int8_t x;
  int8_t y;
  int8_t lives;
  int8_t texture;
  int8_t attack;
  bool active;
};
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
  display.setTextColor(WHITE);
  display.cp437(true);   
  randomSeed(analogRead(0));
  x=EEPROM.read(1023);
  y=EEPROM.read(1022);
  lives=EEPROM.read(1012);
  food=EEPROM.read(1011);
  times2=millis();
}
int8_t xm=0;
int8_t ym=0;
bool menu=false;
int8_t speed0=1;
bool paused=false;
int8_t opt=1;
int8_t inhand=0; 
int8_t progress=0;
int xy;
int8_t opt1=0;
int8_t opt2=0;
Enemy e1;
Enemy e2;
void loop() {
  display.clearDisplay();
  if(menu){//game---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    drawTerrain();
    entities();
    if(inhand==0)
      display.drawBitmap(60,28,player0,player0width,player0height,1);
    else
      display.drawBitmap(60,28,player1,player0width,player0height,1);
    //menu
    display.fillRect(0,0,128,8,BLACK);
    display.setCursor(0,0);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.write(3);
    display.setCursor(6,0);
    display.println(String(lives));
    display.drawBitmap(23,0,foodbmp,7,8,1);
    display.setCursor(31,0);
    display.println(String(food));
    display.drawLine(37,0,37,7,1);//39,0
    if(inhand==0){////////////////////////////////////////////////
      display.drawBitmap(39,0,hand0,itemwidth,itemheight,1);
    }else if(inhand==1){
      display.drawBitmap(39,0,axe0,itemwidth,itemheight,1);
    }else if(inhand==2){
      display.drawBitmap(39,0,sword0,itemwidth,itemheight,1);
    }else if(inhand==3){
      display.drawBitmap(39,0,pick0,itemwidth,itemheight,1);
    }else if(inhand==4){
      display.drawBitmap(39,0,berry0,itemwidth,itemheight,1);
    }else if(inhand==5){
      display.drawBitmap(39,0,stone0,itemwidth,itemheight,1);
    }else if(inhand==6){
      display.drawBitmap(39,0,stick0,itemwidth,itemheight,1);
    }else if(inhand==7){
      display.drawBitmap(39,0,apple0,itemwidth,itemheight,1);
    }else if(inhand==8){
      display.drawBitmap(39,0,seedling0,itemwidth,itemheight,1);
    }else if(inhand==9){
      display.drawBitmap(39,0,wheat0,itemwidth,itemheight,1);
    }else if(inhand==10){
      display.drawBitmap(39,0,meat0,itemwidth,itemheight,1);
    }else if(inhand==11){
      display.drawBitmap(39,0,iron0,itemwidth,itemheight,1);
    }else if(inhand==12){
      display.drawBitmap(39,0,gold0,itemwidth,itemheight,1);
    }/////////////////////////////////////////////////////////////
    // teraz display.setCursor(52,0);
    ////////////////////////////////////////////////////////////
    if(millis()-times2>100000 && food>0){
      times2=millis();
      food--;
      EEPROM.write(1011,food);
    }
    if(food==0 && lives>0){
      lives--;
      EEPROM.write(1012,lives);
    }
    if(lives<=0){
      lose();
    }
    if(random(0,3)==2 && !e1.active){
      e1.lives=random(30,150);
      e1.texture=1;
      e1.attack=random(9,30);
      e1.active=true;
      e1.x=random(-30,150);
      if(random(0,1)==0){
        e1.y=-11;
      }else{
        e1.y=65;
      }
    }
    if(random(0,3)==1 && !e2.active){
      e2.lives=random(30,180);
      e2.texture=1;
      e2.attack=random(9,30);
      e2.active=true;
      e2.x=random(-30,150);
      if(random(0,1)==0){
        e2.y=-11;
      }else{
        e2.y=65;
      }
    }
    ////////////////////////////////////////////////
    if(b(UP)){
      if(b(DOWN)){
        openi();
      }else if(y>0){
        ym-=speed0;
      }
    }
    if(b(DOWN)){
      if(b(UP)){
        openi();
      }else if(y<32){
        ym+=speed0;
      }
    }
    if(b(LEFT)){
      if(b(RIGHT)){
        paused=true;
      }else if(x>0){
        xm-=speed0;
      }
    }
    if(b(RIGHT)){
      if(b(LEFT)){
        paused=true;
      }else if(x<32){
        xm+=speed0;
      }
    }
    if(xm<0){
      x--;
      xm=20;
    }
    if(ym<0){
      y--;
      ym=20;
    }
    if(xm>20){
      x++;
      xm=0;
    }
    if(ym>20){
      y++;
      ym=0;
    }
    if(b(FUNC1)){/////////////////////////////////////////////////
      if(e1.x>60 && e1.x<67 && e1.y>28 && e1.y<36 && millis()-times3>=100){
        if(inhand==0 || inhand>3){
          e1.lives-=2;
        }else if(inhand==1){
          e1.lives-=10;
        }else if(inhand==2){
          e1.lives-=15;
        }else if(inhand==3){
          e1.lives-=random(5,8);
        }
        times3=millis();
      }else if(e2.x>60 && e2.x<67 && e2.y>28 && e2.y<36 && millis()-times3>=100){
        if(inhand==0 || inhand>3){
          e1.lives-=2;
        }else if(inhand==1){
          e1.lives-=10;
        }else if(inhand==2){
          e1.lives-=15;
        }else if(inhand==3){
          e1.lives-=random(5,8);
        }
        times3=millis();
      }else{
        if(progress==0){
          progress++;
        }else if(progress==10){
          int8_t item = EEPROM.read(xy);
          progress=0;
          if(item==4){
            EEPROM.write(xy,5);
            if(EEPROM.read(BERRY)>249){
              EEPROM.write(BERRY,255);
            }else{
              EEPROM.write(BERRY,EEPROM.read(BERRY)+random(1,5));
            }
          }else if(item==1){
            EEPROM.write(xy,0);
            if(EEPROM.read(STICK)>249){
              EEPROM.write(STICK,255);
            }else{
              EEPROM.write(STICK,EEPROM.read(STICK)+random(3,5));
            }
            if(EEPROM.read(APPLE)>250){
              EEPROM.write(APPLE,255);
            }else{
              EEPROM.write(APPLE,EEPROM.read(APPLE)+random(2,4));
            }
            if(EEPROM.read(SEEDLING)>252){
              EEPROM.write(SEEDLING,255);
            }else{
              EEPROM.write(SEEDLING,EEPROM.read(SEEDLING)+random(1,2));
            }
          }else if(item==2){
            EEPROM.write(xy,0);
            if(EEPROM.read(STONE)>248){
              EEPROM.write(STONE,255);
            }else{
              EEPROM.write(STONE,EEPROM.read(STONE)+random(3,6));
            }
            if(EEPROM.read(IRON)>253){
              EEPROM.write(IRON,255);
            }else{
              int change=0;
              if(random(0,4)-3==0)
                EEPROM.write(IRON,EEPROM.read(IRON)+1);
            }
            if(EEPROM.read(GOLD)>253){
              EEPROM.write(GOLD,255);
            }else{
              int change=0;
              if(random(0,5)-3==0)
                EEPROM.write(GOLD,EEPROM.read(GOLD)+1);
            }
          }else if(item==3){
            EEPROM.write(xy,0);
            if(EEPROM.read(WHEAT)>246){
              EEPROM.write(WHEAT,255);
            }else{
              EEPROM.write(WHEAT,EEPROM.read(WHEAT)+random(2,8));
            }
          }else if(item==6){
            EEPROM.write(xy,0);
            if(EEPROM.read(SEEDLING)>246){
              EEPROM.write(SEEDLING,255);
            }else{
              EEPROM.write(SEEDLING,EEPROM.read(SEEDLING)+1);
            }
          }
        }else{
          display.drawLine(59,26,60+progress,26,1);
          progressBar();
        }
      }
    }else{
      progress=0;
    }
    if(b(FUNC1) && inhand>3){
      if(inhand==4 && food<9 && EEPROM.read(BERRY)>0){
        food++;
        EEPROM.write(BERRY,EEPROM.read(BERRY)-1);
      }else if(inhand==5){
      }else if(inhand==6){
      }else if(inhand==7 && food<9 && EEPROM.read(APPLE)>0){
        food+=2;
        EEPROM.write(APPLE,EEPROM.read(APPLE)-1);
      }else if(inhand==8 && EEPROM.read(xy)==0 && EEPROM.read(SEEDLING)>0){
        EEPROM.write(xy,6);
        EEPROM.write(SEEDLING,EEPROM.read(SEEDLING)-1);
      }else if(inhand==9){
      }else if(inhand==10){
      }else if(inhand==11){
      }else if(inhand==12){
      }
      if((inhand==4 && EEPROM.read(BERRY)==0) || (inhand==5 && EEPROM.read(STONE)==0) || (inhand==6 && EEPROM.read(STICK)==0) || (inhand==7 && EEPROM.read(APPLE)==0) || (inhand==8 && EEPROM.read(SEEDLING)==0) || (inhand==9 && EEPROM.read(WHEAT)==0) || (inhand==10 && EEPROM.read(MEAT)==0) || (inhand==11 && EEPROM.read(IRON)==0) || (inhand==12 && EEPROM.read(GOLD)==0)){
        inhand==0;
      }
      delay(300);
    }
    while(paused){
      display.clearDisplay();
      if(b(UP) && opt>1 && millis()-times>100){
        times=millis();
        opt--;
      }
      if(b(DOWN) && opt<3 && millis()-times>100){
        times=millis();
        opt++;
      }
      display.drawRect(41,14,46,33,1);
      if(opt==1){
        display.setCursor(43,18);
        display.setTextColor(0,WHITE);
        display.println("RESUME");//w:6
      }else{
        display.setCursor(43,18);
        display.setTextColor(WHITE,0);
        display.println("RESUME");
      }
      if(opt==2){
        display.setCursor(43,27);
        display.setTextColor(0,WHITE);
        display.println("OPTIONS");
      }else{
        display.setCursor(43,27);
        display.setTextColor(WHITE,0);
        display.println("OPTIONS");
      }
      if(opt==3){
        display.setCursor(43,36);
        display.setTextColor(0,WHITE);
        display.println("SAVE");
      }else{
        display.setCursor(43,36);
        display.setTextColor(WHITE,0);
        display.println("SAVE");
      }
      if(b(FUNC1) && millis()-times>100){
        times=millis();
        if(opt==1){
          paused=false;
        }else if(opt==2){
          //NONE
        }else{
          save();
          paused=false;
          menu=false;
        }
      }
      display.display();
    }
  }else{//-------------------------------------------------------------------------------------------------
    display.drawBitmap(0,16,logo,128,40,1);
    if(b(UP)){
      menu=true;
    }
    if(b(DOWN)){
      menu=true;
      generate();
    }
  }
  display.display();
}
bool b(int b){
  if(digitalRead(b)==HIGH){
    return true;
  }else{
    return false;
  }
}//i-wys j-
void generate(){
  for(int i=1011; i<1022; i++){
    EEPROM.write(i,0);
  }
  EEPROM.write(1012,99);
  EEPROM.write(1011,9);
  display.clearDisplay();
  display.drawBitmap(48,12,loading,32,40,1);
  display.display();
  int structure=0;
  for(int i=0; i<32; i++){
    for(int j=0; j<32; j++){
      int thing=0;
      if(random(0,5)-random(0,5)>0){
        structure=random(0,1);
      }
      if(structure==1){
        for(int k=0; k<25;k++){
          if(k==0 || k==5 || k==20 || k==24 || k==25){
            EEPROM.write(i*j+k,0);
          }else{
            EEPROM.write(i*j+k,1);
          }
        }
        i=i+5;
        j=j+5;
      }else{
        thing=random(0,10)-5;
        if(thing<0){
          thing=0;
        }
        EEPROM.write(i*j,thing);
      }
    }
  }
  EEPROM.write(1023,random(1,31));
  EEPROM.write(1022,random(1,31));
  EEPROM.write(0,1);
  x=EEPROM.read(1023);
  y=EEPROM.read(1022);
  lives=EEPROM.read(1012);
  food=EEPROM.read(1011);
}
void drawTerrain(){
  for(int i=y; i<y+4; i++){
    for(int j=x; j<x+8; j++){
      if(((j-x)*20-xm>52 && (j-x)*20-xm<74) && ((i-y)*20-ym>16 && (i-y)*20-ym<36)){
        xy=j*i;
      }
      if(EEPROM.read(i*j)==1){
        display.drawBitmap((j-x)*20-xm,(i-y)*20-ym,tree0,width,height,1);
      }else if(EEPROM.read(i*j)==2){
        display.drawBitmap((j-x)*20-xm,(i-y)*20-ym,rock0,width,height,1);
      }else if(EEPROM.read(i*j)==3){
        display.drawBitmap((j-x)*20-xm,(i-y)*20-ym,grass0,width,height,1);
      }else if(EEPROM.read(i*j)==4){
        display.drawBitmap((j-x)*20-xm,(i-y)*20-ym,bush1,width,height,1);
      }else if(EEPROM.read(i*j)==5){
        display.drawBitmap((j-x)*20-xm,(i-y)*20-ym,bush0,width,height,1);
        if(millis()-times2>=100000){
          EEPROM.write(i*j,4);
        }
      }else if(EEPROM.read(i*j)==6){
        display.drawBitmap((j-x)*20-xm+4,(i-y)*20-ym+12,seedling0,itemwidth,itemheight,1);
        if(millis()-times2>=100000){
          EEPROM.write(i*j,1);
        }
      }
      if(random(0,20000)==500 && millis()%100==0){
        EEPROM.write(i*j,random(2,3));
      }
    }
  }
}
void save(){
  EEPROM.write(1023,x);
  EEPROM.write(1022,y);
}
void openi(){
  delay(150);
  while(!(b(UP) && b(DOWN))){
    delay(10);
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextColor(WHITE);
    display.print("BERRY:");
    display.println(EEPROM.read(BERRY));
    display.print("STONE:");
    display.println(EEPROM.read(STONE));
    display.print("STICK:");
    display.println(EEPROM.read(STICK));
    display.print("APPLE:");
    display.println(EEPROM.read(APPLE));
    display.print("SEEDLING:");
    display.println(EEPROM.read(SEEDLING));
    display.print("WHEAT:");
    display.println(EEPROM.read(WHEAT));
    display.print("MEAT:");
    display.println(EEPROM.read(MEAT));
    display.print("IRON:");
    display.println(EEPROM.read(IRON));
    display.setCursor(56,50);
    display.print("GOLD:");
    display.println(EEPROM.read(GOLD));
    display.drawLine(73,0,73,47,1);
    display.drawLine(73,47,128,47,1);
    display.setCursor(75,3);
    if(opt1==0)
      display.setTextColor(0,WHITE);
    else
      display.setTextColor(WHITE,0);
    display.println("CRAFTING");
    display.drawLine(73,15,128,15,1);
    display.setTextColor(WHITE,0);
    display.setCursor(75,17);
    if(opt1==1)
      display.setTextColor(0,WHITE);
    else
      display.setTextColor(WHITE,0);
    display.println("In Hand:");
    display.setTextColor(WHITE,0);
    display.setCursor(75,26);
    if(inhand==0){
      display.println("Nothing");
    }else if(inhand==1){
      display.println("Axe");
    }else if(inhand==2){
      display.println("Sword");
    }else if(inhand==3){
      display.println("Pick");//end tools/////////////////////////////////////////////
    }else if(inhand==4){
      display.println("Berry");
    }else if(inhand==5){
      display.println("Stone");
    }else if(inhand==6){
      display.println("Stick");
    }else if(inhand==7){
      display.println("Apple");
    }else if(inhand==8){
      display.println("Seedling");
    }else if(inhand==9){
      display.println("Wheat");
    }else if(inhand==10){
      display.println("Meat");
    }else if(inhand==11){
      display.println("Iron");
    }else if(inhand==12){
      display.println("Gold");
    }
    if(b(UP)){
      opt1=0;
    }else if(b(DOWN)){
      opt1=1;
    }
    if(b(FUNC1) && opt1==1){
        if(inhand==0){
          if(EEPROM.read(AXE)>0){
            inhand=1;
          }else if(EEPROM.read(SWORD)>0){
            inhand=2;
          }else if(EEPROM.read(PICK)>0){
            inhand=3;
          }else if(EEPROM.read(BERRY)>0){
            inhand=4;
          }else if(EEPROM.read(STONE)>0){
            inhand=5;
          }else if(EEPROM.read(STICK)>0){
            inhand=6;
          }else if(EEPROM.read(APPLE)>0){
            inhand=7;
          }else if(EEPROM.read(SEEDLING)>0){
            inhand=8;
          }else if(EEPROM.read(WHEAT)>0){
            inhand=9;
          }else if(EEPROM.read(MEAT)>0){
            inhand=10;
          }else if(EEPROM.read(IRON)>0){
            inhand=11;
          }else if(EEPROM.read(GOLD)>0){
            inhand=12;
          }else{
        inhand=0;
      }
        }else if(inhand==1){
          if(EEPROM.read(SWORD)>0){
            inhand=2;
          }else if(EEPROM.read(PICK)>0){
            inhand=3;
          }else if(EEPROM.read(BERRY)>0){
            inhand=4;
          }else if(EEPROM.read(STONE)>0){
            inhand=5;
          }else if(EEPROM.read(STICK)>0){
            inhand=6;
          }else if(EEPROM.read(APPLE)>0){
            inhand=7;
          }else if(EEPROM.read(SEEDLING)>0){
            inhand=8;
          }else if(EEPROM.read(WHEAT)>0){
            inhand=9;
          }else if(EEPROM.read(MEAT)>0){
            inhand=10;
          }else if(EEPROM.read(IRON)>0){
            inhand=11;
          }else if(EEPROM.read(GOLD)>0){
            inhand=12;
          }else{
        inhand=0;
      }
        }else if(inhand==2){
          if(EEPROM.read(PICK)>0){
            inhand=3;
          }else if(EEPROM.read(BERRY)>0){
            inhand=4;
          }else if(EEPROM.read(STONE)>0){
            inhand=5;
          }else if(EEPROM.read(STICK)>0){
            inhand=6;
          }else if(EEPROM.read(APPLE)>0){
            inhand=7;
          }else if(EEPROM.read(SEEDLING)>0){
            inhand=8;
          }else if(EEPROM.read(WHEAT)>0){
            inhand=9;
          }else if(EEPROM.read(MEAT)>0){
            inhand=10;
          }else if(EEPROM.read(IRON)>0){
            inhand=11;
          }else if(EEPROM.read(GOLD)>0){
            inhand=12;
          }else{
        inhand=0;
      }
        }else if(inhand==3){
          if(EEPROM.read(BERRY)>0){
            inhand=4;
          }else if(EEPROM.read(STONE)>0){
            inhand=5;
          }else if(EEPROM.read(STICK)>0){
            inhand=6;
          }else if(EEPROM.read(APPLE)>0){
            inhand=7;
          }else if(EEPROM.read(SEEDLING)>0){
            inhand=8;
          }else if(EEPROM.read(WHEAT)>0){
            inhand=9;
          }else if(EEPROM.read(MEAT)>0){
            inhand=10;
          }else if(EEPROM.read(IRON)>0){
            inhand=11;
          }else if(EEPROM.read(GOLD)>0){
            inhand=12;
          }else{
        inhand=0;
      }
        }else if(inhand==4){
          if(EEPROM.read(STONE)>0){
            inhand=5;
          }else if(EEPROM.read(STICK)>0){
            inhand=6;
          }else if(EEPROM.read(APPLE)>0){
            inhand=7;
          }else if(EEPROM.read(SEEDLING)>0){
            inhand=8;
          }else if(EEPROM.read(WHEAT)>0){
            inhand=9;
          }else if(EEPROM.read(MEAT)>0){
            inhand=10;
          }else if(EEPROM.read(IRON)>0){
            inhand=11;
          }else if(EEPROM.read(GOLD)>0){
            inhand=12;
          }else{
        inhand=0;
      }
        }else if(inhand==5){
          if(EEPROM.read(STICK)>0){
            inhand=6;
          }else if(EEPROM.read(APPLE)>0){
            inhand=7;
          }else if(EEPROM.read(SEEDLING)>0){
            inhand=8;
          }else if(EEPROM.read(WHEAT)>0){
            inhand=9;
          }else if(EEPROM.read(MEAT)>0){
            inhand=10;
          }else if(EEPROM.read(IRON)>0){
            inhand=11;
          }else if(EEPROM.read(GOLD)>0){
            inhand=12;
          }else{
        inhand=0;
      }
        }else if(inhand==6){
          if(EEPROM.read(APPLE)>0){
            inhand=7;
          }else if(EEPROM.read(SEEDLING)>0){
            inhand=8;
          }else if(EEPROM.read(WHEAT)>0){
            inhand=9;
          }else if(EEPROM.read(MEAT)>0){
            inhand=10;
          }else if(EEPROM.read(IRON)>0){
            inhand=11;
          }else if(EEPROM.read(GOLD)>0){
            inhand=12;
          }else{
        inhand=0;
      }
        }else if(inhand==7){
          if(EEPROM.read(SEEDLING)>0){
            inhand=8;
          }else if(EEPROM.read(WHEAT)>0){
            inhand=9;
          }else if(EEPROM.read(MEAT)>0){
            inhand=10;
          }else if(EEPROM.read(IRON)>0){
            inhand=11;
          }else if(EEPROM.read(GOLD)>0){
            inhand=12;
          }else{
        inhand=0;
      }
        }else if(inhand==8){
          if(EEPROM.read(WHEAT)>0){
            inhand=9;
          }else if(EEPROM.read(MEAT)>0){
            inhand=10;
          }else if(EEPROM.read(IRON)>0){
            inhand=11;
          }else if(EEPROM.read(GOLD)>0){
            inhand=12;
          }else{
        inhand=0;
      }
        }else if(inhand==9){
          if(EEPROM.read(MEAT)>0){
            inhand=10;
          }else if(EEPROM.read(IRON)>0){
            inhand=11;
          }else if(EEPROM.read(GOLD)>0){
            inhand=12;
          }else{
        inhand=0;
      }
        }else if(inhand==10){
          if(EEPROM.read(IRON)>0){
            inhand=11;
          }else if(EEPROM.read(GOLD)>0){
            inhand=12;
          }else{
        inhand=0;
      }
        }else if(inhand==11){
          if(EEPROM.read(GOLD)>0){
            inhand=12;
          }else{
        inhand=0;
      }
        }else if(inhand==12){
          inhand=0;
        }
      delay(150);
    }else if(b(FUNC1) && opt==0){
      crafting();
    }
    display.display();
  }
  delay(150);
};
void progressBar(){
  int asdf=5;
  if(inhand==0){
    asdf=4;
  }else if(inhand==1){
    asdf=2;
  }else if(inhand==2){
    asdf=3;
  }else if(inhand==3){
    asdf=1;
  }else{
    asdf=5;
  }
  if(millis()-times1>30*asdf){
    times1=millis();
    progress++;
  }
}
void lose(){
  generate();
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(28,20);
  display.println("LOSE!");  
  display.display();
  for(;;);
}
void crafting(){
  delay(150);
  while(!(b(UP) && b(DOWN))){
    display.clearDisplay();
    display.drawLine(65,0,65,64,1);
    display.setCursor(0,0);
    display.println("You can craft:");
    display.setCursor(0,8);
    if(EEPROM.read(IRON)>=4 && EEPROM.read(GOLD)>=2 && EEPROM.read(STICK)>=3){
      if(opt2==0){
        display.setTextColor(0,WHITE);
        display.setCursor(65,0);
        display.println("Iron: 4");
        display.setCursor(65,8);
        display.println("Gold: 2");
        display.setCursor(65,16);
        display.println("Stick: 3");
        if(b(FUNC1)){
          EEPROM.write(SWORD,1);
          EEPROM.write(IRON, EEPROM.read(IRON)-4);
          EEPROM.write(GOLD, EEPROM.read(GOLD)-2);
          EEPROM.write(STICK, EEPROM.read(STICK)-3);
        }
      }else
        display.setTextColor(WHITE,0);
      display.println("Sword");
    }else{
      opt2++;
    }
    if(EEPROM.read(IRON)>=3 && EEPROM.read(STICK)>=6){
      if(opt2==1){
        display.setTextColor(0,WHITE);
        display.setCursor(65,0);
        display.println("Iron: 3");
        display.setCursor(65,8);
        display.println("Stick: 6");
        if(b(FUNC1)){
          EEPROM.write(AXE,1);
          EEPROM.write(IRON, EEPROM.read(IRON)-3);
          EEPROM.write(STICK, EEPROM.read(STICK)-6);
        }
      }else
        display.setTextColor(WHITE,0);
       display.println("Axe");
    }else{
      opt2++;
    }
    if(EEPROM.read(IRON)>=3 && EEPROM.read(GOLD)>=3 && EEPROM.read(STICK)>=5){
      if(opt2==2){
        display.setTextColor(0,WHITE);
        display.setCursor(65,0);
        display.println("Iron: 3");
        display.setCursor(65,8);
        display.println("Gold: 3");
        display.setCursor(65,16);
        display.println("Stick: 5");
        if(b(FUNC1)){
          EEPROM.write(PICK,1);
          EEPROM.write(IRON, EEPROM.read(IRON)-3);
          EEPROM.write(GOLD, EEPROM.read(GOLD)-3);
          EEPROM.write(STICK, EEPROM.read(STICK)-5);
        }
      }else
        display.setTextColor(WHITE,0);
       display.println("Pick");
    }else{
      opt2=0;
    }
    if(EEPROM.read(WHEAT)>=7){
      if(opt2==3){
        display.setTextColor(0,WHITE);
        display.setCursor(65,0);
        display.println("Wheat: 7");
      }else
        display.setTextColor(WHITE,0);
       display.println("Bread");
    }else{
      opt2=0;
    }
    if(b(UP) && opt2>0){
      opt2--;
    }
    if(b(DOWN) && opt2<3){
      opt2++;
    }
    display.display();
  }
  delay(150);
}
void entities(){
  //e1
  if(e1.active){
    if(e1.texture==1){
      display.drawBitmap(e1.x,e1.y,enemy0,enemywidth,enemyheight,1);
    }
    if(e1.x<61){
      e1.x++;
    }else if(e1.x>66){
      e1.x--;
    }
    if(e1.y<29){
      e1.y++;
    }else if(e1.x>35){
      e1.y--;
    }
    if(e1.lives<=0){
      e1.active=false;
    }
    if(millis()-times4>=2000 && e1.x>60 && e1.x<67 && e1.y>28 && e1.y<36){
      live(e1.attack);
      times4=millis();
    }
  }
  //e2
  if(e2.active){
    if(e2.texture==1){
      display.drawBitmap(e2.x,e2.y,enemy0,enemywidth,enemyheight,1);
    }
    if(e2.x<61){
      e2.x++;
    }else if(e2.x>66){
      e2.x--;
    }
    if(e2.y<29){
      e2.y++;
    }else if(e2.y>35){
      e2.y--;
    }
    if(e2.lives<=0){
      e2.active=false;
    }
    if(millis()-times5>=2000 && e2.x>60 && e2.x<67 && e2.y>28 && e2.y<36){
      live(e2.attack);
      times5=millis();
    }
  }
}
void live(int l){
  if(lives-l>0){
    lives-=l;
    EEPROM.write(1012,lives);
  }else{
    lose();
  }
}
