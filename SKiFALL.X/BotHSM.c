/*
 * File: BotHSM.c
 * Author: Brian Naranjo
 * Date: 11/13/19
 *
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "BOARD.h"
#include "AD.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BotHSM.h"
//#include "SmartSearch_SubHSM.h"
#include "FS_SubHSM.h"
#include "Shoot_SubHSM.h"
#include "Motors.h"
#include "Trackwire.h"
#include "Tape.h"
#include "IO_Ports.h"
#include "Stepper.h"
#include <stdio.h>

//Events to be defined:
//BEACON1_FOUND 
//BEACON2_FOUND
//BEACON3_FOUND
//BEACON_CLOSE
//TAPE_TRIPPED
//TRACKWIRE_TRIGGERED
//TAPE_TARGETED

//SubHSMs NEEDED:
//SMART SEARCH
//FIND SIDE
//SHOOT


/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
//Speeds
#define FAST_APPROACH_SPEED 1000 //Speed or Sharp Turn
#define APPROACH_SPEED 900 //Speed for constant motion towards target
#define STOP_SPEED 0  //Macro to stop motors
#define SEARCH_SPEED 700 //Speed for Searching for Beacon
#define BACKUP_SPEED 600
#define TURN_SPEED 700
#define SLOW_TURN_SPEED 400
#define SLOW_SPEED 500
#define SLOW_SPEED_BALL 350
#define MAX_SPEED 1000

//Time
#define ONE_BALL 1000 //Time to shoot one ball
#define BACK_TIMER 500
#define BACKTRACK_TIMER 250
#define FWD_TIMER 1000
#define ABIT_TIMER 1000
#define STALLER_TIME 250
#define SHOOT_STALLER_TIME 500
#define TURN_TIME 500
#define BUMP_TIME 150    // updated bumptime , previously 200 
#define BUMP_SPIN_TIME 600
#define BUMP_SPINOTHER_TIME 600
#define BUMP_SPIN_TIME2 500
#define TRACK_WAIT_TIME 700
#define TRACK_BACK_TIME 200
#define CORNER_TIME 2700
#define T_FOUND_STALL_TIME 800
#define STEP_TIME 20
#define THANOS_TIMER 1800
#define THANOS_TIMER2 1800
#define MOVE_STALL_TIME 300
#define ERROR_TIME 3000
#define TB_TIMER 150
#define ON_TIME 200

//Timers For New Traversal
#define X_TURN_TIME 2000

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/


/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/

static uint8_t MyPriority;

typedef enum {
    INIT_STATE,
    DETECT_BEACON1,
    STALL,
    TAPER,
    TAPER2,
    TAPER3,
    TAPEL,
    TAPEL2,
    TAPEL3,
    SWEEP_OTHER,
    DETECT_BEACON2,
    //DETECT_BEACON3,
    APPROACH_TARGET,
    BUMP_SIDE,
    BUMP_S_SPIN,
    BUMP_S_UP,
    BUMP_S_ALIGN,
    BUMP_S_BACK,
    BUMP_S_SPINOTHER,
    BUMP_S_SPINNER,
    BUMP_S_WAIT,
    //New States
    TRACK_S_SPIN,
    TRACK_S_SPINOTHER,
    TRACK_S_SPINNER,
    TRACK_WAIT,
    TRACK_CHECK,
    TRACK_UP,
    TRACK_FOUNDING,
    TRACK_TURN1,
    TRACK_SPIN,
    TRACK_BACK,
    TRACK_SPINOTHER,
    TRACK_SPINNER,
    //    HOLE_SWEEP,
    HOLE_SWEEP_ONE,
    HOLE_SWEEP_TWO,
    HOLE_FOUND,
    HOLE_BACK,
    HOLE_STALL,
    HOLE_BSTALL,
    SHOOT_START,
    SHOOT_END,
    SHOOT_START_TWO,
    SHOOT_END_TWO,
    SHOOT_ENDGAME,
    HOLE_STALLER1,
    HOLE_STALLER2,
    MISS_1,
    MISS_2,
    LEAVE_TARGET,
    TURN_FIRST,
    TURN_BACK,  
    STRAIGHT,
    QUICK_STOP,
    TRACK_BUMP,
    HOLE_MOLY,
    GET_ON_WALL,
    //SHOOT,
    //STOP_BOT,
} BotState_t;

static const char *StateNames[] = {
	"INIT_STATE",
	"DETECT_BEACON1",
	"STALL",
	"TAPER",
	"TAPER2",
	"TAPER3",
	"TAPEL",
	"TAPEL2",
	"TAPEL3",
	"SWEEP_OTHER",
	"DETECT_BEACON2",
	"APPROACH_TARGET",
	"BUMP_SIDE",
	"BUMP_S_SPIN",
	"BUMP_S_UP",
	"BUMP_S_ALIGN",
	"BUMP_S_BACK",
	"BUMP_S_SPINOTHER",
	"BUMP_S_SPINNER",
	"BUMP_S_WAIT",
	"TRACK_S_SPIN",
	"TRACK_S_SPINOTHER",
	"TRACK_S_SPINNER",
	"TRACK_WAIT",
	"TRACK_CHECK",
	"TRACK_UP",
	"TRACK_FOUNDING",
	"TRACK_TURN1",
	"TRACK_SPIN",
	"TRACK_BACK",
	"TRACK_SPINOTHER",
	"TRACK_SPINNER",
	"HOLE_SWEEP_ONE",
	"HOLE_SWEEP_TWO",
	"HOLE_FOUND",
	"HOLE_BACK",
	"HOLE_STALL",
	"HOLE_BSTALL",
	"SHOOT_START",
	"SHOOT_END",
	"SHOOT_START_TWO",
	"SHOOT_END_TWO",
	"SHOOT_ENDGAME",
	"HOLE_STALLER1",
	"HOLE_STALLER2",
	"MISS_1",
	"MISS_2",
	"LEAVE_TARGET",
	"TURN_FIRST",
	"TURN_BACK",
	"STRAIGHT",
	"QUICK_STOP",
	"TRACK_BUMP",
	"HOLE_MOLY",
	"GET_ON_WALL",
};



static BotState_t CurrentState = INIT_STATE; //Initialize static Variables
static ES_Event ThisEvent;
static uint8_t MyPriority;
//static char BEACON1_TARGETED, BEACON2_TARGETED, BEACON3_TARGETED = FALSE;
static uint8_t track_flag = 0;
static uint16_t counts = 0;
static uint8_t b_flag = 0;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitBotHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunBotHSM function.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 
 * @editor Brian Naranjo, 11/13/19   */
