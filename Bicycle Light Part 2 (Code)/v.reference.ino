

#include <Wire.h> // Must include Wire library for I2C

#define PIN 6

#define NUMPIXELS 8


int delayval = 500;

void setup()
{
  Serial.begin(9600);
  Serial.println("Test Code!");
  
  accel.init();
  pixels.begin(); // This initializes the NeoPixel library.
  blinkin_test();
}

void loop()
{
  // Use the accel.available() function to wait for new data
  //  from the accelerometer.
  if (accel.available())
  {
    // First, use accel.read() to read the new variables:
    accel.read();  
    delay(delayval/2);    
    printAccels(); // Printing x,y,z int values
    
    Serial.println(); // Print new line every time.
  }
}

void printAccels()
{
  Serial.print((accel.x)*100);
  Serial.print("\t");
  Serial.print((accel.y)*100);
  Serial.print("\t");
  Serial.print((accel.z)*100);
  Serial.print("\t");
}

void detect_direction()
{
  long X, Y, Z;
  X=(accel.x)*100;
  Y=(accel.y)*100;
  Z=(accel.z)*100;

  if ((27000<X<28000)&&(3500<Y<4000)&&(-8400<Z<-7200))
    {
      red();
    }
  else if ((28000<X<29000)&&(3000<Y<4000)&&(-9500<Z<12000))
    {
      glow_right();
    }
  else if((29000<X<30000)&&(3500<Y<6000)&&(Z<-12000)
    {
      glow_left();
    }
  else
    {
      red();
    }
}

void glow_right(){
  for(int i=NUMPIXELS/2;i<NUMPIXELS;i++)
  {
      pixels.setPixelColor(i, pixels.Color(0,255,0)); //  bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(delayval/2); // Delay for a period of time (in milliseconds).
  }
   
     for(int i=0;i<NUMPIXELS;i++)
  {
      pixels.setPixelColor(i, pixels.Color(0,0,0)); //  turn pixels off.
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(delayval/2); // Delay for a period of time (in milliseconds).
  }
      delay(delayval/2); // Delay for a period of time (in milliseconds).
}

void glow_left(){
  for(int i=(NUMPIXELS/2)-1;i>=0;i--)
  {
      pixels.setPixelColor(i, pixels.Color(0, 255, 0)); //  bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(delayval/2); // Delay for a period of time (in milliseconds).
  }
   for(int i=(NUMPIXELS/2)-1;i>=0;i--)
  {
    pixels.setPixelColor(i, pixels.Color(0,0,0)); //  turn pixels off.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval/2); // Delay for a period of time (in milliseconds).
  }
    delay(delayval/2); // Delay for a period of time (in milliseconds).
}

// Blinking in red for 5 times 
void blinkin_test(){
  for(int i=0;i<=5;i++){
    red();
    delay(delayval/2); // Delay for a period of time (in milliseconds).
    off();
    delay(delayval/2); // Delay for a period of time (in milliseconds).  
  }
}

void red(){
  for(int i=0;i<=NUMPIXELS;i++){
      pixels.setPixelColor(i, pixels.Color(255,0,0));
      pixels.show(); 
    }
}

void off(){
  for(int i=0;i<=NUMPIXELS;i++){
      pixels.setPixelColor(i, pixels.Color(0,0,0)); 
      pixels.show(); 
    }
}
