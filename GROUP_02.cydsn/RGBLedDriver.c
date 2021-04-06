/* ========================================
 * \file RGBLedDriver.c 
 * ========================================
*/
#include "project.h"
#include "RGBLedDriver.h"

extern volatile Color color;

static void RGBLed_WriteRed(uint8_t red);
static void RGBLed_WriteGreen(uint8_t green);
static void RGBLed_WriteBlu(uint8_t blu);

void RGBLed_Start()
{
    PWM_RG_Start();
    PWM_B_Start();
}

void RGBLed_Stop()
{
    PWM_RG_Stop();
    PWM_B_Stop();
}

void RGBLed_WriteColor(Color color)
{
    RGBLed_WriteRed(color.red);
    RGBLed_WriteGreen(color.green);
    RGBLed_WriteBlu(color.blu);
}

static void RGBLed_WriteRed(uint8_t red)
{
    PWM_RG_WriteCompare1(red);
}

static void RGBLed_WriteGreen(uint8_t green)
{
    PWM_RG_WriteCompare2(green);
}

static void RGBLed_WriteBlu(uint8_t blu)
{
    PWM_B_WriteCompare(blu);
}

/* [] END OF FILE */