uint8_t InitBotHSM(uint8_t Priority) {
    MyPriority = Priority;
    CurrentState = INIT_STATE;

    ThisEvent.EventType = ES_INIT;

    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostBotHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25
 * @editor Brian Naranjo, 11/13/19    */

uint8_t PostBotHSM(ES_Event ThisEvent) {
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunBotHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 
 * @editor Brian Naranjo, 11/13/19  */
ES_Event RunBotHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE;
    BotState_t NextState; //declare NextState Variable

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case INIT_STATE:
            b_flag = 0;

            if (ThisEvent.EventType == ES_INIT) {// only respond to ES_Init
                NextState = DETECT_BEACON1; //Transition to First State
                //                NextState = APPROACH_TARGET;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                //                ES_Timer_InitTimer(HOLE_TIMER, STEP_TIME);
            }
            break;

            /**************************************************************************************************************************
             *                                                                                                      x_BEACON
             *************************************************************************************************************************/

        case DETECT_BEACON1:
            Motors_TankTurn(SEARCH_SPEED, TANK_TURN_LEFT);
            Gun_UnSetter();
            Trackwire_UnSetter();

            if (ThisEvent.EventType == BEACON_FOUND) {

                NextState = STALL; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                track_flag = 0;
                ES_Timer_InitTimer(TOP_TIMER, STALLER_TIME);
            }
            break;

        case DETECT_BEACON2:
            Motors_TankTurn(SEARCH_SPEED, TANK_TURN_RIGHT);
            Gun_UnSetter();
            Trackwire_UnSetter();

            if (ThisEvent.EventType == BEACON_FOUND) {

                NextState = STALL; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                track_flag = 0;
                ES_Timer_InitTimer(TOP_TIMER, STALLER_TIME);
            }
            break;

        case STALL:
            Motors_LeftDrive(STOP_SPEED);
            Motors_RightDrive(STOP_SPEED);
            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = APPROACH_TARGET;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

            /**************************************************************************************************************************
             *                                                                                                       x_TAPE
             *************************************************************************************************************************/

        case TAPEL:
            Motors_RightDirection(MOTOR_REVERSE);
            Motors_LeftDirection(MOTOR_REVERSE);
            Motors_LeftDrive(BACKUP_SPEED);
            Motors_RightDrive(BACKUP_SPEED);

            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = TAPEL2; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(TAPE_TIMER, TURN_TIME);
            } else

                break;

        case TAPEL2:
            Motors_TankTurn(TURN_SPEED, TANK_TURN_RIGHT);

            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = TAPEL3; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(TAPE_TIMER, FWD_TIMER);
            }
            break;

        case TAPEL3:
            Motors_RightDirection(MOTOR_FORWARD);
            Motors_LeftDirection(MOTOR_FORWARD);
            Motors_LeftDrive(BACKUP_SPEED);
            Motors_RightDrive(BACKUP_SPEED);

            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = DETECT_BEACON1; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
            //            else if (ThisEvent.EventType == ES_TIMEOUT) {
            //                NextState = DETECT_BEACON2; //Next State
            //                makeTransition = TRUE; //Switch States
            //                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            //            }
            break;

        case TAPER:
            Motors_RightDirection(MOTOR_REVERSE);
            Motors_LeftDirection(MOTOR_REVERSE);
            Motors_LeftDrive(BACKUP_SPEED);
            Motors_RightDrive(BACKUP_SPEED);

            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = TAPER2; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(TAPE_TIMER, TURN_TIME);
            }

            break;

        case TAPER2:
            Motors_TankTurn(TURN_SPEED, TANK_TURN_LEFT);

            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = TAPER3; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(TAPE_TIMER, FWD_TIMER);
            }
            break;

        case TAPER3:
            Motors_RightDirection(MOTOR_FORWARD);
            Motors_LeftDirection(MOTOR_FORWARD);
            Motors_LeftDrive(BACKUP_SPEED);
            Motors_RightDrive(BACKUP_SPEED);

            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = SWEEP_OTHER; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
            //            else if (ThisEvent.EventType == ES_TIMEOUT && b_flag) {
            //                NextState = DETECT_BEACON2; //Next State
            //                makeTransition = TRUE; //Switch States
            //                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            //            }
            break;

        case SWEEP_OTHER:
            Motors_TankTurn(SEARCH_SPEED, TANK_TURN_RIGHT);

            if (ThisEvent.EventType == BEACON_FOUND) {

                NextState = STALL; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(TOP_TIMER, STALLER_TIME);
            }
            break;

            break;

            /**************************************************************************************************************************
             *                                                                                                  x_APPROACH TARGET
             *************************************************************************************************************************/

        case APPROACH_TARGET:
            Motors_LeftDirection(MOTOR_FORWARD);
            Motors_RightDirection(MOTOR_FORWARD);
            Motors_LeftDrive(APPROACH_SPEED);
            Motors_RightDrive(APPROACH_SPEED);
            Trackwire_UnSetter();

            b_flag = 0;


            //            if ((ThisEvent.EventType == RIGHT_BUMP) || (ThisEvent.EventType == LEFT_BUMP)) {
            //                NextState = BUMP_SIDE; //Next State
            //                makeTransition = TRUE; //Switch States
            //                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            //                ES_Timer_InitTimer(BUMP_TIMER, BUMP_TIME);
            //            }

            if (ThisEvent.EventType == (BEACON_LOST)) {
                NextState = DETECT_BEACON1; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            } else if ((ThisEvent.EventType == RIGHT_BUMP) || (ThisEvent.EventType == LEFT_BUMP)) {
                NextState = BUMP_SIDE; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(BUMP_TIMER, BUMP_TIME);
            } else if (ThisEvent.EventType == TAPE_FR_TRIPPED) {
                NextState = TAPER; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(TAPE_TIMER, BACK_TIMER);
            } else if (ThisEvent.EventType == TAPE_FL_TRIPPED) {
                NextState = TAPEL; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(TAPE_TIMER, BACK_TIMER);
            }

            break;

            /**************************************************************************************************************************
             *                                                                                                        x_BUMPERS
             *************************************************************************************************************************/

            /*

    

             */
            /***********************************************************************************************/

            // PING  

        case BUMP_SIDE:
            Motors_RightDirection(MOTOR_REVERSE);
            Motors_LeftDirection(MOTOR_REVERSE);
            Motors_LeftDrive(BACKUP_SPEED);
            Motors_RightDrive(BACKUP_SPEED);
            Trackwire_UnSetter();

            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = BUMP_S_SPIN; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(BUMP_TIMER, BUMP_SPIN_TIME);
            }
            break;

        case BUMP_S_SPIN:
            Motors_TankTurn(SLOW_TURN_SPEED, TANK_TURN_RIGHT);

            if (ThisEvent.EventType == PING_RIGHT_OBJECT) {
                NextState = BUMP_S_SPINOTHER; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(BUMP_TIMER, BUMP_SPINOTHER_TIME);
            } else if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = BUMP_S_SPINOTHER; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(BUMP_TIMER, BUMP_SPINOTHER_TIME);
            }

            break;

        case BUMP_S_SPINOTHER:
            Motors_TankTurn(SLOW_TURN_SPEED, TANK_TURN_RIGHT);

            if (ThisEvent.EventType == PING_LEFT_OBJECT) {
                NextState = BUMP_S_SPINNER; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(BUMP_TIMER, BUMP_SPIN_TIME);
            } else if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = BUMP_S_SPINNER; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(BUMP_TIMER, BUMP_SPIN_TIME);
                //                Trackwire_Setter();                     //X_ADDED
            }
            break;

        case BUMP_S_SPINNER:
            Motors_TankTurn(SLOW_TURN_SPEED, TANK_TURN_LEFT);
            Trackwire_UnSetter();

            if (ThisEvent.EventType == PING_RIGHT_OBJECT) {
                NextState = TRACK_WAIT; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(TRACK_TIMER, TRACK_WAIT_TIME);
            } else if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = TRACK_WAIT; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(TRACK_TIMER, TRACK_WAIT_TIME);
            }
            break;


            /*************************************************** *******************************************************************/




            /**************************************************************************************************************************
             *                                                                                                        x_TRACKWIRE
             *************************************************************************************************************************/


            /***********************************************************************************************/

            // PING

        case TRACK_WAIT:
            Motors_LeftDrive(STOP_SPEED);
            Motors_RightDrive(STOP_SPEED);
            Trackwire_Setter();

            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = TRACK_UP; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(TRACK_TIMER, ERROR_TIME);
            } else if (ThisEvent.EventType == TRACKWIRE_TRIGGERED) {
                NextState = TRACK_FOUNDING; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }

            break;

        case TRACK_FOUNDING:

            Motors_LeftDrive(STOP_SPEED);
            Motors_RightDrive(STOP_SPEED);
            Trackwire_UnSetter();

            if (ThisEvent.EventType == ES_TIMEOUT) {
                Gun_Setter();
                NextState = GET_ON_WALL; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(TRACK_TIMER, ON_TIME);
            }

            break;

        case TRACK_UP:
            Motors_LeftDirection(MOTOR_FORWARD);
            Motors_RightDirection(MOTOR_FORWARD);
            Motors_LeftDrive(SLOW_SPEED);
            Motors_RightDrive(SLOW_SPEED);

            if (ThisEvent.EventType == TRACKWIRE_TRIGGERED) {
                NextState = TRACK_FOUNDING; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(TRACK_TIMER, T_FOUND_STALL_TIME);
            } else if (ThisEvent.EventType == HIGH_PING_CLEARED) {
                NextState = TRACK_TURN1; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(TRACK_TIMER, ERROR_TIME);
            } else if ((ThisEvent.EventType == RIGHT_BUMP) || (ThisEvent.EventType == LEFT_BUMP)) {
                NextState = TRACK_BUMP; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(BUMP_TIMER, TB_TIMER);
            } 
