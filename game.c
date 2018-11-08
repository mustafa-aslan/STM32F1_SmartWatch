// Header: GAME
// File Name: game.c
// Author: Mustafa Aslan
// Date: 30.10.2015

#include "game.h"

extern TIM_HandleTypeDef htim1;

uint8_t Logo_Status;				 // Logo durumu.
uint8_t Random_Status;  	   // Sayac durumu.
uint8_t Point_Status;  			 // Puan durumu.
uint8_t Game_Language_Status;// Dil secme durumu.
uint8_t Game_Language; 		   // Dil.
uint8_t Game_Status;         // Oyun durumu.
uint8_t Game_Exit;  				 // Oyundan exit butonla cikildi.
uint16_t game_counter = 0;   // count_value sifirlandi.

	// Uzay gemisinin bitleri.
uint8_t space_ship[8] = {
0x81, 0x99, 0xFF, 0xBD, 0x99, 0xBD, 0x99, 0x99
};

const unsigned char ma_game_logo [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00,
0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x02, 0x02, 0xFE, 0xFE,
0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x02, 0x02, 0xFE, 0xFE, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
0xAA, 0x00, 0x00, 0x00, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0xFE,
0xFE, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
0x00, 0x00, 0xFF, 0xFF, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0xFF, 0xFF, 0xAA,
0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
0x0A, 0x0A, 0x00, 0xFF, 0xFF, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x2A, 0x2A,
0x2A, 0x2A, 0x2A, 0x2A, 0x00, 0x00, 0x3F, 0x3F, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x00,
0x00, 0x3F, 0x3F, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x2A, 0x2A,
0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2B, 0x2B, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x62, 0xF2, 0xFE, 0xFA, 0xF2, 0x62, 0x62, 0xF2, 0x62, 0x62, 0x00, 0x3C, 0x24, 0x24, 0x24,
0xE4, 0x00, 0x00, 0xFC, 0x24, 0x24, 0x24, 0x3C, 0x00, 0x00, 0xFC, 0x24, 0x24, 0x24, 0xFC, 0x00,
0x00, 0xFC, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0xFC, 0x24, 0x24, 0x24, 0x04, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3C, 0x24, 0x24, 0x24, 0xE4, 0x00, 0x00, 0xFC, 0x20, 0x20, 0x20, 0xFC, 0x00, 0x00,
0xFC, 0x00, 0x00, 0xFC, 0x24, 0x24, 0x24, 0x3C, 0x00, 0x62, 0x62, 0xF2, 0x62, 0x62, 0xF2, 0xFA,
0xFE, 0xF2, 0x62, 0x00, 0x00, 0x04, 0x04, 0x07, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00,
0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00,
0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04,
0x04, 0x04, 0x04, 0x05, 0x07, 0x04, 0x04, 0x00, 
};

	// Oyunda kalan canlari temsil eden kalplerin bitleri.
 uint8_t life[8] = {
	0x06, 0x0F, 0x1E, 0x3C, 0x1E,
	0x0F, 0X06, 0x00
 };

uint16_t score = 0; // Puan sifir.
uint8_t lose_score = 3; // 3 kaybedebilecegimiz can sayisi.
uint8_t for_random; // Rasgele sayi uretmek icin kullanilan bir degisken.
int8_t s_ship_address = 1; // Uzay araci y adresi. Oyunu ilk basladiginda bulunacagi konum 1.sutum.
uint8_t deuterium_x_address = 84; // Doteryum x adresi.

void Game_Reset_All(void){
	score = 0; // Puan sifir.
	lose_score = 3; // 3 kaybedebilecegimiz can sayisi.
	s_ship_address = 1; // Uzay araci y adresi. Oyunu ilk basladiginda bulunacagi konum 1.sutum.
	deuterium_x_address = 84; // Doteryum x adresi.
	HAL_TIM_Base_Stop_IT(&htim1);
	Game_Language_Status = LANGUAGE_NOT_SELECTED;
}

