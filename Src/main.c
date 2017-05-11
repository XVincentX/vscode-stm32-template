#include "stm32f3xx.h"

int main(void)
{
  RCC->AHBENR = 1 << 18 | 1 << 17;                      // Clock on GPIOB and A
  GPIOB->MODER = 1 << 16 | 1 << 12 | 1 << 14 | 1 << 18; //Set port 8,6,7,9 to input
  GPIOA->MODER &= 0;                                    // Set port 0 as input

  const unsigned int leds[] = {
      1 << 6,
      1 << 7,
      1 << 8,
      1 << 9,
  };

  unsigned int index = 0;

  while (1)
  {
    if (GPIOA->IDR & GPIO_IDR_0)
    {
      GPIOB->ODR = leds[index % 4];
      while (GPIOA->IDR & GPIO_IDR_0)
        ;
      index++;
    }
  }
}
