/********************************************************************************************************************************
 *  Author:         Corey Moura
 *  Lab:            FINAL PROJECT
 *  Date:           Dec 7, 2019
 *  Class:          EGR 326
 *  Instructor:     Dr. Kandalaft
 *
 *  Description:    Initializations
 *
 *  Notes:          Initializations.c
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
/* INITIALIZATIONS: Call out to the functions and initialize the pins and timers used in the program.  */
/********************************************************************************************************************/
void inititialize(){
 
//    NVIC_DisableIRQ (SysTick_IRQn);                                    // Button port enable interrupt
//    NVIC_DisableIRQ (TA1_N_IRQn);                                    // Button port enable interrupt
//    NVIC_DisableIRQ (TA2_N_IRQn);                                    // Button port enable interrupt
 
    /* STDBY Pin for motor Initialization */
    Init_InputPin(80,0,0,0,1,0,0,0);                                // STDBY pin pulldown
 
 
    /* CLOCKS  */
    Clock_Init48MHz();
    ACLK_Init();
 
    /* TIMERS  */
    timerA_Init();
    systikInit();
    WDT_A->CTL = 0x5A24;              // Interval of 1 second with the ACLK:  ACLK -> REFOCLK with 4x divider
 
 
    /* LCD  */
    ST7735_InitR(INITR_BLACKTAB);                                  // Black tab seems to grid out better
 
 
    /* OUTPUTS  */
    Init_OutputPin(20);                                             // ON board led red
    Init_OutputPin(21);                                             // ON board led green
 
    Init_OutputPin(23);                                             // Service LED
    Init_OutputPin(24);                                             // Fuel LED
    P2->DIR |= BIT5; P2SEL0 |= BIT5;  P2SEL1 &= ~BIT5;  P2OUT |= BIT5;   // PWM for Speaker
    Init_OutputPin(26);                                             // Reverse LED
    Init_OutputPin(27);                                             // Drive LED
 
    Init_OutputPin(30);                                             // Brake LED
    Init_OutputPin(32);                                             // Left Blinker LED
    Init_OutputPin(33);                                             // Right Blinker LED
    Init_OutputPin(35);                                             // Park LED
 
    Init_OutputPin(47);                                             // Illumination LEDs
 
    Init_OutputPin(55);                                             // Ultrasonic trigger pin
 
    Init_OutputPin(61);                                             // IN1 Silver Stepper
    Init_OutputPin(62);                                             // IN2
    Init_OutputPin(63);                                             // IN3
    Init_OutputPin(60);                                             // IN4
 
    Init_OutputPin(70);                                             // Speedo Direction
    Init_OutputPin(71);                                             // Speedo Step
    Init_OutputPin(72);                                             // Tach Direction
    Init_OutputPin(73);                                             // Tach Step
 
 
 
 
 
    /* INPUTS  */
    Init_InputPin(36,0,0,0,1,1,1,1);                                // Park switch input
    Init_InputPin(37,0,0,0,1,1,1,1);                                // Park switch input
 
    Init_InputPin(40,0,0,0,1,1,1,1);                                // Park switch input
    Init_InputPin(41,0,0,0,1,1,1,1);                                // Reverse switch input
    Init_InputPin(42,0,0,0,1,1,1,1);                                // Drive switch input
    Init_InputPin(43,0,0,0,1,1,1,1);                                // Brake switch input
 
    Init_InputPin(50,0,0,0,1,1,1,1);                                // Fuel switch input
    Init_InputPin(51,0,0,0,1,1,1,1);                                // Acceleration switch input
    Init_InputPin(52,0,0,0,1,1,1,1);                                // Service switch input
 
    Init_InputPin(53,0,0,0,1,1,1,1);                                // Left blinker switch input
    Init_InputPin(54,0,0,0,1,1,1,1);                                // Right blinker switch input
 
    Init_InputPin(56, 1, 0, 0, 0, 0, 0, 0);                         // Ultrasonic echo pin, capture/comp, TA2.1, input
 
 
 
 
    /* COMMUNICATION PROTICOLS */
    I2C1_init();
 
    /* DEFINE INTERRUPT SQW FROM RTC */
    unsigned char secondsInterrupt[]   = {1,0,0,0, 1,1,1,1};        // Alarm1 enable on seconds
    unsigned char interruptRegisters[] = {0,0,0,0, 0,1,0,1};        // Alarm interrupt enabled over SQW pin
 
    I2C1_burstWrite(SLAVE_ADDR, 7,   1, secondsInterrupt);          // (slave address, mem location, #bytes, data)
    I2C1_burstWrite(SLAVE_ADDR, 0xE, 1, interruptRegisters);        // (slave address, mem location, #bytes, data)
 
 
 
 
    /* STDBY Pin for motor Initialization */
    Init_InputPin(80,0,0,0,1,1,0,0);                                // STDBY pin pullup
 
    spi_init(); // Init USCI in SPI mode
 
 
    /* ENABLE PORT INTERRUPT VECTORS  */
    //NVIC_EnableIRQ (PORT5_IRQn);                                    // Button port enable interrupt
    NVIC_EnableIRQ (SysTick_IRQn);                                    // Button port enable interrupt
    NVIC_EnableIRQ (TA1_N_IRQn);                                    // Button port enable interrupt
    NVIC_EnableIRQ (TA2_N_IRQn);                                    // Button port enable interrupt
    NVIC_EnableIRQ (PORT3_IRQn);                                    // Button port / RTC enable interrupt vector
 
 
}
 
