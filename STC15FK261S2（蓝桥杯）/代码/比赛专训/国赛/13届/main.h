#ifndef __MAIN_H
#define __MAIN_H
#include <STC15F2K60S2.H>
#include "Define.h"
#include "HC573.h"
#include "KEY.h"
#include "Timer.h"
#include "PCF8591.h"
#include "AT24C02.h"
#include "Sonic.h"
#include "Delay.h"
/*SMG����:0-F*/
uc code Nodot_SMG[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};	
uc code dot_SMG[]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10,0x08,0x03,0x46,0x21,0x06,0x0e};

#endif