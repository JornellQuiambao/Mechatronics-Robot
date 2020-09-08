/*
 * File:   Motors.h
 * Author: jquiamba
 * 
 * 
 * 
 * 
 */

#ifndef MOTORS_H
#define MOTORS_H

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#define MOTOR_FORWARD 0
#define MOTOR_REVERSE 1
#define TANK_TURN_LEFT 0
#define TANK_TURN_RIGHT 1


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * Function: Motors_Init
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Initializes pins used for each motor (Right = Y12, Left = Y10)
 *          (Directions: Right = Y11, Left = Y9)
 * @author Jornell Quiambao */
char Motors_Init(void);

/**
 * Function: Motors_LeftDrive
 * @param None
 * @return SUCCESS or ERROR
 * @remark Sets motor speed from 0 to 1000.
 * @author Jornell Quiambao*/
char Motors_LeftDrive(unsigned int speed);

/**
 * Function: Motors_LeftDrive
 * @param None
 * @return SUCCESS or ERROR
 * @remark Sets motor speed from 0 to 1000.
 * @author Jornell Quiambao*/
char Motors_RightDrive(unsigned int speed);

/**
 * Function: Motors_LeftDirection
 * @param None
 * @return SUCCESS or ERROR
 * @remark Sets motor direction forward or reverse
 * @author Jornell Quiambao*/
char Motors_LeftDirection(unsigned int dir);

/**
 * Function: Motors_RightDirection
 * @param None
 * @return SUCCESS or ERROR
 * @remark Sets motor direction forward or reverse
 * @author Jornell Quiambao*/
char Motors_RightDirection(unsigned int dir);

/**
 * Function: Motors_TankTurn
 * @param None
 * @return SUCCESS or ERROR
 * @remark Set speed and direction for tank turn
 * @author Jornell Quiambao*/
char Motors_TankTurn(unsigned int speed, unsigned int dir);

/**
 * Function: Motors_Stop
 * @param None
 * @return SUCCESS or ERROR
 * @remark Stops motors
 * @author Jornell Quiambao*/
char Motors_Stop(void);


#endif