//            else if (ThisEvent.EventType == ES_TIMEOUT) {
//                NextState = DETECT_BEACON1; //Next State
//                makeTransition = TRUE; //Switch States
//                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
//            }
            break;
            
        case TRACK_BUMP:
            
            Motors_LeftDirection(MOTOR_FORWARD);
            Motors_RightDirection(MOTOR_REVERSE);
            Motors_LeftDrive(STOP_SPEED);
            Motors_RightDrive(TURN_SPEED);
            
            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = TRACK_UP; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
            
            break;

        case TRACK_TURN1:
            Motors_RightDirection(MOTOR_FORWARD);
            Motors_RightDirection(MOTOR_FORWARD);
            Motors_LeftDrive(STOP_SPEED);
            Motors_RightDrive(FAST_APPROACH_SPEED);

            if ((ThisEvent.EventType == RIGHT_BUMP) || (ThisEvent.EventType == LEFT_BUMP)) {
                //                NextState = TRACK_BACK; //Next State
                NextState = TRACK_BACK; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(TRACK_TIMER, TRACK_BACK_TIME);
            } else if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = DETECT_BEACON1; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }

            break;

        case TRACK_BACK:
            Motors_RightDirection(MOTOR_REVERSE);
            Motors_LeftDirection(MOTOR_REVERSE);
            Motors_LeftDrive(BACKUP_SPEED);
            Motors_RightDrive(BACKUP_SPEED);

            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = TRACK_SPIN; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(TRACK_TIMER, BUMP_SPIN_TIME);
            }

            break;

        case TRACK_SPIN:
            Motors_TankTurn(SLOW_TURN_SPEED, TANK_TURN_RIGHT);

            if (ThisEvent.EventType == PING_RIGHT_OBJECT) {
                NextState = TRACK_SPINOTHER; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(TRACK_TIMER, BUMP_SPINOTHER_TIME);

            } else if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = TRACK_SPINOTHER; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(TRACK_TIMER, BUMP_SPINOTHER_TIME);
            }

        case TRACK_SPINOTHER:
            Motors_TankTurn(SLOW_TURN_SPEED, TANK_TURN_RIGHT);

            if (ThisEvent.EventType == PING_LEFT_OBJECT) {
                NextState = BUMP_S_SPINNER; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            } else if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = TRACK_SPINNER; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(TRACK_TIMER, BUMP_SPIN_TIME);
            }
            break;

        case TRACK_SPINNER:
            Motors_TankTurn(SLOW_TURN_SPEED, TANK_TURN_LEFT);

            if (ThisEvent.EventType == PING_RIGHT_OBJECT) {
                NextState = TRACK_UP; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            } else if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = TRACK_UP; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
            break;





            /*************************************************** *******************************************************************/

            /**************************************************************************************************************************
             *                                                                                                        x_HOLE
             *************************************************************************************************************************/
            
        case GET_ON_WALL:
            Motors_LeftDirection(MOTOR_FORWARD);
            Motors_RightDirection(MOTOR_FORWARD);
            Motors_LeftDrive(SLOW_SPEED_BALL);
            Motors_RightDrive(SLOW_SPEED_BALL);
            
             if (ThisEvent.EventType == TAPE_GUN_MISSED) { // sweep once , full sweep 
                NextState = HOLE_SWEEP_ONE; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT;
                ES_Timer_InitTimer(HOLE_TIMER, STALLER_TIME);
            } else if ((ThisEvent.EventType == RIGHT_BUMP) || (ThisEvent.EventType == LEFT_BUMP)) {
                NextState = HOLE_MOLY; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(HOLE_TIMER, TB_TIMER);
            } else if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = HOLE_SWEEP_ONE; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT;
                ES_Timer_InitTimer(HOLE_TIMER, STALLER_TIME);
            }
            
            break;

        case HOLE_SWEEP_ONE:
            Motors_LeftDirection(MOTOR_FORWARD);
            Motors_RightDirection(MOTOR_FORWARD);
            Motors_LeftDrive(SLOW_SPEED_BALL);
            Motors_RightDrive(SLOW_SPEED_BALL);
            if (ThisEvent.EventType == TAPE_GUN_TARGETED) { // sweep once , full sweep 
                NextState = HOLE_FOUND; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT;
                ES_Timer_InitTimer(HOLE_TIMER, STALLER_TIME);
            } else if (ThisEvent.EventType == PING_LEFT_OBJECT) { // sweep once , full sweep 
                //                ES_Timer_InitTimer(HOLE_TIMER, BACKTRACK_TIMER);
                //            } else if (ThisEvent.EventType == HIGH_PING_CLEARED) { // sweep once , full sweep 
                NextState = HOLE_STALLER1; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT;
                ES_Timer_InitTimer(HOLE_TIMER, MOVE_STALL_TIME);
            } else if ((ThisEvent.EventType == RIGHT_BUMP) || (ThisEvent.EventType == LEFT_BUMP)) {
                NextState = HOLE_MOLY; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(HOLE_TIMER, TB_TIMER);
            } 
            break;

        case HOLE_SWEEP_TWO: // updated case , prev simply set to MOTOR FORWARD 

            // currently 2 scen possible   
            // current error is coming from the light sensor threshold, being targeted with light 
            Motors_LeftDirection(MOTOR_REVERSE);
            Motors_RightDirection(MOTOR_REVERSE);
            Motors_LeftDrive(SLOW_SPEED_BALL);
            Motors_RightDrive(SLOW_SPEED_BALL);
            if (ThisEvent.EventType == TAPE_GUN_TARGETED) { // sweep once , full sweep 
                NextState = HOLE_FOUND; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT;
                ES_Timer_InitTimer(HOLE_TIMER, STALLER_TIME);
            } else if (ThisEvent.EventType == PING_RIGHT_OBJECT) { // sweep once , full sweep
                //                 ES_Timer_InitTimer(HOLE_TIMER, BACKTRACK_TIMER);
                //            } else if (ThisEvent.EventType == HIGH_PING_CLEARED) { // sweep once , full sweep 
                NextState = HOLE_STALLER2; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT;
                ES_Timer_InitTimer(HOLE_TIMER, MOVE_STALL_TIME);
            }

            break;
            
        case HOLE_MOLY:
            
            Motors_LeftDirection(MOTOR_FORWARD);
            Motors_RightDirection(MOTOR_REVERSE);
            Motors_LeftDrive(STOP_SPEED);
            Motors_RightDrive(TURN_SPEED);
            
            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = HOLE_SWEEP_ONE; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
            
            break;

        case HOLE_STALLER1:
            Motors_LeftDirection(MOTOR_FORWARD);
            Motors_RightDirection(MOTOR_FORWARD);
            Motors_LeftDrive(SLOW_SPEED_BALL);
            Motors_RightDrive(SLOW_SPEED_BALL);
            

            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = HOLE_SWEEP_TWO; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT;
