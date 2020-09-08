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

/**
 * Function: Tape_ReadFloorFL
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads floor tape sensors
 * @author Jornell Quiambao */
unsigned int Tape_ReadFloorFL(void);

/**
 * Function: Tape_ReadFloorFR
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads floor tape sensors
 * @author Jornell Quiambao */
unsigned int Tape_ReadFloorFR(void);

/**
 * Function: Tape_ReadFloorRL
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads floor tape sensors
 * @author Jornell Quiambao */
unsigned int Tape_ReadFloorRL(void);

/**
 * Function: Tape_ReadFloorRR
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads floor tape sensors
 * @author Jornell Quiambao */
unsigned int Tape_ReadFloorRR(void);

/**
 * Function: Tape_EnableGun
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Enables tape sensors for the guns
 * @author Jornell Quiambao */
void Tape_EnableGun(void);


/**
 * Function: Tape_DisableGun
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Enables tape sensors for the guns
 * @author Jornell Quiambao */
void Tape_DisableGun(void);

/**
 * Function: Tape_ReadGun1
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads tape sensors for the guns
 * @author Jornell Quiambao */
unsigned int Tape_ReadGun1(void);

/**
 * Function: Tape_ReadGun2
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Reads tape sensors for the guns
 * @author Jornell Quiambao */
unsigned int Tape_ReadGun1(void);

#endif