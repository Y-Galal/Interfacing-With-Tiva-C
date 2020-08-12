#ifndef TIMER_REGISTERS
#define TIMER_REGISTERS

/*****      Timer base addresses              *****/
#define TIMER0_16 0x40030000
#define TIMER1_16 0x40031000
#define TIMER2_16 0x40032000
#define TIMER3_16 0x40033000
#define TIMER4_16 0x40034000
#define TIMER5_16 0x40035000
#define TIMER0_32 0x40036000
#define TIMER1_32 0x40037000
#define TIMER2_32 0x4004C000
#define TIMER3_32 0x4004D000
#define TIMER4_32 0x4004E000
#define TIMER5_32 0x4004F000

#define RCGCTIMER 0x604
#define RCGCWTIMER 0x65C
#define SYSTEM_CONTROL          0x400FE000 
/*****      Timers Important Registers       *****/

#define GPTMCFG     0x000       /*GPTM Configuration*/
/*
     0x0 For a 16/32-bit timer, this value selects the 32-bit timer
        configuration.
        For a 32/64-bit wide timer, this value selects the 64-bit timer
        configuration.

    0x1 For a 16/32-bit timer, this value selects the 32-bit real-time
    clock (RTC) counter configuration.
        For a 32/64-bit wide timer, this value selects the 64-bit
        real-time clock (RTC) counter configuration.
    0x4 For a 16/32-bit timer, this value selects the 16-bit timer
        configuration.
        For a 32/64-bit wide timer, this value selects the 32-bit timer
        configuration.
*/
#define GPTMTAMR    0x004   /*GPTM Timer A Mode*/
        
        #define TAPLO 11    /*GPTM Timer A PWM Legacy Operation*/
        /*
        0 -> Legacy operation with CCP pin driven Low when the
            GPTMTAILR is reloaded after the timer reaches 0.
        1-> CCP is driven High when the GPTMTAILR is reloaded after the
        timer reaches 0.
        This bit is only valid in PWM mode.*/

        #define TAMRSU 10   /*GPTM Timer A Match Register Update*/
        /*
            0-> Update the GPTMTAMATCHR register and the GPTMTAPR
            register, if used, on the next cycle.
            
            1-> Update the GPTMTAMATCHR register and the GPTMTAPR
            register, if used, on the next timeout. 
        */
        #define TAPWMIE 9   /*Timer A PWM Interrupt enable*/
        /*
            0 -> Capture event interrupt is disabled.
            1 -> Capture event interrupt is enabled.
            This bit is only valid in PWM mode.
        */
        #define TAILD   8   /*GPTM Timer A Interval Load Write*/
        /*
            0-> Update the GPTMTAR and GPTMTAV registers with the value
            in the GPTMTAILR register on the next cycle. Also update the
            GPTMTAPS and GPTMTAPV registers with the value in the
            GPTMTAPR register on the next cycle.

            1-> Update the GPTMTAR and GPTMTAV registers with the value
            in the GPTMTAILR register on the next timeout. Also update
            the GPTMTAPS and GPTMTAPV registers with the value in
            the GPTMTAPR register on the next timeout.

        */
        #define TASNAPS 7   /*GPTM Timer A Snap-Shot Mode*/
        /*
            0-> Snap-shot mode is disabled.
            
            1-> If Timer A is configured in the periodic mode, the actual
            free-running, capture or snapshot value of Timer A is loaded at
            the time-out event/capture or snapshot event into the GPTM
            Timer A (GPTMTAR) register. If the timer prescaler is used,
            the prescaler snapshot is loaded into the GPTM Timer A
            (GPTMTAPR).
        */
        #define TAWOT   6   /*GPTM Timer A Wait-on-Trigger*/
        /*
            0->Timer A begins counting as soon as it is enabled.
            1->If Timer A is enabled (TAEN is set in the GPTMCTL register),
            Timer A does not begin counting until it receives a trigger from
            the timer in the previous position in the daisy chain, periodic,
            and PWM modes.
            This bit must be clear for GP Timer Module 0, Timer A.
        */
        #define TAMIE   5   /*GPTM Timer A Match Interrupt Enable*/
        /*
            0-> The match interrupt is disabled for match events.
            1-> An interrupt is generated when the match value in the
                GPTMTAMATCHR register is reached in the one-shot and
                periodic modes.
        */
        #define TACDIR  4   /*GPTM Timer A Count Direction*/
        /*
            0->The timer counts down.
            1->The timer counts up. When counting up, the timer starts from a
               value of 0x0.
        */
        #define TAAMS   3   /*GPTM Timer A Alternate Mode Select*/
        /*
            0-> Capture or compare mode is enabled.
            1-> PWM mode is enabled.
        */
        #define TACMR   2   /*GPTM Timer A Capture Mode*/
        /*
            0-> Edge-Count mode
            1-> Edge-Time mode
        */
        #define TAMR1    1   /*GPTM Timer A Mode*/
        #define TAMR0    0
        /*
            01 One-Shot Timer mode
            10 Periodic Timer mode
            11 Capture mode
        */

