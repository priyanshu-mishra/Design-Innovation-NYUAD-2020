#include <Adafruit_NeoPixel.h>
#include <MPU9250.h>

// Declare component positions
int ledPin = 3, noOfLEDs = 2;

// Initialize NeoPixel object
Adafruit_NeoPixel strip(noOfLEDs, ledPin, NEO_RGB + NEO_KHZ400);

// Setup
void setup() 
{
  // Initialize RGB LEDs
  strip.begin();
  strip.show();
  
  // Serial to display data
  Serial.begin(56700);
}

void loop() 
{
  strip.setPixelColor(0, 0, 0, 0);
  strip.show();
}
