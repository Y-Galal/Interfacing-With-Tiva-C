#ifndef INTERNAL_EEPROM_H
#define INTERNAL_EEPROM_H

#include "macros.h"
#include "std_types.h"
#include "internal_eeprom_registers.h"

void EEPROM_init();
void EEPROM_writeData(uint16 block, uint8 offset,uint32 data);
void EEPROM_readData(uint16 block, uint8 offset,uint32 *data);

void EEPROM_setOffset(uint8 offset);

void EEPROM_writeDataWithInc(uint16 block,uint32 data);
void EEPROM_readDataWithInc(uint16 block,uint32 *data);



#endif
