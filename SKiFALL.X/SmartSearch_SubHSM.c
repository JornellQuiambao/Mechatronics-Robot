/*
 * File: SmartSearch_SubHSM.c
 * Author: Brian Naranjo & jquiamba
 * Date: 11/15/19
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
#include "SmartSearch_SubHSM.h"
#include "Motors.h"
#include "Tape.h"
#include <stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

typedef enum {
    INIT_STATE,
    WAITING,
    AVOID_CENTER_TAPE,
    AVOID_LEFT_TAPE,
    AVOID_RIGHT_TAPE,
    SWEEP_LEFT,
    SWEEP_RIGHT,
    BACKUP1, BACKUP2, STOPPER1, STOPPER2, STALL,
    RUN_FOR_ABIT1,
    RUN_FOR_ABIT2,
    APPROACH_TOP_LEVEL,
} SmartSearch_State_t;

static const char *StateNames[] = {
	"INIT_STATE",
	"WAITING",
	"AVOID_CENTER_TAPE",
	"AVOID_LEFT_TAPE",
	"AVOID_RIGHT_TAPE",
	"SWEEP_LEFT",
	"SWEEP_RIGHT",
	"BACKUP1",
	"BACKUP2",
	"STOPPER1",
	"STOPPER2",
	"STALL",
	"RUN_FOR_ABIT1",
	"RUN_FOR_ABIT2",
	"APPROACH_TOP_LEVEL",
};

#define APPROACH_SPEED 600

#define TIME_STOP 500
#define TIME_AVOID_TAPE_SHORT 700
#define TIME_AVOID_TAPE_LONG 2500
#define TIME_RUN_A_BIT 1000
#define SWEEP_TIME_LIMIT 1500

#define AVOID_SPEED_SLOW 500
#define AVOID_SPEED_FAST 800
#define RUN_SPEED 600
#define STOP_SPEED 0
#define SWEEP_SPEED 500
#define BACK_SPEED 500


/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/


/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/

static SmartSearch_State_t CurrentState = INIT_STATE; //Initialize static Variables
//static ES_Event ThisEvent, returnEvent, InitEvent;
static uint8_t MyPriority;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitSmartSearch_SubHSM(void)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunSmartSearch_SubHSM function.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 
 * @editor Brian Naranjo, 11/15/19   */
