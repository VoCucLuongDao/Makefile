#include "main.h" 
#include "stdio.h"

void Blink_led()
{
  RCC->AHB1ENR |= 0x01;
  
  GPIOA->MODER &= ~(0x3<<12);
  GPIOA->MODER |= 0x01<<12;
  GPIOA->OTYPER &= ~(0x01<<6);
}
void main()
{
  Blink_led();     
  while(1){
     GPIOA->ODR |=  0x01<<6;
     delayms(1000);
     GPIOA->ODR &= ~(0x01<<6);
     delayms(1000);
     
  }
}

//code use to test IRQ function...must comment this code and rebuild makefile to run
/*int x_value_test = 0;
void TIM8_CC_IRQHandler()
{
  if(TIM8->SR & 0x01)
    {
      x_value_test++;
      if(x_value_test > 10)
        GPIOA->ODR |=  0x01<<6;

      TIM8->SR &= ~0x01;
    }
}*/