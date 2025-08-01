#ifndef SA818S_H
#define SA818S_H

#include "stm32f4xx_hal.h" // Adjust for your STM32 series
#include <string.h>
#include <stdio.h>

typedef struct {
    uint8_t bandwidth;      // 0: 12.5kHz, 1: 25kHz
    float tx_freq;         // Transmit frequency in MHz (134.000 to 480.000)
    float rx_freq;         // Receive frequency in MHz (134.000 to 480.000)
    uint16_t tx_ctcss;    // Transmit CTCSS in Hz (0 to 255)
    uint8_t squelch;       // Squelch level (0 to 8)
    uint16_t rx_ctcss;    // Receive CTCSS in Hz (0 to 255)
} SA818S_GroupConfig_t;
// UART Handle (adjust as per your configuration)
extern UART_HandleTypeDef huart2; // Example UART handle
extern SA818S_GroupConfig_t sa818s_config;
// SA818S Driver Functions
HAL_StatusTypeDef SA818S_Init(void);
HAL_StatusTypeDef SA818S_Handshake(void);
HAL_StatusTypeDef SA818S_SetGroup(uint8_t bandwidth, float tx_freq, float rx_freq, uint16_t tx_ctcss, uint8_t squelch, uint16_t rx_ctcss);
HAL_StatusTypeDef SA818S_SetVolume(uint8_t volume);
HAL_StatusTypeDef SA818S_SetFilter(uint8_t pre_de_emph, uint8_t highpass, uint8_t lowpass);
HAL_StatusTypeDef SA818S_SetTailTone(uint8_t enable);
HAL_StatusTypeDef SA818S_ReadGroup(uint8_t *bandwidth, float *tx_freq, float *rx_freq, 
                                   uint16_t *tx_ctcss, uint8_t *squelch, uint16_t *rx_ctcss);
HAL_StatusTypeDef SA818S_ReadRSSI(uint16_t *rssi);
HAL_StatusTypeDef SA818S_ReadVersion(char *version);
// void SA818S_SetGroup_values(void);
void SA818S_ApplyConfig(void);

#endif
