/*-------------------------------------------------*/
/*         ��γ����STM32F407ZGT6������             */
/*    �Ա���ַ�� http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/

#ifndef _DISKIO_DEFINED
/*-------------------------------------------------*/
/*         ��γ����STM32F407ZGT6������             */
/*    �Ա���ַ�� http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/
#define _DISKIO_DEFINED

#ifdef __cplusplus
extern "C" {
#endif

#define _USE_WRITE	1	//��Ȩ��
#define _USE_IOCTL	1	//����Ȩ��

#include "integer.h"

typedef BYTE	DSTATUS;   //����ṹ����

//���ִ���״̬
typedef enum {
	RES_OK = 0,		//��ȷ
	RES_ERROR,		//��д����
	RES_WRPRT,		//������
	RES_NOTRDY,		//δ����
	RES_PARERR		//��Ч�Ĳ���
} DRESULT;


DSTATUS disk_initialize (BYTE pdrv);                                        //��ʼ��Ӳ������
DSTATUS disk_status (BYTE pdrv);                                            //��ô���״̬ 
DRESULT disk_read (BYTE pdrv, BYTE* buff, DWORD sector, UINT count);        //����������  
DRESULT disk_write (BYTE pdrv, const BYTE* buff, DWORD sector, UINT count); //д��������  
DRESULT disk_ioctl (BYTE pdrv, BYTE cmd, void* buff);                       //���ƺ���
DWORD get_fattime (void);       //���ʱ��
void *ff_memalloc (UINT size);  //��̬�����ڴ� 
void ff_memfree (void* mf);     //�ͷ��ڴ�

//״̬��ʾ
#define STA_NOINIT		0x01	//δ��ʼ��
#define STA_NODISK		0x02	//δ���ִ���
#define STA_PROTECT		0x04	//д����


//���²����ã�δ������
/* Command code for disk_ioctrl fucntion */
/* Generic command (used by FatFs) */
#define CTRL_SYNC			0	/* Flush disk cache (for write functions) */
#define GET_SECTOR_COUNT	1	/* Get media size (for only f_mkfs()) */
#define GET_SECTOR_SIZE		2	/* Get sector size (for multiple sector size (_MAX_SS >= 1024)) */
#define GET_BLOCK_SIZE		3	/* Get erase block size (for only f_mkfs()) */
#define CTRL_ERASE_SECTOR	4	/* Force erased a block of sectors (for only _USE_ERASE) */

/* Generic command (not used by FatFs) */
#define CTRL_POWER			5	/* Get/Set power status */
#define CTRL_LOCK			6	/* Lock/Unlock media removal */
#define CTRL_EJECT			7	/* Eject media */
#define CTRL_FORMAT			8	/* Create physical format on the media */

/* MMC/SDC specific ioctl command */
#define MMC_GET_TYPE		10	/* Get card type */
#define MMC_GET_CSD			11	/* Get CSD */
#define MMC_GET_CID			12	/* Get CID */
#define MMC_GET_OCR			13	/* Get OCR */
#define MMC_GET_SDSTAT		14	/* Get SD status */

/* ATA/CF specific ioctl command */
#define ATA_GET_REV			20	/* Get F/W revision */
#define ATA_GET_MODEL		21	/* Get model name */
#define ATA_GET_SN			22	/* Get serial number */

#ifdef __cplusplus
}
#endif

#endif
