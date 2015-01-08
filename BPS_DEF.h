/////////////////////////////////////////////////////////////////////////////////////////////////////
////////BPS_DEF.h////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/*BPS.def */
#ifndef __BPS_DEF_H
#define __BPS_DEF_H

/* BPS LIMIT SETPOINTS */
#define LIMIT_CURRENT_HIGH           80000
#define LIMIT_CURRENT_LOW         (-40000)
#define LIMIT_VOLTAGE_HIGH         3600000
#define LIMIT_VOLTAGE_LOW          2500000
#define LIMIT_TEMP_HIGH                 65
#define LIMIT_VOLTAGE_ARRAY_CUTON  3400000
#define LIMIT_VOLTAGE_ARRAY_CUTOFF 3500000

/* OTHER BPS SETTINGS*/
#define MODULES_USED         20
#define MODULES_MAX          48
#define RELAYON               1
#define RELAYOFF              0
#define DURATION_PRECHARGE 2000
#define DURATION_CHARGE    1000
#define VREF                  5

//////////////////////////////////////////
/*PIN ASSIGNMENTS FOR LEDS*/
#define LED_GOOD    13
#define LED_OV      12
#define LED_UV      12
#define LED_OT      12
#define LED_OC      12
#define LED_OTHER   13

/*PIN ASSIGNMENTS FOR MUXES */
#define MUXE0     6
#define MUXE1     7
#define MUXE2     8
#define MUXS0     2
#define MUXS1     3
#define MUXS2     4
#define MUXS3     5

/*PIN ASSIGNMENTS FOR ADC */
#define pin_Isense         ADC1
#define pin_Tsense         ADC2

/*PIN ASSIGNMENTS FOR OUTPUT RELAYS */
#define relay_main          9
#define relay_array        10
#define relay_precharge    11
////////////////////////////////////////////

/* INTERNALLY USED CONSTANTS */
#define ERR_NONE    0
#define ERR_OV      1
#define ERR_UV      2
#define ERR_OT      3
#define ERR_OC      4
#define ERR_OTHER   5
#define SSEG_NOTHING 0xFF
#define LED_NOTHING  0xFF

#define FALSE 0
#define TRUE 1

#define LOW 0
#define HIGH 1

#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////
////////end BPS_DEF.h////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
