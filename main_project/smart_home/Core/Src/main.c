/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "bsp.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern char topicdevsub[];
extern char topicdevpub[];
char g_at_cmd_buf[100];

int testtemp = 0,testhum = 0;
float testlight = 0.0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	bsp_Init();
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */


  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */


  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */

  /* USER CODE BEGIN 2 */
  uint8_t val;
  int len;
  extern uint8_t g_chinese_fonts[3][32];
  //开启定时器计时2s 第一个参数位定时器序号 再开一个可设置为1 
  bsp_StartAutoTimer(0,2000);
  

  //printf("hello");
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	  DHT11_Test();
//	  LightSensor_Test();
	  //解析数据包
	  ESP8266_Poll();
	  
//	   
//    /* USER CODE END WHILE */
	  
	//定时器时间到返回true
	  if(bsp_CheckTimer(0))
	  {

			if (DHT11_Read(&testhum, &testtemp) !=0 )
			{
				printf("\n\rdht11 read err!\n\r");
				DHT11_Init();
			}
			else if(LightSensor_Read(&testlight)!=0 )
			{
				printf("\n\rlight sensor read err!\n\r");
			}

			else
			{
				//LCD_PrintString(0, 0, "DHT11:");
				LCD_PrintString(0, 0, "Humidity Temp");
				len = LCD_PrintSignedVal(0, 2, testhum);
				LCD_PutChar(len, 2, '%');
				
				len = LCD_PrintSignedVal(9, 2, testtemp);
				LCD_PutChar(11, 2, '%');
				
				LCD_PrintString(0, 4, "Light Sensor:");
				LCD_PrintSignedVal(0, 6, testlight);
				
				sprintf(g_at_cmd_buf,"AT+MQTTPUB=0,\"%s\",\"{\\\"TEMP\\\":%d\\,\\\"HUM\\\":%d\\,\\\"LIGHT\\\":%.2f}\",0,0",topicdevpub,testtemp,testhum,testlight);
				ESP8266_SendAT(g_at_cmd_buf);


	
	  }



    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
  }

