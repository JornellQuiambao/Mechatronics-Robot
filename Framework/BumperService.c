/*
 * File: BumperService.c
 * Author: jquiamba
 *
 * 
 *
 * 
 */
 
/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "BOARD.h"
#include "AD.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include <stdio.h>
#include "Bumpers.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define FL_BUMPER 0x01
#define FR_BUMPER 0x02
#define RL_BUMPER 0x04
#define RR_BUMPER 0x08
#define BOUNCE_TICKS 5

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */
 
/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/
/* You will need MyPriority and maybe a state variable; you may need others
 * as well. */
 
static uint8_t MyPriority;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * Function: InitBumperService
 * @param None
 * @return TRUE or FALSE
 * @remark This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateService function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitBumperService(uint8_t Priority)
{
    ES_Event ThisEvent;
 
    MyPriority = Priority;
 
    // in here you write your initialization code
    // this includes all hardware and software initialization
    // that needs to occur.
 
    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    ES_Timer_InitTimer(BUMPER_TIMER, BOUNCE_TICKS);
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * Function: PostBumperService
 * @param None
 * @return TRUE or FALSE
 * @remark This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */

uint8_t PostBumperService(ES_Event ThisEvent)
{
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * Function: RunBumperService
 * @param None
 * @return TRUE or FALSE
 * @remark This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Remember to rename to something appropriate.
 *       Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 */
ES_Event RunBumperService(ES_Event ThisEvent)
{
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors
 
    /********************************************
     in here you write your service code
     *******************************************/
    static ES_EventTyp_t lastEvent = NO_BUMPER_HIT;
    static uint8_t fodder[4];
    static uint8_t fCount;
    ES_EventTyp_t curEvent;
    uint16_t bumper = Bumpers_Read()
 
    switch (ThisEvent.EventType) {
    case ES_INIT:
        // No hardware initialization or single time setups, those
        // go in the init function above.
        //
        // This section is used to reset service for some reason
        break;
         
    case ES_TIMERACTIVE:
    case ES_TIMERSTOPPED:
        break;
 
    case ES_TIMEOUT:
         
        if(fCount == 0) {
            fodder[0] = bumper;
            fCount++;
        } else if (fCount == 1) {
            fodder[1] = bumper;
            fCount++;
        } else if (fCount == 2) {
            fCount++;
            fodder[2] = bumper;
        } else if (fCount == 3) {
            fCount++;
            fodder[3] = bumper;
        } else {
            fCount = 0;
        }
         
        if (fodder[0] & fodder[1] & fodder[2] & fodder[3]) {
            if (bumper == FL_BUMPER && bumper != 0) {
                curEvent = FL_BUMPER_HIT;
            } else if (bumper == FR_BUMPER && bumper != 0) {
                curEvent = FR_BUMPER_HIT;
            } else if (bumper == RL_BUMPER && bumper != 0) {
                curEvent = RL_BUMPER_HIT;
            } else if (bumper == RR_BUMPER && bumper != 0) {
                curEvent = RR_BUMPER_HIT;
            } else if (bumper == 0){
                curEvent = NO_BUMPER_HIT;
            } else {
                curEvent = lastEvent;
            }
        } else if (bumper == 0) {
            curEvent = NO_BUMPER_HIT;
        }
        else {
            curEvent = lastEvent;
        }
         
        ES_Timer_InitTimer(BUMPER_TIMER, BOUNCE_TICKS);
        if (curEvent != lastEvent) { // check for change from last time
            ReturnEvent.EventType = curEvent;
            ReturnEvent.EventParam = bumper;
            lastEvent = curEvent; // update history
#ifndef SIMPLESERVICE_TEST           // keep this as is for test harness
            PostBotHSM(ReturnEvent);
#else
            PostBumperService(ReturnEvent);
#endif   
        }
        break;
#ifdef SIMPLESERVICE_TEST     // keep this as is for test harness      
    default:
        printf("\r\nEvent: %s\tParam: 0x%X",
                EventNames[ThisEvent.EventType], ThisEvent.EventParam);
        break;
#endif
    }
 
    return ReturnEvent;
}
 
/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/

























