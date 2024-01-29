#include "stm32f4xx.h" // Include the specific STM32 series header file

#define HSE_VALUE    8000000  // External oscillator frequency
#define PLL_M        8       // PLL input divider
#define PLL_N        336     // PLL multiplication factor
#define PLL_P        2       // PLL main divider
#define PLL_Q        7       // PLL output divider for USB OTG FS, SDIO and RNG

void SystemInit(void) {
    // Set up the system clock

    // Configure the system clock source
    RCC->CR |= RCC_CR_HSEON;                    // Enable external oscillator
    while (!(RCC->CR & RCC_CR_HSERDY));        // Wait for HSE ready

    RCC->CFGR |= RCC_CFGR_SW_HSE;              // Select HSE as the system clock
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSE); // Wait for switch

    // Configure PLL
    RCC->PLLCFGR = (PLL_M << 0) | (PLL_N << 6) | (((PLL_P >> 1) - 1) << 16) | (RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24);

    // Enable PLL
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));       // Wait for PLL ready

    // Switch to PLL as the system clock
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL); // Wait for switch
}
