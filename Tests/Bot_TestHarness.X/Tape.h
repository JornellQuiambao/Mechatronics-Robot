/*
 * File:   Tape.h
 * Author: jquiamba
 * 
 * 
 * 
 * 
 */

#ifndef TAPE_H
#define TAPE_H

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#define TAPE_C 0x1
#define TAPE_A 0x2
#define TAPE_L 0x4
#define TAPE_R 0x8
#define TAPE_M_GUN 0x1
#define TAPE_L_GUN 0x2
#define TAPE_R_GUN 0x4

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/


/**
 * Function: Tape_Init
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Initializes pins used for tape sensors
 * @author Jornell Quiambao */
char Tape_Init(void);


#endif