#include "esp8266.h"

#define ESP8266_Send(data,size) HAL_UART_Transmit_DMA(&huart6, data, size);
#define CWJAP      (sprintf((char*)STR_BUF,"AT+CWJAP=\"%s\",\"%s\"",wifista_ssid,wifista_password),(char*)STR_BUF)
#define TRANSLINK  (sprintf((char*)STR_BUF,"AT+SAVETRANSLINK=1,\"%s\",%s,\"TCP\"",tcp_ip,tcp_port),(char*)STR_BUF)
//STA ģʽ�µ�wifi �� ����
char *wifista_ssid     = "dxxy16-403-1";
char *wifista_password = "1234567890";
//TCP ���ӵĶ˿ں�
char *tcp_ip           = "192.168.0.144";
char *tcp_port         = "7220";
//һЩ�̶�����Ӧ
char *_OK    = "OK\r\n\r\n";
char *_ready = "ready\r\n\r\n";
char *_GETIP = "WIFI GOT IP\n";
//���ն���ͷ�Ͷ���β��
u16 head=0,tail=0;

/*!
 *  \brief    ESP8266 RXBUF PUSH
 */
void ESP8266_RX_PUSH(u8 data)
{
	u16 pos = (head+1)%ESP8266_RX_MAX;
	if(pos!=tail)
	{
		ESP8266_RX_BUF[head] = data;
		head = pos;
	}
}
/*!
 *  \brief    ESP8266 RXBUF POP
 */
void ESP8266_RX_POP(u8* data)
{
	if(tail != head)
	{
		*data = ESP8266_RX_BUF[tail];
		tail  = (tail+1)%ESP8266_RX_MAX;
	}
}
/*!
 *  \brief    ESP8266 RXBUF ��ѯack
 */
u8 ESP8266_RX_Find(u8* ack,u8 size,u8* rx)
{
	u16 target= (head+ESP8266_RX_MAX-size)%ESP8266_RX_MAX;
	u16 ptr;
	for(ptr=0;ptr<size;ptr++)
	{
		if(ack[ptr] != ESP8266_RX_BUF[target])return NO;
		target = (target+1)%ESP8266_RX_MAX;
	}
	if(rx != NULL)
	{
		u8* rxp = rx;
		for(;tail != head;rxp++)
			ESP8266_RX_POP(rxp);
		*rxp = 0; //�ַ�������
	}
	else
	{
		u8 rx;
		for(;tail != head;)
			ESP8266_RX_POP(&rx);
	}
	return YES;
}
/*!
 *  \brief    ESP8266��������
 *  \param cmd ��Ҫ���͵�����
 *  \param ack ��������Ӧ
 *  \param response ��Ӧ���ݴ�ŵ�ִ�У���Ϊ NULL (�������½��յ�����)
 *  \param timeout  ��ʱʱ�䣬�����������õô�һЩ
 *  \retval ָ���Ƿ��ͳɹ� (YES Ϊ�ɹ�, NO Ϊʧ��)
 */
u8 ESP8266_Data_Send(char* data, char* ack, u8* response, u16 timeout)
{
	u16 size=0;
	char* pdata=data;
	sprintf((char*)ESP8266_ACK_BUF,"%s",ack);

	//���ý�Ҫ
	ESP8266_ACK_STA = 1;
	ESP8266_ACK_Size = sizeof(ack)-1;
	ESP8266_Response_Ptr = response;
	ESP8266_Timeout_Tick = timeout;

	for(;*pdata;size++,pdata++);
	head = tail;//�������

	ESP8266_Send((u8*)data,size);
	HAL_TIM_Base_Start_IT(&htim7);
	while(ESP8266_ACK_STA == 1);
	HAL_TIM_Base_Stop_IT(&htim7);

	if(ESP8266_ACK_STA == 2)
	{
		return OK;
	}
	else
	{
		return TIMEOUT;
	}
}
/*!
 *  \brief    ESP8266����ָ��
 *  \param cmd ��Ҫ���͵�ָ��
 *  \param ack ��������Ӧ
 *  \param response ��Ӧ���ݴ�ŵ�ִ�У���Ϊ NULL (�������½��յ�����)
 *  \param timeout  ��ʱʱ�䣬�����������õô�һЩ
 *  \retval ָ���Ƿ��ͳɹ� (YES Ϊ�ɹ�, NO Ϊʧ��)
 */
u8 ESP8266_Cmd_Send(char* cmd,char* ack,u8* response, u16 timeout)
{
	//����Ҫ���͵����ݽ��� BUF ��
	sprintf((char*)ESP8266_TX_BUF,"%s\r\n",(char*)cmd);
	return ESP8266_Data_Send((char*)ESP8266_TX_BUF,ack,response,timeout);
}
/*!
 *  \brief    ESP8266��ʼ��
 */
void ESP8266_Init(void)
{
	//�����жϽ���
	HAL_UART_Receive_IT(&huart6, &RxBuffer, 1);

	//����Ƿ��������� ESP8266
	while(ESP8266_Cmd_Send("AT",_OK,NULL,1000) != OK)
	{
		ESP8266_Data_Send("+++", "CLOSED\r\n", NULL, 50); //�˳�͸��
	}
	ESP8266_Cmd_Send("ATE0"              ,_OK   ,NULL,500);  //�رջش�
	ESP8266_Cmd_Send("AT+CWMODE_DEF=1"   ,_OK   ,NULL,500);  //����Ϊ STA ģʽ
	ESP8266_Cmd_Send("AT+CIPMODE=0"      ,_OK   ,NULL,1000); //�ر�͸��
	ESP8266_Cmd_Send("AT+SAVETRANSLINK=0",_OK   ,NULL,1000); //�˳�͸������
	ESP8266_Cmd_Send("AT+RST"            ,_ready,NULL,3000); //����ʹ�� STA ģʽ��Ч
	ESP8266_Cmd_Send(CWJAP               ,_OK   ,NULL,5000); //���� WIFI
	ESP8266_Cmd_Send(TRANSLINK           ,_OK   ,NULL,1000); //���� TCP ����
	ESP8266_Cmd_Send("AT+CIPMODE=1"      ,_OK   ,NULL,1000); //����͸��
	ESP8266_Cmd_Send("AT+RST"            ,_GETIP,NULL,8000); //����ʹ��͸����Ч
	//ESP8266_Cmd_Send("AT+CIPSEND"        ,">"   ,NULL,1000); //���û�õ�

	//����Ϊ��������
	for(;;)
	{
		static u16 i = 0;
		HAL_Delay(300);
		HAL_UART_Transmit(&huart6,Str("Num=%5d\r\n",i++),11,20);
	}
}
