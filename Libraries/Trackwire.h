/*
 * File:   Trackwire.h
 * Author: jquiamba
 * 
 * 
 * 
 * 
 */

#ifndef TRACKWIRE_H
#define TRACKWIRE_H

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/



/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Function: Trackwire_Init
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Initializes pins used for each trackwire (left = W3, right = W4)
 * @author Jornell Quiambao */
char Trackwire_Init(void);

/**
 * Function: Trackwire_enabaleLeft
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Enable left trackwire
 * @author Jornell Quiambao */
void Trackwire_enabaleLeft(void);

/**
 * Function: Trackwire_disableLeft
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Disable left trackwire
 * @author Jornell Quiambao */
void Trackwire_disableLeft(void);

/**
 * Function: Trackwire_enabaleRight
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Enable left trackwire
 * @author Jornell Quiambao */
void Trackwire_enabaleRight(void);

/**
 * Function: Trackwire_disableRight
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Disable left trackwire
 * @author Jornell Quiambao */
void Trackwire_disableRight(void);

/**
 * Function: Trackwire_ReadLeft
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads left trackwire
 * @author Jornell Quiambao */
unsigned int Trackwire_ReadLeft(void);

/**
 * Function: Trackwire_ReadRight
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads right trackwire
 * @author Jornell Quiambao */
unsigned int Trackwire_ReadRight(void);

#endif