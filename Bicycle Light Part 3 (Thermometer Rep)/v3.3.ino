#include <MPU6050_tockn.h>
#include <Adafruit_NeoPixel.h>

// Variable declarations
//=============================================================================================================================================
// Declare component positions
int ledPin = 3, noOfLEDs = 11;

// Mode iteration
int noOfModes = 5, mode = 0;

// Timekeeping
//unsigned long prevMillisDebug = 0;
unsigned long prevMillisShake = 0, prevMillis = 0; 
unsigned long hourLength = 3600000;
int hour = 0;

// Temperature array
int tempArray[24][7] = {20}, tempArrayAvg[365] = {20}; 

// LED indexing
int tempCurrentIndex = 0, tempAvgIndexTotalD = 0, tempAvgIndexTotalW = 0, tempAvgIndexTotalM = 0, tempAvgIndexTotalY = 0, tempAvgIndexHour = 0;

// Initialize MPU Chip
MPU6050 mpu6050(Wire);

// Initialize NeoPixel object
Adafruit_NeoPixel strip(noOfLEDs, ledPin, NEO_RGB + NEO_KHZ400);

// Setup
//=============================================================================================================================================
void setup()
{  
  // Serial to display data
  Serial.begin(56700);
  Wire.begin();
  
  // Initialize RGB LEDs
  strip.begin();

  // Initialize MPU
  mpu6050.begin();
}

// Main loop function
//=============================================================================================================================================
void loop() 
{
  // Timekeeping
  unsigned long currentMillis = millis();

  // Sensor update
  mpu6050.update();

//  // Debug
//  unsigned long currentMillisDebug = millis();
//  if (currentMillisDebug - prevMillisDebug >= 1000)
//  {
//    Serial.print(mpu6050.getTemp()); Serial.print("\t"); Serial.println(tempCurrentIndex);
//    Serial.println(mpu6050.getAccZ());\
//    prevMillisDebug = currentMillisDebug;
//  }
  
  // Every new day:
  if (hour == 0)
  {
    // Shift temp array right for new day
    for (int i = 0; i < 24; i++)
    {
      for (int j = 0; j < 6; j++)
      {
        tempArray[i][j+1] = tempArray[i][j];
      }
    }
    
    // Fill in array for average temperatures and shift right for new day
    tempArrayAvg[0] = averageDayTemperature();
    
    for (int i = 0; i < 364; i++)
    {
      tempArrayAvg[i+1] = tempArrayAvg[i];
    }
  }

  // Every hour: fill in temperature for said hour;
  if (currentMillis - prevMillis >= hourLength)
  {
    tempArray[hour][0] = mpu6050.getTemp(); 
  }

  // Mode iteration  
  if (readShake())
  { 
    mode++;
    Serial.println("Next mode");
    if (mode >= noOfModes) {mode = 0;}
  }

  // LED index calculation
  tempCurrentIndex = ((int) mpu6050.getTemp() - 8) / 2; constrain(tempCurrentIndex, 1, 10);
  tempAvgIndexTotalD = ((int) averageTemperatureTotal(1) - 8) / 2; constrain(tempAvgIndexTotalD, 1, 10);
  tempAvgIndexTotalW = ((int) averageTemperatureTotal(7) - 8) / 2; constrain(tempAvgIndexTotalW, 1, 10);
  tempAvgIndexTotalM = ((int) averageTemperatureTotal(30) - 8) / 2; constrain(tempAvgIndexTotalM, 1, 10);
  tempAvgIndexTotalY = ((int) averageTemperatureTotal(365) - 8) / 2; constrain(tempAvgIndexTotalY, 1, 10);
  tempAvgIndexHour = ((int) averageTemperatureHour(hour, 7) - 8) / 2; constrain(tempAvgIndexHour, 1, 10);
  
  // Thermometer modes
  if (mode == 0) {mode0();} // Mode 0 (diff. avg hour W)
  else if (mode == 1) {mode1();} // Mode 1 (diff. avg total D)
  else if (mode == 2) {mode2();} // Mode 2 (diff. avg total W)
  else if (mode == 3) {mode3();} // Mode 3 (diff. avg total M)
  else if (mode == 4) {mode4();} // Mode 4 (diff. avg total Y)
  else {defaultLED();} // Off

  // Temperature array input control : Hour & day incrementation
  if (currentMillis - prevMillis >= hourLength)
    {
      hour++;
      if (hour == 24) {hour = 0;}
      prevMillis = currentMillis;
    }
}

// Subordinate Functions
//=============================================================================================================================================
// Average over day
float averageDayTemperature()
{
  float avg, sum = 0;
  for (int i = 0; i < 24; i++)
  {
    sum += tempArray[i][0];
  }
  avg = sum / 24;
  return avg;
}

// Average over extended period
float averageTemperatureTotal(int d)
{
  float avg, sum = 0;
  for (int i = 1; i < d; i++)
  {
    sum += tempArrayAvg[i];
  }
  avg = sum / (d-1);
  return avg;
}

// Average for current hour (hour) over period of time (d<7)
float averageTemperatureHour(int hour, int d)
{
  float avg, sum = 0;
  for (int j = 1; j < d; j++)
  {
    sum += tempArray[hour][j];
  }
  avg = sum / (d-1);
  return avg;
}

