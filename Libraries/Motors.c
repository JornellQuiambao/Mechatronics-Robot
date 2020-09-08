/*
 * File:   Motors.c
 * Author: jquiamba
 * 
 * 
 * 
 * 
 */

#include <xc.h>
#include <BOARD.h>
#include <Motors.h>
#include <stdio.h>
#include "pwm.h"
#include <IO_Ports.h>




/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/

#define RIGHT_MOTOR PWM_PORTY12
#define LEFT_MOTOR PWM_PORTY10
#define MOTOR_MAX_SPEED 1000
#define MOTOR_MIN_SPEED 0

/*******************************************************************************
 * PRIVATE VARIABLES                                                            *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * Function: Motors_Init
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Initializes pins used for each motor (Right = Y12, Left = Y10)
 *          (Directions: Right = Y11, Left = Y9)
 * @author Jornell Quiambao */
char Motors_Init(void){
    PWM_AddPins(RIGHT_MOTOR | LEFT_MOTOR);
    TRISEbits.TRISE6 = 0; // Y9
    TRISEbits.TRISE5 = 0; // Y11
    return SUCCESS;
}

/**
 * Function: Motors_LeftDrive
 * @param None
 * @return SUCCESS or ERROR
 * @remark Sets motor speed from 0 to 1000.
 * @author Jornell Quiambao*/
char Motors_LeftDrive(unsigned int speed){
    // Check max speed
    if ((speed > MOTOR_MAX_SPEED) || (speed < MOTOR_MIN_SPEED)) {
        return ERROR;
    }
    
    PWM_SetDutyCycle(LEFT_MOTOR, speed);
    return SUCCESS;
}

/**
 * Function: Motors_LeftDrive
 * @param None
 * @return SUCCESS or ERROR
 * @remark Sets motor speed from 0 to 1000.
 * @author Jornell Quiambao*/
char Motors_RightDrive(unsigned int speed){
    // Check max speed
    if ((speed > MOTOR_MAX_SPEED) || (speed < MOTOR_MIN_SPEED)) {
        return ERROR;
    }
    
    PWM_SetDutyCycle(RIGHT_MOTOR, speed);
    return SUCCESS;
}

/**
 * Function: Motors_LeftDirection
 * @param None
 * @return SUCCESS or ERROR
 * @remark Sets motor direction forward or reverse
 * @author Jornell Quiambao*/
char Motors_LeftDirection(unsigned int dir){
    if (dir == MOTOR_FORWARD) {
        LATEbits.LATE6 = 0;   
    } else if (dir == MOTOR_REVERSE) {
        LATEbits.LATE6 = 1;
    } else {
        return ERROR;
    }
}

/**
 * Function: Motors_RightDirection
 * @param None
 * @return SUCCESS or ERROR
 * @remark Sets motor direction forward or reverse
 * @author Jornell Quiambao*/
char Motors_RightDirection(unsigned int dir){
    if (dir == MOTOR_FORWARD) {
        LATEbits.LATE5 = 0;   
    } else if (dir == MOTOR_REVERSE) {
        LATEbits.LATE5 = 1;
    } else {
        return ERROR;
    }
}

/**
 * Function: Motors_TankTurn
 * @param None
 * @return SUCCESS or ERROR
 * @remark Set speed and direction for tank turn
 * @author Jornell Quiambao*/
char Motors_TankTurn(unsigned int speed, unsigned int dir) {
    if ((speed > MOTOR_MAX_SPEED) || (speed < MOTOR_MIN_SPEED)) {
        return ERROR;
    }
    
    if (dir == TANK_TURN_LEFT) {
        Motors_LeftDirection(MOTOR_REVERSE);
        Motors_LeftDrive(speed);
        Motors_RightDirection(MOTOR_FORWARD);
        Motors_RightDrive(speed);
    } else if (dir == TANK_TURN_RIGHT) {
        Motors_LeftDirection(MOTOR_FORWARD);
        Motors_LeftDrive(speed);
        Motors_RightDirection(MOTOR_REVERSE);
        Motors_RightDrive(speed);
    } else {
        return ERROR;
    }
    
    return SUCCESS;
}

/**
 * Function: Motors_Stop
 * @param None
 * @return SUCCESS or ERROR
 * @remark Stops motors
 * @author Jornell Quiambao*/
char Motors_Stop(void) {
    PWM_SetDutyCycle(RIGHT_MOTOR, 0);
    PWM_SetDutyCycle(LEFT_MOTOR, 0);
    return SUCCESS;
}