#ifndef _STM_EVAL_COMPAT_H_
#define _STM_EVAL_COMPAT_H_

#include "stm32f4xx.h"
#include "armcmx.h"

typedef GPIOPin Led_TypeDef;
typedef GPIOPin Button_TypeDef;
typedef GPIOMode_TypeDef ButtonMode_TypeDef;
typedef usart* COM_TypeDef;


void STM_EVAL_LEDInit(Led_TypeDef Led);
void STM_EVAL_LEDOn(Led_TypeDef Led);
void STM_EVAL_LEDOff(Led_TypeDef Led);
void STM_EVAL_LEDToggle(Led_TypeDef Led);
void STM_EVAL_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
uint32_t STM_EVAL_PBGetState(Button_TypeDef Button);
void STM_EVAL_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct);

#endif
