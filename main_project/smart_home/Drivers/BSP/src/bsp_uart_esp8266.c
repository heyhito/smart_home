/*
*********************************************************************************************************
*
*	ģ������ : ESP8266 ����WIFIģ����������
*	�ļ����� : bsp_esp8266.c
*	��    �� : V1.3
*	˵    �� : ��װ ESP8266 ģ����ص�AT����
*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2014-11-29  armfly  ��ʽ����
*		V1.1    2014-12-11  armfly  �޸� ESP8266_WaitResponse() ����, ʵ�������ַ��жϡ�����TCP���ݷ��ͺ���.
*		V1.2    2014-12-22  armfly  ����GPIO2�� GPIO0 ���ŵ����á���Ӧ�°�Ӳ����
*		V1.3	2015-07-24  armfly	
*					(1) ���Ӻ��� uint8_t ESP8266_CreateTCPServer(void);
*					(2) �޸�ESP8266_JoinAP() ���ӷ���ֵ
*
*	Copyright (C), 2014-2015, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#include "bsp.h"



#define AT_CR		'\r'
#define AT_LF		'\n'

/* ������У���ʾʹ����չ��IO */
//#define USE_HC574

//#ifdef USE_HC574	/* ʹ����չIO */
//	/* Ӳ������������� -- �� 3.3V ��ʼ����  */
//	#define ESP_CH_PD_0()	HC574_SetPin(GPRS_TERM_ON, 0);
//	#define ESP_CH_PD_1()	HC574_SetPin(GPRS_TERM_ON, 1);

//	/* Ӳ����λ���� -- ���Բ��� */
//	#define ESP_RESET_0()	HC574_SetPin(GPRS_RESET, 0);
//	#define ESP_RESET_1()	HC574_SetPin(GPRS_RESET, 1);

//	/* 1��ʾ����̼�����ģʽ 0��ʾ����ATָ��ģʽ */
//	#define ESP_GPIO0_0()	HC574_SetPin(ESP8266_G0, 0);
//	#define ESP_GPIO0_1()	HC574_SetPin(ESP8266_G0, 1);
//	#define ESP_ENTER_ISP()	ESP_GPIO0_0()  /* ����̼�����ģʽ */
//	#define ESP_EXIT_ISP()	ESP_GPIO0_1()	/* �˳��̼�����ģʽ */

//	/* ����Ϊ�ߣ���������; */
//	#define ESP_GPIO2_0()	HC574_SetPin(ESP8266_G2, 0);
//	#define ESP_GPIO2_1()	HC574_SetPin(ESP8266_G2, 1);
//#else	/* ʹ��CPU GPIO */

//	#define PORT_RESET		GPIOB
//	#define PIN_RESET		GPIO_PIN_12

	/* Ӳ����λ���� -- ���Բ��� */
//	#define ESP_RESET_0()	GPIO_ResetBits(PORT_RESET, PIN_RESET);
//	#define ESP_RESET_1()	GPIO_SetBits(PORT_RESET, PIN_RESET);

//#endif



#define WIFI_SSID "Tenda_E7AA00"
#define WIFI_PWD  "a17328655245"



char cmd_buf[100];
char topicdevsub[] = {"/my/devsub"};//��������
char topicdevpub[] = {"/my/devpub"};//��������

char g_EspBuf[2048];	/* ���ڽ��� */

extern uint8_t g_chinese_fonts_1[5][32];
extern uint8_t g_chinese_fonts_2[7][32];
extern uint8_t g_chinese_fonts_3[8][32];
extern uint8_t g_chinese_fonts_4[8][32];
extern uint8_t g_chinese_fonts_5[8][32];
extern uint8_t g_chinese_fonts_6[8][32];
extern uint8_t g_chinese_fonts_7[12][32];
extern uint8_t g_chinese_fonts_8[12][32];
extern uint8_t g_chinese_fonts_9[11][32];
extern uint8_t g_chinese_fonts_10[11][32];
extern uint8_t g_chinese_fonts_11[10][32];
extern uint8_t g_chinese_fonts_12[10][32];

ESP8266_T g_tESP8266;
uint8_t g_esp8266_timeout;

void ESP8266_RxTimeOut(void);

