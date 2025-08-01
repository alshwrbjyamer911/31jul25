/*
 * SSD1309.h
 *
 *  Created on: Jul 13, 2025
 *      Author: rk
 */

#ifndef INC_SSD1309_H_
#define INC_SSD1309_H_

void SSD1309_WriteCommand(uint8_t cmd);
void SSD1309_WriteData(uint8_t * data, size_t length);
void InitDisplay(void);
 void SSD1309_Reset(void);
 void SSD1309_UpdateScreen(void);
 void SSD1309_Fill(uint8_t color);
 void SSD1309_DrawPixel(uint8_t x, uint8_t y, uint8_t color);
 void SSD1309_DrawRectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
 void tempwrite();
 void DisplayChar(uint8_t u8Colmn, uint8_t u8page,unsigned char * data);
 void ClearScreen();
 void WriteText(uint8_t u8Colmn, uint8_t u8page,unsigned char * data);

#define CS_PIN             GPIO_PIN_15
#define CS_PORT            GPIOC

#define DATA_CMD_PIN       GPIO_PIN_5
#define DATA_CMD_PORT      GPIOC

#define RES_PIN            GPIO_PIN_4
#define RES_PORT           GPIOC



#endif /* INC_SSD1309_H_ */
