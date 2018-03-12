#include "main.h"
__CONFIG(0x20E2);
__CONFIG(0x3FFF);

unsigned char arrayMapOfNumber [16] = {1,2,3,'A',4,5,6,'B',
                                       7,8,9,'C','*',0,'E','D'};
unsigned char StringDisplay[]="123A456B789C*0#D";
unsigned char NumberDisplay();

#define     INIT_SYSTEM        0
#define     Nhap               1
#define     TANG               2
#define     GIAM               3
#define     WRONG_PASSWORD     4
unsigned char arrayMapOfOutput [8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
unsigned char statusOutput[8] = {0,0,0,0,0,0,0,0};
unsigned char chuoihienthi[]="0123456789";
unsigned char tram=0,chuc=0,dv=0,tmp=0;
unsigned char ht,hc,dv,x,y,z,count1=0,couter=0;
char dem=9;
void Nhapso();
void ketqua();
unsigned char arrayresutl[2];

//----------------------------------------------------------------------------------
unsigned char arrayPassword[4];
unsigned char status = INIT_SYSTEM;

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
void hethong()
{
    switch(status)
    {
        case INIT_SYSTEM :
            lcd_gotoxy(5,LINE1);
            lcd_puts("Cac che do");
            lcd_gotoxy(0,LINE2);
            lcd_puts("1.Nhap :");
            lcd_gotoxy(0,LINE3);
            lcd_puts("2.TANG :");
            lcd_gotoxy(0,LINE4);
            lcd_puts("3.GIAM :");
            if(isButton1())
            {
                status=Nhap;
                lcd_putc('\f');
            }
            break;
        case Nhap :
            lcd_gotoxy(4,LINE1);
            lcd_puts("Nhap Du Lieu ");
            lcd_gotoxy(0,LINE2);
            lcd_puts("So lieu :");
            lcd_gotoxy(10,LINE2);
            kiemtranut();
            //Nhapso();
            couter=0;
            if(isButtonNumber())
            {
                couter++;
                arrayresutl[count1]=numberValue;
//                x= arrayresutl[0];
//                y=arrayresutl[1];
//                z=x*10+y;
                count1++;
            }
            if(isButtonsao())
            {
                if(couter==1)
                {
                    x=arrayresutl[0];
                    arrayresutl[1]=0;
                    y=arrayresutl[1];
                    z=x;
                }
                else
                {
                    x= arrayresutl[0];
                    y=arrayresutl[1];
                    z=x*10+y;
                }
                lcd_putc('\f');
                status =TANG;
            }
            break;
        case TANG :
            lcd_gotoxy(2,LINE1);
            lcd_puts("Ket qua");
            ketqua();
            break;
            
    }
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
void ketqua()
{
    hc=z/10;
    dv=z%10;
    //lcd_gotoxy(9,LINE2);
    //lcd_puts("  ");
    lcd_gotoxy(9,LINE2);
    lcd_putc(chuoihienthi[hc]);
    lcd_gotoxy(10,LINE2);
    lcd_putc(chuoihienthi[dv]);
}

//xuat nhap

void Nhapso()
{
    if(isButton2())Num++;
    if(isButton3())Num--;
    if(Num>=0&&Num<10)
    {
        lcd_gotoxy(9,LINE2);
        lcd_puts("  ");
        lcd_gotoxy(9,LINE2);
        lcd_putc(chuoihienthi[Num]);
    }        
    if(Num>=10&&Num<100)
    {
        chuc=Num/10;
        dv=Num%10;
        lcd_gotoxy(9,LINE2);
        lcd_puts("  ");
        lcd_gotoxy(9,LINE2);
        lcd_putc(chuoihienthi[chuc]);
        lcd_gotoxy(10,LINE2);
        lcd_putc(chuoihienthi[dv]);
    }
    if(Num>=100&&Num<=999)
    {
        tram=Num/100;
        tmp=Num%100;
        chuc=tmp/10;
        dv=tmp%10;
        lcd_gotoxy(9,LINE2);
        lcd_puts("   ");
        lcd_gotoxy(9,LINE2);
        lcd_putc(chuoihienthi[tram]);
        lcd_gotoxy(10,LINE2);
        lcd_putc(chuoihienthi[chuc]);
        lcd_gotoxy(11,LINE2);
        lcd_putc(chuoihienthi[dv]);
    }   
}
