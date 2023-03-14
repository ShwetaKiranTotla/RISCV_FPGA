#include "uart.h"
#include "pinmux.h"
#include "traps.h"
#include "platform.h"
#include "uart.h"

//3 uart modules, uart0 starts from 11300 offset of 100
//uart are 32 bit registers
void main()
{
*(pinmux_config_reg) = 0x55;
//write_word(0x40310, 0x55);//set pinmux
//write_word(11400, 0x1b); //or set_baud_rate(uart_instance[1],115200);
}
