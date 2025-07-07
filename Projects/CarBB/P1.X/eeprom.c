/*
 * File:   eeprom.c
 * Author: Rahul H H
 *
 * Created on March 5, 2025, 9:53 PM
 */


#include <xc.h>
#include "p1.h"

// function to write data to eeprom using address
void internal_eeprom_write(unsigned char addr, unsigned char data)
{
    EEDATA = data; // loading the data to be stored in eeprom 
    EEADR = addr; // loading the address to where data to be loaded
    
    EEPGD = 0; // selecting eeprom
    CFGS =0;
    
    WREN =1; // enabling write operation
    GIE =0; // disabling the interrupt 
    
    // making the required sequence for writing
    EECON2 = 0x55;
    EECON2 = 0xaa;
    
    WR =1; // initializing write operation
    GIE =1; // enabling interrupt
    
    while(WR); // automatically after writing wr will become 0 , so waiting till wr become 0
    
}


// function to read data from eeprom using address
unsigned char internal_eeprom_read(unsigned char addr)
{
    EEADR = addr; // loading the address to eeadr
    
    EEPGD =0; // selecting eeprom
    CFGS = 0;
    
    WREN =0; // enabling read operation
    
    RD =1; // initializing read operation
    
    return EEDATA; // returning the data from the address eeadr
}