/*
*********************************************************************************************************
*	�� �� ��: bsp_InitESP8266
*	����˵��: ��������ģ����ص�GPIO,  �ú����� bsp_Init() ���á�
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitESP8266(void)
{


	comSetBaud(COM_ESP8266,115200);
}


int bsp_InitESP8266MQTT(void)
{
	uint8_t sta = 0;//��¼��ǰ״̬
	uint8_t errnum = 0,resettime = 0; //��¼�������
	while(1)
	{
		//��λ��������10�Σ���ʾϵͳ��ʼ��ʧ��
		if(resettime > 10)
		{
			resettime = 0;
			LCD_Clear();
			LCD_PrintString(0,3,"Sys Init error");
			bsp_DelayMS(500);
		}
		//��ʼ���ɹ�
		if(sta == 6)
		{
			LCD_Clear();
			LCD_PrintString(0,3,"Sys Init ok");
			bsp_DelayMS(500);
			LCD_Clear();
			return 1;
		}
		switch(sta)
		{
			case 0:
				//ESP8266_SendAT("AT+RST");
				bsp_DelayMS(3000);
				ESP8266_SendAT("AT");
				ESP8266_SendAT("ATE0");
				if(ESP8266_WaitResponse("OK",100)==1) //�յ�OK
				{
					
					
					printf("\r\n [1] �ҵ���ESP8266ģ��");
					LCD_Clear();
					LCD_PrintChinese(3,3,g_chinese_fonts_1,5);

					sta = 1;
					errnum = 0;
					bsp_DelayMS(1000);//�ӳ�1s������һ��
					
				}
				else
				{
					LCD_Clear();
					bsp_DelayMS(200);
					printf("\r\n [1] û���ҵ�ESP8266ģ��");
					LCD_PrintChinese(1,3,g_chinese_fonts_2,7);
					errnum++;
					if(errnum > 20)
					{
						errnum = 0;
						resettime++;

					}
					
				}
			
				break;
			case 1:
				ESP8266_SendAT("AT+CWMODE=1");//����Station����ģʽ
				if(ESP8266_WaitResponse("OK",100)==1) //�յ�OK
				{
					printf("\r\n [2] ����ģʽ���óɹ�");
					LCD_PrintChinese(0,3,g_chinese_fonts_3,8);
					
					sta = 2;
					errnum = 0;
					bsp_DelayMS(1000);//�ӳ�1s������һ��
					LCD_Clear();
				}
				else
				{
					LCD_Clear();
					bsp_DelayMS(200);
					printf("\r\n [1] ����ģʽ����ʧ��");
					LCD_PrintChinese(0,3,g_chinese_fonts_4,8);
					
					errnum++;
					if(errnum > 20)
					{
						errnum = 0;
						resettime++;
						sta = 0;
					}
				}
				//sta = 2;
				break;
			case 2:
				if(ESP8266_JoinAP(WIFI_SSID, WIFI_PWD, 5000))
				{
					printf("\r\n [3] ����WIFI�ɹ�");
					//LCD_PrintChinese(0,3,g_chinese_fonts_5,8);
					LCD_PrintString(0,3,"Join wifi ok");
					
					sta = 3;
					errnum = 0;
					bsp_DelayMS(1000);//�ӳ�1s������һ��
					LCD_Clear();
				}
				else
				{
					LCD_Clear();
					bsp_DelayMS(200);
					printf("\r\n [3] ����WIFIʧ��");
					//LCD_PrintChinese(0,3,g_chinese_fonts_6,8);
					LCD_PrintString(0,3,"Join wifi error");
					
					errnum++;
					if(errnum > 20)
					{
						errnum = 0;
						resettime++;
						sta = 0;
					}
				}
				//sta = 3;
				break;
			case 3:
				ESP8266_SendAT("AT+MQTTUSERCFG=0,1,\"123\",\"admin\",\"admin\",0,0,\"\"");//����MQTT
				if(ESP8266_WaitResponse("OK",500)==1) //�յ�OK
				{
					LCD_Clear();
					printf("\r\n [4] MQTT����ģʽ���óɹ���");
					//LCD_PrintChinese(0,3,g_chinese_fonts_7,12);
					LCD_PrintString(0,3,"MQTT SET OK");
					
					sta = 4;
					errnum = 0;
					bsp_DelayMS(1000);//�ӳ�1s������һ��

				}
				else
				{
					LCD_Clear();
					bsp_DelayMS(200);
					printf("\r\n [4] MQTT����ģʽ����ʧ�ܣ�");
					//LCD_PrintChinese(0,3,g_chinese_fonts_8,12);
					LCD_PrintString(0,3,"MQTT SET false");
					
					errnum++;
					if(errnum > 20)
					{
						errnum = 0;
						resettime++;
						sta = 0;
					}
				}
				break;
			case 4:
				ESP8266_SendAT("AT+MQTTCONN=0,\"broker.emqx.io\",1883,0");//����MQTT
				if(ESP8266_WaitResponse("OK",500)==1) //�յ�OK
				{
					LCD_Clear();
					printf("\r\n [5] MQTT���������ӳɹ���");
					//LCD_PrintChinese(0,3,g_chinese_fonts_9,11);
					LCD_PrintString(0,3,"MQTT Connect ok");
					sta = 5;
					errnum = 0;
					bsp_DelayMS(1000);//�ӳ�1s������һ��
					
				}
				else
				{
					LCD_Clear();
					bsp_DelayMS(200);
					printf("\r\n [5] MQTT����������ʧ�ܣ�");
					//LCD_PrintChinese(0,3,g_chinese_fonts_10,11);
					LCD_PrintString(0,3,"MQTT Connect false");
					errnum++;
					if(errnum > 20)
					{
						errnum = 0;
						resettime++;
						sta = 0;
					}
				}
				break;
			case 5:
				sprintf(cmd_buf,"AT+MQTTSUB=0,\"%s\",0",topicdevsub);//�����ʽ��
				ESP8266_SendAT(cmd_buf);//����MQTT
				if(ESP8266_WaitResponse("OK",500)==1) //�յ�OK
				{
					LCD_Clear();
					printf("\r\n [6] MQTT���ⶩ�ĳɹ���");
					//LCD_PrintChinese(0,3,g_chinese_fonts_11,10);
					LCD_PrintString(0,3,"MQTT subscribe ok");
					sta = 6;
					errnum = 0;
					bsp_DelayMS(1000);//�ӳ�1s������һ��
					
				}
				else
				{
					LCD_Clear();
					bsp_DelayMS(200);
					printf("\r\n [6] MQTT���ⶩ��ʧ�ܣ�");
					//LCD_PrintChinese(0,3,g_chinese_fonts_12,10);
					LCD_PrintString(0,3,"MQTT subscribe false");
					
					errnum++;
					if(errnum > 20)
					{
						errnum = 0;
						resettime++;
						sta = 0;
					}
				}
				break;
			case 6:
				break;
			default:
				break;
		}
	}
}


void ESP8266_ReciveNew(uint8_t _byte)
{
	/*
		3.5���ַ���ʱ������ֻ������RTUģʽ���棬��ΪRTUģʽû�п�ʼ���ͽ�������
		�������ݰ�֮��ֻ�ܿ�ʱ���������֣�Modbus�����ڲ�ͬ�Ĳ������£����ʱ���ǲ�һ���ģ�
		���Ծ���3.5���ַ���ʱ�䣬�����ʸߣ����ʱ������С�������ʵͣ����ʱ������Ӧ�ʹ�

		4800  = 7.297ms
		9600  = 3.646ms
		19200  = 1.771ms
		38400  = 0.885ms
	*/
	
	
	/* �յ�һ���ֽڿ�ʼ��ʱ�� ��ʱ��ʱ�䵽�˴����ж� ��g_tESP8266=1 */
	uint32_t timeout;

	g_esp8266_timeout = 0;
	
	timeout = 35000000 / 115200;			/* ���㳬ʱʱ�䣬��λus 35000000*/
	
	/* Ӳ����ʱ�жϣ���ʱ����us Ӳ����ʱ��1����ADC, ��ʱ��2����Modbus */
	bsp_StartHardTimer(1, timeout, (void *)ESP8266_RxTimeOut);

	if (g_tESP8266.RxCount < S_RX_BUF_SIZE)
	{
		g_tESP8266.RxBuf[g_tESP8266.RxCount++] = _byte;
	}
}


