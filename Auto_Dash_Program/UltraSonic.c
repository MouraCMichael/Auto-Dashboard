/********************************************************************************************************************************
 *  Author:         Corey Moura
 *  Lab:            FINAL PROJECT
 *  Date:           Dec 9, 2019
 *  Class:          EGR 326
 *  Instructor:     Dr. Kandalaft
 *
 *  Description:    UltraSonic functions
 *
 *  Notes:          UltraSonic.c
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
 
 
 
void runUltraSonic(){
 
    NVIC_EnableIRQ (SysTick_IRQn);         // Blinkers
    NVIC_EnableIRQ (TA2_N_IRQn);            // Ultrasonic
 
    systikInit();
 
    Output_Clear();
 
    while(!(P4IN & BIT1)){
 
        blinkerControl();
 
        if(timeout){
            timeout = 0;                                        // Reset the flag
            triggerPulse();                                     // Send the trigger pulse
        }
 
        if(numSonicCapture == 2){
            numSonicCapture = 0;                                     // Reset the counter
            calcDistance_2();                                     // Calculate the distance
        }
    }
}
 
 
void calcDistance_2(){
 
    numClkCycles = abs(ultraSonicCapture_1 - ultraSonicCapture_2);              // The absolute value of the two captures
    totalTime = 4.5 * pow(10,-8) * numClkCycles;                        // period of CLK cycle * number of CLK cycles
    distanceInMeters = (340 * totalTime) / 2;              // Speed of sound * total time / 2
    distanceInCm = distanceInMeters * 100;                          // Conversion from m->cm for displaying
 
    num++;
    totalDistance = totalDistance + distanceInCm;
 
    if(num == 250){
        warningChime = 1;
 
        avgDistance = totalDistance / num - 1;
        num = 0;
 
        Output_Clear();
        ST7735_DrawString(1, 8,"    Distance(cm)", ST7735_RED);
 
        ST7735_SetCursor(10, 10);                                                 // Sets cursor
        ST7735_SetTextColor(ST7735_WHITE);
 
        ST7735_OutUDec(avgDistance);                                           // Displays Dist int value
 
        totalDistance = 0;
 
        assignWarningChime();
 
    }
}
 
void assignWarningChime(){
 
    if(avgDistance <= 4){
        warningChime = 0;
        noteFSharp2();
        brakeON();
    }
 
    if(avgDistance <= 5) SysTick->LOAD = 2000;
    else if(avgDistance <= 6) SysTick->LOAD = 2000;
    else if(avgDistance <= 7) SysTick->LOAD = 2100;
    else if(avgDistance <= 8) SysTick->LOAD = 2200;
    else if(avgDistance <= 9) SysTick->LOAD = 2300;
    else if(avgDistance <= 10) SysTick->LOAD = 2400;
    else if(avgDistance <= 11) SysTick->LOAD = 2500;
    else if(avgDistance <= 12) SysTick->LOAD = 3000;
    else if(avgDistance <= 13) SysTick->LOAD = 3500;
    else if(avgDistance <= 14) SysTick->LOAD = 4000;
    else if(avgDistance <= 15) SysTick->LOAD = 4500;
    else if(avgDistance <= 16) SysTick->LOAD = 5500;
    else if(avgDistance <= 17) SysTick->LOAD = 7500;
    else if(avgDistance <= 18) SysTick->LOAD = 9000;
    else if(avgDistance <= 19) SysTick->LOAD = 10000;
    else if(avgDistance <= 20) SysTick->LOAD = 20000;
    else if(avgDistance <= 21) SysTick->LOAD = 30000;
    else if(avgDistance <= 22) SysTick->LOAD = 40000;
    else if(avgDistance <= 23) SysTick->LOAD = 50000;
    else if(avgDistance <= 24) SysTick->LOAD = 60000;
    else if(avgDistance <= 25) SysTick->LOAD = 70000;
 
//    if(avgDistance <= 5){
//        brakeON();
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();
//        brakeOFF();
//    }
//    else if(avgDistance <= 6){
//        brakeON();
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();
//        brakeOFF();
//    }
//    else if(avgDistance <= 7){
//        brakeON();
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();
//        brakeOFF();
//    }
//    else if(avgDistance <= 8){
//        brakeON();
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();
//        brakeOFF();
//    }
//    else if(avgDistance <= 9){
//        brakeON();
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();
//        brakeOFF();
//    }
//    else if(avgDistance <= 10){
//        brakeON();
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();
//        brakeOFF();
//    }
//    else if(avgDistance <= 11){
//        brakeON();
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();
//        brakeOFF();
//    }
//    else if(avgDistance <= 12){
//        brakeON();
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();
//        brakeOFF();
//    }
//    else if(avgDistance <= 13){
//        brakeON();
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();
//        brakeOFF();
//    }
//    else if(avgDistance <= 14){
//        brakeON();
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();
//        brakeOFF();
//    }
//    else if(avgDistance <= 15){
//        brakeON();
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();
//        brakeOFF();
//    }
//    else if(avgDistance <= 16){
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();    }
//    else if(avgDistance <= 17){
//        brakeON();
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();
//        brakeOFF();
//    }
//    else if(avgDistance <= 18){
//        brakeON();
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();
//        brakeOFF();
//    }
//    else if(avgDistance <= 19){
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();    }
//    else if(avgDistance <= 20){
//        brakeON();
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();
//        brakeOFF();
//    }
//    else if(avgDistance <= 21){
//        brakeON();
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();
//        brakeOFF();
//    }
//    else if(avgDistance <= 22){
//        brakeON();
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();
//        brakeOFF();
//    }
//    else if(avgDistance <= 23){
//        brakeON();
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();
//        brakeOFF();
//    }
//    else if(avgDistance <= 24){
//        brakeON();
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();
//        brakeOFF();
//    }
//    else if(avgDistance <= 25){
//        brakeON();
//        noteFSharp2();
//        _delay_cycles(TRYDELAY);
//        soundOFF();
//        brakeOFF();
//    }
 
}
 
 
 
 
/********************************************************************************************************************/
/*  CALCULATING THE DISTANCE:  Calculates the distance from the timer interrupt values.  The number of clock cycles
 *  between reads is calculated into a time value by finding the period of a clock cycle.  The time is multiplied by
 *  the speed of sound and divided by two to compensate for the travel time to and from the object   */
