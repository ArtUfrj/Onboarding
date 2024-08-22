#include <Arduino.h>
#include "stm32f1xx_hal.h"

// Definições dos pinos dos sensores e atuadores
#define SENSOR_DE_FORCA GPIO_PIN_0
#define SENSOR_DE_PROXIMIDADE GPIO_PIN_1
#define SENSOR_DE_POSICAO GPIO_PIN_2
#define ATUADOR1 GPIO_PIN_3
#define ATUADOR2 GPIO_PIN_4
#define ATUADOR3 GPIO_PIN_5

// Definição do valor de THRESHOLD
#define THRESHOLD 100  

void Relogio_Config(void);
static void MX_GPIO_Init(void);

int main(void) {
    HAL_Init();
    Relogio_Config();
    MX_GPIO_Init();

   while (1) {
        
        uint8_t valor_forca = HAL_GPIO_ReadPin(GPIOA, SENSOR_DE_FORCA);
        uint8_t valor_proximidade = HAL_GPIO_ReadPin(GPIOA, SENSOR_DE_PROXIMIDADE);
        uint8_t valor_posicao = HAL_GPIO_ReadPin(GPIOA, SENSOR_DE_POSICAO);
    // Leitura dos sensores
    if (valor_forca > THRESHOLD) {
            HAL_GPIO_WritePin(GPIOA, ATUADOR1, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(GPIOA, ATUADOR1, GPIO_PIN_RESET);
        }
        if (valor_proximidade > THRESHOLD) {
            HAL_GPIO_WritePin(GPIOA, ATUADOR2, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(GPIOA, ATUADOR2, GPIO_PIN_RESET);
        }
        if (valor_posicao > THRESHOLD) {
            HAL_GPIO_WritePin(GPIOA, ATUADOR3, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(GPIOA, ATUADOR3, GPIO_PIN_RESET);
        }
    }

 // Controle dos atuadores baseado nos valores dos sensores
        if (SENSOR_DE_FORCA > THRESHOLD) {
            HAL_GPIO_WritePin(GPIOA, ATUADOR1, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(GPIOA, ATUADOR1, GPIO_PIN_RESET);
        }

        if (SENSOR_DE_PROXIMIDADE > THRESHOLD) {
            HAL_GPIO_WritePin(GPIOA, ATUADOR2, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(GPIOA, ATUADOR2, GPIO_PIN_RESET);
        }

        if (SENSOR_DE_POSICAO > THRESHOLD) {
            HAL_GPIO_WritePin(GPIOA, ATUADOR3, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(GPIOA, ATUADOR3, GPIO_PIN_RESET);
        }
}

void SystemClock_Config(void) {
    // Configuração do relogio do sistema
}

static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Configuração dos pinos dos sensores
    GPIO_InitStruct.Pin = SENSOR_DE_FORCA | SENSOR_DE_PROXIMIDADE | SENSOR_DE_POSICAO;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, & GPIO_InitStruct);

    // Configuração dos pinos dos atuadores
    GPIO_InitStruct.Pin = ATUADOR1 | ATUADOR2 | ATUADOR3;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, & GPIO_InitStruct);
}

I2C_HandleTypeDef hi2c1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();

    uint8_t i2c_addr = 0x2C; // Endereço I2C do AD5254 sem bits de R/W

    uint8_t data[2];
    data[0] = 0x00; // Endereço do registro de comando
    data[1] = 0x80; // Valor a ser escrito

    while (1) {
        HAL_I2C_Master_Transmit(&hi2c1, i2c_addr << 1, data, 2, HAL_MAX_DELAY);
        HAL_Delay(1000);
    }
}

static void MX_I2C1_Init(void) {
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
        Error_Handler();
    }
}

void SystemClock_Config(void) {
    // Configuração do clock do sistema
}

static void MX_GPIO_Init(void) {
    // Inicialização dos GPIOs
}