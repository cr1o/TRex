#include "lcd.h"
//----------------------------------------------
void delay_us(uint32_t n) //Задержка в ~1мкс (При 8MGz 1.25) 1такт 125нс *10 = 1.25мкс
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
    LCD_Command(0x30); //8бит
    delay_us(1000);
    LCD_Command(0x30);
    delay_us(1000);
    LCD_Command(0x38); //Режим  0011(8бит) 1(4линии)0(5х8)00 
		delay_us(1000);
    LCD_Command(0x38); //Режим  0011(8бит) 1(4линии)0(5х8)00 
    delay_us(1000);
    LCD_Command(0x0F); //Режим мигания  с курсором
    delay_us(1000);
    LCD_Command(0x01); //Очистка дисплея  
    delay_us(2000);
    LCD_Command(0x06); //Пишем влево  
    delay_us(2000);
}    
//----------------------------------------------
void LCD_Clear(void) 
{   
    LCD_Command(0x01);
    delay_us(2000);
}    
//----------------------------------------------
void LCD_SetPos(uint8_t x, uint8_t y) //Установка позиции курсора y-строка
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
void LCD_SetTCur(uint8_t t ) //Установка типа курсора
{   
    switch(t)
    {
        case 0:
            LCD_Command(0x0C); //Отсутствие курсора
            delay_us(2000);
            break;
        case 1:
            LCD_Command(0x0D); //Немигающий курсор
            delay_us(2000);
            break;
        case 2:
            LCD_Command(0x0E); //Мигающий черный квадрат
            delay_us(2000);
            break;
        case 3:
            LCD_Command(0x0F); //Мигающий черный квадрат+подчеркивание
            delay_us(2000);
            break;
    }    
}    
//----------------------------------------------
void LCD_SetLight(uint8_t lt) //Установка яркости (0-100%)
{   
    TIM1->CCR1 = lt; 
}    
//----------------------------------------------
char ANSI1251_CO_FF [] =
{
   0x41,       //код 0xC0, символ 'А'
   0xA0,       //код 0xC1, символ 'Б'
   0x42,       //код 0xC2, символ 'В'
   0xA1,       //код 0xC3, символ 'Г'
   0xE0,       //код 0xC4, символ 'Д'
   0x45,       //код 0xC5, символ 'Е'
   0xA3,       //код 0xC6, символ 'Ж'
   0xA4,       //код 0xC7, символ 'З'
   0xA5,       //код 0xC8, символ 'И'
   0xA6,       //код 0xC9, символ 'Й'
   0x4B,       //код 0xCA, символ 'К'
   0xA7,       //код 0xCB, символ 'Л'
   0x4D,       //код 0xCC, символ 'М'
   0x48,       //код 0xCD, символ 'Н'
   0x4F,       //код 0xCE, символ 'О'
   0xA8,       //код 0xCF, символ 'П'
   0x50,       //код 0xD0, символ 'Р'
   0x43,       //код 0xD1, символ 'С'
   0x54,       //код 0xD2, символ 'Т'
   0xA9,       //код 0xD3, символ 'У'
   0xAA,       //код 0xD4, символ 'Ф'
   0x58,       //код 0xD5, символ 'Х'
   0xE1,       //код 0xD6, символ 'Ц'
   0xAB,       //код 0xD7, символ 'Ч'
   0xAC,       //код 0xD8, символ 'Ш'
   0xE2,       //код 0xD9, символ 'Щ'
   0xAD,       //код 0xDA, символ 'Ъ'
   0xAE,       //код 0xDB, символ 'Ы'
   0x62,       //код 0xDC, символ 'Ь'
   0xAF,       //код 0xDD, символ 'Э'
   0xB0,       //код 0xDE, символ 'Ю'
   0xB1,       //код 0xDF, символ 'Я'
   0x61,       //код 0xE0, символ 'а'
   0xB2,       //код 0xE1, символ 'б'
   0xB3,       //код 0xE2, символ 'в'
   0xB4,       //код 0xE3, символ 'г'
   0xE3,       //код 0xE4, символ 'д'
   0x65,       //код 0xE5, символ 'е'
   0xB6,       //код 0xE6, символ 'ж'
   0xB7,       //код 0xE7, символ 'з'
   0xB8,       //код 0xE8, символ 'и'
   0xB9,       //код 0xE9, символ 'й'
   0xBA,       //код 0xEA, символ 'к'
   0xBB,       //код 0xEB, символ 'л'
   0xBC,       //код 0xEC, символ 'м'
   0xBD,       //код 0xED, символ 'н'
   0x6F,       //код 0xEE, символ 'о'
   0xBE,       //код 0xEF, символ 'п'
   0x70,       //код 0xF0, символ 'р'
   0x63,       //код 0xF1, символ 'с'
   0xBF,       //код 0xF2, символ 'т'
   0x79,       //код 0xF3, символ 'у'
   0xE4,       //код 0xF4, символ 'ф'
   0x78,       //код 0xF5, символ 'х'
   0xE5,       //код 0xF6, символ 'ц'
   0xC0,       //код 0xF7, символ 'ч'
   0xC1,       //код 0xF8, символ 'ш'
   0xE6,       //код 0xF9, символ 'щ'
   0xC2,       //код 0xFA, символ 'ъ'
   0xC3,       //код 0xFB, символ 'ы'
   0xC4,       //код 0xFC, символ 'ь'
   0xC5,       //код 0xFD, символ 'э'
   0xC6,       //код 0xFE, символ 'ю'
   0xC7        //код 0xFF, символ 'я'
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
    LCD_SetPos(0,0);  //Первая строка
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
