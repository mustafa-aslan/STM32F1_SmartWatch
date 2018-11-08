// Header: ICONS
// File Name: icons.h
// Author: Mustafa Aslan
// Date: 7.11.2015

#ifndef ICONS_H_
#define ICONS_H_

#include "stm32f1xx_hal.h"
#include "nokia_5110.h"

#define BLUETOOTH_CONNECT_STATUS GPIO_PIN_12

//@tanim Bataryayi degerini okuyan fonksiyon.
void Battery_Read(void);

//@tanim Batarya iconunun ekrana cizen fonkdiyon.
//@param x_address: Sutunun konumu. x_address [0,84] araliginda.
//@param y_address: Satirin konumu. y_address [0,5] araliginda.
void Battery_Icon(uint8_t x_address, uint8_t y_address);

//@tanim Ses iconun ekrana cizen fonksiyon.
//@param x_address: Sutunun konumu. x_address [0,84] araliginda.
//@param y_address: Satirin konumu. y_address [0,5] araliginda.
void Bluetooth_Icon(uint8_t x_address, uint8_t y_address);

//@tanim Titresim iconun ekrana cizen foksiyon.
//@param x_address: Sutunun konumu. x_address [0,84] araliginda.
//@param y_address: Satirin konumu. y_address [0,5] araliginda.
void Vibration_Icon(uint8_t x_address, uint8_t y_address);

//@tanim Alarm iconunu ekrana cizen fonksiyon.
//@param x_address: Sutunun konumu. x_address [0,84] araliginda.
//@param y_address: Satirin konumu. y_address [0,5] araliginda.
void Alarm_Icon(uint8_t x_address, uint8_t y_address);

#endif /* ICONS_H_ */

