#include "main.h"
#include <htc.h>
__CONFIG(0x20E2);
__CONFIG(0x3FFF);
// Bien Dinh Nghia Chuong Trinh.
//------------------------------------------------------------------------------
#define Stop            RB0
#define SER_ON          RB1
#define ThangLuoi       RB2
// Bien Dinh Nghia Chuong Trinh.
//------------------------------------------------------------------------------

unsigned char SoLan = 0, Luoi = 0, LanMai = 0, DoEp = 0, MaiTho = 0;
unsigned char SLMaiTho = 0; // so lan mai tho
unsigned char countSV = 0;


// Ham thuc thi
//------------------------------------------------------------------------------
void CuaStart();
void CuaStart2();
void maidao();
void maidao2();
void motorX(); //dk dong co buoc truc X
void motorY(); //dk dong co buoc truc Y
void MotorEpTruc(); //dk dong co buoc ep truc
void chuyenluoi(); //servo
void ChuTrinhMaiTho();
void ChuTrinhMaiTho2();
void hamphu2();
//------------------------------------------------------------------------------

int xung1 = 100;

void main() {
    ANSEL = 0;
    ANSELH = 0;
    system1();
    lcd_init();
    nRBPU = 0; //cho phép dien tro kéo lên
    //WPUB0=1;//khai báo kéo tro lên là chân B0
    WPUB = 0b11100001;
    INTEDG = 0; // Chon canh lên /xuong voi các bit 1/0
    INTF = 0; // Xóa  ngat ngoài
    INTE = 1; // Bit cho phép ngat ngoài
    GIE = 1; // Bit cho phép ngat tong  



    lcd_gotoxy(0, 0);
    lcd_puts("Do An Tot Nghiep");
    __delay_ms(1000);
    lcd_putc('\f');
    while (1) {
        scan_key_matrix();
        switch (statusMachine) {
            case HANDLE:
                RC7 = 1; //cho enable tat ca cac dong co
                lcd_gotoxy(0, 0);
                lcd_puts("SO LUOI:");
                lcd_gotoxy(12, 0);
                printf("%d", SoLuoi);
                lcd_gotoxy(0, 1);
                lcd_puts("CHIEU DAI:");
                lcd_gotoxy(15, 1);
                lcd_puts("MM");
                lcd_gotoxy(12, 1);
                printf("%d", ChieuDai);
                lcd_gotoxy(0, 2);
                lcd_puts("SO LAN MAI:");
                lcd_gotoxy(12, 2);
                printf("%d", LanMai);
                lcd_gotoxy(0, 3);
                lcd_puts("DO EP:");
                lcd_gotoxy(15, 3);
                lcd_puts("UM");
                lcd_gotoxy(12, 3);
                printf("%d", DoEp);
                if (ServoOn()) {                 
                    countSV++;
                    if(countSV%2==0)
                    {
                        RB1 = 0; // servo ON
                    }
                    else
                        RB1 = 1; // servo ON
                    STOP = 0;
                }
                if (isButtonMode()) {
                    statusMachine = SET_SO_LUOI;
                }
                if (ButtonEnter()) {
                    lcd_putc('\f');
                    STOP = 0;
                    SoLan = 0;
                    Luoi = 0;
                    SLMaiTho = 0;
                    statusMachine = START;
                }
                if (MotorON()) {
                    DcChinh = 1;
                }
                if (Len()) {
                    RC6 = 0;
                    motorX();
                }
                if (Xuong()) {
                    RC6 = 1;
                    motorX();
                }
                if (Vao()) {
                    RE2 = 0;
                    motorY();
                }
                if (Ra()) {
                    RE2 = 1;
                    motorY();
                }
                if (ChuyenLuoiTrai()) {
                    int pulse = 24000, tong = 0, count = 0;
                    pulse = 24000 / SoLuoi;
                    for (unsigned int i = 0; i < pulse; i++) {
                        RC1 = 1;
                        __delay_us(40);
                        RC1 = 0;
                        __delay_us(40);
                        if (STOP == 1)
                            break;
                    }
                }
                if (ChuyenLuoiPhai()) {
                    int pulse = 24000, tong = 0, count = 0;
                    pulse = 24000 / SoLuoi;
                    for (unsigned int i = 0; i < pulse; i++) {
                        RC2 = 1;
                        __delay_us(40);
                        RC2 = 0;
                        __delay_us(40);
                        if (STOP == 1)
                            break;
                    }
                }
                if (Cap2kXungXuong()) {
                    RE2 = 0;
                    for (int po = 0; po < 2000; po++) {
                        motorY();
                    }
                }
                if (Cap2kXungLen()) {
                    RE2 = 1;
                    for (int po = 0; po < 2000; po++) {
                        motorY();
                    }
                }
                break;
            case SET_SO_LUOI:
                countSV = 0;
                lcd_gotoxy(11, 0);
                lcd_puts("-");
                if (isButtonNumber() && Number() >= 0 && Number() <= 9) {
                    demgiatri++;
                    GiaTri[indexOfNumber++] = Number();
                    TinhGiaTri();
                    SoLuoi = TinhGiaTri();
                }
                lcd_gotoxy(12, 0);
                printf("%d", SoLuoi);
                if (isButtonMode()) {
                    demgiatri = 0;
                    indexOfNumber = 0;
                    SoLan = 0;
                    statusMachine = SET_DAI;
                }
                if (isButtonCancel()) {
                    lcd_gotoxy(12, 0);
                    lcd_puts("     ");
                    SoLuoi = 0;
                    demgiatri = 0;
                    indexOfNumber = 0;
                    SoLan = 0;
                }
                break;
            case SET_DAI:
                lcd_gotoxy(11, 0);
                lcd_puts(" ");
                lcd_gotoxy(11, 1);
                lcd_puts("-");
                if (isButtonNumber() && Number() >= 0 && Number() <= 9) {
                    demgiatri++;
                    GiaTri[indexOfNumber++] = Number();
                    TinhGiaTri();
                    ChieuDai = TinhGiaTri();
                }
                lcd_gotoxy(12, 1);
                printf("%d", ChieuDai);
                if (isButtonMode()) {
                    demgiatri = 0;
                    indexOfNumber = 0;
                    SoLan = 0;
                    statusMachine = SO_LAN_EP;
                }
                if (isButtonUp()) {
                    __delay_ms(100);
                    if (isButtonUp()) {
                        demgiatri = 0;
                        indexOfNumber = 0;
                        SoLan = 0;
                        lcd_gotoxy(11, 1);
                        lcd_puts(" ");
                        statusMachine = SET_SO_LUOI;
                    }
                }
                if (isButtonCancel()) {
                    lcd_gotoxy(12, 1);
                    lcd_puts("   ");
                    demgiatri = 0;
                    indexOfNumber = 0;
                    SoLan = 0;
                    ChieuDai = 0;
                }
                break;
            case SO_LAN_EP:
                lcd_gotoxy(11, 1);
                lcd_puts(" ");
                lcd_gotoxy(11, 2);
                lcd_puts("-");
                if (isButtonNumber() && Number() >= 0 && Number() <= 9) {
                    demgiatri++;
                    GiaTri[indexOfNumber++] = Number();
                    TinhGiaTri();
                    LanMai = TinhGiaTri();
                }
                lcd_gotoxy(12, 2);
                printf("%d", LanMai);
                if (isButtonMode()) {
                    demgiatri = 0;
                    indexOfNumber = 0;
                    SoLan = 0;
                    statusMachine = DO_EP;
                }
                if (isButtonUp()) {
                    __delay_ms(100);
                    if (isButtonUp()) {
                        demgiatri = 0;
                        indexOfNumber = 0;
                        SoLan = 0;
                        lcd_gotoxy(11, 2);
                        lcd_puts(" ");
                        statusMachine = SET_DAI;
                    }
                }
                if (isButtonCancel()) {
                    lcd_gotoxy(12, 2);
                    lcd_puts("   ");
                    demgiatri = 0;
                    indexOfNumber = 0;
                    SoLan = 0;
                    LanMai = 0;
                }
                break;
            case DO_EP:
                lcd_gotoxy(11, 2);
                lcd_puts(" ");
                lcd_gotoxy(11, 3);
                lcd_puts("-");
                if (isButtonNumber() && Number() >= 0 && Number() <= 9) {
                    demgiatri++;
                    GiaTri[indexOfNumber++] = Number();
                    TinhGiaTri();
                    DoEp = TinhGiaTri();
                }
                lcd_gotoxy(12, 3);
                printf("%d", DoEp);
                if (isButtonMode()) {
                    lcd_putc('\f');
                    demgiatri = 0;
                    indexOfNumber = 0;
                    SoLan = 0;
                    statusMachine = MAI_THO;
                }
                if (isButtonUp()) {
                    __delay_ms(100);
                    if (isButtonUp()) {
                        demgiatri = 0;
                        indexOfNumber = 0;
                        SoLan = 0;
                        lcd_gotoxy(11, 3);
                        lcd_puts(" ");
                        statusMachine = SO_LAN_EP;
                    }
                }
                if (isButtonCancel()) {
                    lcd_gotoxy(12, 3);
                    lcd_puts("   ");
                    demgiatri = 0;
                    indexOfNumber = 0;
                    SoLan = 0;
                    DoEp = 0;
                }
                break;
            case MAI_THO:
                lcd_gotoxy(9, 0);
                lcd_puts("-");
                if (isButtonNumber() && Number() >= 0 && Number() <= 9) {
                    demgiatri++;
                    GiaTri[indexOfNumber++] = Number();
                    TinhGiaTri();
                    MaiTho = TinhGiaTri();
                }
                lcd_gotoxy(10, 0);
                printf("%d", MaiTho);
                lcd_gotoxy(0, 0);
                lcd_puts("EP THO:");
                lcd_gotoxy(12, 0);
                lcd_puts("LAN");
                if (isButtonMode()) {
                    lcd_putc('\f');
                    lcd_gotoxy(0, 1);
                    lcd_puts("Da set xong");
                    Delay(10);
                    lcd_putc('\f');
                    demgiatri = 0;
                    indexOfNumber = 0;
                    SoLan = 0;
                    statusMachine = HANDLE;
                }
                if (isButtonUp()) {
                    lcd_putc('\f');
                    lcd_gotoxy(0, 0);
                    lcd_puts("SO LUOI:");
                    lcd_gotoxy(12, 0);
                    printf("%d", SoLuoi);
                    lcd_gotoxy(0, 1);
                    lcd_puts("CHIEU DAI:");
                    lcd_gotoxy(15, 1);
                    lcd_puts("MM");
                    lcd_gotoxy(12, 1);
                    printf("%d", ChieuDai);
                    lcd_gotoxy(0, 2);
                    lcd_puts("SO LAN MAI:");
                    lcd_gotoxy(12, 2);
                    printf("%d", LanMai);
                    lcd_gotoxy(0, 3);
                    lcd_puts("DO EP:");
                    lcd_gotoxy(15, 3);
                    lcd_puts("UM");
                    lcd_gotoxy(12, 3);
                    printf("%d", DoEp);
                    demgiatri = 0;
                    indexOfNumber = 0;
                    SoLan = 0;
                    statusMachine = DO_EP;
                }
                if (isButtonCancel()) {
                    lcd_gotoxy(12, 0);
                    lcd_puts("   ");
                    demgiatri = 0;
                    indexOfNumber = 0;
                    SoLan = 0;
                    MaiTho = 0;
                }
                break;
            case START:
                lcd_gotoxy(0, 0);
                lcd_puts("Chon MODE mai dao:");
                lcd_gotoxy(0, 1);
                lcd_puts("1.Mode_1");
                lcd_gotoxy(0, 2);
                lcd_puts("2.Mode_2");
                if (ChuyenLuoiPhai()) {
                    lcd_putc('\f');
                    statusMachine = MODE_1;
                }
                if (Cap2kXungLen()) {
                    lcd_putc('\f');
                    statusMachine = MODE_2;
                }
                break;
            case MODE_1:
                RC6 = 0;
                SER_ON = 1;
                RE2 = 1;
                if (RB7 == 1) {
                    RC5 = 1; //RC5
                    __delay_us(2500);
                    RC5 = 0;
                    __delay_us(2500);
                } else {
                    cb = 1;
                    dk1 = 1;
                }
                if (cb == 1) {
                    if (RB6 == 1) {
                        RE1 = 1;
                        __delay_us(1500); // tan so toi da 450
                        RE1 = 0;
                        __delay_us(1500);
                    } else
                        dk2 = 1;
                }
                if (dk1 == 1 && dk2 == 1) {
                    Delay(5);

                    RC4 = 0;
                    for (int i = 0; i < 50 * 8; i++) {
                        MotorEpTruc();
                        if (STOP == 1) {
                            RC6 = 0;
                            while (RB7 == 1) {
                                RC5 = 1;
                                __delay_us(2500); //tan so max 2500, 
                                RC5 = 0;
                                __delay_us(2500);
                            }
                            SER_ON = 0;
                            break;
                        }
                    }
                    
                    DcChinh = 1;
                    lcd_gotoxy(0, 0);
                    lcd_puts("So Lan Mai:");
                    lcd_gotoxy(12, 0);
                    printf("%d", SLMaiTho + 1);
                    //DcChinh = 0 ;
                    if (STOP == 0) {
                        CuaStart(); // Ham cho may chay                                
                    }
                    dk1 = 0;
                    dk2 = 0;
                    cb = 0;
                    SER_ON = 0;
                    lcd_putc('\f');
                    biennho2 = 0;
                    biennho1 = 0;
                    DcChinh = 0;
                    demdao = 0;
                    statusMachine = HANDLE;
                }
                break;
//            case MODE_2:
//                RC6 = 0;
//                RB1 = 1;
//                RE2 = 1;
//                if (RB7 == 1) {
//                    RC5 = 1; //RC5
//                    __delay_us(2500);
//                    RC5 = 0;
//                    __delay_us(2500);
//                } else {
//                    cb = 1;
//                    dk1 = 1;
//                }
//                if (cb == 1) {
//                    if (RB6 == 1) {
//                        RE1 = 1;
//                        __delay_us(1500); // tan so toi da 450
//                        RE1 = 0;
//                        __delay_us(1500);
//                    } else
//                        dk2 = 1;
//                }
//                if (dk1 == 1 && dk2 == 1) {
//                    Delay(5);
//                    DcChinh = 1;
//                    lcd_gotoxy(0, 0);
//                    lcd_puts("So Lan Mai:");
//                    lcd_gotoxy(12, 0);
//                    printf("%d", SLMaiTho + 1);
//                    //DcChinh = 0 ;
//                    if (STOP == 0) {
//                        CuaStart2(); // Ham cho may chay                                
//                    }
//                    dk1 = 0;
//                    dk2 = 0;
//                    cb = 0;
//                    lcd_putc('\f');
//                    biennho2 = 0;
//                    biennho1 = 0;
//                    DcChinh = 0;
//                    statusMachine = HANDLE;
//                }
//                break;
            default:
                break;
        }
    }
}

