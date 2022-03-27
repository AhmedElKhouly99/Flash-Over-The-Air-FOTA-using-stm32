/*
 * main.c
 *
 *  Created on: Oct 13, 2020
 *      Author: Ahmed
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "UART_interface.h"
#include "ESP_interface.h"
#include "FPEC_interface.h"

void Parser_voidParseRecord(u8* Copy_u8BufData);

volatile u8  u8RecBuffer[200]   ;
volatile u8  u8RecCounter    = 0;
volatile u8  u8TimeOutFlag   = 0;
volatile u16 u16TimerCounter = 0;
volatile u8  u8BLWriteReq    = 1;
typedef void (*Function_t)(void);
Function_t addr_to_call = 0;

void func(void)
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = 0x08002000;

	addr_to_call = *(Function_t*)(0x08002004);
	addr_to_call();
}

void clear(void){
	u8 i;
	for(i = 0; i < u8RecCounter; i++){
		u8RecBuffer[i] = 0;
	}
	u8RecCounter = 0;
}


void main(void)
{
	u8 Local_u8RecStatus;
	u16 length = 41;

	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2,14); /* USART1 */
	RCC_voidEnableClock(RCC_APB2,2);  /* PortA  */
	RCC_voidEnableClock(RCC_AHB,4);   /* FPEC   */


	MGPIO_voidSetPinDirection(GPIOA,9,0b1010);   /* TX AFPP */
	MGPIO_voidSetPinDirection(GPIOA,10,0b0100);  /* RC Input Floating */

	MUSART1_voidInit();

	MSTK_voidInit();

	//MSTK_voidSetIntervalSingle(15000000,func);
	ESP_voidInit();
	ESP_voidConnectWifi((u8 *)"khouly", (u8 *)"1150011400");
	ESP_voidConnectServer((u8 *)"162.253.155.226", (u8 *)"80");
	ESP_voidSendRecHttpReq((u8 *)"33", (u8 *)"iot.ueuo.com");
	u8 flag = 0;
	//MSTK_voidSetIntervalSingle(15000000,func);

	while(u8TimeOutFlag == 0)
	{
		//u8RecCounter = Counter;
		/*ESP_voidInit();
		ESP_voidConnectWifi((u8 *)"khouly", (u8 *)"1150011400");
		ESP_voidSendRecHttpReq((u8 *)"36", (u8 *)"iot.ueuo.com");*/
		//Local_u8RecStatus = MUSART1_u8Receive( &(u8RecBuffer[u8RecCounter]) );
		if (DataRec[length] != 'z')
		{
			//MSTK_voidStopInterval();

			if(DataRec[length] == '\n')
			{
				flag = 0;
				if (u8BLWriteReq == 1)
				{
					FPEC_voidEraseAppArea();
					u8BLWriteReq = 0;
				}
				//u8RecBuffer[u8RecCounter] = DataRec[length];
				//u8RecCounter ++ ;
				//length ++;
				
				/* Parse */
				Parser_voidParseRecord((u8*)u8RecBuffer);
				clear();
				//MUSART1_voidTransmit((u8 *)"ok");
				u8RecCounter = 0;
				length ++;
			}else if(DataRec[length] == '\r'){

				//Counter ++;
				while(DataRec[length] != ':'){
					length ++;
				}
				/*if(DataRec[length+1] == ':'){
					Parser_voidParseRecord((u8*)u8RecBuffer);
					clear();
					length ++;
					//flag = 1;
				}*/
				length ++;
				//continue;
			}

			else
			{
				u8RecBuffer[u8RecCounter] = DataRec[length];
				u8RecCounter ++ ;
				length ++;
			}

			//length ++;
			//MSTK_voidSetIntervalSingle(15000000,func);
		}

		else
		{
			//MSTK_voidSetIntervalSingle(15000000,func);
			//u8TimeOutFlag = 1;
			func();
		}
		//MSTK_voidSetIntervalSingle(15000000,func);
		//func();
	}
	//MSTK_voidSetIntervalSingle(15000000,func);

}
