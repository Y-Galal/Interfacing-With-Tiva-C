#ifndef PLL_H
#define PLL_H
#include "macros.h"
#include "pll_registers.h"
#include "std_types.h"

typedef enum 
{
    CLK_80 = 0x1000000,
    CLK_50 = 0x1C00000,
    CLK_40 = 0x2400000
}Clock_Select;

void PLL_setClock(Clock_Select Speed);


#endif

