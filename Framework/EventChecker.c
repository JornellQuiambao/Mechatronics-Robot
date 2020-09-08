/*
 * File: EventChecker.c
 * Author: jquiamba
 *
 * 
 *
 * 
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/
 
#include "ES_Configure.h"
#include "EventChecker.h"
#include "ES_Events.h"
#include "serial.h"
#include "AD.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define BATTERY_DISCONNECT_THRESHOLD 175
#define FLOOR_WHITE_THRESHOLD
#define FLOOR_BLACK_THRESHOLD

//#define EVENTCHECKER_TEST
#ifdef EVENTCHECKER_TEST
#include <stdio.h>
#define SaveEvent(x) do {eventName=__func__; storedEvent=x;} while (0)
 
static const char *eventName;
static ES_Event storedEvent;
#endif

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this EventChecker. They should be functions
   relevant to the behavior of this particular event checker */
 
/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/
 
/* Any private module level variable that you might need for keeping track of
   events would be placed here. Private variables should be STATIC so that they
   are limited in scope to this module. */
 
/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * Function: CheckTapeFloor
 * @param None
 * @return TRUE or FALSE
 * @remark Checks for 
 * @author Jornell Quiambao */
uint8_t CheckTapeFloor(void) {
	static ES_EventTyp_t lastEvent = GONE_LIGHT;
    ES_EventTyp_t curEvent = GONE_LIGHT;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    static uint16_t last1 = 0;
    static uint16_t last2 = 0;
    static uint16_t last3 = 0;
    static uint16_t last4 = 0;
    uint16_t read1 = Tape_ReadFloorFL();
    uint16_t read2 = Tape_ReadFloorFR();
    uint16_t read3 = Tape_ReadFloorRL();
    uint16_t read4 = Tape_ReadFloorRR();
    static uint16_t param = 0;

    if ((read1 > FLOOR_BLACK_THRESHOLD) && (last1 < FLOOR_WHITE_THRESHOLD)) {
    	curEvent = ;
    	last1 = read1;
    	param = read1;
    } else if ((read1 < FLOOR_WHITE_THRESHOLD) && (last1 > FLOOR_BLACK_THRESHOLD)) {
    	curEvent = ;
    	last1 = read1;
    	param = read1;
    } else if ((read2 > FLOOR_BLACK_THRESHOLD) && (last2 < FLOOR_WHITE_THRESHOLD)) {
    	curEvent = ;
    	last2 = read2;
    	param = read1;
    } else if ((read2 < FLOOR_WHITE_THRESHOLD) && (last2 > FLOOR_BLACK_THRESHOLD)) {
    	curEvent = ;
    	last2 = read2;
    	param = read1;
    } else if ((read3 > FLOOR_BLACK_THRESHOLD) && (last3 < FLOOR_WHITE_THRESHOLD)) {
    	curEvent = ;
    	last3 = read3;
    	param = read1;
    } else if ((read3 < FLOOR_WHITE_THRESHOLD) && (last3 > FLOOR_BLACK_THRESHOLD)) {
    	curEvent = ;
    	last3 = read3;
    	param = read1;
    } else if ((read4 > FLOOR_BLACK_THRESHOLD) && (last4 < FLOOR_WHITE_THRESHOLD)) {
    	curEvent = ;
    	last4 = read4;
    	param = read1;
    } else if ((read2 < FLOOR_WHITE_THRESHOLD) && (last4 > FLOOR_BLACK_THRESHOLD)) {
    	curEvent = ;
    	last4 = read4;
    	param = read1;
    } else {
    	curEvent = lastEvent;
    	param = 
    }

    if (curEvent != lastEvent) { // check for change from last time
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = batVoltage;
        returnVal = TRUE;
        lastEvent = curEvent; // update history
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostTemplateHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif   
    }
    return (returnVal);
}

 /**
 * @Function TemplateCheckBattery(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is a prototype event checker that checks the battery voltage
 *        against a fixed threshold (#defined in the .c file). Note that you need to
 *        keep track of previous history, and that the actual battery voltage is checked
 *        only once at the beginning of the function. The function will post an event
 *        of either BATTERY_CONNECTED or BATTERY_DISCONNECTED if the power switch is turned
 *        on or off with the USB cord plugged into the Uno32. Returns TRUE if there was an 
 *        event, FALSE otherwise.
 * @note Use this code as a template for your other event checkers, and modify as necessary.
 * @author Gabriel H Elkaim, 2013.09.27 09:18
 * @modified Gabriel H Elkaim/Max Dunne, 2016.09.12 20:08 */
 
uint8_t TemplateCheckBattery(void) {
    static ES_EventTyp_t lastEvent = BATTERY_DISCONNECTED;
    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    uint16_t batVoltage = AD_ReadADPin(BAT_VOLTAGE); // read the battery voltage
 
    if (batVoltage > BATTERY_DISCONNECT_THRESHOLD) { // is battery connected?
        curEvent = BATTERY_CONNECTED;
    } else {
        curEvent = BATTERY_DISCONNECTED;
    }
    if (curEvent != lastEvent) { // check for change from last time
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = batVoltage;
        returnVal = TRUE;
        lastEvent = curEvent; // update history
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostTemplateHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif   
    }
    return (returnVal);
}
 
/* 
 * The Test Harness for the event checkers is conditionally compiled using
 * the EVENTCHECKER_TEST macro (defined either in the file or at the project level).
 * No other main() can exist within the project.
 * 
 * It requires a valid ES_Configure.h file in the project with the correct events in 
 * the enum, and the correct list of event checkers in the EVENT_CHECK_LIST.
 * 
 * The test harness will run each of your event detectors identically to the way the
 * ES_Framework will call them, and if an event is detected it will print out the function
 * name, event, and event parameter. Use this to test your event checking code and
 * ensure that it is fully functional.
 * 
 * If you are locking up the output, most likely you are generating too many events.
 * Remember that events are detectable changes, not a state in itself.
 * 
 * Once you have fully tested your event checking code, you can leave it in its own
 * project and point to it from your other projects. If the EVENTCHECKER_TEST marco is
 * defined in the project, no changes are necessary for your event checkers to work
 * with your other projects.
 */
#ifdef EVENTCHECKER_TEST
#include <stdio.h>
static uint8_t(*EventList[])(void) = {EVENT_CHECK_LIST};
 
void PrintEvent(void);
 
void main(void) {
    BOARD_Init();
    /* user initialization code goes here */
 
    // Do not alter anything below this line
    int i;
 
    printf("\r\nEvent checking test harness for %s", __FILE__);
 
    while (1) {
        if (IsTransmitEmpty()) {
            for (i = 0; i< sizeof (EventList) >> 2; i++) {
                if (EventList[i]() == TRUE) {
                    PrintEvent();
                    break;
                }
 
            }
        }
    }
}
 
void PrintEvent(void) {
    printf("\r\nFunc: %s\tEvent: %s\tParam: 0x%X", eventName,
            EventNames[storedEvent.EventType], storedEvent.EventParam);
}
#endif