#define dmHigh B00000000
#define dmLow B11111111
#define numLeds 125
#define nop __asm__("nop\n\t");
int datapin = 3;

byte testValue = 124;

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
  for(int i=0; i<numLeds*3; i++)
  {
    leds[i] = B11111111;
  }
  byte testV = leds[0];
  String testa = "";
  for(int i=0; i<8; i++)
  {
    if(testV & 1)
    {
      testa += "1";
    }
    else{
      testa += "0";
    }
    testV >>= 1;
  }
  Serial.println(testa);
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
  byte buff = leds[0];
  for(int i=0; i<8; i++)
  {
    PORTD = dmHigh;
    if(buff & 1)
    {
      nop nop nop nop nop nop nop nop nop nop nop //Pull Low after 14 Ticks
      PORTD = dmLow;
    }
    else
    {
      nop nop nop //Pull Low after 7 Ticks
      PORTD = dmLow;
    }
    
    //BIT0: 340 Ticks optimal
    //BIT1: 172,8 Ticks optimal
    if(buff & 1)
    {
      nop nop nop nop //Finish after 7 -1 Ticks
    }
    else
    {
      nop nop nop nop nop nop nop nop nop nop nop //Finish after 14 -1 Ticks
    }
    buff >>= 1; //Shift one right
  }
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

