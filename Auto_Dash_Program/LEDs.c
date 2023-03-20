/********************************************************************************************************************************
 *  Author:         Corey Moura
 *  Lab:            FINAL PROJECT
 *  Date:           Dec 9, 2019
 *  Class:          EGR 326
 *  Instructor:     Dr. Kandalaft
 *
 *  Description:    LED functions
 *
 *  Notes:          LEDs.c
 *******************************************************************************************************************************/
#include <EGR326Lib.h>                                          // Personal library
#include "driverlib.h"                                                          // Driverlib library
#include "msp.h"
 
#include "stdint.h"                                             // Intger lib
#include "string.h"                                                             // Allows the use of string functions
#include <stdbool.h>                                            // Allows Boolean logic
 
#include <math.h>                                               // MathLib used for the calculation of distance
#include <stdio.h>                                              // Allows console use input/output
 
#include <VarAndFuncs.h>                                             // Imported .h and .c file for LCD
#include "ST7735.h"                                                             // Imported .h and .c file for LCD
#include <LCDimages.h>                                          // Hold LCD picture arrays
 
 
/********************************************************************************************************************/
/* LED COMMANDS: Easy to reference functions for modifying the status of an LED. */
/********************************************************************************************************************/
void LBlinkerON()   {   P3->OUT  |=   BIT2;  }
void LBlinkerOFF()  {   P3->OUT  &=~  BIT2;  }
void LBlinkerTOG()  {   P3->OUT  ^=   BIT2;  }
 
void RBlinkerON()   {   P3->OUT  |=   BIT3;  }
void RBlinkerOFF()  {   P3->OUT  &=~  BIT3;  }
void RBlinkerTOG()  {   P3->OUT  ^=   BIT3;  }
 
void serviceON()    {   P2->OUT  |=   BIT3;  }
void serviceOFF()   {   P2->OUT  &=~  BIT3;  }
void serviceTOG()   {   P2->OUT  ^=   BIT3;  }
 
 
void fuelON()       {   P2->OUT  |=   BIT4;  }
void fuelOFF()      {   P2->OUT  &=~  BIT4;  }
void fuelTOG()      {   P2->OUT  ^=   BIT4;  }
 
void parkON()       {   P3->OUT  |=   BIT5;  }
void parkOFF()      {   P3->OUT  &=~  BIT5;  }
void parkTOG()      {   P3->OUT  ^=   BIT5;  }
 
void reverseON()    {   P2->OUT  |=   BIT6;  }
void reverseOFF()   {   P2->OUT  &=~  BIT6;  }
void reverseTOG()   {   P2->OUT  ^=   BIT6;  }
 
void driveON()      {   P2->OUT  |=   BIT7;  }
void driveOFF()     {   P2->OUT  &=~  BIT7;  }
void driveTOG()     {   P2->OUT  ^=   BIT7;  }
 
void illumON()      {   P4->OUT  |=   BIT7;  }
void illumOFF()     {   P4->OUT  &=~  BIT7;  }
void illumTOG()     {   P4->OUT  ^=   BIT7;  }
 
void brakeON()      {   P3->OUT  |=   BIT0;  }
void brakeOFF()     {   P3->OUT  &=~  BIT0;  }
void brakeTOG()     {   P3->OUT  ^=  BIT0;  }