//------------------------------------------------------------------------------

void system1(void) {
    TRIS_BUTTON = 0x0f;
    PORT_BUTTON = 0xff;
    TRISC = 0x00;
    PORTC = 0x00;
    TRISE1 = 0;
    TRISE2 = 0;
    TRISB = 0b11100001;
    PORTB = 0b11100001;
    RE1 = 0;
    RE2 = 0;
}
//------------------------------------------------------------------------------

void Delay(char time) {
    int i;
    for (i = 0; i <= time; i++)
        __delay_ms(100);
}

/*DOC MA TRAN PHIM*/
//---------------------------------------------------------------------

unsigned char isButtonNumber() {
    unsigned char i;
    for (i = 0; i <= 15; i++)
        if (key_code[i] == 1) {
            numberValue = arrayMapOfNumber[i];
            return 1;
        }
    return 0;
}

//----------------------------------------------------------------
// các nút dc nh?n 

unsigned char Cap2kXungLen() {
    if (key_code[1] == 1 || (key_code[1] >= 10 && key_code[1] % 1 == 0))
        return 1;
    else
        return 0;
}

unsigned char Cap2kXungXuong() {
    if (key_code[5] == 1 || (key_code[5] >= 10 && key_code[5] % 1 == 0))
        return 1;
    else
        return 0;
}

