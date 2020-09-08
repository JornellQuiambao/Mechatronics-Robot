/*
 * File:   Tape.c
 * Author: jquiamba
 * 
 * 
 * 
 * 
 */

#include <xc.h>
#include <BOARD.h>
#include "Tape.h"
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
 * Function: Tape_Init
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Initializes pins used for tape sensors
 * @author Jornell Quiambao */
char Tape_Init(void) {
    // floor sensors
    TRISDbits.TRISD4 = 0; // X11, Enable
    TRISBbits.TRISB13 = 1; // W5, read FL
    TRISBbits.TRISB12 = 1; // W6, read FR
    TRISBbits.TRISB15 = 1; // W7, read RL
    TRISBbits.TRISB14 = 1; // W8, read RR
    LATDbits.LATD4 = 1; // turn sensors on

    // gun sensors
    TRISDbits.TRISD6 = 0; // X12, Enable
    TRISBbits.TRISB11 = 1; // W3, read gun 1
    TRISBbits.TRISB10 = 1; // W4, read gun 2
    
    return SUCCESS;
}

/**
 * Function: Tape_ReadFloorFL
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads floor tape sensors
 * @author Jornell Quiambao */
unsigned int Tape_ReadFloorFL(void) {
    return PORTBbits.RB13;
}

/**
 * Function: Tape_ReadFloorFR
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads floor tape sensors
 * @author Jornell Quiambao */
unsigned int Tape_ReadFloorFR(void) {
    return PORTBbits.RB12;
}

/**
 * Function: Tape_ReadFloorRL
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads floor tape sensors
 * @author Jornell Quiambao */
unsigned int Tape_ReadFloorFC(void) {
    return PORTBbits.RB15;
}

/**
 * Function: Tape_ReadFloorRR
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads floor tape sensors
 * @author Jornell Quiambao */
unsigned int Tape_ReadFloorB(void) {
    return PORTBbits.RB14;
}

/**
 * Function: Tape_EnableGun
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Enables tape sensors for the guns
 * @author Jornell Quiambao */
void Tape_EnableGun(void) {
    LATDbits.LATD6 = 1;
}


/**
 * Function: Tape_DisableGun
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Enables tape sensors for the guns
 * @author Jornell Quiambao */
void Tape_DisableGun(void) {
    LATDbits.LATD6 = 1;
}

/**
 * Function: Tape_ReadGun1
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads tape sensors for the guns
 * @author Jornell Quiambao */
unsigned int Tape_ReadGun1(void) {
    return PORTBbits.RB11;
}

/**
 * Function: Tape_ReadGun2
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads tape sensors for the guns
 * @author Jornell Quiambao */
unsigned int Tape_ReadGun1(void) {
    return PORTBbits.RB10;
}