#include <MPU6050_tockn.h>
#include <Adafruit_NeoPixel.h>

// Declare component positions
int ledPin = 3, noOfLEDs = 11;

// Iteration
int noOfModes = 7, mode = 0;

// Timekeeping
unsigned long prevMillisDebug = 0, prevMillis = 0; 
unsigned long hourLength = 3600000;

// Initialize NeoPixel object
Adafruit_NeoPixel strip(noOfLEDs, ledPin, NEO_RGB + NEO_KHZ400);

// MPU Chip
MPU6050 mpu6050(Wire);

// Temperature array
int tempArray[24][7] = {0}, tempArrayAvg[365] = {0}; 
int hour = 0, day = 0; // find way to incorporate actual time

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
}

void loop() 
{
  // Timekeeping
  unsigned long currentMillisDebug = millis();
  unsigned long currentMillis = millis();

  // Sensor update
  mpu6050.update();

  // Temperature verification (debug)
  if (currentMillisDebug - prevMillisDebug >= 1000)
  {
    Serial.println(mpu6050.getTemp());
    prevMillisDebug = currentMillisDebug;
  }
  
  // Shift array right for new day
  if (hour == 0)
  {
    for (int i = 0; i < 24; i++)
    {
      for (int j = 0; j < 6; j++)
      {
        tempArray[i][j+1] = tempArray[i][j];
      }
      tempArray[i][0] = 0;
    }
  }

  // Fill new day temp (hourly)
  if (currentMillis - prevMillis >= hourLength)
  {
    tempArray[hour][0] = mpu6050.getTemp();
  }

  // Mode iteration  
  if (1)
  { 
    mode++;
    if (mode == noOfModes)
    {
      mode = 0;
    }
  }

  // Thermometer modes
  // Mode 0 (current time)
  if (mode == 0)
  {
    
  }

  // Mode 1 (diff. avg total D)
  if (mode == 1)
  {
    
  }
  
  // Mode 2 (diff. avg total W)
  if (mode == 2)
  {
    
  }
  
  // Mode 3 (diff. avg total M)
  if (mode == 3)
  {
    
  }
  
  // Mode 4 (diff. avg total Y)
  if (mode == 4)
  {
    
  }
  
  // Mode 5 (diff. avg hourly D)
  if (mode == 5)
  {
    
  }
  
  // Mode 6 (diff. avg hourly W)
  if (mode == 6)
  {
    
  }
  
  // Light control (arg1 is light index, followed by G R B)
  strip.setPixelColor(0, 0, 255, 0);
  strip.show();
  strip.setPixelColor(1, 0, 0, 255);
  strip.show();

  // Temperature array input control : Day incrementation
  {
    hour++;
    if (hour >= 24)
    {
      hour = 0;
    }
    prevMillis = currentMillis;
  }
}

// Average
float averageTemperatureTotal(int h, int d)
{
  float avg, sum = 0, counter = 0;
  for (int i = 0; i < d; i++)
  {
    sum += tempArrayAvg[i];
  }
  avg = sum / d;
  return avg;
}

// Average for given hour (h) over period of time (d)
float averageTemperatureHour(int h, int d)
{
  float avg, sum = 0, counter = 0;
  for (int j = 0; j < d; j++)
  {
    sum += tempArray[h][j];
    counter++;
  }
  avg = sum / counter;
  return avg;
}
