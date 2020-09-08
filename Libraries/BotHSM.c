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
#include "Motors.h"
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
#define APPROACH_SPEED 800 //Speed for constant motion towards target
#define STOP_SPEED 0  //Macro to stop motors
#define ONE_BALL 1000 //Time to shoot one ball

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
    DETECT_BEACON2,
    DETECT_BEACON3,
    APPROACH_TARGET,
    SMART_SEARCH,
    FIND_SIDE,
    // FIND_TAPE,
    SHOOT,
    STOP_BOT,
} BotState_t;


static BotState_t CurrentState = INIT_STATE; //Initialize static Variables
static ES_Event ThisEvent;
static uint8_t MyPriority;
static char BEACON1_TARGETED, BEACON2_TARGETED, BEACON3_TARGETED = FALSE;


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
uint8_t InitBotHSM(uint8_t Priority){
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

uint8_t PostBotHSM(ES_Event ThisEvent){
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
ES_Event RunBotHSM(ES_Event ThisEvent){
    uint8_t makeTransition = FALSE;
    BotState_t NextState; //declare NextState Variable

    //ES_Tattle(); // trace call stack

    switch (CurrentState){      
        case INIT_STATE:
            if (ThisEvent.EventType == ES_INIT){// only respond to ES_Init
                                        //Initialize SubHSMs

                NextState = DETECT_BEACON1; //Transition to First State
                makeTransition = TRUE; 
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                }
            break;

        case DETECT_BEACON1:
            if(ThisEvent.EventType == BEACON1_FOUND){
                NextState = APPROACH_TARGET; //Next State
                BEACON1_TARGETED = TRUE;
                BEACON2_TARGETED = FALSE;
                BEACON3_TARGETED = FALSE;
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
            break;

        case DETECT_BEACON2:
            if(ThisEvent.EventType == BEACON2_FOUND){
                NextState = APPROACH_TARGET; //Next State
                BEACON1_TARGETED = FALSE;
                BEACON2_TARGETED = TRUE;
                BEACON3_TARGETED = FALSE;
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
            break;    

        case DETECT_BEACON3:
            if(ThisEvent.EventType == BEACON3_FOUND){
                NextState = APPROACH_TARGET; //Next State
                BEACON1_TARGETED = FALSE;
                BEACON2_TARGETED = FALSE;
                BEACON3_TARGETED = TRUE;
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
            break;    

        case APPROACH_TARGET:
            if(ThisEvent.EventType == TAPE_TRIPPED){
                NextState = SMART_SEARCH; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }else if(ThisEvent.EventType == BEACON_CLOSE){
                NextState = FIND_SIDE; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
            Motors_LeftDrive(APPROACH_SPEED); //Set Both Motors to drive FWD
            Motors_RightDrive(APPROACH_SPEED);
            break;    

        case SMART_SEARCH:
            BotSmartSeachSubHSM(ThisEvent); //Avoid Tape and Redetect SAME Beacon
            if(ThisEvent.EventType == (BEACON1_FOUND)||(BEACON2_FOUND)||(BEACON3_FOUND)){
                NextState = APPROACH_TARGET; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }    
            break;
        case FIND_SIDE:
            BotFS_SubHSM(ThisEvent); //Sub HSM handling moving to each side
            if(ThisEvent.EventType == TRACKWIRE_TRIGGERED){
                // NextState = FIND_TAPE; //Next State
                NextState = SHOOT; //Next State
                makeTransition = TRUE; //Switch States
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }            
            break;

        // case FIND_TAPE:
        //     if(ThisEvent.EventType == TAPE_TRIPPED){
        //         Motors_LeftDrive(STOP_SPEED); //Set Both Motors to STOP
        //         Motors_RightDrive(STOP_SPEED);
        //         NextState = SHOOT;
        //         ES_Timer_InitTimer(SHOOT_TIMER, ONE_BALL); //Set Shooter Timer to allow only 1 ball
        //         makeTransition = TRUE; //Switch States
        //         ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
        //     }
        //     BotFindTapeSubHSM(ThisEvent); //Sub HSM handling tape finding
        //     break;

        case SHOOT:
            //Turn on Appropriate RC Servo
            RunShoot_SubHSM(ThisEvent); //Sub HSM handling correct shooting
            if(ThisEvent.EventType == ES_TIMEOUT){
                 if(BEACON1_TARGETED){
                    NextState = DETECT_BEACON2;
                    makeTransition = TRUE; //Switch States
                } else if(BEACON2_TARGETED){
                    NextState = DETECT_BEACON3;
                    makeTransition = TRUE; //Switch States
                } else if(BEACON3_TARGETED){
                     NextState = STOP_BOT;
                    makeTransition = TRUE; //Switch States
                } 
            }
            break;

        case STOP_BOT:
            Motors_LeftDrive(STOP_SPEED); //Set Both Motors to STOP
            Motors_RightDrive(STOP_SPEED);
            if (ThisEvent.EventType == ES_INIT){// Restart HSM on ES_INIT
                                        //Initialize SubHSMs

                NextState = DETECT_BEACON1; //Transition to First State
                makeTransition = TRUE; 
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
            break;
    }    
    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
    // recursively call the current state with an exit event
        RunBotHSM(EXIT_EVENT); // <- Exit SM
        CurrentState = NextState;   //Change States
        RunBotHSM(ENTRY_EVENT); // <- Enter SM
    }
    //ES_Tail(); // trace call stack end
    return ThisEvent;
}   

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/