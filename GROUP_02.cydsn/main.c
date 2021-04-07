/* 
 * File main.c
 * Project GROUP_02: the project aims to control the color of a RGB LED through a serial port.
 * 
 * Authors: Francesce Artioli, Monica Loddo
*/

/*First we include all the header files, containg the declaration of the functions we need 
 to call in the main file.*/
#include "project.h"
#include "InterruptRoutines.h"
#include "RGBLedDriver.h"
#include "stdio.h"

/*Here we are going to add some variables, which are: 
 data_received: a flag which becomes 1 every time a data is received from the UART
 received: a variable containing the data read from the serial port
 status: containg the state in which we are (see the InterruptRoutines.h file)*/
volatile uint8_t data_received=0;
volatile uint8_t received = 0;
volatile uint8_t status = 0;


/*Defining the balck color in RGB.*/
const Color BLACK = {0, 0, 0};
volatile Color color;

/*Defining a variable message needed to print the connection command string on the serial port (and
 eventually for debugging purposes).*/
static char message [20] = {'\0'};

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    UART_RGB_Start(); /*Start UART.*/
    isr_UART_StartEx(Custom_UART_RX_ISR); /*Initialization/startup code for UART isr.*/
    RGBLed_Start(); /*Start RGBLed.*/
    
    /*Initialize the variable status to 0 (IDLE state).*/
    status = 0;
    
    /*Defining and initializing a variable max_value, which defines the seconds of timeout.*/
    uint8_t max_value = 5;

    /*When the system is powered after programming, the LED is ON with color black.*/
	RGBLed_WriteColor(BLACK);

	for (;;)
	{
	    if (data_received == 1 && status == IDLE){ 
            //if a data is received and we are in the IDLE state
            if (received == 160){
                status++;
                data_received = 0;
            } 
            //if received is equal to 160, then we pass in the HEADER state (1) and we lower the flag
            
            else if (received == 161){
                status = TIMER_CONFIG;
                data_received = 0;
            } 
            //if received is equal to 161, the we pass in the TIMER_CONFIGURATION state, and we lower the flag
            
            else if (received == 'v'){
                sprintf(message, "RGB LED Program $$$");
                UART_RGB_PutString(message);
                data_received = 0;
                status = IDLE;
            } 
            //if received is equal to 'v', then a string is sent to the serial port for the testing of the program with a GUI and we lower the flag
            
            else {
                status = IDLE;
                data_received = 0;
            } 
            //if received is any other value, then we remain in the IDLE state
        }
        
        else if (data_received == 1 && status == HEADER){ 
            //if a data is received and we are in the HEADER state
            color.red = received; 
            //the received data is stored in the type red of a struct holding colors
            status++; 
            //status is incremented
            data_received = 0; 
            //the flag is lowered
        }
        
        else if (data_received == 1 && status == RED){ 
            //if a data is received and we are in the RED state
            color.green = received; 
            //the received data is stored in the type green of a struct holding colors
            status++; 
            //status is incremented
            data_received = 0;
            //the flag is lowered
        }
        
        else if (data_received == 1 && status == GREEN){ 
            //if a data is received and we are in the GREEN state
            color.blu = received; 
            //the received data is stored in the type blu of a struct holding colors
            status++; 
            //status is incremented
            data_received = 0; 
            //the flag is lowered
        }
        
        else if (data_received == 1 && status == BLU){ 
            //if a data is received and we are in the BLU state
            if (received == 192){ 
                status++;
            } 
            //if received is equal to 192, then we increment the status passing in TAIL state
            
            else {
                status = IDLE;
                data_received = 0;
            } 
        }
        
        else if (status == TAIL){
            RGBLed_WriteColor(color);
            status = IDLE;
            data_received = 0;
        } 
        //if we are in the TAIL state, then we are ready to write the new color on the LED.
        
        else if (data_received == 1 && status == TIMER_CONFIG){ 
            //if a data is received and we are in the TIMER_CONFIGURATION state
            max_value = received; 
            //the received data represent the value of timeout in second
            status++; 
            //the status is increased in order to enter in the END_CONFIGURATION state
            data_received = 0; 
            //flag is lowered
        }
        
        else if (status == TIMER_ENDCONFIG && data_received == 1){ 
            //if a data is received and we are in the END_CONFIGURATION state
            if (received == 192){
                status = IDLE;
                data_received = 0;
            } 
            //if the received data is 192, then timer configuration is ended and we return to IDLE state
            else {
                status = TIMER_ENDCONFIG; 
                //if any other data is received, we have decided to remain the the END_CONFIGURATION state waiting for the value 192 to be received
            }
        }
    }
}

/* [] END OF FILE */
