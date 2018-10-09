/*-------------------------------------------------*/
/*                    超纬电子                     */
/*    淘宝地址： http://chaoweidianzi.taobao.com   */
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
	
	delay_init();		    //延时初始化 
	Usart1_init(115200);	//串口初始化波特率为115200 
//	Adc_Init();             //初始化ADC	
	
	while(SD_Init())                   //SD卡初始化
	{
		printf("SD卡初始化错误\r\n");  //串口提示SD卡初始化错误
		delay_ms(200);                //延时2s
	}
   printf("SD卡初始化成功\r\n");
	f_mount(&fs[0],"0:",1); 	                                            
	
  f_open(&nqttData_file,"0:/nqttData_file.txt",FA_OPEN_ALWAYS | FA_READ | FA_WRITE );//创建或打开一个文本文档保存数据
	f_sync(&nqttData_file); 
  f_open(&nqttLen_file,"0:/nqttLen_file.txt",FA_OPEN_ALWAYS | FA_READ | FA_WRITE );//创建或打开一个文本文档保存数据
	f_sync(&nqttLen_file); 
  f_open(&nqttRetry_file,"0:/nqttRetry_file.txt",FA_OPEN_ALWAYS | FA_READ | FA_WRITE );//创建或打开一个文本文档保存数据
	f_sync(&nqttRetry_file); 
  f_open(&nqttSta_file,"0:/nqttSta_file.txt",FA_OPEN_ALWAYS | FA_READ | FA_WRITE );//创建或打开一个文本文档保存数据
	f_sync(&nqttSta_file); 
  f_open(&nqttStarAddr_file,"0:/nqttStarAddr_file.txt",FA_OPEN_ALWAYS | FA_READ | FA_WRITE );//创建或打开一个文本文档保存数据
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
					printf("顺序：%d  数据：",i);
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
//			temp=(float)(Get_Adc_Average(i,20))*(3.3/4096);   //获取计算后的带小数的实际电压值，比如3.1111
//			printf("通道%d=%f\r\n",i,temp);                   //串口输出信息
//			sprintf((char *)ADc_temp,"%f|",temp);             //打印格式话的信息
//			strcat((char *)ADc_Buff,(char *)ADc_temp);	      //构建写入文件的数据	
//		}
//		strcat((char *)ADc_Buff,"\r\n");                      //加上回车换行

//		i = f_size(&ADC_file);
//		i = strlen((const char *)ADc_Buff);
//		f_lseek(&ADC_file,f_size(&ADC_file));                                    //将指针定位于文件尾部，准备追加数据
//		f_write(&ADC_file,ADc_Buff,strlen((const char *)ADc_Buff),&Write_Bytes); //将接收到的数据存入文件
//		f_sync(&ADC_file);                                                       //同步文件，将数据写入磁盘
//		printf("共计%d字节数据写入文件\r\n",Write_Bytes);                        //串口打印信息
//		
//		delay_ms(2000);           //延时2s
//		memset(ADc_temp,0,20);    //将ADc_temp数组全部置为0
//		memset(ADc_Buff,0,200);   //将ADc_Buff数组全部置为0
	}
}
