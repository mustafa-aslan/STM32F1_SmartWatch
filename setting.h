// Header: SETTING
// File Name: setting.h
// Author: Mustafa Aslan
// Date: 29.10.2015

#ifndef SETTING_H_
#define SETTING_H_

#include "stm32f1xx_hal.h"
#include "nokia_5110.h"

#define BLUETOOTH_EN GPIO_PIN_11 //GPIOB

#define WRITE 1 // Displaye ciz.
#define CLEAR 0 // Displayden sil.

#define SETTING_MENU_LIGHT 0		 // Arkaplan parlakligi.
#define SETTING_MENU_BLUETOOTH 1		
#define SETTING_MENU_VIBRATION 2 // Titresim
#define SETTING_MENU_LANGUAGE 3  // Dil
#define SETTING_MENU_THEME 4	   // 
#define SETTING_MENU_SET_VIA_BT 5 // Bt ile ayarlari kur.

#define SELECTED 		 1 // Secildi.
#define NOT_SELECTED 0 // Secilmedi.

#define ON    1	// Acik.
#define OFF   0	// Kaplali.

#define TR 1	// Turkce.
#define EN 0	// Ingilizce.

#define THEME_CLASSIC 1 // Tema klasik.
#define THEME_DIGITAL 0 // Tema dijital.

#define CLOCK_BT_ADDRESS   'F' // Saat ayari yapildiginda saatin gonderecegi ilk deger.
#define DATE_BT_ADDRESS    'E' // Tarih ayari yapildiginda saatin gonderecegi ilk deger.

//@tanim Ilk uygulama acildiginda calisacak fonksiyon.
void Set_Via_Bt(void);

//@tanim Bluetoot verilerinin alindigi ve islendigi fonsiksiyon.
void Setting_Loop(void);

//@tanim Telefondan gelen sayi verilerini 2lik sayi sistemine ceviren fonksiyon.
uint8_t Char_To_Decimal(uint8_t char_value);

//@tanim Ayarlar ekraninin ilk göstreriminin ve genel ayarlarin yapildigi fonksiyon.
void Setting_Menu(void);

//@tanim Ayarlarda asagi butonuna basildiginda calisacak fonksiyon.
void Setting_Down_Button(void);

//@tanim Ayarlarda yukari butonuna basildiginda calisacak fonksiyon.
void Setting_Up_Button(void);

//@tanim Ayarlar menusunde ok butonuna basildiginda calisacak fonksiyon.
void Setting_Ok_Button(void);

//@tanim Tum durumlari sifirlayan ve imleci ilk konumuna ayarlayan fonksiyon.
void Setting_Reset(void);

//@tanim Menude secimin gosteren imlec(>)'in yazilmasi veya silinmesini saglayan fonksiyon.
//@param y_address: Satirin konumu. y_address [0,5] araliginda.
//@param write_or_clear: Displayden ciz ya da temizle.
void Greater(uint8_t y_address,uint8_t write_or_clear);

#endif /* SETTING_H_ */

