#ifndef AS32
#define AS32

#include "main.h"
#include <string.h>
#include <stdio.h>

// UART used for LoRa communication
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart1;

extern uint8_t config[5];

// 16-byte encryption key command (starts with 0xC6)
extern const uint8_t enc_key[17];
extern const uint8_t p_reader[3];//cmd sent to module to read paarameter configured on module
extern uint8_t param[6];

extern const uint8_t general[2];//

extern const uint8_t powersaving[2];

extern const uint8_t wakeup[2];/*/uart open wireless chalel open and the only differenace between it and general mode is
before the packet is transmitted the wake code is automatically increased so that it can wake up the reciver in powersaving mode*/

extern const uint8_t sleep[2];// this mode we can configure  module on it


// === Initialization & Setup ===
uint8_t lora_init(void);                      // Put LoRa into config mode
void    lora_set_mode(const uint8_t * mod); // Set mode pins

// === Configuration ===
void    lora_send_config(void);
void    lora_send_enc_key(void);

// === Data ===
uint8_t lora_send_data(uint8_t *data, uint8_t len);   // Send user data
uint8_t lora_receive_data(uint8_t *buffer, uint8_t max_len); // Receive data

// === Utility ===
uint8_t lora_wait_ok();    // Wait for ASCII "OK"
uint8_t lora_read_params();  // Read back config with 0xC1 0xC1 0xC1
uint8_t lora_check_error(void);               // Placeholder for AUX pin or status check

#endif
