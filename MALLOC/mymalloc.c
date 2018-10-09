/*-------------------------------------------------*/
/*         超纬电子STM32F407ZGT6开发板             */
/*    淘宝地址： http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*            动态分配内存源文件,有3个函数         */
/*-------------------------------------------------*/
/* void mymen_Init(void);                          */
/* void *mymalloc(uint32_t size);                  */
/* void *myfree(void *p);                          */
/*-------------------------------------------------*/

#include "mymalloc.h"

#define   MEM_BLOCK_NUM   200           //内存块数量
#define   MEM_BLOCK_SIZE  128           //内存块大小
 
uint8_t   MEM_BUFF[MEM_BLOCK_NUM][MEM_BLOCK_SIZE];    //定义内存池
MEM_BCT   MEM_BCT_TAB[MEM_BLOCK_NUM];                 //内存块管理表，一个数组

/*-------------------------------------------------*/
/*函数名：初始化内存管理表                         */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void mymen_Init(void)                      
{
    uint32_t i;
	for(i=0;i<MEM_BLOCK_NUM;i++)           //遍历整个内存管理表
	{
		MEM_BCT_TAB[i].mem_state=0;        //内存块状态设置为可用
		MEM_BCT_TAB[i].num=0;              //占用连续内存块为0
	}
}

/*-------------------------------------------------*/
/*函数名：申请内存                                 */
/*参  数：size:内存大小                            */
/*返回值：分配到的内存的指针，空间不够返回空指针   */
/*-------------------------------------------------*/
void *mymalloc(uint32_t size)
{
	uint32_t num;                            //num存放需要申请的内存块数目
	uint32_t i;                              //for循环使用
	uint32_t start_N0=MEM_BLOCK_NUM;         //找到的空闲的内存块编码
	uint32_t start_flag=0;                   //找到的连续内存块的数量
	
	if((size%MEM_BLOCK_SIZE)!=0)
	{
		num=(uint32_t)((size/MEM_BLOCK_SIZE)+1); //计算需要多少内存块
	}
	else
	{
		num=(uint32_t)((size/MEM_BLOCK_SIZE)); //计算需要多少内存块
	}
	
	for(i=0;i<MEM_BLOCK_NUM;i++)             //遍历整个内存管理表
	{
		if(MEM_BCT_TAB[i].mem_state==0)      //查看当前内存块是否可用，可用的话if成立，有可用额内存
		{   
			start_N0=i;                      //记录下当前可用的内存编号
			start_flag++;                    //找到连续内存块的数量+1              
		}
		else                                 //查看当前内存块是否可用，不可用的话else成立
		{
			start_N0=MEM_BLOCK_NUM;          //清除当前可用的内存编号
			start_flag=0;                    //清除找到连续内存块的数量
		}
		if(start_flag==num)                  //判断，一旦符合数量要求的连续内存块，就跳出for循环
		{
			break;
		}
	}
	if(start_flag!=num)                      //判断for循环是如何结束的
	{
		return (void*)0;                     //如果找到连续内存块的数量！=num，也就是没有足够的连续内存卡可供申请了，返回空指针
    }
	else                                     //如个start_flag==num，也就是说找到了足够的连续内存块
	{
		for(i=(start_N0+1);i>(start_N0+1-num);i--)   //变量找到的连续内存块
		{
			MEM_BCT_TAB[i-1].mem_state=1;      //将这些内存块状态置1，表示被占用了
		}
		MEM_BCT_TAB[start_N0+1-num].num=num;     //在连续内存块的第一个内存块中标记，连续占用了几个内存块
		return (void *)(MEM_BUFF[start_N0+1-num]);            //返回第一个内存块地址
	}
}

/*-------------------------------------------------*/
/*函数名：释放内存                                 */
/*参  数：*p:指向要释放的内存的指针                */
/*返回值： 返回空指针                              */
/*-------------------------------------------------*/
void *myfree(void *p)
{
	uint32_t number,i;
	u8 *q = p;
	
	number=(uint32_t)((q-MEM_BUFF[0])/MEM_BLOCK_SIZE);     //计算是几个内存块
	for(i=number;i<(MEM_BCT_TAB[number].num+number);i++)   //利用for循环清除状态
	{
		MEM_BCT_TAB[i].mem_state=0;   //清除占用状态
	}
	MEM_BCT_TAB[number].num=0;        
	
	return (void *)0;	
}
