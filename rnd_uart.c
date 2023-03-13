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
        
    }
}



