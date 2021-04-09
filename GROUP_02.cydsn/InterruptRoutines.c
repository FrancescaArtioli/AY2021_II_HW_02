/* 
 * File InterruptRoutines.c
 * For a better undertsanding of the ISR functions, see the code description in the main code.
*/

#include "InterruptRoutines.h"
#include "project.h"
#include "stdio.h"
#include "TimerReset.h"

CY_ISR(Custom_UART_RX_ISR){
    if(UART_RGB_ReadRxStatus() == UART_RGB_RX_STS_FIFO_NOTEMPTY){ 
        received=UART_RGB_ReadRxData();
        data_received=1;

        if (status == IDLE){
            if (received == PACKET_HEADER) {
                status = HEADER;
                Reset_Timer();
            }
            else if (received == TIMER_HEADER){
                status = TIMER_CONFIG;
            }
            else if (received == 'v'){
                status = CONNECTION_COMMAND;
            }
            else{
                status = IDLE;
            }
        
            data_received = 0;
        }
    }
}

CY_ISR(Custom_TIMER_ISR){
    
    Timer_RGB_ReadStatusRegister();
    count++;
    
}

/* [] END OF FILE */