void Game_Loop(void){
	Random_Status = RANDOM_START; // Rasgele sayi uretmeye basla.
		// Logo ekrandan kalti, dil belirlendi ve oyuna start verildi ise.
	if(Game_Status == GAME_START && Logo_Status == LOGO_NOT_ON_SCREEN && Game_Language_Status == LANGUAGE_SELECTED){ 
			// Display 84 sutundan olustugu icin.
		for(uint8_t x = 0; x < 84; x++){
			if(Game_Exit == 0){
				if(Point_Status == POINT_RESET){ 
					Deuterium(deuterium_x_address,  Random_Y_Address(), WRITE); // Doteryumu belirlenen adresten ciz.
					HAL_Delay(Game_Speed()); // Oyun hizini belirle.
					Deuterium(deuterium_x_address--,  Random_Y_Address(), CLEAR); // Doteryumu sil ve sutun adresini bir azalt.
						// Doteryum uzay aracini tam onunde ise ve ayni satirda ise.
					if(deuterium_x_address == 9 && Random_Y_Address() == s_ship_address){ 
						++score; // Skoru bir arttir.
						Write_Number(34, 0, score); // Skoru yazdir.
						Point_Status = POINT_SET; // Puan alindi.
						deuterium_x_address = 84; // Doteryumun adresini sifirla.
						// Doteryum sutun adresi sifir ise (puan alinamamis demektir).
					}else if (deuterium_x_address == 0){
						Life(61, 0, --lose_score); // Kalplerden birini sil.
							// Tum canlar kaybedildiyse.
						if(lose_score == 0){ 
							Clear_Display(); // Ekrani temizle.
							Set_Address(10, 1); // Adresi ayarla.
								//Dil turkce ise.
							if(Game_Language == TURKISH){ 
								Write_String("OYUN BITTI"); // OYUN BITTI cumlesini yazdir.
								Set_Address(10,2);  // Adres ayarla.
								Write_String("SKORUN"); // SKORUN yazisini yazdir.
								Write_Number(10, 3, score); // Alinan skoru yazdir.
								Set_Address(10,4); // Adres ayarla.
								Write_String("TEKRAR OYNA"); // TEKRAR OYNA yazisini yazdir.
						}
								// Dil ingilizce ise.
							else if(Game_Language == ENGLISH){
								Write_String("GAME OVER"); // GAME OVER yazisini yazdir.
								Set_Address(10,2); // Adres ayarla.
								Write_String("YOUR SCORE"); // YOUR SCORE yazisini yazdir.
								Write_Number(10, 3, score); // Alina skoru yazdir.
								Set_Address(10,4); // Adres ayarla.
								Write_String("PLAY AGAIN"); // PLAY AGAIN yazisini yazdir.
							}
						Game_Status = GAME_FINISH; // Oyun bitti.
						}
					}
					if(deuterium_x_address == 0){deuterium_x_address = 84;}; // Deteryun adresi sinira ulastiginda sifirla.
				}
			}	
		}		
		Point_Status = POINT_RESET; // Puan alimi tamamlandi.		
	}	
}

void Game_Timer(void){
	++game_counter; // count_value bir arttir.
		  // Rasgele sayi uretmeye hazirsa.
	if(Random_Status == RANDOM_START){ 
		for_random = game_counter; // for_random'u count_value'ye kopyala.
		Random_Status = RANDOM_STOP;  // Rasgele sayi uretmeyi bitir.
	}
		// count_value sinira ulastigida degiskeni sifirla.
	if(game_counter == 0xFFFF){game_counter = 0;};
}

void Game_Up_Button(void){
	 // Oyun baslamissa.(Yani logo ekrandan kalmis ve dil secilmisse.)
	if(Game_Status == GAME_START && Logo_Status == LOGO_NOT_ON_SCREEN && Game_Language_Status == LANGUAGE_SELECTED){    
		// Display ilk satir 0'inci satir oldugundan uzay araci 0 satirdan yukari cikamaz..
		if(s_ship_address > 1){					 		     
			Space_Ship(0, s_ship_address, CLEAR);  // Uzay aracini eski adresinden sil.
			Space_Ship(0, --s_ship_address, WRITE);// Uzay aracini bir ust satira displaye ciz.
		}
	}
	  // Dil secme bolumundeyken.
	if(Game_Language_Status == LANGUAGE_NOT_SELECTED && Logo_Status == LOGO_NOT_ON_SCREEN){
		Space_Ship(7, 3, CLEAR); // Uzay aracini 3 satirdan sil.
		Space_Ship(7, 2, WRITE); // Uzay aracini 2 satira ciz.			
		Game_Language = TURKISH; 		 // Dil turkce.
	}	
}

