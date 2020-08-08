/*
*   File name: GPIO.C
*   Created By: Youssef Galal
*   Description: Interfacing with I/O ports with different modes in Tiva C board
*   Created On: 19-7-2020
*/

#include "GPIO.h" /* including the header file*/

/*          Private Functions           */


/* Function Name: getNumber
*  Fucntion description: gets the port and returns the corresponding number 
*  This is needed for RCGCGPIO register 
*/
static uint8 getNumber (const uint32 * Port) 
{

    switch(*Port)
    {
        case PORTA :
            return BIT0;
            break;
        case PORTB :
            return BIT1;
            break;
        case PORTC :
            return BIT2;
            break;
        case PORTD :
            return BIT3;
            break;
        case PORTE :
            return BIT4;
            break;
        case PORTF :
            return BIT5;
            break;
        default :
            return -1;
            break;
    }

    return 0;
}

/* Function Name: enableClock
*  Fucntion description: gets the required port and enables the clock for this port 
*  
*/
static void enableClock(const uint32 *Port)
{
    SET_BIT(SYSTEM_CONTROL,RCGCGPIO,getNumber(Port));   /* Enabling clock for the required Port */
    asm(" NOP");                                        /* Assembly code to waste 3 clock cycles*/           
    asm(" NOP");
    asm(" NOP");
    return ;
}

/* Function Name: unlockPort
*  Fucntion description: gets the port and the pin then unlocks the port  
*  to access GPIOCR register
*/
static void unlockPort(uint32 Port,uint8 Pin)
{
    
    ACCESS_REG(Port,GPIOLOCK) = UNLOCK_REG ; // write unlock key to GPIOLOCK register
    SET_BIT(Port,GPIOCR,Pin);

   return ;
}

/* Function Name: lockPort
*  Fucntion description: Locks the port by writing any 
*  value to the GPIOLOCK register  
*/
static void lockPort(uint32 Port)
{
   ACCESS_REG(Port,GPIOLOCK) = LOCK_REG; 
   return ;
}

/* Function Name: setDriveType
*  Fucntion description: gets the port, the pin and the required drive type then
*  sets the drive needed (PULL_UP, PULL_DOWN, OPEN_DRAIN) 
*/
static void setDriveType(uint32 Port,uint8 Drive, uint32 Pin)
{
    switch(Drive)   
    {
        case PULL_UP:
            SET_BIT(Port,GPIOPUR,Pin); 
            break;
        case PULL_DOWN:
            SET_BIT(Port,GPIOPDR,Pin); 
            break;
        case OPEN_DRAIN:
            SET_BIT(Port,GPIOODR,Pin);  
            break;                                    
        default:
            break;
    }
}

/* Function Name: setCurrent
*  Fucntion description: gets the port, the pin and the required drive current  
*  and sets it (2-mA,4-mA,8-mA)
*/
static void setCurrent( uint32 Port , uint8 Current ,uint32 Pin)
{
    switch(Current)
    {
        case TWO :
            SET_BIT(Port,GPIODR2R,Pin); 
            break;
        case FOUR :
            SET_BIT(Port,GPIODR4R,Pin); 
            break;
        case EIGHT :
            SET_BIT(Port,GPIODR8R,Pin);  
            break;                                    
        default:
            break;        
    }
    return ;
}



/*************************************************************************/
/*                            Public Functions                           */
/*************************************************************************/

/* Function Name: GPIO_configureDigitalPin
*  Fucntion description: Takes the required configuration and sets it  
*                        required configurations:
*                                   Port - Pin - Type(I/O) - Drive - Current
*/
void GPIO_configureDigitalPin(const PIN_CONFIG *config)
{
    /* 1- Enable clock to the port*/
    
    enableClock(&(config->Port));

    /* 2- Unlocking the Port */
    unlockPort(config->Port,config->Pin);

    /* 3- The pin becomes a GPIO pin*/
    CLEAR_BIT( config-> Port , GPIOAFSEL , config -> Pin ); /* The pin is GPIO pin */
    CLEAR_BIT( config-> Port , GPIOAMSEL , config -> Pin ); /* Enable analog isolation */

    /* 4- setting the pin (input or output) */
    if( (config->Type) == OUTPUT)
    {
    SET_BIT( config-> Port , GPIODIR , config -> Pin ); /* Set the corresponding bit to make the pin as an Output pin */
    }
    else
    {
    CLEAR_BIT( config-> Port , GPIODIR , config -> Pin ); /* clear the corresponding bit to make the pin as an Input pin*/
    }
    
    /* 5- Setting the current strength */
    setCurrent( config->Port, config->Current ,config->Pin);

    /* 6-Setting the drive type of the pin (internal pull up - pull down - open drain)*/
    setDriveType(config->Port, config->Drive ,config->Pin);

    /* 7- Digital Enable*/
    SET_BIT( config->Port , GPIODEN , config -> Pin ) ;

    /* 8- Locking the port again */
    //lockPort(config -> Port);
}


/* Function Name: GPIO_writeData
*  Fucntion description: Takes the port, the pin and the data to write it   
*  
*/
void GPIO_writeData(uint32 Port, uint32 Pin,uint8 data)
{
    if (data == HIGH)
    {
        SET_BIT(Port,GPIODATA,Pin);
    }
    else
    {
        CLEAR_BIT(Port,GPIODATA,Pin);
    }
}

/* Function Name: GPIO_readData
*  Fucntion description: Takes the port and the pin to read the required pin   
*  
*/
uint8 GPIO_readData(uint32 Port, uint32 Pin)
{
    return ( BIT_IS_SET(Port,GPIODATA,Pin) );
}