unsigned char ChuyenLuoiPhai() {
    if (key_code[0] == 1 || (key_code[0] >= 10 && key_code[0] % 1 == 0))
        return 1;
    else
        return 0;
}

unsigned char ChuyenLuoiTrai() {
    if (key_code[2] == 1 || (key_code[2] >= 10 && key_code[2] % 1 == 0))
        return 1;
    else
        return 0;
}

unsigned char isButtonUp() {
    if (key_code[3] == 1 || (key_code[3] >= 10 && key_code[3] % 1 == 0))
        return 1;
    else
        return 0;
}

unsigned char MotorON() {
    if (key_code[3] == 1 || (key_code[3] >= 10 && key_code[3] % 1 == 0))
        return 1;
    else
        return 0;
}

unsigned char Vao() {
    if (key_code[8] == 1 || (key_code[8] >= 10 && key_code[8] % 1 == 0))
        return 1;
    else
        return 0;
}

unsigned char Ra() {
    if (key_code[9] == 1 || (key_code[9] >= 10 && key_code[9] % 1 == 0))
        return 1;
    else
        return 0;
}

unsigned char Len() {
    if (key_code[10] == 1 || (key_code[10] >= 10 && key_code[10] % 1 == 0))
        return 1;
    else
        return 0;
}

unsigned char Xuong() {
    if (key_code[11] == 1 || (key_code[11] >= 10 && key_code[11] % 1 == 0))
        return 1;
    else
        return 0;
}

