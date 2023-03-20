/********************************************************************************************************************************
 *  Author:         Corey Moura & Xue Hue
 *  Lab:            FINAL PROJECT
 *  Date:           12/5/19
 *  Class:          EGR 326
 *  Instructor:     Dr. Kandalaft
 *
 *  Description:
 *
 *  Notes:          Initialize black tab for best results.
 *                      Pinout:
 *                          VCC     -   (Vcc)   3.3V
 *                          Ground  -   (GND)   0V
 *                          DC pin  -   (AO)    9.2
 *                          Reset   -   (RESET) 9.3
 *                          TFT_CS  -   (CS)    9.4
 *                          CLK     -   (SCK)   9.5
 *                          TDX     -   (SDA)   9.7
 *                          B.Light -   (LED)   3.3V
 *
 * Appendix D - Source Code
 * Source code can be seen below.  Contains 3 .h files and many .c files referenced from the main.c file.  The main.c file is the first .c file below.

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
 
volatile uint8_t systicLBlinkTog, systicRBlinkTog, exitFlag, toggleAllFlag, exitCount;
volatile uint8_t park, reverse, drive, WDT;
volatile uint8_t parkFlag, reverseFlag, driveFlag, WDTFlag = 1;
 
 
 int main(void){
 
    inititialize();
    checkSystems();
    //runSevSeg();
    //checkStepperFreq();
 
 
    Init_SysTick(15500000, 7);                                       // Systick initialization 16700000
 
    NVIC_DisableIRQ(TA1_N_IRQn);                                    // Button port enable interrupt
    NVIC_DisableIRQ(TA2_N_IRQn);                                    // Button port enable interrupt
 
    _delay_cycles(20000000);
 
    while(1){
 
        if(!(P4IN & BIT0)){
            parkFlag = 1;
            PARK();
        }
        if(!(P4IN & BIT1)){
            reverseFlag = 1;
            REVERSE();
        }
        if(!(P4IN & BIT2)){
            driveFlag = 1;
            DRIVE();
 
        }
        if(!(P3IN & BIT6)){
            WDTFlag = 1;
            WATCHDOGBYPASS();
        }
 
 
    }
}
 
 
void PARK(){
 
    while(!(P4IN & BIT0)){
        NVIC_EnableIRQ (PORT3_IRQn);                                    // Button port / RTC enable interrupt vector
        soundOFF();
 
        park = 1;
        reverse = 0;
        drive = 0;
        WDT = 0;
 
        driveSelectLED();
 
 
        if(parkFlag){
 
            SysTick->LOAD = 15500000;
 
            Output_Clear();
            ST7735_DrawString(1, 7,"    DRIVE SELECT:", ST7735_RED);
            ST7735_DrawString(1, 9,"        PARK",      ST7735_WHITE);
 
 
            getData();
            toCharArray(binaryArr);                             // Converts binaryArr to newCharArray
            ST7735_DrawString(3, 12, newCharArray, ST7735_WHITE);
 
            parkFlag = 0;
 
        }
 
        if(updateTimeFlag){
            getData();
            toCharArray(binaryArr);                             // Converts binaryArr to newCharArray
            ST7735_DrawString(3, 12, newCharArray, ST7735_WHITE);
 
            updateTimeFlag = 0;
        }
 
        blinkerControl();
 
        if(!(P5IN & BIT1)){
            Output_Clear();
            ST7735_DrawString(1, 6,"      CAUTION: ", ST7735_RED);
            ST7735_DrawString(1, 9,"    CAR MUST BE", ST7735_WHITE);
            ST7735_DrawString(1, 11,"     IN DRIVE",      ST7735_WHITE);
 
            _delay_cycles(200000000);
 
            parkFlag = 1;
        }
 
 
        if(!(P4IN & BIT3))  brakeON();
        else                brakeOFF();
 
 
    }
}
 
void REVERSE(){
 
    while(!(P4IN & BIT1)){
 
        NVIC_DisableIRQ (PORT3_IRQn);                                    // Button port / RTC enable interrupt vector
 
        reverse = 1;
        park = 0;
        drive = 0;
        WDT = 0;
 
        driveSelectLED();
 
 
        if(reverseFlag){
 
 
            SysTick->LOAD = 15500000;
 
            Output_Clear();
            ST7735_DrawString(1, 7,"    DRIVE SELECT:", ST7735_RED);
            ST7735_DrawString(1, 9,"      REVERSE",     ST7735_WHITE);
 
 
            reverseFlag = 0;
        }
 
 
        blinkerControl();
        runUltraSonic();
 
        reverse = 1;
 
        }
}
 
 
void DRIVE(){
 
    while(!(P4IN & BIT2)){
        soundOFF();
        NVIC_DisableIRQ (PORT3_IRQn);                                    // Button port / RTC enable interrupt vector
 
        drive = 1;
        park = 0;
        reverse = 0;
        WDT = 0;
 
        driveSelectLED();
 
        if(driveFlag){
 
 
            SysTick->LOAD = 15500000;
 
            Output_Clear();
            ST7735_DrawString(1, 7,"    DRIVE SELECT:", ST7735_RED);
            ST7735_DrawString(1, 9,"       DRIVE",     ST7735_WHITE);
 
            driveFlag = 0;
 
        }
 
//        if(updateTimeFlag){
//            getData();
//            toCharArray(binaryArr);                             // Converts binaryArr to newCharArray
//            ST7735_DrawString(3, 12, newCharArray, ST7735_WHITE);
//
//            updateTimeFlag = 0;
//        }
 
        blinkerControl();
 
 
 
        while(!(P5IN & BIT1)){
            blinkerControl();
            speedoDIR_CW();
            speedoStep();
            tachDIR_CW();
            tachStep();
        }
 
        while(!(P4IN & BIT3)){
            blinkerControl();
            brakeON();
            speedoDIR_CCW();
            speedoStep();
            tachDIR_CCW();
            tachStep();
 
        }
 
        if((P4IN & BIT3)) brakeOFF();
    }
 
}
 
void WATCHDOGBYPASS(){
 
    while(!(P3IN & BIT6)){
        soundOFF();
        NVIC_DisableIRQ (PORT3_IRQn);                                    // Button port / RTC enable interrupt vector
 
        if(drive){
            Output_Clear();
            ST7735_DrawString(1, 7,"  WATCHDOG BYPASS", ST7735_RED);
            ST7735_DrawString(1, 9,"   Contuinue for",     ST7735_WHITE);
            ST7735_DrawString(1, 11,"   soft reset",     ST7735_WHITE);
        }
 
        park = 0;
        reverse = 0;
        drive = 0;
 
        parkOFF();
        reverseOFF();
        driveOFF();
        watchdogControl();
 
    }
}
 
/********************************************************************************************************************/
/* SYSTICK INTERRUPT HANDLER:  This is called when the systick timer reaches zero from its load value, sets flag  */
/********************************************************************************************************************/
void SysTick_Handler(void){
    timeout = 1 ;                                                   // set flag for timeout of SysTick, rest in main
 
    if(!exitFlag){
        resetWDT();
    }
 
    if(systicLBlinkTog){
        LblinkDiv++;
    }
 
    if(systicRBlinkTog){
        RblinkDiv++;
    }
 
    if(warningChime){
        brakeON();
        noteFSharp2();
        _delay_cycles(MUSIC_CHECK_DELAY);
        soundOFF();
        warningChime = 0;
        brakeOFF();
 
    }
 
 
    P2->OUT ^= BIT1;                                              // Helps track entry into ISR
}
 
 
/********************************************************************************************************************/
/**/
/********************************************************************************************************************/
void watchdogControl(){
 
    exitFlag = 1;
    toggleAllFlag = 1;
 
    if(toggleAllFlag){
        LBlinkerOFF();
        RBlinkerOFF();
        serviceOFF();
        fuelOFF();
        parkOFF();
        reverseOFF();
        driveOFF();
        brakeOFF();
    }
 
    while(!(P3IN & BIT6)){
 
        LBlinkerTOG();
        RBlinkerTOG();
        serviceTOG();
        fuelTOG();
        parkTOG();
        reverseTOG();
        driveTOG();
        brakeTOG();
        _delay_cycles(20000000);
    }
 
    exitFlag = 0;
 
    if(P3IN & BIT6){
        LBlinkerOFF();
        RBlinkerOFF();
        serviceOFF();
        fuelOFF();
        parkOFF();
        reverseOFF();
        driveOFF();
        brakeOFF();
    }
}
 
 
/********************************************************************************************************************/
/**/
/********************************************************************************************************************/
void driveSelectLED(){
 
    if(park){
        parkON();
        reverseOFF();
        driveOFF();
    }
 
    if(reverse){
        parkOFF();
        reverseON();
        driveOFF();
    }
 
    if(drive){
        parkOFF();
        reverseOFF();
        driveON();
    }
 
}
 
