#include <MPU6050_tockn.h>
#include <Adafruit_NeoPixel.h>

// Variable declarations
//=============================================================================================================================================
// Declare component positions
int ledPin = 3, noOfLEDs = 10;

// Timekeeping
unsigned long prevMillisDebug = 0;
unsigned long prevMillis = 0, hourLength = 3600000;
int hour = 0;

// Temperature array
int tempArray[24][7] = {23};

// LED indexing
int ledIndex = 0;

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

  // Debug
  unsigned long currentMillisDebug = millis();
  if (currentMillisDebug - prevMillisDebug >= 1000)
  {
    Serial.print(mpu6050.getTemp()); Serial.print("\t"); Serial.println(ledIndex);
    prevMillisDebug = currentMillisDebug;
  }
  
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
  }
  
  // Every hour: fill in temperature for said hour;
  if (currentMillis - prevMillis >= hourLength)
  {
    tempArray[hour][0] = mpu6050.getTemp(); 
  }

  // LED index calculation
  ledIndex = (int) mpu6050.getTemp() - averageTemperatureHour(hour);
  
  // Thermometer functionality
  tempCompDisp();

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
// Average for current hour over week
float averageTemperatureHour(int hour)
{
  float avg, sum = 0;
  for (int i = 1; i < 7; i++)
  {
    sum += tempArray[hour][i];
  }
  avg = sum / 6;
  return avg;
}

// Main functionality
void tempCompDisp() // Active (avg temp hourly W)
{
  if (ledIndex > 0)
  {
    for (int i = 0; i < abs(ledIndex); i++) {strip.setPixelColor(i, 0, 255, 0);}
    for (int i = abs(ledIndex); i < noOfLEDs; i++) {strip.setPixelColor(i, 255, 255, 255);}
  }
  else if (ledIndex < 0)
  {
    for (int i = 0; i < abs(ledIndex); i++) {strip.setPixelColor(i, 0, 0, 255);}
    for (int i = abs(ledIndex); i < noOfLEDs; i++) {strip.setPixelColor(i, 255, 255, 255);}
  }
  else if (ledIndex == 0)
  {
    for (int i = 0; i < noOfLEDs; i++) {strip.setPixelColor(i, 255, 255, 255);}
  } 
  strip.show();
}
