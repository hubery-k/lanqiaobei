/*******************************************************************************  
* 文件名称：ADC转换实验
* 实验目的：1.掌握I2C总线通讯基本特点和工作时序
*           2.掌握51单片机模拟I2C总线时序的程序设计方法
*           3.掌握PCF8591 ADC芯片的操作方法
* 程序说明：1.使用程序前在 Preprocessor Symbols 中增加宏定义ADC_PCF8591
*           2.调节电位器Rb2，观察数码管显示情况
* 硬件环境：IAP15F2K61S2@11.0592MHz
* 日期版本：2012-9-5/V1.0a 
*******************************************************************************/

#include "reg52.h"  //定义51单片机特殊功能寄存器
#include "i2c.h"    //I2C总线驱动库 
#include "absacc.h"

sfr AUXR = 0x8E; 	//IAP15F2K61S2单片机特殊功能寄存器

code unsigned char tab[] = { 0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,
                             0xff
                           };
unsigned char dspbuf[8] = {10,10,10,10,10,10,10,10};  //显示缓冲区
unsigned char dspcom = 0;
unsigned char intr;
bit adc_flag;

void display(void);

void cls_buzz()
{
	XBYTE[0xA000] = 0;
}
void cls_led()
{
	XBYTE[0x8000] = 0xFF;
}

//主函数
void main(void)
{ 
    unsigned char adc_value;  //ADC转换数据 
	
	cls_buzz();cls_led();
	P1 &= 0x7f;
		
	AUXR |= 0x80;
	TMOD &= 0xF0;
	TL0 = 0xCD;	
	TH0 = 0xD4;	
	TF0 = 0;	
	TR0 = 1;
	ET0 = 1;
	EA = 1;

	init_pcf8591();  //PCF8591初始化      
    
    while(1)
    {
		if(adc_flag)
		{
			adc_flag = 0;  //清除ADC扫描标志位 
			adc_value = adc_pcf8591();
			//更新显示数据
			(adc_value>= 100)?(dspbuf[5] = adc_value/100):(dspbuf[5] = 10);       
			(adc_value>=10)?(dspbuf[6] = adc_value%100/10):(dspbuf[6] = 10);       
			dspbuf[7] = adc_value%10; 
		}
    }
}

//定时器中断服务函数
void isr_timer_0(void)  interrupt 1  //默认中断优先级 1
{
    if(++intr == 50)
	{
		intr = 0;
		adc_flag = 1;
	} 
    display();
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