/* ��ʱ��ʱ�䵽��ִ�иú��� */
static void ESP8266_RxTimeOut(void)
{
	g_esp8266_timeout = 1;
}


/*
*********************************************************************************************************


�������������strchr�������ĵ���������ָ��ch�ַ���str�ַ����еڼ��γ��֣�
���磬����������Ϊ1����������Ĺ��ܾͺ�strchrһ�����������Ϊ2,��������ͷ���һ��ָ��ch�ַ���str�ַ����еڶ��γ��ֵ�λ�õ�ָ�롣

param:

str: ���ݱ���
ch����Ѱ���ַ�
which���ڼ���
����ֵ�����ҵ����ַ��ĺ�һ���ַ���ָ��
*********************************************************************************************************
*/

char *my_strnchr(char const *str, int ch, int which) {
    char *rs = NULL;
    while(--which >= 0 && (rs = strchr(str, ch)) != NULL) {
        str = rs + 1;
    }
    return rs + 1;
}


/*
*********************************************************************************************************
*	�� �� ��: MODS_Poll
*	����˵��: �������ݰ�. �����������������á�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ESP8266_Poll(void)
{
	uint16_t addr;
	uint16_t crc1;
	char *result = NULL;
	cJSON *json;    
	uint8_t out1 ,out2;
	/* ����3.5���ַ�ʱ���ִ��MODH_RxTimeOut()������ȫ�ֱ��� g_rtu_timeout = 1; ֪ͨ������ʼ���� */
	if (g_esp8266_timeout == 0)	
	{
		return;								/* û�г�ʱ���������ա���Ҫ���� g_tModS.RxCount */
	}
	
	g_esp8266_timeout = 0;	 					/* ���ݽ������ ���־ */

	if (g_tESP8266.RxCount < 4)				/* ���յ�������С��4���ֽھ���Ϊ���� */
	{
		goto err_ret;
	}
	
	//�ӵ�3�����ŵ���һλ��ʼ	
	result = my_strnchr((char *)g_tESP8266.RxBuf,',',3);

	printf("result = %s",result);

	/*
*********************************************************************************************************
	ʹ��cJson��������
	���յ����ݸ�ʽ:
	{
	
		"LED1":1,
		"LED2":2   //���һ�����ݲ���Ҫ�Ӷ���
	
	}
*********************************************************************************************************
*/
	//����json����
	json = cJSON_Parse(result);
	
	if(json != NULL)
	{
		/* LEDѡ�� */
		out1 = cJSON_GetObjectItem(json,"LED")->valueint;
		out2 = cJSON_GetObjectItem(json,"alerm")->valueint;
//		out1 = cJSON_GetObjectItem(json,"LED3")->valueint;
//		out1 = cJSON_GetObjectItem(json,"LED4")->valueint;
//		out1 = cJSON_GetObjectItem(json,"LED5")->valueint;
		
		if(out1 == 1)
		{
			printf("led on\r\n");
			Led_Control(LED_GREEN,1);
		}
		else
		{
			printf("led off\r\n");
			Led_Control(LED_GREEN,0);
		}
		if(out2 == 1)
		{
			PassiveBuzzer_Control(1);
		}
		else
		{
			PassiveBuzzer_Control(0);
		}
	}
	else
	{
		printf("JSON��������\r\n");
		//���buf
		memset(g_tESP8266.RxBuf,0,S_RX_BUF_SIZE);
	}
	cJSON_Delete(json);
	free(json);
		
	
	
