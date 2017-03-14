#define dmHigh B00000000
#define dmLow B11111111
#define numLeds 125
#define nop __asm__("nop\n\t");
int datapin = 3;

//DEBUG LED
int debug_led = 13;

byte leds[numLeds*3];

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
  int buff = leds[0];
  PORTD = dmLow;
  if(buff & 1)
  {
    PORTD = dmLow;
    nop nop nop //Pull High after 7 Ticks
    PORTD = dmHigh;
  }
  else
  {
    PORTD = dmLow;
    nop nop nop nop nop nop nop nop nop nop nop //Pull High after 14 Ticks
    PORTD = dmHigh;
  }
  
  buff = buff << 1;
}

/**
 * Send the bytes to the LEDs
 */
void serialStream()
{
  noInterrupts(); //Disable interrupts to make sure nothing disturbs while sending
  int buff = leds[0];
  
  for(int i=0; i<numLeds; i++)
  {
    PORTD = dmLow;
    if(buff & 1)
    {
      PORTD = dmLow;
      nop nop nop //Pull High after 7 Ticks
      PORTD = dmHigh;
    }
    else
    {
      PORTD = dmLow;
      nop nop nop nop nop nop nop nop nop nop nop //Pull High after 14 Ticks
      PORTD = dmHigh;
    }
    
    buff = buff << 1;
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

