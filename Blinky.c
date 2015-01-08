/*----------------------------------------------------------------------------
 *      RL-ARM - RTX
 *----------------------------------------------------------------------------
 *      Name:    BLINKY.C
 *      Purpose: RTX example program
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2013 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/
#include <RTL.h>
#include <stm32f4xx.h>                  /* STM32F4xx Definitions             */
#include "stm32f4xx_i2c.h"
#include <stdio.h>

#include "BPS_DEF.h"
#include "BPS.h"
#include "LED.h"
#include "Serial.h"
#include "ADC.h"
#include "I2C.h"

extern BPS_STRUCT BPS;
extern ERR_STRUCT ERR;

OS_TID t_ThdSTARTUP;
OS_TID t_ThdBPScheck;
OS_TID t_ThdVget;
OS_TID t_ThdTget;
OS_TID t_ThdIget;
OS_TID t_ThdUSBout;
OS_TID t_ThdDISPLAYout;

os_mbx_declare(mbxBPSGOOD, 1);
os_mbx_declare(mbxV, 1);
os_mbx_declare(mbxT, 1);
os_mbx_declare(mbxI, 1);

__task void ThdSTARTUP (void) {
	void *mbxmsg;
  for (;;) {
		os_mbx_wait(mbxBPSGOOD,&mbxmsg,0xFFFF);
		CARstart();
    os_tsk_delete_self();
  }
}

__task void ThdBPScheck (void) {
	void *mbxmsg;
	uint8_t flag_start = 0;
	os_itv_set(10); /*.1 sec*/
  for (;;) {
    if(flag_start == FALSE) {
			os_mbx_wait(mbxT,&mbxmsg,0xFFFF);
			os_mbx_wait(mbxV,&mbxmsg,0xFFFF);
			os_mbx_wait(mbxI,&mbxmsg,0xFFFF);
    } //END IF
    BPScheck(); //MAIN ROUTINE THAT CHECKS IF ALL VALUES ARE IN RANGE
    if(BPS.is_good && flag_start == FALSE){
       flag_start = TRUE;			  
       os_mbx_send (&mbxBPSGOOD, &mbxmsg, 0xFFFF);
    } //END IF
    os_itv_wait();
  }
}

__task void ThdVget (void) {
	uint8_t i;
  for (;;) {
   for(i = 0; i<BPS.num_modules; i++) {
     BPS.V[i] = Vget(i);
     os_dly_wait(10);
   }
   os_mbx_send (&mbxV, NULL, 0xFFFF);
  }
}

__task void ThdTget (void) {
	uint8_t i;
  for (;;) {
   for(i = 0; i<BPS.num_modules; i++) {
     BPS.T[i] = Tget(i);
     os_dly_wait(10);
   }
   os_mbx_send (&mbxT, NULL, 0xFFFF);
  }
}

__task void ThdIget (void) {
  for (;;) {
    BPS.I = Iget();
		os_mbx_send (&mbxI, NULL, 0xFFFF);
		os_dly_wait(10);
  }
}

__task void ThdUSBout (void) {
 uint8_t flag_started = FALSE;
 printf("===============USB ONLINE ===============\n\r");
 os_itv_set(40); /*.4 sec*/
 while (TRUE) {
   uint8_t i;
   for(i = 0; i<BPS.num_modules; i++) {
     printf("V[%d]=%d\n\r",i,BPS.V[i]);
		 printf("T[%d]=%d\n\r",i,BPS.T[i]);
		 printf("I=%d\n\r",BPS.I);
     if(ERR.error != ERR_NONE){
       printf("===============BPS FAULT! ===============\n\r");
       printf("Error="); 
       switch(ERR.error){
         case    ERR_OV: printf("Over Voltage\n\r"); break;
         case    ERR_UV: printf("Under Voltage\n\r"); break;
         case    ERR_OT: printf("Over Temperature\n\r"); break;
         case    ERR_OC: printf("Over Current\n\r"); break;
         case ERR_OTHER: printf("Sensors not working\n\r"); break;
       }
       printf("Module=%d\n\r",ERR.offender_module);
       printf("V=%d\n\r",ERR.V);
       printf("T=%d\n\r",ERR.T);
       printf("I=%d\n\r",ERR.I);
     }
     if(BPS.is_started && flag_started == FALSE){
       printf("===============CAR STARTED===============\n\r");
       flag_started = TRUE;
     }
     os_itv_wait();
   }

 } // END WHILE
}

__task void ThdDISPLAYout (void) {
	os_itv_set(50); /*.5 sec*/
  for (;;) {
   DISPLAYout();
   os_itv_wait();
  }
}

__task void init (void) {
  
	BPSinit();
	
	os_mbx_init (&mbxBPSGOOD, sizeof(mbxBPSGOOD));
	os_mbx_init (&mbxV, sizeof(mbxV));
	os_mbx_init (&mbxT, sizeof(mbxT));
	os_mbx_init (&mbxI, sizeof(mbxI));
	
  t_ThdSTARTUP    = os_tsk_create (ThdSTARTUP,    0);
	t_ThdBPScheck   = os_tsk_create (ThdBPScheck,   0);
  t_ThdVget       = os_tsk_create (ThdVget,       0);
  t_ThdTget       = os_tsk_create (ThdTget,       0);
  t_ThdIget       = os_tsk_create (ThdIget,       0);
  t_ThdUSBout     = os_tsk_create (ThdUSBout,     0);
  t_ThdDISPLAYout = os_tsk_create (ThdDISPLAYout, 0);

  os_tsk_delete_self ();
}

/*----------------------------------------------------------------------------
 *        Main: Initialize and start RTX Kernel
 *---------------------------------------------------------------------------*/
int main (void) {

  SystemCoreClockUpdate();
  LED_Init ();                              /* Initialize the LEDs           */
  SER_Init ();
	adc_configure();
	init_I2C1();
	
  os_sys_init(init);                        /* Initialize RTX and start init */
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/



