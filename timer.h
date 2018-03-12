#ifndef timer_h
#define	timer_h



void systemtimer0();
void setup_timer0(char tinhieu,char prescaler);
void set_timer (unsigned char value);
void systemtimer2();

#define internal	0
#define external	1

#define Tile2		1
#define Tile4		2
#define Tile8		3
#define Tile16		4
#define Tile32		5
#define Tile64		6
#define Tile128		7
#define Tile256		8
#endif