uint8_t InitSmartSearch_SubHSM(void) {

    ES_Event returnEvent;
    CurrentState = INIT_STATE;
    //    InitEvent.EventType = ES_INIT;
    returnEvent = RunSmartSearch_SubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostSmartSearch_SubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25
 * @editor Brian Naranjo, 11/15/19    */

//uint8_t PostSmartSearch_SubHSM(ES_Event ThisEvent) {
//    return ES_PostToService(MyPriority, ThisEvent);
//}

/**
 * @Function RunSmartSearch_SubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 
 * @editor Brian Naranjo, 11/15/19  */
ES_Event RunSmartSearch_SubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE;
    SmartSearch_State_t NextState; //declare NextState Variable

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case INIT_STATE:

            if (ThisEvent.EventType == ES_INIT) {// only respond to ES_Init
                NextState = WAITING; //Transition to First State
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
            break;
        case WAITING:
            Motors_LeftDrive(APPROACH_SPEED); //Set Both Motors to drive FWD
            Motors_RightDrive(APPROACH_SPEED);
            Motors_LeftDirection(MOTOR_FORWARD);
            Motors_RightDirection(MOTOR_FORWARD);

            if (ThisEvent.EventType == TAPE_FL_TRIPPED) {
                NextState = STOPPER1;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_STOP); //Time Start for Avoid Short
            } else if (ThisEvent.EventType == TAPE_FR_TRIPPED) {
                NextState = STOPPER2;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_STOP); //Time Start for Avoid Short
            }
            break;
            //        case AVOID_CENTER_TAPE:
            //            Motors_TankTurn(AVOID_SPEED_FAST, TANK_TURN_LEFT); //Tank Turn 90 degrees
            //            if (ThisEvent.EventType == ES_TIMEOUT) {
            //                NextState = RUN_FOR_ABIT;
            //                makeTransition = TRUE;
            //                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            //                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_RUN_A_BIT); //Time Start for Running
            //            }
            //            break;
            
        case STALL:
            Motors_LeftDrive(STOP_SPEED);
            Motors_RightDrive(STOP_SPEED);
            if(ThisEvent.EventType == ES_TIMEOUT) {
                NextState = WAITING;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;
            
        case AVOID_LEFT_TAPE:
            //            Motors_LeftDrive(AVOID_SPEED_SLOW); //Set Both Motors to Turn Right
            //            Motors_RightDrive(AVOID_SPEED_FAST);
            Motors_TankTurn(APPROACH_SPEED, TANK_TURN_RIGHT);
            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = RUN_FOR_ABIT1;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_RUN_A_BIT);
                //                ES_Timer_InitTimer(SMARTSEARCH_TIMER, SWEEP_TIME_LIMIT); //Time Start for Sweep Limit
            } else if (ThisEvent.EventType == TAPE_FL_TRIPPED) {
                NextState = AVOID_LEFT_TAPE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_AVOID_TAPE_SHORT); //Time Start for Avoid Short
            } else if (ThisEvent.EventType == TAPE_FR_TRIPPED) {
                NextState = AVOID_RIGHT_TAPE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_AVOID_TAPE_SHORT); //Time Start for Avoid Short
            }
            break;

        case AVOID_RIGHT_TAPE:

            //            Motors_LeftDrive(AVOID_SPEED_FAST); //Set Both Motors to Turn Left
            //            Motors_RightDrive(AVOID_SPEED_SLOW);
            Motors_TankTurn(APPROACH_SPEED, TANK_TURN_LEFT);
            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = RUN_FOR_ABIT2;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_RUN_A_BIT);
                //                ES_Timer_InitTimer(SMARTSEARCH_TIMER, SWEEP_TIME_LIMIT); //Time Start for Sweep Limit
            } else if (ThisEvent.EventType == TAPE_FL_TRIPPED) {
                NextState = AVOID_LEFT_TAPE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_AVOID_TAPE_SHORT); //Time Start for Avoid Short
            } else if (ThisEvent.EventType == TAPE_FR_TRIPPED) {
                NextState = AVOID_RIGHT_TAPE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_AVOID_TAPE_SHORT); //Time Start for Avoid Short
            }
            break;

        case SWEEP_LEFT:
            Motors_TankTurn(SWEEP_SPEED, TANK_TURN_LEFT); //Sweep 180 Degrees Left
            if (ThisEvent.EventType == BEACON_FOUND) {
                NextState = STALL;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            } else if (ThisEvent.EventType == TAPE_FL_TRIPPED) {
                NextState = AVOID_LEFT_TAPE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_AVOID_TAPE_SHORT); //Time Start for Avoid Short
            } else if (ThisEvent.EventType == TAPE_FR_TRIPPED) {
                NextState = AVOID_RIGHT_TAPE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_AVOID_TAPE_SHORT); //Time Start for Avoid Short
            }
            //            if (ThisEvent.EventType == BEACON_FOUND){
            //                NextState = APPROACH_TOP_LEVEL;
            //                makeTransition = TRUE;
            //                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            //            }
            //
            break;

        case SWEEP_RIGHT:
            Motors_TankTurn(SWEEP_SPEED, TANK_TURN_RIGHT); //Sweep 180 Degrees Right
            if (ThisEvent.EventType == BEACON_FOUND) {
                NextState = STALL;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            } else if (ThisEvent.EventType == TAPE_FL_TRIPPED) {
                NextState = AVOID_LEFT_TAPE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_AVOID_TAPE_SHORT); //Time Start for Avoid Short
            } else if (ThisEvent.EventType == TAPE_FR_TRIPPED) {
                NextState = AVOID_RIGHT_TAPE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_AVOID_TAPE_SHORT); //Time Start for Avoid Short
            }

            //            if (ThisEvent.EventType == BEACON_FOUND){
            //                NextState = APPROACH_TOP_LEVEL;
            //                makeTransition = TRUE;
            //                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            //            }
            break;

        case RUN_FOR_ABIT1:
            Motors_LeftDrive(RUN_SPEED); //Set Both Motors to drive FWD a bit
            Motors_RightDrive(RUN_SPEED);
            Motors_LeftDirection(MOTOR_FORWARD);
            Motors_RightDirection(MOTOR_FORWARD);
            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = SWEEP_RIGHT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, SWEEP_TIME_LIMIT); //Time Start for Sweep Limit
            } else if (ThisEvent.EventType == TAPE_FL_TRIPPED) {
                NextState = AVOID_LEFT_TAPE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_AVOID_TAPE_SHORT); //Time Start for Avoid Short
            } else if (ThisEvent.EventType == TAPE_FR_TRIPPED) {
                NextState = AVOID_RIGHT_TAPE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_AVOID_TAPE_SHORT); //Time Start for Avoid Short
            }
            break;

        case RUN_FOR_ABIT2:
            Motors_LeftDrive(RUN_SPEED); //Set Both Motors to drive FWD a bit
            Motors_RightDrive(RUN_SPEED);
            Motors_LeftDirection(MOTOR_FORWARD);
            Motors_RightDirection(MOTOR_FORWARD);
            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = SWEEP_RIGHT;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, SWEEP_TIME_LIMIT); //Time Start for Sweep Limit
            } else if (ThisEvent.EventType == TAPE_FL_TRIPPED) {
                NextState = AVOID_LEFT_TAPE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_AVOID_TAPE_SHORT); //Time Start for Avoid Short
            } else if (ThisEvent.EventType == TAPE_FR_TRIPPED) {
                NextState = AVOID_RIGHT_TAPE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_AVOID_TAPE_SHORT); //Time Start for Avoid Short
            }
            break;

            //        case APPROACH_TOP_LEVEL:
            //            ThisEvent = RunBotHSM(ThisEvent);
            //            ThisEvent.EventType = BEACON_FOUND;
            //            break;

        case STOPPER1:
            Motors_LeftDrive(STOP_SPEED);
            Motors_RightDrive(STOP_SPEED);
            Motors_LeftDirection(MOTOR_FORWARD);
            Motors_RightDirection(MOTOR_FORWARD);
            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = BACKUP1;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_AVOID_TAPE_SHORT);
            }
            break;

        case BACKUP1:
            Motors_LeftDrive(BACK_SPEED);
            Motors_RightDrive(BACK_SPEED);
            Motors_LeftDirection(MOTOR_REVERSE);
            Motors_RightDirection(MOTOR_REVERSE);
            if (ThisEvent.EventType == ES_TIMEOUT) {
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_AVOID_TAPE_SHORT);
                NextState = AVOID_LEFT_TAPE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                //ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_AVOID_TAPE_SHORT);
            } else if (ThisEvent.EventType == TAPE_FL_TRIPPED) {
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_STOP); //Time Start for Avoid Short
                NextState = STOPPER1;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                //ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_STOP); //Time Start for Avoid Short
            } else if (ThisEvent.EventType == TAPE_FR_TRIPPED) {
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_STOP);
                NextState = STOPPER2;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                //ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_STOP); //Time Start for Avoid Short
            }
            break;

        case STOPPER2:
            Motors_LeftDrive(STOP_SPEED);
            Motors_RightDrive(STOP_SPEED);
            Motors_LeftDirection(MOTOR_FORWARD);
            Motors_RightDirection(MOTOR_FORWARD);
            if (ThisEvent.EventType == ES_TIMEOUT) {
                if (ThisEvent.EventParam == 1) {
                    NextState = BACKUP2;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                    ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_AVOID_TAPE_SHORT);
                }
            }
            break;

        case BACKUP2:
            Motors_LeftDrive(BACK_SPEED);
            Motors_RightDrive(BACK_SPEED);
            Motors_LeftDirection(MOTOR_REVERSE);
            Motors_RightDirection(MOTOR_REVERSE);
            if (ThisEvent.EventType == ES_TIMEOUT) {
                NextState = AVOID_RIGHT_TAPE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_AVOID_TAPE_SHORT);
            } else if (ThisEvent.EventType == TAPE_FL_TRIPPED) {
                NextState = STOPPER1;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_STOP); //Time Start for Avoid Short
            } else if (ThisEvent.EventType == TAPE_FR_TRIPPED) {
                NextState = STOPPER2;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(SMARTSEARCH_TIMER, TIME_STOP); //Time Start for Avoid Short
            }
            break;

        default:
            break;
    }
    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunSmartSearch_SubHSM(EXIT_EVENT); // <- Exit SM
        CurrentState = NextState; //Change States
        RunSmartSearch_SubHSM(ENTRY_EVENT); // <- Enter SM
    }
    ES_Tail(); // trace call stack end
    return ThisEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 *****************************************************************************/