// Header: SETTING
// File Name: setting.c
// Author: Mustafa Aslan
// Date: 29.10.2015

#include "setting.h"

extern RTC_HandleTypeDef hrtc;
extern UART_HandleTypeDef huart1;
extern uint8_t Theme;
extern uint8_t Language;
extern RTC_TimeTypeDef Time;

uint8_t Vib_On_Off = ON;		 // Titresim durumu.
uint8_t Language = TR;    	 // Dil durumu. (Saat ilk acilista tr oldugundan.)
uint8_t Bt_On_Off = ON;		   // Bluetooth.
uint8_t Theme;							 // Tema.
uint8_t Light_Status; 			 // Parlaklik durumu.
uint8_t Bluetooth_Status;		 // Bluetooth durumu.
uint8_t Vibration_Status;		 // Titresim durumu.
uint8_t Theme_Status; 			 // Bt ile kur durumu.
uint8_t Setting_Menu_Status; // Ayarlar menu durumu.
uint8_t Language_Status;		 // Dil durumu.
uint8_t Set_Via_Bt_Status;	 // Bt ile kur durumu.
	
int8_t light = 50;	// Parlaklik pwm degeri yuzde olarak. (Saat ilk acilista %50 oldugundan.)
int8_t greater = 0; // (>) Buyuktur isareti. (Buyuktur isaretinin ilk konu 0. satir oldugundan.)

RTC_DateTypeDef bt_date; // Tarih.
RTC_TimeTypeDef bt_time; // Saat.

uint8_t Bt_Data[20];

	// Bt ile kur uygulamasi acildiginda cikan resmin bitleri.
