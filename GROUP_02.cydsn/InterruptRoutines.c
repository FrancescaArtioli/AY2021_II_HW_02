/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "InterruptRoutines.h"
#include "project.h"
#include "stdio.h"

extern volatile uint8_t status;
extern volatile uint8_t received;
extern volatile uint8_t flag_header;
extern volatile uint8_t flag_red;
extern volatile uint8_t flag_green;
extern volatile uint8_t flag_blu;
extern volatile uint8_t flag_tail;
//static char message [20] = {'\0'};

CY_ISR(Custom_UART_RX_ISR)

{
    //received = 0;
    //sprintf(message, "siamo nell'isr\r\n");
    //UART_RGB_PutString(message);
    
    
    if(UART_RGB_ReadRxStatus() == UART_RGB_RX_STS_FIFO_NOTEMPTY && status == IDLE){
        
        received = UART_RGB_ReadRxData();
        //sprintf(message, "Valore ricevuto : %i\r\n", received);
        //UART_RGB_PutString(message);
        flag_header = 1;
    }
    
    if(UART_RGB_ReadRxStatus() == UART_RGB_RX_STS_FIFO_NOTEMPTY){
        //sprintf(message, "registro notempy e stato = %i\r\n", status);
        //UART_RGB_PutString(message);
    }
    
    if(UART_RGB_ReadRxStatus() == UART_RGB_RX_STS_FIFO_NOTEMPTY && status == HEADER){
        
        received = UART_RGB_ReadRxData();
        
        //sprintf(message, "Valore rosso : %i \r\n", received);
        //UART_RGB_PutString(message);
        flag_red = 1;
    }
    
    if(UART_RGB_ReadRxStatus() == UART_RGB_RX_STS_FIFO_NOTEMPTY && status == RED){
        received = UART_RGB_ReadRxData();
        
        //sprintf(message, "Valore verde : %i\r\n", received);
        //UART_RGB_PutString(message);
        flag_green = 1;
    }
    
     if(UART_RGB_ReadRxStatus() == UART_RGB_RX_STS_FIFO_NOTEMPTY && status == GREEN){
        received = UART_RGB_ReadRxData();
        
        //sprintf(message, "Valore blu : %i\r\n", received);
        //UART_RGB_PutString(message);
        flag_blu = 1;
    }
    
     if(UART_RGB_ReadRxStatus() == UART_RGB_RX_STS_FIFO_NOTEMPTY && status == BLU){
        received = UART_RGB_ReadRxData();
        //sprintf(message, "Led in accensione %i\r\n", received);
        //UART_RGB_PutString(message);
        flag_tail = 1;
    }
}

/* [] END OF FILE */
