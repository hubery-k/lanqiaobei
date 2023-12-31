/*******************************************************************************  
* 文件名称：数码管控制实验
* 实验目的：1.掌握数码管动态扫描的基本原理,掌握数码管消除“鬼影”的方法
*           2.掌握51单片机定时器工作模式和配置方法
*           3.掌握keil uvision集成开发环境下，中断服务函数设计方法
* 程序说明：无
* 日期版本：2012-9-4/V1.0a 
*******************************************************************************/

#include "reg52.h"  //定义51单片机特殊功能寄存器
#include "absacc.h"
                           //  0    1    2    3    4    5    6    7    8    9
code unsigned char tab[] = { 0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char dspbuf[8] = {1,2,3,4,5,6,7,8};  //显示缓冲区
unsigned char dspcom = 0;

void display(void);

//主函数
void main(void)
{ 
    TMOD |= 0x01;  //配置定时器工作模式
    TH0 = (65536-2000)/256;
    TL0 = (65536-2000)%256;  
    EA = 1;
    ET0 = 1;  //打开定时器中断
    TR0 = 1;  //启动定时器
    
    while(1)
    {
		//更新数据缓冲区
		;
    }
}

//定时器中断服务函数
void isr_timer_0(void)  interrupt 1  //默认中断优先级 1
{
    TH0 = (65536-2000)/256;
    TL0 = (65536-2000)%256;  //定时器重载 
     
	display();  //2ms执行一次
}

//显示函数
void display(void)
{   
	XBYTE[0xE000] = 0xff;  //消隐
	
	XBYTE[0xC000] = (1<<dspcom);
    XBYTE[0xE000] = tab[dspbuf[dspcom]]; //段码
   
    if(++dspcom == 8){
        dspcom = 0;
    }   
}