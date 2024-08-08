#include <Arduino.h>

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