#ifndef __ONEWIRE_H
#define __ONEWIRE_H

#include <STC15F2K60S2.H>
sbit DQ = P1^4;  

bit init_ds18b20(void);
unsigned char Read_DS18B20(void);
void Write_DS18B20(unsigned char dat); 

#endif
