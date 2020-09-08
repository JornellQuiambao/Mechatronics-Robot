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
#include "Trackwire.h"
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
 * Function: Trackwire_Init
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Initializes pins used for each trackwire (left = Z3,5, right = Z4,6)
 * @author Jornell Quiambao */
char Trackwire_Init(void){
	TRISEbits.TRISE4 = 0; // Z3
    TRISFbits.TRISF1 = 0; // Z4
    TRISEbits.TRISE3 = 1; // Z5
    TRISDbits.TRISD0 = 1; // Z6
	return SUCCESS;
}

/**
 * Function: Trackwire_enabaleLeft
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Enable left trackwire
 * @author Jornell Quiambao */
void Trackwire_enabaleLeft(void) {
    LATEbits.LATE4 = 1;
}

/**
 * Function: Trackwire_disableLeft
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Disable left trackwire
 * @author Jornell Quiambao */
void Trackwire_disableLeft(void) {
    LATEbits.LATE4 = 0;
}

/**
 * Function: Trackwire_enabaleRight
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Enable left trackwire
 * @author Jornell Quiambao */
void Trackwire_enabaleRight(void) {
    LATFbits.LATF1 = 1;
}

/**
 * Function: Trackwire_disableRight
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Disable left trackwire
 * @author Jornell Quiambao */
void Trackwire_disableRight(void) {
    LATFbits.LATF1 = 0;
}

/**
 * Function: Trackwire_ReadLeft
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads left trackwire
 * @author Jornell Quiambao */
unsigned int Trackwire_ReadLeft(void) {
    return  LATEbits.LATE3;
}

/**
 * Function: Trackwire_ReadRight
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads right trackwire
 * @author Jornell Quiambao */
unsigned int Trackwire_ReadRight(void) {
    return  LATDbits.LATD0;
}