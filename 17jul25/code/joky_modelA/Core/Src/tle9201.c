#include "tle9201.h"
#include "main.h"  // Make sure this has your TIM and SPI handles

extern TIM_HandleTypeDef TLE9201_PWM_TIM;

void TLE9201_Init(void)
{
    // Start PWM Timer
    HAL_TIM_PWM_Start(&TLE9201_PWM_TIM, TLE9201_PWM_CHANNEL);

    // Set DIS low to enable output
    HAL_GPIO_WritePin(TLE9201_DIS_GPIO_Port, TLE9201_DIS_Pin, GPIO_PIN_RESET);

    // Default direction
    HAL_GPIO_WritePin(TLE9201_DIR_GPIO_Port, TLE9201_DIR_Pin, GPIO_PIN_RESET);
}

void TLE9201_EnableOutput(void)
{
    HAL_GPIO_WritePin(TLE9201_DIS_GPIO_Port, TLE9201_DIS_Pin, GPIO_PIN_RESET);
}

void TLE9201_DisableOutput(void)
{
    HAL_GPIO_WritePin(TLE9201_DIS_GPIO_Port, TLE9201_DIS_Pin, GPIO_PIN_SET);
}

void TLE9201_SetDirection(uint8_t dir)
{
    HAL_GPIO_WritePin(TLE9201_DIR_GPIO_Port, TLE9201_DIR_Pin, dir ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void TLE9201_SetSpeed(uint8_t duty)
{
    // Clamp to 0–255
    if (duty > 255) duty = 255;
    __HAL_TIM_SET_COMPARE(&TLE9201_PWM_TIM, TLE9201_PWM_CHANNEL, duty);
}

static uint8_t TLE9201_TransferByte(uint8_t tx)
{
    uint8_t rx = 0;
    HAL_GPIO_WritePin(TLE9201_CSN_GPIO_Port, TLE9201_CSN_Pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(&hspi3, &tx, &rx, 1, 100);
    HAL_GPIO_WritePin(TLE9201_CSN_GPIO_Port, TLE9201_CSN_Pin, GPIO_PIN_SET);
    return rx;
}

uint8_t TLE9201_ReadDiagnosis(void)
{
    return TLE9201_TransferByte(TLE9201_CMD_RD_DIA);
}

uint8_t TLE9201_ReadRevision(void)
{
    return TLE9201_TransferByte(TLE9201_CMD_RD_REV);
}

void TLE9201_ResetDiagnosis(void)
{
    TLE9201_TransferByte(TLE9201_CMD_RES_DIA);
}
