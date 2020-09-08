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
#include "AD.h"
#include <stdio.h>
#include <IO_Ports.h>





/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/

#define FLOOR_BLACK_THRESHOLD 400
#define FLOOR_WHITE_THRESHOLD 300

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
    TRISDbits.TRISD4 = 0;
    TRISFbits.TRISF5 = 1;
    LATDbits.LATD4 = 0;
    
    return SUCCESS;
}

/**
 * Function: Tape_ReadFloorFL
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads floor tape sensors
 * @author Jornell Quiambao */
unsigned int Tape_ReadFloorFL(void) {
    return AD_ReadADPin(AD_PORTW5);
    //return PORTBbits.RB13;
}

/**
 * Function: Tape_ReadFloorFR
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads floor tape sensors
 * @author Jornell Quiambao */
unsigned int Tape_ReadFloorFR(void) {
    return AD_ReadADPin(AD_PORTW6);
    //return PORTBbits.RB12;
}

/**
 * Function: Tape_ReadFloorFC
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads floor tape sensors
 * @author Jornell Quiambao */
//unsigned int Tape_ReadFloorFC(void) {
//    return AD_ReadADPin(AD_PORTW7);
//    //return PORTBbits.RB15;
//}

/**
 * Function: Tape_ReadFloorB
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads floor tape sensors
 * @author Jornell Quiambao */
unsigned int Tape_ReadFloorB(void) {
    return AD_ReadADPin(AD_PORTW7);
    //return PORTBbits.RB14;
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
 * Function: Tape_ReadGunL
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads tape sensors for the guns
 * @author Jornell Quiambao */
unsigned int Tape_ReadGunL(void) {
    return AD_ReadADPin(AD_PORTW3);
    //return PORTBbits.RB11;
}

/**
 * Function: Tape_ReadGunR
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads tape sensors for the guns
 * @author Jornell Quiambao */
unsigned int Tape_ReadGunR(void) {
    return AD_ReadADPin(AD_PORTW4);
    //return PORTBbits.RB10;
}

unsigned int Tape_ReadFloor(void) {
    unsigned int ret1 = 0;
    unsigned int ret2 = 0;
    if (Tape_ReadFloorFL() > FLOOR_BLACK_THRESHOLD) {
        ret1 = 1;
    } else {
        ret2 = 0;
    }
    
    if (Tape_ReadFloorFR() > FLOOR_BLACK_THRESHOLD) {
        ret2 = 1;
    } else {
        ret2 = 0;
    }
    return (ret1 + (ret2 << 1));
}

// change the thresholds for the side mounted tape sensors 





void Gun_Setter(void) {
    LATDbits.LATD4 = 1;
}

void Gun_UnSetter(void) {
    LATDbits.LATD4 = 0;
}

unsigned int Gun_Flagger(void) {
    return PORTFbits.RF5;
}