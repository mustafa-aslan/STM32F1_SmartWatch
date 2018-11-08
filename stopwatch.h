// Header: STOPWATCH
// File Name: stopwatch.h
// Author: Mustafa Aslan
// Date: 4.1.2015

#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include "stm32f1xx_hal.h"
#include "nokia_5110.h"

#define STOPWATCH_START 1 // Kronometre sayima basladi.
#define STOPWATCH_STOP  0 // Kronometre sayim yapilmiyor.
#define STOPWATCH_WAITING 2 // Kronometer sonraki sayimi bekliyor.

#define BLUETOOTH_EN GPIO_PIN_11 // GPIOA

//@tanim Kronometre ilk acildiginda calisacacak fonksiyon.
void Stopwatch(void);

//@tanim Kronometre icindeyken ok butonuna basildiginda calisacak fonksiyon.
void Stopwatch_Ok_Button(void);

//@tanim Kronometre degerini 00:00:00 seklinde yazdirean fonksiyon.
//@param miliseconds: Milisaniye degeri.
//@param seconds: Saniye degeri.
//@param minutes: Dakika degeri.
void Stopwatch_Write(uint16_t miliseconds, uint8_t seconds, uint8_t minutes);

//@tanim Krometrinin timer callback fonksiyonunun icinde cakisacak fonksiyon.
//@param: stopwatch_state: Kronometre ekranda olup olmasini belirten degisken girilecek.
void Stopwatch_Timer(uint8_t stopwatch_state);


#endif /* STOPWATCH_H_ */
