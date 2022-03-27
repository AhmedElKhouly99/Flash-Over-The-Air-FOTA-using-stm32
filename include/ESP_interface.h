/*
 *  TFT_interface.h
 *  Date   : 17 AUG , 2021
 *  Author : Ahmed ElKhouly
 *  Version: V01
 */
 
#ifndef ESP_INTERFACE_H
#define ESP_INTERFACE_H

extern void ESP_voidInit(void);

//extern void ESP_voidConnectWifi(void);
extern void ESP_voidConnectWifi(u8 *Copy_u8username, u8 *Copy_u8password);

extern void ESP_voidConnectServer( u8 * Copy_u8Domain , u8 * Copy_u8Port );

extern void ESP8266_VidClearBuffer(void);

extern u8 ESP_voidSendRecHttpReq(u8 *Copy_u8Length, u8 *Copy_u8Req);

extern u8 DataRec[15000];
extern u8 Counter;

#endif /* ESP_INTERFACE_H */
