#include "platform.h"
#include "utils.h" 
#include "gpio.h" 


void togglegpio()
{
//Assumption 1 ---> output, 0 ---> input
	write_word(GPIO_DIRECTION_CNTRL_REG, 0xFFFFEFFF); //GPIO0 to 23-> output

	while (1) {
	//unsigned int var;
	//printf("Enter 32 bit value in Hexadecimal: ");	
	//scanf("%x", &var);
	//write_word(GPIO_DATA_REG, var);
	//write_word(GPIO_DATA_REG, val);
	
	write_word(GPIO_DATA_REG, 0x08001000);	
	delay_loop(1000, 5000);
	write_word(GPIO_DATA_REG, 0xFFFFFFFF);
	delay_loop(1000, 5000);
	}
}

/*int decToBinary(short n,char a1[])
{
    // array to store binary number
    int binaryNum[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 
    // counter for binary array
    int i = 0;
    while (n > 0) {
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    int k=0;
    // printing binary array in reverse order
    for (int j = 15; j >= 0; j--)
       
       { //printf("%d", binaryNum[j]);
       a1[k++]=binaryNum[j];
       }
       
    return 0; 

int merge_words(char d[], char f[], char final[])
{
	for(int i=0;i<32;i++)
   {
       if(i<16)
       final[i]= d[i];
       else
       final[i]= f[i-16];
   }
	return 0;
}

int binarytodecimal(char a[])
{
    int base = 1;
    int dec_value = 0;
    for(int i=31;i>=0;i--)
    {dec_value += a[i] * base;
 
        base = base * 2;
    }
    //printf("%d",dec_value);
    return dec_value;
}


/*
	***** set_f_n takes frequency values in "KHz" (upto 1.52 KHz) and duty cycle in percentage (0-100) ***** 
*/
/*
void set_f_n_d(int freq, int duty)
{
	short cmp_val;
	char c_val[16];
	short max_val;
	char m_val[16];
	
	char merged[32];
	unsigned int final;

	max_val = 100000/freq;
	cmp_val = 0.01*duty*max_val;

	int temp = decToBinary(cmp_val, c_val);
	int temp1 = decToBinary(max_val, m_val);	
	int temp2 = merge_words(c_val, m_val, merged);
	final = binarytodecimal(merged);

	write_word(GPIO_DIRECTION_CNTRL_REG, 0xFFFFFFFF); //GPIO0 to 23-> output
	
	while(1){
	write_word(GPIO_DATA_REG, final);
	delay_loop(1000, 5000);
	write_word(GPIO_DATA_REG, 0xFFFFFFFF);
	delay_loop(1000, 5000);
	}
}
*/
void main()
{	
	togglegpio();
	//set_f_n_d(2500, 50);
	
	return 0;
}
