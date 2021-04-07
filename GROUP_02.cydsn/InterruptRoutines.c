/*
* File InterrupRoutines.c
*/
#include "InterruptRoutines.h"
#include "project.h"
#include "stdio.h"

// static char message [20] = {'\0'}; 

/*UART ISR function: it is executed when a new data comes from the serial port.
  The data is stored in the received variable and the flag data_received is set to 1 */

CY_ISR(Custom_UART_RX_ISR){
    if(UART_RGB_ReadRxStatus() == UART_RGB_RX_STS_FIFO_NOTEMPTY){ 
        //Reading the data coming from the serial port
        received=UART_RGB_ReadRxData();
        data_received=1;
    }
}

/*Timer ISR function: according to the settings of the top design this function is executed every second.
  The count variable is updated when the ISR is called, so it contains the number of seconds. */

CY_ISR(Custom_TIMER_ISR){
    //Read timer status register and bring interrupt line low 
    Timer_RGB_ReadStatusRegister();
    count++;
    
   //Print seconds (useful in the test code phase):
   // sprintf(message, "%i\r\n", count);
   // UART_RGB_PutString(message);
}

/* [] END OF FILE */
