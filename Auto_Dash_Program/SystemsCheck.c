/********************************************************************************************************************************
 *  Author:         Corey Moura
 *  Lab:            FINAL PROJECT
 *  Date:           Dec 8, 2019
 *  Class:          EGR 326
 *  Instructor:     Dr. Kandalaft
 *
 *  Description:    Used for debugging and to present a visual indication of system operations durring startup and priuor to
 *                  opperation.
 *
 *  Notes:          SystemsCheck.c.h
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
/* TOP SYSTEMS CHECK FUNCTION: Arranges and callout appealing system check sequence.*/
/********************************************************************************************************************/
void checkSystems(){
 
    LCDCheck();
 
    //runSevSeg();
 
    rtcCheck();
    musicCheck();
    LEDCheck();
 
    //    for(step = 0; step < 12; step++){
    //        speedoDIR_CW();
    //        speedoStep();
    //    }
 
    ultrasonicCheck();
    brakeOFF();
    soundOFF();
    Output_Clear();
 
    checkStepperFreq();
    Output_Clear();
 
    ST7735_DrawString(1, 9,"Diagnostics Complete", ST7735_GREEN);
 
}
 
void rtcCheck(){
    getData();
    toCharArray(binaryArr);                             // Converts binaryArr to newCharArray
    ST7735_DrawString(3, 12, newCharArray, ST7735_WHITE);
}
/********************************************************************************************************************/
/* LCD CHECK: Displays a test message to the screen.  */
/********************************************************************************************************************/
void LCDCheck(){
 
//    NVIC_DisableIRQ (SysTick_IRQn);         // Blinkers
//    NVIC_DisableIRQ (TA1_N_IRQn);           // Hall Effect
//    NVIC_DisableIRQ (TA2_N_IRQn);           // Ultrasonic
 
    //ST7735_DrawBitmap(1,160, one, 128, 128);
 
    Output_Clear();
    Delay1ms(2000);
 
    ST7735_FillScreen(1);
    Delay1ms(2000);
 
    ST7735_DrawString(1, 7,"Running Diagnostics", ST7735_GREEN);
 
}
 
/********************************************************************************************************************/
/* MUSIC CHECK: Occurs once per sytem startup.  Runs through the LEDs and Guages to ensure response of system to
 * input signals.  Used for visual appeal and debugging.  Additionally, this preps the guages and display for normal
 * opperation.  */
/********************************************************************************************************************/
void musicCheck(){
 
    /* OCTIVE 1 */
    noteC1();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteCSharp1();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteD1();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteDSharp1();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteE1();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteF1();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteFSharp1();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteG1();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteGSharp1();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteA1();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteASharp1();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteB1();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
 
    /* OCTIVE 2 */
    noteC2();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
 
    noteCSharp2();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteD2();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteDSharp2();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteE2();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteF2();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteFSharp2();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteG2();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteGSharp2();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteA2();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteASharp2();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteB2();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
 
    /* OCTIVE 3 */
    noteC3();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteCSharp3();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteD3();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteDSharp3();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteE3();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteF3();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteFSharp3();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteG3();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteGSharp3();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteA3();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteASharp3();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
    noteB3();
    _delay_cycles(MUSIC_CHECK_DELAY);
 
 
    TIMER_A0->CCR[0] = 0;
    TIMER_A0->CCR[2] = 0;
}
 
/********************************************************************************************************************/
/* LED CHECK: Occurs once per sytem startup.  Runs through the LEDs to ensure response of system to
 * input signals.  Used for visual appeal and debugging.  */
/********************************************************************************************************************/
void LEDCheck(){
 
//    NVIC_DisableIRQ (SysTick_IRQn);         // Blinkers
//    NVIC_DisableIRQ (TA1_N_IRQn);           // Hall Effect
//    NVIC_DisableIRQ (TA2_N_IRQn);           // Ultrasonic
 
    serviceON();
    _delay_cycles(SYSTEM_CHECK_DELAY);                                   // Delay the second check to confirm debounce
 
    LBlinkerON();
    _delay_cycles(SYSTEM_CHECK_DELAY);                                   // Delay the second check to confirm debounce
 
    RBlinkerON();
    _delay_cycles(SYSTEM_CHECK_DELAY);                                   // Delay the second check to confirm debounce
 
    brakeON();
    _delay_cycles(SYSTEM_CHECK_DELAY);                                   // Delay the second check to confirm debounce
 
    parkON();
    _delay_cycles(SYSTEM_CHECK_DELAY);                                   // Delay the second check to confirm debounce
 
    reverseON();
    _delay_cycles(SYSTEM_CHECK_DELAY);                                   // Delay the second check to confirm debounce
 
    driveON();
    _delay_cycles(SYSTEM_CHECK_DELAY);                                   // Delay the second check to confirm debounce
 
    fuelON();
    _delay_cycles(SYSTEM_CHECK_DELAY);                                   // Delay the second check to confirm debounce
 
    illumON();
    _delay_cycles(SYSTEM_CHECK_DELAY);                                   // Delay the second check to confirm debounce
 
 
    _delay_cycles(SYSTEM_CHECK_DELAY);                                   // Delay the second check to confirm debounce
    _delay_cycles(SYSTEM_CHECK_DELAY);                                   // Delay the second check to confirm debounce
 
 
    guageCheck();
 
 
    illumOFF();
    _delay_cycles(SYSTEM_CHECK_DELAY);                                   // Delay the second check to confirm debounce
 
    serviceOFF();
    _delay_cycles(SYSTEM_CHECK_DELAY);                                   // Delay the second check to confirm debounce
 
    LBlinkerOFF();
    _delay_cycles(SYSTEM_CHECK_DELAY);                                   // Delay the second check to confirm debounce
 
    RBlinkerOFF();
    _delay_cycles(SYSTEM_CHECK_DELAY);                                   // Delay the second check to confirm debounce
 
    brakeOFF();
    _delay_cycles(SYSTEM_CHECK_DELAY);                                   // Delay the second check to confirm debounce
 
    parkOFF();
    _delay_cycles(SYSTEM_CHECK_DELAY);                                   // Delay the second check to confirm debounce
 
    reverseOFF();
    _delay_cycles(SYSTEM_CHECK_DELAY);                                   // Delay the second check to confirm debounce
 
    driveOFF();
    _delay_cycles(SYSTEM_CHECK_DELAY);                                   // Delay the second check to confirm debounce
 
    fuelOFF();
    _delay_cycles(SYSTEM_CHECK_DELAY);                                   // Delay the second check to confirm debounce
 
    illumON();
 
}
 
