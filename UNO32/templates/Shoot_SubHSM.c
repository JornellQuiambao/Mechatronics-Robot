/*
 * File: Shoot_SubHSM.c
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
#include "Shoot_SubHSM.h"
#include "Motors.h"
#include <stdio.h>



/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define TIME_TO_CHECK 1000 //Duration for checking Side, If expired, no TrackWire
#define TIME_TO_SHOOT 1000 //Time needed to shoot one ball


/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/


/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/

static uint8_t MyPriority;
typedef enum {
    INIT_STATE,
    CHECK_TAPE,
    SHOOT_BALLONE,
    SHOOT_BALLTWO,
    SHOOT_BALLTHREE,
    TARGET_HIT,
    ERROR,
} Shoot_State_t;


static Shoot_State_t CurrentState = INIT_STATE; //Initialize static Variables
static ES_Event ThisEvent;
static uint8_t MyPriority;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitShoot_SubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunShoot_SubHSM function.
 *        Returns TRUE if successful, FALSE otherwise
* @author J. Edward Carryer, 2011.10.23 19:25 
* @editor Brian Naranjo, 11/13/19   */
uint8_t InitShoot_SubHSM(uint8_t Priority){
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
 * @Function PostShoot_SubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25
 * @editor Brian Naranjo, 11/13/19    */

uint8_t PostShoot_SubHSM(ES_Event ThisEvent){
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunShoot_SubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 
 * @editor Brian Naranjo, 11/13/19  */
ES_Event RunShoot_SubHSM(ES_Event ThisEvent){
    uint8_t makeTransition = FALSE;
    FS_State_t NextState; //declare NextState Variable

    //ES_Tattle(); // trace call stack

    switch (CurrentState){      
        case INIT_STATE:
            if (ThisEvent.EventType == ES_INIT){// only respond to ES_Init
                NextState = CHECK_TAPE; //Transition to First State
                ES_Timer_InitTimer(CHECK_TIMER, TIME_TO_CHECK);
                makeTransition = TRUE; 
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                }
            break;

        case CHECK_TAPE:
            if(ThisEvent.EventType == ES_TIMEOUT){ //If CHECK_TAPE_EXPIRED, NO TAPE, ERROR
                NextState = ERROR; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            } else if(Tape_ReadGun() == LEFTGUN){
                ES_Timer_InitTimer(SHOOT_TIMER, TIME_TO_SHOOT);
                NextState = SHOOT_BALLONE; //Next State
                makeTransition = TRUE; //Switch States
            } else if(Tape_ReadGun() == CENTERGUN){
                ES_Timer_InitTimer(SHOOT_TIMER, TIME_TO_SHOOT);
                NextState = SHOOT_BALLTWO; //Next State
                makeTransition = TRUE; //Switch States
            } else if(Tape_ReadGun() == RIGHTGUN){
                ES_Timer_InitTimer(SHOOT_TIMER, TIME_TO_SHOOT);
                NextState = SHOOT_BALLTHREE; //Next State
                makeTransition = TRUE; //Switch States
            } else if(TAPE_READGUN() == TWO_OR_MORE_GUNS){
                NextState = ERROR; //Next State
                makeTransition = TRUE; //Switch States
            }
            break;

        case SHOOT_BALLONE:
            //Turn on RC SERVO 1
            if(ThisEvent.EventType == ES_TIMEOUT){
                NextState = TARGET_HIT;
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case SHOOT_BALLTWO:
            //Turn on RC SERVO 2
            if(ThisEvent.EventType == ES_TIMEOUT){
                NextState = TARGET_HIT;
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case SHOOT_BALLTHREE:
            //Turn on RC SERVO 3
            if(ThisEvent.EventType == ES_TIMEOUT){
                NextState = TARGET_HIT;
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case TARGET_HIT:
            //Turn off RC Servos
            if(ThisEvent.EventType == ES_INIT){
                NextState = CHECK_TAPE;
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;    

        if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
            // recursively call the current state with an exit event
            RunShoot_SubHSM(EXIT_EVENT); // <- Exit SM
            CurrentState = NextState;   //Change States
            RunShoot_SubHSM(ENTRY_EVENT); // <- Enter SM
        }
    }    
    //ES_Tail(); // trace call stack end
    return ThisEvent;
} 

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/