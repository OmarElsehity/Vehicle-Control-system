/*
 *  header.h
 *
 *  Created on: Dec 17, 2021
 *      Author: Omar Elsehity
 */
#include "functions.c"

#ifndef HEADERS_H_
#define HEADERS_H_


short ENGINE_START();
void SWITCH_ENGINE_START();
void ENGINE_ON();
void ENGINE_OFF();
void QUIT();
void SET_LIGHTS(short *speed_ptr);
void Tr(short *Tr_ptr);
void Tg(short *Tg_ptr);
void SPEED(short *Tr_ptr, short *Tg_ptr);
void DISPLAY();
void REQUIST_AGAIN();


#endif /* HEADERS_H_ */
