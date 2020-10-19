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
const uint8_t PROGMEM mark0[]={
  0B11000110,
  0B01101100,
  0B00111000,
  0B00111000,
  0B01101100,
  0B11000110 
};
const uint8_t PROGMEM gun0[]={
  0B10000000,
  0B10000000,
  0B10000000,
  0B10000000,
  0B10000000,
  0B10000000
};
const uint8_t PROGMEM gun1[]={
  0B00000100,
  0B00001000,
  0B00010000,
  0B00100000,
  0B01000000,
  0B10000000
};
const uint8_t PROGMEM gun2[]={
  0B10000000,
  0B01000000,
  0B00100000,
  0B00010000,
  0B00001000,
  0B00000100
};
const uint8_t PROGMEM gun3[]={
  0B11111111,
  0B00000000,
  0B00000000,
  0B00000000,
  0B00000000,
  0B00000000
};
const uint8_t PROGMEM bul0[]={
  0B10000000,
  0B10000000,
  0B10000000
};
const uint8_t PROGMEM bul1[]={
  0B00100000,
  0B01000000,
  0B10000000
};
const uint8_t PROGMEM bul2[]={
  0B10000000,
  0B01000000,
  0B00100000
};
const uint8_t PROGMEM bul3[]={
  0B11110000,
  0B00000000,
  0B00000000
};
const uint8_t  PROGMEM agent0[] = {
  0B00000000,0B00000000,
  0B00100000,0B00000100,
  0B01100000,0B00000110,
  0B01000011,0B11000010,
  0B01100100,0B00100110,
  0B00111000,0B00011100,
  0B00011000,0B00011000,
  0B00001000,0B00010000,
  0B00001000,0B00010000,
  0B00000100,0B00100000,
  0B00000011,0B11000000,
  0B00000000,0B00000000,
  0B00000000,0B00000000,
  0B00000000,0B00000000
};
const uint8_t  PROGMEM agent2[] = {
  0B00000000,0B00111000,
  0B00000000,0B01101100,
  0B00000000,0B11000000,
  0B00000011,0B11000000,
  0B00000100,0B00100000,
  0B00001000,0B00010000,
  0B00001000,0B00010000,
  0B00001000,0B00010000,
  0B00001000,0B00010000,
  0B00000100,0B00100000,
  0B00000011,0B11000000,
  0B00000000,0B11000000,
  0B00000000,0B01101100,
  0B00000000,0B00111000
};
const uint8_t  PROGMEM agent4[] = {
  0B00000000,0B00000000,
  0B00000000,0B00000000,
  0B00000000,0B00000000,
  0B00000011,0B11000000,
  0B00000100,0B00100000,
  0B00001000,0B00010000,
  0B00001000,0B00010000,
  0B00011000,0B00011000,
  0B00111000,0B00011100,
  0B01100100,0B00100110,
  0B01000011,0B11000010,
  0B01100000,0B00000110,
  0B00100000,0B00000100,
  0B00000000,0B00000000
};
const uint8_t  PROGMEM agent6[] = {
  0B00011100,0B00000000,
  0B00110110,0B00000000,
  0B00000011,0B00000000,
  0B00000011,0B11000000,
  0B00000100,0B00100000,
  0B00001000,0B00010000,
  0B00001000,0B00010000,
  0B00001000,0B00010000,
  0B00001000,0B00010000,
  0B00000100,0B00100000,
  0B00000011,0B11000000,
  0B00000011,0B00000000,
  0B00110110,0B00000000,
  0B00011100,0B00000000
};
const uint8_t PROGMEM agent1[] = {
  0B00000000,0B01111000,
  0B00000000,0B11000000,
  0B00000001,0B10000010,
  0B00000011,0B11000010,
  0B00000100,0B00100010,
  0B00001000,0B00010110,
  0B00001000,0B00011100,
  0B00001000,0B00011000,
  0B00001000,0B00010000,
  0B00000100,0B00100000,
  0B00000011,0B11000000,
  0B00000000,0B00000000,
  0B00000000,0B00000000,
  0B00000000,0B00000000
};
const uint8_t PROGMEM agent3[] = {
  0B00000000,0B00000000,
  0B00000000,0B00000000,
  0B00000000,0B00000000,
  0B00000011,0B11000000,
  0B00000100,0B00100000,
  0B00001000,0B00010000,
  0B00001000,0B00011000,
  0B00001000,0B00011100,
  0B00001000,0B00010110,
  0B00000100,0B00100010,
  0B00000011,0B11000010,
  0B00000001,0B10000010,
  0B00000000,0B11000000,
  0B00000000,0B01111000
};
const uint8_t PROGMEM agent5[] = {
  0B00000000,0B00000000,
  0B00000000,0B00000000,
  0B00000000,0B00000000,
  0B00000011,0B11000000,
  0B00000100,0B00100000,
  0B00001000,0B00010000,
  0B00011000,0B00010000,
  0B00111000,0B00010000,
  0B01101000,0B00010000,
  0B01000100,0B00100000,
  0B01000011,0B11000000,
  0B01000001,0B10000000,
  0B00000011,0B00000000,
  0B00011110,0B00000000
};
const uint8_t PROGMEM agent7[] = {
  0B00011110,0B00000000,
  0B00000011,0B00000000,
  0B01000001,0B10000000,
  0B01000011,0B11000000,
  0B01000100,0B00100000,
  0B01101000,0B00010000,
  0B00111000,0B00010000,
  0B00011000,0B00010000,
  0B00001000,0B00010000,
  0B00000100,0B00100000,
  0B00000011,0B11000000,
  0B00000000,0B00000000,
  0B00000000,0B00000000,
  0B00000000,0B00000000
};//--------------------------------------------END-TEXTURES--------------------------------------------
int menu=0;
int level=1;
int levels=level;
int maxlevel=10;
int rotation=0;
int x=56;
int y=25;
int xenemy, yenemy;
int bprotation;
int berotation;
bool bpstarted=false;
bool bestarted=false;
int bpx=0;
int bex=0;
int bpy=0;
int bey=0;
int score=0;
int lives=5;
int record;
int xep=1;
int yep=1;
bool add=true;
unsigned long timing;
unsigned long timing1;
void randomEnemy(){
  xenemy=random(0,112);
  yenemy=random(0,50);
}
void setup() {
  Serial.begin(9600);
  record=EEPROM.read(1);
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  level=1;
  levels=level;
  pinMode(UP, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(FUNC1, INPUT);
  randomSeed(analogRead(A4));
  randomEnemy();
}
void loop() {
  display.clearDisplay();
  if(menu==0){//select
    if(level==0){
      EEPROM.write(1,0);
      level=1;
      levels=level;
    }
    display.setCursor(0,16);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.println("Wybor LVL:");
    display.setCursor(0,34);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    if(levels==1)
      display.println(" "+String(levels)+">");
    if(levels!=1 && levels<maxlevel)
      display.println("<"+String(levels)+">");
    if(levels==maxlevel)
      display.println("<"+String(levels));
    if(digitalRead(LEFT)==HIGH && levels>1){
      levels--;
    }
    if(digitalRead(RIGHT)==HIGH && levels<level){
      levels++;
    }
    if(digitalRead(FUNC1)==HIGH){
      menu=1;
      display.clearDisplay();
      timing=millis();
      timing1=millis();
    }
  }//--------------------------------GAME---------------------------------------------------------
  else if(menu==1){
    display.setCursor(0,0);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Score:"+String(score)+"| Lives:"+String(lives));
    if(lives<=0){
      lose();
    }
    if(digitalRead(UP)==HIGH){
      if(rotation==0 && y>0)
        y--;
      if(rotation==2 && x<128)
        x++;
      if(rotation==4 && y<64)
        y++;
      if(rotation==6 && x>0)
        x--;
      if(rotation==1 && y>0 && x<128){
        y--;
        x++;
      }
      if(rotation==3 && y<64 && x<128){
        y++;
        x++;
      }
      if(rotation==5 && y<64 && x>0){
        y++;
        x--;
      }
      if(rotation==7 && y>0 && x>0){
        y--;
        x--;
      }
    }
    if(digitalRead(DOWN)==HIGH){
      if(rotation==0 && y<64)
        y++;
      if(rotation==2 && x>0)
        x--;
      if(rotation==4 && y>0)
        y--;
      if(rotation==6 && x<128)
        x++;
      if(rotation==1 && y<64 && x>0){
        y++;
        x--;
      }
      if(rotation==3 && y>0 && x>0){
        y--;
        x--;
      }
      if(rotation==5 && y>0 && x<128){
        y--;
        x++;
      }
      if(rotation==7 && y<64 && x<128){
        y++;
        x++;
      }
    }
    if(digitalRead(LEFT) && millis()-timing1>100){
      if(rotation==0)
        rotation=7;
      else
        rotation--;
      timing1=millis();
    }
    if(digitalRead(RIGHT) && millis()-timing1>100){
      if(rotation==7)
        rotation=0;
      else
        rotation++;
      timing1=millis();
    }
    if(digitalRead(FUNC1) && !bpstarted){
      bprotation=rotation;
      bpstarted=true;
      if(rotation==0){
        bpx=x+13;
        bpy=y;
      }
      if(rotation==1){
        bpx=x+13;
        bpy=y;
      }
      if(rotation==2){
        bpx=x+13;
        bpy=y+12;
      }
      if(rotation==3){
        bpx=x+12;
        bpy=y+12;
      }
      if(rotation==4){
        bpx=x+3;
        bpy=y+12;
      }
      if(rotation==5){
        bpx=x;
        bpy=y+10;
      }
      if(rotation==6){
        bpx=x-3;
        bpy=y+2;
      }
      if(rotation==7){
        bpx=x-2;
        bpy=y-5;
      }
    }
    if(bpstarted==true){//pistol-----------------------------------------------------------
      if(bprotation==0 || bprotation==4){
        display.drawBitmap(bpx,bpy,bul0,8,3,1);
        if(bprotation==4){
          bpy++;
        }else{
          bpy--;
        }
      }
      else if(bprotation==1 || bprotation==5){
        display.drawBitmap(bpx,bpy,bul1,8,3,1);
        if(bprotation==1){
          bpy--;
          bpx++;
        }else{
          bpy++;
          bpx--;
        }
      }
      else if(bprotation==3 || bprotation==7){
        display.drawBitmap(bpx,bpy,bul2,8,3,1);
        if(bprotation==3){
          bpy++;
          bpx++;
        }else{
          bpy--;
          bpx--;
        }
      }
      else if(bprotation==2 || bprotation==6){
        display.drawBitmap(bpx,bpy,bul3,8,3,1);
        if(bprotation==2){
          bpx++;
        }else{
          bpx--;
        }
      }
      if(bpx>xenemy && bpx<xenemy+16 && bpy>yenemy && bpy<yenemy+14){
        bpstarted=false;
        randomEnemy();
        score++;
      }
      else if(bpx<0 || bpx>128 || bpy<0 || bpy>64){
        bpstarted=false;
      }
    }
    drawAgent(x,y,rotation,0);
    xenemy-=xep;
    yenemy-=yep;
    if(add){
      xep++;
      yep++;
    }else{
      xep--;
      yep--;
    }
    if(xep>=30 || xep<=0){
      add=!add;
    }
    int xpenemy=xenemy+xep;
    int ypenemy=yenemy+yep;
    if(xpenemy>=128 || ypenemy>=64){
      add=false;
    }
    xenemy=xpenemy;
    yenemy=ypenemy;
    enemyPistol();
    drawAgent(xpenemy,ypenemy,enemyRotation(),1);
  }
  display.display();
}//---------------------------------------------------------------------------------------------------------------------------
void drawAgent(int x, int y, int r,bool e){
  if(e)
    display.drawBitmap(x+4,y-7,mark0,8,6,1);
  if(r==0){
    display.drawBitmap(x,y,agent0,16,14,1);
    display.drawBitmap(x+13,y-3,gun0,8,6,1);
  }
  if(r==1){
    display.drawBitmap(x,y,agent1,16,14,1);
    display.drawBitmap(x+13,y-3,gun1,8,6,1);
  }
  if(r==2){
    display.drawBitmap(x,y,agent2,16,14,1);
    display.drawBitmap(x+13,y+12,gun3,8,6,1);
  }
  if(r==3){
    display.drawBitmap(x,y,agent3,16,14,1);
    display.drawBitmap(x+12,y+12,gun2,8,6,1);
  }
  if(r==4){
    display.drawBitmap(x,y,agent4,16,14,1);
    display.drawBitmap(x+3,y+12,gun0,8,6,1);
  }
  if(r==5){
    display.drawBitmap(x,y,agent5,16,14,1);
    display.drawBitmap(x-3,y+10,gun1,8,6,1);
  }
  if(r==6){
    display.drawBitmap(x,y,agent6,16,14,1);
    display.drawBitmap(x-3,y+2,gun3,8,6,1);
  }
  if(r==7){
    display.drawBitmap(x,y,agent7,16,14,1);
    display.drawBitmap(x-2,y-5,gun2,8,6,1);
  }
}
int enemyRotation(){
  bool left=false;
  bool right=false;
  bool up=false;
  bool down=false;
  int r=0;
  if(xenemy-10>x){
    left=true;
  }else if(xenemy+10<x){
    right=true;
  }
  if(yenemy-10>y){
    up=true;
  }else if(yenemy+10<y){
    down=true;
  }
  if(up && !down && !right && !left){
    r=0;
  }
  if(up && !down && right && !left){
    r=1;
  }
  if(!up && !down && right && !left){
    r=2;
  }
  if(!up && down && right && !left){
    r=3;
  }
  if(!up && down && !right && !left){
    r=4;
  }
  if(!up && down && !right && left){
    r=5;
  }
  if(!up && !down && !right && left){
    r=6;
  }
  if(up && !down && !right && left){
    r=7;
  }
  return r;
}
void enemyPistol(){
  if(!bestarted && millis()-timing>250){
    berotation=enemyRotation();
    bestarted=true;
    if(berotation==0){
      bex=xenemy+13;
      bey=yenemy;
    }
    if(berotation==1){
      bex=xenemy+13;
      bey=yenemy;
    }
    if(berotation==2){
      bex=xenemy+13;
      bey=yenemy+12;
    }
    if(berotation==3){
      bex=xenemy+12;
      bey=yenemy+12;
    }
    if(berotation==4){
      bex=xenemy+3;
      bey=yenemy+12;
    }
    if(berotation==5){
      bex=xenemy;
      bey=yenemy+10;
    }
    if(berotation==6){
      bex=xenemy-3;
      bey=yenemy+2;
    }
    if(berotation==7){
      bex=xenemy-2;
      bey=yenemy-5;
    }
    timing=millis();
  }
  if(bestarted==true){//pistol-----------------------------------------------------------
    if(berotation==0 || berotation==4){
      display.drawBitmap(bex,bey,bul0,8,3,1);
      if(berotation==4){
        bey++;
      }else{
        bey--;
      }
    }
    else if(berotation==1 || berotation==5){
      display.drawBitmap(bex,bey,bul1,8,3,1);
      if(berotation==1){
        bey--;
        bex++;
      }else{
        bey++;
        bex--;
      }
    }
    else if(berotation==3 || berotation==7){
      display.drawBitmap(bex,bey,bul2,8,3,1);
      if(berotation==3){
        bey++;
        bex++;
      }else{
        bey--;
        bex--;
      }
    }
    else if(berotation==2 || berotation==6){
      display.drawBitmap(bex,bey,bul3,8,3,1);
      if(berotation==2){
        bex++;
      }else{
        bex--;
      }
    }
    if(bex>x && bex<x+16 && bey>y && bey<y+14){
      bestarted=false;
      int livies=lives-1; //lives--; niedziala
      lives=livies;
      timing=millis();
    }
    else if(bex<0 || bex>128 || bey<0 || bey>64){
      bestarted=false;
      timing=millis();
    }
  }
}
void lose(){
  record=EEPROM.read(1);
  if(score>record){
    record=score;
    EEPROM.write(1,record);
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
