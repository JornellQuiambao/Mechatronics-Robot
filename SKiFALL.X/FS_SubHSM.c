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
#include "Tape.h"
#include <stdio.h>



/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/


/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/

static uint8_t MyPriority;
typedef enum {
    INIT_STATE,
    WAITING,
    BACKUP,        
    INITIAL_TURN,
    ALIGN_SIDE,
    REALIGN_FRONT,
    REALIGN_BACK,
    CHECK_TRACKWIRE,
    MOVE_TO_F_SIDE1,
    MOVE_TO_F_SIDE2,
    MOVE_TO_F_SIDE3,
    MOVE_TO_B_SIDE1,
    MOVE_TO_B_SIDE2,
    MOVE_TO_B_SIDE3,
    PARALLEL_START,
    S_MOTION_1,
    S_MOTION_2,
    S_MOTION_3,
    STOP_SIDE,
    PARALLEL_DONE,
} FS_State_t;

static const char *StateNames[] = {
	"INIT_STATE",
	"WAITING",
	"BACKUP",
	"INITIAL_TURN",
	"ALIGN_SIDE",
	"REALIGN_FRONT",
	"REALIGN_BACK",
	"CHECK_TRACKWIRE",
	"MOVE_TO_F_SIDE1",
	"MOVE_TO_F_SIDE2",
	"MOVE_TO_F_SIDE3",
	"MOVE_TO_B_SIDE1",
	"MOVE_TO_B_SIDE2",
	"MOVE_TO_B_SIDE3",
	"PARALLEL_START",
	"S_MOTION_1",
	"S_MOTION_2",
	"S_MOTION_3",
	"STOP_SIDE",
	"PARALLEL_DONE",
};

#define TIME_TILL_PARALLEL 2000 //2sec, Amount of time needed to spin bot parallel to side
#define TIME_TO_CHECK 1000 //Duration for checking Side, If expired, no TrackWire
#define APPROACH_SPEED 600
#define ALIGN_SPEED 400
#define BACKUP_TIME 6000
#define STOPSIDE_TIME 6000


#define TANK_TURN_SPEED 600 //Speed for Tank Turning Smoothly
#define TURN_SPEEDL 500 //Speed for constant motion around target, L Motor 
#define TURN_SPEEDR 800 //Speed for constant motion around target, R Motor 
#define STOP_SPEED 0  //Macro to stop motors 
#define D_THRESHOLD 3 //Macro for distance to wall to assume parallel to wall
#define TIME_TO_SIDE_ONE 500 
#define TIME_TO_SIDE_TWO 400 
#define TIME_TO_SIDE_THREE 1000 
#define TIME_S_MOTION_1 500
#define TIME_S_MOTION_2 500
#define TIME_S_MOTION_3 500
#define S1_LEFT_SPEED 500
#define S1_RIGHT_SPEED 500
#define S2_LEFT_SPEED 500 
#define S2_RIGHT_SPEED 500
#define S3_LEFT_SPEED 500
#define S3_RIGHT_SPEED 500

static FS_State_t CurrentState = INIT_STATE; //Initialize static Variables
//static ES_Event ThisEvent;
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
uint8_t InitFS_SubHSM(void){
    ES_Event returnEvent;
    CurrentState = INIT_STATE;
//    ThisEvent.EventType = ES_INIT;
    returnEvent = RunFS_SubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    } else {
        return FALSE;
    }
}

