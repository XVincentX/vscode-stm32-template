#include "stm32f3xx.h"

int main(void)
{
  RCC->AHBENR = RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOEEN;                                        // Clock on GPIOE and A
  GPIOE->MODER = 1 << 18 | 1 << 16 | 1 << 20 | 1 << 30 | 1 << 22 | 1 << 28 | 1 << 24 | 1 << 26; //Set port 8,6,7,9 to input
  GPIOA->MODER &= ~GPIO_MODER_MODER0;                                                           // Set port 0 as input

  const unsigned int leds[] = {
      1 << 9,
      1 << 8,
      1 << 10,
      1 << 15,
      1 << 11,
      1 << 14,
      1 << 12,
      1 << 13,
  };

  unsigned int index = 0;

  while (1)
  {
    if (GPIOA->IDR & GPIO_IDR_0)
    {
      GPIOE->ODR = leds[index % 8];
      while (GPIOA->IDR & GPIO_IDR_0)
        ;
      index++;
    }
  }
}
