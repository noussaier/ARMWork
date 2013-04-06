/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32_OPEN407VC_H
#define __STM32_OPEN407VC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx.h"
#include "armcmx.h"
#include "stm32f4_discovery.h"

typedef enum { 
  JOY_NONE = NOT_A_PIN,
  JOY_SEL = PC7,
  JOY_DOWN = PC6,
  JOY_LEFT = PB15,
  JOY_RIGHT = PA6,
  JOY_UP = PA4
} JOYState_TypeDef;


#ifdef __cplusplus
}
#endif

#endif /* __STM32F4_DISCOVERY_H */
