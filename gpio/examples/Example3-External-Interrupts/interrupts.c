#include "interrupts.h"

volatile void (*PORTACallBackFunction)(void) = NULL ;       /*Pointer to function that used to set the call back function*/
volatile void (*PORTBCallBackFunction)(void) = NULL ;
volatile void (*PORTCCallBackFunction)(void) = NULL ;
volatile void (*PORTDCallBackFunction)(void) = NULL ;
volatile void (*PORTECallBackFunction)(void) = NULL ;
volatile void (*PORTFCallBackFunction)(void) = NULL ;


/************************** Private Functions ******************************/

/* Function Name: processorEnableInterrupt
*  Fucntion description: enables the interrupt using an assembly instruction
*/
static void processorEnableInterrupt()      
{
    asm(" CPSIE i");            /*Assembly instruction to enable interrupts "Change Processor State Interrupt Enable"*/
}

/* Function Name: processorDisableInterrupt
*  Fucntion description: disables the interrupt using an assembly instruction
*/
static void processorDisableInterrupt()
{
    asm(" CPSID i");             /*Assembly instruction to disable interrupts "Change Processor State Interrupt Disable"*/
}

/* Function Name: setInterruptType
*  Fucntion description: sets the interrupt type to detect 
*  rising edge,falling edge,both,high level,low level
*/
static void setInterruptType(const INTERRUPT *Interrupt)
{
    switch(Interrupt->Type)
    {
        case HIGH_RISING :
                CLEAR_BIT(Interrupt->Port,GPIOIBE,Interrupt->Pin); 
                SET_BIT(Interrupt->Port,GPIOIEV,Interrupt->Pin);
            break;
        case LOW_FALLING :
                CLEAR_BIT(Interrupt->Port,GPIOIBE,Interrupt->Pin);
                CLEAR_BIT(Interrupt->Port,GPIOIEV,Interrupt->Pin);
            break;
        case BOTH :
                SET_BIT(Interrupt->Port,GPIOIBE,Interrupt->Pin);
            break;
        default:
            break;
    }
}

/* Function Name: enableInterruptModule
*  Fucntion description: enables the interrupt from the NVIC register
*                        takes the interrupt number (in the datasheet) and enables the corresponding bit
*/
static void enableInterruptModule(volatile uint8 Module )
{
    if(Module<=31 && Module >=0)
    {
        SET_BIT(NVIC,EN0,Module);
    }
    else if (Module<=63 && Module>=32)
    {
        SET_BIT(NVIC,EN1,Module-32);
    }
    else if (Module<=95 && Module >=64)
    {
        SET_BIT(NVIC,EN2,Module-64);
    }
    else if (Module<=127 && Module >=96)
    {
        SET_BIT(NVIC,EN3,Module-96);
    }
    else if (Module<=138 && Module >=128)
    {
        SET_BIT(NVIC,EN4,Module-128);
    }
}

/* Function Name: getInterruptNumber
*  Fucntion description: Takes the port and returns the number required to  
*  enable interrupts for this port
*/
static uint8 getInterruptNumber(uint32 Port)     /*Page 104 in the datasheet*/
{
    switch(Port)
    {
        case PORTA:
            return 0;
            break;
        case PORTB:
            return 1;
            break;
        case PORTC:
            return 2;
            break;
        case PORTD:
            return 3;
            break;
        case PORTE:
            return 4;
            break;
        case PORTF:
            return 30;
            break;            
        default:
            return -1;
            break;
    }
}

/* Function Name: setCallBack
*  Fucntion description: sets the call back function needed 
*  to be called when the interrupt fires
*/
static void setCallBack(uint32 Port, volatile void *callBackFunction)
{
    switch(Port)
    {
        case PORTA:
            PORTACallBackFunction = callBackFunction;
            break;
        case PORTB:
            PORTBCallBackFunction = callBackFunction;;
            break;
        case PORTC:
            PORTCCallBackFunction = callBackFunction;
            break;
        case PORTD:
            PORTDCallBackFunction = callBackFunction;
            break;
        case PORTE:
            PORTECallBackFunction = callBackFunction;
            break;
        case PORTF:
            PORTFCallBackFunction = callBackFunction;
            break;            
        default:
            break;
    }
}

/*********************************************************************************/
/*                              Public Functions                                 */
/*********************************************************************************/

/* Function Name: PORTAInterruptHandler
*  Fucntion description: The ISR function that calls the callback function for PORTA
*/
void PORTAInterruptHandler (void)
{

    if (PORTACallBackFunction!=NULL) {
        (*PORTACallBackFunction)();
    }
}