err_ret:
	memset(g_tESP8266.RxBuf,0,S_RX_BUF_SIZE);
	g_tESP8266.RxCount = 0;					/* ��������������������´�֡ͬ�� */
}




/*
*********************************************************************************************************
*	�� �� ��: ESP8266_PrintRxData
*	����˵��: ��ӡSTM32��ESP8266�յ������ݵ�COM1���ڣ���Ҫ���ڸ��ٵ���
*	��    ��: _ch : �յ�������
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ESP8266_PrintRxData(uint8_t _ch)
{
	#ifdef ESP8266_TO_COM1_EN
		comSendChar(COM1, _ch);		/* �����յ����ݴ�ӡ�����Դ���1 */
	#endif
}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_PowerOn
*	����˵��: ��ESP8266ģ���ϵ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ESP8266_PowerOn(void)
{
	/* WIFIģ���ϵ�ʱ������74880�����ʴ�ӡ������Ϣ:
		 ets Jan  8 2013,rst cause:1, boot mode:(3,6)

		load 0x40100000, len 25052, room 16 
		tail 12
		chksum 0x0b
		ho 0 tail 12 room 4
		load 0x3ffe8000, len 3312, room 12 
		tail 4
		chksum 0x53
		load 0x3ffe8cf0, len 6576, room 4 
		tail 12
		chksum 0x0d
		csum 0x0d	    <-----  ����ʶ�� csum �����Զ��л������������� 
	*/

	//ESP_CH_PD_0();

	comSetBaud(COM_ESP8266, 74880);	/* ���ö˿ڲ�����Ϊ 74880 */

	//ESP_CH_PD_1();

	//ESP8266_Reset();

	/* �ȴ�ģ������ϵ磬��ʱ500ms �Զ��˳� */
	ESP8266_WaitResponse("csum", 1000);	/* �ȵȴ� csum */
	ESP8266_WaitResponse("\n", 1000);	/* �ٵȴ��س������ַ����� */

	comSetBaud(COM_ESP8266,115200);	/* 1��ʾӲ������CRS RTS��Ч;  0��ʾ����Ӳ������ */

	/* �ȴ�ģ������ϵ磬�ж��Ƿ���յ� ready */
	ESP8266_WaitResponse("ready", 5000);
	
	// ESP8266_SendAT("AT+RST");
	// ESP8266_WaitResponse("ready", 5000);
}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_PowerOff
*	����˵��: ����ESP8266ģ��ػ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ESP8266_PowerOff(void)
{
	//ESP_CH_PD_0();
}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_PowerOn
*	����˵��: ��ESP8266ģ���ϵ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
//void ESP8266_Reset(void)
//{
//	ESP_RESET_0();
//	bsp_DelayMS(20);
//	ESP_RESET_1();

