#include <MPU6050_tockn.h>
#include <Adafruit_NeoPixel.h>

// Declare component positions
int ledPin = 3, noOfLEDs = 11;

// Iteration
int noOfModes = 5, mode = 0;

// Timekeeping
unsigned long prevMillisDebug = 0, prevMillis = 0; 
unsigned long hourLength = 3600000;

// Initialize NeoPixel object
Adafruit_NeoPixel strip(noOfLEDs, ledPin, NEO_RGB + NEO_KHZ400);

// Initialize MPU Chip
MPU6050 mpu6050(Wire);

// Temperature array
int tempArray[24][7] = {0}, tempArrayAvg[365] = {0}; 
int hour = 0, day = 0;
int difference = 0;

int tempCurrentIndex = 0, tempAvgIndexTotalD = 0, tempAvgIndexTotalW = 0, tempAvgIndexTotalM = 0, tempAvgIndexTotalY = 0, tempAvgIndexHour = 0;

// Setup
void setup()
{  
  // Serial to display data
  Serial.begin(56700);
  Wire.begin();
  
  // Initialize RGB LEDs
  strip.begin();
  strip.show();

  // Initialize MPU
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop() 
{
  // Timekeeping
  unsigned long currentMillisDebug = millis();
  unsigned long currentMillis = millis();

  // Sensor update
  mpu6050.update();

//  // Debug
//  if (currentMillisDebug - prevMillisDebug >= 1000)
//  {
//    Serial.println(mpu6050.getTemp());
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
  if (0) // implement tap
  { 
    mode++;
    Serial.println("Next mode");
    if (mode == noOfModes)
    {
      mode = 0;
    }
  }

  // Light position index calculation
  tempCurrentIndex = ((int) mpu6050.getTemp() - 10) / 2; constrain(tempCurrentIndex, 1, 10);
  tempAvgIndexTotalD = ((int) averageTemperatureTotal(1) - 10) / 2; constrain(tempAvgIndexTotalD, 1, 10);
  tempAvgIndexTotalW = ((int) averageTemperatureTotal(7) - 10) / 2; constrain(tempAvgIndexTotalW, 1, 10);
  tempAvgIndexTotalM = ((int) averageTemperatureTotal(30) - 10) / 2; constrain(tempAvgIndexTotalM, 1, 10);
  tempAvgIndexTotalY = ((int) averageTemperatureTotal(365) - 10) / 2; constrain(tempAvgIndexTotalY, 1, 10);
  tempAvgIndexHour = ((int) averageTemperatureHour(hour, 7) - 10) / 2; constrain(tempAvgIndexHour, 1, 10);
  
  // Thermometer modes
  // Mode 0 (diff. avg hour W)
  if (mode == 0)
  {
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

  // Mode 1 (diff. avg total D)
  else if (mode == 1)
  {
    strip.setPixelColor(tempCurrentIndex, 255, 255, 255);
    if (tempCurrentIndex != tempAvgIndexTotalD)
    {
      strip.setPixelColor(tempAvgIndexTotalD, 255, 0, 0);
    }
    // Boundary visibility
    if (tempCurrentIndex != 1 && tempAvgIndexTotalD != 1)
    {
      strip.setPixelColor(0, 100, 100, 100);
    }
    if (tempCurrentIndex != 10 && tempAvgIndexTotalD != 10)
    {
      strip.setPixelColor(10, 100, 100, 100);
    }
    // Mode indicator
    strip.setPixelColor(0, 51, 255, 51);
    strip.show();
  }
  
  // Mode 2 (diff. avg total W)
  else if (mode == 2)
  {
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
  
  // Mode 3 (diff. avg total M)
  else if (mode == 3)
  {
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
  
  // Mode 4 (diff. avg total Y)
  else if (mode == 4)
  {
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

  // Temperature array input control : Hour & day incrementation
  if (currentMillis - prevMillis >= hourLength)
    {
      hour++;
      if (hour >= 24)
      {
        hour = 0;
      }
      prevMillis = currentMillis;
    } 
}

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

// Average for given hour (h) over period of time (d)
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
