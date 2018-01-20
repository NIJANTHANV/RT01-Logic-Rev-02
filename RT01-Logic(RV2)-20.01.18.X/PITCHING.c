/*
 * File:   PITCHING.c
 * Author: nijanthan.v
 *
 * Created on July 10, 2017, 10:40 AM
 */


#include <xc.h>
#include "PITCHING.h"
#include "IO_Def.h"
#include "RTC.h"
#include "Initialization.h"
#include "RPM_Measurement.h"
#include "UART.h"
#include "ISR.h"
#include "state.h"
#include "ERROR_HANDLING.h"
#include "OneSecond_Function.h"
#include "Initialization.h"

void Pitch_Release (void)
{
    if(Turbine_state == RAMPUP_STATE)
    {
        if(Pitching_FlAG == 1)
        {
            Two_Sec_Delay_vab = 1;      //TO CREAT 1SEC DELAY TO ON VFD OUT
            if(Two_sec_Delay_Flag)
            {
                Two_Sec_Delay_vab = 0;
                Two_sec_Delay_Flag = 0;
                PITCH_ENABLE;
                Pitching_FlAG = 0; 
            }
        }
    }
}

void Turbine_Pitching (void)
{
    PITCH_DISABLE;
}
 
void Pitch_PS_ON_Function (void)
{
    if(Wind_Speed_Avg >= PITCH_PS_CUT_IN_WIND)
    {
        PITCH_PS_ON;
        Pitch_Ps_Counter = 0;
    }
    else
    {
        Pitch_Ps_Counter++;
        if(Pitch_Ps_Counter > PITCH_PS_OFF_DELAY)
        {
            Pitch_Ps_Counter = 0;
            PITCH_PS_OFF;
        }
    }
    
    
}