///**
// * @Function PostFS_SubHSM(ES_Event ThisEvent)
// * @param ThisEvent - the event (type and param) to be posted to queue
// * @return TRUE or FALSE
// * @brief This function is a wrapper to the queue posting function, and its name
// *        will be used inside ES_Configure to point to which queue events should
// *        be posted to. Remember to rename to something appropriate.
// *        Returns TRUE if successful, FALSE otherwise
// * @author J. Edward Carryer, 2011.10.23 19:25
// * @editor Brian Naranjo, 11/13/19    */
//
//uint8_t PostFS_SubHSM(ES_Event ThisEvent){
//    return ES_PostToService(MyPriority, ThisEvent);
//}

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

    ES_Tattle(); // trace call stack

    switch (CurrentState){      

        case INIT_STATE:
            if (ThisEvent.EventType == ES_INIT){// only respond to ES_Init
                NextState = WAITING; //Transition to First State
               
                makeTransition = TRUE; 
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
//            } else if(ThisEvent.EventType == ES_ENTRY){
//                NextState = BACKUP; //Transition to First State
//                ES_Timer_InitTimer(PARKING_TIMER, BACKUP_TIME);
//                makeTransition = TRUE; 
//                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
//            }
            break;
            
        case WAITING:
            
//            printf("\r\nHEERE!!!");
            if(ThisEvent.EventType == ES_ENTRY){
                
                NextState = BACKUP; //Transition to First State
                makeTransition = TRUE; 
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(PARKING_TIMER, BACKUP_TIME);
            }
//            } else if(ThisEvent.EventType == ES_ENTRY){
//                NextState = BACKUP; //Transition to First State
//                ES_Timer_InitTimer(PARKING_TIMER, BACKUP_TIME);
//                makeTransition = TRUE; 
//                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
//            }
            break;
            
        case BACKUP:
            Motors_LeftDrive(APPROACH_SPEED); //Set Both Motors to drive FWD
            Motors_RightDrive(APPROACH_SPEED);
            Motors_LeftDirection(MOTOR_REVERSE);
            Motors_RightDirection(MOTOR_REVERSE);
            if(ThisEvent.EventType == ES_TIMEOUT){
                NextState = INITIAL_TURN; //Transition to First State
                makeTransition = TRUE; 
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
           
//            else{
//                NextState = BACKUP;
//                //makeTransition = TRUE; 
//                //ThisEvent.EventType = ES_NO_EVENT; 
//            }
            
            
            break;
    
        case INITIAL_TURN:
            Motors_TankTurn(APPROACH_SPEED, TANK_TURN_RIGHT);
            
            if(ThisEvent.EventType == PING_RIGHT_OBJECT){
                NextState = ALIGN_SIDE; //Transition to First State
                makeTransition = TRUE; 
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
            
//            Motors_LeftDrive(STOP_SPEED); //Set Both Motors to drive FWD
//            Motors_RightDrive(STOP_SPEED);
//            if((Ping_Distance() > D_THRESHOLD) && (Ping_Distance2() > D_THRESHOLD)){
//                NextState = CHECK_TRACKWIRE;
//                makeTransition = TRUE; 
//                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
//                ES_Timer_InitTimer(PARKING_TIMER, TIME_TO_CHECK);
//            }
            // if (ThisEvent.EventType == ES_TIMEOUT){
            //     if((Ping_Distance() < D_THRESHOLD) && (Ping_Distance2() < D_THRESHOLD)){ //both sides close
            //         NextState = CHECK_TRACKWIRE;
            //         makeTransition = TRUE; 
            //         ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            //     } else if((Ping_Distance() > D_THRESHOLD) && (Ping_Distance2() < D_THRESHOLD)){
            //         NextState = REALIGN_FRONT;
            //         makeTransition = TRUE; 
            //         ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            //     } else if((Ping_Distance() < D_THRESHOLD) && (Ping_Distance2() > D_THRESHOLD)){
            //         NextState = REALIGN_BACK;
            //         makeTransition = TRUE; 
            //         ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            //     } 
            // }
            
            break;

            
        case ALIGN_SIDE: // first proxy is high , get second proxy 
            
            Motors_LeftDrive(ALIGN_SPEED); 
            Motors_RightDrive(ALIGN_SPEED); 
            Motors_LeftDirection(MOTOR_FORWARD); 
            Motors_RightDirection(MOTOR_FORWARD); 
            
            if (ThisEvent.EventType == PING_LEFT_OBJECT) { // both proxys are high 
                NextState = REALIGN_FRONT; //Transition to First State
                makeTransition = TRUE; 
                ThisEvent.EventType = ES_NO_EVENT; 
                
                
            }
            
            
            
            
            break; 
            
            
        case STOP_SIDE: 
            
            Motors_LeftDrive(STOP_SPEED); 
            Motors_RightDrive(STOP_SPEED); 
            
            if(ThisEvent.EventType == ES_TIMEOUT){
                NextState = CHECK_TRACKWIRE; //Transition to First State
                makeTransition = TRUE; 
                ThisEvent.EventType = ES_NO_EVENT;
                ES_Timer_InitTimer(PARKING_TIMER, STOPSIDE_TIME);
            }
            
            break; 
            
            
            
            
        case CHECK_TRACKWIRE:     
            
            Motors_TankTurn(APPROACH_SPEED,TANK_TURN_LEFT);
            
            
         break;    
            
            
        case REALIGN_FRONT:
            Motors_TankTurn(APPROACH_SPEED, TANK_TURN_LEFT);
            if((Ping_Distance() > D_THRESHOLD) && (Ping_Distance2() > D_THRESHOLD)){
                NextState = CHECK_TRACKWIRE;
                makeTransition = TRUE; 
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
                ES_Timer_InitTimer(PARKING_TIMER, TIME_TO_CHECK);
            }
            break;

        case REALIGN_BACK:
            Motors_TankTurn(APPROACH_SPEED, TANK_TURN_LEFT);
            if((Ping_Distance() > D_THRESHOLD) && (Ping_Distance2() > D_THRESHOLD)){
                NextState = CHECK_TRACKWIRE;
                makeTransition = TRUE; 
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
            }
            break;

//        case CHECK_TRACKWIRE:
//            Motors_LeftDrive(STOP_SPEED); //Set Both Motors to STOP
//            Motors_RightDrive(STOP_SPEED);
//            if(ThisEvent.EventType == TRACKWIRE_TRIGGERED){
//                NextState = PARALLEL_START;
//                makeTransition = TRUE; 
//                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
//            } else if(ThisEvent.EventType == TRACKWIRE_L_TRIGGERED){
//                NextState = MOVE_TO_B_SIDE1;
//                makeTransition = TRUE; 
//                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
//                ES_Timer_InitTimer(PARKING_TIMER, TIME_TO_SIDE_ONE);
//            } else if(ThisEvent.EventType == TRACKWIRE_R_TRIGGERED){
//                NextState = MOVE_TO_F_SIDE1;
//                makeTransition = TRUE; 
//                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event
//                ES_Timer_InitTimer(PARKING_TIMER, TIME_TO_SIDE_ONE);
//            }

//            break;

        case MOVE_TO_F_SIDE1:
            if(ThisEvent.EventType == ES_TIMEOUT){
                NextState = MOVE_TO_F_SIDE2;
                makeTransition = TRUE; 
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event 
                ES_Timer_InitTimer(PARKING_TIMER, TIME_TO_SIDE_TWO);
            }
            break;

        case MOVE_TO_F_SIDE2:
            if(ThisEvent.EventType == ES_TIMEOUT){
                NextState = MOVE_TO_F_SIDE3;
                makeTransition = TRUE; 
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event 
                ES_Timer_InitTimer(PARKING_TIMER, TIME_TO_SIDE_THREE);
            }
            break;

        case MOVE_TO_F_SIDE3:
            if(ThisEvent.EventType == ES_TIMEOUT){
                NextState = PARALLEL_START;
                makeTransition = TRUE; 
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event 
                ES_Timer_InitTimer(PARKING_TIMER, TIME_TO_CHECK);
            }
            break;

        case MOVE_TO_B_SIDE1:
            if(ThisEvent.EventType == ES_TIMEOUT){
                NextState = MOVE_TO_B_SIDE2;
                makeTransition = TRUE; 
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event 
                ES_Timer_InitTimer(PARKING_TIMER, TIME_TO_SIDE_TWO);
            }
            break;

        case MOVE_TO_B_SIDE2:
            if(ThisEvent.EventType == ES_TIMEOUT){
                NextState = MOVE_TO_B_SIDE3;
                makeTransition = TRUE; 
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event 
                ES_Timer_InitTimer(PARKING_TIMER, TIME_TO_SIDE_THREE);
            }
            break;

        case MOVE_TO_B_SIDE3:
            if(ThisEvent.EventType == ES_TIMEOUT){
                NextState = PARALLEL_START;
                makeTransition = TRUE; 
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event 
                ES_Timer_InitTimer(PARKING_TIMER, TIME_TO_CHECK);
            }
            break;

        case PARALLEL_START:
            Motors_LeftDrive(STOP_SPEED); //Set Both Motors to STOP
            Motors_RightDrive(STOP_SPEED);
            if(ThisEvent.EventType == ES_TIMEOUT){
                NextState = S_MOTION_1;
                makeTransition = TRUE; 
                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event 
                ES_Timer_InitTimer(PARKING_TIMER, TIME_S_MOTION_1);
            }
            break;

//        case S_MOTION_1:
//            Motors_LeftDrive(S1_LEFT_SPEED); //Set Both Motors to STOP
//            Motors_RightDrive(S1_RIGHT_SPEED);
//            Motors_LeftDirection(MOTOR_REVERSE);
//            Motors_RightDirection(MOTOR_REVERSE);
//            if(ThisEvent.EventType == ES_TIMEOUT){
//                NextState = S_MOTION_2;
//                makeTransition = TRUE; 
//                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event 
//                ES_Timer_InitTimer(PARKING_TIMER, TIME_S_MOTION_2);
//            }
//            break;
//
//        case S_MOTION_2:
//            Motors_LeftDrive(S2_LEFT_SPEED); //Set Both Motors to STOP
//            Motors_RightDrive(S2_RIGHT_SPEED);
//            Motors_LeftDirection(MOTOR_REVERSE);
//            Motors_RightDirection(MOTOR_REVERSE);
//            if(ThisEvent.EventType == ES_TIMEOUT){
//                NextState = S_MOTION_3;
//                makeTransition = TRUE; 
//                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event 
//                ES_Timer_InitTimer(PARKING_TIMER, TIME_S_MOTION_3);
//            }
//            break;
//
//        case S_MOTION_3:
//            Motors_LeftDrive(S3_LEFT_SPEED); //Set Both Motors to STOP
//            Motors_RightDrive(S3_RIGHT_SPEED);
//            Motors_LeftDirection(MOTOR_FORWARD);
//            Motors_RightDirection(MOTOR_FORWARD);
//            if(ThisEvent.EventType == GUN_BUMPERS_HIT){
//                NextState = PARALLEL_DONE;
//                makeTransition = TRUE; 
//                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event 
//                Motors_LeftDrive(STOP_SPEED); //Set Both Motors to STOP
//                Motors_RightDrive(STOP_SPEED);
//            } else if(ThisEvent.EventType == ES_TIMEOUT){
//                NextState = S_MOTION_1;
//                makeTransition = TRUE; 
//                ThisEvent.EventType = ES_NO_EVENT; //Initialize Event 
//            }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
//        case PARALLEL_DONE:
//            Motors_LeftDrive(STOP_SPEED); //Set Both Motors to STOP
//            Motors_RightDrive(STOP_SPEED);
//            break;

        default:
            break;           

        }
        if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
            // recursively call the current state with an exit event
            RunFS_SubHSM(EXIT_EVENT); // <- Exit SM
            CurrentState = NextState;   //Change States
            RunFS_SubHSM(ENTRY_EVENT); // <- Enter SM
        }
        
    ES_Tail(); // trace call stack end
    return ThisEvent;
} 

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/


