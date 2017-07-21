// Libraries
#include <Adafruit_NeoPixel.h>

// Constants
#define PIN 13
#define BFSENSOR 2
#define HFSENSOR 1

// Initialize the WS2812 LED strip for 70 LEDs
Adafruit_NeoPixel strip = Adafruit_NeoPixel(70, PIN, NEO_GRB + NEO_KHZ800);

// Global variables
int hf_read=0;
int bf_read=0;
int hf_voltage=0;
int bf_voltage=0;

// Setup (executed only once)
void setup()
{
  Serial.begin(9600);
  strip.begin();
  strip.show();
}

// Main loop (infinite)
void loop()
{
  int i;
  // Measuring voltage on HF pin
  hf_read=analogRead(HFSENSOR);
  // Converting voltage in mV
  hf_voltage=map(hf_read,0,1023,0,1800);  
  // Measuring voltage on BF pin
  bf_read=analogRead(BFSENSOR);
  // Converting voltage in mV
  bf_voltage=map(bf_read,0,1023,0,1800);
  // Printing both values  
  Serial.print(hf_voltage);
  Serial.print(" ");
  Serial.print(bf_voltage);
  Serial.println();
  // High frequencies
  // 1st level reached (red, black, black)
  if((300<hf_voltage)&&(hf_voltage<500))
  {
    for(i=14;i<25;i++) // Intensity level 1
      strip.setPixelColor(i,255,0,0);
    for(i=9;i<14;i++)  // Intensity level 2
      strip.setPixelColor(i,0,0,0);
    for(i=25;i<31;i++) // Intensity level 2
      strip.setPixelColor(i,0,0,0);
    for(i=5;i<9;i++)   // Intensity level 3
      strip.setPixelColor(i,0,0,0);
    for(i=31;i<35;i++) // Intensity level 3
      strip.setPixelColor(i,0,0,0);
  }
  // 1st and 2nd levels reached (red, red/orange, black)
  else if((500<hf_voltage)&&(hf_voltage<600))
  {
    for(i=14;i<24;i++) // Intensity level 1
      strip.setPixelColor(i,255,0,0);
    for(i=9;i<14;i++)  // Intensity level 2
      strip.setPixelColor(i,255,102,102);
	for(i=24;i<31;i++) // Intensity level 2
      strip.setPixelColor(i,255,102,102);
    for(i=5;i<9;i++)   // Intensity level 3
      strip.setPixelColor(i,0,0,0);
    for(i=31;i<35;i++) // niveau d'intensité 3
      strip.setPixelColor(i,0,0,0);
  }
  // 1st, 2nd and 3rd levels reached (red, red/orange, orange)
  else if(600<hf_voltage)
  {
    for(i=14;i<24;i++) // Intensity level 1
      strip.setPixelColor(i,255,0,0);
    for(i=9;i<14;i++)  // Intensity level 2
      strip.setPixelColor(i,255,102,102);
    for(i=24;i<31;i++) // Intensity level 2
      strip.setPixelColor(i,255,102,102);
    for(i=5;i<9;i++)   // Intensity level 3
      strip.setPixelColor(i,255,128,0);
    for(i=31;i<35;i++) // Intensity level 3
      strip.setPixelColor(i,255,128,0);
  }
  // Low frequencies
  // 1st level reached (yellow, black, black)
  if((300<hf_voltage)&&(hf_voltage<500))
  {
    for(i=68;i<57;i--) // Intensity level 1
      strip.setPixelColor(i,255,255,0);
    for(i=62;i<69;i++) // Intensity level 2 
      strip.setPixelColor(i,0,0,0);
    for(i=57;i<39;i--) // Intensity level 2
      strip.setPixelColor(i,0,0,0);
    for(i=38;i<34;i--) // Intensity level 3
      strip.setPixelColor(i,0,0,0);
    for(i=0;i<5;i++)   // Intensity level 3
      strip.setPixelColor(i,0,0,0);
  }
  // 1st and 2nd levels reached (yellow, yellow/orange, black)
  else if((500<hf_voltage)&&(hf_voltage<600))
  {
    for(i=68;i<57;i--) // Intensity level 1
      strip.setPixelColor(i,255,255,0);
    for(i=62;i<69;i++) // Intensity level 2 
      strip.setPixelColor(i,255,204,153);
    for(i=57;i<39;i--) // Intensity level 2
      strip.setPixelColor(i,255,204,153);
    for(i=38;i<34;i--) // Intensity level 3
      strip.setPixelColor(i,0,0,0);
    for(i=0;i<5;i++)   // Intensity level 3
      strip.setPixelColor(i,0,0,0);
  }
  // 1st, 2nd and 3rd levels reached (yellow, yellow/orange, orange)
  else if(600<hf_voltage)
  {
	for(i=68;i<57;i--) // Intensity level 1
      strip.setPixelColor(i,255,255,0);
    for(i=62;i<69;i++) // Intensity level 2 
      strip.setPixelColor(i,255,204,153);
    for(i=57;i<39;i--) // Intensity level 2
      strip.setPixelColor(i,255,204,153);
    for(i=38;i<34;i--) // Intensity level 3
      strip.setPixelColor(i,255,128,0);
    for(i=0;i<5;i++)   // Intensity level 3
      strip.setPixelColor(i,255,128,0);
  }
  strip.show();            // Displaying everythin'!
  strip.setBrightness(50); // Set the strip brightness
  delay(1000); 
}
