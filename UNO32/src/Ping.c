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

#define TIME_HI 6
#define TIME_LO 37500

/*******************************************************************************
 * PRIVATE VARIABLES                                                            *
 ******************************************************************************/

static unsigned int start;
static unsigned int end;
static unsigned int EW;

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
    OpenTimer3(T3_ON | T3_SOURCE_INT | T3_PS_1_64, 8);
    INTClearFlag(INT_T3);
    INTSetVectorPriority(INT_TIMER_3_VECTOR, 3);
    INTSetVectorSubPriority(INT_TIMER_3_VECTOR, 3);
    INTEnable(INT_T3, INT_ENABLED);
    TRISBbits.TRISB4 = 0; // V5
    // set input capture change notify for echo
    mCNOpen(CN_ON, CN7_ENABLE, 0); // CN7 = V6
    int temp = PORTB;
    ConfigIntCN(CHANGE_INT_ON | CHANGE_INT_PRI_1);
}

/**
 * Function: Timer3IntHandler
 * @param None
 * @return None
 * @remark  ISR to pulse trigger pin
 * @author Jornell Quiambao */
void __ISR(_TIMER_3_VECTOR, ipl3auto) Timer3IntHandler(void) {
    INTClearFlag(INT_T3);
    int trigger = 0;
    trigger = PORTBbits.RB4;
    if (!trigger) {
        LATBbits.LATB4 = 1;
        PR3 = TIME_HI;
    } else {
        LATBbits.LATB4 = 0;
        PR3 = TIME_LO;
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
    int time = 0;
    if (echo) {
        start = TIMERS_GetMicro();
    } else {
        end = TIMERS_GetMicro();
        time = end - start;
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