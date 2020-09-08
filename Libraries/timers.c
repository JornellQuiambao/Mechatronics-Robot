/*
 * File:   timers.c
 * Author: mdunne
 *
 * Created on November 15, 2011, 9:53 AM
 */
 
#include <xc.h>
#include <BOARD.h>
#include <peripheral/timer.h>
#include "timers.h"
 
 
/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
//#define TIMERS_TEST
 
#define F_PB (BOARD_GetPBClock())
#define TIMER_FREQUENCY 1000
#define NUM_TIMERS 16
 
/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/
 
//static unsigned int milliSecondCount;
static unsigned int Timer_Array[NUM_TIMERS];
static unsigned int TimerActiveFlags;
static unsigned int TimerEventFlags;
static unsigned int FreeRunningTimer;
static unsigned int microSecondCount;
 
/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/
 
/**
 * @Function TIMERS_Init(void)
 * @param none
 * @return None.
 * @brief  Initializes the timer module
 * @author Max Dunne */
void TIMERS_Init(void) {
    TimerActiveFlags = 0;
    TimerEventFlags = 0;
    FreeRunningTimer = 0;
    microSecondCount = 0;
    OpenTimer5(T5_ON | T5_SOURCE_INT | T5_PS_1_8, F_PB / 8 / TIMER_FREQUENCY);
    INTClearFlag(INT_T5);
    INTSetVectorPriority(INT_TIMER_5_VECTOR, 3);
    INTSetVectorSubPriority(INT_TIMER_5_VECTOR, 3);
    INTEnable(INT_T5, INT_ENABLED);
}

/**
 * @Function TIMERS_SetTimer(unsigned char Num, unsigned int NewTime)
 * @param Num - the number of the timer to set.
 * @param NewTime -  the number of milliseconds to be counted
 * @return ERROR or SUCCESS
 * @brief  sets the time for a timer, but does not make it active.
 * @author Max Dunne  2011.11.15 */
char TIMERS_SetTimer(unsigned char Num, unsigned int NewTime) {
    if (Num >= NUM_TIMERS)
        return ERROR;
    Timer_Array[Num] = NewTime;
    return SUCCESS;
}

/**
 * @Function TIMERS_StartTimer(unsigned char Num)
 * @param Num - the number of the timer to start
 * @return ERROR or SUCCESS
 * @brief  simply sets the active flag in TMR_ActiveFlags to resart a stopped timer.
 * @author Max Dunne, 2011.11.15 */
char TIMERS_StartTimer(unsigned char Num) {
    if (Num >= NUM_TIMERS)
        return ERROR;
    TimerActiveFlags |= (1 << Num);
    return SUCCESS;
}

/**
 * @Function TIMERS_StopTimer(unsigned char Num)
 * @param Num - the number of the timer to stop.
 * @return ERROR or SUCCESS
 * @brief  simply clears the bit in TimerActiveFlags associated with this timer. This 
 * will cause it to stop counting.
 * @author Max Dunne 2011.11.15 */
char TIMERS_StopTimer(unsigned char Num) {
    if (Num >= NUM_TIMERS)
        return ERROR;
    TimerActiveFlags &= ~(1 << Num);
    return SUCCESS;
}

/**
 * @Function TIMERS_InitTimer(unsigned char Num, unsigned int NewTime)
 * @param Num -  the number of the timer to start
 * @param NewTime - the number of tick to be counted
 * @return ERROR or SUCCESS
 * @brief  sets the NewTime into the chosen timer and clears any previous event flag 
 * and sets the timer actice to begin counting.
 * @author Max Dunne 2011.11.15 */
char TIMERS_InitTimer(unsigned char Num, unsigned int NewTime) {
    if (Num >= NUM_TIMERS)
        return ERROR;
    Timer_Array[Num] = NewTime;
    TimerEventFlags &= ~(1 << Num);
    TimerActiveFlags |= (1 << Num);
    return SUCCESS;
}

/**
 * @Function TIMERS_IsTimerActive(unsigned char Num)
 * @param Num - the number of the timer to check
 * @return ERROR or TIMER_NOT_ACTIVE or TIMER_ACTIVE
 * @brief  used to determine if a timer is currently counting.
 * @author Max Dunne   2011.11.15 */
char TIMERS_IsTimerActive(unsigned char Num) {
    if (Num >= NUM_TIMERS)
        return ERROR;
    if ((TimerActiveFlags & (1 << Num)) != 0) {
        return TIMER_ACTIVE;
    } else {
        return TIMER_NOT_ACTIVE;
    }
}

/**
 * @Function TIMERS_IsTimerExpired(unsigned char Num)
 * @param Num - the number of the timer to check
 * @return ERROR or TIMER_NOT_EXPIRED or TIMER_EXPIRED
 * @brief  used to determine if a timer is currently expired.
 * @author Max Dunne   2011.11.15 */
char TIMERS_IsTimerExpired(unsigned char Num) {
    if (Num >= NUM_TIMERS)
        return ERROR;
    if ((TimerEventFlags & (1 << Num)) != 0) {
        return TIMER_EXPIRED;
    } else {
        return TIMER_NOT_EXPIRED;
    }
}

/**
 * @Function TIMERS_ClearTimerExpired(unsigned char Num) 
 * @param Num - the timer whose event flag should be cleared.
 * @return ERROR or SUCCESS
 * @brief  simply clears the appropriate bit in Event Flags to show that the event 
 * has been serviced.
 * @author Max Dunne  211.11.15 */
char TIMERS_ClearTimerExpired(unsigned char Num) {
    if (Num >= NUM_TIMERS)
        return ERROR;
    TimerEventFlags &= ~(1 << Num);
    return SUCCESS;
}

/**
 * Function: TIMERS_GetTime
 * @param None
 * @return FreeRunningTimer, the current value of the module variable FreeRunningTimer
 * @remark Provides the ability to grab a snapshot time as an alternative to using
 * the library timers. Can be used to determine how long between 2 events.
 * @author Max Dunne 2011.11.15  */
unsigned int TIMERS_GetTime(void) {
    return FreeRunningTimer;
}
 
/**
 * Function: TIMERS_GetMicroSeconds
 * @param None
 * @return the current MicroSecond Count, it will roll over in 1.9 hours
 * @author Max Dunne
 */
 
unsigned int TIMERS_GetMicroSeconds(void) {
    return (microSecondCount + TMR5 / 5);
}
 
/**
 * @Function Timer5IntHandler(void)
 * @param None.
 * @return None.
 * @brief  This is the interrupt handler to support the timer module. It will increment 
 * time
 * @author Max Dunne */
 
void __ISR(_TIMER_5_VECTOR, ipl3auto) Timer5IntHandler(void) {
    INTClearFlag(INT_T5);
    FreeRunningTimer++;
    microSecondCount+=1000;
    char CurTimer = 0;
    if (TimerActiveFlags != 0) {
        for (CurTimer = 0; CurTimer < NUM_TIMERS; CurTimer++) {
            if ((TimerActiveFlags & (1 << CurTimer)) != 0) {
                if (--Timer_Array[CurTimer] == 0) {
                    TimerEventFlags |= (1 << CurTimer);
                    TimerActiveFlags &= ~(1 << CurTimer);
                }
            }
        }
    }
}
 
 
 
