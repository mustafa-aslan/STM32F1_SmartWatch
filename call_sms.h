// Header: CALL SMS
// File Name: call_sms.h
// Author: Mustafa Aslan
// Date: 7.11.2015

#ifndef CALL_SMS_H_
#define CALL_SMS_H_

#include "stm32f1xx_hal.h"
#include "nokia_5110.h"

#define CALL_STARTED_ADDRES   'B' // Arama basladi saatin gonderecegi ilk deger.
#define SMS_ADDRESS    				'C' // Sms geldiginde saatin gonderecegi ilk deger.
#define CALL_ENDED_ADDRESS 		'K' // Arama sonlandiginda saatin gonderecegi deger.

#define VIB_MOTOR_PIN GPIO_PIN_2 // GPIOB
//@tanim Arama sonlandiginda calisacak fonksiyon.
void Call_Ended_Loop(void);

//@tanim Arama basladiginda calisacak fonksiyon.
void Call_Started_Loop(void);

void Sms_Loop(void);

#endif /* CALL_SMS_H_ */

