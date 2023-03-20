/********************************************************************************************************************************
 *  Author:         Corey Moura
 *  Lab:            FINAL PROJECT
 *  Date:           Dec 9, 2019
 *  Class:          EGR 326
 *  Instructor:     Dr. Kandalaft
 *
 *  Description:    Hall effect functions
 *
 *  Notes:          HallEffect.c
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
 
const uint32_t speedDelay = 500;                               //
 
 
 
const uint32_t silverNumSteps  = 1000;                              // Determines # of steps taken by the stepper motor
uint32_t seqCount;
uint32_t minSpeed = 15000;
uint32_t decrement = 7;
uint32_t j;
uint32_t cnt;
 
volatile uint8_t tolerance = 50;                               // Determines the tolerance of the rpm val filter
 
 
 
 
void delay(uint32_t cycles){
     for(j = 0; j < cycles; j++);
}
 
 
/********************************************************************************************************************/
/* STEPPER ROTATION: Energizes and de-energizes the output pins controlling the stepper motor rotation.  The
 * sequence of the pins to the stepper motor determine the direction, while the delays between determine rotation
 * speed.  The sequence is half stepping as is specific to the device - Check TM of device for sequence.  */
/********************************************************************************************************************/
void stepperStartUp(){
 
    //NVIC_DisableIRQ (SysTick_IRQn);                                    // Button port enable interrupt
    NVIC_DisableIRQ (TA2_N_IRQn);                                    // Button port enable interrupt
 
    for(cnt = 0; cnt < silverNumSteps; cnt++){
 
 
        P6OUT |=  BIT0;                                              // Assigns pin 0001 0000 high
        P6OUT &=~ BIT3;
        P6OUT &=~ BIT2;
        P6OUT &=~ BIT1;
        delay(minSpeed - (seqCount * decrement));
 
        P6OUT |=  BIT0;                                              // Assigns pin 0001 0000 high
        P6OUT |=  BIT3;
        P6OUT &=~ BIT2;
        P6OUT &=~ BIT1;
        delay(minSpeed - (seqCount * decrement));
 
        P6OUT &=~ BIT0;                                              // Assigns pin 0001 0000 high
        P6OUT |=  BIT3;
        P6OUT &=~ BIT2;
        P6OUT &=~ BIT1;
        delay(minSpeed - (seqCount * decrement));
 
        P6OUT &=~ BIT0;                                              // Assigns pin 0001 0000 high
        P6OUT |=  BIT3;
        P6OUT |=  BIT2;
        P6OUT &=~ BIT1;
        delay(minSpeed - (seqCount * decrement));
 
        P6OUT &=~ BIT0;                                              // Assigns pin 0001 0000 high
        P6OUT &=~ BIT3;
        P6OUT |=  BIT2;
        P6OUT &=~ BIT1;
        delay(minSpeed - (seqCount * decrement));
 
        P6OUT &=~ BIT4;                                              // Assigns pin 0001 0000 high
        P6OUT &=~ BIT3;
        P6OUT |=  BIT2;
        P6OUT |=  BIT1;
        delay(minSpeed - (seqCount * decrement));
 
        P6OUT &=~ BIT0;                                              // Assigns pin 0001 0000 high
        P6OUT &=~ BIT3;
        P6OUT &=~ BIT2;
        P6OUT |=  BIT1;
        delay(minSpeed - (seqCount * decrement));
 
        P6OUT |=  BIT0;                                              // Assigns pin 0001 0000 high
        P6OUT &=~ BIT3;
        P6OUT &=~ BIT2;
        P6OUT |=  BIT1;
        delay(minSpeed - (seqCount * decrement));
 
        seqCount++;
    }
 
    for(cnt = 0; cnt < silverNumSteps; cnt++){
        P6OUT |=  BIT0;                                              // Assigns pin 0001 0000 high
        P6OUT &=~ BIT3;
        P6OUT &=~ BIT2;
        P6OUT &=~ BIT1;
        delay(minSpeed - (seqCount * decrement));
 
        P6OUT |=  BIT0;                                              // Assigns pin 0001 0000 high
        P6OUT |=  BIT3;
        P6OUT &=~ BIT2;
        P6OUT &=~ BIT1;
        delay(minSpeed - (seqCount * decrement));
 
        P6OUT &=~ BIT0;                                              // Assigns pin 0001 0000 high
        P6OUT |=  BIT3;
        P6OUT &=~ BIT2;
        P6OUT &=~ BIT1;
        delay(minSpeed - (seqCount * decrement));
 
        P6OUT &=~ BIT0;                                              // Assigns pin 0001 0000 high
        P6OUT |=  BIT3;
        P6OUT |=  BIT2;
        P6OUT &=~ BIT1;
        delay(minSpeed - (seqCount * decrement));
 
        P6OUT &=~ BIT0;                                              // Assigns pin 0001 0000 high
        P6OUT &=~ BIT3;
        P6OUT |=  BIT2;
        P6OUT &=~ BIT1;
        delay(minSpeed - (seqCount * decrement));
 
        P6OUT &=~ BIT0;                                              // Assigns pin 0001 0000 high
        P6OUT &=~ BIT3;
        P6OUT |=  BIT2;
        P6OUT |=  BIT1;
        delay(minSpeed - (seqCount * decrement));
 
        P6OUT &=~ BIT0;                                              // Assigns pin 0001 0000 high
        P6OUT &=~ BIT3;
        P6OUT &=~ BIT2;
        P6OUT |=  BIT1;
        delay(minSpeed - (seqCount * decrement));
 
        P6OUT |=  BIT0;                                              // Assigns pin 0001 0000 high
        P6OUT &=~ BIT3;
        P6OUT &=~ BIT2;
        P6OUT |=  BIT1;
        delay(minSpeed - (seqCount * decrement));
 
        seqCount--;
    }
 
 
    seqCount = 0;
 
}
 
