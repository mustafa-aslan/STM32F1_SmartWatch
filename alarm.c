// Header: ALARM
// File Name: alarm.c
// Author: Mustafa Aslan
// Date: 9.11.2015

#include "alarm.h"

extern uint8_t Language;
extern const unsigned char Clock_Numbers [10][60];
extern const unsigned char Clock_Dot [];

uint8_t Alarm_Bar_Location; // Alarm ayarlarken sayilarin üstünde gezen bar konumu.
uint8_t Set_Alarm_Status; // Alarm kuruldumunda butonlar arasi gecis durumu.
uint8_t Alarm_Status; // Alarm kuruldu mu kurulmadimi.
int8_t min_first_number, min_second_number; // Dakikanin birinci ve ikinci basamakalarinin degiskenleri.
int8_t hour_first_number, hour_second_number; // Saatin birinci ve ikinci basamaklarinin degiskenleri.
int8_t alarm_hour; // Iki basamakli sayi olarak saat.
int8_t alarm_min; // Iki basamakli sayi olarak dakika.

	// Alarm kurarken rakamlarin uzerinde gecen barin bitleri.
const unsigned char alarm_bar[15] = {
0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01};

void Set_Alarm(void){
	Clear_Display();
	Write_Alarm_Numbers(5, 1, hour_first_number, hour_second_number);
	Write_Alarm_Numbers(45, 1, min_first_number, min_second_number);
	Alarm_Bar_Location = 0;	// Barin ilk konumu.
	Write_Alarm_Bar(Alarm_Bar_Location ,BAR_WRITE); // Bari ciz.
		// Alarm daha onceden kurulmussa.
	if(Alarm_Status == SET){ 
		Write_String_Language_Address(15, 5, "KALDIR   ", 15, 5, "CLEAR   ", Language);
	}
		// Alarm henuz kurulmasi ise.
	else if(Alarm_Status == NOT_SET){
		Write_String_Language_Address(15, 5, "ALARM KUR", 15, 5, "SET ALARM", Language);
	}	
}

void Alarm_Ok_Button(void){
	if(Alarm_Bar_Location == 4 && Alarm_Status == NOT_SET){
		Write_String_Language_Address(15, 5, "KALDIR   ", 15, 5, "CLEAR    ", Language);
		Alarm_Status = SET; // Alarm kuruldu.
	}
	else if(Alarm_Status == SET && Alarm_Bar_Location == 4){
		Alarm_Status = NOT_SET; // Alarm henuz kurulmadi.
		Write_String_Language_Address(15, 5, "ALARM KUR", 15, 5, "SET ALARM", Language);
	}
	else if(Set_Alarm_Status == SET_ALARM_FIRST_OK && Alarm_Status == NOT_SET){
		Set_Alarm_Status = SET_ALARM_SECOND_OK;
	}
	else if(Set_Alarm_Status == SET_ALARM_SECOND_OK && Alarm_Status == NOT_SET){
		Set_Alarm_Status = SET_ALARM_FIRST_OK;
	}
}

