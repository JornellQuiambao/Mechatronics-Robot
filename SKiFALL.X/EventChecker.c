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

#include "Motors.h"
#include "BOARD.h"
#include <xc.h>
#include "pwm.h"
#include "serial.h"
#include "IO_Ports.h"
#include "Bumpers.h"
#include "Tape.h"
#include "Trackwire.h"
#include <stdio.h>
#include "AD.h"
#include "Ping.h"
#include "timers.h"
#include "Stepper.h"
#include <math.h>
#include <stdlib.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define BATTERY_DISCONNECT_THRESHOLD 175
#define FLOOR_WHITE_THRESHOLD 300
#define FLOOR_BLACK_THRESHOLD 400
#define BEACON_LO_THRESHOLD  350
#define BEACON_HI_THRESHOLD  700
#define TRACKW_LO_THRESHOLD 350
#define TRACKW_HI_THRESHOLD 700
#define TRACKW_A_LO_THRESHOLD 700 
#define TRACKW_A_HI_THRESHOLD 720
//#define GUN_THRESHOLD_LO 300 // LO
//#define GUN_THRESHOLD_HI 850 // updated, prev 850 ; HI 
#define GUN_WHITE_THRESHOLD 200//300
#define GUN_BLACK_THRESHOLD 700 
//#define GUN_THRESHOLDL 750 
#define GUN_THRESHOLDL 720 
#define GUN_THRESHOLDL_EMPTY 850 
#define GUN_THRESHOLDR 650 
#define GUN_THRESHOLDR_EMPTY 800 
#define FL_BUMPER 1
#define FR_BUMPER 2
#define PING_OBJECT_THRESHOLD 8
#define PING_OBJECT_THRESHOLD2 10
#define HIGH_PING_THRESHOLD 20

//#define EVENTCHECKER_TEST
#ifdef EVENTCHECKER_TEST
//#include <stdio.h>
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

uint8_t CheckBumpers(void) {
    static ES_EventTyp_t lastEvent = ES_NO_EVENT;
    ES_EventTyp_t curEvent = ES_NO_EVENT;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    static uint16_t lastbump = 0;
    uint16_t bumper = Bumpers_Read();

    if (bumper == FL_BUMPER && lastbump == 0) {

        curEvent = LEFT_BUMP;

    } else if (bumper == FR_BUMPER && lastbump == 0) {
        curEvent = RIGHT_BUMP;

    } else if (bumper == 0) {
        curEvent = NO_BUMPER_HIT;
    } else {
        curEvent = lastEvent;
    }

    if (curEvent != lastEvent) { // check for change from last time
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = bumper;
        returnVal = TRUE;
        lastEvent = curEvent; // update history
        curEvent = ES_NO_EVENT;
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostBotHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif   
    }
    return (returnVal);
}

/**
 * Function: CheckTapeFloor
 * @param None
 * @return TRUE or FALSE
 * @remark Checks for Tripped Tape Sensors
 * @author Jornell Quiambao */
uint8_t CheckTapeFloor(void) {
    static ES_EventTyp_t lastEvent = ES_NO_EVENT;
    ES_EventTyp_t curEvent = ES_NO_EVENT;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    static uint16_t last1 = 0;
    static uint16_t last2 = 0;
    static uint16_t last3 = 0;
    static uint16_t last4 = 0;
    uint16_t read1 = Tape_ReadFloorFL();
    uint16_t read2 = Tape_ReadFloorFR();
    //    uint16_t read3 = Tape_ReadFloorFC();
    uint16_t read4 = Tape_ReadFloorB();
    static uint16_t param = 0;
    static uint16_t lastparam = 0;

    if ((read1 > FLOOR_BLACK_THRESHOLD) && (last1 < FLOOR_WHITE_THRESHOLD)) {
        curEvent = TAPE_FL_TRIPPED;
        last1 = read1;
        param = read1;
    } else if ((read1 < FLOOR_WHITE_THRESHOLD) && (last1 > FLOOR_BLACK_THRESHOLD)) {
        curEvent = TAPE_FL_CLEARED;
        last1 = read1;
        param = read1;
    } else if ((read2 > FLOOR_BLACK_THRESHOLD) && (last2 < FLOOR_WHITE_THRESHOLD)) {
        curEvent = TAPE_FR_TRIPPED;
        last2 = read2;
        param = read2;
    } else if ((read2 < FLOOR_WHITE_THRESHOLD) && (last2 > FLOOR_BLACK_THRESHOLD)) {
        curEvent = TAPE_FR_CLEARED;
        last2 = read2;
        param = read2;
    } else if ((read4 > FLOOR_BLACK_THRESHOLD) && (last4 < FLOOR_WHITE_THRESHOLD)) {
        curEvent = TAPE_BACK_TRIPPED;
        last4 = read4;
        param = read4;
    } else if ((read4 < FLOOR_WHITE_THRESHOLD) && (last4 > FLOOR_BLACK_THRESHOLD)) {
        curEvent = TAPE_BACK_CLEARED;
        last4 = read4;
        param = read4;
    } else { //No change in         Event
        curEvent = lastEvent;
        param = lastparam;
    }
    lastparam = param;

    if (curEvent != lastEvent) { // check for change from last time
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = param;
        returnVal = TRUE;
        lastEvent = curEvent; // update history
        curEvent = ES_NO_EVENT;
        //printf("\r\n TAPE EVENT, Param: %d", thisEvent.EventParam);
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostBotHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif   
    }
    return (returnVal);
}

