/*
 * File:   Ping.h
 * Author: jquiamba
 * 
 * 
 * 
 * 
 */

#ifndef PING_H
#define PING_H

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/



/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Function: PING_Init
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Initializes pins used for the ping sensor
 * @author Jornell Quiambao */
char PING_Init(void);

/**
 * Function: Ping_Distance
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Returns distance read from the ping sensor
 * @author Jornell Quiambao */
unsigned int Ping_Distance(void);

unsigned int Ping_Distance2(void);


#endif