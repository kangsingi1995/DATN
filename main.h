#ifndef	main_h
#define	main_h

#include <htc.h>
//#include <math.h>
//#include<stdio.h>
#include"interrup.h"
#include"lcd_4bit.h"
#include "timer.h"
#include "adc.h"
#include"button.h"

#define	_XTAL_FREQ	4000000

#define LINE1 0//dinh nghia hang 1 
#define LINE2 1//dinh nghia hang 2
#define LINE3 2 
#define LINE4 3

#include "button.h"

unsigned char count=0;

void system1(void);
unsigned char isButtonNumber();
unsigned char numberValue;
void Delay(char time);
void Test_KeyMatrix();
void hethong();
void kiemtranut();
void testnut();

#endif