void Game_Down_Button(void){
	// Oyun baslamissa.(Yani logo ekrandan kalmis ve dil secilmisse.) 
	if(Game_Status == GAME_START && Logo_Status == LOGO_NOT_ON_SCREEN && Game_Language_Status == LANGUAGE_SELECTED){
		// Display 5'inci satirdan olustugundan uzay araci 5 satirdan asagi inemez. Ilk satir 0'inci satirdir.
		if(s_ship_address < 5){										
			Space_Ship(0, s_ship_address, CLEAR);   // Uzay aracini eski adresinde sil.		
			Space_Ship(0, ++s_ship_address, WRITE);	// Uzay aracini bir alt satira displaye ciz.
		}
	}
		// Dil secme bolumundeyken.
	if(Game_Language_Status == LANGUAGE_NOT_SELECTED && Logo_Status == LOGO_NOT_ON_SCREEN){
		Space_Ship(7, 2, CLEAR); // Uzay aracini 2 satirdan sil.
		Space_Ship(7, 3, WRITE); // Uzay aracini 3 satira ciz.
		Game_Language = ENGLISH; 		 // Dil ingilizce.
	}	
}

void Game_Ok_Button(void){
	// Oyun bittiyse.
	if(Game_Status == GAME_FINISH){
		score = 0; // Skoru yeni oynu icin sifirla.
		lose_score = 3; // Kaybedebilecegimiz can sayici tekrar 3. 
		Game_Status = GAME_START; // Oyunu baslat.
		Clear_Display(); // Ekrani temizle.
		Space_Ship(0, s_ship_address, WRITE); // Uzay aracini 0'inci satira ciz. 
			// Dil türkce ise.
		if(Game_Language == TURKISH){
			Set_Address(0, 0); // Adres 0'inci satir 0'inci sutun.
			Write_String("SKOR"); // SKOR kelimesini belirlene adrese yaz.
			Write_Number(34, 0, score); // Skoru 34'uncu satir 0'inci sutuna yaz.
		}
		  // Dil ingilizce ise.
		else if(Game_Language == ENGLISH){
			Set_Address(0, 0); // Adres 0'inci satir 0'inci sutun.
			Write_String("SCORE"); // SCORE kelimesini belirlene adrese yaz.
			Write_Number(34, 0, score); // Skoru 34'uncu satir 0'inci sutuna yaz.
		}
			Life(61, 0, lose_score); // Cani belirten kalpleri 61'inci satir 0'inci sutuna yaz.				
	}
	  // Dil secim bolumdeyse.
	if(Game_Language_Status == LANGUAGE_NOT_SELECTED && Logo_Status == LOGO_NOT_ON_SCREEN){
		Game_Language_Status = LANGUAGE_SELECTED; // Dil artik secildi.				
		Clear_Display(); // Displayi dil seceneklerinden temizle.
		Space_Ship(0, s_ship_address, WRITE); // Uzay gemizi belirlenen adrese ciz.
			//Dil Turkce ise.
		if(Game_Language == TURKISH){
			Set_Address(0, 0); // Adres 0'inci satir 0'inci sutun.
			Write_String("SKOR"); // SKOR kelimesini belirlene adrese yaz.
			Write_Number(34, 0, score); // Skoru 34'uncu satir 0'inci sutuna yaz.
		}
		else if(Game_Language == ENGLISH){
			Set_Address(0, 0); // Adres 0'inci satir 0'inci sutun.
			Write_String("SCORE"); // SCORE kelimesini belirlene adrese yaz.
			Write_Number(34, 0, score); // Skoru 34'uncu satir 0'inci sutuna yaz.
		}
			Life(61, 0, lose_score); // Cani belirten kalpleri 61'inci satir 0'inci sutuna yaz.			
		}
			// Logo ekranda ise.
	if(Logo_Status == LOGO_ON_SCREEN){			
		Clear_Display(); // Logo ekrandan temizle.	
		Logo_Status = LOGO_NOT_ON_SCREEN; // Logo ekrandan kalkti.					
		Set_Address(20, 2); // Adres 20'inci satir 2'inci sutun.
		Write_String("TURKCE"); // Belirlene adrese TURKCE yaz. 
		Set_Address(20, 3); // Adres 20'inci satir 3'inci sutun.
		Write_String("ENGLISH"); // Belirlene adrese ENGLISH yaz.
		Space_Ship(7, 2, WRITE); // Uzay aracini 7'inci satir 2'ci sutuna ciz. 
		Game_Language = TURKISH; // Uzay araci ilk turkceyi isaret ettigi icin.		
	}		 	
}

