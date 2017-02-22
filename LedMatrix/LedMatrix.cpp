#include "LedMatrix.h"

byte[][] leds;

LedMatrix::LedMatrix(int amount)
{
	byte[][] leds = ;
}

void::draw()
{
	for(int i=0; i<sizeof(leds); i++)
	{
		leds[i][0]
	}
}

boolean[] toBits(byte color)
{
	boolean[] output = new boolean[8];
	byte buff;
	
	for(int i=7; i<0; i--)
	{
		buff = color >> i;
		
		if(buff & 1)
		{
			output[i] = true;
		}
		else
		{
			output[i] = false;
		}
	}
}
