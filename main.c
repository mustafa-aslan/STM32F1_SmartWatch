/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* USER CODE BEGIN Includes */
#include "nokia_5110.h"
#include "menu_bitmap.h"
#include "game.h"
#include "setting.h"
#include "clock.h"
#include "stopwatch.h"
#include "call_sms.h"
#include "icons.h"
#include "find_my_phone.h"
#include "alarm.h"

extern const unsigned char alarm[];
extern const unsigned char setting[];
extern const unsigned char game[];
extern const unsigned char clock[];
extern const unsigned char date[];
extern const unsigned char ma_watch_logo [];
extern const unsigned char about_me [];
extern const unsigned char stopwatch [];
extern const unsigned char set_via_bluetooth [];
extern const unsigned char find_phone [];
extern uint8_t Game_Exit;
extern uint8_t Language;
extern uint8_t Theme;

// Butonlarin tanimlari.
#define LEFT_BUTTON  GPIO_PIN_5 // GPIOA
#define OK_BUTTON	   GPIO_PIN_6 // GPIOA
#define RIGHT_BUTTON GPIO_PIN_7 // GPIOA
#define EXIT_BUTTON  GPIO_PIN_0 // GPIOB

// Menudeki uygulamalarin gosterilme siralarinin tainimlari.
#define MENU_NUMBER    7 // Menudeki uygulama sayisi.
#define MENU_CLOCK     0
#define MENU_ALARM     1
#define MENU_STOPWATCH 2
#define MENU_GAME      3
#define MENU_SETTING   5
#define MENU_ABOUTME   6
#define MENU_FIND_MY_PHONE 4
int8_t Menu = 0; // Menu hangi sirada oldugunun tutlacagi degisken.


#define STATUS_SET   1
#define STATUS_RESET 0

#define ON_SCREEN 		1 // Ekranda.
#define NOT_ON_SCREEN 0 // Ekranda degil.

#define SELECTED     1 // Secildi.
#define NOT_SELECTED 0 // Secilmedi.


RTC_TimeTypeDef Time;
RTC_DateTypeDef Date;

uint8_t Menu_Status; 							   // Menu durumu
uint8_t Watch_Logo_Status;				   // Saatin logo durumu.
uint8_t Menu_Clock_Status;				   // Saat uygulamasinin durumu.
uint8_t Menu_Alarm_Status;				   // Alarm uygulamasinin durumu.
uint8_t Menu_Game_Status;				     // Oyun uygulamisinin durumu.
uint8_t Menu_Setting_Status;			   // Ayarlar uygulamasinin durumu.
uint8_t Menu_Select_Status = NOT_SELECTED;// Menu secim durumu.
uint8_t Menu_Aboutme_Status;			   // Hakkimda uygulamasinin durumu.
uint8_t Menu_Stopwatch_Status;		   // Kronometre uygulamasinin durumu.
uint8_t Menu_Find_My_Phone_Status;   // Telefonumu bul uygulamasinin durumu.
uint8_t Menu_Call_Sms_Status;			   // Arama ve Sms ekraninin durumu.
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_RTC_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART1_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

//@tanim Hakkimda uygulamasi acildiginda calisacak fonksiyon.
void About_Me(void);

//@tanim Menudeki uygulamalari cizen fonksiyon.
//@param menu_select: Ugulamanin numara sirasi.
void Menu_View(int8_t menu_select);

