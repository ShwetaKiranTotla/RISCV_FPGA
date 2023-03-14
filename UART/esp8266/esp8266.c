/***************************************************************************
* Project           			:  shakti devt board
* Name of the file	     		:  weatherstation.c
* Brief Description of file     :  A sample project to demonstrate 
					   integration of temperature sensor 
                                           and transmission of data to a website
* Name of Author    	        :  Anand Kumar S
* Email ID                      :  007334@imail.iitm.ac.in

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
  * @file weatherstation.c
  * @brief sample project using temperature sensor and esp8266
  * @details Sample project to demonstrate integration of temperature sensor and
  * transmission of data to a website.
  * LM75 sensor is used to collect ambient temperature, ESP8266 module is  used to
  * send data to thingspeak.com
  * Prerequisite:

  * 1. ESP8266 is configured to baud rate 115200
  * 2. ESP8266 is set in station mode
  * 3. ESP8266 is configured to connect to access point.
  * 4. A channel to receive data is configured in thingspeak.com
  * 5. Change the API_key in the weatherstation.c

*/

#include "uart.h" //Includes the definitions of uart communication protocol//
#include "string.h"
#include "pinmux.h"
//#include "i2c.h"
#include "log.h"
//#include "bmp280.h"
#include "platform.h"
#include "utils.h" 
#include "gpio.h" 

// Replace the API KEY
#define API_KEY "G6VZUKSKB8L2XI7V"

// UART 1 to communicate to ESP8266
#define ESP_UART uart_instance[1]

// Using I2C 1 to connect to BMP280
//#define I2C i2c_instance[1]

/**
  * @fn int write_to_esp8266(char *data,uart_num sel,int baudrate)
  * @brief sends data to esp8266 using UART
  * @param data data that has to be sent to could
  * @param sel Uart that is connected to esp8266
  * @param baudrate Baudrate that is used to communicate with esp8266
*/

int write_to_esp8266(char *data)
{
	while (*data != '\0')
	{
		write_uart_character(ESP_UART, *data);
		data++;
	}
	write_uart_character(ESP_UART, '\r');
	write_uart_character(ESP_UART, '\n');
}

/**
  * @fn int write_to_esp8266(char *data,uart_num sel,int baudrate)
  * @brief sends carriage return and new line charector to esp8266
  * @detail sends carriage return and new line charector to esp8266
  *         this method is neeed to indicate end to data transmission
  * @param data data that has to be sent to could
  * @param sel Uart that is connected to esp8266
  * @param baudrate Baudrate that is used to communicate with esp8266
*/

int write_enter_to_esp8266()
{
	write_uart_character(ESP_UART, '\r');
	write_uart_character(ESP_UART, '\n');
}

/**
  * @fn int read_from_esp8266(char *data,uart_num sel,int baudrate)
  * @brief Reads data sent by esp8266
  * @details Reads data sent by esp8266 until one of the key word is found
  * @param data responses read from esp8266, mainly used for logging
  * @param sel Uart that is connected to esp8266
  * @param baudrate Baudrate that is used to communicate with esp8266
*/
int read_from_esp8266(char *data)
{
	int ch;
	char *str = data;
	char *test = data;
	for (int i = 0; i < 198; i++)
	{
		read_uart_character(ESP_UART, &ch);
		*str = ch;
		str++;
		*str = '\0';
		if (strstr(test, "OK") != NULL)
		{
			log_debug("read from esp8266 %s\n", test);
			return;
		}
		if (strstr(test, "ERROR") != NULL)
		{
			log_debug("read from esp8266 %s\n", test);
			return;
		}
		if (strstr(test, ">") != NULL)
		{
			log_debug("read from esp8266 %s\n", test);
			return;
		}
		if (strstr(test, "RECV") != NULL)
		{
			log_debug("read from esp8266 %s\n", test);
			return;
		}
		if (strstr(test, "IP") != NULL)
		{
			log_debug("read from esp8266 %s\n", test);
			return;
		}
	}
	*str = '\0';
	return 1;
}

