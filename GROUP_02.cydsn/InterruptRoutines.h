/*
 * File InterruptRoutines.h
 * Brief declaration of the two interrupt
 * functions we need, one for UART and one
 * for the timer.
*/
   
    
#ifndef __INTERRUPT_ROUTINES_H__
    #define __INTERRUPT_ROUTINES_H__
    
    //Include project header file
    #include "project.h"
    
    //Status definition
    #define IDLE 0
    #define HEADER 1
    #define RED 2
    #define GREEN 3
    #define BLU 4
    #define TIMER_CONFIG 5
    #define TIMER_ENDCONFIG 6
    #define CONNECTION_COMMAND 7
    #define PACKET_HEADER 160
    #define TIMER_HEADER 161
    #define PACKET_TAIL 192
    
    //Here we are going to add some variables: 
    //data_received: a flag which becomes 1 every time a data is received from the UART
    //received: a variable containing the data read from the serial port
    //status: containg the current state
    //count: used to count seconds every time the Timer ISR is called
    volatile uint8_t data_received;
    volatile uint8_t status; 
    volatile uint8_t received; 
    volatile uint8_t count;
    
    //ISR prototypes 
    CY_ISR_PROTO(Custom_UART_RX_ISR);
    CY_ISR_PROTO(Custom_TIMER_ISR);
   
   
#endif
/* [] END OF FILE */
