/*
 * File:   lOGIC_CAL.c
 * Author: nijanthan.v
 *
 * Created on July 8, 2017, 10:48 AM
 */


#include <xc.h>
#include "SLIP_CALCULATIONS.h"
#include "RPM_Measurement.h"
#include "ERROR_HANDLING.h"
#include "state.h"
#include "UART.h"
#include "Initialization.h"

void Rotor_Slip_Cal (void)
{
    Temp = (Generator_RPM_FLT / TURBINE_2_WHEEL_RATIO);
    Rotor_slip_1 = (Turbine_RPM -  Temp) / Temp;
    Rotor_slip = Rotor_slip_1 * 100;
}

void Motor_Slip_Cal (void)
{
    if(Turbine_state == RAMPUP_STATE)
    {
        Mot_Frequency = Desired_Frequency;
    }
    if(Turbine_state == RUNNING_STATE)
    {
        Mot_Frequency = 50;//Frequency;
    }
    Gen_Theory = 120 * Mot_Frequency / NO_OF_POLE; 
    
    Motor_slip_1 = (Generator_RPM_FLT - Gen_Theory)/Gen_Theory;
    Motor_slip = Motor_slip_1 * 100;
}

void Ramp_Up_Slip (void)
{
    if(Rotor_slip > ROTOR_SLIP_PERCENTAGE && Motor_slip > MOTOR_SLIP_PERCENTAGE)
    {
        Slip_Flag = 1;
    }
    if(Rotor_slip <= ROTOR_SLIP_PERCENTAGE || Motor_slip <= MOTOR_SLIP_PERCENTAGE)
    {
        Slip_Flag = 0;
    }
}

void Ramp_Up_Slip_Error_Trigger (void)
{
    if(Rotor_slip < ROTOR_SLIP_PERCENTAGE)
    {
        Slip_Error_Counter++;
    }
    if(Rotor_slip >= ROTOR_SLIP_PERCENTAGE)
    {
        Slip_Error_Counter = 0;
    }
    if(Slip_Error_Counter >= SLIP_ERROR_TIME_DELAY)
    {
        Slip_Error_Counter = 0;
        Rotor_Slip_Error_Flag = 1;
        if(Rotor_slip < ROTOR_SLIP_PERCENTAGE)
        {
            Errors = ROTOR_SLIP;
        }
    }
    
    
    if(Motor_slip < MOTOR_SLIP_PERCENTAGE)
    {
        Slip_Error_Counter_1++;
    }
    if(Motor_slip >= MOTOR_SLIP_PERCENTAGE)
    {
        Slip_Error_Counter_1 = 0;
    }
    if(Slip_Error_Counter_1 >= SLIP_ERROR_TIME_DELAY)
    {
        Slip_Error_Counter_1 = 0;
        Motor_Slip_Error_Flag = 1;
        if(Motor_slip < MOTOR_SLIP_PERCENTAGE)
        {
            Errors = MOTOR_SLIP;
        }
    }
}