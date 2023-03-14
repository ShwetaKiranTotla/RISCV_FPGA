//led code for blinking
#include "platform.h"
#include "utils.h" 
#include "gpio.h" 

void led_blinking()
{
//1 is output
	write_word(GPIO_DIRECTION_CNTRL_REG, 0x00FFFFFF); //GPIO0 to 23 set as output

	while (1) {
	write_word(GPIO_DATA_REG, 0x000F0000);//GPIO16 to 19 on board LED set as 1
	delay_loop(1000,3000);// call delay	
	write_word(GPIO_DATA_REG, 0x00);// GPIO0 to 23 set as low
	delay_loop(1000,3000);//call delay
	}
}

void main()
{
	led_blinking();
	return 0;
}
