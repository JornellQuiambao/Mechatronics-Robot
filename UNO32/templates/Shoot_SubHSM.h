/*
 * File: Shoot_SubHSM.h
 * Author: Brian Naranjo
 * Date: 11/13/19
 *
 */

#ifndef Shoot_SubHSM_H  // <- This should be changed to your own guard on both
#define Shoot_SubHSM_H //    of these lines


/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitShoot_SubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunShoot_SubHSM function.
 *        Returns TRUE if successful, FALSE otherwise
* @author J. Edward Carryer, 2011.10.23 19:25 
* @editor Brian Naranjo, 11/13/19   */
uint8_t InitShoot_SubHSM(uint8_t Priority);
/**
 * @Function PostShoot_SubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25
 * @editor Brian Naranjo, 11/13/19    */

uint8_t PostShoot_SubHSM(ES_Event ThisEvent);

/**
 * @Function RunShoot_SubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 
 * @editor Brian Naranjo, 11/13/19  */
ES_Event RunShoot_SubHSM(ES_Event ThisEvent);

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/