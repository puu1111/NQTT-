/*-------------------------------------------------*/
/*         ��γ����STM32F407ZGT6������             */
/*    �Ա���ַ�� http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/

#ifndef _MY_MALLOC_
#define _MY_MALLOC_

#include "main.h"

typedef struct           //����һ���ڴ�����ṹ��
{
	uint8_t  mem_state;  //��ǰ��Ӧ�ڴ濨��״̬  0 ����  1��ռ��
	uint8_t  num;        //����ռ�õ��ڴ������ 
}MEM_BCT;

void mymen_Init(void);            //��ʼ���ڴ�����
void *mymalloc(uint32_t size);    //�����ڴ�  
void *myfree(void *p);            //�ͷ��ڴ�
 
#endif