void Alarm_Right_Button(void){
		// Ok butonu ikicide ise.
	if(Set_Alarm_Status == SET_ALARM_SECOND_OK){
		if(Alarm_Bar_Location == 4){Alarm_Bar_Location = 3;}; // Bar en fazla 3 konuma kadar gidebilir.
		Write_Alarm_Bar(Alarm_Bar_Location, BAR_CLEAR);
		Write_Alarm_Bar(++Alarm_Bar_Location, BAR_WRITE);
	}
		// Zaman ayarlanmasi icin.
		// Alarm kurulmamis ve ok butonu ilk okta ise.
	else if(Set_Alarm_Status == SET_ALARM_FIRST_OK && Alarm_Status == NOT_SET){
			// Bar konumu 0 ise.
		if(Alarm_Bar_Location == 0){
			++hour_first_number; 			
				// Bir gün 24 saat oldugundan, saatin ikinci basamagi 2 den buyuk olamaz.
			if(hour_first_number == 3){hour_first_number = 2;};
				// Ilkinci basamak 4'den buyukken birinci basamagin 1 den buyuk olmasina izin vermez.
			// Ornegin 25:00 yada 56:00 gibi bir alarmalar kurulamaz.
			if(hour_second_number > 4){hour_first_number = 1;};
			Write_Alarm_Numbers(5, 1, hour_first_number, hour_second_number);
		}
			// Bar konumu 1 ise.
		else if(Alarm_Bar_Location == 1){
			++hour_second_number;
				// 9 rakam oldugundan.
			if(hour_second_number == 10){hour_second_number = 9;}
				// Saati ilk basamagi 2 iken saatin ikinci basamagi 4 den buyuk olamaz.
				// Ornegin 27:00 gibi alarmlar kurulamaz.
			if(hour_first_number == 2 && hour_second_number == 5){hour_second_number = 4;};
			Write_Alarm_Numbers(5, 1, hour_first_number, hour_second_number);
		}
			// Bar konumu 2 ise.
		else if(Alarm_Bar_Location == 2){
			++min_first_number;
				// Bir saat 60 dakika oldugundan.
				// Dakikanin ilk basamagi 5 den buyuk olamaz.
			if(min_first_number == 6){min_first_number = 5;};	
			Write_Alarm_Numbers(45, 1, min_first_number, min_second_number);
		}
			// Bar konumu 3 ise.
		else if(Alarm_Bar_Location == 3){
			++min_second_number;
				// 9 rakam oldugundan.
			if(min_second_number == 10){min_second_number = 9;}
			Write_Alarm_Numbers(45, 1, min_first_number, min_second_number);
		}
	}
	alarm_hour = 10 * hour_first_number + hour_second_number;
	alarm_min = 10 * min_first_number + min_second_number;
}

void Alarm_Left_Button(void){
		// Ok butonu ikicide ise.
	if(Set_Alarm_Status == SET_ALARM_SECOND_OK){
			// Bar konumu 0 dan kucuk olamaz.
		if(Alarm_Bar_Location == 0){Alarm_Bar_Location = 1;};
		Write_Alarm_Bar(Alarm_Bar_Location, BAR_CLEAR);	
		Write_Alarm_Bar(--Alarm_Bar_Location, BAR_WRITE);	
	}
		// Alarm kurulmamis ve Ok butonu ilk okta.
	else if(Set_Alarm_Status == SET_ALARM_FIRST_OK && Alarm_Status == NOT_SET){
			 // Bar 0 konumunda ise.
		if(Alarm_Bar_Location == 0){
			--hour_first_number;
				// 0 dan kucuk olmayacagindan.
			if(hour_first_number == -1){hour_first_number = 0;};
			Write_Alarm_Numbers(5, 1, hour_first_number, hour_second_number);
		}
			// Bar 1 konumunda ise.
		else if(Alarm_Bar_Location == 1){
			--hour_second_number;
				// 0 dan kucuk olmayacagindan.
			if(hour_second_number == -1){hour_second_number = 0;};		
			Write_Alarm_Numbers(5, 1, hour_first_number, hour_second_number);
		}
			// Bar 2 konumunda ise.
		else if(Alarm_Bar_Location == 2){
			--min_first_number;
				// 0 dan kucuk olamayacagindan.
			if(min_first_number == -1){min_first_number = 0;};		
			Write_Alarm_Numbers(45, 1, min_first_number, min_second_number);
		}
			// Bar 3 konumunda ise.
		else if(Alarm_Bar_Location == 3){
			--min_second_number;
				// 0 dan kucuk olmayacagindan.
			if(min_second_number == -1){min_second_number = 0;};		
			Write_Alarm_Numbers(45, 1, min_first_number, min_second_number);
		}
	}
	alarm_hour = 10 * hour_first_number + hour_second_number;
	alarm_min = 10 * min_first_number + min_second_number;
}

