/*
*   File name: uart.c
*   Created By: Youssef Galal
*   Description: source file for uart0 to communicate with pc
*   Created On: 5-8-2020
*/


#include "uart0.h"

/* Function Name: UART_init
*  Fucntion description: Function that initializes UART0 
*  Input: the selected system clock and baudrate 
*  
*/
void UART_init(uint32 clock , uint32 baudrate)
{
    float32 fraction;

    SET_BIT(SYSTEM_CONTROL,RCGCUART,BIT0); /*enable uart0*/

    SET_BIT(SYSTEM_CONTROL,RCGCGPIO,BIT0);  /*give clock to PORTA*/


    ACCESS_REG(PORTA,GPIOLOCK) = UNLOCK_REG ; // write unlock key to GPIOLOCK register
    SET_BIT(PORTA,GPIOCR,PIN0);
    SET_BIT(PORTA,GPIOCR,PIN1);

    SET_BIT(PORTA,GPIODEN,PIN0);
    SET_BIT(PORTA,GPIODEN,PIN1);

    SET_BIT(PORTA,GPIOAFSEL,PIN0);  /*Choosing alternate function for pin0*/
    SET_BIT(PORTA,GPIOAFSEL,PIN1);  /*Choosing alternate function for pin1*/

    SET_BIT(PORTA,GPIOPCTL,BIT4);   /*Enabling UART0*/
    SET_BIT(PORTA,GPIOPCTL,BIT0);

    CLEAR_BIT(UART0,UART_CTL,BIT0) ;    /*UARTEN is 0 to adjust the baudrate*/
    
    fraction = (clock/(float32)(16*baudrate))-(uint32)(clock/(16*baudrate));    /*setting the baudrate needed*/
    ACCESS_REG(UART0,UART_IBRD) = (uint32)(clock/(16*baudrate));
    ACCESS_REG(UART0,UART_FBRD) = (uint32)(fraction *64 +0.5);

    ACCESS_REG(UART0,UART_CTL) |= (ACCESS_REG(UART0,UART_CTL) | 0x0301) ; /*RXE-> receive enable, TXE transmit enable, UARTEN uart enable*/
    ACCESS_REG(UART0,UART_LCRH) |= (ACCESS_REG(UART0,UART_LCRH) | 0x70 ); /*  WLEN1,0 = 1 "8 bits data" - FEN =1 FIFO enabled */


}

/* Function Name: UART_sendByte
*  Fucntion description: function that Transmitts 1 byte 
*  
*/
void UART_sendByte(const uint8 data)
{
    while( (BIT_IS_SET(UART0,UART_FR,TXFF)) != 0 ){}       /*staying in loop while the TXFF=1 and the FIFO is full*/
    ACCESS_REG(UART0,UART_DR) = data;
}

/* Function Name: UART_receiveByte
*  Fucntion description: function that returns the value(1 Byte) received from pc
*   
*/
uint8 UART_receiveByte(void)
{
    while( (BIT_IS_SET(UART0,UART_FR,RXFE)) !=0 ){}       /*staying in loop while RXFF=1 and the FIFO is full*/

    return ( (uint8)(ACCESS_REG(UART0,UART_DR) & 0xFF ));   /*the receiver can receive data now*/
}

/* Function Name: UART_sendString
*  Fucntion description: Sends a string 
*/
void UART_sendString(const char *Str)
{
    uint8 i = 0;
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
	UART_sendByte('\r');
	UART_sendByte('\n');
}

/* Function Name: UART_receiveString
*  Fucntion description: Receives a string 
*  
*/
void UART_receiveString(uint8 *Str)
{
    uint8 i = 0;
	Str[i] = UART_receiveByte();
	UART_sendByte(Str[i]);
	while(Str[i] != '\r')
	{
		i++;
		Str[i] = UART_receiveByte();
	    UART_sendByte(Str[i]);

	}
	Str[i] = '\0';
	UART_sendByte('\n');
}

/* Function Name: UART_sendNumber
*  Fucntion description: Sends a number by converting its digits into a string
*  
*/
void UART_sendNumber(uint16 out)
{

        uint8 c[10] = {0} ;
        uint8 m;
        sint8 i = 0 ;

        if(out == 0)
        {
            c[0] = 48;
            i = 0 ;
        }
        while(out)
        {
            m = out%10;
            c[i++] = m + 48;
            out = out/10;
        }
        while(i != -1)
        {
            UART_sendByte(c[i--]);
        }
        UART_sendByte('\r');
        UART_sendByte('\n');
}