/**
 * Function: CheckTapeGun
 * @param None
 * @return TRUE or FALSE
 * @remark Checks Tape for Firing Mechanism
 * @author Jornell Quiambao & Brian Naranjo */


uint8_t CheckTapeGun(void) { // check this event 
    static ES_EventTyp_t lastEvent = LEFT_GUN_MISSED;
    ES_EventTyp_t curEvent = ES_NO_EVENT;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE; //State of Beacon

    unsigned int readLeft = Tape_ReadGunL(); //W3
    unsigned int readRight = Tape_ReadGunR(); //W4
    int flag = Gun_Flagger();

    static unsigned int param = 0;
    static unsigned int lastparam = 0;
    static unsigned int lastGunLeft = 0;
    static unsigned int lastGunRight = 0;
    //static uint16_t lastGun2 = 0;
    //static uint16_t lastGun3 = 0;
    //static uint16_t lastGun4 = 0;


    //    if ((readLeft > GUN_THRESHOLDL_HI)) {
    //        curEvent = LEFT_GUN_TARGETED;
    //    } else if ((readLeft < GUN_THRESHOLDL_LO)) {
    //        curEvent = LEFT_GUN_MISSED;
    //    } else {
    //        curEvent = lastEvent;
    //    }
    //
    //    lastGunLeft = readLeft;

    //    if ((readLeft >= GUN_THRESHOLD_HI)&&(readRight >= GUN_THRESHOLD_HI) && ((lastGunLeft < GUN_THRESHOLD_LO) || (lastGunRight < GUN_THRESHOLD_LO)) && flag) {
    //        curEvent = TAPE_GUN_TARGETED;
    //
    //    } else if ((readRight >= GUN_THRESHOLD_HI) && (readLeft < GUN_THRESHOLD_LO) && ((lastGunRight < GUN_THRESHOLD_LO) || (lastGunLeft >= GUN_THRESHOLD_HI)) && flag) {
    //        curEvent = RIGHT_GUN_TARGETED;
    //
    //
    //    } else if ((readLeft >= GUN_THRESHOLD_HI) && (readRight < GUN_THRESHOLD_LO) && ((lastGunLeft < GUN_THRESHOLD_LO) || (lastGunRight >= GUN_THRESHOLD_HI)) && flag) {
    //        curEvent = LEFT_GUN_TARGETED;
    //
    //
    //    } else if ((readLeft < GUN_THRESHOLD_LO)&&(readRight < GUN_THRESHOLD_LO) && ((lastGunLeft >= GUN_THRESHOLD_HI) || (lastGunRight >= GUN_THRESHOLD_HI)) && flag) {
    //        curEvent = TAPE_GUN_MISSED;


    if ((readLeft >= GUN_THRESHOLDL) &&(readRight >= GUN_THRESHOLDR) && ((lastGunLeft < GUN_THRESHOLDL) || (lastGunRight < GUN_THRESHOLDR)) && flag) {
        curEvent = TAPE_GUN_TARGETED;

    } else if ((readRight >= GUN_THRESHOLDR) && (readLeft < GUN_THRESHOLDL) && ((lastGunRight < GUN_THRESHOLDR) || (lastGunLeft >= GUN_THRESHOLDL)) && flag) {
        //        curEvent = LEFT_GUN_TARGETED;
        curEvent = RIGHT_GUN_TARGETED;


    } else if ((readLeft >= GUN_THRESHOLDL) && (readRight < GUN_THRESHOLDR) && ((lastGunLeft < GUN_THRESHOLDL) || (lastGunRight >= GUN_THRESHOLDR)) && flag) {
        //       curEvent = RIGHT_GUN_TARGETED;
        curEvent = LEFT_GUN_TARGETED;


    } else if ((readLeft < GUN_THRESHOLDL)&&(readRight < GUN_THRESHOLDR) && ((lastGunLeft >= GUN_THRESHOLDL) || (lastGunRight >= GUN_THRESHOLDR))) {
        curEvent = TAPE_GUN_MISSED;

    } else { //No change in Event
        param = lastparam;
        curEvent = lastEvent;
    }
    lastGunLeft = readLeft;
    lastGunRight = readRight;
    lastparam = param;


    if (curEvent != lastEvent) { // check for change from last time
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = param;
        returnVal = TRUE;
        lastEvent = curEvent; // update history
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostBotHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif   
    }
    return (returnVal);
}