#define GPTMTBMR    0x008       /*GPTM Timer B Mode*/ /*Same bits as GPTMAMR */
            #define TBPLO 11    /*GPTM Timer B PWM Legacy Operation*/
        /*
        0 -> Legacy operation with CCP pin driven Low when the
            GPTMTAILR is reloaded after the timer reaches 0.
        1-> CCP is driven High when the GPTMTBILR is reloaded after the
        timer reaches 0.
        This bit is only valid in PWM mode.*/

        #define TBMRSU 10   /*GPTM Timer B Match Register Update*/
        /*
            0-> Update the GPTMTBMATCHR register and the GPTMTBPR
            register, if used, on the next cycle.
            
            1-> Update the GPTMTBMATCHR register and the GPTMTBPR
            register, if used, on the next timeout. 
        */
        #define TBPWMIE 9   /*Timer B PWM Interrupt enable*/
        /*
            0 -> Capture event interrupt is disabled.
            1 -> Capture event interrupt is enabled.
            This bit is only valid in PWM mode.
        */
        #define TBILD   8   /*GPTM Timer B Interval Load Write*/
        /*
            0-> Update the GPTMTBR and GPTMTBV registers with the value
            in the GPTMTBILR register on the next cycle. Also update the
            GPTMTBPS and GPTMTBPV registers with the value in the
            GPTMTBPR register on the next cycle.

            1-> Update the GPTMTBR and GPTMTBV registers with the value
            in the GPTMTBILR register on the next timeout. Also update
            the GPTMTBPS and GPTMTBPV registers with the value in
            the GPTMTBPR register on the next timeout.

        */
        #define TBSNAPS 7   /*GPTM Timer B Snap-Shot Mode*/
        /*
            0-> Snap-shot mode is disabled.
            
            1-> If Timer B is configured in the periodic mode, the actual
            free-running, capture or snapshot value of Timer B is loaded at
            the time-out event/capture or snapshot event into the GPTM
            Timer B (GPTMTBR) register. If the timer prescaler is used,
            the prescaler snapshot is loaded into the GPTM Timer B
            (GPTMTBPR).
        */
        #define TBWOT   6   /*GPTM Timer B Wait-on-Trigger*/
        /*
            0->Timer B begins counting as soon as it is enabled.
            1->If Timer B is enabled (TAEN is set in the GPTMCTL register),
            Timer B does not begin counting until it receives a trigger from
            the timer in the previous position in the daisy chain, periodic,
            and PWM modes.
            This bit must be clear for GP Timer Module 0, Timer B.
        */
        #define TBMIE   5   /*GPTM Timer B Match Interrupt Enable*/
        /*
            0-> The match interrupt is disabled for match events.
            1-> An interrupt is generated when the match value in the
                GPTMTAMATCHR register is reached in the one-shot and
                periodic modes.
        */
        #define TBCDIR  4   /*GPTM Timer B Count Direction*/
        /*
            0->The timer counts down.
            1->The timer counts up. When counting up, the timer starts from a
               value of 0x0.
        */
        #define TBAMS   3   /*GPTM Timer B Alternate Mode Select*/
        /*
            0-> Capture or compare mode is enabled.
            1-> PWM mode is enabled.
        */
        #define TBCMR   2   /*GPTM Timer B Capture Mode*/
        /*
            0-> Edge-Count mode
            1-> Edge-Time mode
        */
        #define TBMR1    1   /*GPTM Timer B Mode*/
        #define TBMR0    0
        /*
            01 One-Shot Timer mode
            10 Periodic Timer mode
            11 Capture mode
        */

