/**
 * @file lora.cpp
 * @brief Implementation of LoRa communication driver functions.
 *
 * This file contains the implementation of functions for initializing and communicating
 * with a LoRa module using the STM32 HAL library.
 */

#include "lora.hpp"
#include <cstring>
#include <cstdio>

/**
 * @brief Buffer for UART reception.
 */
uint8_t uart_rx_buffer[100];

/**
 * @brief Initializes the LoRa module by setting the band and password.
 */
void lora_init() {
    receiver_id = get_id();
    receiver_addr = get_address();

    HAL_UART_Transmit(&huart2, band, sizeof(band)-1, 100);
    HAL_UART_Transmit(&huart2, password, sizeof(password)-1, 100);
}

/**
 * @brief Sends initialization data over LoRa.
 * @param pdata Pointer to the data to send.
 */
void lora_sendinit(uint8_t *pdata) {
    HAL_UART_Transmit(&huart2, pdata, sizeof(pdata)-1, 100);
}

/**
 * @brief Receives data from the LoRa module.
5.
 * @return The received data after processing.
 */
uint8_t lora_recive() {
    return receive_message();
}

/**
 * @brief Receives and processes a LoRa message.
 * @return The processed command/data.
 */
uint8_t receive_message() {
    memset(uart_rx_buffer, 0, 100);
    uint8_t cmd;
    HAL_UART_Receive(&huart2, uart_rx_buffer, 100, 100);

    if (strstr((const char*)uart_rx_buffer, "+RCV=")) {
        cmd = process_message((const char*)uart_rx_buffer);
    }

    return cmd;
}

/**
 * @brief Processes a received LoRa message.
 * @param message The received message string.
 * @return The extracted data from the message.
 */
uint8_t process_message(const char *message) {
    int address = 0;
    int rssi = 0;
    int lenth = 0;
    uint8_t data = 0;
    sscanf(message, "+RCV=%d,%d,%[^,],%d,%d", &address, &lenth, &data, &rssi, NULL);
    return data;
}

/**
 * @brief Sends a single character over LoRa.
 * @param data The character to send.
 */
void lora_send_char(uint8_t data) {
    uint8_t buffer[50] = {0};
    memset(buffer, 0, 50);
    sprintf(buffer, "AT+SEND=%d,1,%c\r\n", receiver_addr, data);
    HAL_UART_Transmit(&huart2, buffer, sizeof(buffer), 100);
}

/**
 * @brief Retrieves the network ID of the device.
 * @return The network ID incremented by 1.
 */
uint8_t get_id() {
    uint8_t buffer[25] = {0};
    HAL_UART_Transmit(&huart2, getid, sizeof(getid), 100);
    HAL_UART_Receive(&huart2, buffer, sizeof(buffer), 100);
    sscanf(buffer, "+NETWORKID=%d", &my_id);
    return my_id + 1;
}

/**
 * @brief Retrieves the device address.
 * @return The device address set to 1.
 */
uint8_t get_address() {
    uint8_t buffer[25] = {0};
    HAL_UART_Transmit(&huart2, getadd, sizeof(getadd), 100);
    HAL_UART_Receive(&huart2, buffer, sizeof(buffer), 100);
    sscanf(buffer, "+ADDRESS=%d", &my_addr);
    return my_addr = 1;
}
