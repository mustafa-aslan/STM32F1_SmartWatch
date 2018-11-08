// Header: CLOCK
// File Name: clock.h
// Author: Mustafa Aslan
// Date: 29.10.2015

#ifndef CLOCK_H_
#define CLOCK_H_

#include "stm32f1xx_hal.h"
#include "nokia_5110.h"

#define CLASSIC 1 // Saat temasi klasik.
#define DIGITAL 0	// Saat temasi dijital.

#define VIB_MOTOR_PIN GPIO_PIN_2 // GPIOB

//@tanim Saat degerlerini iki basamakli yazdiran fonksiyon.
//@param x_address: Sutunun konumu. x_address [0,84] araliginda.
//@param y_address: Satirin konumu. y_address [0,5] araliginda.
//@param number: saat degeri.
void Write_Clock_Numbers(uint8_t x_address, uint8_t y_address, uint8_t number);

//@tanim Saat degerlerinin 00:00 seklinde toplandigi fonksiyon.
//@param minutes: Dakika degeri.
//@param hours: Saat degeri.
//@param theme: Saat temeasi.
void Write_Clock(uint32_t minutes, uint32_t hours, uint8_t theme);

//@tanim Saat while(1) dongusunde calisacak fonksiyon.
void Clock_Loop(void);

//@tanim Alarm caldiginda ok butonuna basildiginda alarmi durduracak fonksiyon.
void Clock_Ok_Button(void);

//@tanim Uygulama ilk acildiginda calisacak fonksiyon.
void Clock(void);

//@tanim Tarih degerlerinin 00:00:00 seklinde toplandigi fonksiyon.
//@param date_day: Ayin kacinci gunu.
//@param date_month: Kacinci ay.
//@param date_year: Hangi yil.
void Write_Date(uint8_t date_day, uint8_t date_month, uint16_t date_year);

//@tanim Tarih degerlerini iki basamakli yazdiran fonksiyon.
//@param x_address: Sutunun konumu. x_address [0,84] araliginda.
//@param y_address: Satirin konumu. y_address [0,5] araliginda.
//@param number: tarih degeri.
void Write_Date_Numbers(uint8_t x_address, uint8_t y_address, uint8_t number);
#endif /* CLOCK_H_ */

