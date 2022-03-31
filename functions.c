/*
 *  functions.c
 *
 *  Created on: Dec 17, 2021
 *      Author: Omar Elsehity
 */
#include <stdio.h>
#include "headers.h"

// Preprocessors for the traffic light input
#define Green_LIGHT ('g')
#define Yellow_LIGHT ('y') //Here you can change the Y to O in order to match the requirement without much edit.
#define Red_LIGHT ('r')


// Car components State at the beginning
short AC_STATE  = 0;
short ENGINE_STATE = 0;						// Initially engine is off
short ENGINE_TEMP_CONTROLLER = 0;

// Control flags for the functions
short SWITCH_FLAG = 1;

short SENSOR_STATE = 1;
short LIGHT = 1;


// Data needed and initially has been set to a logical values
short current_speed = 0, room_temp = 35, engine_temp = 90;


// Function takes the input of requirement 1
short ENGINE_START(){
	char StartInput;
	printf ("a. Turn on the vehicle engine\n");
	printf ("b. Turn off the vehicle engine\n");
	printf ("c. Quit the system\n\n");
	scanf  (" %c", &StartInput);

	return StartInput;
}

// The core function that controls the flow of the program depends on data of requirement 1
void SWITCH_ENGINE_START(){

	short StartInput;
	do{								// Loop to validate the input
		StartInput = ENGINE_START();

		switch (StartInput){
			case 'a':
			case 'A':
				printf("Engine is starting  \n\n");
				SWITCH_FLAG = 0;  	// To exit the do while loop
				ENGINE_ON();      	// Continue to the sensors menu list
				break;
			case 'b':
			case 'B':
				SWITCH_FLAG = 0;
				ENGINE_OFF();		// Call function of requirement 3
				break;
			case 'c':
			case 'C':
				SWITCH_FLAG = 0;
				QUIT();				// Call function of requirement 2
				break;
			default:
				printf("Please enter a suitable choice\n\n");
		}

	}while(SWITCH_FLAG == 1);
}

// Function of the ON state that displays sensors menu
void ENGINE_ON(){

	ENGINE_STATE = 1;						// Update Engine state flag
	char SensorsMenuInput;
	printf ("a. Turn off the vehicle engine\n");
	printf ("b. Set the traffic light color\n");
	printf ("c. Set the room temperature\n");
	printf ("d. Set the engine temperature\n");

	do{										// Loop to validate the input
		scanf  (" %c", &SensorsMenuInput);

		switch (SensorsMenuInput){
			case 'a':
			case 'A':
				printf("Engine is turning off  \n\n");
				ENGINE_STATE = 0;
				SENSOR_STATE = 0;
				SWITCH_ENGINE_START(); 		// Back to the first Function (requirement 8)
				break;

			case 'b':
			case 'B':
				SENSOR_STATE = 0;
				SET_LIGHTS(&current_speed); // Function of requirement 7.a
				break;

			case 'c':
			case 'C':
				SENSOR_STATE = 0;
				Tr(&room_temp);				// Function of requirement 7.b
				break;

			case 'd':
			case 'D':
				SENSOR_STATE = 0;
				Tg(&engine_temp);			// Function of requirement 7.c
				break;

			default:
				printf("Please enter a suitable choice\n");
		}

	}while(SENSOR_STATE == 1);


}

// Function of requirement 3
void ENGINE_OFF(){

	// Check the engine if off
	if (ENGINE_STATE == 0){
		printf("Engine is already turned of  \n\n");
	}
	else{
		ENGINE_STATE = 0;
	}


	SPEED(&room_temp, &engine_temp);		// Function of requirement 7.d
	SWITCH_ENGINE_START(); 					// Back to the first menu

}

// Function of requirement 2
void QUIT(){
	printf ("\n\n************************\n*** System has ended ***\n************************\n");

}

