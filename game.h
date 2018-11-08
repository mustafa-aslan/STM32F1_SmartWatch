// Header: GAME
// File Name: game.h
// Author: Mustafa Aslan
// Date: 30.10.2015

#ifndef GAME_H_
#define GAME_H_

#include "stm32f1xx_hal.h"
#include "nokia_5110.h"

// MA logo tanimlari ve degiskeni.
#define LOGO_ON_SCREEN 		 1	// Logo ekranda cizili.
#define LOGO_NOT_ON_SCREEN 0	// Logo ekranda cizli degil.


// Rasgele sayi uretimi icin.
#define RANDOM_START 1	// Random sati icin sayaci baslat.
#define RANDOM_STOP  0  // Sayaci durdur.


// SPACE_SHIP ve doteryum fonksiyonlari icin
#define WRITE 1 // Displaye ciz.  
#define CLEAR 0 // Displayden temizle.

// Puan durumu icin.
#define POINT_SET 1   // Puan alindi.
#define POINT_RESET 0 // Puan alimi tamamlandi.


// Dil secimi.
#define LANGUAGE_SELECTED 1 // Dil belirlendi.
#define LANGUAGE_NOT_SELECTED 0 // Dil henuz belirlenmedi.

#define TURKISH 1 // Turkce dil secenegi.
#define ENGLISH 0 // Ingilizce dil secenegi.


// Oyun
#define GAME_START 1  // Oyunu baslat.
#define GAME_FINISH 0 // Oyunu bitir.

 
//@tanim Displaye logoyu ciz.
void Game_Logo(void);

//@tanim Uzay gemisini ciz, temizle ve geminin konumunun belirlendigi fonksiyon.
//@param x_address: Sutunun konumu. x_address [0,84] araliginda.
//@param y_address: Satirin konumu. y_address [0,5] araliginda.
//@param clear_or_write: Displayden temizle ya da ciz.
void Space_Ship(uint8_t x_address, uint8_t y_address, uint8_t clear_or_write);
 
//@tanim Doteryumun ciz, temizle ve doteryum konumunun belirlendigi fonksiyon.
//@param x_address: Sutunun konumu. x_address [0,84] araliginda.
//@param y_address: Satirin konumu. y_address [0,5] araliginda.
//@param clear_or_write: Displayden temizle ya da ciz.
void Deuterium(uint8_t x_address, uint8_t y, uint8_t clear_or_write);
 
//@tanim Oyundaki canin ciz, temizle ve canin konumunun belirlendigi fonksiyon.
//@param x_address: Sutunun konumu. x_address [0,84] araliginda.
//@param y_address: Satirin konumu. y_address [0,5] araliginda.
//@param clear_or_write: Displayden temizle ya da ciz.
void Life(uint8_t x_address, uint8_t y_address, uint8_t life_number);
 
//@tanim Rasgele sayi uretme fonksiyonu.
uint8_t Random_Y_Address(void);
 
//@tanim Oyun hizinin belirledigi fonksiyon.
uint8_t Game_Speed(void);

//@tanim Oyundaki tum ayarlari, puan durumlarini sifirlayan fonksiyon.
void Game_Reset_All(void);

//@tanim Ok butonuna basildiginda calisacak fonksiyon.
void Game_Ok_Button(void);

//@tanim Dowm butonuna basildiginda calicak fonksiyon.
void Game_Down_Button(void);

//@tanim Up butonuna basildiginda calicak fonksiyon.
void Game_Up_Button(void);

//@tanim Rasgele sayi uretmek icin timer callback fonksiyonunda calisacak fonksiyon.
void Game_Timer(void);

//@tanim Dongude calicak fonksiyon.
void Game_Loop(void);


#endif /* GAME_H_ */
