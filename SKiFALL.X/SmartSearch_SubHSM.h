/*
 * File: SmartSearch_SubHSM.h
 * Author: Brian Naranjo & jquiamba
 * Date: 11/15/19
 *
 */

#ifndef SMARTSEARCH_H
#define	SMARTSEARCH_H


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/


/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/




/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/


/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitSmartSearch_SubHSM(void)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunSmartSearch_SubHSM function.
 *        Returns TRUE if successful, FALSE otherwise
* @author J. Edward Carryer, 2011.10.23 19:25 
* @editor Brian Naranjo, 11/15/19   */
uint8_t InitSmartSearch_SubHSM(void);

/**
 * @Function PostSmartSearch_SubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its namevoid
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25
 * @editor Brian Naranjo, 11/15/19    */

//uint8_t PostSmartSearch_SubHSM(ES_Event ThisEvent);

/**
 * @Function RunSmartSearch_SubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 
 * @editor Brian Naranjo, 11/15/19  */
ES_Event RunSmartSearch_SubHSM(ES_Event ThisEvent);

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/
 #endif