/*
 * Ultra_Private.h
 *
 * Created: 25/04/2022 17:05:57
 *  Author: shahe
 */ 


#ifndef ULTRA_PRIVATE_H_
#define ULTRA_PRIVATE_H_

#include "Ultra_Configuration.h"

void SetupUltrasonic(void);
void delay_10us();
void SendTrigger(void);
float ReceiveEcho(void);

#endif /* ULTRA_PRIVATE_H_ */