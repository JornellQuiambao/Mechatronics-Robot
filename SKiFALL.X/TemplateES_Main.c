#include <BOARD.h>
#include <xc.h>
#include <stdio.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "Motors.h"
#include "Bumpers.h"
#include "Beacon.h"
#include "Tape.h"
#include "AD.h"
#include "Ping.h"
#include "timers.h"
#include "Trackwire.h"
#include "Stepper.h"
#include "pwm.h"

void main(void)
{
    ES_Return_t ErrorType;

    BOARD_Init();

    printf("Starting ES Framework Template\r\n");
    printf("using the 2nd Generation Events & Services Framework\r\n");


    // Your hardware initialization function calls go here
    PWM_Init();
    AD_Init();
    Tape_Init();
    Beacon_Init();
    Motors_Init();
    Bumpers_Init();
    TIMERS_Init(); 
    PING_Init();
    Trackwire_Init();
    Stepper_Init();
    AD_AddPins(AD_PORTV7|AD_PORTV8|AD_PORTW3|AD_PORTW4|AD_PORTW5|AD_PORTW6|AD_PORTW7|AD_PORTW8);
    PWM_AddPins(PWM_PORTZ06);
    PWM_SetFrequency(MIN_PWM_FREQ);
    PWM_SetDutyCycle(PWM_PORTZ06, 200);
    
    
    // now initialize the Events and Services Framework and start it running
    ErrorType = ES_Initialize();
    if (ErrorType == Success) {
        ErrorType = ES_Run();

    }
    //if we got to here, there was an error
    switch (ErrorType) {
    case FailedPointer:
        printf("Failed on NULL pointer");
        break;
    case FailedInit:
        printf("Failed Initialization");
        break;
    default:
        printf("Other Failure: %d", ErrorType);
        break;
    }
    for (;;)
        ;

};

/*------------------------------- Footnotes -------------------------------*/
/*------------------------------ End of file ------------------------------*/
