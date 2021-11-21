#include "lcd.h"
//----------------------------------------------
void delay_us(uint32_t n) //�������� � ~1��� (��� 8MGz 1.25) 1���� 125�� *10 = 1.25���
{
    uint32_t i;
    for (i = 0; i < n*10; i++)
    {
    }
}    
//----------------------------------------------
void LCD_Command(uint8_t dt)
{   
    RS_reset();
    if ((dt & 0x80) != 0) { D7_set();} else { D7_reset();}
    if ((dt & 0x40) != 0) { D6_set();} else { D6_reset();}
    if ((dt & 0x20) != 0) { D5_set();} else { D5_reset();}
    if ((dt & 0x10) != 0) { D4_set();} else { D4_reset();}
    if ((dt & 0x08) != 0) { D3_set();} else { D3_reset();}
    if ((dt & 0x04) != 0) { D2_set();} else { D2_reset();}
    if ((dt & 0x02) != 0) { D1_set();} else { D1_reset();}
    if ((dt & 0x01) != 0) { D0_set();} else { D0_reset();}
    E_set();
    delay_us(100);
    E_reset();
}    
//----------------------------------------------
void LCD_WriteData(uint8_t dt)
{   
    RS_set();
    if ((dt & 0x80) != 0) { D7_set();} else { D7_reset();}
    if ((dt & 0x40) != 0) { D6_set();} else { D6_reset();}
    if ((dt & 0x20) != 0) { D5_set();} else { D5_reset();}
    if ((dt & 0x10) != 0) { D4_set();} else { D4_reset();}
    if ((dt & 0x08) != 0) { D3_set();} else { D3_reset();}
    if ((dt & 0x04) != 0) { D2_set();} else { D2_reset();}
    if ((dt & 0x02) != 0) { D1_set();} else { D1_reset();}
    if ((dt & 0x01) != 0) { D0_set();} else { D0_reset();}
    E_set();
    delay_us(100);
    E_reset();
}    
//----------------------------------------------
void LCD_Init(void)
{        
    delay_us(40000);
    LCD_Command(0x30); //8bit
    delay_us(1000);
    LCD_Command(0x30); //8���
    delay_us(1000);
    LCD_Command(0x30);
    delay_us(1000);
    LCD_Command(0x38); //�����  0011(8���) 1(4�����)0(5�8)00 
		delay_us(1000);
    LCD_Command(0x38); //�����  0011(8���) 1(4�����)0(5�8)00 
    delay_us(1000);
    LCD_Command(0x0F); //����� �������  � ��������
    delay_us(1000);
    LCD_Command(0x01); //������� �������  
    delay_us(2000);
    LCD_Command(0x06); //����� �����  
    delay_us(2000);
}    
//----------------------------------------------
void LCD_Clear(void) 
{   
    LCD_Command(0x01);
    delay_us(2000);
}    
//----------------------------------------------
void LCD_SetPos(uint8_t x, uint8_t y) //��������� ������� ������� y-������
{   
    switch(y)
    {    
        case 0:
            LCD_Command(x|0x80);
            delay_us(50); //min 39us
            break;
        case 1:
            LCD_Command((0x40+ x) |0x80);
            delay_us(50); //min 39us
            break;
        case 2:
            LCD_Command((0x14+ x)|0x80);
            delay_us(50); //min 39us
            break;
        case 3:
            LCD_Command((0x54+ x)|0x80);
            delay_us(50); //min 39us
            break;        
    }
}    
//----------------------------------------------
void LCD_SendChar(char ch)
{   
    LCD_WriteData((uint8_t) ch);
    delay_us(100); 
}    
//----------------------------------------------
void LCD_Print(char* str)
{   
    uint8_t i = 0;
    while(str[i]!=0)
    {
        LCD_WriteData(str[i]);
        delay_us(100);
        i++;
    }
}    
//----------------------------------------------
void LCD_SetTCur(uint8_t t ) //��������� ���� �������
{   
    switch(t)
    {
        case 0:
            LCD_Command(0x0C); //���������� �������
            delay_us(2000);
            break;
        case 1:
            LCD_Command(0x0D); //���������� ������
            delay_us(2000);
            break;
        case 2:
            LCD_Command(0x0E); //�������� ������ �������
            delay_us(2000);
            break;
        case 3:
            LCD_Command(0x0F); //�������� ������ �������+�������������
            delay_us(2000);
            break;
    }    
}    
//----------------------------------------------
void LCD_SetLight(uint8_t lt) //��������� ������� (0-100%)
{   
    TIM1->CCR1 = lt; 
}    
//----------------------------------------------
char ANSI1251_CO_FF [] =
{
   0x41,       //��� 0xC0, ������ '�'
   0xA0,       //��� 0xC1, ������ '�'
   0x42,       //��� 0xC2, ������ '�'
   0xA1,       //��� 0xC3, ������ '�'
   0xE0,       //��� 0xC4, ������ '�'
   0x45,       //��� 0xC5, ������ '�'
   0xA3,       //��� 0xC6, ������ '�'
   0xA4,       //��� 0xC7, ������ '�'
   0xA5,       //��� 0xC8, ������ '�'
   0xA6,       //��� 0xC9, ������ '�'
   0x4B,       //��� 0xCA, ������ '�'
   0xA7,       //��� 0xCB, ������ '�'
   0x4D,       //��� 0xCC, ������ '�'
   0x48,       //��� 0xCD, ������ '�'
   0x4F,       //��� 0xCE, ������ '�'
   0xA8,       //��� 0xCF, ������ '�'
   0x50,       //��� 0xD0, ������ '�'
   0x43,       //��� 0xD1, ������ '�'
   0x54,       //��� 0xD2, ������ '�'
   0xA9,       //��� 0xD3, ������ '�'
   0xAA,       //��� 0xD4, ������ '�'
   0x58,       //��� 0xD5, ������ '�'
   0xE1,       //��� 0xD6, ������ '�'
   0xAB,       //��� 0xD7, ������ '�'
   0xAC,       //��� 0xD8, ������ '�'
   0xE2,       //��� 0xD9, ������ '�'
   0xAD,       //��� 0xDA, ������ '�'
   0xAE,       //��� 0xDB, ������ '�'
   0x62,       //��� 0xDC, ������ '�'
   0xAF,       //��� 0xDD, ������ '�'
   0xB0,       //��� 0xDE, ������ '�'
   0xB1,       //��� 0xDF, ������ '�'
   0x61,       //��� 0xE0, ������ '�'
   0xB2,       //��� 0xE1, ������ '�'
   0xB3,       //��� 0xE2, ������ '�'
   0xB4,       //��� 0xE3, ������ '�'
   0xE3,       //��� 0xE4, ������ '�'
   0x65,       //��� 0xE5, ������ '�'
   0xB6,       //��� 0xE6, ������ '�'
   0xB7,       //��� 0xE7, ������ '�'
   0xB8,       //��� 0xE8, ������ '�'
   0xB9,       //��� 0xE9, ������ '�'
   0xBA,       //��� 0xEA, ������ '�'
   0xBB,       //��� 0xEB, ������ '�'
   0xBC,       //��� 0xEC, ������ '�'
   0xBD,       //��� 0xED, ������ '�'
   0x6F,       //��� 0xEE, ������ '�'
   0xBE,       //��� 0xEF, ������ '�'
   0x70,       //��� 0xF0, ������ '�'
   0x63,       //��� 0xF1, ������ '�'
   0xBF,       //��� 0xF2, ������ '�'
   0x79,       //��� 0xF3, ������ '�'
   0xE4,       //��� 0xF4, ������ '�'
   0x78,       //��� 0xF5, ������ '�'
   0xE5,       //��� 0xF6, ������ '�'
   0xC0,       //��� 0xF7, ������ '�'
   0xC1,       //��� 0xF8, ������ '�'
   0xE6,       //��� 0xF9, ������ '�'
   0xC2,       //��� 0xFA, ������ '�'
   0xC3,       //��� 0xFB, ������ '�'
   0xC4,       //��� 0xFC, ������ '�'
   0xC5,       //��� 0xFD, ������ '�'
   0xC6,       //��� 0xFE, ������ '�'
   0xC7        //��� 0xFF, ������ '�'
};
//----------------------------------------------

