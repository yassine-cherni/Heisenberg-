#include "stm32f4xx_hal.h"

#define MOTOR1_PIN1 GPIO_PIN_0
#define MOTOR1_PIN2 GPIO_PIN_1
#define MOTOR2_PIN1 GPIO_PIN_2
#define MOTOR2_PIN2 GPIO_PIN_3

void GPIO_Init(void);
void MotorControl(int motor, int direction);

int main(void) {
    HAL_Init();
    SystemClock_Config();

    GPIO_Init();

    while (1) {
        MotorControl(1, 1);  // Moteur 1 en avant
        MotorControl(2, 0);  // Moteur 2 en arrière

        HAL_Delay(1000);

        MotorControl(1, 0);  // Arrêt moteur 1
        MotorControl(2, 1);  // Moteur 2 en avant

        HAL_Delay(1000);
    }
}

void GPIO_Init(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = MOTOR1_PIN1 | MOTOR1_PIN2 | MOTOR2_PIN1 | MOTOR2_PIN2;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void MotorControl(int motor, int direction) {
    if (motor == 1) {
        if (direction == 1) {
            HAL_GPIO_WritePin(GPIOA, MOTOR1_PIN1, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOA, MOTOR1_PIN2, GPIO_PIN_RESET);
        } else {
            HAL_GPIO_WritePin(GPIOA, MOTOR1_PIN1, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, MOTOR1_PIN2, GPIO_PIN_SET);
        }
    } else if (motor == 2) {
        if (direction == 1) {
            HAL_GPIO_WritePin(GPIOA, MOTOR2_PIN1, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOA, MOTOR2_PIN2, GPIO_PIN_RESET);
        } else {
            HAL_GPIO_WritePin(GPIOA, MOTOR2_PIN1, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, MOTOR2_PIN2, GPIO_PIN_SET);
        }
    }
}
