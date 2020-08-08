#ifndef UART_REGISTERS_H
#define UART_REGISTERS_H

/* UART base addresses */
#define UART0 0x4000C000
#define UART1 0x4000D000
#define UART2 0x4000E000
#define UART3 0x4000F000
#define UART4 0x40010000
#define UART5 0x40011000
#define UART6 0x40012000
#define UART7 0x40013000

/* UART register map*/

#define UART_DR               0x00000000    /* UART Data*/
/*
*   bits: OE(11) BE(10) PE(9) FE(8) DATA(7:0)
    OE: overrun error 0-> No data has been lost due to a FIFO overrun.
                      1-> New data was received when the FIFO was full, resulting in data loss.

    BE: Break Error 0 -> No break condition has occurred
                    1 -> A break condition has been detected, indicating that the receive
                         data input was held Low for longer than a full-word transmission
                         time (defined as start, data, parity, and stop bits).

    PE: Parity Error 0->  No parity error has occurred
                     1->  The parity of the received data character does not match the
                          parity defined by bits 2 and 7 of the UARTLCRH register

    FE: Frame Error 0 -> No framing error has occurred
                    1 -> The received character does not have a valid stop bit (a valid
                         stop bit is 1).

    Data: Data transmitted or received
*/

#define UART_RSR              0x00000004    /* UART Receive Status/Error Clear*/
#define UART_ECR              0x00000004    /* UART Receive Status/Error Clear*/
/*
*   OE(3) BE(2) PE(1) FE(0)
*   read only register that you can also check for the errors and clear them by writing any value on UART_ECR (Write only) 
*/

#define UART_FR               0x00000018    /* UART Flag*/
/*This register has some flags that are defined below*/
        #define TXFE 7      /* UART Transmit FIFO empty */
        /*
        *   The meaning of this bit depends on the state of the FEN bit in the
        *   UARTLCRH register.
        *
        *   0 -> The transmitter has data to transmit.
        *   1 ->    If the FIFO is disabled (FEN is 0), the transmit holding register is empty.
        *           If the FIFO is enabled (FEN is 1), the transmit FIFO is empty
        */

        #define RXFF 6 
        /*
        *   0 -> The receiver can receive data.
        *    1 -> If the FIFO is disabled (FEN is 0), the receive holding register is full.
        *         If the FIFO is enabled (FEN is 1), the receive FIFO is full.
        */

        #define TXFF 5 
        /*
        *   0-> The transmitter is not full.
        *   1-> If the FIFO is disabled (FEN is 0), the transmit holding register is full.
        *       If the FIFO is enabled (FEN is 1), the transmit FIFO is full. 
        */

        #define RXFE 4 
        /*  
        *   0 -> The receiver is not empty.
        *   1 -> If the FIFO is disabled (FEN is 0), the receive holding register is empty.
        *        If the FIFO is enabled (FEN is 1), the receive FIFO is empty.
        */

        #define BUSY 3
        /*
        *    0 -> The UART is not busy.
        *    1 -> The UART is busy transmitting data. This bit remains set until
        *           the complete byte, including all stop bits, 
        *           has been sent from the shift register.
        */

#define UART_ILPR             0x00000020    /* UART IrDA Low-Power Register*/

#define UART_IBRD             0x00000024    /* UART Integer Baud-Rate Divisor*/

#define UART_FBRD             0x00000028    /* UART Fractional Baud-Rate Divisor*/

