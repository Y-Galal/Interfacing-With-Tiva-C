#include "internal_eeprom.h"

/*********************      Public functions      *********************/
/*
    Function Name: EEPROM_init
    Description: This function initializes the internal EEPROM
*/
void EEPROM_init()
{
    asm(" NOP");
    asm(" NOP");
    SET_BIT(SYSTEM_CONTROL,RCGCEEPROM,0);   /*Enabling the clock to the module*/
    asm(" NOP");    /*Inserting a delay for 6 cycles using assembly language*/
    asm(" NOP");
    asm(" NOP");
    asm(" NOP");
    asm(" NOP");
    asm(" NOP");

    while( BIT_IS_SET(EEPROM,EEDONE,WORKING) ){}
                /*Waiting untill the Working flag is 0 to indicate that the eeprom is working */
    SET_BIT(SYSTEM_CONTROL,SREEPROM,0);
    asm(" NOP");    /*Inserting a delay for 6 cycles using assembly language*/
    asm(" NOP");
    asm(" NOP");
    asm(" NOP");
    asm(" NOP");
    asm(" NOP");
    
    CLEAR_BIT(SYSTEM_CONTROL,SREEPROM,0);
    while( BIT_IS_SET(EEPROM,EEDONE,WORKING) ){}
            /*Waiting untill the Working flag is 0 to indicate that the eeprom finished working */
    
}
/*
    Function Name: EEPROM_writeData
    Description: This function writes a 32-bit data in the requested address (block+offset)
*/
void EEPROM_writeData(uint16 block, uint8 offset,uint32 data)
{
    ACCESS_REG(EEPROM,EEBLOCK) = block; /*selecting the block*/
    ACCESS_REG(EEPROM,EEOFFSET)= offset; /*selecting the offset*/
    ACCESS_REG(EEPROM,EERDWR) = data;    /*writing the data*/
    while(BIT_IS_SET(EEPROM,EEDONE,WKCOPY));
}
/*
    Function Name: EEPROM_readData
    Description: this function reads the data from a specific address (block+offset)
*/
void EEPROM_readData(uint16 block, uint8 offset,uint32 *data)
{
    ACCESS_REG(EEPROM,EEBLOCK) = block; /*selecting the block*/
    ACCESS_REG(EEPROM,EEOFFSET)= offset; /*selecting the offset*/
    *data = ACCESS_REG(EEPROM,EERDWR);    /*writing the data*/
    while(BIT_IS_SET(EEPROM,EEDONE,WORKING));
}
/*
    Function Name: EEPROM_writeDataWithInc
    Description: This function writes a 32-bit data in the requested address and then 
                increments the offset register by 1 (to be used in loops)
*/
void EEPROM_writeDataWithInc(uint16 block,uint32 data)
{
    ACCESS_REG(EEPROM,EEBLOCK) = block; /*selecting the block*/
    ACCESS_REG(EEPROM,EERDWRINC) = data;    /*writing the data*/
    while(BIT_IS_SET(EEPROM,EEDONE,WKCOPY));  /*waiting to write in the EEPROM*/
}

/*
    Function Name: EEPROM_readDataWithInc
    Description: This function reads a 32-bit data from the requested address and then 
                increments the offset register by 1 (to be used in loops)
*/
void EEPROM_readDataWithInc(uint16 block,uint32 *data)
{
    ACCESS_REG(EEPROM,EEBLOCK) = block; /*selecting the block*/
    *data = ACCESS_REG(EEPROM,EERDWRINC);    /*writing the data then increment the offset*/
    while(BIT_IS_SET(EEPROM,EEDONE,WORKING));   /*Waiting to read successfully*/
}

/*
    Function Name: EEPROM_setOffset
    Description: This function sets the offset needed to write/read data from it
*/
void EEPROM_setOffset(uint8 offset)
{
    if(offset <=16) /*Offset must be between 0 to 16*/
    {
        ACCESS_REG(EEPROM,EEOFFSET)= offset; /*selecting the offset*/
    }
}