// Function of requirement 7.a
void SET_LIGHTS(short *speed_ptr){

	char LIGHT_COLOR;
	printf("Enter the required light color\n");

	do{									// Loop to validate the input
		scanf (" %c", &LIGHT_COLOR);

		switch(LIGHT_COLOR){
			case Green_LIGHT:
				LIGHT = 0;
				*speed_ptr = 100;		// Set speed to 100
				break;
			case Yellow_LIGHT:
				LIGHT = 0;
				*speed_ptr = 30;		// Set speed to 30
				break;
			case Red_LIGHT:
				LIGHT = 0;
				*speed_ptr = 0;			// Set speed to 0
				break;
			default:
				printf("Please enter a suitable choice\n");

		}

	}while(LIGHT == 1);

	SPEED(&room_temp, &engine_temp);		// Function of requirement 7.d
	DISPLAY();								// Function of requirement 7.e
	ENGINE_ON();							// Back to the first menu
}

// Function of requirement 7.b
void Tr(short *Tr_ptr){				// Tr stands for Room temperature

	int ROOM_TEMP;
	printf ("Enter the required room temperature\n");
	scanf (" %d", &ROOM_TEMP);

	if (ROOM_TEMP <= 10 || ROOM_TEMP >= 30){
		AC_STATE = 1;
		*Tr_ptr = 20;
	}
	else if(ROOM_TEMP > 10 && ROOM_TEMP < 30){
		*Tr_ptr = ROOM_TEMP;
		AC_STATE = 0;
	}

	SPEED(&room_temp, &engine_temp);		// Function of requirement 7.d
	DISPLAY();								// Function of requirement 7.e
	ENGINE_ON(); 							// Back to the first menu

}

// Function of requirement 7.c
void Tg(short *Tg_ptr){				// Tg stands for Engine temperature


	int ENGINE_TEMP;
	printf("Enter the required engine temperature\n");
	scanf (" %d", &ENGINE_TEMP);

	if (ENGINE_TEMP < 100 || ENGINE_TEMP > 150){
		ENGINE_TEMP_CONTROLLER = 1;
		*Tg_ptr = 125;
	}
	else{
		ENGINE_TEMP_CONTROLLER = 0;
		*Tg_ptr = ENGINE_TEMP;
	}

	SPEED(&room_temp, &engine_temp);		// Function of requirement 7.d
	DISPLAY();								// Function of requirement 7.e
	ENGINE_ON();		 					// Back to the first menu

}

// Function of requirement 7.d
void SPEED(short *Tr_ptr, short *Tg_ptr){

	if (current_speed == 30){  				 // Checking the speed meter if = 30
		if (AC_STATE == 0){
			AC_STATE = 1;
			*Tr_ptr = ((*Tr_ptr)*1.25) +1;   // Set room temp
		}
		if(ENGINE_TEMP_CONTROLLER == 0){
			ENGINE_TEMP_CONTROLLER = 1;
			*Tg_ptr = ((*Tg_ptr)*1.25) +1;	 // Set engine temp
		}

	}
}

// Function of requirement 7.e
void DISPLAY(){


	printf("\n----------------------------------\n");

	//	Printing Engine state (ON/ OFF) and the current speed
	if (ENGINE_STATE){
		printf("\nEngine is currently ON\n");
	}
	else{
		printf("\nEngine is currently OFF\n");
	}
	printf("current_speed is: %d\n", current_speed);


	//	Printing AC state and Room temperature (Tr)
	if (AC_STATE){
		printf("\nAC is currently ON\n");
	}
	else{
		printf("\nAC is currently OFF\n");
	}
	printf("current room temperature is: %d C\n", room_temp);


	//	Printing Engine Temperature Controller State and Engine temperature (Tg)
	if (ENGINE_TEMP_CONTROLLER){
		printf("\nEngine temperature controller is currently ON\n");
	}
	else{
		printf("\nEngine temperature controller is currently OFF\n");
	}
	printf("Current engine temperature is: %d C\n", engine_temp);


	printf("\n----------------------------------\n\n");

}







