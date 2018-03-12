#include "main.h"

void interrupt isr(void)
{
	if(T0IF)
	{
		T0IF=0;
		count++;
		if(count==125)
		{
			count=0;
			RE2=~RE2;	
		}
	}
	if(INTF&&INTE)
	{
		INTF=0;
		count++;//sau m?i l?n nh?n press s? t? tang 1 don v?
			switch(count)
			{
				case 1: 
					RE1 = 1;
					RE2	= 0;
					Delay(5);
					break;
				case 2:
					RE1 = 0;
					RE2	= 1;
					Delay(5);
					break;
				case 3: 
					RE1 = 1;
					RE2	= 1;
					Delay(5);
					break;
				default: 
					RE1 = 0;
					RE2	= 0;
					Delay(5);
				    count = 0;
					break;	
			}
			
		
	}
}

void enble_interrupt(char name_interrupt)
{
	switch(name_interrupt)
	{
		case global:
			 GIE=1;
		   	 break;
		case timer0:
			 T0IE=1;
			 T0IF=0;
			 break;
		case timer2:
			 TMR2IE=1;
			 TMR2IF=0;
			 break;
		case ngatRB0:
			 INTEDG = 0;
			 INTE=1;
			 INTF=0;
 			break;
		
	}			
}

