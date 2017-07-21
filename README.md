![bluetoothghetto](https://github.com/pcotret/BluetoothGhetto/blob/master/img/bluetoothghetto.png)
# BluetoothGhetto – A tiny Bluetooth-enabled ghetto blaster

### Arnaud Droulers & Martin Hintzy
CentraleSupélec, Rennes campus, 2016/2017

This project has been realized by Arnaud Droulers and Martin Hintzy for a short-term project under the supervision of Dr. Pascal Cotret.

## Goals of this project
It was a personal idea we had for our short-term project. Even if we're born in the 1990s, we always remember people with ghetto blasters near a basketball playground when we watched American sitcoms on TV. We wanted to make a modern version of such a device with some wireless connection and a few RGB LEDs in order to make it shiny as f###.

After some searches on the Internet, we have found two interesting tutorials (thanks Instructables !):

* http://www.instructables.com/id/LED-Color-Organ-Triple-Deluxe/
* http://www.instructables.com/id/Powerfull-Portable-Bluetooth-Speaker-2x5W/

Our BluetoothGhetto was born! We just had to gather those two projects and to add a microcontroller with a LED strip to make our project. In the next parts of this tutorial, we will write a few notes about existing project and some details about the microcontroller/LED enhancement.

![box](https://github.com/pcotret/BluetoothGhetto/blob/master/img/img1.png)

## Bluetooth speaker
### Bill of material

* [Micro USB 5V 1A 18650 charging board](http://ebay.eu/2odylMV)
* [2 cheap speakers (5W in our case)](http://ebay.eu/2vqZBvy)
* [PAM8406 audio amplifier board](http://ebay.eu/2oQBBi5)
* [3.5mm USB Wireless Bluetooth Music Audio Stereo Speaker Receiver Adapter Dongle](http://ebay.eu/2gPPyNm)
* [CP2102 USB/UART adapter](http://ebay.eu/2phIPib)
* [ON/OFF/ON 3-positions switch](http://ebay.eu/2p91Ake)
* [Voltmeter digital display (3,5 - 30V)](http://ebay.eu/2nl9wlZ)
![schemablue](https://github.com/pcotret/BluetoothGhetto/blob/master/img/bluetooth.png)
Just connect as it is done in the schematic: that's it, you have your own Bluetooth speaker!
![montageblue](https://github.com/pcotret/BluetoothGhetto/blob/master/img/img2.png)

## LED color organ
![fritzing](https://github.com/pcotret/BluetoothGhetto/blob/master/img/led_schematic.png)
![spice](https://github.com/pcotret/BluetoothGhetto/blob/master/img/led_spice.png)
### How does it work?
This electronic circuits is basically a combination of 3 filters (sections with transistors) with 3 different cutoff frequencies. We start by the highest frequencies.

* [2500-...] Hz
* [120-2500] Hz
* [0-120] Hz

We wanted to do a SPICE simulation to check the behavior of each filter. However, it failed for an unknown reason. We took values as it was written in the original tutorial.

BluetoothGhetto is born :)
![bg](https://github.com/pcotret/BluetoothGhetto/blob/master/img/img3.png)

## Make it shine!
![rgb](https://github.com/pcotret/BluetoothGhetto/blob/master/img/img4.png)

The next idea was to put a few WS2812 RGB LEDs on the wooden box instead of basic RGB LEDs in the circuit. As a consequence, we had to use a microcontroller to drive such a LED strip. Of course, the whole processing may be performed on the microcontroller...
We decided to use an Arduino Nano as in the schematic below, it turns out that even a Lilypad would do the trick.

![strip](https://github.com/pcotret/BluetoothGhetto/blob/master/img/led_strip.png)

The Arduino code implemented in the Arduino is available here: https://github.com/pcotret/BluetoothGhetto/blob/master/docs/ledstrip/ledstrip.ino

```C++
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
```

## References
* http://www.instructables.com/id/LED-Color-Organ-Triple-Deluxe/
* http://www.instructables.com/id/Powerfull-Portable-Bluetooth-Speaker-2x5W/
* https://learn.adafruit.com/adafruit-neopixel-uberguide/overview
