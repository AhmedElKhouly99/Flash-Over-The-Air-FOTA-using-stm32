/****************************************************************************************************************/
/*	Author 	: 	Ahmed Karrar																					*/
/*	Version : 	V01																								*/
/*	Date 	:	19 Sept 2020																					*/
/****************************************************************************************************************/ 					

#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

void MUSART1_voidInit(void);
void MUSART1_voidTransmit(u8 * arr);
u8 MUSART1_u8Receive(void);
u8 MUSART1_u8ReceiveWait(void);
//u8 MUSART1_u8Receive(u8* Copy_u8Data);
u8 MUSART1_u8ReceiveString(u8 * Local_u8Respone, u8 Delimiter);
#endif
