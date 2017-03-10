#define dmHigh B00000000
#define dmLow B11111111
#define numLeds 125
int datapin = 3;

//DEBUG LED
int debug_led = 13;

byte leds[numLeds*3];
int R = 0;
int G = 1;
int B = 2;

void setup()
{
  pinMode(datapin, OUTPUT);
  pinMode(debug_led, OUTPUT);
  digitalWrite(13, LOW);
  Serial.begin(9600);
}

void loop()
{
  noInterrupts();
  long t1 = micros();
  test();
  long t2 =  micros();
  interrupts();
  Serial.println((t2-t1-4)*16); // Subtract 4 to exlude the time the micros function takes
  delay(90);
}

/**
 * Method to run through the time measurement
 */
void test()
{
  //1088 - 1152 bzw 1728 - 1792 bzw 2560 - 2624
  for(int i=0; i<numLeds*3; i++)
  {
    PORTD = dmHigh;
    
    
  }
}

/**
 * Send the bytes to the LEDs
 */
void serialStream()
{
  noInterrupts(); //Disable interrupts to make sure nothing disturbs while sending

  for(int i=0; i<numLeds; i++)
  {
    
  }
  
  interrupts(); //Turn them back on again
}

void toBits(byte color, boolean bits[])
{
  byte buff;
  
  for(int i=7; i<0; i--)
  {
    buff = color >> i;
    
    if(buff & 1)
    {
      bits[i] = true;
    }
    else
    {
      bits[i] = false;
    }
  }
}

