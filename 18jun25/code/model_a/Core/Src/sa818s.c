#include "sa818s.h"

// UART Buffer for responses
#define RX_BUFFER_SIZE 64
static uint8_t rx_buffer[RX_BUFFER_SIZE];
static volatile uint8_t rx_index = 0;
static volatile uint8_t rx_complete = 0;
uint8_t group_data[6]; // Buffer to hold group data
// typedef struct {
//     uint8_t bandwidth;      // 0: 12.5kHz, 1: 25kHz
//     float tx_freq;         // Transmit frequency in MHz (134.000 to 480.000)
//     float rx_freq;         // Receive frequency in MHz (134.000 to 480.000)
//     uint16_t tx_ctcss;    // Transmit CTCSS in Hz (0 to 255)
//     uint8_t squelch;       // Squelch level (0 to 8)
//     uint16_t rx_ctcss;    // Receive CTCSS in Hz (0 to 255)
// } SA818S_GroupConfig_t;
SA818S_GroupConfig_t sa818s_config;

 //= {
//     .bandwidth = 0,      // Default: 12.5kHz
//     .tx_freq = 134.000f, // Default: 134.000 MHz
//     .rx_freq = 134.000f, // Default: 134.000 MHz
//     .tx_ctcss = 0,       // Default: No CTCSS
//     .squelch = 0,        // Default: Squelch level 0
//     .rx_ctcss = 0        // Default: No CTCSS
// };
// UART Receive Callback
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//    if (huart == &huart2) {
//        rx_complete = 1; // Signal that a response has been received
//    }
//}

// Send AT command and wait for response
static HAL_StatusTypeDef SA818S_SendCommand(const char *cmd, char *response, uint32_t timeout) {
    rx_index = 0;
    rx_complete = 0;
    memset(rx_buffer, 0, RX_BUFFER_SIZE);

    // Send command
    if (HAL_UART_Transmit(&huart2, (uint8_t *)cmd, strlen(cmd), 100) != HAL_OK) {
        return HAL_ERROR;
    }

    // Start receiving response
    HAL_UART_Receive_IT(&huart2, rx_buffer, RX_BUFFER_SIZE);

    // Wait for response or timeout
    uint32_t start = HAL_GetTick();
    while (!rx_complete && (HAL_GetTick() - start) < timeout) {
        HAL_Delay(1);
    }

    if (!rx_complete) {
        HAL_UART_AbortReceive(&huart2);
        return HAL_TIMEOUT;
    }

    // Copy response to output buffer
    if (response) {
        strncpy(response, (char *)rx_buffer, RX_BUFFER_SIZE);
    }

    return HAL_OK;
}

// Initialize SA818S module (UART only)
HAL_StatusTypeDef SA818S_Init(void) {
    // Initialize UART (already configured in STM32CubeMX, ensure 9600 baud, 8-N-1)
    HAL_UART_Receive_IT(&huart2, rx_buffer, RX_BUFFER_SIZE);
    SA818S_ReadGroup(&sa818s_config.bandwidth, &sa818s_config.tx_freq, &sa818s_config.rx_freq, &sa818s_config.tx_ctcss, &sa818s_config.squelch, &sa818s_config.rx_ctcss);

    // Verify module connectivity
    // return SA818S_Handshake();
}

// Handshake command
HAL_StatusTypeDef SA818S_Handshake(void) {
    char response[RX_BUFFER_SIZE];
    HAL_StatusTypeDef status = SA818S_SendCommand("AT+DMOCONNECT\r\n", response, 1000);
    
    if (status == HAL_OK && strstr(response, "+DMOCONNECT:0") != NULL) {
        return HAL_OK;
    }
    return HAL_ERROR;
}

// Set group parameters
HAL_StatusTypeDef SA818S_SetGroup(uint8_t bandwidth, float tx_freq, float rx_freq, 
                                  uint16_t tx_ctcss, uint8_t squelch, uint16_t rx_ctcss) {
    char cmd[64];
    char response[RX_BUFFER_SIZE];
    
    // Validate inputs
    if (bandwidth > 1 || squelch > 8 || tx_freq < 134.0f || tx_freq > 480.0f || rx_freq < 134.0f || rx_freq > 480.0f) {
        return HAL_ERROR;
    }

    sprintf(cmd, sizeof(cmd), "AT+DMOSETGROUP=%u,%.4f,%.4f,%04u,%u,%04u\r\n",bandwidth, tx_freq, rx_freq, tx_ctcss, squelch, rx_ctcss);
    
    HAL_StatusTypeDef status = SA818S_SendCommand(cmd, response, 1000);
    if (status == HAL_OK && strstr(response, "+DMOSETGROUP:0") != NULL) {
        return HAL_OK;
    }
    return HAL_ERROR;
}

