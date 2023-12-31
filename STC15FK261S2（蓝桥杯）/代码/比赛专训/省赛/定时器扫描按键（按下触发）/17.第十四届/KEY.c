#include "KEY.h"

//#define set(x) P4=(x>>3)|(x>>4);P3=x
//#define get() ((P4&0X04)<<4)|((P4&0X10)<<3)|(P3&0X3F)

//static uc KeyNum;
//uc Trg,Cont;

//void KBD()
//{
//	uc Dat;
//	set(0X0F);
//	Dat=get();
//	set(0XF0);
//	Dat=(Dat|get())^0XFF;
//	Trg=Dat&(Dat^Cont);
//	Cont=Dat;
//}

//void KEY_Loop()
//{
//	KBD();
//	switch(Trg^0XFF)
//	{
//		case 0X77:KeyNum=4;break;//S4
//		case 0X7B:KeyNum=5;break;//S5
//		case 0XB7:KeyNum=8;break;//S8
//		case 0XBB:KeyNum=9;break;//S9
//	}
//}

//uc KEY()
//{
//	uc Temp;
//	Temp=KeyNum;
//	KeyNum=0;
//	return Temp;
//}
/*三行按键缺点：把所有矩阵按键IO联合，所有IO必须用到，不能屏蔽用不到的按键IO。例如P34引脚用来测量频率会相互影响*/

uc key_val;
uc Key_state;
void KBD()
{
	uc key_temp=0;
	uc key1,key2;
	
	P32=1;P33=1;P42=0;P44=0;
	if(P33==0)key1=0x07;
	if(P32==0)key1=0x0b;
	if(P33==1 && P32==1)key1=0x0f;
	
	P32=0;P33=0;P42=1;P44=1;
	if(P44==0)key2=0x70;
	if(P42==0)key2=0xb0;
	if(P44==1 && P42==1)key2=0xf0;
	key_temp=key1|key2;
	
	switch(Key_state)
	{
		case 0:
				if(key_temp!=0xff)Key_state=1;
			break;
		case 1:
				if(key_temp==0xff)Key_state=0;
				else 
				{
					switch(key_temp)
					{
						case 0X77:key_val=4;break;//S4
						case 0X7B:key_val=5;break;//S5
						case 0XB7:key_val=8;break;//S8
						case 0XBB:key_val=9;break;//S9
					}
					Key_state=2;
				}
			break;
		case 2:
				if(key_temp==0xff)
				{
					Key_state=0;
				}
			break;
	}
}

uc KEY()
{
	uc KeyNum;

	KBD();
	KeyNum=key_val;
	key_val=0;
	return KeyNum;
}