/**
 * Function: CheckBeacon
 * @param None
 * @return TRUE or FALSE
 * @remark Checks for Beacon Signal
 * @author Jornell Quiambao & Brian Naranjo */


uint8_t CheckBeacon(void) {
    static ES_EventTyp_t lastEvent = BEACON_LOST;
    ES_EventTyp_t curEvent = ES_NO_EVENT;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE; //State of Beacon
    static unsigned int beaconSignal, lastbeaconSignal = 900;
    static uint16_t param = 0;

    beaconSignal = Beacon_Read(); //Read Beacon Signal
    param = Beacon_Read();
    if ((beaconSignal < BEACON_LO_THRESHOLD) && (lastbeaconSignal > BEACON_HI_THRESHOLD)) {
        curEvent = BEACON_FOUND;
        param = beaconSignal;
    } else if ((beaconSignal > BEACON_HI_THRESHOLD) && (lastbeaconSignal < BEACON_LO_THRESHOLD)) { //No change in Event
        curEvent = BEACON_LOST;
    } else { //No change in Event
        curEvent = lastEvent;
    }
    lastbeaconSignal = beaconSignal;


    if (curEvent != lastEvent) { // check for change from last time
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = param;
        returnVal = TRUE;
        lastEvent = curEvent; // update history
        curEvent = ES_NO_EVENT;
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostBotHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif   
    }
    return (returnVal);
}

///**
// * Function: CheckTrackwireAnalog
// * @param None
// * @return TRUE or FALSE
// * @remark Checks for TrackWire Analog Signal
// * @author Jornell Quiambao & Brian Naranjo */
//
//
//uint8_t CheckTrackwire(void) {
//    static ES_EventTyp_t lastEvent = ES_NO_EVENT;
//    ES_EventTyp_t curEvent = ES_NO_EVENT;
//    ES_Event thisEvent;
//    uint8_t returnVal = FALSE; //State of Beacon
//    static unsigned int trackwire_Signal, last_trackwire_Signal = 900;
//    //    static unsigned int trackwire_Signal_left,last_trackwire_Signal_left =  900;
//    //    static unsigned int trackwire_Signal_right,last_trackwire_Signal_right =  900;
//    static uint16_t param = 0;
//
//    trackwire_Signal = Trackwire_Read(); //R
//    param = trackwire_Signal;
//    //    trackwire_Signal_left = Trackwire_ReadLeft(); //Read TW L
//    //    trackwire_Signal_right = Trackwire_ReadRight(); //Read TW R
//    //    param = last_trackwire_Signal_left - last_trackwire_Signal_right;
//
//
//    if ((trackwire_Signal < TRACKW_LO_THRESHOLD) && (last_trackwire_Signal > TRACKW_HI_THRESHOLD)) {
//        curEvent = TRACKWIRE_TRIGGERED;
//    } else if ((trackwire_Signal > TRACKW_HI_THRESHOLD) && (last_trackwire_Signal < TRACKW_LO_THRESHOLD)) {
//        curEvent = TRACKWIRE_CLEARED;
//
//        //    if ((trackwire_Signal_left < TRACKW_LO_THRESHOLD) && (trackwire_Signal_right > TRACKW_HI_THRESHOLD)
//        //        && (last_trackwire_Signal_left > TRACKW_HI_THRESHOLD)){
//        //        curEvent = TRACKWIRE_L_TRIGGERED;
//        //    } else if((trackwire_Signal_right < TRACKW_LO_THRESHOLD) && (trackwire_Signal_left > TRACKW_HI_THRESHOLD)
//        //        && (last_trackwire_Signal_right > TRACKW_HI_THRESHOLD)) {  
//        //    	curEvent = TRACKWIRE_R_TRIGGERED;
//        //    } else if((trackwire_Signal_right < TRACKW_LO_THRESHOLD) && (trackwire_Signal_left < TRACKW_LO_THRESHOLD)
//        //        && ((last_trackwire_Signal_right > TRACKW_HI_THRESHOLD)||(last_trackwire_Signal_left > TRACKW_HI_THRESHOLD))) {  //No change in Event
//        //    	curEvent = TRACKWIRE_BOTH_TRIGGERED;
//        //    } else if((trackwire_Signal_right > TRACKW_HI_THRESHOLD) && (trackwire_Signal_left > TRACKW_HI_THRESHOLD)
//        //        && ((last_trackwire_Signal_right > TRACKW_HI_THRESHOLD)||(last_trackwire_Signal_left > TRACKW_HI_THRESHOLD))){
//        //        curEvent = TRACKWIRE_CLEARED;
//        //    } else if ((lastEvent == TRACKWIRE_BOTH_TRIGGERED)&&((trackwire_Signal_right > TRACKW_HI_THRESHOLD))){
//        //        curEvent = TRACKWIRE_L_TRIGGERED;
//        //    } else if ((lastEvent == TRACKWIRE_BOTH_TRIGGERED)&&((trackwire_Signal_left > TRACKW_HI_THRESHOLD))){
//        //        curEvent = TRACKWIRE_R_TRIGGERED;
//    } else { //No change in Event
//        curEvent = lastEvent;
//    }
//
//    last_trackwire_Signal = trackwire_Signal;
//    //    last_trackwire_Signal_left = trackwire_Signal_left;
//    //    last_trackwire_Signal_right = trackwire_Signal_right;
//
//    if (curEvent != lastEvent) { // check for change from last time
//        thisEvent.EventType = curEvent;
//        thisEvent.EventParam = param;
//        returnVal = TRUE;
//        lastEvent = curEvent; // update history
//        curEvent = ES_NO_EVENT;
//#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
//        PostBotHSM(thisEvent);
//#else
//        SaveEvent(thisEvent);
//#endif   
//    }
//    return (returnVal);
//}

