/* ========================================
 Interrupt Routines
 Authors: Francesce Artioli, Monica Loddo
*/
#include "project.h"
#include "InterruptRoutines.h"
#include "RGBLedDriver.h"
#include "stdio.h"

volatile uint8_t data_received=0;
volatile uint8_t received = 0;
volatile uint8_t status = 0;
const Color BLACK = {0, 0, 0};
volatile Color color;

static char message [20] = {'\0'};

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    UART_RGB_Start(); /*Start Uart*/
    isr_UART_StartEx(Custom_UART_RX_ISR);
    RGBLed_Start();
    
    status = 0;
    uint8_t max_value=5;

    
	RGBLed_WriteColor(BLACK);

	for (;;)
	{
	    if (data_received==1 && status==IDLE){ 
            if (received==160){
                status++;
                data_received=0;
            }
            
            else if (received==161){
                //sprintf(message,"161 ricevuto/r/n");
                //UART_RGB_PutString(message);
                status=TIMER_CONFIG;
                data_received=0;
            }
            
            else if (received=='v'){
                sprintf(message, "RGB LED Program $$$");
                UART_RGB_PutString(message);
                data_received=0;
                status = IDLE;
            }
            else {
                status=IDLE;
                data_received=0;
            }
        }
        
        else if (data_received==1 && status==HEADER){
            color.red = received;
            status++;
            data_received=0;
        }
        
        else if (data_received==1 && status==RED){
            color.green=received;
            status++;
            data_received=0;
        }
        
        else if (data_received==1 && status==GREEN){
            color.blu=received;
            status++;
            data_received=0;
        }
        
        else if (data_received==1 && status==BLU){
            if (received==192){
                status++;
            }
            else {
                status=IDLE;
                data_received=0;
            }
        }
        
        else if (status==TAIL){
            RGBLed_WriteColor(color);
            status=IDLE;
            data_received=0;
        }
        else if (data_received==1 && status==TIMER_CONFIG){
            max_value=received;
            //sprintf(message, "%i/r/n", max_value);
            //UART_RGB_PutString(message);
            status++;
            data_received=0;
        }
        else if (status==TIMER_ENDCONFIG && data_received==1){
            if (received==192){
                status=IDLE;
                data_received=0;
            }
            else {
                status =TIMER_ENDCONFIG;
            }
        }
    }
}

/* [] END OF FILE */
