// Header: NOKIA 5110
// File Name: nokia_5110.h
// Author: Mustafa Aslan
// Date: 25.10.2015

#ifndef NOKIA_5110_H_
#define NOKIA_5110_H_

#include "stm32f1xx_hal.h"

/*
 __________________
| ________________ |		#84X84 LCD DISPLAY -> NOKIA 5110	  
||						    ||			1  -> RST     (Reset)
||	  84X84LCD	  ||      2  -> CE	    (Chip Sec)
||  mustafaaslan  ||			3  -> DC	    (Data/Komut)
|| 2015.wordpress ||      4  -> DIN	(Data giris)
||		 .com		    ||			5  -> CLK    (Clock hiz)
||________________||			6  -> 3.3V   (Vcc)
|									 |			7	 -> LIGHT  (Arkaplan ekran aydinlatmasi)
|__________________|			8  -> GND    (Ground)
  | | | | | | | |
  1 2 3 4 5 6 7 8

*/
// MCU baglanti tanimlari.
#define RST GPIO_PIN_0	// GPIOA
#define CE  GPIO_PIN_1	// GPIOA	
#define DC  GPIO_PIN_2	// GPIOA
#define DIN GPIO_PIN_3	// GPIOA
#define CLK GPIO_PIN_4	// GPIOA

// D/C tanimlari
#define COMMAND GPIO_PIN_RESET // Komut
#define DATA    GPIO_PIN_SET   // Veri

// FUNCTION_SET  Function set tanimlari
#define PD_SET 		4	 // Chip aktif
#define PD_RESET  0	 // Power down modu
#define V_SET     2  // Dikey adresleme
#define V_RESET   0  // Yatay adresleme
#define H_RESET 	0  // Basit ayarlar
#define H_SET     1  // Genisletilmis ayarlar
/*
#V_SET DIKEY ADRESLEME        	#V_RESET YATAY ADRESLEME    
	0 	6		.		.		.								0		1		2		.		.		.
	1		7		.		.		.								84	85  86	.		.		.
	2		.		.		.		.								.		.		.		.		.		.
	3		. 	.		.		.								.		.		.		.		.		.
	4		.		.		.		.								.		.		.		.		.		.
	5		.		.		.		504							.		.		.		.		.		504

*/

// Display mode tanimlari
#define DISPLAY_BLANK  					 0 // Tüm pikseller kapali.
#define NORMAL_MODE     				 4 // Arkaplan beyaz üstüne siyah karakterler yazmak icin.
#define ALL_DISPLAY_SEGMENTS_ON  1 // Tum pikseller acik.
#define INVERSE_VIDEO_MODE       5 // Arkaplan siyah üstüne beyaz karakterler yazmak icin.

// Temperature control tanimlari
#define Vlcd_TEMP_COEF_0	0 
#define Vlcd_TEMP_COEF_1	1  
#define Vlcd_TEMP_COEF_2	2 
#define Vlcd_TEMP_COEF_3	3 

//@tanim Bit kaydirarak 8 bit veri iletimi.
//@param spi_value: Gonderilecek deger.
void Basic_Spi(uint8_t spi_value);

//@tanim Display fonksiyon secme.
//@param pd_select: pd degerini sec.
//@not Parametrelerin alabilecegi degerler ve aciklamalari yukarida.
void Function_Set(uint8_t pd_select, uint8_t v_select, uint8_t h_select);;

//@tanim 8 bit veri yazma fonksiyonu.
//@param write_data: Yazilacak veri.
void Write_Data(uint8_t write_data);

//@tanim Karakter yazma fonksiyonu.
//@param write_char: Yazilacak karakterin degeri.
void Write_Char(unsigned char write_char);

//@tanim Kelime ya da cumle yazdirma fonksiyonu.
//@param write_string: Yazilacak kelime ya da cumle. 
void Write_String(char* write_string);

//@tanim Numara yazdirma fonksiyonu.
//@param x_address: Sutunun konumu. x_address [0,84] araliginda.
//@param y_address: Satirin konumu. y_address [0,5] araliginda.
//@param number: Yazdirilacak sayi.
void Write_Number(uint8_t x_address, uint8_t y_address, uint16_t number);
 
//@tanim Display modu secme fonksiyonu.
//@param display_mode_select: Secilecek mode.
//@not Secilecek modun degerleri ve aciklamalari yukarida.
void Display_Control(uint8_t display_mode_select);
 
//@tanim Displayde konum belirleme.
//@param x_address: Sutunun konumu. x_address [0,84] araliginda.
//@param y_address: Satirin konumu. y_address [0,5] araliginda.
void Set_Address(uint8_t x_address, uint8_t y_address);
 
//@tanim 
//@param 
void Temperature_Control(uint8_t set_temperature_coeffcient);
 
//@tanim
//@param
void Bias_System(uint8_t set_bias_system);
 
//@tanim
//@param
void Set_Vop(uint8_t set_vop);
 
//@tanim Direk komut verisi gonderme.
//@param command: Komut verisi
void Command_Data(uint8_t command);
 
//@tanim Displayi temizle.
void Clear_Display(void);
 
//@tanim Ornek ayarlar.
//@not Bu fonksiyon main'in iceinde tanimlandiktan sonra WRITE_DATA,
//WRITE_CHAR, WRITE_NUMBER, WRITE_STRING gibi fonksiyonlar kullanilabilir.
void Example_Setting(void);

//@tanim Uc basamakli sayi yazmak icin kullanilan fonksiyon.
//@param x_address: Sutunun konumu. x_address [0,84] araliginda.
//@param y_address: Satirin konumu. y_address [0,5] araliginda.
//@param number: Yazilacak sayi.
void Write_Three_Number(uint8_t x_address, uint8_t y_address, uint16_t number);

//@tanim Dile gore string yazdirma fonksiyounu.
//@param turkish_string: Turkce kelime yada cumle.
//@param english_string: Ingilizce kelime yada cumle.
//@param tr_or_en: Dil secimi.
void Write_String_Language(char* turkish_string, char* english_string, uint8_t tr_or_en);

//@tanim Dile gore belirlene adrese string yazdirma fonksiyounu.
//@param turkish_string: Turkce kelime yada cumle.
//@param tr_address: Sutunun konumu. x_address [0,84] araliginda.
//@param tr_address: Satirin konumu. y_address [0,5] araliginda.
//@param english_string: Ingilizce kelime yada cumle.
//@param en_address: Sutunun konumu. x_address [0,84] araliginda.
//@param en_address: Satirin konumu. y_address [0,5] araliginda.
//@param tr_or_en: Dil secimi.
void Write_String_Language_Address(uint8_t x_tr, uint8_t y_tr, char* tr_string, uint8_t x_en, uint8_t y_en, char* en_string, uint8_t tr_or_en);

//@tanim Iki basamakli sayi yazmak icin kullanilan fonksiyon.
//@param x_address: Sutunun konumu. x_address [0,84] araliginda.
//@param y_address: Satirin konumu. y_address [0,5] araliginda.
//@param number: Yazilacak sayi.
void Write_Two_Number(uint8_t x_address, uint8_t y_address, uint16_t number);
#endif /* NOKIA_5110_H_ */
