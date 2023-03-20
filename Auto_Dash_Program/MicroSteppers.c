/********************************************************************************************************************************
 *  Author:     	Corey Moura
 *  Lab:        	FINAL PROJECT
 *  Date:       	Dec 9, 2019
 *  Class:      	EGR 326
 *  Instructor: 	Dr. Kandalaft
 *
 *  Description:	Micro Step functions
 *
 *  Notes:     	 MicroSteppers.c
 *******************************************************************************************************************************/
#include <EGR326Lib.h>                                      	// Personal library
#include "driverlib.h"                                                          // Driverlib library
#include "msp.h"
 
#include "stdint.h"                                         	// Intger lib
#include "string.h"                                                         	// Allows the use of string functions
#include <stdbool.h>                                        	// Allows Boolean logic
 
#include <math.h>                                           	// MathLib used for the calculation of distance
#include <stdio.h>                                          	// Allows console use input/output
 
#include <VarAndFuncs.h>                                         	// Imported .h and .c file for LCD
#include "ST7735.h"                                              	           // Imported .h and .c file for LCD
#include <LCDimages.h>                                      	// Hold LCD picture arrays
 
/********************************************************************************************************************/
/* STEP THE MOTOR:  */
/********************************************************************************************************************/
void speedoStep(){
	P7OUT |= BIT1;
	_delay_cycles(100000);                               	// Delay the second check to confirm debounce
	P7OUT &=~ BIT1;
}
/********************************************************************************************************************/
/* MOTOR DIRECTION:  */
/********************************************************************************************************************/
void speedoDIR_CW(){
	P7OUT &=~ BIT0;
}
/********************************************************************************************************************/
/* MOTOR DIRECTION:  */
/********************************************************************************************************************/
void speedoDIR_CCW(){
	P7OUT |= BIT0;
}
 
 
/********************************************************************************************************************/
/* MOTOR DIRECTION:  */
/********************************************************************************************************************/
void tachStep(){
	P7OUT |= BIT3;
	_delay_cycles(100000);                               	// Delay the second check to confirm debounce
	P7OUT &=~ BIT3;
}
/********************************************************************************************************************/
/* MOTOR DIRECTION:  */
/********************************************************************************************************************/
void tachDIR_CW(){
	P7OUT &=~ BIT2;
}
/********************************************************************************************************************/
/* MOTOR DIRECTION:  */
/********************************************************************************************************************/
void tachDIR_CCW(){
	P7OUT |= BIT2;
}
 
 
void accelerate(){
 
	while(!(P5IN & BIT1)){
    	speedoDIR_CW();
    	tachDIR_CW();
 
    	for(gear1 = 0; gear1 < 20; gear1++){
        	blinkerControl();
 
        	speedoStep();
      	  tachStep();
        	tachStep();
        	tachStep();
        	tachStep();
        	speedoStep();
        	tachStep();
        	tachStep();
        	tachStep();
        	tachStep();
        	speedoStep();
 
        	speedStepCount = speedStepCount + 3;
        	tachStepCount = tachStepCount + 8;
    	}
 
    	tachDIR_CCW();
    	for(gear1 = 0; gear1 < 20; gear1++){
        	blinkerControl();
 
        	tachStep();
        	tachStep();
        	tachStep();
        	tachStep();
        	tachStep();
        	tachStep();
        	tachStep();
        	tachStep();
 
        	tachStepCount = tachStepCount - 8;
 
    	}
 
    	tachDIR_CW();
    	for(gear2 = 0; gear2 < 28; gear2++){
        	blinkerControl();
 
        	speedoStep();
        	tachStep();
        	tachStep();
        	tachStep();
        	speedoStep();
        	tachStep();
        	tachStep();
        	tachStep();
        	speedoStep();
 
        	speedStepCount = speedStepCount + 3;
        	tachStepCount = tachStepCount + 6;
 
    	}
 
    	tachDIR_CCW();
    	for(gear2 = 0; gear2 < 28; gear2++){
        	blinkerControl();
 
        	tachStep();
      	  tachStep();
        	tachStep();
        	tachStep();
        	tachStep();
        	tachStep();
 
        	tachStepCount = tachStepCount - 6;
 
    	}
 
    	tachDIR_CW();
    	for(gear3 = 0; gear3 < 32; gear3++){
        	blinkerControl();
 
        	speedoStep();
        	tachStep();
        	tachStep();
        	speedoStep();
        	tachStep();
        	tachStep();
        	speedoStep();
 
        	speedStepCount = speedStepCount + 3;
        	tachStepCount = tachStepCount + 4;
 
    	}
 
    	tachDIR_CCW();
    	for(gear3 = 0; gear3 < 32; gear3++){
        	blinkerControl();
 
        	tachStep();
        	tachStep();
        	tachStep();
        	tachStep();
 
        	tachStepCount = tachStepCount - 4;
 
    	}
 
    	tachDIR_CW();
    	for(gear4 = 0; gear4 < 36; gear4++){
        	blinkerControl();
 
        	speedoStep();
        	tachStep();
        	speedoStep();
        	tachStep();
      	  speedoStep();
 
        	speedStepCount = speedStepCount + 3;
        	tachStepCount = tachStepCount + 2;
 
 
    	}
 
    	tachDIR_CCW();
    	for(gear4 = 0; gear4 < 36; gear4++){
        	blinkerControl();
 
        	tachStep();
   	     tachStep();
 
        	tachStepCount = tachStepCount - 2;
 
    	}
 
    	tachDIR_CW();
    	for(gear4 = 0; gear4 < 36; gear4++){
        	blinkerControl();
 
        	speedoStep();
        	tachStep();
        	speedoStep();
        	tachStep();
        	speedoStep();
 
        	speedStepCount = speedStepCount + 3;
        	tachStepCount = tachStepCount + 2;
 
 
    	}
 
    	tachDIR_CCW();
    	for(gear4 = 0; gear4 < 36; gear4++){
        	blinkerControl();
 
        	tachStep();
        	tachStep();
 
        	tachStepCount = tachStepCount - 2;
 
    	}
 
    	_delay_cycles(20000000);
 
    	speedoDIR_CCW();
    	for(stop = 0; stop <= speedStepCount;  stop++){
        	blinkerControl();
 
        	speedoStep();
    	}
    	speedStepCount = 0;
 
    	tachDIR_CCW();
    	for(stop = 0; stop <= tachStepCount;  stop++){
        	blinkerControl();
 
        	tachStep();
    	}
 
 
    	tachStepCount = 0;
 
	}
 
}