void Write_Alarm_Numbers(uint8_t x_address, uint8_t y_address, uint8_t first_number, uint8_t second_number){
		
	Set_Address(x_address, y_address);
	for(uint8_t _15times = 0; _15times < 15; _15times++){
		Write_Data(Clock_Numbers[first_number][_15times]);
	}
	Set_Address(x_address, ++y_address);
	for(uint8_t _15times = 0; _15times < 15; _15times++){
		Write_Data(Clock_Numbers[first_number][_15times + 15]);
	}
	Set_Address(x_address, ++y_address);
	for(uint8_t _15times = 0; _15times < 15; _15times++){
		Write_Data(Clock_Numbers[first_number][_15times + 30]);
	}	
	Set_Address(x_address, ++y_address);
	for(uint8_t _15times = 0; _15times < 15; _15times++){
		Write_Data(Clock_Numbers[first_number][_15times + 45]);
	}
	
	y_address -= 3;
	x_address += 18;
	
	Set_Address(x_address, y_address);
	for(uint8_t _15times = 0; _15times < 15; _15times++){
		Write_Data(Clock_Numbers[second_number][_15times]);
	}
	Set_Address(x_address, ++y_address);
	for(uint8_t _15times = 0; _15times < 15; _15times++){
		Write_Data(Clock_Numbers[second_number][_15times + 15]);
	}
	Set_Address(x_address, ++y_address);
	for(uint8_t _15times = 0; _15times < 15; _15times++){
		Write_Data(Clock_Numbers[second_number][_15times + 30]);
	}	
	Set_Address(x_address, ++y_address);
	for(uint8_t _15times = 0; _15times < 15; _15times++){
		Write_Data(Clock_Numbers[second_number][_15times + 45]);
	}
	
	Set_Address(40, 1);
	for(uint8_t _3times = 0; _3times < 3; _3times++){
		Write_Data(Clock_Dot[_3times]);
	}
	Set_Address(40, 2);
	for(uint8_t _3times = 0; _3times < 3; _3times++){
		Write_Data(Clock_Dot[_3times + 3]);
	}
	Set_Address(40, 3);
	for(uint8_t _3times = 0; _3times < 3; _3times++){
		Write_Data(Clock_Dot[_3times + 6]);
	}	
	Set_Address(40, 4);
	for(uint8_t _3times = 0; _3times < 3; _3times++){
		Write_Data(Clock_Dot[_3times + 9]);
	}
}

void Write_Alarm_Bar(uint8_t location, uint8_t write_or_clear){
	if(write_or_clear == 1){
		if(Alarm_Bar_Location == 1 || Alarm_Bar_Location == 0){
			Set_Address((Alarm_Bar_Location*18) + 5, 0);
		}
		else if(Alarm_Bar_Location == 2 || Alarm_Bar_Location == 3){
			Set_Address((Alarm_Bar_Location*18) + 9, 0);
		}
		if(Alarm_Bar_Location == 1 || Alarm_Bar_Location == 0 || Alarm_Bar_Location == 2 || Alarm_Bar_Location == 3){
			for(uint8_t _15line = 0; _15line < 15; _15line++){
				Write_Data(alarm_bar[_15line]);
			}
		}
		if(Alarm_Bar_Location == 4){
			Set_Address(9, 5);
			Write_Char('>');
		}
	}
	else if(write_or_clear == 0){
		if(Alarm_Bar_Location == 1 || Alarm_Bar_Location == 0){
			Set_Address((Alarm_Bar_Location*18) + 5, 0);
		}
		else if(Alarm_Bar_Location == 2 || Alarm_Bar_Location == 3){
			Set_Address((Alarm_Bar_Location*18) + 9, 0);
		}
		if(Alarm_Bar_Location == 1 || Alarm_Bar_Location == 0 || Alarm_Bar_Location == 2 || Alarm_Bar_Location == 3){
			for(uint8_t _15line = 0; _15line < 15; _15line++){
				Write_Data(0x00);
			}
		}
		if(Alarm_Bar_Location == 4){
			Set_Address(9, 5);
			Write_Char(' ');
		}
	}
}
