/**
 * @file lora.hpp
 * @brief Header file for LoRa communication driver.
 *
 * This file contains declarations for functions and variables used in the LoRa communication driver.
 * It interfaces with the STM32 HAL library for UART communication.
 */

#ifndef LORA_INIT
#define LORA_INIT

#include "main.h"

/**
 * @brief Buffer for UART reception.
 */
extern uint8_t uart_rx_buffer[100];

/**
 * @brief UART handle for LoRa communication.
 */
extern UART_HandleTypeDef huart2;

/**
 * @brief Command to set LoRa band.
 */
uint8_t const band[] = "AT+BAND=868000000\r\n";

/**
 * @brief Command to set LoRa password.
 */
uint8_t const password[] = "AT+CPIN=LoRaSecure1234\r\n";

/**
 * @brief Command to get network ID.
 */
uint8_t const getid[] = "AT+NETWORKID\r\n";

/**
 * @brief Command to get device address.
 */
uint8_t const getadd[] = "AT+ADDRESS\r\n";

/**
 * @brief Device network ID.
 */
uint8_t my_id = 0;

/**
 * @brief Device address.
 */
uint8_t my_addr = 0;

/**
 * @brief Receiver network ID.
 */
uint8_t receiver_id = 0;

/**
 * @brief Receiver address.
 */
uint8_t receiver_addr = 0;

/**
 * @brief Retrieves the network ID of the device.
 * @return The network ID incremented by 1.
 */
uint8_t get_id();

/**
 * @brief Retrieves the device address.
 * @return The device address set to 1.
 */
uint8_t get_address();

/**
 * @brief Initializes the LoRa module.
 */
void lora_init();

/**
 * @brief Sends a single character over LoRa.
 * @param data The character to send.
 */
void lora_send_char(uint8_t data);

/**
 * @brief Sends initialization data over LoRa.
 * @param pdata Pointer to the data to send.
 */
void lora_sendinit(uint8_t *pdata);

/**
 * @brief Receives data from the LoRa module.
 * @return The received data.
 */
uint8_t lora_recive();

/**
 * @brief Processes a received LoRa message.
 * @param message The received message string.
 * @return The extracted data from the message.
 */
uint8_t process_message(const char *message);

/**
 * @brief Receives and processes a LoRa message.
 * @return The processed command/data.
 */
uint8_t receive_message();

/**
 * @brief Sends data over LoRa (not implemented).
 */
void lora_send();

#endif
