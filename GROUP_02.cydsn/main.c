/* 
 * File main.c
 * Project GROUP_02: the project aims to control the color of a RGB LED through a serial port.
 *
 * Code Description:
 *
 *
 * Notes:
 *
 *
 * Authors: Francesce Artioli, Monica Loddo
*/

/*First we include all the header files, containg the declaration of the functions we need 
 to call in the main file.*/
#include "project.h"
#include "InterruptRoutines.h"
#include "RGBLedDriver.h"
#include "stdio.h"
#include "TimerReset.h"

/*Here we are going to add some variables: 
 data_received: a flag which becomes 1 every time a data is received from the UART
 received: a variable containing the data read from the serial port
 status: containg the state in which we are (see the InterruptRoutines.h file)
 count: used to count seconds every time the Timer ISR is called*/
volatile uint8_t data_received=0;
volatile uint8_t received = 0;
volatile uint8_t status = 0;
volatile uint8_t count = 0;

/*Defining the balck color in RGB.*/
const Color BLACK = {0, 0, 0};
volatile Color color;

/*Defining a variable message needed to print the connection command string on the serial port (and
 eventually for debugging purposes).*/
static char message [20] = {'\0'};

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    /*Initialization/startup code*/
    UART_RGB_Start(); 
    isr_UART_StartEx(Custom_UART_RX_ISR); 
    RGBLed_Start(); 
    Timer_RGB_Start(); 
    isr_Timer_StartEx(Custom_TIMER_ISR); 
    
    /*Initialize the variable status to 0 (IDLE state).*/
    status = IDLE;
    
    /*Defining and initializing a variable max_value, which defines the seconds of timeout: default 5s*/
    uint8_t max_value = 5;

    /*When the system is powered after programming, the LED is ON with color black.*/
	RGBLed_WriteColor(BLACK);

	for (;;)
	{
	    if (data_received == 1 && status == IDLE){ 
            //when we are in the IDLE state and we receive a new data we have to check its value
            if (received == 160){
                status++;
                data_received = 0;
                Reset_Timer();   
            } 
            //if received is equal to 160, then we pass in the HEADER state (1) and we lower the flag.
            //We also reset the timer in order to start counting and to allow the system to go back to the idle state
            //if no command is received within the end of timeout.
            
            
            else if (received == 161){
                status = TIMER_CONFIG;
                data_received = 0;
            } 
            //if received is equal to 161, then we pass in the TIMER_CONFIGURATION state, and we lower the flag
            
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
        
        if (count == max_value){
            status = IDLE;
        }
        
        else {
            if (data_received == 1 && status == HEADER){ 
                //if a data is received and we are in the HEADER state
                color.red = received; 
                //the received data is stored in the type red of a struct holding colors
                status++; 
                data_received = 0; 
                Reset_Timer(); 
                //We chose to reset the timer when a data is written in one of the RGB Led channels. 
                //In this way the count variable contains the seconds that elapse between the reception of two consecutive data
                //See the TimerReset.c for more information about the implementation of the function.
            }
        
            else if (data_received == 1 && status == RED){ 
                //if a data is received and we are in the RED state
                color.green = received; 
                //the received data is stored in the type green of a struct holding colors
                status++; 
                data_received = 0;
                Reset_Timer();
            }
        
            else if (data_received == 1 && status == GREEN){ 
                //if a data is received and we are in the GREEN state
                color.blu = received; 
                //the received data is stored in the type blu of a struct holding colors
                status++; 
                data_received = 0; 
                Reset_Timer();
            }
        
            else if (data_received == 1 && status == BLU){ 
                //if a data is received and we are in the BLU state we have to check the value of received 
                if (received == 192){ 
                    status++;
                    Reset_Timer();
                } 
                //if received is equal to 192, then we increment the status passing in TAIL state
            }
        }
        
        if (status == TAIL){
            //when we receive the entire sequence we can  switch on the RGB Led
            RGBLed_WriteColor(color);
            status = IDLE;
            data_received = 0;
            Reset_Timer();
        }
        
        else if (data_received == 1 && status == TIMER_CONFIG){ 
            //In this state the configuration of the new timeout condition is performed 
            //We can set the new timeout only if the data coming from the UART are in the admissible range [1;20] 
            if (received>=1 && received<=20){
                //new timeout condition
                max_value = received; 
                //the received data represent the value of timeout in seconds
                status++; 
                //the status is increased in order to enter in the END_CONFIGURATION state
                data_received = 0; 
            }
            else {
                //if the value is not admissible we chose to come back to the IDLE state
                status= IDLE;
            }
                
        }
        
        else if (data_received == 1 && status == TIMER_ENDCONFIG){ 
            //if a data is received and we are in the END_CONFIGURATION state and it is necessary to send again 161 to proceed with the timeout configuration.
            if (received == 192){
                status = IDLE;
                data_received = 0;
            } 
            //if the received data is 192, then timer configuration is ended and we return to IDLE state
            else {
                status = IDLE; 
                //if any other data is received, we have decided to come back to the IDLE state and it is necessary to send again 161 to proceed with the timeout configuration.
            }
        }
    }
}

/* [] END OF FILE */
