// Header: ALARM
// File Name: alarm.h
// Author: Mustafa Aslan
// Date: 9.11.2015

#ifndef ALARM_H_
#define ALARM_H_

#include "stm32f1xx_hal.h"
#include "nokia_5110.h"

#define SET     1 // Alarm kuruldu.
#define NOT_SET 0 // Alarm kurulmasi.

#define ALARM_NOT_SETTED // Alarm kurumadi.

#define SET_ALARM_FIRST_OK 1 // Ok butonuna basilmasi.
#define SET_ALARM_SECOND_OK  0 // Ok butonuna basilmasi.

#define BAR_WRITE 1 // Bari ciz.
#define BAR_CLEAR 0 // Bari sil.

//@tanim Alarm ilk acildiginda calisacak fonksiyon.
void Set_Alarm(void);

//@tanim Alarm uygulamasinda iken ok butonuna basidiginda calisacak fonksiyon.
void Alarm_Ok_Button(void);

//@tanim Alarm uygulamisnda iken left butonuna basildiginda calisacak fonksiyon.
void Alarm_Left_Button(void);

//@tanim Alarm uygulamisnda iken right butonuna basildiginda calisacak fonksiyon.
void Alarm_Right_Button(void);

//@tanim Bari ekrana yazdiran ve silen fonksiyon.
//@param location: Barin konumu. location [0,3] deger araliginda.
//@param write_or_clear: Ekrana ciz yada sil.
void Write_Alarm_Bar(uint8_t location, uint8_t write_or_clear);

//@tanim Alarm sayilari ekrana yazdiran fonksiyon.
//@param x_address: Sutun konumu. x [0,84] deger araliginda.
//@param y_address: Satir konumu. y [0, 5] deger araliginda.
//@param firs_number: Saat yada dakikanin ilk rakami.
//@param second_number: Saat yada dakikanin ikinci rakami.
void Write_Alarm_Numbers(uint8_t x_address, uint8_t y_address, uint8_t first_number, uint8_t second_number);

#endif /* ALARM_H_ */







