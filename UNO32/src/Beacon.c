/*
 * File:   Beacon.c
 * Author: jquiamba
 * 
 * 
 * 
 * 
 */

#include <xc.h>
#include <BOARD.h>
#include "Beacon.h"
#include "AD.h"
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
 * Function: Beacon_Init
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Initializes pins used for beacon detector (Z11,12)
 * @author Jornell Quiambao */
char Beacon_Init(void){
//    TRISEbits.TRISE0 = 0; //Z11, ENABLE
//    TRISFbits.TRISF2 = 1; //Pin Z12, READ
//    AD_AddPins(AD_PORTW8);
	return SUCCESS;
}

/**
 * Function: Beacon_Enable
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Enables beacon detector
 * @author Jornell Quiambao */
void Beacon_Enable(void){
    LATEbits.LATE0 = 1;
}

/**
 * Function: Beacon_Disable
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Disable beacon detector
 * @author Jornell Quiambao */
void Beacon_Disble(void){
    LATEbits.LATE0 = 0;
}

/**
 * Function: Beacon_Read
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads beacon detector
 * @author Jornell Quiambao */
unsigned int Beacon_Read(void){
    //return PORTFbits.RF2;
    return AD_ReadADPin(AD_PORTW8);
}