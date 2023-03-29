/***************************************************************************
 * Project           	       : shakti devt board
 * Name of the file	       : leds.c
 * Brief Description of file   : Control an led with the help of a button, gpio based.
 * Name of Author    	       : Kotteeswaran
 * Email ID                    : kottee.1@gmail.com

 Copyright (C) 2019  IIT Madras. All rights reserved.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
 ***************************************************************************/
/**
@file leds.c
@brief Contains the driver routines to glow LEDs.
@detail Switches ON/OFF/TOGGLE the LEDs.
*/

#include "platform.h"
#include "gpio.h" // includes definitions of gpio pins and read, write functions//
#include "led_driver.h"
#include "utils.h"

/*! Define one of the the following macros to control LEDs in different ways. */
//#define CONTROL_INDIVIDUAL_LEDS  /*! Controls LEDs Individually */
//#define CONTROL_NORMAL_LEDS /*! Control Normal LEDs only */
//#define CONTROL_RGB_LEDX /*! Controls RGB LEDs individually */
#define CONTROL_RGB_LEDS /*! controls RGB leds only */
//#define CONTROL_ALL_LEDS /*! Controls all LEDs */
//#define TOGGLE_LEDX /*! Toggles LEDs individually */
//#define TOGGLE_NORMAL_LEDX /*! Toggles Normal LEDx ONLY */
//#define TOGGLE_RGB_LEDX //!Toggles RGB leds only 
//#define TOGGLE_ALL_LEDX //Toggles all led

#define DELAY1 1000
#define DELAY2 1000

/** @fn void main()
 * @brief Performs the toggling operation  with the help of button.
 * @details Based on the uncommented macro. Performs the on/off/toggle 
 * operation on LEDS.     
 */
void main()
{
	//  write_word(GPIO_DIRECTION_CNTRL_REG, 0x0);
	//  write_word(GPIO_DATA_REG, 0x0);

#if defined(ARTIX7_35T) || defined(ARTIX7_100T)
//#if defined(PARASHU) || defined(ARTIX7_100T)

#ifdef CONTROL_INDIVIDUAL_LEDS
	configure_ledx(LED0_B);
	configure_ledx(LED0_R);
	configure_ledx(LED0_G);
	configure_ledx(LED1_B);
	configure_ledx(LED1_R);
	configure_ledx(LED1_G);
	configure_ledx(LED2);
	configure_ledx(LED3);
#endif

#ifdef  CONTROL_RGB_LEDX
	configure_rgb_ledx(RGB_LED0);
	configure_rgb_ledx(RGB_LED1);
#endif

#ifdef  CONTROL_RGB_LEDS
	configure_rgb_leds();
#endif

#ifdef  CONTROL_NORMAL_LEDS
	configure_normal_leds();
#endif

#ifdef CONTROL_ALL_LEDS
	configure_all_leds();
#endif

#ifdef TOGGLE_LEDX
	configure_ledx(LED0_B);
	configure_ledx(LED0_R);
	configure_ledx(LED0_G);
	configure_ledx(LED1_B);
	configure_ledx(LED1_R);
	configure_ledx(LED1_G);
	configure_ledx(LED2);
	configure_ledx(LED3);
#endif

#ifdef TOGGLE_NORMAL_LEDX
	configure_normal_leds();
#endif

#ifdef TOGGLE_RGB_LEDX
	configure_rgb_leds();
#endif

#ifdef TOGGLE_ALL_LEDX
	configure_all_leds();
#endif


	write_word(GPIO_DATA_REG, 0x0);

	while (1)
	{
#ifdef CONTROL_INDIVIDUAL_LEDS
		delay_loop(DELAY1, DELAY2);
		turn_on_ledx( LED0_G);
		delay_loop(DELAY1, DELAY2);
		turn_on_ledx( LED0_B);
		delay_loop(DELAY1, DELAY2);
		turn_off_ledx( LED0_R);
		delay_loop(DELAY1, DELAY2);
		turn_off_ledx( LED0_G);
		delay_loop(DELAY1, DELAY2);
		turn_off_ledx( LED0_B);
		delay_loop(DELAY1, DELAY2);

		turn_on_ledx( LED1_R);
		delay_loop(DELAY1, DELAY2);
		turn_on_ledx( LED1_G);
		delay_loop(DELAY1, DELAY2);
		turn_on_ledx( LED1_B);
		delay_loop(DELAY1, DELAY2);
		turn_off_ledx( LED1_R);
		delay_loop(DELAY1, DELAY2);
		turn_off_ledx( LED1_G);
		delay_loop(DELAY1, DELAY2);
		turn_off_ledx( LED1_B);
		delay_loop(DELAY1, DELAY2);


		turn_on_ledx( LED2);
		delay_loop(DELAY1, DELAY2);
		turn_on_ledx( LED3);
		delay_loop(DELAY1, DELAY2);
		turn_off_ledx( LED2);
		delay_loop(DELAY1, DELAY2);
		turn_off_ledx( LED3);
		delay_loop(DELAY1, DELAY2);
#endif

#ifdef CONTROL_NORMAL_LEDS
		turn_on_normal_leds();
		delay_loop(DELAY1, DELAY2);
		turn_off_normal_leds();
		delay_loop(DELAY1, DELAY2);
#endif

#if 0
#ifdef CONTROL_RGB_LEDX
		turn_on_rgb_ledx( RGB_LED0);
		turn_on_rgb_ledx( RGB_LED1);
		delay_loop(DELAY1, DELAY2);
		turn_off_rgb_ledx( RGB_LED0);
		turn_off_rgb_ledx( RGB_LED1);
		delay_loop(DELAY1, DELAY2);
#endif
#endif
#ifdef CONTROL_RGB_LEDX
		turn_on_rgb_ledx( RGB_LED0);
		turn_off_rgb_ledx( RGB_LED1);
		delay_loop(DELAY1, DELAY2);
		turn_off_rgb_ledx( RGB_LED0);
		turn_on_rgb_ledx( RGB_LED1);
		delay_loop(DELAY1, DELAY2);
#endif

#ifdef CONTROL_RGB_LEDS
		turn_on_rgb_leds();
		delay_loop(DELAY1, DELAY2);
		turn_off_rgb_leds();
		delay_loop(DELAY1, DELAY2);
#endif


#ifdef CONTROL_ALL_LEDS
		turn_on_all_leds();
		delay_loop(DELAY1, DELAY2);
		turn_off_all_leds();
		delay_loop(DELAY1, DELAY2);
		//  ToggleAllLeds(1000);
#endif


#ifdef TOGGLE_LEDX
		toggle_ledx(LED0_R, DELAY1, DELAY2);
		toggle_ledx(LED0_G, DELAY1, DELAY2);
		toggle_ledx(LED0_B, DELAY1, DELAY2);
		toggle_ledx(LED1_R, DELAY1, DELAY2);
		toggle_ledx(LED1_G, DELAY1, DELAY2);
		toggle_ledx(LED1_B, DELAY1, DELAY2);
		toggle_ledx(LED2, DELAY1, DELAY2);
		toggle_ledx(LED3, DELAY1, DELAY2);
#endif

#ifdef TOGGLE_NORMAL_LEDX
		toggle_normal_leds(DELAY1, DELAY2);
#endif

#ifdef TOGGLE_RGB_LEDX
		toggle_rgb_leds(DELAY1, DELAY2);
#endif

#ifdef TOGGLE_ALL_LEDX
		toggle_all_leds(DELAY1, DELAY2);
#endif
	}
#endif
}
