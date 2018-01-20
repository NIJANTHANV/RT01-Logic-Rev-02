/*
 * File:   RAMP_UP.c
 * Author: nijanthan.v
 *
 * Created on June 30, 2017, 4:25 PM
 */
#include "state.h"
#include "RAMP_UP.h"
#include "ERROR_HANDLING.h"
#include "UART.h"
#include "SLIP_CALCULATIONS.h"
#include <xc.h>
#include "OneSecond_Function.h"
#include "RPM_Measurement.h"
#include "Initialization.h"
#include "RS485_COMMUNICATION.h"
#include "ISR.h"
#include<math.h>

#define _XTAL_FREQ 8000000

void RAMP_UP (void)
{
    switch (VFD_RAMP)
    {
        case VFD_IN:
            VFD_IN_ON;
            VFD_On_Off = 0;
            One_Sec_Delay_vab = 1;      //TO CREAT 1SEC DELAY TO ON VFD OUT
            if(One_sec_Delay_Flag)
            {
                VFD_RAMP = VFD_OUT;
                One_Sec_Delay_vab = 0;
                One_sec_Delay_Flag = 0;
            }
            break;
            
        case VFD_OUT:
            VFD_OUT_ON;
            if(DC_Bus_Voltage_Flag)
            {
               DC_Bus_Voltage_Flag  = 0;
               VFD_RAMP = VFD_Frequency_Step_up;
            }
            Desired_Frequency = DEFUALT_FREQUENCY;
            break;
            
        case VFD_Frequency_Step_up:
            VFD_On_Off = 1;
            if(DC_Bus_Voltage_Flag)
            {
                DC_Bus_Voltage_Flag  = 0;
//                Five_Sec_Delay_vab = 1;
//                if(Five_sec_Delay_Flag)
//                {
//                    Five_sec_Delay_Flag = 0;
//                    Five_Sec_Delay_vab = 0;
//                    Slip_Flag = 0;
//                    VFD_Freq_Step_up();
//                }
                if(Slip_Flag)
                {
                    Slip_Flag = 0;
                    VFD_Freq_Step_up();
                }
            }
            Pitch_Release();
            break;
            
        case GRID_Connect:
            VFD_IN_OFF;        /***Interlock between contact is must*******/
            VFD_On_Off = 0; //VFD PLUSE OFF
            One_Sec_Delay_vab = 1;      //TO CREAT 1SEC DELAY TO ON VFD OUT
            if(One_sec_Delay_Flag)
            {
                One_sec_Delay_Flag = 0;
                One_Sec_Delay_vab  = 0;
                VFD_OUT_OFF;
                __delay_ms(50);
                GRID_ON;
                Turbine_state = RUNNING_STATE;
                VFD_Data_Kill();
            }
            break;
            
        case VFD_Stop:
            VFD_On_Off = 0;
            Desired_Frequency = 0;
            Turbine_Pitching();
            VFD_IN_OFF;
            VFD_OUT_OFF;
            Turbine_state = STOPPING_STATE;            
            break;
    }
}
void VFD_Freq_Step_up (void)
{
    if(Desired_Frequency < 50)
    {
        Desired_Frequency++;
    }
    GENERATOR_RPM_THEORY = (120*50)/NO_OF_POLE  ; 
    TURBINE_RPM_THEORY = GENERATOR_RPM_THEORY / TURBINE_2_WHEEL_RATIO ;
    RAMP_UP_TURBINE_CUT_IN_RPM = (TURBINE_RPM_THEORY * 0.92) ;
    RAMP_UP_GENERATOR_CUT_IN_RPM = (GENERATOR_RPM_THEORY * 0.90) ;
    
    if( (Turbine_RPM >= RAMP_UP_TURBINE_CUT_IN_RPM)  && (Generator_RPM_FLT >= RAMP_UP_GENERATOR_CUT_IN_RPM) ) 
    {
        VFD_On_Off = 0;
        VFD_RAMP = GRID_Connect;
    }
}

void VFD_PS_ON_Function (void)
{
    if( (Initial_Delay_Second >= VFD_PS_DELAY) && (Turbine_state == STARTUP_STATE) )
    {
        VFD_PS_ON; VFD_ON_Flag = 1; 
    }
    else if( (Initial_Delay_Second < VFD_PS_DELAY) && (Turbine_state == STARTUP_STATE) && (VFD_Bus_Voltage < 50) )
    {
        VFD_PS_OFF;  VFD_ON_Flag = 0;
    }
    
    if( (VFD_Bus_Voltage < 50) && (Turbine_state == RUNNING_STATE) )
    {
        VFD_PS_OFF;  VFD_ON_Flag = 0;
    }
}
void VFD_Data_Kill (void)
{
    VFD_Frequency = 0;
    Desired_Frequency = 0;
    VFD_Run_Time_Counter = 0;
    Rotor_Slip_Error_Flag = 0;
    Motor_Slip_Error_Flag = 0;
    Slip_Error_Counter = 0;
    Slip_Error_Counter_1 = 0;
}
void Error_Flag_Kill (void)
{
    Two_Sec_Delay_vab = 0;
    Pitch_FB_Error_Flag = 0;
    VFD_DC_EXTREM_LOW_Error = 0;
    VFD_SHORT_CIRCUIT_fLAG = 0;
    Turbine_Over_Speed_Flag = 0;
    VFD__Run_Time_Error = 0 ;
    VFD_DC_Bus_Low_Error = 0; 
    VFD_DC_Bus_High_Error = 0; 
    VFD_Error_Flag = 0;
    VFD_DC_Bus_Current_Error = 0; 
    Grid_Over_current = 0;    
    Generator_One_Feedback_Error = 0;
    Tur_OverLoaded_Error = 0;
    KW_Minimum_Error = 0;
    KW_Maximum_Error = 0;
    Turbine_Under_Speed_Flag = 0;
    Generator_Over_Speed = 0;
    Grid_Und_voltage = 0;
    Grid_Ovr_voltage  = 0;
    Wind_Cut_In_Flag = 0; 
    Grid_Frequency_Error = 0;
    Wind_Cut_Out_Flag = 0;  
    Motor_slip = 0;
    Rotor_slip = 0;
    Data_1[1] = 0;
    Data_1[7] = 0;
    Data_1[9] = 0;
}