//@tanim Uygulama numaralarinin belli bir aralikta kalmasinin saglan fonksiyon.
//@param number: sayi
int8_t Menu_Select_Number(int8_t number);

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == LEFT_BUTTON){
		if(Watch_Logo_Status == NOT_ON_SCREEN && Menu_Select_Status == NOT_SELECTED){
			Menu_View(Menu_Select_Number(--Menu));
		}
		else if(Menu_Game_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
			Game_Down_Button();
		}
		else if(Menu_Setting_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
			Setting_Down_Button();
		}
		else if(Menu_Alarm_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
			Alarm_Left_Button();
		}
	}
	
	else if(GPIO_Pin == OK_BUTTON){
		if(Watch_Logo_Status == ON_SCREEN){
			Watch_Logo_Status = NOT_ON_SCREEN;
			Menu_Status = ON_SCREEN;			
			Menu_View(Menu);
		}
		else if(Menu_Status == ON_SCREEN){
			switch(Menu_Select_Number(Menu)){
				case MENU_CLOCK:
					Menu_Clock_Status = ON_SCREEN;
					Menu_Status = NOT_ON_SCREEN;
					Menu_Select_Status = SELECTED;
					Clock();
					break;
				case MENU_ALARM:
					Menu_Alarm_Status = ON_SCREEN;
					Menu_Status = NOT_ON_SCREEN;
					Menu_Select_Status = SELECTED;
					Set_Alarm();
					break;
				case MENU_GAME: 					
					Menu_Status = NOT_ON_SCREEN;
					Menu_Game_Status = ON_SCREEN;
					Menu_Select_Status = SELECTED;
					Game_Exit = STATUS_RESET;
					Game_Logo();					
					break;
				case MENU_SETTING:
					Menu_Setting_Status = ON_SCREEN;
					Menu_Status = NOT_ON_SCREEN;
					Menu_Select_Status = SELECTED;
					Setting_Menu();
					break;
				case MENU_ABOUTME:
					Menu_Status = NOT_ON_SCREEN;					
					Menu_Select_Status = SELECTED;
					Menu_Aboutme_Status = ON_SCREEN;
					About_Me();
					break;
				case MENU_STOPWATCH:
					Menu_Status = NOT_ON_SCREEN;					
					Menu_Select_Status = SELECTED;
					Menu_Stopwatch_Status = ON_SCREEN;		
					Stopwatch();
					break;
				case MENU_FIND_MY_PHONE:
					Menu_Status = NOT_ON_SCREEN;					
					Menu_Select_Status = SELECTED;
					Menu_Find_My_Phone_Status = ON_SCREEN;
					Find_My_Phone();
					break;
			}
		}
		else if(Menu_Clock_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
			Clock_Ok_Button();
		}
		else if(Menu_Game_Status == ON_SCREEN && Menu_Select_Status == SELECTED){	 
			Game_Ok_Button();
		}	
		else if(Menu_Setting_Status == ON_SCREEN && Menu_Select_Status == SELECTED){	 
			Setting_Ok_Button();
		}
		else if(Menu_Stopwatch_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
			Stopwatch_Ok_Button();
		}
		else if(Menu_Alarm_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
			Alarm_Ok_Button();
		}
	}
	
	else if(GPIO_Pin == RIGHT_BUTTON){	
		if(Watch_Logo_Status == NOT_ON_SCREEN && Menu_Select_Status == NOT_SELECTED){
			Menu_View(Menu_Select_Number(++Menu));
		}
		else if(Menu_Game_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
			Game_Up_Button();
		}
		else if(Menu_Setting_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
			Setting_Up_Button();
		}
		else if(Menu_Alarm_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
			Alarm_Right_Button();
		}
	}
	
	else if(GPIO_Pin == EXIT_BUTTON){
		if(Menu_Select_Status == NOT_SELECTED && Watch_Logo_Status == NOT_ON_SCREEN){
			Menu_Clock_Status = ON_SCREEN;
			Menu_Status = NOT_ON_SCREEN;
			Menu_Select_Status = SELECTED;
			Clock();
		}
		else if(Menu_Game_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
			Menu_Status = ON_SCREEN;
			Menu_Game_Status = NOT_ON_SCREEN;
			Menu_Select_Status = NOT_SELECTED;
			Game_Exit = STATUS_SET;
			Game_Reset_All();			
			Menu_View(Menu_Select_Number(Menu));
		}
		else if(Menu_Aboutme_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
			Menu_Status = ON_SCREEN;
			Menu_Select_Status = NOT_SELECTED;
			Menu_Aboutme_Status = NOT_ON_SCREEN;
			Menu_View(Menu_Select_Number(Menu));
		}
		else if(Menu_Setting_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
			Menu_Status = ON_SCREEN;
			Menu_Select_Status = NOT_SELECTED;
			Menu_Setting_Status = NOT_ON_SCREEN;
			Setting_Reset();
			Menu_View(Menu_Select_Number(Menu));
		}
		else if(Menu_Clock_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
			Menu_Status = ON_SCREEN;
			Menu_Select_Status = NOT_SELECTED;
			Menu_Clock_Status = NOT_ON_SCREEN;
			Menu_View(Menu_Select_Number(Menu));
		}
		else if (Menu_Stopwatch_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
			Menu_Status = ON_SCREEN;
			Menu_Select_Status = NOT_SELECTED;
			Menu_Stopwatch_Status = NOT_ON_SCREEN;
			Menu_View(Menu_Select_Number(Menu));			
		}
		else if (Menu_Call_Sms_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
			Menu_Call_Sms_Status = NOT_ON_SCREEN;
			Menu_Clock_Status = ON_SCREEN;
			Menu_Status = NOT_ON_SCREEN;
			Menu_Select_Status = SELECTED;
			Clock();
		}
		else if (Menu_Find_My_Phone_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
			Menu_Status = ON_SCREEN;
			Menu_Select_Status = NOT_SELECTED;
			Menu_Find_My_Phone_Status = NOT_ON_SCREEN;
			Menu_View(Menu_Select_Number(Menu));
		}
		else if (Menu_Alarm_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
			Menu_Status = ON_SCREEN;
			Menu_Select_Status = NOT_SELECTED;
			Menu_Alarm_Status = NOT_ON_SCREEN;
			Menu_View(Menu_Select_Number(Menu));
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM1){
		if(Menu_Game_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
			Game_Timer();
		}
	}
	if(htim->Instance == TIM3){
		Stopwatch_Timer(Menu_Stopwatch_Status);
	}
}

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_RTC_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();

  /* USER CODE BEGIN 2 */
	// Saat ilk acildiginda yapilacak genel ayarlamalar.
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET); // Baslangicta bluetooth acik.
	HAL_RTC_GetDate(&hrtc, &Date, FORMAT_BIN); 
  Time.Hours = 0x12; // Saat 12:00 
  HAL_RTC_SetTime(&hrtc, &Time, FORMAT_BCD);	
	HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_3);
	TIM2->CCR3 = 32750; // Display parlakligi yari yariya.
	Example_Setting(); // Nokia 5110 displayin ayarlari.
	
	// Saat ilk acildiginda cizilecek logo.
	for(uint16_t bit=0; bit<504; bit++){	
		Write_Data(ma_watch_logo[bit]);		
	}	
	Watch_Logo_Status = ON_SCREEN;
	
	Battery_Read(); // Bateri degerini oku.
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	if(Menu_Game_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
		Game_Loop();
	}
	else if(Menu_Clock_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
		Clock_Loop();
		Sms_Loop();
		Call_Started_Loop();		
	}
	else if(Menu_Call_Sms_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
		Call_Ended_Loop();	
	}
	else if(Menu_Setting_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
		Setting_Loop();	
	}
	else if(Menu_Find_My_Phone_Status == ON_SCREEN && Menu_Select_Status == SELECTED){
		Find_My_Phone_Loop();
	}
	else{
		Call_Ended_Loop();		
	}
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Common config 
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  HAL_ADC_Init(&hadc1);

    /**Configure Regular Channel 
    */
  sConfig.Channel = ADC_CHANNEL_9;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

}

