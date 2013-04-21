/*
 * delay5.c
 *
 *  Created on: 2012/11/15
 *      Author: sin
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"

#include "delay.h"
//#include "platform_config.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

volatile uint32_t __counter_micros;
volatile uint32_t __counter_millis;
volatile uint32_t __countdown_millis;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
 * @brief  millisecond
 * @param  none
 * @retval None
 */
void TIMx_delaytimer_start(void) {
	// TIM_TimeBaseInitTypeDef's order is {uint16_t TIM_Prescaler, uint16_t TIM_CounterMode, uint16_t TIM_Period, uint16_t TIM_ClockDivision, uint8_t TIM_RepetitionCounter}
	TIM_TimeBaseInitTypeDef TimeBaseStructure;
//			= { 84, TIM_CounterMode_Up, 999, TIM_CKD_DIV1, 0 };
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);

	TimeBaseStructure.TIM_Prescaler = (RCC_Clocks.SYSCLK_Frequency>>1)/1000000L ;
	TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBaseStructure.TIM_Period = 1000 - 1;
	TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TimeBaseStructure.TIM_RepetitionCounter = 0;

	//Supply APB1 Clock
	RCC_APB1PeriphClockCmd(DELAYRCCPERIPH, ENABLE);
	/* Time base configuration */
	TIM_TimeBaseInit(DELAYTIMx, &TimeBaseStructure);
//  TIM_SelectOnePulseMode(TIM2, TIM_OPMode_Repetitive);
	TIM_ITConfig(DELAYTIMx, TIM_IT_Update, ENABLE);

	/* Enable the TIM2 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = DELAYIRQCHANNEL;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// reset time-passed counters
	__counter_micros = 0;
	__counter_millis = 0;
	TIM_SetCounter(DELAYTIMx, 0);
	__countdown_millis = 0;
	
	/* TIM enable counter */
	TIM_Cmd(DELAYTIMx, ENABLE);
}

uint32_t micros(void) {
	return __counter_micros + TIM_GetCounter(DELAYTIMx);
}

uint32_t millis(void) {
	return __counter_millis;
}


void TIMx_delaytimer_reset() {
	__counter_millis = 0;
	__counter_micros = 0;
	TIM_SetCounter(DELAYTIMx, 0);
}

void TIMx_delaytimer_up(void) {
	uint32 timx = TIM_GetCounter(DELAYTIMx);
	while( timx == TIM_GetCounter(DELAYTIMx) );
}


void delay_ms(uint32_t w) {
	uint32_t wtill = millis() + w;
	if ( wtill < millis() ) {
		while ( millis() >= wtill );
	}
	while (millis() < wtill) ;
}

void delay_us(uint32_t w) {
	uint32 timx = TIM_GetCounter(DELAYTIMx);
	for ( ; w > 0 ; ) {
		if (timx == TIM_GetCounter(DELAYTIMx)) 
			continue;
		timx = TIM_GetCounter(DELAYTIMx);
		w--;
	}
}

void delay_nop(uint32_t w) {
	for(; w > 0; w--) {
		__NOP();
	}
}

void countdown_start(uint32_t t) {
	__countdown_millis = t;
}

uint8_t countdown_expired(void) {
	return __countdown_millis == 0;
}

void DELAYIRQHANDLER(void) {
	if (TIM_GetITStatus(DELAYTIMx, TIM_IT_Update ) == SET) {
		TIM_ClearITPendingBit(DELAYTIMx, TIM_IT_Update );
		if ( __countdown_millis > 0 )
			__countdown_millis--;
		__counter_micros += 1000;
		__counter_millis += 1;
	}
}

