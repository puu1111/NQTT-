/*-------------------------------------------------*/
/*                    ��γ����                     */
/*    �Ա���ַ�� http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/

#ifndef __ADC_H
#define __ADC_H	

#include "main.h" 
							   
void Adc_Init(void); 				//��ʼ��ADC
u16  Get_Adc(u8 ch); 				//���ADC��� 
u16 Get_Adc_Average(u8 ch,u8 times);//ƽ�����ADC�������߾���

#endif 
