#include "main.h"

void systemtimer0()
{
	T0CS=0;
	T0IF=0;
	T0IE=1;
	GIE=1;
	TMR0=131;
	PSA=0;
	PS0=0;
	PS1=0;
	PS2=1;
}

void setup_timer0(char tinhieu,char prescaler)
{
	switch(tinhieu)
	{
		case internal :
			PSA=0;
			T0CS=0;
			T0IF=0;
			break;
		case external:
			T0CS=1;
			PSA=1;
			break;
		default : break;
	}
	switch(prescaler)
	{
		case Tile2 :
		 	 PS2 = 0;
		 	 PS1 = 0;
			 PS0 = 0;
			break;
		case Tile4:
		 	 PS2 = 0;
		 	 PS1 = 0;
			 PS0 = 1;
			break;
		case Tile8:
		 	 PS2 = 0;
		 	 PS1 = 1;
			 PS0 = 0;
			break;
		case Tile16:
		 	 PS2 = 0;
		 	 PS1 = 1;
			 PS0 = 1;
			break;
		case Tile32:
		 	 PS2 = 1;
		 	 PS1 = 0;
			 PS0 = 0;
			break;
		case Tile64:
		 	 PS2 = 1;
		 	 PS1 = 0;
			 PS0 = 1;
			break;
		case Tile128:
		 	 PS2 = 1;
		 	 PS1 = 1;
			 PS0 = 0;
			break;
		case Tile256:
		 	 PS2 = 1;
		 	 PS1 = 1;
			 PS0 = 1;
			break;
		default :
			break;
	}
}

void set_timer(unsigned char value)
{	
	TMR0=value;
}

void systemtimer2()
{
	

}
