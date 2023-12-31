/*******************************************************************************  
* 文件名称：DS18B20温度传感器实验
* 实验目的：1.掌握单总线通讯基本特点和工作时序
*           2.掌握51单片机模拟单总线时序的程序设计方法
*           3.掌握DS18B20温度传感器的操作方法
* 程序说明：1.通过数码管显示实时温度数据
*           2.DS18B20数据线引脚DQ与单片机P1.4引脚连接
*           3.测量精度为1摄氏度
*           4.数码管驱动函数采用IO方式编写，将跳线J13调整为IO模式
* 日期版本：2012-9-5/V1.0a 
*******************************************************************************/

#include "reg52.h"  //定义51单片机特殊功能寄存器
#include "onewire.h"  //单总线函数库
#include "absacc.h"

unsigned char dspbuf[8] = {10,10,10,10,10,10,0,0};//显示缓冲区
unsigned char dspcom = 0;
unsigned char intr;
bit temper_flag = 0;//温度读取标志
code unsigned char tab[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,
                            0xff};

void display(void);

//主函数
void main(void)
{ 
    unsigned char temperature;
    
    TMOD |= 0x01;  //配置定时器工作模式
    TH0 = (65536-2000)/256;
    TL0 = (65536-2000)%256;  
    EA = 1;
    ET0 = 1;  //打开定时器中断
    TR0 = 1;  //启动定时器
	
    while(1)
    {
        if(temper_flag)
		{
			temper_flag = 0;
			temperature = rd_temperature();  //读温度         
        }
		
		//显示数据更新    
		dspbuf[6] = temperature/10;       
		dspbuf[7] = temperature%10; 
    }
}

//定时器中断服务函数
void isr_timer_0(void)  interrupt 1  //默认中断优先级 1
{
    TH0 = (65536-2000)/256;
    TL0 = (65536-2000)%256;  //定时器重载  
    display();
	if(++intr == 100)  //2ms执行一次
	{
        intr = 0;
		temper_flag = 1;  //200ms温度读取标志位置1
    }
}

//显示函数
void display(void)
{   
	P2 = ((P2&0x1f)|0xE0); 
	P0 = 0xff;
	P2 &= 0x1f;

	P2 = ((P2&0x1f)|0xC0); 
	P0 = 1<<dspcom;
	P2 &= 0x1f;
	
    P2 = ((P2&0x1f)|0xE0); 
	P0 = tab[dspbuf[dspcom]];
	P2 &= 0x1f;
  
    if(++dspcom == 8){
        dspcom = 0;
    }    
}