#include "Timer.h"

/*使用12MHz晶振，1us就是一个机器周期（使用12T模式不倍速）*/
/*在12MHz晶振下，1个时钟周期是1/12us，在传统的51单片机中机械周期的时序由12个时钟周期组成(12T)，一个机械周期就是1us。
	如果使用定时器1T模式的话，一个时钟周期就是一个机械周期为1/12us（这也就是为什么这款比传统51运行速度快了12倍）*/
	
void Timer0Init(void)		//0微秒@12.000MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x00;		//设置定时初值
	TH0 = 0x00;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 0;		//定时器0等待开始计时
	/*不需要打开中断，只是利用定时器计时*/
}
void Timer1Init(void)		//1毫秒@12.000MHz
{
	AUXR |= 0x40;		//定时器时钟1T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0x20;		//设置定时初值
	TH1 = 0xD1;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	ET1=1;
	EA=1;
}
