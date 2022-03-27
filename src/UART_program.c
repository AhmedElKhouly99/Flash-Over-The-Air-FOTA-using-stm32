/****************************************************************************************************************/
/*	Author 	: 	Ahmed Karrar																					*/
/*	Version : 	V01																								*/
/*	Date 	:	19 Sept 2020																					*/
/****************************************************************************************************************/ 					
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"

#include "UART_config.h"
#include "UART_private.h"
#define THRESHOLD_VALUE  9000000UL


void MUSART1_voidInit(void)
{
	/* 9600   BRR = 0x341 */
	//MUSART1 -> BRR = 0x341;
	/* 115200 BRR */
	MUSART1 -> BRR = 0x45;
	/*
	1- Enable RX
	2- Enable TX
	3- Enable USART
	*/
	SET_BIT(MUSART1 -> CR1,2);
	SET_BIT(MUSART1 -> CR1,3);
	SET_BIT(MUSART1 -> CR1,13);
	/* Clear Status Register */
	MUSART1 -> SR = 0;
}
void MUSART1_voidTransmit(u8 * arr)
{
	u8 i = 0;
	while(arr[i] != '\0')
	{
		MUSART1 -> DR = arr[i];
		/* Wait till Transmission is Complete */
		while(GET_BIT(MUSART1 -> SR,6)==0);
		CLR_BIT( MUSART1 -> SR , 6 );
		//while(((MUSART1 -> SR) & 0x40 ) == 0);
		i++;
	}
}

/*u8 MUSART1_u8Receive(u8* Copy_u8Data)
{
	u8 Local_u8Result = 1;

	if ( (GET_BIT((MUSART1 -> SR), 5)) == 1 )
	{
		*Copy_u8Data = MUSART1 -> DR;
	}
	else
	{
		Local_u8Result = 0;
	}

	return (Local_u8Result);
}*/


u8 MUSART1_u8ReceiveWait(void)
{
	while(((MUSART1 -> SR) & 1 << 5) == 0);
	return ( 0xFF & (MUSART1 -> DR));
}

u8 MUSART1_u8Receive(void){

	u16 timeout = 0;

	u8 Loc_u8ReceivedData = 0;
	while((GET_BIT((MUSART1 -> SR), 5)) == 0){
		timeout++;

		if(timeout== 10000){
			Loc_u8ReceivedData = 255;
			break;
		}
	}
	if(Loc_u8ReceivedData == 0){
		Loc_u8ReceivedData = MUSART1 -> DR;
	}
	return Loc_u8ReceivedData;
}


/*u8 MUSART1_u8Receive(void){

	u16 timeout = 0;

	u8 Loc_u8ReceivedData = 0;
	while((GET_BIT((MUSART1 -> SR), 5)) == 0){
		timeout++;

		if(timeout== THRESHOLD_VALUE){
			Loc_u8ReceivedData = 255;
			break;
		}
	}
	if(Loc_u8ReceivedData == 0){
		Loc_u8ReceivedData = MUSART1 -> DR;
	}
	return Loc_u8ReceivedData;
}*/


/*u8 MUSART1_u8Receive(void){
	u8  LOC_u8Data  = 0 ;
	u32 LOC_TimeOut = 0 ;

	CLR_BIT ( MUSART1 -> SR, 5);

	while( ( GET_BIT ( MUSART1 -> SR, 5) == 0 ) && ( LOC_TimeOut < THRESHOLD_VALUE ) )
	{
		LOC_TimeOut++;
	}

	if( LOC_TimeOut == THRESHOLD_VALUE )
	{
		LOC_u8Data = 255;
	}
	else
	{

		LOC_u8Data = MUSART1 -> DR;
	}

	return LOC_u8Data;
}*/


u8 MUSART1_u8ReceiveString(u8 * Local_u8Respone, u8 Delimiter){
	u16 i = 0;
	u8 result = 0;
	u16 timeout = 0;
	do{
		result = MUSART1_u8Receive();
		if(result != 255){
			Local_u8Respone[i] = result;
			i++;
		}
		timeout ++;
	}while(result != Delimiter && timeout != 20000);

	if(timeout == 20000){
		i = 0;
	}

	/*while((result = MUSART1_u8Receive()) != Delimiter){
		Local_u8Respone[i] = result;
		i++;
	}*/

	return i;
}
