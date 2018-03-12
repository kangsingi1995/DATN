#include"main.h"

void _KhoiTao_ADC(void)
{
	ADFM=1;			//Dinh dang 10 bit ket qua chuyen doi AD (canh phai -> LSB)
	ADCON0=0;		//Khoi dong thanh ghi ADCON0
	ADCS0=1;	//Chon xung chuyen doi AD tu mach RC trong chip
	ADCS1=1;				
}

unsigned int _Read_ADC(char Kenh)
{
	_ChonKenh(Kenh);
	__delay_us(5);		//CHo ADC thuc hien lay mau
	GO_nDONE = 1;			//bat dau thuc hien chuyen doi AD
	while (GO_nDONE);		//Cho ADC thuc hien chuyen doi xong
						//Tra ve ket qua ADC sau khi chuyen doi xong
	return (((unsigned int)ADRESH)<<8)|ADRESL;	//Ghep byte thap va byte cao cua gia tri ADC
//[7][6][5][4][3][2][1][0] [7][6][5][4][3][2][1][0]
//ADRESH	:	ADRESL
//ADON=0;	//Khong cho phep ADC hoat dong	
}

void ChonKenh(char Kenh)
{
	switch(Kenh)
	{
		case 0:
		{
			CHS0=0;		//Chon kenh chuyen doi AD la AN0
			CHS1=0;
			CHS2=0;
            CHS3=0;
			ADON=1;		//CHo phep ADC hoat dong			
			break;
		}
		case 1:
		{
			CHS0=1;		//Chon kenh chuyen doi AD la AN1
			CHS1=0;
			CHS2=0;
            CHS3=0;
			ADON=1;		//CHo phep ADC hoat dong			
			break;
		}
		case 2:
		{
			CHS0=0;		//Chon kenh chuyen doi AD la AN2
			CHS1=1;
			CHS2=0;
            CHS3=0;
			ADON=1;		//CHo phep ADC hoat dong			
			break;
		}
		case 3:
		{
			CHS0=1;		//Chon kenh chuyen doi AD la AN3
			CHS1=1;
			CHS2=0;
            CHS3=0;
			ADON=1;		//CHo phep ADC hoat dong			
			break;
		}
		case 4:
		{
			CHS0=0;		//Chon kenh chuyen doi AD la AN4
			CHS1=0;
			CHS2=1;
            CHS3=0;
			ADON=1;		//CHo phep ADC hoat dong			
			break;
		}
		case 5:
		{
			CHS0=1;		//Chon kenh chuyen doi AD la AN5
			CHS1=0;
			CHS2=1;
            CHS3=0;
			ADON=1;		//CHo phep ADC hoat dong			
			break;
		}
		case 6:
		{
			CHS0=0;		//Chon kenh chuyen doi AD la AN6
			CHS1=1;
			CHS2=1;
            CHS3=0;
			ADON=1;		//CHo phep ADC hoat dong			
			break;
		}
		case 7:
		{
			CHS0=1;		//Chon kenh chuyen doi AD la AN6
			CHS1=1;
			CHS2=1;
            CHS3=0;
			ADON=1;		//CHo phep ADC hoat dong			
			break;
		}
        case 8:
		{
			CHS0=0;	
            CHS2=0;//Chon kenh chuyen doi AD la AN6
			CHS2=0;
			CHS3=1;
			ADON=1;		//CHo phep ADC hoat dong			
			break;
		}
        case 9:
		{
			CHS0=1;		//Chon kenh chuyen doi AD la AN6
			CHS1=0;
            CHS2=0;
			CHS3=1;
			ADON=1;		//CHo phep ADC hoat dong			
			break;
		}
        case 10:
		{
			CHS0=0;		//Chon kenh chuyen doi AD la AN6
			CHS1=1;
			CHS2=0;
            CHS3=1;
			ADON=1;		//CHo phep ADC hoat dong			
			break;
		}
        case 11:
		{
			CHS0=1;		//Chon kenh chuyen doi AD la AN6
			CHS1=1;
			CHS2=0;
            CHS3=1;
			ADON=1;		//CHo phep ADC hoat dong			
			break;
		}
        case 12:
		{
			CHS0=0;		//Chon kenh chuyen doi AD la AN6
			CHS1=0;
			CHS2=1;
            CHS3=1;
			ADON=1;		//CHo phep ADC hoat dong			
			break;
		}
        case 13:
		{
			CHS0=1;		//Chon kenh chuyen doi AD la AN6
			CHS1=0;
            CHS2=1;
			CHS3=1;
			ADON=1;		//CHo phep ADC hoat dong			
			break;
		}
		default:
		{
			break;
		}	
	}
}

