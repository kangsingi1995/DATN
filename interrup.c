#include "main.h"

void interrupt isr()
{
    if(INTE && INTF)
    {
        INTF = 0;
        STOP = 1;
        dk1 = 0;
        dk2 = 0;
        cb = 0;
        biennho1 = 0;
        biennho2 = 0;
        demdao = 0;
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
        case ngatPortB:
            nRBPU = 0;//cho phép dien tro kéo lên
            //WPUB0=1;//khai báo kéo tro lên là chân B0
            WPUB=0b00000111;
            INTEDG = 0;
            RBIF = 0;
            RBIE = 1;
            GIE = 1;
            IOCB = 0b00000111;
            break;
		
	}			
}

