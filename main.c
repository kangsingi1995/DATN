#include "main.h"
__CONFIG(0x20E2);
__CONFIG(0x3FFF);

unsigned char arrayMapOfNumber [16] = {1,2,3,'A',4,5,6,'B',
                                       7,8,9,'C','*',0,'E','D'};
unsigned char StringDisplay[]="123A456B789C*0#D";
unsigned char NumberDisplay();


char dem=9;
void Nhapso();
void ketqua();
unsigned char arrayresutl[2];

//----------------------------------------------------------------------------------
unsigned char arrayPassword[4];


int Num=9;
//----------------------------------------------------------------------------------
// khai báo các nút
unsigned char isButton1();
unsigned char isButton2();
unsigned char isButton3();
unsigned char isButtonsao();
//----------------------------------------------------------------------------------
void main()
{
	ANSEL=0;
	ANSELH=0;
    nRBPU = 0;//cho phép dien tro kéo lên
	WPUB=0x0f;
	system1();
    lcd_init();
    lcd_putc('\f');
    Delay(2);
	while(1)
	{
        scan_key_matrix();
        hethong();
      
       
	}	
}
unsigned char NumberDisplay()
{
    for(int i = 0;i<=15;i++)
    {
        if(key_code[i]==1)
            return i;
    }
}

//----------------------------------------------------------------------------------
void system1(void)
{
	TRIS_BUTTON = 0x0f; 
	PORT_BUTTON = 0xff;
}
//----------------------------------------------------------------------------------
void Delay(char time)
{
    int i;
    for(i=0;i<=time;i++)
        __delay_ms(100);
}


//---------------------------------------------------------------------
unsigned char isButtonNumber()
{
    unsigned char i;
    for (i = 0; i<=15; i++)
        if (key_code[i] == 1)
        {
            numberValue = arrayMapOfNumber[i];
            return 1;
        }
    return 0;
}


void kiemtranut()
{
    if(isButtonNumber()==1)
           {
               if(dem>=9 && dem <=10)
               {
                    lcd_gotoxy(dem,LINE2);    
                    lcd_putc(StringDisplay[NumberDisplay()]);
                    dem++;   
               }
           }
    
}


//----------------------------------------------------------------
// các nút dc nh?n 
unsigned char isButton1()
{
    if (key_code[0] == 1)
        return 1;
    else
        return 0;
}
unsigned char isButton2()
{
    if (key_code[1] == 1 || (key_code[1] >= 50 && key_code[1]%2 == 1))
        return 1;
    else
        return 0;
}
unsigned char isButton3()
{
    if (key_code[2] == 1 || (key_code[2] >= 50 && key_code[2]%2 == 1))
        return 1;
    else
        return 0;
}
unsigned char isButtonsao()
{
    if (key_code[12] == 1 || (key_code[12] >= 50 && key_code[12]%2 == 1))
        return 1;
    else
        return 0;
}
//-----------------------------------------------------------------------

//xuat nhap