/* Function Name: PORTBInterruptHandler
*  Fucntion description: The ISR function that calls the callback function for PORTB
*/
void PORTBInterruptHandler (void) 
{

    if (PORTBCallBackFunction!=NULL) 
    {
        (*PORTBCallBackFunction)();
    }
}

/* Function Name: PORTCInterruptHandler
*  Fucntion description: The ISR function that calls the callback function for PORTC
*/
void PORTCInterruptHandler (void) 
{

    if (PORTCCallBackFunction!=NULL) 
    {
        (*PORTCCallBackFunction)();
    }
}
/* Function Name: PORTDInterruptHandler
*  Fucntion description: The ISR function that calls the callback function for PORTD
*/
void PORTDInterruptHandler (void) 
{

    if (PORTDCallBackFunction!=NULL) 
    {
        (*PORTDCallBackFunction)();
    }
}

/* Function Name: PORTEInterruptHandler
*  Fucntion description: The ISR function that calls the callback function for PORTE
*/
void PORTEInterruptHandler (void) 
{

    if (PORTECallBackFunction!=NULL) 
    {
        (*PORTECallBackFunction)();
    }
}

/* Function Name: PORTFInterruptHandler
*  Fucntion description: The ISR function that calls the callback function for PORTF
*/
void PORTFInterruptHandler (void) 
{

    if (PORTFCallBackFunction!=NULL) 
    {
        (*PORTFCallBackFunction)();
    }
}

/* Function Name: GPIO_enableInterrupt
*  Fucntion description: function that takes the configurations for the interrupt and the call back function
*                       and sets everything for the external interrupts
*/
void GPIO_enableInterrupt(const INTERRUPT *configInterrupt, volatile void *callbackFunction)
{
    processorDisableInterrupt();         /* Disabling interrupts */

    /*1 - Mask the corresponding port by clearing the IME field in the GPIOIM register */
    CLEAR_BIT(configInterrupt->Port,GPIOIM,configInterrupt->Pin);

    /*2 - Configure the IS field in the GPIOIS register and the IBE field in the GPIOIBE register */
    if(configInterrupt->Sense == EDGE_SENSE)
    {
        CLEAR_BIT(configInterrupt->Port,GPIOIS,configInterrupt->Pin);
    }
    else if(configInterrupt->Sense == LEVEL_SENSE)
    {
        SET_BIT(configInterrupt->Port,GPIOIS,configInterrupt->Pin);
    }

    /*3 - Sets the interrupt type (Rising,Falling,Both,Low,High)*/
    setInterruptType(configInterrupt);

    /*4 - Clears the register to avoid false interrupts*/
    SET_BIT(configInterrupt->Port,GPIOICR,configInterrupt->Pin);

    /*5- Unmasking the interrupt to detect it*/
    SET_BIT(configInterrupt->Port,GPIOIM,configInterrupt->Pin);
    
    /*6- enabling the interrupt module in the vector table*/
    enableInterruptModule( getInterruptNumber(configInterrupt->Port) );
    
    /*7- setting the callback function*/
    setCallBack(configInterrupt->Port,callbackFunction);

    /*8- enabling the interrupts from the processor using an assembly instruction*/
    processorEnableInterrupt();   
}

/* Function Name: detectPin
*  Fucntion description: The interrupt that fires detects the whole port, so we need to detect which pin
*                        fired the interrupt so we need this function to be called inside the ISR.
*                        This function takes the port and dectects which pin has the interrupt from the GPIOMIS register
*/
uint8 detectPin(uint32 Port)
{
    switch(ACCESS_REG(Port,GPIOMIS))    /*access masked interrupt register*/
    {
        case 0 :
            return 0xFF ;               /*No Interrupts*/

        case 1 :
            return PIN0 ;

        case 2 :
            return PIN1 ;

        case 4 :
            return PIN2 ;

        case 8 :
            return PIN3 ;

        case 16 :
            return PIN4 ;

        case 32 :
            return PIN5 ;

        case 64 :
            return PIN6 ;

        case 128 :
            return PIN7 ;

        default :
            return ACCESS_REG(Port,GPIOMIS);            /*More than one pin*/
    }
}

/* Function Name: clearAfterHandle
*  Fucntion description: function that clears the corresponding interrupt pin after handling the interrupt so we detect future
*                        interrupts, this function should be called in the ISR before returning from it.
                         the function takes the Port and the pin that fired the interrupt.
*/
void clearAfterHandle(uint32 Port,uint32 Pin)
{
    SET_BIT(Port,GPIOICR,Pin);      /*clearing the corrseponding interrupt after handling it "Call in the end of the ISR"*/

}
