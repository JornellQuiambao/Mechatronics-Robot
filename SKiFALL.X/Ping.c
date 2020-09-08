/*
 * File:   Ping.c
 * Author: jquiamba
 * 
 * 
 * 
 * 
 */
     

#include <xc.h>
#include <BOARD.h>
#include "Ping.h"
#include <stdio.h>
#include <timers.h>
#include <IO_Ports.h>
#include <plib.h>



/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/

#define TIME_HI 50
//#define TIME_LO 37500
#define TIME_LO 50000

/*******************************************************************************
 * PRIVATE VARIABLES                                                            *
 ******************************************************************************/

static unsigned int start;
static unsigned int end;
static unsigned int EW;

static unsigned int start2;
static unsigned int end2;
static unsigned int EW2;

static int flag = 0;
static int change = 0;
/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * Function: PING_Init
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Initializes pins used for the ping sensor (trig = V5, echo = V6)
 * @author Jornell Quiambao */
char PING_Init(void) {
    // set timer for trigger
    OpenTimer4(T4_ON | T4_SOURCE_INT | T4_PS_1_64, 8);
    INTClearFlag(INT_T4);
    INTSetVectorPriority(INT_TIMER_4_VECTOR, 3);
    INTSetVectorSubPriority(INT_TIMER_4_VECTOR, 3);
    INTEnable(INT_T4, INT_ENABLED);
    TRISBbits.TRISB4 = 0; // V5
    TRISBbits.TRISB2 = 0; // V3
    
    // set input capture change notify for echo
    mCNOpen(CN_ON, CN7_ENABLE | CN5_ENABLE, 0); // CN7 = V6, CN5 = V4
    int temp = PORTB;
    ConfigIntCN(CHANGE_INT_ON | CHANGE_INT_PRI_1);
}

/**
 * Function: Timer3IntHandler
 * @param None
 * @return None
 * @remark  ISR to pulse trigger pin
 * @author Jornell Quiambao */
void __ISR(_TIMER_4_VECTOR, ipl3auto) Timer4IntHandler(void) {
    INTClearFlag(INT_T4);
    int trigger = 0;
    int trigger2 = 0;
    trigger = PORTBbits.RB4;
    trigger2 = PORTBbits.RB2;
    if (flag == 0) {
        flag = 1;
        if (!trigger) {
            LATBbits.LATB4 = 1;
            PR4 = TIME_HI;
        } else {
            LATBbits.LATB4 = 0;
            PR4 = TIME_LO;
        }
    } else {
        flag = 0;
        if (!trigger2) {
            LATBbits.LATB2 = 1;
            PR4 = TIME_HI;
        } else {
            LATBbits.LATB2 = 0;
            PR4 = TIME_LO;
        }
    }
}

/**
 * Function: ChangeNotice_Handler
 * @param None
 * @return SUCCESS or ERROR
 * @remark  ISR to read echo pin
 * @author Jornell Quiambao */
void __ISR(_CHANGE_NOTICE_VECTOR, ipl1auto) ChangeNotice_Handler(void) {
    static char readPort = 0;
    readPort = PORTB;
    INTClearFlag(INT_CN); 
    int echo = PORTBbits.RB5;
    int echo2 = PORTBbits.RB3;
    int time = 0;
    int time2 = 0;
    
    if (echo2) start2 = TIMERS_GetMicroSeconds();
    else {
        end2 = TIMERS_GetMicroSeconds();
        time2 = end2 - start2;
        if (time2 >= 165 && time2 <= 23528) {
            EW2 = time2;
        } 
    }
    if (echo) start = TIMERS_GetMicroSeconds();
    else {
        end = TIMERS_GetMicroSeconds();
        time = end - start;
        if (time >= 165 && time <= 23528) {
            EW = time;
        } 
    }
}

/**
 * Function: Ping_Distance
 * @param None
 * @return SUCCESS or ERROR
 * @remark  Returns distance read from the ping sensor
 * @author Jornell Quiambao */
unsigned int Ping_Distance(void) {
    // D = EW/148 * 2.54 to convert in to cm 
    return ((EW * 254) / (148 * 100));
}

unsigned int Ping_Distance2(void) {
    // D = EW/148 * 2.54 to convert in to cm 
    return ((EW2 * 254) / (148 * 100));
}