/********************************************************************************************************************/
void calcDistance(){
 
    numClkCycles = abs(ultraSonicCapture_1 - ultraSonicCapture_2);              // The absolute value of the two captures
    totalTime = 4.5 * pow(10,-8) * numClkCycles;                        // period of CLK cycle * number of CLK cycles
    distanceInMeters = (340 * totalTime) / 2;              // Speed of sound * total time / 2
    distanceInCm = distanceInMeters * 100;                          // Conversion from m->cm for displaying
 
    num++;
    totalDistance = totalDistance + distanceInCm;
 
    if(num == 250){
 
        avgDistance = totalDistance / num - 1;
        num = 0;
 
        Output_Clear();
        ST7735_DrawString(2, 5,"Testing Ultrasonic", ST7735_RED);
 
        ST7735_DrawString(1, 8,"    Distance(cm)", ST7735_RED);
 
        ST7735_SetCursor(10, 10);                                                 // Sets cursor
        ST7735_SetTextColor(ST7735_WHITE);
        ST7735_OutUDec(avgDistance);                                           // Displays Dist int value
 
        totalDistance = 0;
 
        sensorCheckCNT++;                                                       // Used for systemscheck
 
        assignWarningChime();
    }
 
}
 
 
/********************************************************************************************************************/
/*  TRIGGER PULSE: It is required to toggle the trigger pin of the Ultrasonic to initiate a reading   */
/********************************************************************************************************************/
void triggerPulse(){
    P5->OUT  |=  BIT5;                                              // Toggle bit ON
    _delay_cycles(200);
    P5->OUT  &=~  BIT5;                                             // Toggle bit OFF
}
 
/********************************************************************************************************************/
/*  TIMER A0.2 ISR: This is called whenever the timer object detects an input signal changes.      */
/********************************************************************************************************************/
void TA2_N_IRQHandler(void){
    TIMER_A2->CCTL[1] &=~ BIT0;                                     // Clear the interrupt flag
 
 
    ultraSonicCapture = TIMER_A2->CCR[1];                                  // Read the value of the captured TAxR number
 
    numSonicCapture++;                                                   // Track the begining and end of interval
 
    if(numSonicCapture == 1) ultraSonicCapture_1 = ultraSonicCapture;                 // Beginning of interval CCR val is assigned here
    if(numSonicCapture == 2) ultraSonicCapture_2 = ultraSonicCapture;                 // End of interval CCR val is assigned here
 
    TIMER_A2->CTL  =  0x02A0;
}
