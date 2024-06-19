#ifndef __USER_LCD_H
#define __USER_LCD_H

#include "main.h"

extern TIM_HandleTypeDef htim5;

#define Rotation 2

#if  (Rotation == 0) || (Rotation == 1)
#define LCD_W 128
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 128
#endif

#define WHITE         	 0xFFFF
#define BLACK         	 0x0000
#define BLUE           	 0x001F
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40
#define BRRED 			 0XFC07
#define GRAY  			 0X8430
#define DARKBLUE      	 0X01CF
#define LIGHTBLUE      	 0X7D7C
#define GRAYBLUE       	 0X5458
#define LIGHTGREEN     	 0X841F
#define LGRAY 			 0XC618
#define LGRAYBLUE        0XA651
#define LBBLUE           0X2B12

#define LCD_RES_Clr()  HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_RESET)//RES
#define LCD_RES_Set()  HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_SET)

#define LCD_DC_Clr()   HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET)//DC
#define LCD_DC_Set()   HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET)
 		     
#define LCD_CS_Clr()   HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET)//CS
#define LCD_CS_Set()   HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET)

#define LCD_BLK_Clr()  LCD_Set_PWM_Brightness(0)//BLK
#define LCD_BLK_Set()  LCD_Set_PWM_Brightness(100)

void LCD_Set_PWM_Brightness(uint8_t brightness);
void LCD_Write_Data_8Bit(uint8_t data);
void LCD_Write_Data_16Bit(uint16_t data);
void LCD_Write_Reg(uint8_t dat);
void LCD_Set_Address(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end);
void LCD_Init(void);

void LCD_Fill(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end,uint16_t color);
void LCD_Draw_Point(uint16_t x,uint16_t y,uint16_t color);
void LCD_Draw_Line(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end,uint16_t color);
void LCD_Draw_Rectangle(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end,uint16_t color);
void LCD_Draw_Circle(uint16_t x,uint16_t y,uint8_t r,uint16_t color);

void LCD_Show_Char(uint16_t x,uint16_t y,uint8_t num,uint16_t font_color,uint16_t background_color,uint8_t font_size,uint8_t mode);
void LCD_Show_String(uint16_t x,uint16_t y,const uint8_t *p,uint16_t font_color,uint16_t background_color,uint8_t font_size,uint8_t mode);
uint32_t mypow(uint8_t m,uint8_t n);
void LCD_Show_Int_Num(uint16_t x,uint16_t y,uint16_t num,uint8_t length,uint16_t font_color,uint16_t background_color,uint8_t font_size);
void LCD_Show_Float_Num(uint16_t x,uint16_t y,float num,uint8_t length,uint16_t font_color,uint16_t background_color,uint8_t font_size);


#endif