//*****************************************************************************
// CHUONG TRINH DIEU KHIEN LCD SU DUNG CHIP DRIVER HD4470 HITACHI
// 
// Che do hoat dong: 4-bit Mode
// Dia chi hang: bat dau tu 0 -> 4
// Dia chi cot:  bat dau tu 0 -> 40 (tuy nhien tuy vao lcd ma so cot duoc hien thi khac nhau)
//*****************************************************************************
//
#include <htc.h>
#include <pic.h>
#include <ctype.h>
#include <stdlib.h>
#include "lcd_4bit.h"


//-----------------------------------------------------------------------------
// Ten ham:   lcd_4bit_init()
//
// Chuc nang: khoi tao cac chan IO cho LCD
//-----------------------------------------------------------------------------

void lcd_init()
{
    LCD_EN_TRIS = 0;
    LCD_RS_TRIS = 0;
    LCD_RW_TRIS = 0;
    LCD_DATA7_TRIS = 0;
    LCD_DATA6_TRIS = 0;
    LCD_DATA5_TRIS = 0;
    LCD_DATA4_TRIS = 0;

    LCD_EN_PIN = 0;
    LCD_RS_PIN = 0;
    LCD_RW_PIN = 0;
    lcd_delay(100);

    // reset lcd
    lcd_command(0x30);
    lcd_wait_busy();
    lcd_command(0x30);
    lcd_wait_busy();
    lcd_command(0x30);
    lcd_wait_busy();
    lcd_command(0x32);
    lcd_wait_busy();
    lcd_delay(100); //wait for lcd reset

    // setup lcd
    lcd_command(_LCD_4BIT_DEFAULT_MODE); //command value: 0x28 - set function
    lcd_wait_busy();
    lcd_command(_LCD_CUR_OFF & _LCD_BLINK_OFF); //command value: 0x0c - set display control
    lcd_wait_busy();
    lcd_command(_LCD_SHIFT_DISP_LEFT); //command value: 0x06 - set entry mode
    lcd_wait_busy();
    lcd_command(_LCD_CLEAR);
    lcd_delay(1000);
}


//-----------------------------------------------------------------------------
// Ten ham: lcd_write_char(char charactor)
//
// Tham so truyen vao: charactor - du lieu can xuat ra LCD
//
// Chuc nang: xuat mot byte du lieu hoac mot ky tu ra LCD
//-----------------------------------------------------------------------------

void lcd_putc(char charactor)
{
    lcd_wait_busy(); // wait for lcd not busy
    LCD_RS_PIN = 1;
    LCD_RW_PIN = 0;
    LCD_EN_PIN = 0;

    write_data(charactor);
}


//-----------------------------------------------------------------------------
// Ten ham: lcd_write_string(char *string_char)
//
// Tham so truyen vao: *string_char - chuoi ky tu can hien thi ra LCD
//
// Chuc nang: hien thi mot chuoi ky tu ra LCD
//-----------------------------------------------------------------------------

void lcd_puts(const char *string_char)
{
    do
    {
        lcd_putc(*string_char);
        string_char++;
    }
    while (*string_char);
}


//-----------------------------------------------------------------------------
// Ten ham: lcd_command(unsigned char _command)
//
// Tham so truyen vao: _command: la cac lenh dieu khien hoat dong cua LCD, co the
//								 la so hex hoac cac define duoc dinh nghia o file lcd_4bit.h
//
// Chuc nang: ghi cac lenh dieu khien chuc nang hoat dong cua LCD
//-----------------------------------------------------------------------------

void lcd_command(unsigned char _command)
{
    lcd_wait_busy(); // wait for lcd not busy
    LCD_RS_PIN = 0;
    LCD_RW_PIN = 0;
    write_data(_command);
}


//-----------------------------------------------------------------------------
// Ten ham: lcd_clear()
//
// Chuc nang: xoa hien thi
//-----------------------------------------------------------------------------

void lcd_clear()
{
    lcd_wait_busy(); // wait for lcd not busy
    LCD_RS_PIN = 0;
    LCD_RW_PIN = 0;
    write_data(_LCD_CLEAR);
}
//-----------------------------------------------------------------------------
// Ten ham: lcd_wait_busy()
//
// Chuc nang: kiem tra co ban cua LCD va cho cho den khi LCD het ban
//-----------------------------------------------------------------------------

void lcd_wait_busy()
{
    unsigned char busy;

    LCD_DATA7_TRIS = 1; // set PIN as input

    LCD_RW_PIN = 1;
    LCD_RS_PIN = 0;

    do
    {
        LCD_EN_PIN = 1; //get 4-bit hight data
        lcd_delay(10);
        busy = LCD_DATA7_PIN; //and assign MSB-bit for busy
        LCD_EN_PIN = 0;

        LCD_EN_PIN = 1; //get 4-bit low data
        lcd_delay(10);
        LCD_EN_PIN = 0; //and do nothing else
    }
    while (busy);

    LCD_DATA7_TRIS = 0; // set PIN as output
}


//-----------------------------------------------------------------------------
// Ten ham: write_data(unsigned char _data)
//
// Tham so truyen vao: _data: la cac lenh, cac du lieu can dua vao LCD
//
// Chuc nang: su dung de dua du lieu vao LCD theo kieu 4bit, phuc vu cho cac ham khac
//-----------------------------------------------------------------------------