void LCD_PrintASCII(uint8_t* str)
{
    uint8_t i = 0;
    while(str[i]!=0)
    {
        if ( ((str[i]) == (0xA8)) || ( ( str[i]) == (0xB8))) 
        {
            if ((str[i]) == (0xA8))
            {
                LCD_WriteData(0xA2);
                delay_us(100);
            }
            if ((str[i]) == (0xB8))
            {
                LCD_WriteData(0xB5);
                delay_us(100);
            }                
        }
        else
        {
            if ((str[i]) < 0xC0)
            {
                LCD_WriteData(str[i]);
                delay_us(100);
            }
            else
            {
                LCD_WriteData(ANSI1251_CO_FF[(unsigned char)(str[i])-0xC0]);
                delay_us(100);            
            }
        }
        i++;
    }
}
    
//----------------------------------------------
void LCD_Print80(uint8_t* str)
{
    LCD_SetPos(0,0);  //������ ������
    uint8_t line[21];
    for (int i = 0; i < 20; i++)
    {
        line[i] = str[i];
    }
    line[20] = 0;
    LCD_PrintASCII(line);
    
    LCD_SetPos(0,1);  //
    for (int i = 0; i < 20; i++)
    {
        line[i] = str[i+20];
    }
    line[20] = 0;
    LCD_PrintASCII(line);
    
    LCD_SetPos(0,2);
    for (int i = 0; i < 20; i++)
    {
        line[i] = str[i+40];
    }
    line[20] = 0;
    LCD_PrintASCII(line);
    
    LCD_SetPos(0,3);
    for (int i = 0; i < 20; i++)
    {
        line[i] = str[i+60];
    }
    line[20] = 0;
    LCD_PrintASCII(line);
}
//----------------------------------------------
