#include <MPU9250.h>

// Declare component positions
int buttonPin = 4, led1 = 5, led2 = 6, led3 = 7, led4 = 8, led5 = 9;

// Iteration
bool buttonState = 1, buttonOldState = 0; // Note, state is 0 when pressed
int noOfModes = 5, mode = 0;

// Timekeeping
unsigned long prevMillis = 0, interval = 0;
int cycle = 0;

// MPU Chip
MPU9250 IMU(SPI, 3);
int status;

// Temperature
float temperature;

// Setup
void setup() 
{
  // initialize button as input
  pinMode(buttonPin, INPUT);
  // initialize led pins as output.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  // Serial to display data
  Serial.begin(56700);

  // Initiate communication with IMU
  status = IMU.begin();
}

// Loop
void loop() 
{
  // Button tracking
  unsigned long currentMillis = millis();
  buttonState = digitalRead(buttonPin);
  
  // Sensor update
  IMU.readSensor();
  temperature = IMU.getTemperature_C();

  // Temperature verification (debug)
  if (currentMillis - prevMillis >= interval && cycle == 0)
  {
    Serial,println(temperature);
    prevMillis = currentMillis;
  }

  // Mode iteration  
  if (buttonState == 0 && buttonOldState == 1)
  { 
    mode++;
    if (mode == noOfModes)
    {
      mode = 0;
    }
  }

  // Mode 0 (all off)
  if (mode == 0) 
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
  }
  
  // Mode 1 (all on)
  else if (mode == 1)
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }
  
  // Mode 2 (blink)
  else if (mode == 2) 
  { 
    interval = 125;
    if (currentMillis - prevMillis >= interval && cycle == 0)
      {
        cycle = 1;
        prevMillis = currentMillis;
      }
    else if (currentMillis - prevMillis >= interval && cycle == 1)
      {
        cycle = 0;
        prevMillis = currentMillis;
      }

    if (cycle == 0)
      {
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, HIGH);
        digitalWrite(led4, HIGH);
        digitalWrite(led5, HIGH); 
      } 
    else if (cycle == 1)
      {
        digitalWrite(led1, LOW);   
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
        digitalWrite(led5, LOW); 
      }
  }
  
  // Mode 3 (alternating blink)
  else if (mode == 3)
  {
    interval = 250;
    if (currentMillis - prevMillis >= interval && cycle == 0)
    {
      cycle = 1;
      prevMillis = currentMillis;
    }
    else if (currentMillis - prevMillis >= interval && cycle == 1)
    {
      cycle = 0;
      prevMillis = currentMillis;
    }

    if (cycle == 0)
    {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, LOW);
      digitalWrite(led5, HIGH); 
    }
    else if (cycle == 1)
    {
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, LOW);
    }
  }
  
  // Mode 4 (shuttle run)
  else if (mode == 4)
  {
    interval = 125;
    if (currentMillis - prevMillis >= interval)
    {
      cycle++;
      if (cycle > 7)
      {
        cycle = 0;
      }
      prevMillis = currentMillis;
    }
  
    if (cycle == 0)
    {
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH); 
    }
    if (cycle == 1)
    {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
    }
    if (cycle == 2)
    {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
    }
    if (cycle == 3)
    {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, LOW);
      digitalWrite(led5, HIGH);
    }
    if (cycle == 4)
    {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, LOW); 
    }
    if (cycle == 5)
    {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, LOW);
      digitalWrite(led5, HIGH);
    }
    if (cycle == 6)
    {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
    }
    if (cycle == 7)
    {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
    }  
  }
  buttonOldState = buttonState;
}