const unsigned char waiting [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0,
0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xC0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0,
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xF0, 0x10, 0x10, 0x10, 0x10, 0x30, 0x30, 0x10, 0x10, 0x10,
0x10, 0xF0, 0x20, 0x20, 0x20, 0xE0, 0x20, 0x20, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFF,
0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x1F, 0x20, 0x22, 0x20, 0x22, 0x20, 0x20, 0x7F, 0x42, 0x42, 0x40, 0x40, 0x6E,
0x62, 0x41, 0x40, 0x42, 0x42, 0x7F, 0x20, 0x20, 0x20, 0x3F, 0x22, 0x20, 0x1F, 0x00, 0x00, 0x02,
0x07, 0x00, 0x00, 0x02, 0x07, 0x00, 0x00, 0x02, 0x07, 0x00, 0x00, 0x02, 0x07, 0x00, 0x00, 0x02,
0x07, 0x00, 0x00, 0x02, 0x07, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
0x80, 0x80, 0x80, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x10, 0x10, 0x10, 0x10,
0x10, 0x16, 0x16, 0x16, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

void Greater(uint8_t y_address,uint8_t write_or_clear){
	Set_Address(0, y_address);
	if(write_or_clear == WRITE){
		Write_String(">"); 
	}
	else if (write_or_clear == CLEAR)
	{
		Write_String(" ");
	}
}

void Setting_Menu(void){
	Set_Address(0, 0);
	Clear_Display();
	
	Set_Address(6, 0);
	Write_String_Language("Isik: %", "Light:%", Language);
	Write_Three_Number(49, 0, light);
	
	
	Set_Address(6, 1);
	Write_String_Language ("Bluetooth:", "Bluetooth:", Language);
	Set_Address(65, 1);
	if(Bt_On_Off == ON){
		Write_String("ON");
		HAL_GPIO_WritePin(GPIOA, BLUETOOTH_EN, GPIO_PIN_SET);
	}
	else{
		Write_String("OFF");
		HAL_GPIO_WritePin(GPIOA, BLUETOOTH_EN, GPIO_PIN_RESET);
	}
	
	Set_Address(6, 2);
	Write_String_Language ("Titresim :", "Vibration:", Language);
	Set_Address(65, 2);
	if(Vib_On_Off == ON){Write_String("ON");}
	else{Write_String("OFF");}
	
	Set_Address(6, 3);
	Write_String_Language ("Saat Dili:", "Language :", Language);
	Set_Address(65, 3);
	if(Language == TR){Write_String("TR");}
	else{Write_String("EN");}
	
	
	Set_Address(6, 4);
	Write_String_Language ("Tema :", "Theme:", Language);
	Set_Address(42, 4);
	if(Theme == THEME_CLASSIC){
		// Klasik saat gorunumu kaldirildi.
		Write_String_Language("Klasik ", "Classic", Language);
	}else{
		Write_String_Language("Dijital", "Digital", Language);
	}
	
	Set_Address(6, 5);
	Write_String_Language ("BT ile kur", "Set via BT", Language);
	
	Greater(greater, WRITE);
}

void Setting_Down_Button(void){
		//  Ayarlardaki menulerden biri secilmisse imlecin(>) hareketi asagiya.
	if(Setting_Menu_Status == NOT_SELECTED){
		Greater(greater, CLEAR);
		if(greater == 5){greater = 4;};
		Greater(++greater, WRITE);
	}
		// Ayarlar menusunde isik secilmisse isigin pwm degerini azalt.
	else if(Light_Status == SELECTED){
		if(light == -1){light = 0;};
	  Write_Three_Number(49, 0, --light);	
		uint16_t pwm_value = light*655;
		TIM2->CCR3 = pwm_value;		
	}
		// Ayarlar menusunde bluetooth secilmisse bluetooth kapat.
	else if(Bluetooth_Status == SELECTED){
		Set_Address(65, 1);
		Write_String("OFF");
		HAL_GPIO_WritePin(GPIOA, BLUETOOTH_EN, GPIO_PIN_RESET);
		Bt_On_Off = OFF;
	}
		// Ayarlar menusunden titresim selcilmisse titresimi kapat.
	else if(Vibration_Status == SELECTED){
		Set_Address(65, 2);
		Write_String("OFF");
		Vib_On_Off = OFF;
	}
		// Ayarlarda saat dili secilmisse dili turkce yap.
	else if(Language_Status == SELECTED){
		Set_Address(65, 3);
		Write_String("TR");
		Language = TR;
	}
		// Ayarlarda tema secilmisse temayi dijital yap.
	else if(Theme_Status == SELECTED){
		Set_Address(43, 4);
		Write_String_Language("Dijital", "Digital", Language);
		Theme = THEME_DIGITAL;
	}	
}

void Setting_Up_Button(void){
		// Ayarlardaki menulerden biri secilmisse imlecin(>) hareketi asagiya.
	if(Setting_Menu_Status == NOT_SELECTED){
		Greater(greater, CLEAR);
		if(greater == 0){greater = 1;};
		Greater(--greater, WRITE);
	}
		// Ayarlar menusunde isik secilmisse isigin pwm degerini arttir.
	else if(Light_Status == SELECTED){
		if(light == 100){light = 99;};
		Write_Three_Number(49, 0, ++light);
		uint16_t pwm_value = light*655;
		TIM2->CCR3 = pwm_value;
	}
		// Ayarlar menusunde bluetooth secilmisse bluetooth ac.
	else if(Bluetooth_Status == SELECTED){
		Set_Address(65, 1);
		Write_String("ON ");
		HAL_GPIO_WritePin(GPIOA, BLUETOOTH_EN, GPIO_PIN_SET);
		Bt_On_Off = ON;
	}	
		// Ayarlar menusunde titerisim secilmisse titresimi ac.
	else if(Vibration_Status == SELECTED){
		Set_Address(65, 2);
		Write_String("ON ");
		Vib_On_Off = ON;
	}	
		// Ayarlar menusunde saat dili secilmisse saat dilini ingilizce yap.
	else if(Language_Status == SELECTED){
		Set_Address(65, 3);		
		Write_String("EN");
		Language = EN;
	}	
		// Ayarlar menusunde tema secilmisse temayi klasik yap.
	else if(Theme_Status == SELECTED){
		Set_Address(42, 4);
		Write_String_Language("Klasik ", "Classic", Language);
		Theme = THEME_CLASSIC;
	}		
}

void Setting_Ok_Button(void){
		// Ayarlar menusunden henuz secim yapilmamissa.
	if(Setting_Menu_Status == NOT_SELECTED){
		switch(greater){
			case SETTING_MENU_LIGHT:
				Light_Status = SELECTED; // Menude isik secildi.
				Setting_Menu_Status = SELECTED;
				break;
			case SETTING_MENU_BLUETOOTH:
				Bluetooth_Status = SELECTED; // Menude ses secildi.
				Setting_Menu_Status = SELECTED;
				break;
			case SETTING_MENU_VIBRATION:
				Vibration_Status = SELECTED; // Menude titresim secildi.
				Setting_Menu_Status = SELECTED;
				break;			
			case SETTING_MENU_LANGUAGE:
				Language_Status = SELECTED; // Menude saat dili secildi.
				Setting_Menu_Status = SELECTED;				
				break;
			case SETTING_MENU_THEME:
				Theme_Status = SELECTED; // Menude saat dili secildi.
				Setting_Menu_Status = SELECTED;						
			  break;
			case SETTING_MENU_SET_VIA_BT:
				Set_Via_Bt_Status = SELECTED; // Menude saat dili secildi.
				Setting_Menu_Status = SELECTED;
				Set_Via_Bt();
				break;
		}	
	}	
		// Menuden isik secilmisse.
	else if(Light_Status == SELECTED){
			Light_Status = NOT_SELECTED;
			Setting_Menu_Status = NOT_SELECTED;
	}		
		// Menuden bluetooth secilmisse.
	else if(Bluetooth_Status == SELECTED){
			Bluetooth_Status = NOT_SELECTED;
			Setting_Menu_Status = NOT_SELECTED;	
	}
		// Menuden titresim secilmisse.
	else if(Vibration_Status == SELECTED){
			Vibration_Status = NOT_SELECTED;
			Setting_Menu_Status = NOT_SELECTED;
	}
		// Menuden saat dili secilmisse.
	else if(Language_Status == SELECTED){
			Setting_Menu();
			Language_Status = NOT_SELECTED;
			Setting_Menu_Status = NOT_SELECTED;
	}
		// Menuden tema dili secilmisse.
	else if(Theme_Status == SELECTED){
			Theme_Status = NOT_SELECTED;
			Setting_Menu_Status = NOT_SELECTED;			
	}
}

void Setting_Reset(void){
		greater = 0;
		Light_Status = NOT_SELECTED;
		Theme_Status = NOT_SELECTED;
		Setting_Menu_Status = NOT_SELECTED;
		Vibration_Status = NOT_SELECTED;
		Bluetooth_Status = NOT_SELECTED;
}


void Set_Via_Bt(void){
	Set_Address(0,0);
	Clear_Display(); // Ekrani temizle.			
	for(uint16_t bit=0; bit<504; bit++){	
		Write_Data(waiting[bit]);	
	}
	Write_String_Language_Address(18, 0, "BEKLIYOR", 21, 0, "WAITING", Language);
}

void Setting_Loop(void){
	HAL_UART_Receive(&huart1, (uint8_t *)Bt_Data, 20, 100); // Veri al.
	
	// Tarih.
	if(Bt_Data[0] == DATE_BT_ADDRESS){
		bt_date.Date = Char_To_Decimal(Bt_Data[1])*10 + Char_To_Decimal(Bt_Data[2]); 
		bt_date.Month = Char_To_Decimal(Bt_Data[3])*10 + Char_To_Decimal(Bt_Data[4]);
		bt_date.Year =  Char_To_Decimal(Bt_Data[7])*10 + Char_To_Decimal(Bt_Data[8]);
		HAL_RTC_SetDate(&hrtc, &bt_date, FORMAT_BIN);
	}

	// Saat		
	else if (Bt_Data[0] == CLOCK_BT_ADDRESS){		
		bt_time.Hours = Char_To_Decimal(Bt_Data[1])*10 + Char_To_Decimal(Bt_Data[2]);
		bt_time.Minutes = Char_To_Decimal(Bt_Data[3])*10 + Char_To_Decimal(Bt_Data[4]);
		bt_time.Seconds = 0;	// Saatte saniye kurulumuna gerek duyulmadigindan.
		HAL_RTC_SetTime(&hrtc, &bt_time, FORMAT_BIN);
	}
	
}

uint8_t Char_To_Decimal(uint8_t char_value){
		// Telefon 5 sayisini gonderdiginde CHAR degeri 53.
		// Bu degerden 48 cikararak(53 - 48 = 5). 
		// Telefonun gonderdigi deger istenen sekilde alinmis olacak.
	if (char_value > 47 && char_value < 58){
		char_value -= 48;
	}
	return char_value;
}
