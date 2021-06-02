
/* Header includes -----------------------------------------------------------*/
#include "delay.h"

/* Macro definitions ---------------------------------------------------------*/
/* Type definitions ----------------------------------------------------------*/
/* Variable declarations -----------------------------------------------------*/
/* Variable definitions ------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/
/* Function definitions ------------------------------------------------------*/

/**
  * @brief  Microsecond delay.
  * @param  [in] nus: The number of microseconds delay.
  * @return None.
  */
void delayus(uint64_t nus)
{
  uint64_t nms = 0;
  
  if(nus == 0)
  {
    return;
  }
  
  nms = nus / 1000;
  nus = nus % 1000;
  
  if(nms > 0)
  {
    delayms(nms);
  }
  
  if(nus > 0)
  {

    SysTick->CTRL &= ~(0x010007);                  /* Configures the SysTick clock source. */
    SysTick->LOAD = SystemCoreClock / 8000000 * nus; /* Time load (SysTick-> LOAD is 24bit). */
    
    SysTick->VAL = 0;                                               /* Empty counter. */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;                       /* Start the countdown. */
    
    while((SysTick->CTRL&(1UL<<16)) != (1UL<<16));                  /* Wait time is reached. */
    
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;                      /* Close counter. */
  }
}

/**
  * @brief  Millisecond delay.
  * @param  [in] nms: The number of millisecond delay.
  * @return None.
  */
void delayms(uint64_t nms)
{
  if(nms == 0)
  {
    return;
  }
  
  while(nms > 500)
  {

    SysTick->CTRL &= ~(0x010007);                /* Configures the SysTick clock source. */
    SysTick->LOAD = SystemCoreClock / 8000 * 500;  /* Time load (SysTick-> LOAD is 24bit). */
    
    
    SysTick->VAL = 0;                                             /* Empty counter. */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;                     /* Start the countdown. */
    
    while((SysTick->CTRL&(1UL<<16)) != (1UL<<16));                /* Wait time is reached. */
    
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;                    /* Close counter. */
    
    nms -= 500;
  }
  

  SysTick->CTRL &= ~(0x010007);                 /* Configures the SysTick clock source. */
  SysTick->LOAD = SystemCoreClock / 8000 * nms;    /* Time load (SysTick-> LOAD is 24bit). */
  
  
  SysTick->VAL = 0;                                               /* Empty counter. */
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;                       /* Start the countdown. */
  
  while((SysTick->CTRL&(1UL<<16)) != (1UL<<16));                  /* Wait time is reached. */
  
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;                      /* Close counter. */
}

/**
  * @brief  Second delay.
  * @param  [in] ns: The number of second delay.
  * @return None.
  */
void delays(uint64_t ns)
{
  while(ns > 0)
  {
    delayms(1000);
    ns--;
  }
}
