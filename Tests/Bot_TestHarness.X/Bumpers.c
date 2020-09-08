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
	TRISFbits.TRISF5 = 1; // X3
	TRISBbits.TRISB0 = 1; // X4
	TRISGbits.TRISG6 = 1; // X5
	TRISFbits.TRISF4 = 1; // X6
	return SUCCESS;
}

/**
 * Function: Bumpers_ReadFrontLeft
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads state of front left bumper
 * @author Jornell Quiambao */
unsigned int Bumpers_ReadFrontLeft(void){
	return PORTFbits.RF5;
}

/**
 * Function: Bumpers_ReadFrontRight
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads state of front right bumper
 * @author Jornell Quiambao */
unsigned int Bumpers_ReadFrontRight(void){
	return PORTBbits.RB0;
}

/**
 * Function: Bumpers_ReadRearLeft
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads state of rear left bumper
 * @author Jornell Quiambao */
unsigned int Bumpers_ReadRearLeft(void){
	return PORTGbits.RG6;
}

/**
 * Function: Bumpers_ReadRearRight
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads state of rear right bumper
 * @author Jornell Quiambao */
unsigned int Bumpers_ReadRearRight(void){
	return PORTFbits.RF4;
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
    unsigned int RL = Bumpers_ReadRearLeft();
    unsigned int RR = Bumpers_ReadRearRight();
    return (FL + (FR << 1) + (RL << 2) + (RR << 3));
 }