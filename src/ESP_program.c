/*
 *  TFT_program.c
 *  Date   : 17 AUG , 2021
 *  Author : Ahmed ElKhouly
 *  Version: V01
 */
 
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "UART_interface.h"
#include "ESP_private.h"
#include "ESP_interface.h"
#include "ESP_config.h"

u8 DataRec[15000] = {0};
//u8 DataNeeded[1000] = {0};
u8 Counter = 0;
u8 volatile Iterator = 0  ;
 
void ESP_voidInit(void){
	u8 Local_u8Result = 0;

	while(Local_u8Result == 0){
		// STOP ECHO
		//MUSART1_voidTransmit((u8 *)"AT\r\n");
		MUSART1_voidTransmit((u8 *)"ATE0\r\n");
		Local_u8Result = voidESPValidateCmd('K');
	}
	Local_u8Result = 0;
	while(Local_u8Result == 0){
		// STOP ECHO
		MUSART1_voidTransmit((u8 *)"AT+CWMODE=3\r\n");
		Local_u8Result = voidESPValidateCmd('K');
	}
	Local_u8Result = 0;
	while(Local_u8Result == 0){
	// SET STATION MODE
	MUSART1_voidTransmit((u8 *)"AT+CIPMODE=0\r\n");
	Local_u8Result = voidESPValidateCmd('K');
	}
}

static u8 voidESPValidateCmd(u8 Delimiter){
	
	//u8 Local_u8Respone[100] = {0};
	u8 Result = 0;

	//ESP8266_VidClearBuffer();
	//MUSART1_u8ReceiveString(DataRec, Delimiter);
	Result = MUSART1_u8ReceiveString(DataRec, Delimiter);

	
	// CHECK IF OK
	/*if(Local_u8Respone[0] == 'O' && Local_u8Respone[1] == 'K'){
		Result = 1;
	}*/
	//Result = 1;
	
	return Result;
	
}


void ESP_voidConnectWifi(u8 *Copy_u8username, u8 *Copy_u8password){

	u8 Local_u8Result = 0;
	
	while(Local_u8Result==0){
		// CONNECT WLAN
		MUSART1_voidTransmit((u8 *)"AT+CWJAP=\"");
		MUSART1_voidTransmit((u8 *)Copy_u8username);
		MUSART1_voidTransmit((u8 *)"\",\"");
		MUSART1_voidTransmit((u8 *)Copy_u8password);
		MUSART1_voidTransmit((u8 *)"\"\r\n");
		Local_u8Result = voidESPValidateCmd('K');
	}
	
}


void ESP_voidConnectServer( u8 * Copy_u8Domain , u8 * Copy_u8Port ){
	
	u8 Local_u8Result = 0;
	
	while(Local_u8Result==0){
		// CONNECT SEVER
		MUSART1_voidTransmit((u8 *)"AT+CIPSTART=\"TCP\",\"");
		MUSART1_voidTransmit((u8 *)Copy_u8Domain);
		MUSART1_voidTransmit((u8 *)"\",");
		MUSART1_voidTransmit((u8 *)Copy_u8Port);
		MUSART1_voidTransmit((u8 *)"\r\n");
		Local_u8Result = voidESPValidateCmd('K');
	}
	
}


u8 ESP_voidSendRecHttpReq(u8 *Copy_u8Length, u8 *Copy_u8Req){
	u8 Local_u8Result = 0;

	while(Local_u8Result==0){
	// SEND HTTP REQ LENGTH
		ESP8266_VidClearBuffer();
		MUSART1_voidTransmit((u8 *)"AT+CIPSEND=");
		MUSART1_voidTransmit( (u8 *) Copy_u8Length);
		MUSART1_voidTransmit((u8 *)"\r\n");
		Local_u8Result = voidESPValidateCmd('K');
	}
	ESP8266_VidClearBuffer();
	Local_u8Result = 0;
	while(Local_u8Result==0){
		MUSART1_voidTransmit( (u8 *) "GET http://" );
		MUSART1_voidTransmit( (u8 *) Copy_u8Req);
		MUSART1_voidTransmit( (u8 *) "/hex.txt\r\n");
		Local_u8Result = voidESPValidateCmd('z');
	}
	//ESP_VoidExtractData();

		return DataRec[37];
	
}



void ESP8266_VidClearBuffer ( void ){

	u16 LOC_u8Iterator1 = 0 ;
	Iterator     = 0 ;

	for( LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < 15000 ; LOC_u8Iterator1++ ){

		DataRec[ LOC_u8Iterator1 ] = 0 ;
		//DataNeeded[LOC_u8Iterator1] = 0;

	}

}

/*static void ESP_VoidExtractData(void){
	u8 Length = DataRec[35] - 48;
	//u8 i = 0;
	Counter = 0;
	for(Counter = 0; Counter < Length; Counter++){
		DataNeeded[Counter] = DataRec[37+Counter];
	}
	ESP8266_VidClearBuffer();
}*/