/**
 * Function: CheckTrackwireAnalog
 * @param None
 * @return TRUE or FALSE
 * @remark Checks for TrackWire Signal
 * @author Jornell Quiambao & Brian Naranjo */


uint8_t CheckTrackwireAnalog(void) {
    static ES_EventTyp_t lastEvent = TRACKWIRE_CLEARED;
    ES_EventTyp_t curEvent = ES_NO_EVENT;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE; //State of Beacon
    static unsigned int trackwire_Signal, last_trackwire_Signal = 0;
    int flag = 0;
    //    static unsigned int trackwire_Signal_left,last_trackwire_Signal_left =  900;
    //    static unsigned int trackwire_Signal_right,last_trackwire_Signal_right =  900;
    static uint16_t param = 0;

    trackwire_Signal = Trackwire_Read(); //R
    flag = Trackwire_Flagger();
    param = trackwire_Signal;



    //    if ((trackwire_Signal >= TRACKW_A_HI_THRESHOLD) && (last_trackwire_Signal < TRACKW_A_LO_THRESHOLD)) {
    //        curEvent = TRACKWIRE_TRIGGERED;
    //    } else if ((trackwire_Signal <= TRACKW_A_LO_THRESHOLD) && (last_trackwire_Signal > TRACKW_A_HI_THRESHOLD)) {
    //        curEvent = TRACKWIRE_CLEARED;
    //
    //    } else { //No change in Event
    //        curEvent = lastEvent;
    //    }
    if ((trackwire_Signal >= TRACKW_A_HI_THRESHOLD) && flag) {
        curEvent = TRACKWIRE_TRIGGERED;
    } else if ((trackwire_Signal <= TRACKW_A_LO_THRESHOLD)) {
        curEvent = TRACKWIRE_CLEARED;

    } else { //No change in Event
        curEvent = lastEvent;
    }

    last_trackwire_Signal = trackwire_Signal;
    //    last_trackwire_Signal_left = trackwire_Signal_left;
    //    last_trackwire_Signal_right = trackwire_Signal_right;

    if (curEvent != lastEvent) { // check for change from last time
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = param;
        returnVal = TRUE;
        lastEvent = curEvent; // update history
        curEvent = ES_NO_EVENT;
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostBotHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif   
    }
    return (returnVal);
}

/**
 * Function: CheckPing
 * @param None
 * @return TRUE or FALSE
 * @remark Checks for Ping Event
 * @author Jornell Quiambao */
