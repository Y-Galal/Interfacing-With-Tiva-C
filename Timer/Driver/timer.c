#include "timer.h"

static volatile void (*g_timerSetCallBack_ptr)() = NULL;

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

/* Function Name: enableInterruptModule
*  Fucntion description: Enables interrupt for the selected timer module
*/
static void enableInterruptModule(volatile uint8 Module )
{
    if(Module<=31 )
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

/* Function Name: enableClock
*  Fucntion description: Enables clock for the selected timer module
*/

static void enableClock(volatile uint32 TimerNumber)
{
    switch(TimerNumber)
    {

        case TIMER0_16:
            SET_BIT(SYSTEM_CONTROL,RCGCTIMER,0);
            break;
        case TIMER1_16:
            SET_BIT(SYSTEM_CONTROL,RCGCTIMER,1);
            break;
        case TIMER2_16:
            SET_BIT(SYSTEM_CONTROL,RCGCTIMER,2);
            break;
        case TIMER3_16:
            SET_BIT(SYSTEM_CONTROL,RCGCTIMER,3);
            break;
        case TIMER4_16:
            SET_BIT(SYSTEM_CONTROL,RCGCTIMER,4);
            break;
        case TIMER5_16:
            SET_BIT(SYSTEM_CONTROL,RCGCTIMER,5);
            break;
        case TIMER0_32:
            SET_BIT(SYSTEM_CONTROL,RCGCWTIMER,0);
            break;
        case TIMER1_32:
            SET_BIT(SYSTEM_CONTROL,RCGCWTIMER,1);
            break;
        case TIMER2_32:
            SET_BIT(SYSTEM_CONTROL,RCGCWTIMER,2);
            break;
        case TIMER3_32:
            SET_BIT(SYSTEM_CONTROL,RCGCWTIMER,3);
            break;
        case TIMER4_32:
            SET_BIT(SYSTEM_CONTROL,RCGCWTIMER,4);
            break;
        case TIMER5_32:
            SET_BIT(SYSTEM_CONTROL,RCGCWTIMER,5);
            break;
        default:
            #warning enable clock and interrupt failed
            break;
    }
}

/**************** Public Functions ***********************/

/* Function Name: TIMER_init
*  Fucntion description: starts the timer with the selected configurations that are 
*                       stored in TimerConfigurations Structure
*/
void TIMER_init(const TimerConfigurations *config)
{
    processorDisableInterrupt();


    enableClock(config->Module);    /*Enable clock for the selected module*/
    enableInterruptModule(config->TimerSelect); /*enabling interrupts for the selected module*/

    ACCESS_REG(config->Module,GPTMCFG)=config->Size;    /*For a single module, we can choose 16 bits or 32 bits */
                                                        /*In wide timers we can choose also 32 bits or 64 bits*/

    if( (config->Half) == A )
    {
        CLEAR_BIT(config->Module,GPTMCTL,TAEN);
        ACCESS_REG(config->Module,GPTMTAMR) = (1<<TAMIE)|(config->Direction)|(config->Type)|(1<<TAILD)| (1<<TAMRSU);
                                        /*enables match interrupt, direction up or down*/
                                        /* and the type of the timer (one shot or periodic) */
        ACCESS_REG(config->Module,GPTMIMR)=(1<<TATOIM); /*enable Timeout interrupt*/

        if( (config->Size) == FULL) /*putting the value of the timer*/
        {
           ACCESS_REG(config->Module,GPTMTBILR) = ((config->TimerValue)&(0xFFFFFFFF00000000))>> 32;
           ACCESS_REG(config->Module,GPTMTAILR) = (config->TimerValue);

        }
        else if ( (config->Size) == HALF)
        {
            ACCESS_REG(config->Module,GPTMTAILR) = (config->TimerValue);
            
            ACCESS_REG(config->Module,GPTMTAPR)= (config->Prescale);  /*setting prescaler*/
        }
        
        
        SET_BIT(config->Module,GPTMCTL,TAEN);   /*Starting Timer A*/
    }
   else if((config->Half) == B )
   {
        CLEAR_BIT(config->Module,GPTMCTL,TBEN);

        ACCESS_REG(config->Module,GPTMTBMR) = (1<<TBMIE)|(config->Direction)|(config->Type)|(1<<TBILD)| (1<<TBMRSU);
                                        /*enables match interrupt, direction up or down*/
                                        /* and the type of the timer (one shot or periodic) */
        ACCESS_REG(config->Module,GPTMIMR)=(1<<TBTOIM); /*enable Timeout interrupt*/

        /*putting the value of the timer*/
        ACCESS_REG(config->Module,GPTMTBILR) = (config->TimerValue);

        ACCESS_REG(config->Module,GPTMTBPR)= (config->Prescale);  /*setting prescaler*/

        SET_BIT(config->Module,GPTMCTL,TBEN);   /*Starting Timer B*/
   }
    processorEnableInterrupt();                 /*Enabling interrupts from the processor*/        
}

/* Function Name: TIMER_setCallBack
*  Fucntion description: Sets the callback function to be called when the interrupt fires 
*                       
*/
void TIMER_setCallBack( volatile void (*timerCallBack)() )
{
    g_timerSetCallBack_ptr = timerCallBack;
}

/* Function Name: TIMER_deinit
*  Fucntion description: Clears the timer registers and stops the timer
*                       
*/
void TIMER_deinit(uint32 Module)
{
    ACCESS_REG(Module,GPTMCTL)=0;
    ACCESS_REG(Module,GPTMCFG)=0;
    ACCESS_REG(Module,GPTMTAMR)=0;
    ACCESS_REG(Module,GPTMTBMR)=0;
    ACCESS_REG(Module,GPTMIMR)=0;
    ACCESS_REG(Module,GPTMICR)=0xFFFFFFFF;
    ACCESS_REG(Module,GPTMTAILR)=0xFFFFFFFF;
    ACCESS_REG(Module,GPTMTBILR)=0xFFFFFFFF;
    ACCESS_REG(Module,GPTMTAMATCHR)=0xFFFFFFFF;
    ACCESS_REG(Module,GPTMTAR)=0xFFFFFFFF;
    ACCESS_REG(Module,GPTMTAPR)=0;
    ACCESS_REG(Module,GPTMTAPMR)=0;
    ACCESS_REG(Module,GPTMTBMATCHR)=0xFFFFFFFF;
    ACCESS_REG(Module,GPTMTBR)=0xFFFFFFFF;
    ACCESS_REG(Module,GPTMTBPR)=0;
    ACCESS_REG(Module,GPTMTBPMR)=0;
}

/* Function Name: TIMER_ISR
*  Fucntion description: The interrupt service routine that will be called when the interrupt comes
!   NOTE: You should extern this function in the startup code and copy it to the interrupt vector table
*                       
*/
void TIMER_ISR()
{
    if(g_timerSetCallBack_ptr != NULL)
    {
        g_timerSetCallBack_ptr();
    }
}