unsigned char isButtonMode() {
    if (key_code[12] == 1)
        return 1;
    else
        return 0;
}

unsigned char ServoOn() {
    if (key_code[13] == 1)
        return 1;
    else
        return 0;
}

unsigned char isButtonCancel() {
    if (key_code[14] == 1)
        return 1;
    else
        return 0;
}

unsigned char ButtonEnter() {
    if (key_code[15] == 1)
        return 1;
    else
        return 0;
}


//-----------------------------------------------------------------------


//xuat nhap

int Number() {
    if (key_code[13] == 1)
        return 0;
    if (key_code[3] == 1)
        return 15;
    if (key_code[0] == 1)
        return 1;
    if (key_code[1] == 1)
        return 2;
    if (key_code[2] == 1)
        return 3;
    if (key_code[4] == 1)
        return 4;
    if (key_code[5] == 1)
        return 5;
    if (key_code[6] == 1)
        return 6;
    if (key_code[7] == 1)
        return 16;
    if (key_code[8] == 1)
        return 7;
    if (key_code[9] == 1)
        return 8;
    if (key_code[10] == 1)
        return 9;
}
// Tinh toan
//------------------------------------------------------------------------------

int TinhGiaTri() {
    int Tong;
    if (demgiatri == 1) {
        Tong = GiaTri[0];
        return Tong;
    } else if (demgiatri == 2) {
        Tong = GiaTri[0]*10 + GiaTri[1];
        return Tong;
    } else if (demgiatri == 3) {
        Tong = GiaTri[0]*100 + GiaTri[1]*10 + GiaTri[2];
        return Tong;
    } else
        demgiatri = 0;
}
//------------------------------------------------------------------------------