/* RTC init function */
void MX_RTC_Init(void)
{

  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef DateToUpdate;
  RTC_AlarmTypeDef sAlarm;

    /**Initialize RTC and set the Time and Date 
    */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  HAL_RTC_Init(&hrtc);

  sTime.Hours = 0x1;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;

  HAL_RTC_SetTime(&hrtc, &sTime, FORMAT_BCD);

  DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
  DateToUpdate.Month = RTC_MONTH_JANUARY;
  DateToUpdate.Date = 0x1;
  DateToUpdate.Year = 0x0;

  HAL_RTC_SetDate(&hrtc, &DateToUpdate, FORMAT_BCD);

    /**Enable the Alarm A 
    */
  sAlarm.AlarmTime.Hours = 0x0;
  sAlarm.AlarmTime.Minutes = 0x0;
  sAlarm.AlarmTime.Seconds = 0x0;
  sAlarm.Alarm = RTC_ALARM_A;
  HAL_RTC_SetAlarm(&hrtc, &sAlarm, FORMAT_BCD);

}

/* TIM1 init function */
void MX_TIM1_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 7999;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 9;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  HAL_TIM_Base_Init(&htim1);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig);

}

/* TIM2 init function */
void MX_TIM2_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_PWM_Init(&htim2);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);

}

