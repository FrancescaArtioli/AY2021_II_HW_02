/* 
 * File main.c
 * Project GROUP_02: the project aims to control the color of a RGB LED through a serial port.
 *
 * Code Description: when the project is first powered and programmed, the RGB LED is ON with black 
 * color. Then, we are in the IDLE state. Every time a byte is received, an interrupt (UART) is triggered.
 * The timer is configured as to trigger an interrupt every 1 second. It is configured as UDB in order
 * to correctly use the function Timer_RGB_WriteCounter(), which also requires to Stop the Timer before
 * calling it. For simplicity, we have written a function which reset the Timer everytime is needed. 
 * For a better undertsanding of the code, see further comments below.
 *
 * Note 1: In order to send just one byte in HEX we have used the tool 'Send string' on CoolTerm, which
 * can be found under 'Connection' menu.
 * Note 2: The code is thought as to enter in different status when a given condition is met. In particular,
 * when we are in the HEADER state we receive and store the RED byte, where we already are in the RED state
 * we receive and store the GREEN value and so on. 
 *
 * Authors: Monica Loddo, Francesca Artioli.
*/

/*First we include all the header files, containg the declaration of the functions we need 
 to call in the main file.*/
#include "project.h"
#include "InterruptRoutines.h"
#include "RGBLedDriver.h"
#include "stdio.h"
#include "TimerReset.h"

/*Defining the balck color in RGB and a struct holding colors.*/
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
    
    /*Defining and initializing a variable timeout_value, which defines the seconds of timeout: default 5s.
     We define also another variable needed to hold the time_out value.*/
    uint8_t timeout_value = 5;
    uint8_t received_timeout_value = 0;
    
    /*When the system is powered after programming, the LED is ON with color black.*/
	RGBLed_WriteColor(BLACK);

	for (;;)
	{   
        //TIMEOUT CONFIGURATION
        if (data_received == 1 && status == TIMER_CONFIG){ 
            //We can set the new timeout only if the data coming from the UART are in the admissible range [1-20].
            if (received >= 1 && received <= 20){
                received_timeout_value = received; 
                status++; 
                //The status is increased in order to enter in the END_CONFIGURATION state.
                data_received = 0; 
            }
            else {
                status= IDLE;
                //If the value is not admissible we chose to come back to the IDLE state.
            }   
        }
         else if (data_received == 1 && status == TIMER_ENDCONFIG){ 
            if (received == PACKET_TAIL){
                timeout_value = received_timeout_value;
                status = IDLE;
                data_received = 0;
            } 
            //If the received data is 192, then timer configuration is ended and we return to IDLE state.
            else {
                status = IDLE; 
                //If any other data is received, we have decided to come back to the IDLE state and it is necessary to send again 161 to proceed with the timeout configuration.
            }
        }
        
        //CONNECTION COMMAND
        else if (status == CONNECTION_COMMAND){
            sprintf(message, "RGB LED Program $$$");
            UART_RGB_PutString(message);
            status = IDLE;
        }
        
        //TIMEOUT CONDITION AND COLOR CONFIGURATION
        if (count == timeout_value){
            status = IDLE;
        }
        else {
            if (data_received == 1 && status == HEADER){ 
                //If a data is received and we are in the HEADER state the received data is stored in the type red of a struct holding colors.
                color.red = received; 
                status++;
                data_received = 0;
                Reset_Timer();
            }
            else if (data_received == 1 && status == RED){ 
                //If a data is received and we are in the RED state the received data is stored in the type green of a struct holding colors.
                color.green = received; 
                status++; 
                data_received = 0;
                Reset_Timer();
            }
            else if (data_received == 1 && status == GREEN){ 
                //If a data is received and we are in the GREEN state the received data is stored in the type blu of a struct holding colors.
                color.blu = received; 
                status++; 
                data_received = 0;
                Reset_Timer();
            }
            else if (data_received == 1 && status == BLU){ 
                //If a data is received and we are in the BLU state we have to check the value of received.
                //If received is equal to 192, then we increment the status passing in TAIL state.
                if (received == PACKET_TAIL){ 
                   RGBLed_WriteColor(color);
                   data_received = 0;
                   status = IDLE;
                } 
            }
        }
    }
}

/* [] END OF FILE */
