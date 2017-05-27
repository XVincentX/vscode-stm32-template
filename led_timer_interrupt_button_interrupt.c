#include "stm32f3xx.h"

const unsigned int leds[] = {
    1 << 8,
    1 << 9,
    1 << 10,
    1 << 11,
    1 << 12,
    1 << 13,
    1 << 14,
    1 << 15,
    1 << 8 | 1 << 9 | 1 << 10 | 1 << 11 | 1 << 12 | 1 << 13 | 1 << 14 | 1 << 15,
    0,
};

const unsigned int array_size = sizeof(leds) / sizeof(unsigned int);
unsigned int index = 0;

int main(void)
{
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN |
                 RCC_AHBENR_GPIOEEN;

  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

  GPIOE->MODER = 1 << 18 |
                 1 << 16 |
                 1 << 20 |
                 1 << 30 |
                 1 << 22 |
                 1 << 28 |
                 1 << 24 |
                 1 << 26;

  GPIOA->MODER &= ~GPIO_MODER_MODER0;

  TIM3->ARR = 4000;
  TIM3->PSC = 1000;
  TIM3->DIER |= TIM_DIER_UIE;

  NVIC->ISER[0] |= 1 << 29; // Timer
  NVIC->ISER[0] |= 1 << 6;  // User button

  SYSCFG->EXTICR[1] &= ~7;
  EXTI->IMR |= EXTI_IMR_MR0;
  EXTI->RTSR = EXTI_RTSR_TR0;

  while (1)
    ;
}

void EXTI0_IRQHandler()
{
  if ((GPIOA->IDR & GPIO_IDR_0))
  {
    TIM3->CR1 |= TIM_CR1_CEN;
    TIM3->CNT = 0;
    index = 0;
  }
}

void TIM3_IRQHandler()
{
  if ((TIM3->SR & TIM_SR_UIF) == TIM_SR_UIF)
  {
    GPIOE->ODR = leds[index % array_size];
    index++;
    TIM3->SR &= ~TIM_SR_UIF;

    if ((index % array_size) == 0)
    {
      TIM3->ARR = TIM3->ARR / 2;
      TIM3->CR1 &= ~TIM_CR1_CEN;
    }
  }
}
