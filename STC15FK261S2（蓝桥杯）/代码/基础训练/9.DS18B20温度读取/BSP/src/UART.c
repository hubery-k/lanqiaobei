#include "UART.h"


	/*一般来说，单片机给发送上位机发送数据，上位机可以实时接收，但如果上位机给单片机发送数据
	单片机此时正处于while循环中处理其他程序那么数据就接收不到了，所以接收数据需要串口中断
	当然也可以利用查询方式在while循环中不断查询是否有数据发送过来，当然这比较浪费CPU资源。*/

/******************串口1**********************/
/*串口1默认位置是P30和P31，可以通过PWS_1寄存器在P30、P31和P36、P37和P16、P17之间进行引脚切换。
蓝桥杯开发板上自带的CH340下载电路上连接的是P30和P31引脚，所以串口1配置完后可以直接与串口助手进行通信。*/
void UART_Init(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率(且开启了REN使能位)
	AUXR &= 0xBF;		//定时器时钟12T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xE8;		//设置定时初始值
	TH1 = 0xFF;		//设置定时初始值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时
	
	//清除中断标志位
	RI=0;
	//开中断
	ES=1;
	EA=1;
}
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);//等待数据发送完成TI由硬件置1
	TI=0;//需要软件清零
}

void UART_SendString(char *String)
{
	unsigned char i;
		for(i=0;String[i]!=0;i++)
		{	
			UART_SendByte(String[i]);
		}
}



//重定义putchar函数(为了使用printf函数)

char putchar(char ch)
{
    SBUF = ch;
    while(TI == 0);
    TI = 0;
    return ch;
}

/******************串口2**********************/
/*由于蓝桥杯单片机上串口下载的位置是P30和P31该位置是串口1的默认位置，所以配置串口1可以通过串口助手进行通信。
而串口2默认位置是P10和P11，通过P_SW2寄存器在P46、P47和P10、P11之间切换。
所以想要通过串口2通信需要另外连接CH340驱动芯片。*/
/*
void UART_Init(void)		//9600bps@11.0592MHz
{
	S2CON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xFB;		//定时器时钟12T模式
	T2L = 0xE8;		//设置定时初始值
	T2H = 0xFF;		//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时
	
	//清除中断标志位
	S2CON&=~0X01;
	//开中断
	IE2|=0X01;//开启ES2;（IE2不可位寻址）
	EA=1;
}

void UART_SendByte(unsigned char Byte)
{
	S2BUF=Byte;
	while((S2CON&0X02)==0);//等待数据发送完成TI由硬件置1
	S2CON&=~0X02;//需要软件清零
}

void UART_Routine(void) interrupt 8
{
	if(S2CON&0X01)
	{
		Data=S2BUF;
		UART_SendByte(Data);
		S2CON&=~0X01;
	}
}
*/
