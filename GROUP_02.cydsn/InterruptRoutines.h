/*
 * File InterruptRoutines.h
 * Brief declaration of the two interrupt
 * function we need, one for UART and one
 * for the timer.
*/
   
    
#ifndef __INTERRUPT_ROUTINES_H__
    #define __INTERRUPT_ROUTINES_H__
    
    //Include project header file
    #include "project.h"
    
    // Status definition
    #define IDLE 0
    #define HEADER 1
    #define RED 2
    #define GREEN 3
    #define BLU 4
    #define TAIL 5
    #define TIMER_CONFIG 6
    #define TIMER_ENDCONFIG 7
    
    //Variables declaration
    extern volatile uint8_t data_received; //flag to be set to 1 every time one data is received from the UART
    extern volatile uint8_t received; //variable containing data coming from the serial port
    extern volatile uint8_t count; // variable containing seconds
    
    // ISR prototypes 
    CY_ISR_PROTO(Custom_UART_RX_ISR);
    CY_ISR_PROTO(Custom_TIMER_ISR);
   
   
#endif
/* [] END OF FILE */
