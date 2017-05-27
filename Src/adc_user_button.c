#include "stm32f3xx.h"

float res = 0.0f;

int main(void)
{
  RCC->AHBENR |= RCC_AHBENR_ADC12EN | RCC_AHBENR_GPIOAEN;
  GPIOA->MODER |= GPIO_MODER_MODER0;

  ADC1->CR &= ~ADC_CR_ADVREGEN_1;
  ADC1->CR |= ADC_CR_ADVREGEN_0;

  for (int i = 0; i < 1000; i++)
    ;

  ADC1_2_COMMON->CCR |= ADC12_CCR_CKMODE_0;

  ADC1->CR |= ADC_CR_ADCAL;

  while ((ADC1->CR & ADC_CR_ADCAL) == ADC_CR_ADCAL)
    ;

  ADC1->CR |= ADC_CR_ADEN;

  while ((ADC1->ISR & ADC_ISR_ADRD) == ADC_ISR_ADRD)
    ;

  ADC1->CFGR |= ADC_CFGR_CONT;
  ADC1->SQR1 = ADC_SQR1_SQ1_0;
  ADC1->SQR1 &= ~ADC_SQR1_L;
  ADC1->SMPR1 |= ADC_SMPR1_SMP1;

  ADC1->CR |= ADC_CR_ADSTART;

  while (1)
  {
    while ((ADC1->ISR & ADC_ISR_EOC) != ADC_ISR_EOC)
      ;

    res = ADC1->DR * (3.0f / 4096.0f);
    
    printf("Res is: %f", res);
  }
}
