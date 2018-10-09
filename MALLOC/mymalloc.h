/*-------------------------------------------------*/
/*         超纬电子STM32F407ZGT6开发板             */
/*    淘宝地址： http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/

#ifndef _MY_MALLOC_
#define _MY_MALLOC_

#include "main.h"

typedef struct           //定义一个内存块管理结构体
{
	uint8_t  mem_state;  //当前对应内存卡的状态  0 可用  1被占用
	uint8_t  num;        //连续占用的内存块数量 
}MEM_BCT;

void mymen_Init(void);            //初始化内存管理表
void *mymalloc(uint32_t size);    //申请内存  
void *myfree(void *p);            //释放内存
 
#endif