//	bsp_DelayMS(10);
//}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_EnterISP
*	����˵��: ����ESP8266ģ�����̼�����ģʽ
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ESP8266_EnterISP(void)
{

}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_ExitISP
*	����˵��: ����ESP8266ģ���˳��̼�����ģʽ
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ESP8266_ExitISP(void)
{

}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_9600to115200
*	����˵��: 9600�������л���115200
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ESP8266_9600to115200(void)
{
	comSetBaud(COM_ESP8266, 9600);			/* ģ��ȱʡ��9600bps */
	ESP8266_SendAT("AT+CIOBAUD=115200");	/* �� 9600bps ����ָ���л�Ϊ 115200 */
	ESP8266_WaitResponse("OK\r\n", 2000);	/* ��� OK ��ģ�鰴 9600 Ӧ��� */
	comSetBaud(COM_ESP8266, 115200);		/* �л�STM32�Ĳ�����Ϊ 115200 */

	/* �л�Ϊ Stationģʽ */
	bsp_DelayMS(100);
	ESP8266_SendAT("AT+CWMODE=1");
	ESP8266_WaitResponse("OK\r\n", 2000);
	bsp_DelayMS(1500);
	ESP8266_SendAT("AT+RST");
}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_WaitResponse
*	����˵��: �ȴ�ESP8266����ָ����Ӧ���ַ���, ���԰��������ַ���ֻҪ������ȫ���ɷ��ء�
*	��    ��: _pAckStr : Ӧ����ַ����� ���Ȳ��ó���255
*			 _usTimeOut : ����ִ�г�ʱ��0��ʾһֱ�ȴ�. >����ʾ��ʱʱ�䣬��λ1ms
*	�� �� ֵ: 1 ��ʾ�ɹ�  0 ��ʾʧ��
*********************************************************************************************************
*/
uint8_t ESP8266_WaitResponse(char *_pAckStr, uint16_t _usTimeOut)
{
	uint8_t ucData;
	uint16_t pos = 0;
	uint32_t len;
	uint8_t ret;

	len = strlen(_pAckStr);
	if (len > 255)
	{
		return 0;
	}

	/* _usTimeOut == 0 ��ʾ���޵ȴ� */
	if (_usTimeOut > 0)
	{
		bsp_StartTimer(ESP8266_TMR_ID, _usTimeOut);		/* ʹ�������ʱ��3����Ϊ��ʱ���� */
	}
	while (1)
	{
		bsp_Idle();				/* CPU����ִ�еĲ����� �� bsp.c �� bsp.h �ļ� */

		if (_usTimeOut > 0)
		{
			if (bsp_CheckTimer(ESP8266_TMR_ID))
			{
				ret = 0;	/* ��ʱ */
				break;
			}
		}

		if (comGetChar(COM_ESP8266, &ucData))
		{
			ESP8266_PrintRxData(ucData);		/* �����յ����ݴ�ӡ�����Դ���1 */

			if (ucData == _pAckStr[pos])
			{
				pos++;
				
				if (pos == len)
				{
					ret = 1;	/* �յ�ָ����Ӧ�����ݣ����سɹ� */
					break;
				}
			}
			else
			{
				pos = 0;
			}
		}
	}
	return ret;
}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_ReadLine
*	����˵��: ��ȡESP8266���ص�һ��Ӧ���ַ���(0x0D 0x0A����)���ú��������ַ��䳬ʱ�жϽ����� ��������Ҫ����AT����ͺ�����
*	��    ��: _pBuf : ���ģ�鷵�ص������ַ���
*			  _usBufSize : ��������󳤶�
*			 _usTimeOut : ����ִ�г�ʱ��0��ʾһֱ�ȴ�. >0 ��ʾ��ʱʱ�䣬��λ1ms
*	�� �� ֵ: 0 ��ʾ���󣨳�ʱ��  > 0 ��ʾӦ������ݳ���
*********************************************************************************************************
*/
uint16_t ESP8266_ReadLine(char *_pBuf, uint16_t _usBufSize, uint16_t _usTimeOut)
{
	uint8_t ucData;
	uint16_t pos = 0;
	uint8_t ret;

	/* _usTimeOut == 0 ��ʾ���޵ȴ� */
	if (_usTimeOut > 0)
	{
		bsp_StartTimer(ESP8266_TMR_ID, _usTimeOut);		/* ʹ�������ʱ����Ϊ��ʱ���� */
	}
	while (1)
	{
		bsp_Idle();				/* CPU����ִ�еĲ����� �� bsp.c �� bsp.h �ļ� */

		if (bsp_CheckTimer(ESP8266_TMR_ID))
		{
			_pBuf[pos] = 0;	/* ��β��0�� ���ں���������ʶ���ַ������� */
			ret = pos;		/* �ɹ��� �������ݳ��� */
			break;
		}

		if (comGetChar(COM_ESP8266, &ucData))
		{
			ESP8266_PrintRxData(ucData);		/* �����յ����ݴ�ӡ�����Դ���1 */

			bsp_StartTimer(ESP8266_TMR_ID, 500);
			_pBuf[pos++] = ucData;		/* ������յ������� */
			if (ucData == 0x0A)
			{
				_pBuf[pos] = 0;
				ret = pos;		/* �ɹ��� �������ݳ��� */
				break;
			}
		}
	}
	return ret;
}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_SendAT
*	����˵��: ��ģ�鷢��AT��� �������Զ���AT�ַ���������<CR>�ַ�
*	��    ��: _Str : AT�����ַ�����������ĩβ�Ļس�<CR>. ���ַ�0����
*	�� �� ֵ: ��T
*********************************************************************************************************
*/
void ESP8266_SendAT(char *_Cmd)
{
	comSendBuf(COM_ESP8266, (uint8_t *)_Cmd, strlen(_Cmd));
	comSendBuf(COM_ESP8266, (uint8_t *)"\r\n", 2);
}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_SetWiFiMode
*	����˵��: ����WiFiģ�鹤��ģʽ
*	��    ��: _mode : 1 = Stationģʽ,  2 = APģʽ,  3 = AP��Stationģʽ
*	�� �� ֵ: 0 ��ʾʧ�ܡ� 1��ʾ�ɹ�
*********************************************************************************************************
*/
uint8_t ESP8266_SetWiFiMode(uint8_t _mode)
{
	char cmd_buf[30];
	
	if (_mode == 0 || _mode > 3)
	{
		_mode = 3;
	}
	sprintf(cmd_buf, "AT+CWMODE=%d", _mode);
	ESP8266_SendAT(cmd_buf);
	if (ESP8266_WaitResponse("OK\r\n", 2000) == 0)
	{
		return 0;
	}
	
	return 1;
}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_CIPMUX
*	����˵��: ����������ģʽ
*	��    ��: _mode : 0,��ʾ�رգ� 1��ʾ����
*	�� �� ֵ: 0 ��ʾʧ�ܡ� 1��ʾ�ɹ�
*********************************************************************************************************
*/
uint8_t ESP8266_CIPMUX(uint8_t _mode)
{
	char cmd_buf[30];
	
	if (_mode > 0)
	{
		_mode = 1;
	}
	sprintf(cmd_buf, "AT+CIPMUX=%d", _mode);
	ESP8266_SendAT(cmd_buf);
	if (ESP8266_WaitResponse("OK\r\n", 200) == 0)
	{
		return 0;
	}
	
	return 1;
}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_Set_AP_IP
*	����˵��: AT+CIPAP ���� AP �� IP ��
*	��    ��: _ip :AP��IP��ַ����׼�ַ���
*	�� �� ֵ: 0 ��ʾʧ�ܡ� 1��ʾ�ɹ�
*********************************************************************************************************
*/
uint8_t ESP8266_Set_AP_IP(char *_ip)
{
	char cmd_buf[30];
	
	sprintf(cmd_buf, "AT+CIPAP=\"%s\"", _ip);
	ESP8266_SendAT(cmd_buf);
	if (ESP8266_WaitResponse("OK\r\n", 500) == 0)
	{
		return 0;
	}
	
	return 1;
}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_Set_AP_NamePass
*	����˵��: ����SoftAP�����֣����ܷ�ʽ������.  ���ܷ�ʽΪ �� 
*	��    ��: _name :AP�����֣��ַ�������������� 64 �ֽ� ASCII
*			 _pwd : AP�����룬�ַ�������������� 64 �ֽ� ASCII
*			 _ch : ͨ����
*	�� �� ֵ: 0 ��ʾʧ�ܡ� 1��ʾ�ɹ�
*********************************************************************************************************
*/
uint8_t ESP8266_Set_AP_NamePass(char *_name, char * _pwd, uint8_t _ch, uint8_t _ecn)
{
	char cmd_buf[40];

	/* AT+CWSAP="ESP8266","1234567890",5,3 */	
	sprintf(cmd_buf, "AT+CWSAP=\"%s\",\"%s\",%d,%d", _name, _pwd, _ch, _ecn);
	ESP8266_SendAT(cmd_buf);
	if (ESP8266_WaitResponse("OK\r\n", 500) == 0)
	{
		return 0;
	}
	
	return 1;
}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_CreateTCPServer
*	����˵��: ����һ��TCP����ˡ� ���������ӵ�AP֮����С� ��Ҫ�����ö�����
*	��    �Σ�_TcpPort : TCP �˿ں�
*	�� �� ֵ: 0 ��ʾʧ�ܡ� 1��ʾ����TCP�ɹ�
*********************************************************************************************************
*/
uint8_t ESP8266_CreateTCPServer(uint16_t _TcpPort)
{
	char cmd_buf[30];
	
	ESP8266_SendAT("AT+CIPMUX=1");	/* ���������� */
	if (ESP8266_WaitResponse("OK", 2000) == 0)
	{
		return 0;
	}
	
	/* ����TCP server, �˿�Ϊ _TcpPort */
	sprintf(cmd_buf, "AT+CIPSERVER=1,%d", _TcpPort);
	ESP8266_SendAT(cmd_buf);	
	if (ESP8266_WaitResponse("OK", 2000) == 0)
	{
		return 0;
	}

	ESP8266_SendAT("ATE0");		/* �رջ��Թ��ܣ��������͵��ַ���ģ�����践�� */
	if (ESP8266_WaitResponse("OK", 10000) == 0)
	{
		return 0;
	}
	
	return 1;
}


