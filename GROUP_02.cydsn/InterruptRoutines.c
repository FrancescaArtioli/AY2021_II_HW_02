/* ========================================
* InterrupRoutines.c
* authors: Francesca Artioli, Monica Loddo
*/
#include "InterruptRoutines.h"
#include "project.h"
#include "stdio.h"

extern volatile uint8_t data_received;
extern volatile uint8_t status; //variable containing the current status
extern volatile uint8_t received; //variable containing data coming from the serial port
//static char message [20] = {'\0'};

CY_ISR(Custom_UART_RX_ISR){
    if(UART_RGB_ReadRxStatus() == UART_RGB_RX_STS_FIFO_NOTEMPTY){ 
        //Reading the data coming from the serial port
        received=UART_RGB_ReadRxData();
        data_received=1;
    }
}

/* [] END OF FILE */
