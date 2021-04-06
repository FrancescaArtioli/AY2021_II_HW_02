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
#include "project.h"
#include "InterruptRoutines.h"
#include "RGBLedDriver.h"
#include "stdio.h"

volatile uint8_t status = 0;
volatile uint8_t received = 0;
volatile uint8_t flag_header = 0;
volatile uint8_t flag_red = 0;
volatile uint8_t flag_green = 0;
volatile uint8_t flag_blu = 0;
volatile uint8_t flag_tail = 0;

const Color BLACK = {0, 0, 0};
volatile Color color;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_RGB_Start();
    isr_UART_StartEx(Custom_UART_RX_ISR);
    RGBLed_Start();
    status = IDLE;
    //char a = 0;
    
    RGBLed_WriteColor(BLACK);
    //static char message [20] = {'\0'};
    
    for(;;)
    {
        if (status == IDLE && flag_header == 0){
            /*if(a==0){
                sprintf(message, "IDLE\r\n");
                UART_RGB_PutString(message);
                a++;}*/
        }
    
        
        if (status == IDLE && flag_header == 1){
            if (received == 160){
                status = HEADER;
                //flag_header =0;
                
                /*if(a==1){
                sprintf(message, "HEADER\r\n");
                UART_RGB_PutString(message);
                a++;
                }*/
            }
            else
            {   //a = 0;
                status = IDLE;
                flag_header = 0;
            }
            
        }
        
        else if (flag_red == 1){
           
            color.red = received;
            status ++;
            flag_red = 0;
            
            /*if(a==2){
            sprintf(message, "RED: %i \r\n", color.red);
            UART_RGB_PutString(message);
            a++;}*/
        }
        
        else if (flag_green == 1){

            
            color.green = received;
            status ++;
            flag_green = 0;
            /*if(a==3){ 
            sprintf(message, "GREEN: %i \r\n", color.green);
            UART_RGB_PutString(message);
            a++;}*/        
        }
        
        else if (flag_blu == 1){

            color.blu = received;
            status ++;
            flag_blu = 0;
            /*if(a==4){ 
            sprintf(message, "BLUE: %i \r\n", color.blu);
            UART_RGB_PutString(message);
            a++;}*/          
        }
        
        else if (flag_tail == 1){
            if (received == 192){
                /*if(a==5){
                sprintf(message, "TAIL CORRETTA, LED ACCESO\r\n");
                UART_RGB_PutString(message);
                a++;}*/
                RGBLed_WriteColor(color);
                
                //a = 0;
                status = IDLE;
                flag_header = 0;
                flag_red = 0;
                flag_green = 0;
                flag_blu = 0;
                flag_tail = 0;
            }
            else
            {   //a = 4;
                status = BLU;
            }
        }    
    }
}

/* [] END OF FILE */
