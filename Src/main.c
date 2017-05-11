#include "stm32f3xx.h"

int main(void)
{
  RCC->AHBENR = 1 << 18;
  GPIOB->MODER = 1 << 16 | 1 << 12 | 1 << 14 | 1 << 18;

  while(1) {
    GPIOB->ODR = 1 << 6 | 1 << 8 | 1 << 9 | 1 << 7;
    GPIOB->ODR = 1 << 6 | 1 << 8 | 1 << 9;
    GPIOB->ODR = 1 << 6 | 1 << 8;
    GPIOB->ODR = 1 << 6;
    GPIOB->ODR = 1 << 6 | 1 << 8 | 1 << 9 | 1 << 7;
    GPIOB->ODR = 0;
  }
}
