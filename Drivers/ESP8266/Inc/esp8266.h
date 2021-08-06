#ifndef __ESP8266_H_
#define __ESP8266_H_
#include "main.h"
void ESP8266_RX_PUSH(u8 data);
void ESP8266_RX_POP(u8* data);
u8 ESP8266_RX_Find(u8* ack,u8 size,u8* rx);
u8 ESP8266_Cmd_Send(char* cmd, char* ack, u8* response ,u16 timeout);
void ESP8266_Init(void);
#endif
