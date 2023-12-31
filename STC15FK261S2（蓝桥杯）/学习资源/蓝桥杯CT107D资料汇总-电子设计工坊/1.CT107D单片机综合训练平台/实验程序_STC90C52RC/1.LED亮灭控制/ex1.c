/*******************************************************************************  
* 文件名称：LED闪烁实验
* 实验目的：1.掌握单片机IO口操作的基本方法
*           2.掌握软件延时函数的设计方法
* 程序说明：LED以0.2S为间隔亮灭(STC89C52RC单片机)
* 日期版本：2012-9-3/V1.0a 
*******************************************************************************/

#include "reg52.h"  //定义51单片机特殊功能寄存器

//延时函数
void delay(void)
{
    unsigned char i,j,k;
    for(i=0; i<20; i++)
    {
        for(j=0; j<20; j++)
        {
            for(k=0; k<248; k++);
        }
    } 
}

//主函数
void main(void)
{
    while(1)
    {
        P2 = ((P2&0x1f)|0x80);
		P0 = 0xff;  //LED熄灭
		P2 &= 0x1f;
        delay();
        
        P2 = ((P2&0x1f)|0x80);
		P0 = 0x00;  //LED点亮
		P2 &= 0x1f;
        delay();
    }
}