#include <MPU6050_tockn.h>
#include <Adafruit_NeoPixel.h>
// Variable declarations ====================================================================
int ledPin = 3, noOfLEDs = 8;
unsigned long prevMs = 0, hourLength = 3600000; // Timekeeping
int hour = 0;
int tempArray[24][7] = {24}; // Temperature array
int ledIndex = 0; // LED indexing
MPU6050 mpu(Wire); // Initialize MPU Chip
Adafruit_NeoPixel led(noOfLEDs, ledPin, NEO_RGB + NEO_KHZ400); // Initialize NeoPixel
// Setup ====================================================================================
void setup()
{
  Wire.begin();
  led.begin(); // Initialize RGB LEDs
  mpu.begin(); // Initialize MPU
}
// Main loop function =======================================================================
void loop() 
{
  if (millis() - prevMs >= 1000) {mpu.update();} // Sensor update
  if (hour == 0) // Shift temp array right for new day
  {
    for (int i = 0; i < 24; i++)
    {
      for (int j = 0; j < 6; j++)
      {tempArray[i][j+1] = tempArray[i][j];}
    }
  }
  // Every hour: fill in temperature for said hour;
  if (millis() - prevMs >= hourLength) {tempArray[hour][0] = mpu.getTemp();}
  ledIndex = (int) mpu.getTemp() - averageTemperature(); // LED index calc
  constrain(ledIndex, 0, noOfLEDs-1);
  tempDisplay(); // Thermometer function
  // Temperature array input control : Hour & day incrementation
  if (millis() - prevMs >= hourLength)
  {
    hour++; prevMs = millis();
    if (hour == 24) {hour = 0;}
  }
}
// Subordinate Functions ====================================================================
float averageTemperature() // Average for current hour over week
{
  float avg, sum = 0;
  for (int i = 1; i < 7; i++) {sum += tempArray[hour][i];}
  avg = sum / 6;
  return avg;
}
void tempDisplay() // Main functionality
{
  if (ledIndex > 0)
  {
    for (int i = 0; i < abs(ledIndex); i++) {led.setPixelColor(i, 0, 255, 0);} // Red
    for (int i = abs(ledIndex); i < noOfLEDs; i++) {led.setPixelColor(i, 100, 100, 100);}
  }
  else if (ledIndex < 0)
  {
    for (int i = 0; i < abs(ledIndex); i++) {led.setPixelColor(i, 0, 0, 255);} // Blue
    for (int i = abs(ledIndex); i < noOfLEDs; i++) {led.setPixelColor(i, 100, 100, 100);}
  }
  else if (ledIndex == 0)
  {
    for (int i = 0; i < noOfLEDs; i++) {led.setPixelColor(i, 100, 100, 100);} // White
  }
  led.show();
}
