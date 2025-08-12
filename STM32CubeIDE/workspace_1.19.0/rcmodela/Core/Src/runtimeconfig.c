#include "runtimeconfig.h"
void getargs_sa818s() {

    HAL_UART_Transmit(&huart6, (uint8_t*)"Write the tx_freq:\r\n", 20, 1000);
    char tx_freq_buf[10] = {0};
    HAL_UART_Receive(&huart6, (uint8_t*)tx_freq_buf, sizeof(tx_freq_buf)-1, HAL_MAX_DELAY);
    sa818s_config.tx_freq = atof(tx_freq_buf);

    HAL_UART_Transmit(&huart6, (uint8_t*)"Write the rx_freq:\r\n", 20, 1000);
    char rx_freq_buf[10] = {0};
    HAL_UART_Receive(&huart6, (uint8_t*)rx_freq_buf, sizeof(rx_freq_buf)-1, HAL_MAX_DELAY);
    sa818s_config.rx_freq = atof(rx_freq_buf);

    HAL_UART_Transmit(&huart6, (uint8_t*)"Write the squelch:\r\n", 21, 1000);
    char squelch_buf[3] = {0};
    HAL_UART_Receive(&huart6, (uint8_t*)squelch_buf, sizeof(squelch_buf)-1, HAL_MAX_DELAY);
    sa818s_config.squelch = atoi(squelch_buf);
    // SA818S_SetGroup_values();
    SA818S_ApplyConfig();
}

void getargs_ryrl898() {
    HAL_UART_Transmit(&huart6, (uint8_t*)"Write the config and start by edit password for default password contact alebel\r\n", 84, 1000);
    HAL_UART_Receive(&huart6, (uint8_t*)lora_config.password, sizeof(lora_config.password)-1, HAL_MAX_DELAY);

    HAL_UART_Transmit(&huart6, (uint8_t*)"Write the id:\r\n", 15, 1000);
    char id_buf[6] = {0};
    HAL_UART_Receive(&huart6, (uint8_t*)id_buf, sizeof(id_buf)-1, HAL_MAX_DELAY);
    lora_config.id = atoi(id_buf);

    HAL_UART_Transmit(&huart6, (uint8_t*)"Write the address:\r\n", 20, 1000);
    char addr_buf[6] = {0};
    HAL_UART_Receive(&huart6, (uint8_t*)addr_buf, sizeof(addr_buf)-1, HAL_MAX_DELAY);
    lora_config.addr = atoi(addr_buf);

    HAL_UART_Transmit(&huart6, (uint8_t*)"Enter band:\r\n", 13, 1000);
    HAL_UART_Receive(&huart6, (uint8_t*)lora_config.band, sizeof(lora_config.band)-1, HAL_MAX_DELAY);

    lora_config.receiver_id = (IAM == LORA_ROLE_TRANSMITTER) ? lora_config.id + 1 : lora_config.id - 1;
    lora_apply_config();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART6) {
    
        getargs_ryrl898();
        getargs_sa818s();
        
    }
}


//gckc
