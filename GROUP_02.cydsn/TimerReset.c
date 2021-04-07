/* ========================================
Function to reset the Timer
*/

/* [] END OF FILE */
#include "project.h"
#include "TimerReset.h"

extern volatile uint8_t count;

void Reset_Timer(){
Timer_RGB_Stop();
Timer_RGB_WriteCounter(999);
count=0;
Timer_RGB_Start();
}