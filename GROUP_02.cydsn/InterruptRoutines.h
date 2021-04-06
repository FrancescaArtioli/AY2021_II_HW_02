/* ========================================
 * \file InterruptRoutines.h
 * Brief declaration of the two interrupt
 * function we need, one for UART and one
 * for the timer.
 * ========================================
*/
    #define IDLE 0
    #define HEADER 1
    #define RED 2
    #define GREEN 3
    #define BLU 4
    #define TAIL 5
    #define TIMER_CONFIG 6
    #define TIMER_ENDCONFIG 7
    
#ifndef __INTERRUPT_ROUTINES_H__
    #define __INTERRUPT_ROUTINES_H__
    
    //Include project header file
    #include "project.h"

    CY_ISR_PROTO(Custom_UART_RX_ISR);
    CY_ISR_PROTO(Custom_TIMER_ISR);
   
   
#endif
/* [] END OF FILE */