// Initial Setup
void spi_init(){
 
    P1->SEL0 |= SPI_SIMO|SPI_CLK; // Set port pins for USCI
    P1->SEL1 &= ~ SPI_SIMO|SPI_CLK;
    P1->SEL0 &= ~SPI_CS;            // set SPI_CS as GPIO
    P1->SEL1 &= ~SPI_CS;
    P1->OUT &= ~ SPI_CS;
    P1->DIR |= SPI_SIMO|SPI_CLK| SPI_CS;
 
 
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_SWRST; // Put eUSCI state machine in reset
    // Leading edge + MSB first + Master + Sync mode (spi)
    EUSCI_B0->CTLW0 = EUSCI_B_CTLW0_SWRST |
            EUSCI_B_CTLW0_CKPH|
            EUSCI_B_CTLW0_MSB|
            EUSCI_B_CTLW0_MST|
            EUSCI_B_CTLW0_SYNC;
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_SSEL__SMCLK; // ACLK
 
    EUSCI_B0->BRW = 0x01;                   // /2,fBitClock = fBRCLK/(UCBRx+1).
 
    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;// Initialize USCI state machine
}
 
 
/********************************************************************************************************************/
/* I2C INITIALIZATION: (Code gathered from open source Engineering 226 book) configureS UCB1 as I2C */
/********************************************************************************************************************/
void I2C1_init() {
 
    EUSCI_B1->CTLW0 |= 1;                                   // Disable UCB1 during config
    EUSCI_B1->CTLW0 = 0x0F81;                               // 7-bit slave addr, master, I2C, synch mode, use SMCLK
    EUSCI_B1->BRW = 40;                                     // Set clock prescaler 12MHz / 60 = 200kHz < 400KHz max
 
    P6->SEL0 |= 0x30;                                       // P6.5, P6.4 for UCB1
    P6->SEL1 &= ~0x30;                                      // P6.5, P6.4 for UCB1
 
    EUSCI_B1->CTLW0 &= ~1;                                  // Enable UCB1 after config
}
 