uint8_t CheckPing(void) {
    static ES_EventTyp_t lastEvent = PING_CLEARED;
    ES_EventTyp_t curEvent = ES_NO_EVENT;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    //    static uint16_t lastbump = 0;
    uint16_t Ping_R = Ping_Distance(); //Port V6
    uint16_t Ping_L = Ping_Distance2(); //Port V4

    unsigned int parallel = abs(Ping_R - Ping_L);

    //    printf("\r\nPing: %d", Ping_1);

    //    if ((parallel < 2) && (Ping_R <= PING_OBJECT_THRESHOLD)) {
    //        curEvent = PING_PARALLEL;
    //    } else 
    if ((Ping_L <= PING_OBJECT_THRESHOLD) && (Ping_R > PING_OBJECT_THRESHOLD)) {
        curEvent = PING_LEFT_OBJECT;
    } else if ((Ping_L > PING_OBJECT_THRESHOLD) && (Ping_R <= PING_OBJECT_THRESHOLD)) {
        curEvent = PING_RIGHT_OBJECT;
    } else if ((Ping_L <= PING_OBJECT_THRESHOLD) && (Ping_R <= PING_OBJECT_THRESHOLD)) {
        curEvent = PING_BOTH_OBJECT;
    } else if ((Ping_L > PING_OBJECT_THRESHOLD) && (Ping_R > PING_OBJECT_THRESHOLD) && (Ping_R < HIGH_PING_THRESHOLD) && (Ping_L < HIGH_PING_THRESHOLD)) {
        curEvent = PING_CLEARED;
        //    } else if (parallel > 2) {
        //        curEvent = PING_CLEARED;  
        //    } else if ((Ping_L <= HIGH_PING_THRESHOLD) && (Ping_R <= HIGH_PING_THRESHOLD)) {
        //        curEvent = HIGH_PING;
    } else if ((Ping_L > HIGH_PING_THRESHOLD) && (Ping_R > HIGH_PING_THRESHOLD)) {
        curEvent = HIGH_PING_CLEARED;
    } else {
        curEvent = lastEvent;
    }

    if (curEvent != lastEvent) { // check for change from last time
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = Ping_L - Ping_R;
        returnVal = TRUE;
        lastEvent = curEvent; // update history
        curEvent = ES_NO_EVENT;
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostBotHSM(thisEvent);
#else
        SaveEvent(thisEvent);
#endif   
    }
    return (returnVal);
}

uint8_t CheckStepper(void) {
    static ES_EventTyp_t lastEvent = NOT_STEPPING;
    ES_EventTyp_t curEvent = ES_NO_EVENT;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    int8_t stepping = Stepper_IsStepping();
    int32_t param = Stepper_GetRemainingSteps();

    if (stepping) {
        curEvent = STEPPING;
    } else if (!stepping) {
        curEvent = NOT_STEPPING;
    } else {
        curEvent = lastEvent;
    }



    if (curEvent != lastEvent) { // check for change from last time
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = param;
        returnVal = TRUE;
        lastEvent = curEvent; // update history
        //        curEvent = ES_NO_EVENT;
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        PostBotHSM(thisEvent);
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
        PostBotHSM(thisEvent);
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
void delay(int ticks);

void main(void) {
    BOARD_Init(); //Initialization Code


    /* user initialization code goes here */
    PWM_Init();
    AD_Init();
    //    Motors_Init();
    Bumpers_Init();
    Tape_Init();
    TIMERS_Init();
    //    Gun_Setter();
    PING_Init();
    //        Trackwire_Setter();
//    Stepper_Init();
//    Gun_Setter();
    LATEbits.LATE2 = 0;

    AD_AddPins(AD_PORTV7 | AD_PORTV8 |
            AD_PORTW3 | AD_PORTW4 | AD_PORTW5 | AD_PORTW6 | AD_PORTW7 | AD_PORTW8);

    // Do not alter anything below this line
    int i;

    printf("\r\nEvent checking test harness for %s", __FILE__);

    while (1) {
//        if (IsTransmitEmpty()) {
//            for (i = 0; i< sizeof (EventList) >> 2; i++) {
//                if (EventList[i]() == TRUE) {
//                    PrintEvent();
//                    break;
//                }
//            }
//        }
        //        printf("\r\n L:%d R: %d", Tape_ReadGunL(), Tape_ReadGunR());
        //                delay(100000);
                printf("\r\n L:%d R: %d", Ping_Distance2(), Ping_Distance());
                delay(100000);
    }
}

void PrintEvent(void) {
    printf("\r\nFunc: %s\tEvent: %s\tParam: 0x%X", eventName,
            EventNames[storedEvent.EventType], storedEvent.EventParam);
}

void delay(int ticks) {
    int i = 0;
    while (i < ticks) {
        i++;
    }
}
#endif