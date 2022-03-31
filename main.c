/*
 *  main.c
 *
 *  Created on: Dec 17, 2021
 *      Author: Omar Elsehity
 */



#include <stdio.h>
#include "headers.h"


int main(){

	setvbuf(stdout, NULL, _IONBF, 0);
	SWITCH_ENGINE_START();

	return 0;
}
