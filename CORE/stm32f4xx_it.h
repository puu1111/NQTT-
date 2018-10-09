/*-------------------------------------------------*/
/*                    超纬电子                     */
/*    淘宝地址： http://chaoweidianzi.taobao.com   */
/*-------------------------------------------------*/

#ifndef __STM32F4xx_IT_H
#define __STM32F4xx_IT_H

#include "stm32f4xx.h"

/*-------------------------------------------------*/
/*                                                 */
/*                    系统中断                     */
/*                                                 */
/*-------------------------------------------------*/

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);


/*-------------------------------------------------*/
/*                                                 */
/*                    应用中断                     */
/*                                                 */
/*-------------------------------------------------*/

void SDIO_IRQHandler(void);//SDIO中断服务函数 

#endif 
