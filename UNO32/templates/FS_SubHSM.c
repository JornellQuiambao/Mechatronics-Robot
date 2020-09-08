/*
 * File: FS_SubHSM.c
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
#include "FS_SubHSM.h"
#include "Motors.h"
#include <stdio.h>



/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define TIME_TILL_PARALLEL 2000 //2sec, Amount of time needed to spin bot parallel to side
#define TIME_TO_CHECK 1000 //Duration for checking Side, If expired, no TrackWire

#define TANK_TURN_SPEED 600 //Speed for Tank Turning Smoothly
#define TURN_SPEEDL 500 //Speed for constant motion around target, L Motor 
#define TURN_SPEEDR 800 //Speed for constant motion around target, R Motor 
#define STOP_SPEED 0  //Macro to stop motors 

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/


/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/

static uint8_t MyPriority;
typedef enum {
    INIT_STATE,
    PARALLEL_PARK,
    CHECK_SIDE,
    SWITCH_SIDE,
    SIDE_FOUND,
} FS_State_t;


static FS_State_t CurrentState = INIT_STATE; //Initialize static Variables
static ES_Event ThisEvent;
static uint8_t MyPriority;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitFS_SubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunFS_SubHSM function.
 *        Returns TRUE if successful, FALSE otherwise
* @author J. Edward Carryer, 2011.10.23 19:25 
* @editor Brian Naranjo, 11/13/19   */
uint8_t InitFS_SubHSM(uint8_t Priority){
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
 * @Function PostFS_SubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25
 * @editor Brian Naranjo, 11/13/19    */

uint8_t PostFS_SubHSM(ES_Event ThisEvent){
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunFS_SubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 
 * @editor Brian Naranjo, 11/13/19  */
ES_Event RunFS_SubHSM(ES_Event ThisEvent){
    uint8_t makeTransition = FALSE;
    FS_State_t NextState; //declare NextState Variable

    //ES_Tattle(); // trace call stack

    switch (CurrentState){      
        case INIT_STATE:
            if (ThisEvent.EventType == ES_INIT){// only respond to ES_Init
                NextState = PARALLEL_PARK; //Transition to First State
                ES_Timer_InitTimer(PARKING_TIMER, TIME_TILL_PARALLEL);
                makeTransition = TRUE; 
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                }
            break;

        case PARALLEL_PARK:
            if(ThisEvent.EventType == ES_TIMEOUT){ //If Parallel Park Done, Check Side
                NextState = CHECK_SIDE; //Next State
                ES_Timer_InitTimer(CHECK_TIMER, TIME_TO_CHECK);
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                Motors_LeftDrive(STOP_SPEED); //Set Both Motors to STOP
                Motors_RightDrive(STOP_SPEED);
            }
            Motors_TankTurn(TANK_TURN_SPEED, TANK_TURN_RIGHT);
            break;

        case CHECK_SIDE:
            if(ThisEvent.EventType == ES_TIMEOUT){
                NextState = SWITCH_SIDE; //Next State if Check Timer Expires
                makeTransition = TRUE; //Switch States
                ES_Timer_InitTimer(SS_TIMER, TIME_SWITCH_SIDE); //Time for bot to switch side
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }else if(ThisEvent.EventType == TRACKWIRE_TRIGGERED){
                NextState = SIDE_FOUND; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
            Motors_LeftDrive(STOP_SPEED); //Set Both Motors to STOP
            Motors_RightDrive(STOP_SPEED);
            break;    

        case SWITCH_SIDE:
            if(ThisEvent.EventType == ES_TIMEOUT){
                NextState = CHECK_SIDE; //Once Side is Switched, Check again
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            Motors_LeftDrive(TURN_SPEEDL); //Set Both Motors to Turn Left around target
            Motors_RightDrive(TURN_SPEEDR);
            break;    

        case SIDE_FOUND:
            if(ThisEvent.EventType == ES_Init){
                NextState = PARALLEL_PARK; //Transition back to First State In case Stuck
                ES_Timer_InitTimer(PARKING_TIMER, TIME_TILL_PARALLEL);
                makeTransition = TRUE; 
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
            Motors_LeftDrive(STOP_SPEED); //Set Both Motors to STOP
            Motors_RightDrive(STOP_SPEED);
            break;     

        
        if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
            // recursively call the current state with an exit event
            RunFS_SubHSM(EXIT_EVENT); // <- Exit SM
            CurrentState = NextState;   //Change States
            RunFS_SubHSM(ENTRY_EVENT); // <- Enter SM
        }
    }    
    //ES_Tail(); // trace call stack end
    return ThisEvent;
} 

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/