void CuaStart() {
    int pulse1 = 600, pulse3 = 300;
    RC6 = 1;
    RC4 = 1;
    RE2 = 1; // chay theo chieu thuan 
    /*KO XAI TRUC Y, MAI LUOI LOAI 1 CHAY THEO TRUC X*/
    for (int i = 0; i < pulse1; i++) {
        motorX();
        if (STOP == 1) {
            RC6 = 0;
            while (RB7 == 1) {
                RC5 = 1;
                __delay_us(2500); //tan so max 2500, 
                RC5 = 0;
                __delay_us(2500);
            }
            SER_ON = 0;
            break;
        }
    }
    
    
    RC4 = 1;// ep dao vao
    for (int i = 0; i < 50 * 8; i++) {
        MotorEpTruc();
        if (STOP == 1) {
            RC6 = 0;
            while (RB7 == 1) {
                RC5 = 1;
                __delay_us(2500); //tan so max 2500, 
                RC5 = 0;
                __delay_us(2500);
            }
            SER_ON = 0;
            break;
        }
    }
    
    while (Luoi < SoLuoi) /*Luu y*/ {
        //CHU TRINH MAI THO 
        for (int j = 0; j < MaiTho; j++) {
            lcd_gotoxy(0, 0);
            lcd_puts("So Lan Mai:");
            lcd_gotoxy(12, 0);
            printf("%d", SLMaiTho + 1);
            ChuTrinhMaiTho();
            SLMaiTho++;
            if (STOP == 1) {
                RC6 = 0;
                while (RB7 == 1) {
                    RC5 = 1;
                    __delay_us(2500); //tan so max 2500, 
                    RC5 = 0;
                    __delay_us(2500);
                }
                SER_ON = 0;
                break;
            }
        }

        if (STOP == 1)
            break;
        lcd_putc('\f');

        /*CHU TRINH MAI TINH*/
        for (SoLan = 0; SoLan < LanMai; SoLan++)// Tien vao mai du so lan thi ngung 
        {
            lcd_gotoxy(0, 0);
            lcd_puts("So Lan:");
            lcd_gotoxy(12, 0);
            printf("%d", SoLan + 1);
            lcd_gotoxy(0, 1);
            lcd_puts("So Luoi:");
            lcd_gotoxy(12, 1);
            printf("%d", Luoi + 1);

            //EP truc vao   
            RC4 = 1;
            biennho2 = biennho2 + DoEp;
            for (int k = 0; k < DoEp * 8; k++)// ep truc, sua biennho2 thanh doep*16
            {
                MotorEpTruc();
                if (STOP == 1)
                    break;
            }

            RC6 = 1;
            maidao();
            Delay(1);
            RC6 = 0;
            maidao();

            if (STOP == 1) {
                RC6 = 0;
                while (RB7 == 1) {
                    RC5 = 1;
                    __delay_us(2500); //tan so max 2500, 
                    RC5 = 0;
                    __delay_us(2500);
                }
                SER_ON = 0;
                break;
            }
        }
        if (STOP == 1)
            break;
        //rut dao xuong vi tri goc
        RE2 = 0;
        //rut dao trc roi ha sau       
        RC4 = 0;
        for (int k1 = 0; k1 < (biennho2 + 50) * 8; k1++)// cho truc ep rut ve
        {
            MotorEpTruc();
            if (STOP == 1)
                break;
        }

        RC6 = 0;
        for (int i = 0; i < pulse1; i++) {
            motorX();
            if (STOP == 1) {
                RC6 = 0;
                while (RB7 == 1) {
                    RC5 = 1;
                    __delay_us(2500); //tan so max 2500, 
                    RC5 = 0;
                    __delay_us(2500);
                }
                SER_ON = 0;
                break;
            }
        }
        if (STOP == 1)
            break;

        for (int i1 = 0; i1 < pulse3; i1++) {
            motorY();
            if (STOP == 1)
                break;
        }
        //chuyen luoi ti le 1:50 hop so
        //Lay boi so chung nho nhat - dem chia cho so luoi dao
        chuyenluoi();
        if (STOP == 1) {
            RC6 = 0;
            while (RB7 == 1) {
                RC5 = 1;
                __delay_us(2500); //tan so max 2500, 
                RC5 = 0;
                __delay_us(2500);
            }
            SER_ON = 0;
            break;
        }
        Luoi++;
        
        RC6 = 1;
        RC4 = 1;

        SLMaiTho = 0;
        biennho2 = 0;
        RE2 = 1;
        //cho dao ve vi tri mai
        for (int i2 = 0; i2 < pulse3; i2++) {
            motorY();
            if (STOP == 1)
                break;
        }
        if (demdao < (SoLuoi - 1)) {
            for (int i = 0; i < pulse1; i++) {
                motorX();
                if (STOP == 1) {
                    RC6 = 0;
                    while (RB7 == 1) {
                        RC5 = 1;
                        __delay_us(2500); //tan so max 2500, 
                        RC5 = 0;
                        __delay_us(2500);
                    }
                    SER_ON = 0;
                    break;
                }
            }
            demdao++;
        }
        RC4 = 1;// ep dao vao
        for (int i = 0; i < 50 * 8; i++) {
            MotorEpTruc();
            if (STOP == 1) {
                RC6 = 0;
                while (RB7 == 1) {
                    RC5 = 1;
                    __delay_us(2500); //tan so max 2500, 
                    RC5 = 0;
                    __delay_us(2500);
                }
                SER_ON = 0;
                break;
            }
        }
        if (STOP == 1)
            break;

        lcd_putc('\f');
    }

    RC6 = 0;
    while (RB7 == 1) {
        RC5 = 1;
        __delay_us(2500); //tan so max 2500, 
        RC5 = 0;
        __delay_us(2500);
    }
}

