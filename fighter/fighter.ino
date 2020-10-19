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
}
void loop() {
  display.clearDisplay();
  display.setCursor(0,17);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("hello world");
  display.drawBitmap(0,0,mario,16,11,1);
  display.display();
}\