/********************************************************************************************************************/
/* TIMER A2.2 ISR: This is called whenever the timer object detects an input signal from high to low.  Collects and
 * sets the values for each capture durring the rotation of the stepper.        */
/********************************************************************************************************************/
extern void TA1_N_IRQHandler(void){
 
    P2->OUT ^= BIT0;                                              // Helps track entry into ISR
 
    TIMER_A1->CCTL[2] &=~ BIT0;                                     // Clear the interrupt flag
 
    hallEffectcapture = TIMER_A1->CCR[2];                                  // Read the value of the captured TAxR count
 
    numCapture++;                                                   // Track the begining and end of interval
 
    if(numCapture == 1){
        hallEffectcapture_1 = hallEffectcapture;                                 // Beginning of interval CCR val is assigned here
    }
 
    if(numCapture == 2){
 
        hallEffectcapture_2 = hallEffectcapture;                                 // End of interval CCR val is assigned here
        TIMER_A1->CCTL[2] |= BIT2;                                  // TACLR - Timer_A clear before calculating
 
 
        numCapture = 0;                                             // Reset the counter
        calcRPM();
    }
}
/********************************************************************************************************************/
/* CALCULATING THE RPM:  Calculates the rpm based on the two collected capture values, and the timer used.  The
 * timer used is ACLK @ 16kHz, thus the period is used to determine time for a rotation.   */
