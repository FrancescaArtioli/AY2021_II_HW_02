/*
Function to reset the Timer.
We created a timer reset function in order to make more sliding the main.c code.
The function stops the timer, writes in the counter register the value 999, resets the count variable and starts again the timer.
We chose to write in the counter register 999 to guarantee that the timer starts counting from the first value.
*/

#include "project.h"
#include "TimerReset.h"

extern volatile uint8_t count;

void Reset_Timer(){
    Timer_RGB_Stop();
    Timer_RGB_WriteCounter(999);
    count = 0;
    Timer_RGB_Start();
}

/* [] END OF FILE */