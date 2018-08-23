#ifndef _BUTTON_H_
#define _BUTTON_H_


#define PORT_BUTTON		PORTD
#define TRIS_BUTTON		TRISD
#define	MAX_COL			4
#define MAX_ROW			4

extern unsigned int key_code[];

//#include <p16f887.h>

void init_key_matrix();
void scan_key_matrix();
void button_process();
void button_delay_ms(int value);
void scan_key_matrix_demo();
void scan_key_button();

#endif