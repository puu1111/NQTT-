#ifndef _QUEUE_H
#define _QUEUE_H	

#include "main.h"

#define QUE_SIZE    		1400
#define QUE_RTRY_MAX    5

#define NQTT_LEN_SIZE        		6
#define NQTT_STARADDR_SIZE     	9
#define NQTT_STA_SIZE       		4
#define NQTT_RETRY_SIZE       	4


typedef char QUE_TYPE;

typedef enum
{
	QUE_RETRY_ERR,
	
}QUE_ERRx;


typedef enum
{
	NONE_STA,
	WAIT_STA,
	OK_STA,
}QUE_STAx;

typedef struct
{
	u8  TimerFlag;
	u32 WU_Addr_MAX;
	u32 WU_CNT;
	u32 WU_Sta;
	
	char W_Data[QUE_SIZE];
	u32  W_Addr;
	u32  W_Len;
	u32  W_RealyNum;
	u32  W_ReTry;
	
	char U_Data[QUE_SIZE];
	u32  U_Addr;
	u32  U_Len;
	u32  U_RealyNum;
	u32  U_ReTry;
	
	QUE_ERRx ErrFlag;
}stuNQTTx;
	


extern FATFS fs[_VOLUMES];     //逻辑磁盘工作区.文件系统默认支持3个磁盘，我们只用了一个 SD编号0

extern FIL   nqttData_file;	  		   		//文件变量，用于ADC的存储
extern FIL   nqttLen_file;	  		      //文件变量，用于ADC的存储
extern FIL   nqttRetry_file;	  		    //文件变量，用于ADC的存储
extern FIL   nqttSta_file;	  		      //文件变量，用于ADC的存储
extern FIL   nqttStarAddr_file;	  		  //文件变量，用于ADC的存储

extern stuNQTTx stuNQTT1; 

/*
nqttData_file
nqttLen_file
nqttRetry_file
nqttSta_file
nqttStarAddr_file
*/

u8 File_W(	FIL* fp,char *buff,u32  Addr,	UINT btw,UINT* bw	);
u8 File_R(	FIL* fp,char *buff,u32  Addr,	UINT btr,UINT* br	);
void nqtt_WrQue(u32 CNT,char* Buff,u32 Len);
void nqtt_UpLoad(u32 CNT,char* Buff,u32* Len);
void ItoS(char* sData,u32 uData);
void StoI(u32* uData,char* sData);














#endif

