void SA818S_ApplyConfig(void){
    SA818S_SetGroup(sa818s_config.bandwidth, sa818s_config.tx_freq, sa818s_config.rx_freq, 
                  sa818s_config.tx_ctcss, sa818s_config.squelch, sa818s_config.rx_ctcss);
}
// Set volume
HAL_StatusTypeDef SA818S_SetVolume(uint8_t volume) {
    char cmd[32];
    char response[RX_BUFFER_SIZE];
    
    if (volume < 1 || volume > 8) {
        return HAL_ERROR;
    }

    snprintf(cmd, sizeof(cmd), "AT+DMOSETVOLUME=%u\r\n", volume);
    HAL_StatusTypeDef status = SA818S_SendCommand(cmd, response, 1000);
    if (status == HAL_OK && strstr(response, "+DMOSETVOLUME:0") != NULL) {
        return HAL_OK;
    }
    return HAL_ERROR;
}

// Set filters
HAL_StatusTypeDef SA818S_SetFilter(uint8_t pre_de_emph, uint8_t highpass, uint8_t lowpass) {
    char cmd[32];
    char response[RX_BUFFER_SIZE];
    
    snprintf(cmd, sizeof(cmd), "AT+SETFILTER=%u,%u,%u\r\n", pre_de_emph, highpass, lowpass);
    HAL_StatusTypeDef status = SA818S_SendCommand(cmd, response, 1000);
    if (status == HAL_OK && strstr(response, "+DMOSETFILTER:0") != NULL) {
        return HAL_OK;
    }
    return HAL_ERROR;
}

// Set tail tone
HAL_StatusTypeDef SA818S_SetTailTone(uint8_t enable) {
    char cmd[32];
    char response[RX_BUFFER_SIZE];
    
    snprintf(cmd, sizeof(cmd), "AT+SETTAIL=%u\r\n", enable);
    HAL_StatusTypeDef status = SA818S_SendCommand(cmd, response, 1000);
    if (status == HAL_OK && strstr(response, "+DMOSETTAIL:0") != NULL) {
        return HAL_OK;
    }
    return HAL_ERROR;
}

// Read group parameters
HAL_StatusTypeDef SA818S_ReadGroup(uint8_t *bandwidth, float *tx_freq, float *rx_freq, 
                                   uint16_t *tx_ctcss, uint8_t *squelch, uint16_t *rx_ctcss) {
    char response[RX_BUFFER_SIZE];
    HAL_StatusTypeDef status = SA818S_SendCommand("AT+DMOREADGROUP\r\n", response, 1000);
    
    if (status == HAL_OK && strstr(response, "+DMOREADGROUP:") != NULL) {
        sscanf(response, "+DMOREADGROUP:%hhu,%f,%f,%hu,%hhu,%hu", bandwidth, tx_freq, rx_freq, tx_ctcss, squelch, rx_ctcss);
        return HAL_OK;
    }
    return HAL_ERROR;
}

// Read RSSI
HAL_StatusTypeDef SA818S_ReadRSSI(uint16_t *rssi) {
    char response[RX_BUFFER_SIZE];
    HAL_StatusTypeDef status = SA818S_SendCommand("RSSI?\r\n", response, 1000);
    
    if (status == HAL_OK && strstr(response, "RSSI:") != NULL) {
        sscanf(response, "RSSI:%hu", rssi);
        return HAL_OK;
    }
    return HAL_ERROR;
}

// Read version
HAL_StatusTypeDef SA818S_ReadVersion(char *version) {
    char response[RX_BUFFER_SIZE];
    HAL_StatusTypeDef status = SA818S_SendCommand("AT+VERSION\r\n", response, 1000);
    
    if (status == HAL_OK && strstr(response, "+VERSION:") != NULL) {
        sscanf(response, "+VERSION:%s", version);
        return HAL_OK;
    }
    return HAL_ERROR;
}

// Function to get user input for SA818S configuration
// void getargs_sa818s() {

//     HAL_UART_Transmit(&huart6, (uint8_t*)"Write the tx_freq:\r\n", 20, 1000);
//     char tx_freq_buf[10] = {0};
//     HAL_UART_Receive(&huart6, (uint8_t*)tx_freq_buf, sizeof(tx_freq_buf)-1, HAL_MAX_DELAY);
//     sa818s_config.tx_freq = atof(tx_freq_buf);

//     HAL_UART_Transmit(&huart6, (uint8_t*)"Write the rx_freq:\r\n", 20, 1000);
//     char rx_freq_buf[10] = {0};
//     HAL_UART_Receive(&huart6, (uint8_t*)rx_freq_buf, sizeof(rx_freq_buf)-1, HAL_MAX_DELAY);
//     sa818s_config.rx_freq = atof(rx_freq_buf);

//     HAL_UART_Transmit(&huart6, (uint8_t*)"Write the squelch:\r\n", 21, 1000);
//     char squelch_buf[3] = {0};
//     HAL_UART_Receive(&huart6, (uint8_t*)squelch_buf, sizeof(squelch_buf)-1, HAL_MAX_DELAY);
//     sa818s_config.squelch = atoi(squelch_buf);

// }