#define GPTMCTL     0x00C       /*GPTM Control*/

    #define TBPWML  14      /*GPTM Timer B PWM Output Level*/
    /*
            0-> Output is unaffected.
            1-> Output is inverted.
    */

    #define TBOTE   13      /*GPTM Timer B Output Trigger Enable*/
    /*
        0-> The output Timer B ADC trigger is disabled.
        1-> The output Timer B ADC trigger is enabled.
    */
    #define TBEVENT1 11      /*GPTM Timer B Event Mode*/ 
    #define TBEVENT0 10
    /*
        0x0 Positive edge
        0x1 Negative edge
        0x2 Reserved
        0x3 Both edges
    */
    #define TBSTALL 9      /*GPTM Timer B Stall Enable*/
    /*
        0-> Timer B continues counting while the processor is halted by the
            debugger.

        1-> Timer B freezes counting while the processor is halted by the
            debugger.
    */
    #define TBEN    8       /*GPTM Timer B Enable*/
    /*
        0-> Timer B is disabled.
        1-> Timer B is enabled and begins counting or the capture logic is
            enabled based on the GPTMCFG register.
    */
    #define TAPWML  6       /*GPTM Timer A PWM Output Level*/
    #define TAOTE   5       /*GPTM Timer A Output Trigger Enable*/
    #define RTCEN   4       /*GPTM RTC Stall Enable*/
    #define TAEVENT1    3       /*GPTM Timer A Event Mode*/
    #define TAEVENT0    2 
    /*
            0x0 Positive edge
            0x1 Negative edge
            0x2 Reserved
            0x3 Both edges
    */
    #define TASTALL 1       /*GPTM Timer B Stall Enable*/
    #define TAEN    0       /*GPTM Timer A Enable*/

#define GPTMSYNC    0x010   /*GPTM Synchronize, This register is only implemented on GPTM Module 0 only.*/
                            /*This register allows software to synchronize a number of timers.*/
    
#define GPTMIMR     0x018   /*GPTM Interrupt Mask 0-> disabled, 1-> enabled*/
        #define WUEIM 16   /*32/64-Bit Wide GPTM Write Update Error Interrupt Mask*/
        #define TBMIM 11   /*GPTM Timer B Match Interrupt Mask*/ 
        #define CBEIM 10    /*GPTM Timer B Capture Mode Event Interrupt Mask*/
        #define CBMIM 9     /*GPTM Timer B Capture Mode Match Interrupt Mask*/
        #define TBTOIM 8    /*GPTM Timer B Time-Out Interrupt Mask*/
        #define TAMIM 4     /*GPTM Timer A Match Interrupt Mask*/
        #define RTCIM 3     /*GPTM RTC Interrupt Mask*/
        #define CAEIM 2     /*GPTM Timer A Capture Mode Event Interrupt Mask*/
        #define CAMIM 1     /*GPTM Timer A Capture Mode Match Interrupt Mask*/
        #define TATOIM 0    /*GPTM Timer A Time-Out Interrupt Mask*/

#define GPTMRIS     0x01C   /*GPTM Raw Interrupt Status */
        #define WUERIS 16   /*32/64-Bit Wide GPTM Write Update Error Raw Interrupt Status*/
        #define TBMRIS 11   /*GPTM Timer B Match Raw Interrupt Status*/ 
        #define CBERIS 10    /*GPTM Timer B Capture Mode Event Raw Interrupt Status*/
        #define CBMRIS 9     /*GPTM Timer B Capture Mode Match Raw Interrupt Status*/
        #define TBTORIS 8    /*GPTM Timer B Time-Out Raw Interrupt Status*/
        #define TAMRIS 4     /*GPTM Timer A Match Raw Interrupt Status*/
        #define RTCRIS 3     /*GPTM RTC Raw Interrupt Status*/
        #define CAERIS 2     /*GPTM Timer A Capture Mode Event Raw Interrupt Status*/
        #define CAMRIS 1     /*GPTM Timer A Capture Mode Match Raw Interrupt Status*/
        #define TATORIS 0    /*GPTM Timer A Time-Out Raw Interrupt Status*/

