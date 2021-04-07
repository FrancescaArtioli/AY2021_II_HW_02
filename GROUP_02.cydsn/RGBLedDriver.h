/* 
 * File RGBLedDriver.h
 * 
*/

#ifndef __RGB_LED_DRIVER_H__
    #define __RGB_LED_DRIVER_H__
    
    //Include project header file
    
    #include "project.h"
    
    //Struct holding color data
    typedef struct {
        uint8_t red;
        uint8_t green;
        uint8_t blu;
    } Color;
    
    //Start Driver
    void RGBLed_Start();
    
    //Stop Driver
    void RGBLed_Stop();
    
    //Update current color of the RGB LED
    void RGBLed_WriteColor(Color c);
    
#endif

/* [] END OF FILE */
