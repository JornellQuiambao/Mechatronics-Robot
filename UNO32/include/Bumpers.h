/*
 * File:   Bumpers.h
 * Author: jquiamba
 * 
 * 
 * 
 * 
 */

#ifndef BUMPER_H
#define BUMPER_H

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#define FL_BUMPER_HIT 0x1
#define FR_BUMPER_HIT 0x2


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Function: Bumpers_Init
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Initializes pins used for each bumper (FL=X3, FR=X4, RL=X5, RR=X6)
 * @author Jornell Quiambao */
char Bumpers_Init(void);

/**
 * Function: Bumpers_ReadFrontLeft
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads state of front left bumper
 * @author Jornell Quiambao */
unsigned int Bumpers_ReadFrontLeft(void);

/**
 * Function: Bumpers_ReadFrontRight
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads state of front right bumper
 * @author Jornell Quiambao */
unsigned int Bumpers_ReadFrontRight(void);



/**
 * Function: Bumpers_Read
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads state of all bumpers as a 4-bit number
 * 			(RR, RL, FR, FL) <-- LSB
 * @author Jornell Quiambao */
 unsigned int Bumpers_Read(void);

#endif