/* TIM3 init function */
void MX_TIM3_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 799;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 99;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htim3);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig);

}

/* USART1 init function */
void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart1);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __GPIOC_CLK_ENABLE();
  __GPIOA_CLK_ENABLE();
  __GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : PA0 PA1 PA2 PA3 
                           PA4 PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */
int8_t Menu_Select_Number(int8_t number){
	if(number < 0){number*=-1;};
	number %= MENU_NUMBER;
	return number;
}

void Menu_View(int8_t menu_select){
	Set_Address(0, 0);
	if(menu_select < 0){menu_select*=-1;};
	menu_select %= MENU_NUMBER;
	switch (menu_select){
		case MENU_CLOCK:
			Clear_Display(); 			
			for(uint16_t bit=0; bit<504; bit++){	
				Write_Data(clock[bit]);		
			}
			Write_String_Language_Address(30, 5, "SAAT", 27, 5, "CLOCK", Language);
			Set_Address(0, 0);
		break;
			
		case MENU_ALARM:
			Clear_Display(); 			
			// Logoyu ekrana ciz.
			for(uint16_t bit=0; bit<504; bit++){	
				Write_Data(alarm[bit]);		
			}	
			Set_Address(27, 5);			
			Write_String("ALARM");
			Set_Address(0, 0);
		break;		
		case MENU_GAME:
			Clear_Display();
			for(uint16_t bit=0; bit<504; bit++){	
				Write_Data(game[bit]);		
			}	
			Set_Address(29, 5);
			Write_String_Language("OYUN", "GAME", Language);			
			Set_Address(0, 0);
		break;	
		case MENU_SETTING:
			Clear_Display();
			for(uint16_t bit=0; bit<504; bit++){	
				Write_Data(setting[bit]);		
			}	
			Set_Address(20, 5);
			Write_String_Language ("AYARLAR", "SETTING", Language);
			Set_Address(0, 0);			
		break;
		case MENU_ABOUTME:
			Clear_Display();
			for(uint16_t bit=0; bit<504; bit++){	
				Write_Data(about_me[bit]);		
			}	
			Set_Address(17, 5);
			Write_String_Language ("HAKKIMDA", "ABOUT ME", Language);
			Set_Address(0, 0);	
		break;
		case MENU_STOPWATCH:
			Clear_Display();
			for(uint16_t bit=0; bit<504; bit++){	
				Write_Data(stopwatch[bit]);		
			}	
			Write_String_Language_Address (12, 5, "KRONOMETRE",17, 5, "STOPWATCH", Language);
			Set_Address(0, 0);	
		break;
		case MENU_FIND_MY_PHONE:
			Clear_Display();
			for(uint16_t bit=0; bit<504; bit++){	
				Write_Data(find_phone[bit]);		
			}	
			Write_String_Language_Address (0, 5, "TELEFONUMU BUL", 6, 5, "FIND MY PHONE", Language);
			Set_Address(0, 0);	
		break;	
	}	
}
void About_Me(void){
	Clear_Display();
	Set_Address(3, 0);
	Write_String("MUSTAFA ASLAN");	
	Set_Address(18, 1);
	Write_String("EGE UNI.");	
	Set_Address(9, 2);
	Write_String("MUHENDISLIK");	
	Set_Address(21, 3);
	Write_String("1.SINIF");	
	Set_Address(15, 4);
	Write_String("OGRENCISI");	
	Set_Address(0, 5);
	Write_String("MAWATCH V.4.10");
}

/* USER CODE END 4 */

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
