#ifndef AS32
#define AS32

#include "main.h"
#include <string.h>
#include <stdio.h>

// UART used for LoRa communication
extern UART_HandleTypeDef huart1;

// 16-byte encryption key command (starts with 0xC6)
const uint8_t enc_key[17] = {
    0xC6, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F, 0x70,
    0x81, 0x92, 0xA3, 0xB4, 0xC5, 0xD6, 0xE7, 0xF8, 0x09
};

// === Initialization & Setup ===
uint8_t lora_init(void);                      // Put LoRa into config mode
void    lora_set_mode(uint8_t md0, uint8_t md1); // Set mode pins

// === Configuration ===
void    lora_send_config(uint8_t addh, uint8_t addl, uint8_t speed, uint8_t chan, uint8_t option);
void    lora_send_enc_key(void);

// === Data ===
uint8_t lora_send_data(uint8_t *data, uint8_t len);   // Send user data
uint8_t lora_receive_data(uint8_t *buffer, uint8_t max_len); // Receive data

// === Utility ===
uint8_t lora_wait_ok(uint16_t timeout_ms);    // Wait for ASCII "OK"
uint8_t lora_read_params(uint8_t *response);  // Read back config with 0xC1 0xC1 0xC1
uint8_t lora_check_error(void);               // Placeholder for AUX pin or status check

#endif
