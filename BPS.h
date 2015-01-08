///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////BPS.h/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "BPS_DEF.h"
#include "ADC.h"
//#include "stm32f4xx_adc.h"
#include <stm32f4xx.h> 

typedef struct BPS_STRUCT {
  uint32_t V[MODULES_MAX]; //Voltage in microVolts
  int8_t  T[MODULES_MAX]; //Temp in Celsius
  int32_t  I; //Current in milliAmps (discharge positive)
  uint8_t  num_modules;
  uint8_t  is_good;
  uint8_t  is_started;
} BPS_STRUCT;

typedef struct ERR_STRUCT {
  uint32_t V; //Voltage in microVolts
  int8_t  T; //Temp in Celsius
  int32_t  I; //Current in milliAmps (discharge positive)
  uint8_t  offender_module;
  uint8_t  error;
} ERR_STRUCT;

////////////////////////////////////////////////////////////////////////////
/* TASK LAYER ///////////////////////////////////////////////////         */

void     BPSinit(void);
void     BPScheck(void);
void     DISPLAYout(void);

/* MIDDLE LAYER ////////////////////////////////////////////////////////////
   Items in this layer control the collecting of specific pieces of 
   information from the different input sources. It also includes
   functions for handling the output relays, and onboard displays         */

uint32_t Vget(uint8_t index);
int8_t   Tget(uint8_t index);
int32_t  Iget(void);
void     MUXset(uint8_t index);
void     CARstart(void);
void     CARshutdown(uint8_t errorcd, uint8_t offender,uint32_t V, int8_t T, int32_t I);
void     SSEGwrite(uint8_t val);
void     LEDwrite(uint8_t led);
void     ARRAYcheck(uint8_t i);

/* LOW LEVEL //////////////////////////////////////////////////////////////////////////////////
   Handles helper functions which directly access microcontroller hardware */

uint16_t ADCget(ADC_TypeDef* ADCx);
void     I2Ctx(unsigned char address, unsigned char reg, unsigned char data, unsigned char data2);
////EXTRAS FOR ARDUINO COMPATIBILITY
void digitalWrite(uint8_t pin, uint8_t state);
uint8_t digitalRead(uint8_t pin);
uint16_t analogRead(ADC_TypeDef* ADCx);
uint8_t bitRead(uint8_t bitfield,  uint8_t bitpos);
void delay(int x);
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////end BPS.h///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
