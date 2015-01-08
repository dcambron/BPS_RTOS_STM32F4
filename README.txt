This is a port of the BPS_RTOS originally created for Arduino Mega that is intended for the STM32F4 Discovery Board

It is a complete KEIL uVision 5 project with several files. The STM32F4 std peripheral drivers are used.The RTX RTOS is used



To DO:

Add code in function "Iget" to implement current sensing. Function currently just returns 0 current. Needs to call ADCget(pin_Isense) and convert this ADC value to a current in milliamps.

Add code in function "Vget" to implement voltage sensing. Currently returns 3200000 Startup code will need to be added in the BPSinit function to communicate with SPI. Another function will need to be written to handle charge-balancing.


Edit "BPScheck" so that the temperature limit while charging is different than the temperature limit while discharging

Edit "BPScheck" so that the voltage measured is compensated for current

Add options for DIP switches to effect operation like disabling current sensing or moving to an alternate current sensor

Add options for a user button to control things such as what the sevenseg screen shows.

Correct potential atomic code problems .... readers / writers should be mutually excluded.

Also To DO:

The ADC has not yet been set up for two ADC pins

GPIO initialization code had not been written

none of the pins in the definitions file are correct
