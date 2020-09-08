/*
 * File:   Bumpers.c
 * Author: jquiamba
 * 
 * 
 * 
 * 
 */

#include <xc.h>
#include <BOARD.h>
#include <Bumpers.h>
#include <stdio.h>
#include <IO_Ports.h>




/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/


/*******************************************************************************
 * PRIVATE VARIABLES                                                            *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * Function: Bumpers_Init
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Initializes pins used for each bumper(FL=X3, FR=X4, RL=X5, RR=X6)
 * @author Jornell Quiambao */
char Bumpers_Init(void){
    TRISDbits.TRISD11 = 1; // Y3, Front Left Read
    TRISDbits.TRISD5 = 1; // Y5, Front Right Read
	return SUCCESS;
}

/**
 * Function: Bumpers_ReadFrontLeft
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads state of front left bumper
 * @author Jornell Quiambao */
unsigned int Bumpers_ReadFrontLeft(void){
	unsigned int read = PORTDbits.RD11;
    return read;
}

/**
 * Function: Bumpers_ReadFrontRight
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads state of front right bumper
 * @author Jornell Quiambao */
unsigned int Bumpers_ReadFrontRight(void){
	unsigned int read = PORTDbits.RD5;
    return read;
}

/**
 * Function: Bumpers_Read
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads state of all bumpers as a 4-bit number
 * 			(RR, RL, FR, FL) <-- LSB
 * @author Jornell Quiambao */
 unsigned int Bumpers_Read(void){
    unsigned int FL = Bumpers_ReadFrontLeft();
    unsigned int FR = Bumpers_ReadFrontRight();
    return (!FL + (!FR << 1));
 }