void Game_Logo(void){
	HAL_TIM_Base_Start_IT(&htim1);
	Set_Address(0,0);	
	Clear_Display(); // Ekrani temizle.			
		// Logoyu ekrana ciz.
	for(uint16_t bit=0; bit<504; bit++){	
		Write_Data(ma_game_logo[bit]);		
	}	
	Logo_Status = LOGO_ON_SCREEN; // Logo ekranda cizili.
}

uint8_t Random_Y_Address(void){
	uint8_t random_address = for_random % 5;	// Display 6 satirdan olustugu icin.
	++random_address; // 0'inci satirda skor yazdigi icin;
	return random_address;	// Random sayiyi dondur.
}

void Space_Ship(uint8_t x_address, uint8_t y_address, uint8_t clear_or_write){
	Set_Address(x_address, y_address);
	if(clear_or_write == WRITE){
		for(uint8_t _8column = 0; _8column < 8; _8column++){
			Write_Data(space_ship[_8column]);
		}
	}
	else if(clear_or_write == CLEAR){
		Set_Address(x_address, y_address);
		for(uint8_t _8column = 0; _8column < 8; _8column++){
			Write_Data(0);
		}
	}
}

void Deuterium(uint8_t x_address, uint8_t y_address, uint8_t clear_or_write){
	Function_Set(PD_RESET, V_SET, H_RESET);
	if(clear_or_write == WRITE){
		Set_Address(x_address, y_address);
		Write_Data(0x3C);
		Set_Address(++x_address, y_address);
		Write_Data(0x3C);
		Set_Address(++x_address, y_address);
		Write_Data(0x3C);
		Set_Address(++x_address, y_address);
		Write_Data(0x3C);
		Set_Address(++x_address, y_address);
		Write_Data(0x3C);
	}
	else if(clear_or_write == CLEAR){
		Set_Address(x_address, y_address);
		Write_Data(0);
		Set_Address(++x_address, y_address);
		Write_Data(0);
		Set_Address(++x_address, y_address);
		Write_Data(0);
		Set_Address(++x_address, y_address);
		Write_Data(0);
		Set_Address(++x_address, y_address);
		Write_Data(0);}
	Function_Set(PD_RESET, V_RESET, H_RESET);
}

void Life(uint8_t x_address, uint8_t y_address, uint8_t life_number){
	Set_Address(x_address, y_address);
	 // Can degeri 3.
	if(life_number == 3){
		for(uint8_t tree_times = 0; tree_times < 3; tree_times++){
			for(uint8_t _8line = 0; _8line < 8; _8line++){
				Write_Data(life[_8line]);
			}
		}
	}
	 // Can degeri 2.
	else if(life_number == 2){
		for(uint8_t two_times = 0; two_times < 2; two_times++){
			for(uint8_t _8line= 0; _8line< 8; _8line++){
				Write_Data(life[_8line]);
			}
		}
		for(uint8_t _8line = 0; _8line <8; _8line++){
			Write_Data(0x00);
		}
	}
	 // Can degeri 1.
	if(life_number == 1){
		for(uint8_t one_time = 0; one_time< 8; one_time++){
			Write_Data(life[one_time]);
		}
		for(uint8_t two_times = 0; two_times < 2; two_times++){
			for(uint8_t _8line= 0; _8line < 8; _8line++){
				Write_Data(0x00);
			}
		}	
	}
	 // Can degeri 0.
	if(life_number == 0){
		for(uint8_t four_times = 0; four_times< 4; four_times++){
			for(uint8_t _8line= 0; _8line < 8; _8line++){
				Write_Data(0x00);
		  }
	  }	
	}
}

uint8_t Game_Speed(void){
	uint8_t speed;
	// Oyun hizinin skora gore degisimi.
	if(score < 15){speed = 100;}
	else if((score > 14) && (score < 25)){speed = 87;}
	else if((score > 24) && (score < 35)){speed = 83;}
	else if((score > 34) && (score < 45)){speed = 75;}
	else if((score > 44) && (score < 55)){speed = 66;}
	else if((score > 54) && (score < 65)){speed = 62;}
	else if((score > 64) && (score < 75)){speed = 51;}
	else if((score > 74) && (score < 95)){speed = 40;}
	else if((score > 94) && (score < 115)){speed = 30;}
	else if(score > 114){speed = 20;}
	return speed; 
}