// Thu tu, chay vao, ep dao, len xuong 
// bat dau cho dao chay vao,200 xung 1 vong = 10mm   

void motorX() {// RC6 chinh chieu, xung 2000 2/3 quang duong, RC6 = 0 di vao, = 1 di ra
    RC5 = 1;
    __delay_us(3000); //tan so max 2500, 
    RC5 = 0;
    __delay_us(3000);
}

//200 xung 1 vong = 5mm

void motorY() { // chieu RE2 = 0 la di len, = 1 di xuong
    RE1 = 1;
    __delay_us(1500); // tan so toi da 450
    RE1 = 0;
    __delay_us(1500);
}


//454 xung 1 vong = 5mm//vi buoc x16

void MotorEpTruc() {//chieu RC4  = 0 , trai -> phai, = 1 phai -> trai, xung 2000
    RC3 = 1;
    __delay_us(1000); //tan so toi da 1300
    RC3 = 0;
    __delay_us(1000);
}
//------------------------------------------------------------------------------

/*CHU TRINH MAI THO*/
void ChuTrinhMaiTho() {
    int tong2 = 0;
    int pulse2 = 5; //1 xung = 0.01mm, mai tho 5 xung

    RC4 = 1;
    for (int i = 0; i < pulse2 * 8; i++) {
        MotorEpTruc();
        if (STOP == 1) {
            RC6 = 0;
            while (RB7 == 1) {
                RC5 = 1;
                __delay_us(2500); //tan so max 2500, 
                RC5 = 0;
                __delay_us(2500);
            }
            SER_ON = 0;
            break;
        }
    }

    RC6 = 1;
    maidao();
    Delay(1);
    RC6 = 0;
    maidao();

}