/**
  * @fn void setup_esp8266()
  * @brief setup MUX mode in  esp8266
  * @details setup MUX mode in  esp8266
*/
void setup_esp8266()
{
	char data[200];
	write_to_esp8266("AT");
	delay_loop(1000, 1000);
	read_from_esp8266(data);
	printf("%s \n",data);
	printf("sending AT Echo off command to esp\n");
	write_to_esp8266("ATE0");
	delay_loop(50, 50);
	read_from_esp8266(data);
	printf("%s \n",data);
	printf("write AT+CIPMUX\n");
	write_to_esp8266("AT+CIPMUX=0");
	delay_loop(50, 50);
	read_from_esp8266(data);
	printf("%s \n",data);
	
	// Steps for connecting to wifi //
	
	write_to_esp8266("AT+RST");
	read_from_esp8266(data);
	printf("%s \n",data);
	write_to_esp8266("AT+CWMODE=1");
	read_from_esp8266(data);
	printf("%s \n",data);
	//write_to_esp8266("AT+CWLAP=3,\"Device\"");
		//read_from_esp8266(data);
		//write_to_esp8266("AT+CWLAP=\"Wi-Fi\"");
	//read_from_esp8266(data);
	//printf("%s \n",data);
	//write_to_esp8266("AT+CWJAP=\"mandar\",\"mandar12\"");
	write_to_esp8266("AT+CWJAP=\"chirag\",\"wifipassword\"");
	read_from_esp8266(data);
	printf("%s \n",data);
	write_to_esp8266("AT+CIFSR");
	read_from_esp8266(data);
	printf("%s \n",data);
	write_to_esp8266("ATE0");
	read_from_esp8266(data);
	printf("%s \n",data);
	write_to_esp8266("AT+CIPMUX=0");
	read_from_esp8266(data);
	printf("%s \n",data);
	
}
/**
  * @fn void transmit_data(int temperature, int baudrate)
  * @brief formats AT commands  to be sent to esp8266
  * @details formats the data in AT commands and sends to esp8266 in  sequence
  *      Open connection to server (thingspeak.com in this example)
  *      Send data to the server 
  *      Close connection
  * @param temperature temperate that has to be sent to database in cloud
  * @param baudrate baudrate used to communicate with esp8266
*/
void transmit_data(char *Data)
{
	char data[200];
	char sendData[93];
	char CIPSEND[15];
	int length;
	int a = (int) Data;
	sprintf(sendData, "GET https://api.thingspeak.com/update?api_key=%s&field1=0",API_KEY);	
	length = strlen(sendData);
	length = length + 2;
	printf("%d",length);
	printf(CIPSEND, "AT+CIPSEND=%d", length);
	// Connect to Wifi using esp8266

	// Connect to Wifi using esp8266
	printf("\n Open connection to thingspeak.com\n");
	printf("\n sending  %s\n", sendData);
	flush_uart(ESP_UART);
	write_to_esp8266("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
	read_from_esp8266(data);                                            // Stuck at this line
	printf(" data from esp :%s\n",data);
													
	//delay_loop(2000,2000);
	printf("\n%s\n", CIPSEND);
	flush_uart(ESP_UART);
	write_to_esp8266(CIPSEND);
	read_from_esp8266(data);
	printf(" data from esp :%s\n",data);

	printf(" write Data\n");
	flush_uart(ESP_UART);
	write_to_esp8266(sendData);

	//flush_uart(ESP_UART);
	write_enter_to_esp8266();
	//delay(100,100);
	read_from_esp8266(data);
	printf(" data from esp :%s\n",data);
	// disconnect from link
	printf(" write AT+CIPCLOSE\n");
	flush_uart(ESP_UART);
	write_to_esp8266("AT+CIPCLOSE");
	read_from_esp8266(data);
}

void transmit_Data(char *Data1)
{
	char data[200];
	char sendData[93];
	char CIPSEND[15];
	int length;
	int a = (int) Data1;
	sprintf(sendData, "GET https://api.thingspeak.com/update?api_key=%s&field4=2",API_KEY);
		
	length = strlen(sendData);
	length = length + 2;
	printf("%d",length);
	printf(CIPSEND, "AT+CIPSEND=%d", length);
	// Connect to Wifi using esp8266

	// Connect to Wifi using esp8266
	printf("\n Open connection to thingspeak.com\n");
	printf("\n sending  %s\n", sendData);
	flush_uart(ESP_UART);
	write_to_esp8266("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
	read_from_esp8266(data);                                            // Stuck at this line
	printf(" data from esp :%s\n",data);
													
	//delay_loop(2000,2000);
	printf("\n%s\n", CIPSEND);
	flush_uart(ESP_UART);
	write_to_esp8266(CIPSEND);
	read_from_esp8266(data);
	printf(" data from esp :%s\n",data);

	printf(" write Data\n");
	flush_uart(ESP_UART);
	write_to_esp8266(sendData);

	//flush_uart(ESP_UART);
	write_enter_to_esp8266();
	//delay(100,100);
	read_from_esp8266(data);
	printf(" data from esp :%s\n",data);
	// disconnect from link
	printf(" write AT+CIPCLOSE\n");
	flush_uart(ESP_UART);
	write_to_esp8266("AT+CIPCLOSE");
	read_from_esp8266(data);
}

void togglegpio()
{
//Assumption 1 ---> output, 0 ---> input
	write_word(GPIO_DIRECTION_CNTRL_REG, 0xFFFFFFFF); //GPIO0 to 23-> output

	while (1) {
	//unsigned int var;
	//printf("Enter 32 bit value in Hexadecimal: ");	
	//scanf("%x", &var);
	//write_word(GPIO_DATA_REG, var);
	//write_word(GPIO_DATA_REG, val);
	
	write_word(GPIO_DATA_REG, 0x0E661000);
	delay_loop(1000, 5000);
	write_word(GPIO_DATA_REG, 0x04002000);
	delay_loop(1000, 5000);
	}
}



void receive_data(){
	unsigned long a = 0;
	write_word(GPIO_DIRECTION_CNTRL_REG, 0x00000000); //GPIO0 to 23-> output
	a =read_word(GPIO_DATA_REG) & GPIO12;
	if(a){
		togglegpio();
}

	char receiveData[93];
	char data1[] = "Mandar";
	sprintf(receiveData, "GET https://api.thingspeak.com/channels/1885967/fields/3.json?api_key=R0UV0SXG8YBJQ88F&results=2");
	printf("%s",receiveData);

	if(receiveData == 1){
	transmit_Data(data1);
	
	}
}

/**
  * @fn void main()
  * @brief Entry point for the program
*/
void main()
{
	write_word(GPIO_DIRECTION_CNTRL_REG, 0xFFFFFFFF);
	write_word(GPIO_DATA_REG, 0xFFFFFFFF);
	//delay_loop(1000, 5000);

	int baudrate = 115200;
	char data[] = "Mandar";

	printf("\n setting PIN MUX config to 2 .... \n");
	*pinmux_config_reg = 0x5;
	printf("\n set PIN MUX config to 2 .... \n");
	set_baud_rate(ESP_UART, baudrate);
	printf("\n Sending data to cloud server!....\n");
	printf("\n Baud rate set to %d \n", baudrate);
	printf("\n Waiting to ESP8266 to initialize \n");
	delay_loop(1000, 1000);
	//setup_esp8266();
	//transmit_data(data);
	receive_data();
	while(1);
}

