#ifndef TLE9201_H
#define TLE9201_H

#include "stm32f4xx_hal.h"  // Change this to match your STM32 family

// SPI handle for SPI3
extern SPI_HandleTypeDef hspi3;

// Pin mappings (define according to CubeMX settings)
#define TLE9201_CSN_GPIO_Port GPIOB
#define TLE9201_CSN_Pin       GPIO_PIN_7

#define TLE9201_DIS_GPIO_Port GPIOC
#define TLE9201_DIS_Pin       GPIO_PIN_11

#define TLE9201_DIR_GPIO_Port GPIOB
#define TLE9201_DIR_Pin       GPIO_PIN_8

#define TLE9201_PWM_TIM       htim4      // Timer used for PWM generation
#define TLE9201_PWM_CHANNEL   TIM_CHANNEL_1

// SPI Commands
#define TLE9201_CMD_RD_DIA       0x00
#define TLE9201_CMD_RES_DIA      0x80
#define TLE9201_CMD_RD_REV       0x20

// Function Prototypes
void TLE9201_Init(void);
void TLE9201_EnableOutput(void);
void TLE9201_DisableOutput(void);
void TLE9201_SetDirection(uint8_t dir); // 0: Reverse, 1: Forward
void TLE9201_SetSpeed(uint8_t duty);    // 0–255
uint8_t TLE9201_ReadDiagnosis(void);
uint8_t TLE9201_ReadRevision(void);
void TLE9201_ResetDiagnosis(void);

#endif
