// Header: ICONS
// File Name: icons.c
// Author: Mustafa Aslan
// Date: 7.11.2015

#include "icons.h"

extern ADC_HandleTypeDef hadc1; 	
extern uint8_t Vib_On_Off;
extern uint8_t Bt_On_Off;
extern uint8_t Alarm_Status;

uint32_t Battery_Adc; // ADC degeri.
uint32_t Battery_Value; // Bataryanin % de olarak degeri.

	// Batarya iconun bitleri.
const unsigned char battery [10][10] = {
{0x1F, 0x11, 0x11, 0x15, 0x15, 0x15, 0x15, 0x11, 0x11, 0x0E}, // Battery bitme sinirinda.
{0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}, // Battery gostergesi tamamen bos.
{0x1F, 0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}, // Battery bir cizgi dolu.
{0x1F, 0x1F, 0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}, // Battery iki cizgi dolu.
{0x1F, 0x1F, 0x1F, 0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}, // Battery uc cizgi dolu.
{0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x11, 0x11, 0x11, 0x11, 0x0E}, // Battery dort cizgi dolu.
{0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x11, 0x11, 0x11, 0x0E}, // Battery bes cizgi dolu.
{0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x11, 0x11, 0x0E}, // Battery alti cizgi dolu.
{0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x11, 0x0E}, // Battery yedi cizgi dolu.
{0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0E}  // Battery sekiz cizgi dolu.
};
	// Bluetooth iconunun bitleri.
const unsigned char bluetooth_icon [2][9] = {
{0x00, 0x00, 0x0A, 0x04, 0x1F, 0x15, 0x0A, 0x00, 0x00},	// Saat telefona baglandi. 	
{0x0A, 0x04, 0x1F, 0x15, 0x0A, 0x00, 0x0A, 0x04, 0x0A} 	// Saat telefona henuz baglanmadi.
};

	// Titresim iconunun bitleri.
const unsigned char vibration_icon [2][11] = {
{0x04, 0x00, 0x0E, 0x00, 0x1F, 0x11, 0x1F, 0x00, 0x0E, 0x00, 0x04}, // Tiresim acik.
{0x0A, 0x04, 0x0A, 0x00, 0x1F, 0x11, 0x1F, 0x00, 0x0A, 0x04, 0x0A}	// Tiresim kapali.
};

	// Alarm iconunun bitleri.
const unsigned char alarm_icon [] = {
0x07, 0x00, 0x0E, 0x00, 0x1C, 0x14, 0x1C, 0x00, 0x0E, 0x00, 0x07 // Alarm kurulu. 
};

void Battery_Read(void){
	for(uint8_t x = 0; x < 255; x++){
		HAL_ADC_Start(&hadc1);	// ADCyi baslat.
		Battery_Adc = hadc1.Instance->DR;	// ADC degerini oku.
		HAL_ADC_Stop(&hadc1);	// ADCyi kapat.
	}
	// 3.3V yakalasik ADC degeri 4000. BATTERY_VALUE ADCnin yuzde degeri.
	Battery_Value = (Battery_Adc * 100)/4000;	
}

void Battery_Icon(uint8_t x_address, uint8_t y_address){
	Set_Address(x_address, y_address);
		// Bataryanin %90dan fazlasi dolu ise.
	if(Battery_Value > 95){
		for(uint16_t bit=0; bit<10; bit++){	
			Write_Data(battery[9][bit]);		
		}	
	}
		// Bataryanin %80den falasi dolu ise.
	else if(Battery_Value > 80 && Battery_Value < 90){
		for(uint16_t bit=0; bit<10; bit++){	
			Write_Data(battery[8][bit]);		
		}	
	}
		// Bataryanin %70den falasi dolu ise.
	else if(Battery_Value > 70 && Battery_Value < 85){
		for(uint16_t bit=0; bit<10; bit++){	
			Write_Data(battery[7][bit]);		
		}	
	}
		// Bataryanin %60den falasi dolu ise.
	else if(Battery_Value > 60 && Battery_Value < 80){
		for(uint16_t bit=0; bit<10; bit++){	
			Write_Data(battery[6][bit]);		
		}	
	}
		// Bataryanin %50den falasi dolu ise.
	else if(Battery_Value > 50 && Battery_Value < 75){
		for(uint16_t bit=0; bit<10; bit++){	
			Write_Data(battery[5][bit]);		
		}	
	}
		// Bataryanin %40den falasi dolu ise.
	else if(Battery_Value > 40 && Battery_Value < 70){
		for(uint16_t bit=0; bit<10; bit++){	
			Write_Data(battery[4][bit]);		
		}	
	}
		// Bataryanin %30den falasi dolu ise.
	else if(Battery_Value > 30 && Battery_Value < 65){
		for(uint16_t bit=0; bit<10; bit++){	
			Write_Data(battery[3][bit]);		
		}	
	}
		// Bataryanin %20den falasi dolu ise.
	else if(Battery_Value > 20 && Battery_Value < 60){
		for(uint16_t bit=0; bit<10; bit++){	
			Write_Data(battery[2][bit]);		
		}	
	}
		// Bataryanin %10den falasi dolu ise.
	else if(Battery_Value > 10 && Battery_Value > 50){
		for(uint16_t bit=0; bit<10; bit++){	
			Write_Data(battery[1][bit]);		
		}	
	}
		// Batarya %10dan az ise.
	else{
		for(uint16_t bit=0; bit<10; bit++){	
			Write_Data(battery[0][bit]);		
		}	
	}
}

void Bluetooth_Icon(uint8_t x_address, uint8_t y_address){
	Set_Address(x_address, y_address);
		// Ses acik ise.
	if(HAL_GPIO_ReadPin(GPIOA, BLUETOOTH_CONNECT_STATUS) == GPIO_PIN_RESET){
		for(uint16_t bit=0; bit<9; bit++){	
			Write_Data(bluetooth_icon[1][bit]);		
		}	
	}
		// Ses kapali ise.
	else{
		for(uint16_t bit=0; bit<9; bit++){	
			Write_Data(bluetooth_icon[0][bit]);		
		}	
	}
}

void Vibration_Icon(uint8_t x_address, uint8_t y_address){
	Set_Address(x_address, y_address);
		// Titresim acik ise.
	if(Vib_On_Off == 1){
		for(uint16_t bit=0; bit<11; bit++){	
			Write_Data(vibration_icon[0][bit]);		
		}	
	}
		// Titresim kapali ise.
	else{
		for(uint16_t bit=0; bit<11; bit++){	
			Write_Data(vibration_icon[1][bit]);		
		}	
	}
}

void Alarm_Icon(uint8_t x_address, uint8_t y_address){
	Set_Address(x_address, y_address);
		// Alarm kurulu ise.
	if(Alarm_Status == 1){
		for(uint16_t bit=0; bit<11; bit++){	
			Write_Data(alarm_icon[bit]);		
		}	
	}
		// Alarm kurulu degil ise.
	else{
		for(uint16_t bit=0; bit<11; bit++){	
			Write_Data(0x00);		
		}	
	}
}