/********************************************************************************************************************/
/* CONFIGURE 48MHz CLOCK: Unlock timers and initialize the 48MHz clk as the MCLK. Clock Defaults to 3.3MHz  */
/********************************************************************************************************************/
void Clock_Init48MHz(void){
 
    /* Configure Flash wait-state to 1 for both banks 0 & 1 */
    FLCTL->BANK0_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK0_RDCTL_WAIT_MASK)) |
                          FLCTL_BANK0_RDCTL_WAIT_1;
 
    FLCTL->BANK1_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK0_RDCTL_WAIT_MASK)) |
                          FLCTL_BANK1_RDCTL_WAIT_1;
 
    /* Step 3: Configure HFXT to use 48MHz crystal, source to MCLK & HSMCLK*/
    PJ->SEL0 |= BIT2 | BIT3;                            // Configure PJ.2/3 for HFXT function
    PJ->SEL1 &= ~(BIT2 | BIT3);
 
    CS->KEY = CS_KEY_VAL ;                              // Unlock CS module for register access
 
    CS->CTL2 |= CS_CTL2_HFXT_EN | CS_CTL2_HFXTFREQ_6 | CS_CTL2_HFXTDRIVE;
 
    while(CS->IFG & CS_IFG_HFXTIFG) CS->CLRIFG |= CS_CLRIFG_CLR_HFXTIFG;
 
    /* Select MCLK & HSMCLK = HFXT, divide by 4 */
    CS->CTL1 = CS->CTL1 & ~(CS_CTL1_SELM_MASK     | CS_CTL1_DIVM_MASK   |
                            CS_CTL1_SELS_MASK     |  CS_CTL1_DIVHS_2)   |
                            CS_CTL1_SELM__HFXTCLK | CS_CTL1_SELS__HFXTCLK;
 
    CS->KEY = 0;                                        // Lock CS module from unintended accesses
 
}
 
/********************************************************************************************************************/
/* CONFIGURE SYSTIK TIMER:  Sets the systic to count down from 10000.  Additionally, 7 enables interrupts  */
/********************************************************************************************************************/
void systikInit(){
    Init_SysTick(10000, 7);                                       // Systick initialization 16700000
}
 
/********************************************************************************************************************/
/*  TIMER A INITIALIZATIONS:
 *        Timer AO.2 used as the input interrupt timer
 *        Timer A2.1 used as the ouptut timer for LED PWM                        */
/********************************************************************************************************************/
void timerA_Init(){
 
    /* PWM for Sound Generation */
    TIMER_A0->CCR[0] = 0;                           // PWM Period (# cycles of the clock)
    TIMER_A0->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7;     // Output mode, count up
    TIMER_A0->CCR[2] = 0;                           // CCR1 PWM duty cycle in 10ths of percent
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP | TIMER_A_CTL_CLR;
 
    /* UltraSonic Capture for Echo Pin */
    TIMER_A2->CTL  =  0x02A0;                       // SMCLK, interrupts disabled, continuous mode, no divider 0x0220;
    TIMER_A2->CCTL[1] = 0xCD78;                     // Intrpt en, set/rst, capture, sync, CCIxA signal, rising edge 0xCD78
 
    /* Hall Effect Capture  */
    TIMER_A1->CTL  =  0x0120;                       // ACLK 128kHz, interrupts disabled, continuous mode, no divider
    TIMER_A1->CCTL[2] = 0x8D78;                     // Intrpt en, set/rst, capture, sync, CCIxA signal, falling edge
    Init_InputPin(76, 1, 0, 0, 1, 1, 0, 0);                         // Hall effect Pin6.6, TA2.3, input
 
 
}
 
 
/********************************************************************************************************************/
/* CONFIGURE ACLK: Use the CSCTL1 register to adjust the source and divider of the ACLK.  Bit masking is preformed
 * placing values of 1 in each bank of the register we wish to change, then these values are bitwise ORd with the
 * desired values.
 *
 *                         xxxx xxxx xxxx xxxx xxxx xxxx xxxx       Dont know current values so we mask with 1s below
 *                         xxxx x111 xxxx xxxx x111 xxxx xxxx       Masked values are ORd with desired values
 *                         xxxx x010 xxxx xxxx x010 xxxx xxxx       Resulting values are now set        */
/********************************************************************************************************************/
void ACLK_Init(void){
 
    CS->KEY = CS_KEY_VAL ;                              // Unlock CS module for register access
 
    CS->CTL1 = CS->CTL1 &~ (CS_CTL1_SELA_MASK  | CS_CTL1_DIVA_MASK)  | CS_CTL1_DIVA_2 | CS_CTL1_SELA__REFOCLK;
 
    CS->KEY = 0;                                        // Lock CS module from unintended accesses
 
}
