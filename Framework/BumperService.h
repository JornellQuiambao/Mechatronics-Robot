/*
 * File: BumperService.c
 * Author: jquiamba
 *
 * 
 *
 * 
 */

#ifndef BUMPER_SERVICE_H
#define BUMPER_SERVICE_H

/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/
 
#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT
 
/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
 
 
/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/
 
 
/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
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
uint8_t InitBumperService(uint8_t Priority);

/**
 * Function: PostBumperService
 * @param None
 * @return TRUE or FALSE
 * @remark This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */

uint8_t PostBumperService(ES_Event ThisEvent);

/**
 * Function: RunBumperService
 * @param None
 * @return TRUE or FALSE
 * @remark This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Remember to rename to something appropriate.
 *       Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 */
ES_Event RunBumperService(ES_Event ThisEvent);

#endif /* BUMPER_SERVICE_H */