/*
 * File:   TestHarnessMain.c
 * Author: jquiamba
 *
 * Created on November 14, 2019, 2:08 PM
 */

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
#include "Motors.h"
#include "BOARD.h"
#include <xc.h>
#include "pwm.h"
#include "serial.h"
#include "IO_Ports.h"
#include "Bumpers.h"
#include "Tape.h"
#include <stdio.h>
#include "AD.h"

#define HALF_DUTY_CYCLE 500

void delay(int ticks);

int main(void) {
    BOARD_Init();   //Initialization Code
    PWM_Init();
    AD_Init();
    Motors_Init();
    Bumpers_Init();
    Tape_Init();
    AD_Init();
    AD_AddPins(AD_PORTV3);

    unsigned int read = 0;
    unsigned int read1 = 0;
    unsigned int read2 = 0;
    unsigned int read3 = 0;
    unsigned int read4 = 0;
    unsigned int read5 = 0;

//    Tape_EnableGun();
    
//    AD_AddPins(AD_PORTV3 | AD_PORTV4 | AD_PORTV5 | AD_PORTV6 | AD_PORTV7);
    
    
    
//    PWM_AddPins(PWM_PORTZ06); //Add PWM Pin Z06 for Motor A
//    TRISFbits.TRISF1 = 0; // ZO4
//    TRISEbits.TRISE4 = 0; // ZO3 
//    LATEbits.LATE4 = 1; 
//    LATFbits.LATF1 = 1;
//    PWM_SetDutyCycle(PWM_PORTZ06, HALF_DUTY_CYCLE);
    
//    PWM_AddPins(PWM_PORTY12); //Add PWM Pin Y12 for Motor B
//    
////    PWM_SetFrequency(PWM_5KHZ); //Set initial frequency 1kHz
//    
//    PWM_SetDutyCycle(PWM_PORTZ06,HALF_DUTY_CYCLE); //Set PWM signal 
//    PWM_SetDutyCycle(PWM_PORTY12,HALF_DUTY_CYCLE); //Set PWM signal 
    
    
    // Test Harness
    
    //temp = Motors_LeftDrive(speed); 
    while(1) {
        Motors_LeftDrive(900);
        Motors_LeftDirection(MOTOR_FORWARD);
        Motors_RightDrive(900);
        Motors_RightDirection(MOTOR_FORWARD);
        delay(2000000);
        Motors_Stop();
        delay(500000);
//        Motors_LeftDrive(900);
    //    Motors_LeftDirection(MOTOR_FORWARD);
//        Motors_RightDrive(900);
    //    Motors_RightDirection(MOTOR_FORWARD);
//        delay(1000000);
//        Motors_Stop();
//        delay(500000);
        Motors_LeftDrive(900);
        Motors_LeftDirection(MOTOR_REVERSE);
        Motors_RightDrive(900);
        Motors_RightDirection(MOTOR_REVERSE);
        delay(2000000);
//        Motors_Stop();
        
        
//        read = Bumpers_ReadFrontLeft();
//        read = Bumpers_Read();
        
//        if (Tape_ReadGun() > )
//        read = Tape_ReadGun();
//        read1 = AD_ReadADPin(AD_PORTV3);
//        read2 = AD_ReadADPin(AD_PORTV4);
//        read3 = AD_ReadADPin(AD_PORTV5);
//        read4 = AD_ReadADPin(AD_PORTV6);
//        read5 = AD_ReadADPin(AD_PORTV7);
//        printf("\r\ntape = %d, %d, %d, %d, %d", read1, read2, read3, read4, read5);
        
//        printf("\r\nBump: %d", read);
//        delay(100000);
        
        
    }
    
    return 0;
}

void delay(int ticks) {
    int i = 0;
    while(i < ticks) {
        i++;
    }
}