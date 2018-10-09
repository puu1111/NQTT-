// Header:
// File Name: 
// Author:Qierven
// Date:xx

#include "queue.h"

FATFS fs[_VOLUMES];     //�߼����̹�����.�ļ�ϵͳĬ��֧��3�����̣�����ֻ����һ�� SD���0
 
stuNQTTx stuNQTT1; 
 
 
FIL   nqttData_file;	  		   		//�ļ�����������ADC�Ĵ洢
FIL   nqttLen_file;	  		        //�ļ�����������ADC�Ĵ洢
FIL   nqttRetry_file;	  		      //�ļ�����������ADC�Ĵ洢
FIL   nqttSta_file;	  		        //�ļ�����������ADC�Ĵ洢
FIL   nqttStarAddr_file;	  		  //�ļ�����������ADC�Ĵ洢

/*Fun: SDָ���ļ���λ�� д ָ������
 Author:Qierven
 Note:xx
 �ļ�   ����   ��ַ   ����  ʵ��д�볤��
*/
u8 File_W(	FIL* fp,char *buff,u32  Addr,	UINT btw,UINT* bw	)
{
		f_lseek(fp,Addr);                                    
		f_write(fp,buff,btw,bw); 
		f_sync(fp);                                                       
    if(btw != *bw)
			return 1;
		return 0;
}

/*Fun: SDָ���ļ���λ�� �� ָ������
 Author:Qierven
 Note:xx
 �ļ�   ����   ��ַ   ����  ʵ�ʶ�������
*/
u8 File_R(	FIL* fp,char *buff,u32  Addr,	UINT btr,UINT* br	)
{
	  memset(buff,0,strlen(buff));
		f_lseek(fp,Addr);                                    
		f_read(fp,buff,btr,br); 
		f_sync(fp);                                                       
    if(btr != *br)
			return 1;
		return 0;
}

/*Fun: ����ת�ַ���
 Author:Qierven
 Note:xx
Ŀ�ĵ�ַ   ����
*/
void ItoS(char* sData,u32 uData)
{
	memset(sData,0,strlen(sData));
	sprintf(sData,"%u",uData);
	strcat(sData,"\r\n");
}

/*Fun: �ַ��� ת ����
 Author:Qierven
 Note:xx
Ŀ�ĵ�ַ   ����
*/
void StoI(u32* uData,char* sData)
{
	*uData = 0;
	sscanf(sData,"%u",uData);
	memset(sData,0,strlen(sData)); 
}



/*Fun: nqtt����д
 Author:Qierven
 Note:xx
*/
void nqtt_WrQue(u32 CNT,char* Buff,u32 Len)
{
	if(stuNQTT1.W_Addr > stuNQTT1.WU_Addr_MAX)
	stuNQTT1.W_Addr = 0;

	ItoS(stuNQTT1.W_Data,stuNQTT1.W_Addr);//˳��
	File_W(&nqttStarAddr_file,stuNQTT1.W_Data,CNT*NQTT_STARADDR_SIZE,NQTT_STARADDR_SIZE,&stuNQTT1.W_RealyNum);
	
	ItoS(stuNQTT1.W_Data,WAIT_STA);//״̬
	File_W(&nqttSta_file,stuNQTT1.W_Data,CNT*NQTT_STA_SIZE,NQTT_STA_SIZE,&stuNQTT1.W_RealyNum);
	
	ItoS(stuNQTT1.W_Data,Len);//����
	File_W(&nqttLen_file,stuNQTT1.W_Data,CNT*NQTT_LEN_SIZE,NQTT_LEN_SIZE,&stuNQTT1.W_RealyNum);
	
	stuNQTT1.W_ReTry = QUE_RTRY_MAX;
	ItoS(stuNQTT1.W_Data,QUE_RTRY_MAX);//���Դ���
	File_W(&nqttRetry_file,stuNQTT1.W_Data,CNT*NQTT_RETRY_SIZE,NQTT_RETRY_SIZE,&stuNQTT1.W_RealyNum);
	
//	ItoS(stuNQTT1.W_Data,CNT);//˳��
	while((stuNQTT1.W_ReTry--)&&(File_W(&nqttData_file,Buff,stuNQTT1.W_Addr,Len,&stuNQTT1.W_RealyNum)));
	
	stuNQTT1.W_Addr += Len;
}

/*Fun: nqtt�����ϴ�
 Author:Qierven
 Note:xx
*/
void nqtt_UpLoad(u32 CNT,char* Buff,u32* Len)
{
	File_R(&nqttStarAddr_file,stuNQTT1.U_Data,CNT*NQTT_STARADDR_SIZE,NQTT_STARADDR_SIZE-2,&stuNQTT1.U_RealyNum);
	StoI(&stuNQTT1.U_Addr,stuNQTT1.U_Data);
	
	File_R(&nqttSta_file,stuNQTT1.U_Data,CNT*NQTT_STA_SIZE,NQTT_STA_SIZE-2,&stuNQTT1.U_RealyNum);
	StoI(&stuNQTT1.WU_Sta,stuNQTT1.U_Data);
	
	File_R(&nqttLen_file,stuNQTT1.U_Data,CNT*NQTT_LEN_SIZE,NQTT_LEN_SIZE-2,&stuNQTT1.U_RealyNum);
	StoI(&stuNQTT1.U_Len,stuNQTT1.U_Data);
	
	File_R(&nqttRetry_file,stuNQTT1.U_Data,CNT*NQTT_RETRY_SIZE,NQTT_RETRY_SIZE-2,&stuNQTT1.U_RealyNum);
	StoI(&stuNQTT1.U_ReTry,stuNQTT1.U_Data);
	
	if(stuNQTT1.WU_Sta == WAIT_STA)
	{
		while((stuNQTT1.U_ReTry--)&&(File_R(&nqttData_file,Buff,stuNQTT1.U_Addr,stuNQTT1.U_Len,&stuNQTT1.U_RealyNum)));
	}
	*Len = stuNQTT1.U_RealyNum;
}

















