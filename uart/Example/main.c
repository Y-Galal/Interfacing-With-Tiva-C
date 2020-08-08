

/**
 * main.c
 * example to interface with pc using UART0
 */
#include "uart0.h"
#include "GPIO.h"
#include "app.h"

void delay()
{
    uint32 i =0;
    for(i=0;i<=180000;i++)
    {
        continue;
    }
}

struct Info myInfo;

int main(void)
{
    UART_init(16000000,115200);
    uint8 request;
    uint8 message1[]="Enter Your Name";
    uint8 message2[]="Enter Your Age";
    uint8 message3[]="Enter Your Gender";
    uint8 message4[]="Enter Your Weight";
    uint8 message5[]="Enter Your Height";
    uint8 message6[]="Data is saved successfully!";
    uint8 message7[]="Press [N]ame [A]ge [G]ender [W]eight [H]eight [I]nfo";
    uint8 message9[]="Your Name is: ";
    uint8 message10[]="Your Age is: ";
    uint8 message11[]="Your Gender is: ";
    uint8 message12[]="Your Weight is:";
    uint8 message13[]="Your Height is:";
    uint8 message14[]="Wrong input";
    UART_sendString(message1);
    UART_receiveString(myInfo.s_name);
    UART_sendString(message2);
    UART_receiveString(myInfo.s_age);
    UART_sendString(message3);
    UART_receiveString(myInfo.s_gender);
    UART_sendString(message4);
    UART_receiveString(myInfo.s_weight);
    UART_sendString(message5);
    UART_receiveString(myInfo.s_height);
    UART_sendString(message6);


    while(1)
    {
        UART_sendString(message7);
        request = UART_receiveByte();
        switch(request)
        {
            case 'n':
                UART_sendString(message9);
                UART_sendString(myInfo.s_name);
                break;
            case 'a':
                UART_sendString(message10);
                UART_sendString(myInfo.s_age);
                break;
            case 'g':
                UART_sendString(message11);
                UART_sendString(myInfo.s_gender);
                break;
            case 'w':
                UART_sendString(message12);
                UART_sendString(myInfo.s_weight);
                break;
            case 'h':
                UART_sendString(message13);
                UART_sendString(myInfo.s_height);
                break;
            case 'i':
                UART_sendString(message9);
                UART_sendString(myInfo.s_name);
                UART_sendString(message10);
                UART_sendString(myInfo.s_age);
                UART_sendString(message11);
                UART_sendString(myInfo.s_gender);
                UART_sendString(message12);
                UART_sendString(myInfo.s_weight);
                UART_sendString(message13);
                UART_sendString(myInfo.s_height);
                break;
            default:
                UART_sendString(message14);
                break;
        }
    }
	return 0;
}
