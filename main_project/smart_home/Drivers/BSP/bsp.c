/*
*********************************************************************************************************
*
*	模块名称 : BSP模块(For STM32F429)
*	文件名称 : bsp.c
*	版    本 : V1.0
*	说    明 : 这是硬件底层驱动程序的主文件。每个c文件可以 #include "bsp.h" 来包含所有的外设驱动模块。
*			   bsp = Borad surport packet 板级支持包
*	修改记录 :
*		版本号  日期         作者       说明
*		V1.0    2018-07-29  Eric2013   正式发布
*
*	Copyright (C), 2018-2030, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/
#include "bsp.h"



/*
*********************************************************************************************************
*	                                   函数声明
*********************************************************************************************************
*/
static void SystemClock_Config(void);


/*
*********************************************************************************************************
*	函 数 名: bsp_Init
*	功能说明: 初始化所有的硬件设备。该函数配置CPU寄存器和外设的寄存器并初始化一些全局变量。只需要调用一次
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_Init(void)
{
	/* 
       STM32H429 HAL 库初始化，此时系统用的还是F429自带的16MHz，HSI时钟:
	   - 调用函数HAL_InitTick，初始化滴答时钟中断1ms。
	   - 设置NVIV优先级分组为4。
	 */
	HAL_Init();

	/* 
       配置系统时钟到168MHz
       - 切换使用HSE。
       - 此函数会更新全局变量SystemCoreClock，并重新配置HAL_InitTick。
    */
	SystemClock_Config();
	
	MX_GPIO_Init();
	MX_TIM1_Init();
	MX_I2C1_Init();
	MX_ADC1_Init();
	Key_Init();
	
	/* 
	   Event Recorder：
	   - 可用于代码执行时间测量，MDK5.25及其以上版本才支持，IAR不支持。
	   - 默认不开启，如果要使能此选项，务必看V5开发板用户手册第8章
	*/	
	
//	bsp_InitKey();    	/* 按键初始化，要放在滴答定时器之前，因为按钮检测是通过滴答定时器扫描 */
	bsp_InitTimer();  	/* 初始化滴答定时器 */
	bsp_InitUart();		/* 初始化串口 */
//	bsp_InitExtIO();    /* 初始化扩展IO */
//	bsp_InitLed();    	/* 初始化LED */
	DHT11_Init();
	LightSensor_Init();
//	BEEP_InitHard();    /* 初始化蜂鸣器 */
	LCD_Init();
	LCD_Clear();
	Led_Init();
//	LCD_Clear();
	bsp_InitESP8266();
	bsp_InitESP8266MQTT();/* 初始化MQTT */
	//PassiveBuzzer_Init();
	
	

	
	

}

/*
****************************************************** ***************************************************
*	函 数 名: SystemClock_Config
*	功能说明: 初始化系统时钟
*            	System Clock source            = PLL (HSE)
*            	SYSCLK(Hz)                     = 168000000 (CPU Clock)
*            	HCLK = SYSCLK / 1              = 168000000 (AHB1Periph)
*            	PCLK2 = HCLK / 2               = 84000000  (APB2Periph)
*            	PCLK1 = HCLK / 4               = 42000000  (APB1Periph)
*            	HSE Frequency(Hz)              = 25000000
*           	PLL_M                          = 25
*            	PLL_N                          = 336
*            	PLL_P                          = 2
*            	PLL_Q                          = 4
*            	VDD(V)                         = 3.3
*            	Flash Latency(WS)              = 5
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */



/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
	  
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */


/*
*********************************************************************************************************
*	函 数 名: bsp_RunPer10ms
*	功能说明: 该函数每隔10ms被Systick中断调用1次。详见 bsp_timer.c的定时中断服务程序。一些处理时间要求不严格的
*			任务可以放在此函数。比如：按键扫描、蜂鸣器鸣叫控制等。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_RunPer10ms(void)
{
	//bsp_KeyScan10ms();
//	BEEP_Pro();
}

/*
*********************************************************************************************************
*	函 数 名: bsp_RunPer1ms
*	功能说明: 该函数每隔1ms被Systick中断调用1次。详见 bsp_timer.c的定时中断服务程序。一些需要周期性处理的事务
*			 可以放在此函数。比如：触摸坐标扫描。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_RunPer1ms(void)
{
	
}

/*
*********************************************************************************************************
*	函 数 名: bsp_Idle
*	功能说明: 空闲时执行的函数。一般主程序在for和while循环程序体中需要插入 CPU_IDLE() 宏来调用本函数。
*			 本函数缺省为空操作。用户可以添加喂狗、设置CPU进入休眠模式的功能。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_Idle(void)
{
	/* --- 喂狗 */

	/* --- 让CPU进入休眠，由Systick定时中断唤醒或者其他中断唤醒 */

	/* 例如 emWin 图形库，可以插入图形库需要的轮询函数 */
	//GUI_Exec();

	/* 例如 uIP 协议，可以插入uip轮询函数 */
	//TOUCH_CapScan();
}

/*
*********************************************************************************************************
*	函 数 名: HAL_Delay
*	功能说明: 重定向毫秒延迟函数。替换HAL中的函数。因为HAL中的缺省函数依赖于Systick中断，如果在USB、SD卡
*             中断中有延迟函数，则会锁死。也可以通过函数HAL_NVIC_SetPriority提升Systick中断
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
/* 当前例子使用stm32f4xx_hal.c默认方式实现，未使用下面重定向的函数 */
#if 0
void HAL_Delay(uint32_t Delay)
{
	bsp_DelayUS(Delay * 1000);
}
#endif

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
