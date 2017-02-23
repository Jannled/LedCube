int datapin = 3;
byte datamask = B00000000;

//DEBUG LED
int debug_led = 13;

int amount = 1;
//byte leds[1][3];
int R = 0;
int G = 1;
int B = 2;

void setup()
{
  // leds[amount][3] = new byte[amount][3];
  pinMode(datapin, OUTPUT);
  pinMode(debug_led, OUTPUT);
  digitalWrite(13, LOW);
  datamask = B00010000;          //TODO Mask adapts to Data Pin
}

void loop()
{
  digitalWrite(13, LOW);
  test();
  digitalWrite(13, HIGH); 
}

void test()
{
  bitHigh();
  bitHigh();
  bitHigh();
  bitHigh();
  bitHigh();
  bitHigh();
  bitHigh();
  bitHigh();
  bitHigh();
  bitHigh();
  bitHigh();
  bitHigh();
  bitHigh();
  bitHigh();
  bitHigh();
  bitHigh();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();

  /*bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();
  bitLow();*/

  PORTD = datamask; //LOW
  delay(50);
}

/*void draw()
{
  for(int i=0; i<sizeof(leds); i++)
  {
    
  }
}*/

void bitLow()
{
  for(int i=0; i<6; i++)
  {
    PORTD = ~datamask; //HIGH
  }
  for(int i=0; i<14; i++)
  {
    PORTD = datamask; //LOW
  }
}

void bitHigh()
{
  for(int i=0; i<13; i++)
  {
    PORTD = ~datamask; //HIGH
  }
  for(int i=0; i<7; i++)
  {
    PORTD = datamask; //LOW
  }
}

void bitReset()
{
  for(int i=0; i<800; i++)
  {
    PORTD = datamask; //LOW
  }
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

