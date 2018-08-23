#ifndef	main_h
#define	main_h

#include <htc.h>
//#include <math.h>
#include<stdio.h>
#include"interrup.h"
#include "lcd4x20.h"
#include "timer.h"
#include"button.h"

#define	_XTAL_FREQ	8000000

#define LINE1 0//dinh nghia hang 1 
#define LINE2 1//dinh nghia hang 2
#define LINE3 2 
#define LINE4 3


#define DcChinh             RB3
//----------------------------------------------------------------------
// Define các bien   
#define HANDLE              101
#define SET_DAI             102
#define SET_SO_LUOI         103
#define SO_LAN_EP           104
#define DO_EP               105
#define MAI_THO             106
#define MODE_1              107
#define MODE_2              108
#define START               109

//----------------------------------------------------------------------
unsigned char statusMachine = HANDLE;
unsigned char arrayMapOfNumber [16] = {1,2,3,'A',4,5,6,'B',
                                       7,8,9,'C','*',0,'E','0'};
unsigned char numberValue;
unsigned char indexOfNumber = 0;
unsigned char demgiatri = 0;
unsigned char GiaTri[4];
int ChieuDai = 0, DoEpDao = 0;
unsigned char SoLuoi = 0, SoLanMaiTinh = 0;    
volatile unsigned char STOP = 0;
unsigned char press = 0;

unsigned char cb1 = 0;
unsigned char cb2 = 0;
unsigned char cb = 0;
unsigned char dk1 = 0, dk2 = 0, dk3 = 0;
volatile int biennho1 = 0, biennho2 = 0;
volatile unsigned char demdao = 0;
//----------------------------------------------------------------------

void system1(void);
void Delay(char time);
int Number();
int TinhGiaTri();
void Maychay();

//----------------------------------------------------------------------------------
// khai báo các nút
unsigned char isButtonMode();
unsigned char isButtonsao();
unsigned char ButtonEnter();
unsigned char isButtonNumber();
unsigned char isButtonCancel();
unsigned char isButtonUp();
unsigned char MotorON();
unsigned char Len();
unsigned char Xuong();
unsigned char Ra();
unsigned char Vao();
unsigned char ChuyenLuoiPhai();
unsigned char ChuyenLuoiTrai();
unsigned char ServoOn();
unsigned char Cap2kXungXuong();
unsigned char Cap2kXungLen();
//----------------------------------------------------------------------------------
#endif