/*CHU TRINH MAI DAO*/
void maidao() {
    int domaix = 0, domaiy = 0;
    domaix = ChieuDai * 20 - 400;

    for (int i = 0; i < domaix; i++) {
        motorX();
        if (STOP == 1) {
            RC6 = 0;
            while (RB7 == 1) {
                RC5 = 1;
                __delay_us(2500); //tan so max 2500, 
                RC5 = 0;
                __delay_us(2500);
            }
            SER_ON = 0;
            break;
        }
    }
}

/*CHU TRINH CHUYEN LUOI DAO*/
void chuyenluoi() {
    int pulse = 24000, tong = 0, count = 0;
    pulse = 24000 / SoLuoi;
    for (unsigned int i = 0; i < pulse; i++) {
        RC1 = 1;
        __delay_us(40);
        RC1 = 0;
        __delay_us(40);
    }
}

//------------------------------------------------------------------------------

void CuaStart2() {
    int pulse1 = 1, pulse3 = 300;
    RC6 = 1;
    RC4 = 1;
    RE2 = 0; // chay theo chieu thuan 
    //    /* MAI LUOI LOAI 2 CHAY THEO 2 TRUC X,Y*/

    for (int i9 = 0; i9 < 5 * 8; i9++) {
        MotorEpTruc();
        if (STOP == 1) {
            RC6 = 0;
            while (RB7 == 1) {
                RC5 = 1;
                __delay_us(2500); //tan so max 2500, 
                RC5 = 0;
                __delay_us(2500);
            }
            SER_ON = 0;
            break;
        }
    }
    while (Luoi < SoLuoi) /*Luu y*/ {
        //CHU TRINH MAI THO 
        RE2 = 0;
        for (int j = 0; j < MaiTho; j++) {
            lcd_gotoxy(0, 0);
            lcd_puts("So Lan Mai:");
            lcd_gotoxy(12, 0);
            printf("%d", SLMaiTho + 1);
            ChuTrinhMaiTho2();
            SLMaiTho++;
            if (STOP == 1) {
                RC6 = 0;
                while (RB7 == 1) {
                    RC5 = 1;
                    __delay_us(2500); //tan so max 2500, 
                    RC5 = 0;
                    __delay_us(2500);
                }
                SER_ON = 0;
                break;
            }
        }
        if (STOP == 1)
            break;
        lcd_gotoxy(0, 0);
        lcd_puts("Ket thuc mai tho");
        Delay(10);
        lcd_putc('\f');

        /*CHU TRINH MAI TINH*/
        for (SoLan = 0; SoLan < LanMai; SoLan++)// Tien vao mai du so lan thi ngung 
        {
            lcd_gotoxy(0, 0);
            lcd_puts("So Lan:");
            lcd_gotoxy(12, 0);
            printf("%d", SoLan + 1);
            lcd_gotoxy(0, 1);
            lcd_puts("So Luoi:");
            lcd_gotoxy(12, 1);
            printf("%d", Luoi + 1);
            //EP truc vao     
            biennho2 = biennho2 + DoEp;
            RC6 = 1;
            RE2 = 0;
            maidao2();
            RC6 = 0;
            RE2 = 1;
            Delay(1);
            hamphu2();
            RC4 = 1;

            while (RB7 == 1) {
                RC5 = 1;
                __delay_us(2500); //tan so max 2500, 
                RC5 = 0;
                __delay_us(2500);
            }
            for (int k = 0; k < DoEp * 8; k++)// ep truc, sua biennho2 thanh doep*16
            {
                MotorEpTruc();
                if (STOP == 1)
                    break;
            }
            RC6 = 1;
            Delay(5);
            if (SoLan < (LanMai - 1)) {
                for (int i = 0; i < pulse1; i++) {
                    motorX();
                    if (STOP == 1)
                        break;
                }
                if (STOP == 1)
                    break;
            }
        }
        if (STOP == 1)
            break;
        //rut dao xuong vi tri goc
        RE2 = 0;
        //rut dao trc roi ha sau       
        RC4 = 0;
        for (int k1 = 0; k1 < biennho2 * 8; k1++)// cho truc ep rut ve
        {
            MotorEpTruc();
            if (STOP == 1)
                break;
        }
        for (int i1 = 0; i1 < pulse3; i1++) {
            motorY();
            if (STOP == 1)
                break;
        }
        RC6 = 1;
        //chuyen luoi ti le 1:50 hop so
        //Lay boi so chung nho nhat - dem chia cho so luoi dao
        chuyenluoi();
        if (STOP == 1) {
            RC6 = 0;
            while (RB7 == 1) {
                RC5 = 1;
                __delay_us(2500); //tan so max 2500, 
                RC5 = 0;
                __delay_us(2500);
            }
            SER_ON = 0;
            break;
        }
        Luoi++;
        RC4 = 1;
        for (int i9 = 0; i9 < 5 * 8; i9++) {
            MotorEpTruc();
            if (STOP == 1)
                break;
        }
        SLMaiTho = 0;
        biennho2 = 0;
        RE2 = 1;
        //cho dao ve vi tri mai
        for (int i2 = 0; i2 < pulse3; i2++) {
            motorY();
            if (STOP == 1)
                break;
        }
        if (Luoi == (SoLuoi - 1)) {
            for (int i = 0; i < pulse1; i++) {
                motorX();
                if (STOP == 1)
                    break;
            }
            if (STOP == 1)
                break;
        }

    }
    RC6 = 0;
}

