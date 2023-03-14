/*//Tanish's code:
#include "uart.h"
#include "string.h"
#include <stdint.h>
#include "platform.h"
#include "pinmux.h"
#include "traps.h"
#include <stdio.h>
#include "log.h"
#include "utils.h" 
#include "gpio.h" 
//might wanna remove unnecessary header files later

int putchar_1(int ch)//function to send a character to the output device via UART_1
{
	while(uart_instance[1]->status & STS_TX_FULL);

	uart_instance[1]->tx_reg = ch;

	return 0;
}

void main()
{	
	uart_init();//initialising uart modules
	*(pinmux_config_reg) = 0x55;//pinmux set to use both UART1 and UART2
	printf("\n Checking\n");
	char input_ch;


        putchar_1('U');//U=10101010
	set_baud_rate(uart_instance[1],9600);
//Interrupt required?
	//write_uart_character(uart_instance[1], 'q');//sending character..check if req
        flush_uart(uart_instance[1]);

	//printf("\n Checking UART input, loopback\n");
	//read_uart_character(uart_instance[1], &tx_reg);
	//printf("\n Reading Complete \n");
	
}
*/


//Shweta's code:
/*
#include "uart.h"
#include <stdint.h>
#include "platform.h"
#include "pinmux.h"
#include "traps.h"
#include <stdio.h>
#include <utils.h>

void main()
{	
	*(pinmux_config_reg) = 0x55;//pinmux set to use both UART1 and UART2
	printf("\n Checking\n");
	char input_ch;	
	set_baud_rate(uart_instance[1],19200);
	write_uart_character(uart_instance[1], 'q');
	//printf("\n Checking UART input, loopback\n");
	//read_uart_character(uart_instance[1], &tx_reg);
	//printf("\n Reading Complete \n");
	
//why does the uart.c file have uart_instance[0] and not uart_instance[1/2]?
}
	
*/


#include "uart.h"
#include <stdint.h>
#include "platform.h"
#include "pinmux.h"
#include "traps.h"
#include <stdio.h>
#include <utils.h>
void main()
{
    *pinmux_config_reg=0x55;
    uart_init();
    set_baud_rate(uart_instance[1], 9600);
    printf("Test uart !\r\n");
    flush_uart(uart_instance[1]);


    while(1){
        // uint8_t result;
        char temp1;
        write_uart_character(uart_instance[1], 10);
        
            read_uart_character(uart_instance[1], &temp1);
            printf("rec %d\n", temp1);
        

       // printf(" - - - - - - - - - - - - - - \n");
        //delay(2);
    }
}
/*
#include <string.h>
#include "uart.h"
#include "pinmux.h"
#include "i2c.h"
#include "log.h"

#define BAUDRATE 9600


int read_from_lora(char *data)
{
	int ch;
	char *str = data;
	char *test = data;
	for (int i = 0; i < 9; i++)
	{
		read_uart_character(uart_instance[1], &ch);
		*str = ch;
		str++;
		if (ch == '\n')
		{
			break;
		}
	}
	return;	
}

*/