//                ES_Timer_InitTimer(TRACK_TIMER, ERROR_TIME);
            } else  if (ThisEvent.EventType == TAPE_GUN_TARGETED) { // sweep once , full sweep 
                NextState = HOLE_FOUND; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT;
                ES_Timer_InitTimer(HOLE_TIMER, STALLER_TIME);
            }

            break;

        case HOLE_STALLER2:
            Motors_LeftDirection(MOTOR_REVERSE);
            Motors_RightDirection(MOTOR_REVERSE);
            Motors_LeftDrive(SLOW_SPEED_BALL);
            Motors_RightDrive(SLOW_SPEED_BALL);

            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = HOLE_SWEEP_ONE; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT;
//                ES_Timer_InitTimer(TRACK_TIMER, ERROR_TIME);
            } else  if (ThisEvent.EventType == TAPE_GUN_TARGETED) { // sweep once , full sweep 
                NextState = HOLE_FOUND; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT;
                ES_Timer_InitTimer(HOLE_TIMER, STALLER_TIME);
            }

            break;


        case HOLE_STALL:
            Motors_LeftDrive(STOP_SPEED);
            Motors_RightDrive(STOP_SPEED);

            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = HOLE_BACK; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
            break;

        case HOLE_BACK:
            Motors_LeftDirection(MOTOR_REVERSE);
            Motors_RightDirection(MOTOR_REVERSE);
            Motors_LeftDrive(SLOW_SPEED);
            Motors_RightDrive(SLOW_SPEED);

            if (ThisEvent.EventType == TAPE_GUN_TARGETED) {
                NextState = HOLE_FOUND; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(HOLE_TIMER, STALLER_TIME);
            } else if (ThisEvent.EventType == HIGH_PING_CLEARED) {
                NextState = HOLE_BSTALL; //Switch States
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(HOLE_TIMER, STALLER_TIME);
            }
            break;

        case HOLE_BSTALL:
            Motors_LeftDrive(STOP_SPEED);
            Motors_RightDrive(STOP_SPEED);

            if (ThisEvent.EventType == ES_TIMEOUT) {
                //                NextState = HOLE_SWEEP; //Next State
                NextState = HOLE_SWEEP_ONE; //Next State

                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
            break;

        case HOLE_FOUND:
            Motors_LeftDrive(STOP_SPEED);
            Motors_RightDrive(STOP_SPEED);
            Gun_UnSetter();
            Trackwire_UnSetter();

            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = SHOOT_START; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT;
                ES_Timer_InitTimer(HOLE_TIMER, STEP_TIME);

                //                Stepper_InitSteps(1, 40);
            }
            break;

            /**************************************************************************************************************************
             *                                                                                                        x_SHOOT
             *************************************************************************************************************************/

        case SHOOT_START:
            LATEbits.LATE2 = 1; // enable stepper

            if (ThisEvent.EventType == ES_TIMEOUT) {
                counts++;
                NextState = SHOOT_END; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(HOLE_TIMER, SHOOT_STALLER_TIME);
                //                ES_Timer_InitTimer(HOLE_TIMER, STEP_TIME);
            }

            break;

        case SHOOT_END:
            LATEbits.LATE2 = 0; // disable stepper

            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = SHOOT_START_TWO; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(HOLE_TIMER, STEP_TIME);
            } else if (counts == 10) {
                counts = 0;
                NextState = SHOOT_ENDGAME; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(HOLE_TIMER, THANOS_TIMER);
            }
            break;

        case SHOOT_START_TWO:
            LATEbits.LATE2 = 1; // enable stepper

            if (ThisEvent.EventType == ES_TIMEOUT) {
                counts++;
                NextState = SHOOT_END_TWO; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(HOLE_TIMER, SHOOT_STALLER_TIME);
                //                ES_Timer_InitTimer(HOLE_TIMER, STEP_TIME);
            }

            break;

        case SHOOT_END_TWO:
            LATEbits.LATE2 = 0; // disable stepper

            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = SHOOT_START; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(HOLE_TIMER, STEP_TIME);
            } else if (counts == 10) {
                counts = 0;
                NextState = SHOOT_ENDGAME; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(HOLE_TIMER, THANOS_TIMER);
            }
            break;

        case SHOOT_ENDGAME:
            LATEbits.LATE2 = 0; // disable stepper
            Motors_LeftDrive(STOP_SPEED);
            Motors_RightDrive(STOP_SPEED);
            Gun_UnSetter();

            //            b_flag = 1;

            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = TURN_FIRST; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(HOLE_TIMER, THANOS_TIMER);
            }
            break;
            
        case TURN_FIRST:
            Motors_TankTurn(TURN_SPEED, TANK_TURN_RIGHT);

            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = TURN_BACK; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(HOLE_TIMER, THANOS_TIMER2);
            } else if (ThisEvent.EventType == BEACON_FOUND) {
                NextState = APPROACH_TARGET; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(TAPE_TIMER, BACK_TIMER);
            }
            break;

        case TURN_BACK:
            Motors_TankTurn(TURN_SPEED, TANK_TURN_LEFT);
            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = QUICK_STOP; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(HOLE_TIMER, TRACK_WAIT_TIME);
            } else if (ThisEvent.EventType == BEACON_FOUND) {
                //                NextState = TRACK_BACK; //Next State
                NextState = APPROACH_TARGET; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
            break;
            
        case QUICK_STOP:
            Motors_LeftDrive(STOP_SPEED);
            Motors_RightDrive(STOP_SPEED);
            
            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = STRAIGHT; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
            break;
            
        case STRAIGHT:
            Motors_RightDirection(MOTOR_FORWARD);
            Motors_LeftDirection(MOTOR_FORWARD);
            Motors_LeftDrive(SEARCH_SPEED);
            Motors_RightDrive(SEARCH_SPEED);
            
            if (ThisEvent.EventType == HIGH_PING_CLEARED) {
                //                NextState = TRACK_BACK; //Next State
                NextState = LEAVE_TARGET; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            } else if (ThisEvent.EventType == BEACON_FOUND) {
                //                NextState = TRACK_BACK; //Next State
                NextState = APPROACH_TARGET; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
            
            break;
            
        case LEAVE_TARGET:
            Motors_RightDirection(MOTOR_FORWARD);
            Motors_LeftDirection(MOTOR_FORWARD);
            Motors_LeftDrive(STOP_SPEED);
            Motors_RightDrive(FAST_APPROACH_SPEED);

            if (ThisEvent.EventType == BEACON_FOUND) {
                //                NextState = TRACK_BACK; //Next State
                NextState = APPROACH_TARGET; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            } else if ((ThisEvent.EventType == RIGHT_BUMP) || (ThisEvent.EventType == LEFT_BUMP)) {
                NextState = DETECT_BEACON2; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            } 
//            else if (ThisEvent.EventType == TAPE_FR_TRIPPED) {
//                NextState = TAPER; //Next State
//                makeTransition = TRUE; //Switch States
//                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
//                ES_Timer_InitTimer(TAPE_TIMER, BACK_TIMER);
//            } else if (ThisEvent.EventType == TAPE_FL_TRIPPED) {
//                NextState = TAPEL; //Next State
//                makeTransition = TRUE; //Switch States
//                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
//                ES_Timer_InitTimer(TAPE_TIMER, BACK_TIMER);
//            }
            break;
        default:
            break;

    }

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunBotHSM(EXIT_EVENT); // <- Exit SM
        CurrentState = NextState; //Change States
        RunBotHSM(ENTRY_EVENT); // <- Enter SM
    }
    ES_Tail(); // trace call stack end
    return ThisEvent;

}

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/