#define GPTMMIS     0x020   /*GPTM Masked Interrupt Status*/
        #define WUEMIS 16   /*32/64-Bit Wide GPTM Write Update Error Masked Interrupt Status*/
        #define TBMMIS 11   /*GPTM Timer B Match Masked Interrupt Status*/ 
        #define CBEMIS 10    /*GPTM Timer B Capture Mode Event Masked Interrupt Status*/
        #define CBMMIS 9     /*GPTM Timer B Capture Mode Match Masked Interrupt Status*/
        #define TBTOMIS 8    /*GPTM Timer B Time-Out Masked Interrupt Status*/
        #define TAMMIS 4     /*GPTM Timer A Match Masked Interrupt Status*/
        #define RTCMIS 3     /*GPTM RTC Masked Interrupt Status*/
        #define CAEMIS 2     /*GPTM Timer A Capture Mode Event Masked Interrupt Status*/
        #define CAMMIS 1     /*GPTM Timer A Capture Mode Match Masked Interrupt Status*/
        #define TATOMIS 0    /*GPTM Timer A Time-Out Masked Interrupt Status*/

#define GPTMICR     0x024   /*GPTM Interrupt Clear (Bits are cleared when we WRITE 1 TO IT) */
        #define WUECINT 16   /*32/64-Bit Wide GPTM Write Update Error Raw Interrupt Clear*/
        #define TBMCINT 11   /*GPTM Timer B MatchRaw Interrupt Clear*/ 
        #define CBECINT 10    /*GPTM Timer B Capture Mode Event Raw Interrupt Clear*/
        #define CBMCINT 9     /*GPTM Timer B Capture Mode Match Raw Interrupt Clear*/
        #define TBTOCINT 8    /*GPTM Timer B Time-Out Raw Interrupt Clear*/
        #define TAMCINT 4     /*GPTM Timer A Match Raw Interrupt Clear*/
        #define RTCCINT 3     /*GPTM RTC Raw Interrupt Clear*/
        #define CAECINT 2     /*GPTM Timer A Capture Mode Event Raw Interrupt Clear*/
        #define CAMCINT 1     /*GPTM Timer A Capture Mode Match Raw Interrupt Clear*/
        #define TATOCINT 0    /*GPTM Timer A Time-Out Raw Interrupt Clear*/

#define GPTMTAILR   0x028    /*GPTM Timer A Interval Load*/
/*
    When the timer is counting down, this register is used to load the starting count value into the timer.
    When the timer is counting up, this register sets the upper bound for the timeout event.
    When a 32/64-bit Wide GPTM is configured to one of the 64-bit modes, GPTMTAILR contains bits
    31:0 of the 64-bit count and the GPTM Timer B Interval Load (GPTMTBILR) register contains bits
    63:32.
*/

#define GPTMTBILR   0x02C   /*GPTM Timer B Interval Load*/
/*
    Same as GPTMAILR
*/
#define GPTMTAMATCHR 0x030  /*GPTM Timer A Match*/
/*
        When a 16/32-bit GPTM is configured to one of the 32-bit modes, GPTMTAMATCHR appears as
        a 32-bit register (the upper 16-bits correspond to the contents of the GPTM Timer B Match
        (GPTMTBMATCHR) register). In a 16-bit mode, the upper 16 bits of this register read as 0s and
        have no effect on the state of GPTMTBMATCHR.
        When a 32/64-bit Wide GPTM is configured to one of the 64-bit modes, GPTMTAMATCHR contains
        bits 31:0 of the 64-bit match value and the GPTM Timer B Match (GPTMTBMATCHR) register
        contains bits 63:32.
*/
#define GPTMTBMATCHR 0x034  /*GPTM Timer B Match*/
/*
        When a 16/32-bit GPTM is configured to one of the 32-bit modes, the contents of bits 15:0 in this
        register are loaded into the upper 16 bits of the GPTMTAMATCHR register. Reads from this register
        return the current match value of Timer B and writes are ignored. In a 16-bit mode, bits 15:0 are
        used for the match value. Bits 31:16 are reserved in both cases.
        When a 32/64-bit Wide GPTM is configured to one of the 64-bit modes, GPTMTAMATCHR contains
        bits 31:0 of the 64-bit match value and the GPTMTBMATCHR register contains bits 63:32.
*/
#define GPTMTAPR    0x038   /*GPTM Timer A Prescale*/
/*
    This register has 16 bits to write the prescale. 
    If we are using wide timer we will set the prescaler
    in the whole 16 bits.
    If we are using the normal timers we will set the prescaler in the 
    first 8 bits only. 
*/
#define GPTMTBPR    0x03C   /*GPTM Timer B Prescale*/
/*
    This register has 16 bits to write the prescale. 
    If we are using wide timer we will set the prescaler
    in the whole 16 bits.
    If we are using the normal timers we will set the prescaler in the 
    first 8 bits only. 
*/