#define UART_LCRH             0x0000002C    /* UART Line Control*/

        #define SPS 7   /*UART Stick Parity Select*/
        /*
        *    When bits 1, 2, and 7 of UARTLCRH are set, the parity bit is transmitted
        *    and checked as a 0. When bits 1 and 7 are set and 2 is cleared, the
        *    parity bit is transmitted and checked as a 1.
        *    When this bit is cleared, stick parity is disabled. 
        * */

        #define WLEN1 6     /*UART Word Length*/
        #define WLEN0 5
        /*
        *    0x0 5 bits (default)
        *    0x1 6 bits
        *    0x2 7 bits
        *    0x3 8 bits
        */

        #define FEN 4 /*UART Enable FIFOs*/
        /*
        *   0 -> The FIFOs are disabled (Character mode). The FIFOs become
        *        1-byte-deep holding registers.
        *    1 -> The transmit and receive FIFObuffers are enabled (FIFOmode).
         */

        #define STP2 3 /*UART Two Stop Bits Select*/
        /*
        *  0 -> One stop bit is transmitted at the end of a frame.
           1 -> Two stop bits are transmitted at the end of a frame. The receive
                logic does not check for two stop bits being received.
        * */

        #define EPS 2 /*UART Even Parity Select*/
        /*
        *    0 -> Odd parity is performed, which checks for an odd number of 1s.
             1 -> Even parity generation and checking is performed during
                  transmission and reception, which checks for an even number
                  of 1s in data and parity bits.
            ***This bit has no effect when parity is disabled by the PEN bit.
        */

        #define PEN 1 /*UART Parity Enable*/
        /*
        *   0 -> Parity is disabled and no parity bit is added to the data frame.
        *    1 -> Parity checking and generation is enabled.
        */

        #define BRK 0   /*UART Send Break*/
        /*
        *   0 -> Normal use.
            1 -> A Low level is continually output on the UnTx signal, after
                completing transmission of the current character. For the proper
                execution of the break command, software must set this bit for
                at least two frames (character periods).
        * */


#define UART_CTL              0x00000030    /* UART Control*/

    #define CTSEN 15        /*Enable Clear To Send*/
    /*
    *   0 ->  CTS hardware flow control is disabled.
        1 ->  CTS hardware flow control is enabled. Data is only transmitted
              when the U1CTS signal is asserted.
    */

    #define RTSEN 14        /*Enable Request to Send*/
    /*
    *   0 -> RTS hardware flow control is disabled.
        1 -> RTS hardware flow control is enabled. Data is only requested
            (by asserting U1RTS) when the receive FIFO has available entries.
    * */

    #define RTS 11          /*Request to Send*/
    /*
    *   When RTSEN is clear, the status of this bit is reflected on the U1RTS
        signal. If RTSEN is set, this bit is ignored on a write and should be ignored on read.
    * */

    #define RXE 9           /*UART Receive Enable*/
    /*
    *   0 -> The receive section of the UART is disabled.
        1 -> The receive section of the UART is enabled.
    * */

    #define TXE 8           /*UART Transmit Enable*/
    /*
    *   0 -> The transmit section of the UART is disabled.
        1 -> The transmit section of the UART is enabled.
    * */
    #define LBE 7           /*UART Loop Back Enable*/
    /*
    *   0 -> Normal operation.
        1 -> The UnTx path is fed through the UnRx path.
    * */

    #define HSE 5           /*High-Speed Enable*/
    /*
    *   0 -> The UART is clocked using the system clock divided by 16.
        1 -> The UART is clocked using the system clock divided by 8.
    * */

    #define EOT 4           /*End of Transmission*/
    /*
    *   0 -> The TXRIS bit is set when the transmit FIFO condition specified in UARTIFLS is met.
        1 -> The TXRIS bit is set only after all transmitted data, including
             stop bits, have cleared the serializer.
    * */

    #define SMART 3         /*ISO 7816 Smart Card Support*/
    /*
    *    0 -> Normal operation.
    *    1 -> The UART operates in Smart Card mode.
    * */

    #define SIRLP 2         /*UART SIR Low-Power Mode*/
    /*
    *       
    *   0 ->    Low-level bits are transmitted as an active High pulse with a
                width of 3/16th of the bit period.

        1 ->    The UART operates in SIR Low-Power mode. Low-level bits
                are transmitted with a pulse width which is 3 times the period
                of the IrLPBaud16 input signal, regardless of the selected bit rate.
    * */

    #define SIREN 1         /*UART SIR Enable*/
    /*
    *   0 -> Normal operation.
        1 -> The IrDA SIR block is enabled, and the UART will transmit and
            receive data using SIR protocol.
    * */

    #define UARTEN 0        /*UART Enable*/
    /*
    *   0 -> The UART is disabled.
        1 -> The UART is enabled.
    * */