/*
*********************************************************************************************************
*	�� �� ��: ESP8266_CreateUDPServer
*	����˵��: ����һ��UDP����ˡ� ���������ӵ�AP֮����С� ��Ҫ�����ö�����
*	��    ��:   _id : ����ID, 0-4
*				_LaocalPort : UDP �˿ں�
*	�� �� ֵ: 0 ��ʾʧ�ܡ� 1��ʾ����UDP�ɹ�
*********************************************************************************************************
*/
uint8_t ESP8266_CreateUDPServer(uint8_t _id, uint16_t _LaocalPort)
{
	char cmd_buf[64];

	ESP8266_SendAT("AT+CIPMUX=1");	/* ���������� */
	if (ESP8266_WaitResponse("OK", 2000) == 0)
	{
		return 0;
	}
	
	/* ������ UDP */
	//AT+CIPSTART=0,"UDP","255.255.255.255",8080,8080,0 
	sprintf(cmd_buf, "AT+CIPSTART=%d,\"UDP\",\"255.255.255.255\",8080,%d, 0", _id, _LaocalPort);
	
	//AT+CIPSTART="UDP","255.255.255.255",8080,8080,1	
	//sprintf(cmd_buf, "AT+CIPSTART=\"UDP\",\"255.255.255.255\",8080,%d,2", _LaocalPort);
	
	ESP8266_SendAT(cmd_buf);	
	if (ESP8266_WaitResponse("OK\r\n", 3000) == 0)
	{
		return 0;
	}
	
	ESP8266_SendAT("ATE0");		/* �رջ��Թ��ܣ��������͵��ַ���ģ�����践�� */
	if (ESP8266_WaitResponse("OK", 10000) == 0)
	{
		return 0;
	}
	
	return 1;
}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_LinkTCPServer
*	����˵��: ���ӵ�һ��TCP����ˡ�  ��(+CIPMUX=1) ������ģʽ��
*	��    ��: _id : ���ӵ�id��
*			  _server_ip : ������������IP��ַ
*			  _TcpPort : TCP �˿ں�
*	�� �� ֵ: 0 ��ʾʧ�ܡ� 1��ʾ����TCP�ɹ�
*********************************************************************************************************
*/
uint8_t ESP8266_LinkTCPServer(uint8_t _id, char *_server_ip, uint16_t _TcpPort)
{
	char cmd_buf[30];
	
	ESP8266_SendAT("AT+CIPMUX=1");	/* ���������� */
	if (ESP8266_WaitResponse("OK", 2000) == 0)
	{
		return 0;
	}
	
#if 0	/* ������ */
	//AT+CIPSTART="TCP","192.168.101.110",1000
	sprintf(cmd_buf, "AT+CIPSTART=\"TCP\",\"%s\",%d",_server_ip, _TcpPort);
#else	/* ������ */
	//AT+CIPSTART=0, "TCP","192.168.101.110",1000
	sprintf(cmd_buf, "AT+CIPSTART=%d,\"TCP\",\"%s\",%d", _id, _server_ip, _TcpPort);
#endif	
	
	ESP8266_SendAT(cmd_buf);	
	if (ESP8266_WaitResponse("OK\r\n", 3000) == 0)
	{
		return 0;
	}
	
	ESP8266_SendAT("ATE0");		/* �رջ��Թ��ܣ��������͵��ַ���ģ�����践�� */
	if (ESP8266_WaitResponse("OK", 10000) == 0)
	{
		return 0;
	}
	
	return 1;
}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_SendTcpUdp
*	����˵��: ����TCP��UDP���ݰ�
*	��    ��: _id : ������ʱ������ID ��0-4��
*			  _databuf ����
*			  _len ���ݳ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
uint8_t ESP8266_SendTcpUdp(uint8_t _id, uint8_t *_databuf, uint16_t _len)
{
	char buf[32];
	uint8_t ret = 1;

	if (_len > 2048)
	{
		_len = 2048;
	}

	sprintf(buf, "AT+CIPSEND=%d,%d\r\n", _id, _len);
	comSendBuf(COM_ESP8266, (uint8_t *)buf, strlen(buf));

	ret = ESP8266_WaitResponse(">", 1000);
	
	if(ret == 0) 
	{
		return 0;
	}

	comSendBuf(COM_ESP8266, _databuf, _len);
	ret = ESP8266_WaitResponse("SEND OK", 8000);
	
	if(ret == 0) 
	{
		return 0;
	}
	
	return 1;
}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_CloseTcpUdp
*	����˵��: �ر�TCP��UDP����. ���ڶ�·����
*	��    ��: _databuf ����
*			 _len ���ݳ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ESP8266_CloseTcpUdp(uint8_t _id)
{
	char buf[32];

	ESP8266_SendAT("ATE1");		/* �򿪻��Թ��� */
	ESP8266_WaitResponse("SEND OK", 50);
	
	sprintf(buf, "AT+CIPCLOSE=%d", _id);
	ESP8266_SendAT(buf);	
	ESP8266_WaitResponse("OK", 200);
}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_GetLocalIP
*	����˵��: ��ѯ����IP��ַ��MAC
*	��    ��: _ssid : AP�����ַ���
*			  _pwd : �����ַ���
*	�� �� ֵ: 1 ��ʾOK�� 0 ��ʾδ֪
*********************************************************************************************************
*/
uint8_t ESP8266_GetLocalIP(char *_ip, char *_mac)
{
	char buf[64];
	uint8_t i, m;
	uint8_t ret = 0;
	uint8_t temp;
	
	ESP8266_SendAT("AT+CIFSR");
	
	/*��ģ�齫Ӧ��:
		
	+CIFSR:STAIP,"192.168.1.18"
	+CIFSR:STAMAC,"18:fe:34:a6:44:75"
	
	OK	
	*/
	
	_ip[0] = 0;
	_mac[0] = 0;
	for (i = 0; i < 4; i++)
	{
		ESP8266_ReadLine(buf, sizeof(buf), 500);
		if (memcmp(buf, "+CIFSR:STAIP", 12) == 0)
		{
			
			for (m = 0; m < 20; m++)
			{
				temp = buf[14 + m];
				_ip[m] = temp;
				if (temp == '"')
				{
					_ip[m] = 0;
					ret = 1;
					break;
				}
			}
		}
		else if (memcmp(buf, "+CIFSR:STAMAC,", 14) == 0)
		{
			for (m = 0; m < 20; m++)
			{
				temp = buf[15 + m];
				_mac[m] = temp;
				if (temp == '"')
				{
					_mac[m] = 0;
					break;
				}
			}
		}
		else if (memcmp(buf, "OK", 2) == 0)
		{
			break;
		}
	}
	return ret;
}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_JoinAP
*	����˵��: ����AP
*	��    ��: _ssid : AP�����ַ���
*			  _pwd : �����ַ���
*	�� �� ֵ: 1 ��ʾ 0K  0 ��ʾʧ��
*********************************************************************************************************
*/
uint8_t ESP8266_JoinAP(char *_ssid, char *_pwd, uint16_t _timeout)
{
	char buf[64];
	uint8_t ret;

	sprintf(buf, "AT+CWJAP=\"%s\",\"%s\"", _ssid, _pwd);
	ESP8266_SendAT(buf);

#if	0
	if (ESP8266_ReadLine(buf, 64, _timeout))
	{
		/* ATE1���������������Ե���� */
		if (memcmp(buf, "AT+CWJAP", 8) == 0)		/* ��1�ζ������� ����� */
		{
			ESP8266_ReadLine(buf, 64, _timeout);	/* ����ǻس� */
			ESP8266_ReadLine(buf, 64, _timeout);	/* ����Ƕ�Ӧ���OK */
			
			if (memcmp(buf, "OK", 2) == 0)
			{
				return 1;
			}
		}		
		else	/* ATE0 �޻��Ե���� */
		{
			ret = ESP8266_WaitResponse("OK\r\n", _timeout);
			if (ret == 1)
			{
				return 1;
			}
		}
	}
#else

	ret = ESP8266_WaitResponse("OK\r\n", _timeout);
	if (ret == 1)
	{
		return 1;
	}

#endif

	return 0;
}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_QuitAP
*	����˵��: �˳���ǰ��AP����
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ESP8266_QuitAP(void)
{
	ESP8266_SendAT("AT+ CWQAP");
}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_ScanAP
*	����˵��: ɨ��AP����������_pList �ṹ������. �˺�����ռ���5��ʱ�䡣ֱ���յ�OK��ERROR��
*	��    ��: _pList : AP�б�����;
*			  _MaxNum : ���������AP��������Ҫ�Ƿ�ֹ�����������
*	�� �� ֵ: -1 ��ʾʧ��; 0 ��ʾ������0��; 1��ʾ1����
*********************************************************************************************************
*/
int16_t ESP8266_ScanAP(WIFI_AP_T *_pList, uint16_t _MaxNum)
{
	uint16_t i;
	uint16_t count;
	char buf[128];
	WIFI_AP_T *p;
	char *p1, *p2;
	uint16_t timeout;

	buf[127] = 0;
	ESP8266_SendAT("AT+CWLAP");
	
	p = (WIFI_AP_T *)_pList;
	count = 0;
	timeout = 8000;
	for (i = 0; i < _MaxNum; i++)
	{
		ESP8266_ReadLine(buf, 128, timeout);
		if (memcmp(buf, "OK", 2) == 0)
		{
			break;
		}
		else if (memcmp(buf, "ERROR", 5) == 0)
		{
			break;
		}
		else if (memcmp(buf, "+CWLAP:", 7) == 0)
		{		
			p1 = buf;
			
			/* +CWLAP:(4,"BaiTu",-87,"9c:21:6a:3c:89:52",1) */
			/* �������ܷ�ʽ */
			p1 = strchr(p1, '(');	/* ������(*/
			p1++;
			p->ecn = str_to_int(p1);
			
			/* ����ssid */
			p1 = strchr(p1, '"');	/* ��������1���ֺ� */
			p1++;
			p2 = strchr(p1, '"');	/* ��������2���ֺ� */
			memcpy(p->ssid, p1, p2 - p1);
			p->ssid[p2 - p1] = 0;
			
			/* ���� rssi */
			p1 = strchr(p2, ',');	/* ����������*/
			p1++;
			p->rssi = str_to_int(p1);
			
			/* ����mac */
			p1 = strchr(p1, '"');	/* �������ֺ�*/
			p1++;
			p2 = strchr(p1, '"');	/* �������ֺ�*/
			memcpy(p->mac, p1, p2 - p1);
			p->mac[p2 - p1] = 0;
			
			/* ����ch */
			p1 = strchr(p2, ',');	/* ����������*/
			p1++;
			p->ch = str_to_int(p1);
			
			/* ��Ч��AP���� */
			count++;
			
			p++;
			
			timeout = 2000;
		}
	}
	
	return count;
}