#define GPTMTAPMR   0x040   /*GPTM TimerA Prescale Match*/
/*
    This register allows software to extend the range of the GPTMTAMATCHR when the timers are
    used individually. This register holds bits 23:16 in the 16-bit modes of the 16/32-bit GPTM and bits
    47:32 in the 32-bit modes of the 32/64-bit Wide GPTM.
*/
#define GPTMTBPMR   0x044   /*GPTM TimerB Prescale Match*/
/*
    This register allows software to extend the range of the GPTMTBMATCHR when the timers are
    used individually. This register holds bits 23:16 in the 16-bit modes of the 16/32-bit GPTM and bits
    47:32 in the 32-bit modes of the 32/64-bit Wide GPTM.
*/
#define GPTMTAR     0x048   /*GPTM Timer A*/
/*
    This register shows the current value of the Timer A counter in all cases except for Input Edge Count
    and Time modes. In the Input Edge Count mode, this register contains the number of edges that
    have occurred. In the Input Edge Time mode, this register contains the time at which the last edge
    event took place.
*/
#define GPTMTBR     0x04C  /*GPTM Timer B*/
/*
    This register shows the current value of the Timer B counter in all cases except for Input Edge Count
    and Time modes. In the Input Edge Count mode, this register contains the number of edges that
    have occurred. In the Input Edge Time mode, this register contains the time at which the last edge
    event took place.
*/
#define GPTMTAV     0x050   /*GPTM Timer A Value*/
/*
    When read, this register shows the current, free-running value of Timer A in all modes. Software
    can use this value to determine the time elapsed between an interrupt and the ISR entry when using
    the snapshot feature with the periodic operating mode. When written, the value written into this
    register is loaded into the GPTMTAR register on the next clock cycle.
*/
#define GPTMTBV     0x054   /*GPTM Timer B Value*/
/*
    When read, this register shows the current, free-running value of Timer B in all modes. Software
    can use this value to determine the time elapsed between an interrupt and the ISR entry. When
    written, the value written into this register is loaded into the GPTMTBR register on the next clock
    cycle.
*/
#define GPTMRTCPD   0x058   /*GPTM RTC Predivide*/
/*
This register provides the current RTC predivider value when the timer is operating in RTC mode.
*/
#define GPTMTAPS    0x05C   /*GPTM Timer A Prescale Snapshot*/
/*
    For the 32/64-bit Wide GPTM, this register shows the current value of the Timer A prescaler in the
    32-bit modes. For 16-/32-bit wide GPTM, this register shows the current value of the Timer A
    prescaler for periodic snapshot mode.
*/
#define GPTMTBPS    0x060   /*GPTM Timer B Prescale Snapshot*/
/*
    For the 32/64-bit Wide GPTM, this register shows the current value of the Timer B prescaler in the
    32-bit modes. For 16-/32-bit wide GPTM, this register shows the current value of the Timer B
    prescaler for periodic snapshot mode.
*/
#define GPTMTAPV    0x064   /*GPTM Timer A Prescale Value*/
/*
    For the 32/64-bit Wide GPTM, this register shows the current free-running value of the Timer A
    prescaler in the 32-bit modes. Software can use this value in conjunction with the GPTMTAV register
    to determine the time elapsed between an interrupt and the ISR entry. This register is ununsed in
    16/32-bit GPTM mode.
*/
#define GPTMTBPV    0x068   /*GPTM Timer B Prescale Value*/
/*
    For the 32/64-bit Wide GPTM, this register shows the current free-running value of the Timer B
    prescaler in the 32-bit modes. Software can use this value in conjunction with the GPTMTBV register
    to determine the time elapsed between an interrupt and the ISR entry. This register is ununsed in
    16/32-bit GPTM mode.
*/
#define GPTMPP      0xFC0   /*GPTM Peripheral Properties*/
/*
    0-> Timer A and Timer B counters are 16 bits each with an 8-bit
        prescale counter.
    1-> Timer A and Timer B counters are 32 bits each with a 16-bit
        prescale counter.
*/

#endif




