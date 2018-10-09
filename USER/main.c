/*-------------------------------------------------*/
/*                    ��γ����                     */
/*    �Ա���ַ�� http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/

#include "main.h"

char Data[1400] = {
"01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n"
"01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n"
"01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n"
"01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n"
"01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n"
"01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n"
"01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n"
"01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n"
"01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n"
"01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n"
"01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n""01234567890123456789\r\n"
};

u32 i=0;


int main(void)
{ 
//    float temp;
//	u8 i;
//	u8 ADc_Buff[200];
//	u8 ADc_temp[20];
	
	delay_init();		    //��ʱ��ʼ�� 
	Usart1_init(115200);	//���ڳ�ʼ��������Ϊ115200 
//	Adc_Init();             //��ʼ��ADC	
	
	while(SD_Init())                   //SD����ʼ��
	{
		printf("SD����ʼ������\r\n");  //������ʾSD����ʼ������
		delay_ms(200);                //��ʱ2s
	}
   printf("SD����ʼ���ɹ�\r\n");
	f_mount(&fs[0],"0:",1); 	                                            
	
  f_open(&nqttData_file,"0:/nqttData_file.txt",FA_OPEN_ALWAYS | FA_READ | FA_WRITE );//�������һ���ı��ĵ���������
	f_sync(&nqttData_file); 
  f_open(&nqttLen_file,"0:/nqttLen_file.txt",FA_OPEN_ALWAYS | FA_READ | FA_WRITE );//�������һ���ı��ĵ���������
	f_sync(&nqttLen_file); 
  f_open(&nqttRetry_file,"0:/nqttRetry_file.txt",FA_OPEN_ALWAYS | FA_READ | FA_WRITE );//�������һ���ı��ĵ���������
	f_sync(&nqttRetry_file); 
  f_open(&nqttSta_file,"0:/nqttSta_file.txt",FA_OPEN_ALWAYS | FA_READ | FA_WRITE );//�������һ���ı��ĵ���������
	f_sync(&nqttSta_file); 
  f_open(&nqttStarAddr_file,"0:/nqttStarAddr_file.txt",FA_OPEN_ALWAYS | FA_READ | FA_WRITE );//�������һ���ı��ĵ���������
	f_sync(&nqttStarAddr_file); 
	
	stuNQTT1.WU_Addr_MAX = SDCardInfo.CardCapacity / 2 ;
	
//	File_W(&nqttData_file,Data,0,44,&stuNQTT1.W_RealyNum);
//	File_W(&nqttLen_file,Data,0,55,&stuNQTT1.W_RealyNum);
//	File_W(&nqttRetry_file,Data,0,66,&stuNQTT1.W_RealyNum);
//	File_W(&nqttSta_file,Data,0,77,&stuNQTT1.W_RealyNum);
//	File_W(&nqttStarAddr_file,Data,0,88,&stuNQTT1.W_RealyNum);
	
	while(1) 
	{
				delay_ms(100);
		    for(i=0; i<200; i++)
				{
					nqtt_WrQue(i,Data,22);
					printf("˳��%d  ���ݣ�",i);
					delay_ms(10);
					nqtt_UpLoad(i,stuNQTT1.U_Data,&stuNQTT1.U_RealyNum);
					printf(stuNQTT1.U_Data);
				}
//			File_R(&nqttData_file,stuNQTT1.U_Data,0,88,&stuNQTT1.U_RealyNum);
//			memset(stuNQTT1.U_Data,0,strlen(stuNQTT1.U_Data));
//		
//			File_R(&nqttLen_file,stuNQTT1.U_Data,0,88,&stuNQTT1.U_RealyNum);
//			memset(stuNQTT1.U_Data,0,strlen(stuNQTT1.U_Data));
//		
//			File_R(&nqttRetry_file,stuNQTT1.U_Data,0,88,&stuNQTT1.U_RealyNum);
//			memset(stuNQTT1.U_Data,0,strlen(stuNQTT1.U_Data));
//		
//			File_R(&nqttSta_file,stuNQTT1.U_Data,0,88,&stuNQTT1.U_RealyNum);
//			memset(stuNQTT1.U_Data,0,strlen(stuNQTT1.U_Data));
//		
//			File_R(&nqttStarAddr_file,stuNQTT1.U_Data,0,88,&stuNQTT1.U_RealyNum);
//			memset(stuNQTT1.U_Data,0,strlen(stuNQTT1.U_Data));
		  
		
		
//		for(i=0;i<8;i++)
//		{
//			temp=(float)(Get_Adc_Average(i,20))*(3.3/4096);   //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//			printf("ͨ��%d=%f\r\n",i,temp);                   //���������Ϣ
//			sprintf((char *)ADc_temp,"%f|",temp);             //��ӡ��ʽ������Ϣ
//			strcat((char *)ADc_Buff,(char *)ADc_temp);	      //����д���ļ�������	
//		}
//		strcat((char *)ADc_Buff,"\r\n");                      //���ϻس�����

//		i = f_size(&ADC_file);
//		i = strlen((const char *)ADc_Buff);
//		f_lseek(&ADC_file,f_size(&ADC_file));                                    //��ָ�붨λ���ļ�β����׼��׷������
//		f_write(&ADC_file,ADc_Buff,strlen((const char *)ADc_Buff),&Write_Bytes); //�����յ������ݴ����ļ�
//		f_sync(&ADC_file);                                                       //ͬ���ļ���������д�����
//		printf("����%d�ֽ�����д���ļ�\r\n",Write_Bytes);                        //���ڴ�ӡ��Ϣ
//		
//		delay_ms(2000);           //��ʱ2s
//		memset(ADc_temp,0,20);    //��ADc_temp����ȫ����Ϊ0
//		memset(ADc_Buff,0,200);   //��ADc_Buff����ȫ����Ϊ0
	}
}
