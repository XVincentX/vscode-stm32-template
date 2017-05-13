#include "stm32f3xx.h"

int main(void)
{
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN |
                 RCC_AHBENR_GPIOEEN;

  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

  GPIOE->MODER = 1 << 18 |
                 1 << 16 |
                 1 << 20 |
                 1 << 30 |
                 1 << 22 |
                 1 << 28 |
                 1 << 24 |
                 1 << 26;

  GPIOA->MODER &= ~GPIO_MODER_MODER0;

  const unsigned int leds[] = {
      1 << 8,
      1 << 9,
      1 << 10,
      1 << 11,
      1 << 12,
      1 << 13,
      1 << 14,
      1 << 15,
      1 << 8 | 1 << 9  | 1 << 10  | 1 << 11  | 1 << 12 | 1 << 13 | 1 << 14 | 1 << 15,
      0,
  };

  const unsigned int array_size = sizeof(leds) / sizeof(unsigned int);

  unsigned int index = 0;

  TIM2->ARR = 4000000;

  while (1)
  {
    if ((GPIOA->IDR & GPIO_IDR_0))
    {
      TIM2->CR1 |= TIM_CR1_CEN;
      TIM2->CNT = 0;
      index = 0;
    }

    if ((TIM2->SR & TIM_SR_UIF) == TIM_SR_UIF)
    {
      GPIOE->ODR = leds[index % array_size];
      index++;
      TIM2->SR &= ~TIM_SR_UIF;

      if ((index % array_size) == 0)
      {
        TIM2->ARR = TIM2->ARR / 2;
        TIM2->CR1 &= ~TIM_CR1_CEN;
      }

    }
  }
}
