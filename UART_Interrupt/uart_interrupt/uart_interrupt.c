#include "pinmux.h"
#include "traps.h"
#include "platform.h"
#include "plic_driver.h"
#include "log.h"
#include "uart.h"
//This program is to send a character and receive using interrupt
//Characters are shown once every 10 times the interrupt is received 

unsigned int uart1_prev_rcv_isr_count_flag = 0;
unsigned int uart1_prev_tx_isr_count_flag = 0;

void init_variables()
{
	uart0_complete = 0;
	uart1_complete = 0;
	uart2_complete = 0;
	uart0_tx_isr_count = 0;
	uart0_rcv_isr_count = 0;
	uart1_tx_isr_count = 0;
	uart1_rcv_isr_count = 0;
	uart2_tx_isr_count = 0;
	uart2_rcv_isr_count = 0;
	memset(u0_rcv_char,'\0', UARTX_BUFFER_SIZE);
	memset(u1_rcv_char,'\0', UARTX_BUFFER_SIZE);
	memset(u2_rcv_char,'\0', UARTX_BUFFER_SIZE);
	//uart0_prev_rcv_isr_count_flag = 0;
	uart1_prev_rcv_isr_count_flag = 0;
	//uart2_prev_rcv_isr_count_flag = 0;

	//uart0_prev_tx_isr_count_flag = 0;
	uart1_prev_tx_isr_count_flag = 0;
	//uart2_prev_tx_isr_count_flag = 0;
}

/*
void configure_interrupt(uint32_t int_id)
{
	log_trace("\nconfigure_interrupt entered \n");

	
	   //Call only for GPIO pins
	 
	if(int_id >6 && int_id < 22)
	{
		configure_interrupt_pin(int_id);
	}

	interrupt_enable(int_id);

	log_trace("configure_interrupt exited \n");
}
void enable_uart_interrupts(uart_struct * instance, unsigned char interrupt)
{
	instance->ien = interrupt; 
}
*/
/*
unsigned char uart1_isr()
{
	uint32_t read_value = '\0';

	if(uart_instance[1]->status & STS_RX_THRESHOLD)
	{
		while(uart_instance[1]->status & STS_RX_NOT_EMPTY)
		{
			read_value = uart_instance[1]->rcv_reg;
			u1_rcv_char[uart1_rcv_isr_count++] = read_value;
			write_uart_character(uart_instance[1], read_value);
		}
	}
	else if(uart_instance[1]->status & STS_RX_FULL)
	{
		write_word(GPIO_DIRECTION_CNTRL_REG, RTS);
		write_word(GPIO_DATA_REG, read_word(GPIO_DATA_REG) | RTS);

		while(uart_instance[1]->status & STS_RX_NOT_EMPTY)
		{
			read_value = uart_instance[1]->rcv_reg;
			u1_rcv_char[uart1_rcv_isr_count++] = read_value;
			write_uart_character(uart_instance[1], read_value);
		}
		write_word(GPIO_DATA_REG, read_word(GPIO_DATA_REG) & ~(RTS));
	}
	else if(uart_instance[1]->status & STS_RX_NOT_EMPTY)
	{
		read_value = uart_instance[1]->rcv_reg;
		u1_rcv_char[uart1_rcv_isr_count++] = read_value;
		write_uart_character(uart_instance[1], read_value);
	}
	return 0;
}
*/


extern volatile unsigned int* pinmux_config_reg;//extern is  to increase the scope of accessing the variable


int main(void){


	register uint32_t retval;
	int i;
	init_variables();

	printf("\n---------------Uart module 1 Interrupt Test---------------\n");

	*(pinmux_config_reg) = 0x55;
	set_baud_rate(uart_instance[0], 19200);
	set_baud_rate(uart_instance[1], 19200);
	plic_init();

	configure_interrupt(PLIC_INTERRUPT_26);
	isr_table[PLIC_INTERRUPT_26] = uart1_isr;
/*
The asm keyword allows you to embed assembler instructions within C code. GCC provides two forms of inline asm statements. A basic asm statement is one with no operands (see Basic Asm), while an extended asm statement (see Extended Asm) includes one or more operands. The extended form is preferred for mixing C and assembly language within a function, but to include assembly language at top level you must use basic asm.

You can also use the asm keyword to override the assembler name for a C symbol, or to place a C variable in a specific register
*/
	// Enable Global (PLIC) interrupts.
	asm volatile("li      t0, 8\t\n"
		     "csrrs   zero, mstatus, t0\t\n"
		    );

	asm volatile("li      t0, 0x800\t\n"
		     "csrrs   zero, mie, t0\t\n"
		    );

	asm volatile(
		     "csrr %[retval], mstatus\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	printf("\n retval = %x", retval);
	asm volatile(
		     "csrr %[retval], mie\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );

	printf("\t retval = %x", retval);

	asm volatile(
		     "csrr %[retval], mip\n"
		     :
		     [retval]
		     "=r"
		     (retval)
		    );
	printf("\t retval = %x", retval);


	uart1_prev_tx_isr_count_flag = uart1_tx_isr_count;
	uart1_prev_rcv_isr_count_flag = uart1_rcv_isr_count;


	enable_uart_interrupts(uart_instance[1],  ENABLE_RX_NOT_EMPTY | ENABLE_RX_FULL);
	printf("\n Before Tx: Status Register= %x \n", uart_instance[1]->status);
	i = 0;
	write_uart_string(uart_instance[0], "\n---------------UART 1: Receiving char--------------");
	write_uart_string(uart_instance[1], "\n-----------UART 0: Transmitting characters received-----------\n");

        //UART2 Configuration:
        set_baud_rate(uart_instance[2], 19200);
        flush_uart(uart_instance[2]);
	while(1)
	{
		//sending character using UART2
                write_uart_character(uart_instance[2],'U'); 
#if 0
		if(i % 2)
			write_uart_string(uart_instance[1], "TeSt");
		else
			write_uart_string(uart_instance[1], "tEsT");
#endif
		delay_loop(2000,2000);
		if(uart1_prev_tx_isr_count_flag != uart1_tx_isr_count)
		{
			uart1_prev_tx_isr_count_flag = uart1_tx_isr_count;
		}
		if(uart1_prev_rcv_isr_count_flag != uart1_rcv_isr_count)
		{
			uart1_prev_rcv_isr_count_flag = uart1_rcv_isr_count;
		}
		if(i++ >= 10)
		{
			u1_rcv_char[++uart1_rcv_isr_count] = '\0';
//			printf("\n TxISR Count Flag: %d", uart1_tx_isr_count);
			printf("\n The characters received: %s\t Count: %d", u1_rcv_char, uart1_rcv_isr_count-1);
			i = 0;
			uart1_rcv_isr_count = 0;
			memset(u1_rcv_char,'\0', UARTX_BUFFER_SIZE);
			//break;
		}
	};


	return 0;
}

/*
Pin mapping:
UART0: J10 USB Cable
UART1: Tx= CK_IO_1
       Rx= CK_IO_0
UART2: Tx= CK_IO_3
       Rx= CK_IO_2

*/