void write_data(unsigned char _data)
{
    unsigned char H_data = 0, L_data = 0;

    H_data = _data & 0xf0; // 4-bit high data
    L_data = (_data << 4)&0xf0; // 4-bit low data

    LCD_EN_PIN = 0;

    LCD_DATA7_PIN = (H_data >> 7)&1;
    LCD_DATA6_PIN = (H_data >> 6)&1;
    LCD_DATA5_PIN = (H_data >> 5)&1;
    LCD_DATA4_PIN = (H_data >> 4)&1;

    LCD_EN_PIN = 1;
    LCD_EN_PIN = 0;
    lcd_delay(10);

    LCD_DATA7_PIN = (L_data >> 7)&1;
    LCD_DATA6_PIN = (L_data >> 6)&1;
    LCD_DATA5_PIN = (L_data >> 5)&1;
    LCD_DATA4_PIN = (L_data >> 4)&1;

    LCD_EN_PIN = 1;
    LCD_EN_PIN = 0;
    lcd_delay(10);
}


//-----------------------------------------------------------------------------
// Ten ham: lcd_delay(unsigned int time)
//
// Tham so truyen vao: time - so chu ky may muon tao tre
//
// Chuc nang: tao tre so chu ky may, dam bao toc do hoat dong cua LCD va MCU
//-----------------------------------------------------------------------------

void lcd_delay(unsigned int time)
{
    while (time)
    {
        time--;
    }
}


//-----------------------------------------------------------------------------
// Ten ham: lcd_goto_row_col(unsigned char row, unsigned char col)
//
// Tham so truyen vao:
//			+ row: 0 -> 4 : vi tri hang muon di chuyen den
//			+ col: 0 -> 39: vi tri cot muon di chuyen den
//
// Chuc nang: dua con tro den vi tri hang-cot mong muon
//-----------------------------------------------------------------------------

void lcd_gotoxy(unsigned char col, unsigned char row)
{
    unsigned char address;

    switch (row)
    {
    case 0: address = 0x00;
        break; //line 1: begin 0  (0x00) -> 39  (0x27)
    case 1: address = 0x40;
        break; //line 2: begin 64 (0x40) -> 103 (0x67)
    case 2: address = 0x14;
        break; //line 3: begin 64 (0x40) -> 103 (0x67)
    case 3: address = 0x54;
        break; //line 4: begin 64 (0x40) -> 103 (0x67)
    default:address = 0x00;

    }

    address += col;
    lcd_command(0x80 | address); //goto memory cell at address of DDRAM (setup DDRAM address)
    lcd_wait_busy();
}


//-----------------------------------------------------------------------------
// Ten ham: lcd_custom_char(char row, char col, char add_cgram, unsigned char custom_char[])
//
// Tham so truyen vao:
//			+ row		: 0 -> 4 : vi tri hang muon di chuyen den
//			+ col		: 0 -> 39: vi tri cot muon di chuyen den
//			+ add_cgram	: 0 -> 7 : dia chi vung nho dung de luu ky tu muon tao
//								   bo nho CGRAM co 64 o tuong ung voi 8 ky tu ,
//			+ custom_char:  mang chua ma cua ky tu muon tao ra
//
// Chuc nang: ghi mot ky tu tu tao vao CGRAM va xuat ra tai vi tri hang-cot mong muon
//-----------------------------------------------------------------------------

void lcd_custom_char(char row, char col, char add_cgram, const char custom_char[])
{
    char i, add_cgram_cell = 1;

    add_cgram_cell = add_cgram * 8;

    lcd_command(_LCD_SET_CGRAM | add_cgram_cell); //set CGRAM address

    for (i = 0; i < 8; i++)lcd_putc(custom_char[i]);

    lcd_gotoxy(col, row);
    lcd_putc(add_cgram);
}


//-----------------------------------------------------------------------------
// Ten ham: lcd_write_cgram(char add_cgram, unsigned char custom_char[])
//
// Tham so truyen vao:
//			+ add_cgram	: 0 -> 7 : dia chi vung nho dung de luu ky tu muon tao
//								   bo nho CGRAM co 64 o tuong ung voi 8 ky tu ,
//			+ custom_char:  mang chua ma cua ky tu muon tao ra
//
// Chuc nang: ghi mot ky tu tu tao vao CGRAM (day la chuong trinh nho cua chuong
//			  trinh lcd_custom_char() phia tren
//-----------------------------------------------------------------------------

void lcd_write_cgram(char add_cgram, const char custom_char[])
{
    char i, add_cgram_cell = 1;

    add_cgram_cell = add_cgram * 8;
    lcd_command(_LCD_SET_CGRAM | add_cgram_cell); //set CGRAM address

    for (i = 0; i < 8; i++)
    {
        lcd_putc(custom_char[i]);
    }

    lcd_gotoxy(0, 0); //dua con tro ve dau dong hang thu nhat
}



//-----------------------------------------------------------------------------
// Ten ham: putch(char c)
//
// Chuc nang: dung de xuat du lieu ra LCD bang lenh printf()
// Cach dung: printf("%u chuoi can xuat", gia_tri);
// voi gia tri la 1 bien nguyen duoc thay vao %u (unsigned)
// xem them ham printf cua C
//-----------------------------------------------------------------------------

void putch(char c)
{
    lcd_putc(c);
}