#ifndef INTERRUPT_REGISTERS_H
#define INTERRUPT_REGISTERS_H

#define NVIC 0xE000E000     /*Nested Vector Interrupt controller*/

/*Interrupt enable*/
#define EN0 0x100
#define EN1 0x104
#define EN2 0x108
#define EN3 0x10C
#define EN4 0x110

/*Interrupt Disable*/

#define DIS0 0x200
#define DIS1 0x204
#define DIS2 0x208
#define DIS3 0x20C
#define DIS4 0x210





#endif