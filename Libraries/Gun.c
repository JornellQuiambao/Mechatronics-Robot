/*
 * File:   Gun.c
 * Author: jquiamba
 * 
 * 
 * 
 * 
 */

#include <xc.h>
#include <BOARD.h>
#include "Gun.h"
#include <stdio.h>
#include <IO_Ports.h>
#include <RC_Servo.h>




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
 * Function: Gun_Init
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Initializes pins used gun mechanisms
 * @author Jornell Quiambao */
char Gun_Init(void) {
    RC_AddPins();
    return SUCCESS;
}

