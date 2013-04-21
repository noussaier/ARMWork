/*
 * delay.h
 *
 *  Created on: 2012/11/15
 *      Author: sin
 */

#ifndef _DELAY_H_
#define _DELAY_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "stm32f4xx.h"
#include "armcmx.h"

#if (!defined (DELAYTIMER) ) || ( DELAYTIMER==2 )
#define DELAYTIMx           TIM2
#define DELAYIRQHANDLER     TIM2_IRQHandler
#define DELAYIRQCHANNEL     TIM2_IRQn
#define DELAYRCCPERIPH      RCC_APB1Periph_TIM2
#endif

extern volatile uint32_t __counter_micros;
extern volatile uint32_t __counter_millis;
extern volatile uint32_t __countdown_millis;

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

uint32_t micros(void);
uint32_t millis(void);
	
void TIMx_delaytimer_start(void);
void TIMx_delaytimer_up(void);
void TIMx_delaytimer_reset(void);
void TIMx_IRQHandler(void);

void delay_ms(uint32_t);
void delay_us(uint32_t);
void countdown_start(uint32_t t);
uint8_t countdown_expired(void);
void delay_nop(uint32_t);

#define delay(x)  delay_ms(x)
#define delayMicroseconds(x)  delay_us(x)


#ifdef __cplusplus
}
#endif


#endif /* _DELAY_H_ */
