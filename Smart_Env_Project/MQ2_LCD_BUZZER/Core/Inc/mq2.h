/*
 * mq2.h
 *
 *  Created on: Dec 30, 2025
 *      Author: priya
 */

#ifndef INC_MQ2_H_
#define INC_MQ2_H_
void MX_GPIO_Init(void);
void MX_ADC1_Init(void);

#ifndef __MAIN_H
#define __MAIN_H

#ifdef  __cplusplus

#endif




#include "stm32f4xx_hal.h"
void MX_ADC1_Init(void);
void MX_GPIO_Init(void);


#ifdef __cplusplus
}
#endif

#endif  /*  __MAIN_H */

#endif /* INC_MQ2_H_ */
