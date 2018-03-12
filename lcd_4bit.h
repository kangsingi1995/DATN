#ifndef _LCD_4BIT_H_
#define _LCD_4BIT_H_

#include <htc.h>  //use include for Hitech C complier
//#include <xc.h>     //use include for XC8 complier
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef _XTAL_FREQ
		#define _XTAL_FREQ	4000000
	#endif
//LCD pins mapping
#define LCD_RS_PIN			RD1
#define LCD_RW_PIN			RD2
#define LCD_EN_PIN			RD3
#define LCD_DATA4_PIN		RD4
#define LCD_DATA5_PIN		RD5
#define LCD_DATA6_PIN		RD6
#define LCD_DATA7_PIN		RD7

#define LCD_RS_TRIS			TRISD1
#define LCD_RW_TRIS			TRISD2
#define LCD_EN_TRIS			TRISD3
#define LCD_DATA4_TRIS		TRISD4
#define LCD_DATA5_TRIS		TRISD5
#define LCD_DATA6_TRIS		TRISD6
#define LCD_DATA7_TRIS		TRISD7


// LCD display commands (use operation AND BIT "&" to combine effects)
#define _LCD_ON_ALL				0b00001111		// display on, on cursor and blink it
#define _LCD_OFF				0b00001011		// display off
#define _LCD_CUR_OFF			0b00001101		// cursor off
#define _LCD_BLINK_OFF			0b00001110		// cursor not blink
#define _LCD_CUR_AND_BLINK_OFF	0b00001100		// cursor off and not blink

#define	_LCD_CLEAR				0b00000001		// clear screen and move cursor to home
#define _LCD_CUR_TO_HOME		0b00000010		// move cursor to home

// LCD Entry Mode Set commands
#define _LCD_SHIFT_CUR_LEFT    	0b00000100		// Cursor shifts to the left
#define _LCD_SHIFT_CUR_RIGHT   	0b00000101		// Cursor shifts to the right
#define _LCD_SHIFT_DISP_LEFT   	0b00000110		// Display shifts to the left
#define _LCD_SHIFT_DISP_RIGHT  	0b00000111		// Display shifts to the right


// LCD Function set commands (use operation OR BIT "|" to combine funcitons)
#define _LCD_4BIT_MODE			0b00100000		// select 4-bit protocol mode
#define _LCD_8BIT_MODE			0b00110000		// select 8-bit protocol mode

#define _LCD_1LINE_MODE			0b00100000		// select 1 line display mode
#define _LCD_2LINE_MODE			0b00101000		// select 2 lines display mode

#define _LCD_FONT_5X7_MODE		0b00100000		// select font 5x7 display mode
#define _LCD_FONT_5X10_MODE 	0b00100100		// select font 5x10 display mode

#define _LCD_4BIT_DEFAULT_MODE 	0b00101000		// select 4-bit mode, 2 lines display, font 5x7
#define _LCD_8BIT_DEFAULT_MODE 	0b00111000		// select 8-bit mode, 2 lines display, font 5x7


//LCD set CGRAM
#define _LCD_SET_CGRAM			0b01000000


//
//List Function
//

//cac lenh su dung dieu khien lcd
void write_data(unsigned char _data);
void lcd_delay(unsigned int time);
void lcd_wait_busy();

//cac lenh cau hinh khoi tao lcd
void lcd_init();
void lcd_command(unsigned char _command);

//cac lenh xuat du lieu ra lcd
void lcd_clear();
void lcd_putc(unsigned char charactor);
void lcd_puts(const char *string_char);
void lcd_gotoxy(unsigned char col, unsigned char row);

//cac lenh ghi ky tu dac biet vao CGRAM
void lcd_custom_char(char row, char col, char add_cgram, const char custom_char[]);
void lcd_write_cgram(char add_cgram, const char custom_char[]);
#endif