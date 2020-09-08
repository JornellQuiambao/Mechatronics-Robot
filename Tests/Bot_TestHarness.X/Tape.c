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
    TRISGbits.TRISG8 = 1; // C = X9
    TRISDbits.TRISD7 = 1; // A = X10
    TRISDbits.TRISD4 = 1; // L = X11
    TRISDbits.TRISD6 = 1; // R = X12
    
    // gun sensor read
    TRISBbits.TRISB11 = 1; // M = W3
    TRISBbits.TRISB10 = 1; // L = W3
    TRISBbits.TRISB13 = 1; // R = W3
    
    // gun sensor enable
    TRISEbits.TRISE2 = 0; // M = Z7
    TRISDbits.TRISD8 = 0; // M = Z8
    TRISEbits.TRISE1 = 0; // M = Z9
    
    return SUCCESS;
}

/**
 * Function: Tape_ReadFloor
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads floor tape sensors
 * @author Jornell Quiambao */
unsigned int Tape_ReadFloor(void) {
    unsigned int tc = PORTGbits.RG8;
    unsigned int ta = PORTDbits.RD7;
    unsigned int tl = PORTDbits.RD4;
    unsigned int tr = PORTDbits.RD6;
    return (tc + (ta << 1) + (tl << 2) + (tr << 3));
}

/**
 * Function: Tape_EnableGun
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Enables tape sensors for the guns
 * @author Jornell Quiambao */
void Tape_EnableGun(void) {
    LATEbits.LATE2 = 1;
    LATDbits.LATD8 = 1;
    LATEbits.LATE1 = 1;
}


/**
 * Function: Tape_DisableGun
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Enables tape sensors for the guns
 * @author Jornell Quiambao */
void Tape_DisableGun(void) {
    LATEbits.LATE2 = 0;
    LATDbits.LATD8 = 0;
    LATEbits.LATE1 = 0;
}

/**
 * Function: Tape_ReadGun
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads tape sensors for the guns
 * @author Jornell Quiambao */
unsigned int Tape_ReadGun(void) {
    unsigned int m = PORTBbits.RB11;
    unsigned int l = PORTBbits.RB10;
    unsigned int r = PORTBbits.RB13;
    return (m + (l << 1) + (r << 2));
}