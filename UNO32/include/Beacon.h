/*
 * File:   Beacon.h
 * Author: jquiamba
 * 
 * 
 * 
 * 
 */

#ifndef BEACON_H
#define BEACON_H

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/



/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/


/**
 * Function: Beacon_Init
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Initializes pins used for beacon detector (Z11,12)
 * @author Jornell Quiambao */
char Beacon_Init(void);

/**
 * Function: Beacon_Enable
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Enables beacon detector
 * @author Jornell Quiambao */
void Beacon_Enable(void);

/**
 * Function: Beacon_Disable
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Disable beacon detector
 * @author Jornell Quiambao */
void Beacon_Disble(void);

/**
 * Function: Beacon_Read
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads beacon detector
 * @author Jornell Quiambao */
unsigned int Beacon_Read(void);

#endif