/*CHU TRINH MAI THO 2*/
void ChuTrinhMaiTho2() {
    int tong2 = 0;
    int pulse1 = 0;
    int pulse2 = 5; //1 xung = 0.01mm, mai tho 5 xung
    biennho1 = biennho1 + pulse2;
    maidao2();
    RC6 = 0;
    RE2 = 1;
    Delay(1);
    hamphu2();
    RC6 = 1;
    RE2 = 0;
    while (RB7 == 1) {
        RC5 = 1;
        __delay_us(2500); //tan so max 2500, 
        RC5 = 0;
        __delay_us(2500);
    }
    RC4 = 1;
    for (int i = 0; i < pulse2 * 8; i++)//thay biennho1 = pulse2*16
    {
        MotorEpTruc();
        if (STOP == 1)
            break;
    }
    Delay(5);
}

/*CHU TRINH MAI DAO 2*/
void maidao2() {
    int domaix = 0, domaiy = 0;
    domaix = ChieuDai * 20 + 200;
    domaiy = ChieuDai * 20;

    for (int i = 0; i < domaix; i++) {
        motorX();
        if (STOP == 1) {
            RC6 = 0;
            while (RB7 == 1) {
                RC5 = 1;
                __delay_us(2500); //tan so max 2500, 
                RC5 = 0;
                __delay_us(2500);
            }
            SER_ON = 0;
            break;
        }
    }

    for (int i = 0; i < domaiy; i++) {
        motorY();
        if (STOP == 1) {
            RC6 = 0;
            while (RB7 == 1) {
                RC5 = 1;
                __delay_us(2500); //tan so max 2500, 
                RC5 = 0;
                __delay_us(2500);
            }
            SER_ON = 0;
            break;
        }
    }
}

void hamphu2() {
    int domaix = 0, domaiy = 0;
    domaix = ChieuDai * 20 + 200;
    domaiy = ChieuDai * 20;

    for (int i = 0; i < domaiy; i++) {
        motorY();
        if (STOP == 1) {
            RC6 = 0;
            while (RB7 == 1) {
                RC5 = 1;
                __delay_us(2500); //tan so max 2500, 
                RC5 = 0;
                __delay_us(2500);
            }
            SER_ON = 0;
            break;
        }
    }

    for (int i = 0; i < domaix; i++) {
        motorX();
        if (STOP == 1) {
            RC6 = 0;
            while (RB7 == 1) {
                RC5 = 1;
                __delay_us(2500); //tan so max 2500, 
                RC5 = 0;
                __delay_us(2500);
            }
            SER_ON = 0;
            break;
        }
    }


}