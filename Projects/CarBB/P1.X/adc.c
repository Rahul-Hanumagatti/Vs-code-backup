
#include <xc.h>
#include "p1.h"

void init_adc(void)
{
    // ADCON0 CONFIGURATION
    
    CHS3 =0;
    CHS2 =1;  // Selected the AN4 channel
    CHS1 =0;
    CHS0 =0;
    
    ADON =1; //  ADC enabled
    
    GO =0; // no conversion enabled initially
    
    // ADCON1
    
    VCFG1 =0; // no reference voltage needed  i.e, 0 - 5v
    VCFG0 =0;
    
    PCFG3 =1;
    PCFG2 =0;
    PCFG1 =1;  // making only  AN4  Channel as analog channel
    PCFG0 =0;
    
    // ADCON2
    
    ADFM =1; // RIGHT JUSTIFIED
    
    ADCS2 =0;
    ADCS1 =1; // CLOCK SPEED OF 0.625 MHZ
    ADCS0 =0;
    
    ACQT2 = 1;
    ACQT2 = 0; // 8 TAD (12.86 micro seconds of ACQ TIME)
    ACQT2 = 0;
    
    
}

unsigned short read_adc(void)
{
    // start conversion
    GO =1;
    
    // wait till conversion complete
    while(GO);
    
    // read / fetch value from adc registers
    return (ADRESH << 8)| ADRESL;
}
