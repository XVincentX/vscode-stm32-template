#include "stm32f3xx.h"

int main(void)
{
  RCC->AHBENR = 1 << 18;
  GPIOB->MODER = 1 << 16;

  GPIOB->ODR = 1 << 8;

  while(1);
}
