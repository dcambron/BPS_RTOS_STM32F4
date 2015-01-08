#ifndef __ADC_H
#define __ADC_H

#include "stm32f4xx_adc.h"
extern void adc_configure(void);
extern int adc_convert(ADC_TypeDef* ADCx);

#endif