/*
*********************************************************************************************************
*	�� �� ��: ESP8266_RxNew
*	����˵��: ����������֡ +IPD
*	��    ��: _pRxBuf : ���յ������ݴ���ڴ˻�����
*			 _link_id : TCP���ӵ�id�� ʶ���Ǿ������ֻ������������ڷ�����
*	�� �� ֵ: ���յ������ݳ���. 0 ��ʾ������
*********************************************************************************************************
*/
uint16_t ESP8266_RxNew(uint8_t *_pRxBuf, uint8_t *_link_id)
{
	uint8_t ucData;
	static uint8_t s_buf[2048];	/* Լ���1460 */
	static uint16_t s_len = 0;
	static uint8_t s_flag = 0;
	static uint16_t s_data_len = 0;
	char *p1;
	
	/* +IPD,0,7:ledon 1 */
	while (comGetChar(COM_ESP8266, &ucData))
	{
		//ESP8266_PrintRxData(ucData);		/* �����յ����ݴ�ӡ�����Դ���1 */

		if (s_flag == 0)
		{
			if (s_len < sizeof(s_buf))
			{
				s_buf[s_len++] = ucData;		/* ������յ������� */
			}			
			if (ucData == '+')
			{
				s_len = 1;
				s_data_len = 0;
				s_buf[0] = 0;
			}
			if (s_len > 7 && ucData == ':')
			{
				p1 = (char *)&s_buf[5];
				*_link_id = str_to_int(p1);		/* ����������id */
				
				p1 = (char *)&s_buf[7];
				s_data_len = str_to_int(p1);	/* ���������ݰ����� */
				s_flag = 1;	
				s_len = 0;
			}
		}
		else
		{
			if (s_len < sizeof(s_buf))
			{
				s_buf[s_len++] = ucData;		/* ������յ������� */
				
				if (s_len == s_data_len)
				{
					s_flag = 0;
					s_len = 0;
					
					memcpy(_pRxBuf, s_buf, s_data_len);
					
					return s_data_len;
				}
			}	
			else
			{
				s_flag = 0;
			}
		}

	}
	return 0;
}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
