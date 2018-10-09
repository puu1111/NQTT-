/*-------------------------------------------------*/
/*         ��γ����STM32F407ZGT6������             */
/*    �Ա���ַ�� http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*            ��̬�����ڴ�Դ�ļ�,��3������         */
/*-------------------------------------------------*/
/* void mymen_Init(void);                          */
/* void *mymalloc(uint32_t size);                  */
/* void *myfree(void *p);                          */
/*-------------------------------------------------*/

#include "mymalloc.h"

#define   MEM_BLOCK_NUM   200           //�ڴ������
#define   MEM_BLOCK_SIZE  128           //�ڴ���С
 
uint8_t   MEM_BUFF[MEM_BLOCK_NUM][MEM_BLOCK_SIZE];    //�����ڴ��
MEM_BCT   MEM_BCT_TAB[MEM_BLOCK_NUM];                 //�ڴ������һ������

/*-------------------------------------------------*/
/*����������ʼ���ڴ�����                         */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void mymen_Init(void)                      
{
    uint32_t i;
	for(i=0;i<MEM_BLOCK_NUM;i++)           //���������ڴ�����
	{
		MEM_BCT_TAB[i].mem_state=0;        //�ڴ��״̬����Ϊ����
		MEM_BCT_TAB[i].num=0;              //ռ�������ڴ��Ϊ0
	}
}

/*-------------------------------------------------*/
/*�������������ڴ�                                 */
/*��  ����size:�ڴ��С                            */
/*����ֵ�����䵽���ڴ��ָ�룬�ռ䲻�����ؿ�ָ��   */
/*-------------------------------------------------*/
void *mymalloc(uint32_t size)
{
	uint32_t num;                            //num�����Ҫ������ڴ����Ŀ
	uint32_t i;                              //forѭ��ʹ��
	uint32_t start_N0=MEM_BLOCK_NUM;         //�ҵ��Ŀ��е��ڴ�����
	uint32_t start_flag=0;                   //�ҵ��������ڴ�������
	
	if((size%MEM_BLOCK_SIZE)!=0)
	{
		num=(uint32_t)((size/MEM_BLOCK_SIZE)+1); //������Ҫ�����ڴ��
	}
	else
	{
		num=(uint32_t)((size/MEM_BLOCK_SIZE)); //������Ҫ�����ڴ��
	}
	
	for(i=0;i<MEM_BLOCK_NUM;i++)             //���������ڴ�����
	{
		if(MEM_BCT_TAB[i].mem_state==0)      //�鿴��ǰ�ڴ���Ƿ���ã����õĻ�if�������п��ö��ڴ�
		{   
			start_N0=i;                      //��¼�µ�ǰ���õ��ڴ���
			start_flag++;                    //�ҵ������ڴ�������+1              
		}
		else                                 //�鿴��ǰ�ڴ���Ƿ���ã������õĻ�else����
		{
			start_N0=MEM_BLOCK_NUM;          //�����ǰ���õ��ڴ���
			start_flag=0;                    //����ҵ������ڴ�������
		}
		if(start_flag==num)                  //�жϣ�һ����������Ҫ��������ڴ�飬������forѭ��
		{
			break;
		}
	}
	if(start_flag!=num)                      //�ж�forѭ������ν�����
	{
		return (void*)0;                     //����ҵ������ڴ���������=num��Ҳ����û���㹻�������ڴ濨�ɹ������ˣ����ؿ�ָ��
    }
	else                                     //���start_flag==num��Ҳ����˵�ҵ����㹻�������ڴ��
	{
		for(i=(start_N0+1);i>(start_N0+1-num);i--)   //�����ҵ��������ڴ��
		{
			MEM_BCT_TAB[i-1].mem_state=1;      //����Щ�ڴ��״̬��1����ʾ��ռ����
		}
		MEM_BCT_TAB[start_N0+1-num].num=num;     //�������ڴ��ĵ�һ���ڴ���б�ǣ�����ռ���˼����ڴ��
		return (void *)(MEM_BUFF[start_N0+1-num]);            //���ص�һ���ڴ���ַ
	}
}

/*-------------------------------------------------*/
/*���������ͷ��ڴ�                                 */
/*��  ����*p:ָ��Ҫ�ͷŵ��ڴ��ָ��                */
/*����ֵ�� ���ؿ�ָ��                              */
/*-------------------------------------------------*/
void *myfree(void *p)
{
	uint32_t number,i;
	u8 *q = p;
	
	number=(uint32_t)((q-MEM_BUFF[0])/MEM_BLOCK_SIZE);     //�����Ǽ����ڴ��
	for(i=number;i<(MEM_BCT_TAB[number].num+number);i++)   //����forѭ�����״̬
	{
		MEM_BCT_TAB[i].mem_state=0;   //���ռ��״̬
	}
	MEM_BCT_TAB[number].num=0;        
	
	return (void *)0;	
}
