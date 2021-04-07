/* ========================================
* InterrupRoutines.c
* authors: Francesca Artioli, Monica Loddo
*/
#include "InterruptRoutines.h"
#include "project.h"
#include "stdio.h"

// static char message [20] = {'\0'}; 

CY_ISR(Custom_UART_RX_ISR){
    if(UART_RGB_ReadRxStatus() == UART_RGB_RX_STS_FIFO_NOTEMPTY){ 
        //Reading the data coming from the serial port
        received=UART_RGB_ReadRxData();
        data_received=1;
    }
}

CY_ISR(Custom_TIMER_ISR){
    Timer_RGB_ReadStatusRegister();
    count++;
   // sprintf(message, "%i\r\n", count);
   // UART_RGB_PutString(message);
}

/* [] END OF FILE */
