# Shakti
The board used is Xilinx Arty 7 100T (Parashu)
##Resources
Has documents which can be referred to for pin mapping, register addresses, etc.
## LED GPIO
This code blinks all the on board LEDs.
## UART
Sends and receives charaters using on board UART modules.  
UART0 is connected to JTAG and reception/transmission can be done either by a C code or by directly writing/reading values from an address using GDB.  
Reference for UART0 programming: https://blogshakti.org.in/shakti-uart/  
UART1 and UART2 are on board modules. In order to enable both the modules set the pinmux to 0x55.  
Reference for pinmux: https://blogshakti.org.in/pinmux-in-shakti/  
After enabling these modules using pinmux in the UART C program (rnd_uart.c), rx1, tx1, rx2, tx1 values are available at io[0], io[1], io[2], and io[3] respectively.  

## UART_Interrupt
Sends and receives charaters using on board UART modules using interrupt.
## XADC
Uses 6 on board single ended ADC channels.  
Single ended channel pins and addresses are as follows:  
Channel 1 on Pin A5, read value at 0x41240.  
Channel 2 on Pin A0, read value at 0x41250.  
Channel 3 on Pin A1, read value at 0x41254.  
Channel 4 on Pin A2, read value at 0x41258.  
Channel 5 on Pin A3, read value at 0x4125c.  
Channel 6 on Pin A4, read value at 0x4127c.  

## XDC Files
Contains constraints file for Xilinx Artix 7 100T and Shakti Microprocessor.
## Verilog
Code to define a register that generates pwm signals on GPIO Pin.
#
fpga_top.bit is the bitstream of the Shakti module.
##
MAKEFILE is the makefile for the overall shakti-sdk toolchain.
