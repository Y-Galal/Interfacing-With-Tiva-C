#ifndef INTERNAL_EEPROM_REGISTERS_H
#define INTERNAL_EEPROM_REGISTERS_H



#define EEPROM 0x400AF000           /* Internal EEPROM Base Address*/

#define SYSTEM_CONTROL 0x400FE000   /*System control register*/
#define RCGCEEPROM 0x658            /*EEPROM Clock Gating Control offset*/
#define SREEPROM 0x558

#define EESIZE 0x000                
/*The EESIZE register indicates the number of 16-word blocks and 32-bit words in the EEPROM.*/

#define EEBLOCK 0x004       /*EEPROM Current Block*/
/*The EEBLOCK register is used to select the EEPROM block for subsequent reads, writes, and
protection control.*/

#define EEOFFSET 0x008      /*EEPROM Current Offset */
/*The EEOFFSET register is used to select the EEPROM word to read or write within the block
selected by the EEBLOCK register.*/

#define EERDWR 0x010        /*EEPROM Read-Write*/
/*The EERDWR register is used to read or write the EEPROM word at the address pointed to by the
EEBLOCK and EEOFFSET registers.*/

#define EERDWRINC 0x014     /*EEPROM Read-Write with Increment*/
/*The EERDWRINC register is used to read or write the EEPROM word at the address pointed to by
the EEBLOCK and EEOFFSET registers, and then increment the OFFSET field in the EEOFFSET
register.*/

#define EEDONE 0x018        /*EEPROM Done Status*/
/*The EEDONE register indicates the successful or failed completion of the operations*/
    #define WRBUSY 5    /*Write Busy, 0-> No error, 1-> Error*/
    #define NOPERM 4    /*trying to access a locked block, no permission error*/
    #define WKCOPY 3    /*Working on a Copy, 1-> A write is in progress and is waiting for the EEPROM to copy*/
                            /*to or from the copy buffer.*/
    #define WKERASE 2   /*Working on an erase*/
    #define WORKING 0   /*EEPROM Working, 1-> it's working on your requested operation*/

#define EESUPP 0x01C        /*EEPROM Support Control and Status*/

#define EEUNLOCK 0x020      /*EEPROM Unlock */
/*The EEUNLOCK register can be used to unlock the whole EEPROM or a single block using a
password. you can unlock a block using EEPASS registers*/

#define EEPROT 0x030        /*EEPROM Protection*/
/*The EEPROT register is used to set or read the protection for the current block, as selected by the
EEBLOCK register.*/
    #define PROT0 0x00      /*If there is no password, the block is not protected and is readable and writable */
                            /*If there is a password, the block is readable, but only writable When unlocked.*/
    #define PROT1 0x01      /*If there is a password, the block is readable or writable only when unlocked.*/       
    #define PROT2 0x02      /*If there is no password, the block is readable, not writable.*/
                            /*If there is a password, the block is readable only when unlocked,
                                    but is not writable under any conditions.*/

#define EEPASS0 0x034
#define EEPASS1 0x038
#define EEPASS2 0x03C
        /*The EEPASSn registers are used to configure a password for a block. A password may only be set
        once and cannot be changed. The password may be 32-bits, 64-bits, or 96-bits. Each word of the
        password can be any 32-bit value other than 0xFFFF.FFFF (all 1s). To set a password, the EEPASS0
        register is written to with a value other than 0xFFFF.FFFF. When the write completes, as indicated
        in the EEDONE register, the application may choose to write to the EEPASS1 register with a value
        other than 0xFFFF.FFFF. When that write completes, the application may choose to write to the
        EEPASS2 register with a value other than 0xFFFF.FFFF to create a 96-bit password. The registers
        do not have to be written consecutively, and the EEPASS1 and EEPASS2 registers may be written
        at a later date. Based on whether 1, 2, or all 3 registers have been written, the unlock code also
        requires the same number of words to unlock*/

#define  EEINT 0x040    /*EEPROM Interrupt*/
/*The EEINT register is used to control whether an interrupt should be generated when a write to
EEPROM completes as indicated by the EEDONE register value changing from 0x1 to any other
value. If the INT bit in this register is set, the ERIS bit in the Flash Controller Raw Interrupt Status
(FCRIS) register is set whenever the EEDONE register value changes from 0x1 as the Flash memory
and the EEPROM share an interrupt vector.*/

#define EEHIDE 0x050    /*EEPROM Block Hide*/
/*The EEHIDE register is used to hide one or more blocks other than block 0.*/
/*  0-> The corresponding block is not hidden.
    1-> The block number that corresponds to the bit number is hidden.
        A hidden block cannot be accessed, and the OFFSET value in
        the EEBLOCK register cannot be set to that block number. If
        an attempt is made to configure the OFFSET field to a hidden
        block, the EEBLOCK register is cleared.
        Any attempt to clear a bit in this register that is set is ignored.*/



#endif
