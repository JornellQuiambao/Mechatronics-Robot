/*
 * File:   GunsMAIN.c
 * Author: jquiamba
 *
 * Created on November 20, 2019, 3:41 PM
 */


#include "xc.h"
#include <BOARD.h>
#include <stdio.h>
#include <AD.h>
#include <LED.h>
#include <Stepper.h>
#include <pwm.h>

#define RATE 7
#define STEPS 2

void delay(int ticks);

int main(void) {
    BOARD_Init();
    AD_Init();
    Stepper_Init();
    LED_Init();
    PWM_Init();
    
    TRISEbits.TRISE4 = 0; // Z3
    LATEbits.LATE4 = 1;
    
//    PWM_AddPins(PWM_PORTZ06);
//    
//    PWM_SetFrequency(MIN_PWM_FREQ);
//    PWM_SetDutyCycle(PWM_PORTZ06, 500);
//    PWM_SetDutyCycle(PWM_PORTY10, 500);
    
    
    
    Stepper_SetRate(RATE);
    Stepper_InitSteps(FORWARD, STEPS);
    
    while (1) {
        if (Stepper_GetRemainingSteps() == 0) {
            LATEbits.LATE4 = 0;
        }
    }
    
//    LATEbits.LATE4 = 0;
}

void delay(int ticks)
{
    int i = 0;
    while(i < ticks){
        i++;
    }
}