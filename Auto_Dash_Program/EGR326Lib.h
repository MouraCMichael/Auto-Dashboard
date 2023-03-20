/********************************************************************************************************************
 *
 * Author: Corey Moura
 *
 * EGR326Lib.h
 *
 * Created on: Sep 13, 2019
 *
 ********************************************************************************************************************/
 
 
#ifndef INCLUDE_EGR326LIB_H_
#define INCLUDE_EGR326LIB_H_
 
void red_On();
void red_Off();
 
void blue_On();
void blue_Off();
 
 
/********************************************************************************************************************/
/* SYSTIC TIMER INITIALIZATION - First value is the count down from value. Second val = 7, interrupts enabled*/
/********************************************************************************************************************/
void Init_SysTick(int LOAD, int CTRL);
 
 
 
/********************************************************************************************************************/
/* OUTPUT PIN INITIALIZATION -
 *   Parameters:
 *      portPin -       Port and pin desired to be initialized EX. 3.4 = 34 */
/********************************************************************************************************************/
void Init_OutputPin(int portPin);
 
 
 
 
/********************************************************************************************************************/
/*     INPUT PIN INITIALIZATION -
 *       Parameters:
 *          1. portPin - Port and pin desired to be initialized EX. 3.4 = 34
 *          2. SEL0 -    Pin mode:            (GPIO = 00)     (TimerA = 10)
 *          3  SEL1 -    Pin mode:            (GPIO = 00)     (TimerA = 10)
 *          4. DIR -     Pin Direction:       (input = 0)     (ouput = 1)
 *          5. REN -     Internal resistor:   (disabled = 0)  (enabled = 1)
 *          6. OUT -     Internal resistor:   (pullD = 0)     (pullUp = 1)
 *          7. IE  -     Interrupt:           (disable = 0)   (enable = 1)
 *          8. IES -     Edge Select Register:(low->high transition = 0) (high->low transition = 1)*/
/********************************************************************************************************************/
void Init_InputPin(int portPin, int SEL0, int SEL1, int DIR, int REN, int OUT, int IE, int IES);
 
 
 
 
 
#endif /* INCLUDE_EGR326LIB_H_ */
