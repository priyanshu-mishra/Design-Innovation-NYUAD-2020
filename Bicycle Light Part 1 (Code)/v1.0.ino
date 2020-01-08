
int led1 = 5, led2 = 6, led3 = 7, led4 = 8, led5 = 9;
int buttonPin = 2;

int buttonNew;
int buttonOld=0;
int switchState = 0;
unsigned long previousMillis = 0;
long interval=0;
int cycler=0;
// the setup function runs once when you press reset or power the board
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

// the loop function runs over and over again forever
void loop() {

  unsigned long currentMillis = millis();
  buttonNew = digitalRead(buttonPin);
  
  if (buttonNew == 0 && buttonOld == 1 && switchState==0)
  { 
    switchState = 1;
  }
  else if (buttonNew == 0 && buttonOld == 1 && switchState==1)
  {
    switchState = 2;
  }
  else if (buttonNew == 0 && buttonOld == 1 && switchState==2)
  {
    switchState = 3;
  }
  else if (buttonNew == 0 && buttonOld == 1 && switchState==3)
  {
    switchState = 4;
  }
  else if (buttonNew == 0 && buttonOld == 1 && switchState==4)
  {
    switchState = 0;
  }
  
  if (switchState == 0) 
  {
    digitalWrite(led1, HIGH);   // HIGH=OFF
    digitalWrite(led2, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led3, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led4, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led5, HIGH);   // turn the LED on (HIGH is the voltage level) 
  }
  else if (switchState == 1)
  {
    digitalWrite(led1, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led2, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led3, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led4, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led5, LOW);   // turn the LED on (HIGH is the voltage level) 
  }
  else if (switchState == 2) 
  { interval=50;
  if(currentMillis-previousMillis>=interval && cycler==0)
  {cycler=1;
  previousMillis=currentMillis;}
  else if(currentMillis-previousMillis>=interval && cycler==1)
  {cycler=0;
  previousMillis=currentMillis;}

  if (cycler==0)
  {
    digitalWrite(led1, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led2, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led3, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led4, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led5, HIGH);   // turn the LED on (HIGH is the voltage level) 
    
    }
 else if (cycler==1)
  {
    digitalWrite(led1, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led2, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led3, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led4, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led5, LOW);   // turn the LED on (HIGH is the voltage level) 
    
    }
  
  }
  else if (switchState==3)
  { interval=250;
  if(currentMillis-previousMillis>=interval && cycler==0)
  {cycler=1;
  previousMillis=currentMillis;}
  else if(currentMillis-previousMillis>=interval && cycler==1)
  {cycler=0;
  previousMillis=currentMillis;}

  if (cycler==0)
  {
    digitalWrite(led1, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led2, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led3, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led4, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led5, HIGH);   // turn the LED on (HIGH is the voltage level) 
    
    }
 else if (cycler==1)
  {
    digitalWrite(led1, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led2, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led3, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led4, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(led5, LOW);   // turn the LED on (HIGH is the voltage level) 
    
    }
  
  }
  else if (switchState=4)
  {
    interval=50;
    if(currentMillis-previousMillis>=interval && cycler==0)
  {cycler=1;
  previousMillis=currentMillis;}
  else if(currentMillis-previousMillis>=interval && cycler==1)
  {cycler=2;
  previousMillis=currentMillis;}
  else if(currentMillis-previousMillis>=interval && cycler==2)
  {cycler=3;
  previousMillis=currentMillis;}
  else if(currentMillis-previousMillis>=interval && cycler==3)
  {cycler=4;
  previousMillis=currentMillis;}
  else if(currentMillis-previousMillis>=interval && cycler==4)
  {cycler=5;
  previousMillis=currentMillis;}
  else if(currentMillis-previousMillis>=interval && cycler==5)
  {cycler=6;
  previousMillis=currentMillis;}
  else if(currentMillis-previousMillis>=interval && cycler==6)
  {cycler=7;
  previousMillis=currentMillis;}
  else if(currentMillis-previousMillis>=interval && cycler==7)
  {cycler=8;
  previousMillis=currentMillis;}
  else if(currentMillis-previousMillis>=interval && cycler==8)
  {cycler=0;
  previousMillis=currentMillis;}
  
  
    
    
    
    }
  buttonOld=buttonNew;
}
