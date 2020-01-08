// Declare component positions
int buttonPin = 4, led1 = 5, led2 = 6, led3 = 7, led4 = 8, led5 = 9;

// Iteration
int buttonNew, buttonOld = 0;
int mode = 0;

// Timekeeping
unsigned long prevMillis = millis();
long interval = 0;
int cycle;

// Setup
void setup() {
  // initialize button as input
  pinMode(buttonPin, INPUT);
  // initialize led pins as output.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
}

// Loop
void loop() {
  // Button tracking
  buttonNew = digitalRead(buttonPin);

  // Mode iteration  
  if (buttonNew == 0 && buttonOld == 1 && mode >= 0 && mode <= 4)
    { 
      mode++;
      if (mode == 4)
      {
        mode = 0;
      }
    }

  // Mode 0 (off)
  if (mode == 0) 
    {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
    }
  
  // Mode 1 (on)
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
      interval = 100;
      cycle = 0;
      if (millis() - prevMillis >= interval && cycle == 0)
        {
          cycle = 1;
          prevMillis = millis();
        }
      else if(millis() - prevMillis >= interval && cycle == 1)
        {
          cycle = 0;
          prevMillis = millis();
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
  
  // Mode 3 (altBlink)
  else if (mode == 3)
    { 
      interval = 250;
      cycle = 0;
      if (millis() - prevMillis >= interval && cycle == 0)
        {
          cycle = 1;
          prevMillis = millis();
        }
      else if (millis() - prevMillis >= interval && cycle == 1)
        {
          cycle = 0;
          prevMillis = millis();
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
  
  // Mode 4 (zigzag)
  else if (mode == 4)
    {
      interval = 100;
      cycle = 0;
      if (millis() - prevMillis >= interval && cycle >= 0 && cycle <=7)
        {
          cycle++;
          if (cycle == 7)
            {
              cycle = 0;
            }
          prevMillis = millis();
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
  buttonOld = buttonNew;
}
