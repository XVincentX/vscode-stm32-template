#include "stm32f3xx.h"

int main(void)
{
  RCC->AHBENR = 1 << 18 | 1 << 17; // Clock on GPIOB and A
  GPIOB->MODER = 1 << 16 | 1 << 12 | 1 << 14 | 1 << 18; //Set port 8,6,7,9 to input
  GPIOA->MODER = 0; // Set port 0 as input

  while(1) {
    if (GPIOA->IDR & 1)
      GPIOB->ODR = 1 << 6 | 1 << 8 | 1 << 9 | 1 << 7;
  }
}