/********************************************************************************************************************/
/* GUAGE CHECK: Runs speedomiter and tach through their line of motion. Zeros out the spedomiter.*/
/********************************************************************************************************************/
void guageCheck(){
//
//    NVIC_DisableIRQ (SysTick_IRQn);         // Blinkers
//    NVIC_DisableIRQ (TA1_N_IRQn);           // Hall Effect
//    NVIC_DisableIRQ (TA2_N_IRQn);           // Ultrasonic
 
    for(step = 0; step < 475; step++){
        speedoDIR_CW();
        tachDIR_CW();
        speedoStep();
        tachStep();
    }
 
    for(step = 0; step < 475; step++){
        speedoDIR_CCW();
        tachDIR_CCW();
        speedoStep();
        tachStep();
    }
}
 
/********************************************************************************************************************/
/* ULTRASONIC CHECK: Displays distance to the screen for 20 readings to ensure correct operation.  */
/********************************************************************************************************************/
void ultrasonicCheck(){
 
    NVIC_EnableIRQ (TA2_N_IRQn);            // Ultrasonic
//    NVIC_DisableIRQ (TA1_N_IRQn);           // Hall Effect
    //NVIC_DisableIRQ (SysTick_IRQn);         // Blinkers
 
    Output_Clear();
    ST7735_DrawString(4, 9,"Ultrasonic", ST7735_GREEN);
 
    while(sensorCheckCNT < 21){
 
        if(timeout){
            timeout = 0;                                        // Reset the flag
            triggerPulse();                                     // Send the trigger pulse
        }
 
        if(numSonicCapture == 2){
            numSonicCapture = 0;                                     // Reset the counter
            calcDistance();                                     // Calculate the distance
        }
    }
 
    sensorCheckCNT = 0;
}
 
/********************************************************************************************************************/
/* STEPPER FREQUENCY AND SPEEDOMITER CHECK: */
/********************************************************************************************************************/
void checkStepperFreq(){
 
    NVIC_DisableIRQ (TA2_N_IRQn);           // Ultrasonic
    NVIC_EnableIRQ (TA1_N_IRQn);           // Hall Effect
//    NVIC_DisableIRQ (SysTick_IRQn);         // Blinkers
 
    ST7735_DrawString(6, 6, "Speed Test", ST7735_GREEN);                          // Displays text in green
    ST7735_DrawString(7, 9, "RPM:", ST7735_GREEN);                          // Displays text in green
 
    stepperStartUp();
 
    ST7735_DrawString(7, 9, "          ", ST7735_GREEN);                          // Displays text in green
    ST7735_DrawString(6, 6, "Speed Test", ST7735_GREEN);                          // Displays text in green
 
 
 
}
 
/********************************************************************************************************************/
/* BUTTONS CHECK: Used only for debugging GPIO switch inputs and GPIO LED outputs.  Only 1 LED/Switch combo can be
 * "ON" at a time - Multiple LEDs will not be displayed singles only. */
/********************************************************************************************************************/
void buttonsCheck(){
    //NVIC_DisableIRQ (SysTick_IRQn);         // Blinkers
    //NVIC_DisableIRQ (TA1_N_IRQn);           // Hall Effect
    //NVIC_DisableIRQ (TA2_N_IRQn);           // Ultrasonic
 
    while(!(P5IN & BIT3))   LBlinkerON();
    while(!(P5IN & BIT4))   RBlinkerON();
    while(!(P5IN & BIT2))   serviceON();
    while(!(P5IN & BIT0))   fuelON();
    while(!(P4IN & BIT0))   parkON();
    while(!(P4IN & BIT1))   reverseON();
    while(!(P4IN & BIT2))   driveON();
 
    fuelOFF();
    serviceOFF();
    LBlinkerOFF();
    RBlinkerOFF();
    driveOFF();
    parkOFF();
    reverseOFF();
 
}