// Modes
void mode0() // Mode 0 (avg temp hourly W)
{
  for (int i = 1; i < noOfLEDs; i++) {strip.setPixelColor(i, 0, 0, 0);}
  strip.setPixelColor(tempCurrentIndex, 255, 255, 255);
  // Comparison temperature
  if (tempCurrentIndex != tempAvgIndexHour)
  {
    strip.setPixelColor(tempAvgIndexHour, 255, 0, 0);
  }
  // Boundary visibility
  if (tempCurrentIndex != 1 && tempAvgIndexHour != 1)
  {
    strip.setPixelColor(1, 100, 100, 100);
  }
  if (tempCurrentIndex != 10 && tempAvgIndexHour != 10)
  {
    strip.setPixelColor(10, 100, 100, 100);
  }
  // Mode indicator
  strip.setPixelColor(0, 153, 51, 255);
  strip.show();
}
void mode1() // Mode 1 (avg temp total D)
{
  for (int i = 1; i < noOfLEDs; i++) {strip.setPixelColor(i, 0, 0, 0);}
  strip.setPixelColor(tempCurrentIndex, 255, 255, 255);
  if (tempCurrentIndex != tempAvgIndexTotalD)
  {
    strip.setPixelColor(tempAvgIndexTotalD, 255, 0, 0);
  }
  // Boundary visibility
  if (tempCurrentIndex != 1 && tempAvgIndexTotalD != 1)
  {
    strip.setPixelColor(1, 100, 100, 100);
  }
  if (tempCurrentIndex != 10 && tempAvgIndexTotalD != 10)
  {
    strip.setPixelColor(10, 100, 100, 100);
  }
  // Mode indicator
  strip.setPixelColor(0, 51, 255, 51);
  strip.show();  
}
void mode2() // Mode 2 (avg temp total W)
{
  for (int i = 1; i < noOfLEDs; i++) {strip.setPixelColor(i, 0, 0, 0);}
  strip.setPixelColor(tempCurrentIndex, 255, 255, 255);
  if (tempCurrentIndex != tempAvgIndexTotalW)
  {
    strip.setPixelColor(tempAvgIndexTotalW, 255, 0, 0);
  }
  // Boundary visibility
  if (tempCurrentIndex != 1 && tempAvgIndexTotalW != 1)
  {
    strip.setPixelColor(1, 100, 100, 100);
  }
  if (tempCurrentIndex != 10 && tempAvgIndexTotalW != 10)
  {
    strip.setPixelColor(10, 100, 100, 100);
  }
  // Mode indicator
  strip.setPixelColor(0, 153, 255, 51);
  strip.show();
}
void mode3() // Mode 3 (avg temp total M)
{
  for (int i = 1; i < noOfLEDs; i++) {strip.setPixelColor(i, 0, 0, 0);}
  strip.setPixelColor(tempCurrentIndex, 255, 255, 255);
  if (tempCurrentIndex != tempAvgIndexTotalM)
  {
    strip.setPixelColor(tempAvgIndexTotalM, 255, 0, 0);
  }
  // Boundary visibility
  if (tempCurrentIndex != 1 && tempAvgIndexTotalM != 1)
  {
    strip.setPixelColor(1, 100, 100, 100); 
  }
  if (tempCurrentIndex != 10 && tempAvgIndexTotalM != 10)
  {
    strip.setPixelColor(10, 100, 100, 100);
  }
  // Mode indicator
  strip.setPixelColor(0, 255, 255, 51);
  strip.show();
}
void mode4() // Mode 4 (avg temp total Y)
{
  for (int i = 1; i < noOfLEDs; i++) {strip.setPixelColor(i, 0, 0, 0);}
  strip.setPixelColor(tempCurrentIndex, 255, 255, 255);
  if (tempCurrentIndex != tempAvgIndexTotalY)
  {
    strip.setPixelColor(tempAvgIndexTotalY, 255, 0, 0);
  }
  // Boundary visibility
  if (tempCurrentIndex != 1 && tempAvgIndexTotalY != 1)
  {
    strip.setPixelColor(1, 100, 100, 100);
  }
  if (tempCurrentIndex != 10 && tempAvgIndexTotalY != 10)
  {
    strip.setPixelColor(10, 100, 100, 100);
  }
  // Mode indicator
  strip.setPixelColor(0, 255, 153, 51);
  strip.show();
}
void defaultLED() // All off
{
  strip.setPixelColor(0, 0, 0, 0);
  strip.setPixelColor(1, 0, 0, 0);
  strip.setPixelColor(2, 0, 0, 0);
  strip.setPixelColor(3, 0, 0, 0);
  strip.setPixelColor(4, 0, 0, 0);
  strip.setPixelColor(5, 0, 0, 0);
  strip.setPixelColor(6, 0, 0, 0);
  strip.setPixelColor(7, 0, 0, 0);
  strip.setPixelColor(8, 0, 0, 0);
  strip.setPixelColor(9, 0, 0, 0);
  strip.setPixelColor(10, 0, 0, 0);
}

bool readShake()
{
  bool shake = false;
  unsigned long currentMillisShake = millis();
  if (currentMillisShake - prevMillisShake > 300)
  {
    prevMillisShake = currentMillisShake;
    if (abs(mpu6050.getAccZ()) >= 1.5)
    {
      shake = true; 
    }
  }
  return shake;
}
