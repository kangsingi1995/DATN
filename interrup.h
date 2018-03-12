#ifndef	interrupt_h
#define	interrupt_h

#define	global	0
#define	timer0	1
#define	timer1	2
#define	timer2	3
#define ngatRB0 4

void interrupt isr();
void enble_interrupt(char name_interrupt);
#endif