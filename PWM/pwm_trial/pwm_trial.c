#include "pwm_driver.h"
#include "pinmux.h"

/** @fn int main()
 * @brief main function that runs the code
 * @return zero
 */
int main()
{
	/**we need to set the period, duty cycle and the clock divisor in order
	 *to set it to the frequency required. Base clock is 50MHz
	 **/

	//Configuring PWM0

    //int module_number=PWM_0;
    int module_number=0;

    volatile short* period_value;
	period_value = (int*) (PWM_BASE_ADDRESS + module_number*PWM_MODULE_OFFSET + PERIOD_REGISTER);
	*period_value = 0xf0;

    volatile short* clock_value;
    clock_value = PWM_BASE_ADDRESS + module_number*PWM_MODULE_OFFSET + CLOCK_REGISTER;
	*clock_value = 0xf000;

    volatile short* duty_value;
	duty_value = PWM_BASE_ADDRESS + module_number*PWM_MODULE_OFFSET + DUTY_REGISTER;
	*duty_value = 0x80;

	//configuring PWM Mode

        int value = 0x0;
		value += PWM_ENABLE;
		value += PWM_START;
		value += PWM_OUTPUT_ENABLE;

		volatile char* control_value;
		control_value = PWM_BASE_ADDRESS + module_number*PWM_MODULE_OFFSET + CONTROL_REGISTER;
		*control_value = value;



	//pwm_configure(PWM_0, 0xf000, 0xf0, 0x80, false);
    *pinmux_config_reg = 0x80;
		
	/*This function starts the PWM in the specified mode*/
	//pwm_start(PWM_0,0);
	return 0;
}

/*
void pwm_configure(int module_number,int clock_divisor, int period, int duty, bool external_clock)
{
	pwm_set_periodic_cycle(module_number, period);
	pwm_set_duty_cycle(module_number, duty);
	pwm_set_clock(module_number, clock_divisor);
	pwm_use_external_clock(module_number, external_clock);
	log_info("\nPWM %d succesfully configured",module_number);
}
*/