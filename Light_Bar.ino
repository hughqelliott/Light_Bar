#include <Adafruit_NeoPixel.h>

#define PIN 6
#define BUTTON_PIN 7
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(32, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.
boolean buttonClicked = false;
int animationType = 0;
int animationMax = 8;
void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(BUTTON_PIN, INPUT_PULLUP);//simple 2-post button
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.println("Let's do this!/n");
}

void loop() {
  if(digitalRead(BUTTON_PIN) == LOW){
  //button is clicked
  Serial.println("BUTTON MOTHERFUCKER!/n");
  buttonClicked = true;
}else{
  if(buttonClicked){
    buttonClicked = false;
    if(animationType < animationMax){
    animationType++;
  }else{
    animationType = 0;
}
    Serial.println(animationType,DEC);
  }
  switch(animationType){
    case 0:
    singleColor(255,255,255,20);
    break;
    case 1:
    singleColor(255,0,0,20);
    break;
    case 2:
    singleColor(0,255,0,20);
    break;
    case 3:
    singleColor(0,0,255,20);
    break;
    case 4:
    singleColor(255,0,255,20);
    break;
    case 5:
    singleColor(255,140,0,20);
    break;
    case 6:
    singleColor(255,255,0,20);
    break;
    case 7:
    clearStrip(5);
    animateOut(20);
    break;
    case 8:
    clearStrip(5);
    animateIn(20);
    break;
  }
}
}
void clearStrip(uint8_t wait){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
      
      //delay(wait);
  }
  strip.show();
}
int ledCount = 0;
void animateIn(uint8_t wait){
  //start at 0 and 16
  //cycle through strip.
  //not using delay
  if(ledCount<0){
    ledCount = 15;
  }else{
    ledCount--;
  }
  Serial.println(ledCount,DEC);
  strip.setPixelColor(ledCount,strip.Color(255,0,0));
  strip.setPixelColor(ledCount+16,strip.Color(255,0,0));
  strip.show();
  delay(wait);
}
void animateOut(uint8_t wait){
  //start at 0 and 16
  //cycle through strip.
  //not using delay
  if(ledCount>15){
    ledCount = 0;
  }else{
    ledCount++;
  }
  Serial.println(ledCount,DEC);
  strip.setPixelColor(ledCount,strip.Color(255,0,0));
  strip.setPixelColor(ledCount+16,strip.Color(255,0,0));
  strip.show();
  delay(wait);
}
void singleColor(int red, int green, int blue,uint8_t wait){
  for(uint16_t i=0;i<strip.numPixels();i++){
   strip.setPixelColor(i,strip.Color(red,green,blue));
  }
  strip.show();
 delay(wait); 
}
void rainbow(uint8_t wait) {
  
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

