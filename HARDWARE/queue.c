// Header:
// File Name: 
// Author:Qierven
// Date:xx

#include "queue.h"

FATFS fs[_VOLUMES];     //逻辑磁盘工作区.文件系统默认支持3个磁盘，我们只用了一个 SD编号0
 
stuNQTTx stuNQTT1; 
 
 
FIL   nqttData_file;	  		   		//文件变量，用于ADC的存储
FIL   nqttLen_file;	  		        //文件变量，用于ADC的存储
FIL   nqttRetry_file;	  		      //文件变量，用于ADC的存储
FIL   nqttSta_file;	  		        //文件变量，用于ADC的存储
FIL   nqttStarAddr_file;	  		  //文件变量，用于ADC的存储

/*Fun: SD指定文件和位置 写 指定长度
 Author:Qierven
 Note:xx
 文件   数据   地址   长度  实际写入长度
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

/*Fun: SD指定文件和位置 读 指定长度
 Author:Qierven
 Note:xx
 文件   数据   地址   长度  实际读出长度
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

/*Fun: 数据转字符串
 Author:Qierven
 Note:xx
目的地址   数据
*/
void ItoS(char* sData,u32 uData)
{
	memset(sData,0,strlen(sData));
	sprintf(sData,"%u",uData);
	strcat(sData,"\r\n");
}

/*Fun: 字符串 转 整形
 Author:Qierven
 Note:xx
目的地址   数据
*/
void StoI(u32* uData,char* sData)
{
	*uData = 0;
	sscanf(sData,"%u",uData);
	memset(sData,0,strlen(sData)); 
}



/*Fun: nqtt数据写
 Author:Qierven
 Note:xx
*/
void nqtt_WrQue(u32 CNT,char* Buff,u32 Len)
{
	if(stuNQTT1.W_Addr > stuNQTT1.WU_Addr_MAX)
	stuNQTT1.W_Addr = 0;

	ItoS(stuNQTT1.W_Data,stuNQTT1.W_Addr);//顺序
	File_W(&nqttStarAddr_file,stuNQTT1.W_Data,CNT*NQTT_STARADDR_SIZE,NQTT_STARADDR_SIZE,&stuNQTT1.W_RealyNum);
	
	ItoS(stuNQTT1.W_Data,WAIT_STA);//状态
	File_W(&nqttSta_file,stuNQTT1.W_Data,CNT*NQTT_STA_SIZE,NQTT_STA_SIZE,&stuNQTT1.W_RealyNum);
	
	ItoS(stuNQTT1.W_Data,Len);//长度
	File_W(&nqttLen_file,stuNQTT1.W_Data,CNT*NQTT_LEN_SIZE,NQTT_LEN_SIZE,&stuNQTT1.W_RealyNum);
	
	stuNQTT1.W_ReTry = QUE_RTRY_MAX;
	ItoS(stuNQTT1.W_Data,QUE_RTRY_MAX);//重试次数
	File_W(&nqttRetry_file,stuNQTT1.W_Data,CNT*NQTT_RETRY_SIZE,NQTT_RETRY_SIZE,&stuNQTT1.W_RealyNum);
	
//	ItoS(stuNQTT1.W_Data,CNT);//顺序
	while((stuNQTT1.W_ReTry--)&&(File_W(&nqttData_file,Buff,stuNQTT1.W_Addr,Len,&stuNQTT1.W_RealyNum)));
	
	stuNQTT1.W_Addr += Len;
}

/*Fun: nqtt数据上传
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

