/********************************************************************************************************************/
void calcRPM(){
 
    numClkCycles =  abs(hallEffectcapture_1 - hallEffectcapture_2);                     // The absolute value of the two captures
    rotationT    =  2 * pow(10,-4) * numClkCycles;                         // period of CLK cycle * number of CLK cycles
    newRPM          =  60 / rotationT;                                      // 60 seconds / seconds per rotation
 
 
    difference = abs(newRPM - oldRPM);
 
 
    /* Filter out the eronious values generated by the timer and captured values.
     * Increases the accuracy of the RPM and with low tolerance values we can update much quicker */
    if(difference <= tolerance || freqCounter == 0){
 
        freqCounter++;                                                          // New rotation has occured
 
        sumRpmValues = sumRpmValues + newRPM;                                   // Sum the values of rpm for the average
 
        oldRPM = newRPM;
 
        if(freqCounter == 4){
 
            uint32_t avgRPM = 0;                                                // New var to hold avgRPM
            avgRPM = sumRpmValues / 10;                                         // Calculating the avg
 
            displayRPM(avgRPM);                                                 // Send avg to be displayed
 
            freqCounter = 0;                                                    // Reset counter
            sumRpmValues = 0;                                                   // Reset sum of RPMs
 
        }
    }
}
 
 
/********************************************************************************************************************/
/* DISPLAY THE RPM:  Recieves the average rpm data and sends it to the LCD to be displayed.  Display updated ~ every
 * 20 samples.  */
/********************************************************************************************************************/
void displayRPM(uint32_t avgRPM){
 
    //Output_Clear();
    //ST7735_DrawString(2, 9, "RPM:", ST7735_GREEN);                          // Displays text in green
    ST7735_DrawString(13, 9, "   ", ST7735_GREEN);                          // Displays text in green
    ST7735_SetCursor(13, 9);                                                 // Sets cursor
    ST7735_OutUDec(avgRPM);                                                 // Displays RPM int value
 
}
 
 
/********************************************************************************************************************/
/* STEPPER ROTATION: Energizes and de-energizes the output pins controlling the stepper motor rotation.  The
 * sequence of the pins to the stepper motor determine the direction, while the delays between determine rotation
 * speed.  The sequence is half stepping as is specific to the device - Check TM of device for sequence.  */
/********************************************************************************************************************/
void stepper_clockwise(){
 
    for(i = 0; i< silverNumSteps; i++){
 
//        if(numCapture == 2) {
//            numCapture = 0;
//            calcRPM();                                                  // Calculate the RPM of the motor
//        }
 
        P6OUT |=  BIT4;                                              // Assigns pin 0001 0000 high
        P6OUT &=~ BIT3;
        P6OUT &=~ BIT2;
        P6OUT &=~ BIT1;
        Delay1ms(speedDelay);
 
        P6OUT |=  BIT4;                                              // Assigns pin 0001 0000 high
        P6OUT |=  BIT3;
        P6OUT &=~ BIT2;
        P6OUT &=~ BIT1;
        Delay1ms(speedDelay);
 
        P6OUT &=~ BIT4;                                              // Assigns pin 0001 0000 high
        P6OUT |=  BIT3;
        P6OUT &=~ BIT2;
        P6OUT &=~ BIT1;
        Delay1ms(speedDelay);
 
        P6OUT &=~ BIT4;                                              // Assigns pin 0001 0000 high
        P6OUT |=  BIT3;
        P6OUT |=  BIT2;
        P6OUT &=~ BIT1;
        Delay1ms(speedDelay);
 
        P6OUT &=~ BIT4;                                              // Assigns pin 0001 0000 high
        P6OUT &=~ BIT3;
        P6OUT |=  BIT2;
        P6OUT &=~ BIT1;
        Delay1ms(speedDelay);
 
        P6OUT &=~ BIT4;                                              // Assigns pin 0001 0000 high
        P6OUT &=~ BIT3;
        P6OUT |=  BIT2;
        P6OUT |=  BIT1;
        Delay1ms(speedDelay);
 
        P6OUT &=~ BIT4;                                              // Assigns pin 0001 0000 high
        P6OUT &=~ BIT3;
        P6OUT &=~ BIT2;
        P6OUT |=  BIT1;
        Delay1ms(speedDelay);
 
        P6OUT |=  BIT4;                                              // Assigns pin 0001 0000 high
        P6OUT &=~ BIT3;
        P6OUT &=~ BIT2;
        P6OUT |=  BIT1;
        Delay1ms(speedDelay);
 
    }
