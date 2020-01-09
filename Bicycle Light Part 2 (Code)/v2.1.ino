#include <MPU9250.h>

#include <Adafruit_NeoPixel.h>
#include <MPU9250.h>

// Declare component positions
int ledPin = 3, noOfLEDs = 2;

// Timekeeping
unsigned long prevMillis = 0, interval = 0;

// Initialize NeoPixel object
Adafruit_NeoPixel strip(noOfLEDs, ledPin, NEO_RGB + NEO_KHZ400);

// MPU Chip
MPU9250 IMU(Wire, 0x68);
int status;

// Setup
void setup() 
{
  // Initialize RGB LEDs
  strip.begin();
  strip.show();
  
  // Serial to display data
  Serial.begin(56700);

  // Initiate communication with IMU
  status = IMU.begin();
}

void loop() 
{
  // Timekeeping
  unsigned long currentMillis = millis();

  // Sensor update
  IMU.readSensor();

  // Temperature verification (debug)
  if (currentMillis - prevMillis >= interval)
  {
    Serial.println(IMU.getTemperature_C(), 6);
    prevMillis = currentMillis;
  }
  
  // Light control (arg1 is light index, followed by G R B)
  strip.setPixelColor(0, 0, 255, 0);
  strip.show();
  strip.setPixelColor(1, 0, 0, 255);
  strip.show();
}
