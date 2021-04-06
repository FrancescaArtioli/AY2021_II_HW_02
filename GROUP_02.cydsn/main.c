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



int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_RGB_Start(); /*Enable Uart*/
    isr_UART_StartEx(Custom_UART_RX_ISR);
    RGBLed_Start();
    status = 0;
	RGBLed_WriteColor(BLACK);

	for (;;)
	{
	if (data_received==1 && status==0){ //IDLE
	if (received==160){
	status++;
	data_received=0;
	}
	else {
	status=0;
	data_received=0;
	}
    }

	
 
    else if (data_received==1 && status==1){
	color.red = received;
	status++;
	data_received=0;
	}
	
	else if (data_received==1 && status==2){
	color.green=received;
	status++;
	data_received=0;
	}
	
	
	else if (data_received==1 && status==3){
	color.blu=received;
	status++;
	data_received=0;
	}
	
	
	else if (data_received==1 && status==4){
	if (received==192){
	status++;
	}
	else {
        status=0;
        data_received=0;
    }
    }
	
	
	else if (status==5){
	RGBLed_WriteColor(color);
	status=0;
	data_received=0;
	}
	
	
    
}
}

	
   


/* [] END OF FILE */
