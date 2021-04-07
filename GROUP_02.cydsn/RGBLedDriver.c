/* ========================================
 * \file RGBLedDriver.c 
 * ========================================
*/
#include "project.h"
#include "RGBLedDriver.h"

extern volatile Color color;

//functions to write colors on RGB led
static void RGBLed_WriteRed(uint8_t red);
static void RGBLed_WriteGreen(uint8_t green);
static void RGBLed_WriteBlu(uint8_t blu);

//Function to start RGB Led
void RGBLed_Start()
{
    PWM_RG_Start();
    PWM_B_Start();
}

//Function to stop RGB Led
void RGBLed_Stop()
{
    PWM_RG_Stop();
    PWM_B_Stop();
}

//Function to assign the new color to the RGB Led
void RGBLed_WriteColor(Color color)
{
    RGBLed_WriteRed(color.red);
    RGBLed_WriteGreen(color.green);
    RGBLed_WriteBlu(color.blu);
}

//Function to assign a new value to the red channel of the RGB Led
static void RGBLed_WriteRed(uint8_t red)
{
    PWM_RG_WriteCompare1(red);
}

//Function to assign a new value to the green channel of the RGB Led
static void RGBLed_WriteGreen(uint8_t green)
{
    PWM_RG_WriteCompare2(green);
}

//Function to assign a new value to the blue channel of the RGB Led
static void RGBLed_WriteBlu(uint8_t blu)
{
    PWM_B_WriteCompare(blu);
}

/* [] END OF FILE */