#define UART_IFLS             0x00000034    /* UART Interrupt FIFO Level Select*/
    
    #define RXIFLSEL2 5
    #define RXIFLSEL1 4
    #define RXIFLSEL0 3         /*
                                *   0x0 RX FIFO ≥ ⅛ full
                                *    0x1 RX FIFO ≥ ¼ full
                                *    0x2 RX FIFO ≥ ½ full (default)
                                *    0x3 RX FIFO ≥ ¾ full
                                *   0x4 RX FIFO ≥ ⅞ full
                                * */

    #define TXIFLSEL2 2
    #define TXIFLSEL1 1
    #define TXIFLSEL0 0         /*
                                *   0x0 TX FIFO ≤ ⅞ empty
                                *   0x1 TX FIFO ≤ ¾ empty
                                *   0x2 TX FIFO ≤ ½ empty (default)
                                *   0x3 TX FIFO ≤ ¼ empty
                                *   0x4 TX FIFO ≤ ⅛ empty
                                * */


#define UART_IM               0x00000038    /* UART Interrupt Mask*/
    #define NINEBITIM 12    /*9-Bit Mode Interrupt Mask 0 -> Masked , 1-> not masked*/
    #define OEIM 10         /*UART Overrun Error Interrupt Mask*/
    #define BEIM 9          /*UART Break Error Interrupt Mask*/
    #define PEIM 8          /*UART Parity Error Interrupt Mask*/
    #define FEIM 7          /*UART Framing Error Interrupt Mask*/
    #define RTIM 6          /*UART Receive Time-Out Interrupt Mask*/
    #define TXIM 5          /*UART Transmit Interrupt Mask*/
    #define RXIM 4          /*UART Receive Interrupt Mask*/
    #define CTSIM 1         /*UART Clear to Send Modem Interrupt Mask*/

#define UART_RIS              0x0000003C    /* UART Raw Interrupt Status*/
    #define NINEBITIS 12    /*9-Bit Mode Interrupt Status */
    #define OEIS 10         /*UART Overrun Error Interrupt Status*/
    #define BEIS 9          /*UART Break Error Interrupt Status*/
    #define PEIS 8          /*UART Parity Error Interrupt Status*/
    #define FEIS 7          /*UART Framing Error Interrupt Status*/
    #define RTIS 6          /*UART Receive Time-Out Interrupt Status*/
    #define TXIS 5          /*UART Transmit Interrupt Status*/
    #define RXIS 4          /*UART Receive Interrupt Status*/
    #define CTSIS 1         /*UART Clear to Send Modem Interrupt Status*/

#define UART_MIS              0x00000040    /* UART Masked Interrupt Status*/

#define UART_ICR              0x00000044    /* UART Interrupt Clear (((WRITE 1 TO CLEAR)))*/
    #define NINEBITIC 12    /*9-Bit Mode Interrupt Clear */
    #define OEIC 10         /*UART Overrun Error Interrupt Clear*/
    #define BEIC 9          /*UART Break Error Interrupt Clear*/
    #define PEIC 8          /*UART Parity Error Interrupt Clear*/
    #define FEIC 7          /*UART Framing Error Interrupt Clear*/
    #define RTIC 6          /*UART Receive Time-Out Interrupt Clear*/
    #define TXIC 5          /*UART Transmit Interrupt Clear*/
    #define RXIC 4          /*UART Receive Interrupt Clear*/
    #define CTSIC 1         /*UART Clear to Send Modem Interrupt Clear*/

#define UART_DMACTL           0x00000048    /* UART DMA Control*/
#define UART_9BITADDR         0x000000A4    /* UART 9-Bit Self Address*/
#define UART_9BITAMASK        0x000000A8    /* UART 9-Bit Self Address Mask*/
#define UART_PP               0x00000FC0    /* UART Peripheral Properties*/
#define UART_CC               0x00000FC8    /* UART Clock Configuration*/


            

#define RCGCUART 0x618      /*Run mode clock generation*/
 


#endif