/********************************************************************************************************************/
/**/
/********************************************************************************************************************/
void blinkerControl(){
 
    if(!(P5IN & BIT3)){
        systicLBlinkTog = 1;
    }
    else{
        LBlinkerOFF();
        systicLBlinkTog = 0;
    }
 
    if(LblinkDiv == 2){
        LBlinkerTOG();
        noteFSharp1();
        _delay_cycles(MUSIC_CHECK_DELAY);
        soundOFF();
        LblinkDiv = 0;
    }
 
 
    if(!(P5IN & BIT4)){
        systicRBlinkTog = 1;
    }
 
    else{
        RBlinkerOFF();
        systicRBlinkTog = 0;
    }
 
    if(RblinkDiv == 2){
        RBlinkerTOG();
        noteFSharp1();
        _delay_cycles(MUSIC_CHECK_DELAY);
        soundOFF();
        RblinkDiv = 0;
    }
}
 
 
/********************************************************************************************************************/
/* RESET THE WDT: Reset the timer to prevent timeout and soft system reset from occuring.  If not reset, the system
 * will reset every 4 seconds.  Data written to the WDT must be 16 bits or the system will generate a reset.
 * WDT is set to:
 *                      WDTIS       =   Watchdog clock source / 215 (1 s at 32.768 kHz)
 *                      WDTCNTCL    =   0000h
 *                      WDTTMSEL    =   Watchdog mode
 *                      WDTSSEL     =   ACLK
 *                      WDTHOLD     =   NotStopped
 *                      WDTPW       =   5A
 *                                                                                                      */
/********************************************************************************************************************/
void resetWDT(){
 
    WDT_A->CTL = 0x5A2C;              // Interval of 1 second with the ACLK:  ACLK -> REFOCLK with 4x divider
 
}
 
 
 
/********************************************************************************************************************/
/* PORT 3 ISR HANDLER: */
/********************************************************************************************************************/
void PORT3_IRQHandler(void){
    uint32_t status = P3->IFG;                                              // status holds the value of the flag
 
    if(status & BIT7){
 
        updateTimeFlag = 1;
 
        P3->IFG &=~ BIT7;                                               // Reset interrupt flag
    }
 
 
}
 
 
///********************************************************************************************************************/
///* PORT 5 ISR HANDLER: Handles the GPIO input buttons used to control the stepper motor.  */
///********************************************************************************************************************/
//void PORT5_IRQHandler(void){
//    uint32_t status = P5->IFG;                                          // status holds the value of the flag
//
//
//    if(status & BIT2){
//        serviceTOG();
//        P5->IFG &=~ BIT2;                                               // Reset interrupt flag
//    }
//
//    if(status & BIT0){
//        fuelTOG();                                                   // Set clockwise flag
//        P5->IFG &=~ BIT0;                                               // Reset interrupt flag
//    }
//
//}