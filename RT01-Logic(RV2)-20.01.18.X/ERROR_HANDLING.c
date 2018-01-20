/*
 * File:   ERROR_HANDLING.c
 * Author: nijanthan.v
 *
 * Created on April 27, 2017, 9:49 AM
 */


#include <xc.h>
#include "ERROR_HANDLING.h"
#include "state.h"
#include "RPM_Measurement.h"
#include "Initialization.h"
#include "stdio.h"
#include "OneSecond_Function.h"
#include "ISR.h"
#include "UART.h"
#include "RAMP_UP.h"
#include "SLIP_CALCULATIONS.h"
#include "Power_Meter.h"
#include "RS485_COMMUNICATION.h"
#include "EEPROM.h"

state_h Turbine_state;

void Error_Scan_start_up (void)
{
    if(EEPROM_Error_Flag == 1 || Feedback_Error == 1 || Grid_Over_current == 1 || VFD_communication_Error_Flag == 1 ||  Start_Stop_Flag == 1 || Grid_Und_voltage==1 || Wind_Cut_In_Flag ==0 || Grid_Phase_Sequence_Error == 1 || Grid_Frequency_Error == 1 || Wind_Cut_Out_Flag == 1 || Grid_Ovr_voltage  == 1)
    {
        Start_up_Error = 1;
        Initial_Delay_Second = 0;
        RA5 = 1;    //Logic error io to VFD
    }
    if(EEPROM_Error_Flag == 0 && Feedback_Error == 0 && Gen_EP_Err_Flag == 0 && Pitch_EP_Err_Flag == 0 && Grid_Over_current == 0 && VFD_communication_Error_Flag == 0 && Start_Stop_Flag == 0 && Grid_Und_voltage == 0 && Wind_Cut_In_Flag == 1 && Grid_Phase_Sequence_Error == 0 && Grid_Frequency_Error == 0 && Wind_Cut_Out_Flag == 0 && Grid_Ovr_voltage == 0)
    {
        Initial_Delay_Second++;
        RA5 = 0;
        Errors = NO_ERROR; 
        if(Initial_Delay_Second == INITIAL_DELAY)
        {
            Initial_Delay_Second = 0;
            Start_up_Error = 0;
        }
    }
}
void Error_Scan_Ramp_up (void)
{
    if(EEPROM_Error_Flag == 1 || VFD_communication_Error_Flag == 1 || Start_Stop_Flag == 1 || Pitch_FB_Error_Flag == 1 || VFD_DC_EXTREM_LOW_Error == 1 || VFD_SHORT_CIRCUIT_fLAG == 1 || Turbine_Over_Speed_Flag == 1 || VFD__Run_Time_Error == 1 || VFD_DC_Bus_Low_Error == 1 || VFD_DC_Bus_High_Error == 1 || VFD_Error_Flag == 1 || VFD_DC_Bus_Current_Error == 1 || Motor_Slip_Error_Flag == 1 || Rotor_Slip_Error_Flag == 1 ||  Grid_Over_current == 1 )
    {
        VFD_RAMP = VFD_Stop;
        //EEPROM Error//
        if(VFD__Run_Time_Error == 1 || VFD_DC_EXTREM_LOW_Error == 1 || Motor_Slip_Error_Flag == 1 || Rotor_Slip_Error_Flag == 1 || Pitch_FB_Error_Flag == 1 || VFD_SHORT_CIRCUIT_fLAG == 1)
        {
            EEPROM_Error_Stop();
        }
        ////////////////
    }
}
void Error_Scan_Running (void)
{
    if(EEPROM_Error_Flag == 1 || VFD_communication_Error_Flag == 1 || Start_Stop_Flag == 1 || Generator_One_Feedback_Error == 1 || Pitch_FB_Error_Flag == 1 || Tur_OverLoaded_Error == 1 || KW_Minimum_Error == 1 || KW_Maximum_Error == 1 || Turbine_Under_Speed_Flag == 1 || Turbine_Over_Speed_Flag == 1 || Grid_Over_current == 1 || Generator_Over_Speed == 1 || Turbine_Over_Speed_Flag == 1 ||  Grid_Und_voltage == 1 || Wind_Cut_Out_Flag == 1 && Grid_Phase_Sequence_Error == 0 || Grid_Frequency_Error == 1 || Grid_Ovr_voltage  == 1)
    {
        Turbine_state = STOPPING_STATE;
        //EEPROM Error//
        if(Generator_One_Feedback_Error == 1 || Pitch_FB_Error_Flag == 1 || Tur_OverLoaded_Error == 1)
        {
            EEPROM_Error_Stop();
        }
        ////////////////
        Stopping_state_function();
    }
}
void Error_Checking_Interrupt_Overflow (void)
{    
    Capacitor_Adding();
    VFD_IO_Error();
}
void Error_Checking_One_Second (void)
{
    if(Turbine_state == STARTUP_STATE)
    {
        Wind_Speed_Error_Trigger();        
        VFD_PS_ON_Function();
        Pitch_PS_ON_Function();        
        Grid_UV();
        Grid_OV();
        Grid_Frequency();
        DC_Bus_Voltage();
        Grid_Phase_Sequence();
        Turbine_Restore_Check();
        Start_Stop();
        Communication_Error();
        Grid_Over_Current(); 
    }
    if(Turbine_state == RUNNING_STATE)
    {
        VFD_PS_ON_Function();
        Wind_Speed_Error_Trigger();        
        Turbine_Under_speed();
        Generator_RPM();        
        Rotor_Slip_Cal();
        Motor_Slip_Cal();        
        Pitch_Feedback();
        Generator_One_Feedback();
        Start_Stop();
        Communication_Error();
        Turbine_Over_Speed(); 
        
        //Initial Five Second Delay//
        if(Five_Second_flag)
        {
            Turbine_OverLoaded_Error();               
            Grid_Over_Current();
            Grid_UV();
            Grid_OV();
            Grid_Frequency();
            Grid_Minimum_Power();
            Grid_Maximum_Power();
        }
        
    }    
    if(Turbine_state == RAMPUP_STATE)
    {
        DC_Bus_Voltage();
        Rotor_Slip_Cal();
        Motor_Slip_Cal();
        Ramp_Up_Slip();
        Pitch_Feedback();
        if(Ten_Sec_RampUp_Flag)
        {
            Ramp_Up_Slip_Error_Trigger();
            VFD_Run_Time_Error();
            Turbine_Over_Speed();
            Grid_Over_Current(); 
        }
        Start_Stop();
        Communication_Error();
    }
}
void Last_Five_Error (void)
{
    
    if(Errors != Errors1)
    {
        Errors5 = Errors4;
        Errors4 = Errors3;
        Errors3 = Errors2;
        Errors2 = Errors1;
        Errors1 = Errors;
    }
    
}
void Turbine_Restore_Check (void)
{
    if(Turbine_RPM > 5 || Generator_RPM_FLT > 100)
    {
        Turbine_Restore_Error = 1;
        Errors = TURBINE_NR;
    }
    if(Turbine_RPM <= 5 && Generator_RPM_FLT <= 100)
    {
        Turbine_Restore_Error = 0;
    }
    
}
void Wind_Speed_Error_Trigger (void)
{    
    if(Turbine_state == STARTUP_STATE)
    {
        if(Wind_Speed_Avg >= CUT_IN_WIND)
        {
                Wind_Cut_In_Flag = 1;        
        }
        else if(Wind_Speed_Avg < CUT_IN_WIND)
        {
            Wind_Cut_In_Flag = 0;
            Errors = WS_MIN_MAX;
        }
    }
    
    if(Turbine_state == STARTUP_STATE)
    {
        if(Wind_Speed_Avg >= CUT_Out_WIND)
        {
            Wind_Cut_Out_Counter++;
            if(Wind_Cut_Out_Counter >= 1)
            {
                Wind_Cut_Out_Flag = 1;       //Flag to Trigger Error
                Wind_Cut_Out_Counter  = 0;
                Errors = WS_MIN_MAX;
            }            
        }
        else if(Wind_Speed_Avg < CUT_Out_WIND)
        {
            Wind_Cut_Out_Flag = 0;
            Wind_Cut_Out_Counter = 0;
        }
    }
    if(Turbine_state == RUNNING_STATE)
    {
        if(Wind_Speed_Avg >= CUT_Out_WIND)
        {
            Wind_Cut_Out_Counter++;
            if(Wind_Cut_Out_Counter >= 10)
            {
                Wind_Cut_Out_Flag = 1;       //Flag to Trigger Error
                Wind_Cut_Out_Counter  = 0;
                Errors = WS_MIN_MAX;
            }            
        }
        else if(Wind_Speed_Avg < CUT_Out_WIND)
        {
            Wind_Cut_Out_Flag = 0;
            Wind_Cut_Out_Counter = 0;
        }
    }
    
}


void Grid_UV (void)
{
    if(Turbine_state == STARTUP_STATE)
    {
        if(R_Volt <= UNDER_VOLTAGE_LIMIT || Y_Volt <= UNDER_VOLTAGE_LIMIT || B_Volt <= UNDER_VOLTAGE_LIMIT)
        {
            Grid_UV_Counter++;
            if(Grid_UV_Counter >= 2)
            {
                Grid_UV_Counter = 0;
                Grid_Und_voltage  = 1;
                Errors = VOLT_LOW;
            }
            else
            {
                Grid_Und_voltage = 0;
            }
        }
        else
        {
            Grid_Und_voltage = 0;
            Grid_UV_Counter = 0;
        }
    }
    if(Turbine_state == RUNNING_STATE)
    {
        if(R_Volt <= UNDER_VOLTAGE_LIMIT || Y_Volt <= UNDER_VOLTAGE_LIMIT || B_Volt <= UNDER_VOLTAGE_LIMIT)
        {
            Grid_UV_Counter++;
            if(Grid_UV_Counter >= 10)
            {
                Grid_UV_Counter = 0;
                Grid_Und_voltage  = 1;
                Errors = VOLT_LOW;
            }
            else
            {
                Grid_Und_voltage = 0;
            }
        }
        else
        {
            Grid_Und_voltage = 0;
            Grid_UV_Counter = 0;
        }
    }
    
}
void Grid_OV (void)
{
    if(Turbine_state == STARTUP_STATE)
    {
        if(R_Volt >= OVER_VOLTAGE_LIMIT || Y_Volt >= OVER_VOLTAGE_LIMIT || B_Volt >= OVER_VOLTAGE_LIMIT)
        {
            Grid_Ov_Counter++;
            if(Grid_Ov_Counter >= 2)
            {
                Grid_Ov_Counter = 0;
                Grid_Ovr_voltage  = 1;
                Errors = VOLT_HIGH;
            }
            else
            {
                Grid_Ovr_voltage = 0;
            }
        }
        else
        {
            Grid_Ovr_voltage = 0;
            Grid_Ov_Counter = 0;
        }
    }
    if(Turbine_state == RUNNING_STATE)
    {
        if(R_Volt >= OVER_VOLTAGE_LIMIT || Y_Volt >= OVER_VOLTAGE_LIMIT || B_Volt >= OVER_VOLTAGE_LIMIT)
        {
            Grid_Ov_Counter++;
            if(Grid_Ov_Counter >= 10)
            {
                Grid_Ov_Counter = 0;
                Grid_Ovr_voltage  = 1;
                Errors = VOLT_HIGH;
            }
            else
            {
                Grid_Ovr_voltage = 0;
            }
        }
        else
        {
            Grid_Ovr_voltage = 0;
            Grid_Ov_Counter = 0;
        }
    }
    
}

void Turbine_Over_Speed (void)
{
    if(Turbine_RPM >= TURBINE_OVER_SPEED_LIMIT)
    {
        TRPM_OverSpeed_Counter++;
        if(TRPM_OverSpeed_Counter >= 2)
        {
            TRPM_OverSpeed_Counter = 0;
            Turbine_Over_Speed_Flag = 1;
            Errors = TURBINE_US_OS;
        }
        
    }
    else
    {
        Turbine_Over_Speed_Flag = 0;
        TRPM_OverSpeed_Counter = 0;
    }        
}
void Turbine_Under_speed (void)
{
    if(Turbine_RPM < TURBINE_UNDER_SPEED_LIMIT)
    {
        TRPM_Under_Speed_Counter++;
        if(TRPM_Under_Speed_Counter >= 10)
        {
            TRPM_Under_Speed_Counter = 0;
            Turbine_Under_Speed_Flag = 1;
            Errors = TURBINE_US_OS;
        }
        else
        {
            Turbine_Under_Speed_Flag = 0;
        }
    }
    else
    {
        TRPM_Under_Speed_Counter = 0;
        Turbine_Under_Speed_Flag = 0;
    }
}
void Grid_Frequency (void)
{
    if(Frequency <= FREQUENCY_LOW_LIMIT || Frequency >= FREQUENCY_HIGH_LIMIT)
    {
        Frequency_Error_counter++;
        if(Frequency_Error_counter >= 5)
        {
            Frequency_Error_counter = 0;
            Grid_Frequency_Error = 1;
            Errors = FREQ;
        }
        else
        {
            Grid_Frequency_Error = 0;
        }
    }
    else
    {
        Frequency_Error_counter = 0;
        Grid_Frequency_Error = 0;
    }
}

void Grid_Over_Current (void)
{
    if( (Turbine_state == RAMPUP_STATE) || (Turbine_state == RUNNING_STATE) )
    {
        if(R_Curr >= GRID_OVER_CURRENT_LIMIT || Y_Curr >= GRID_OVER_CURRENT_LIMIT || B_Curr >= GRID_OVER_CURRENT_LIMIT)
        {
            OV_Counter++;
            if(OV_Counter == 1)
            {
                OV_Counter = 0;
                Grid_Over_current = 1;
                Errors = CURRENT_H;
            }
            
        }
        else
        {
            Grid_Over_current  = 0;
            OV_Counter = 0;
        }
    }
    if(Turbine_state == STARTUP_STATE)
    {
        if(R_Curr >= MEASUREMENT_ERROR_CURRENT_LIMIT || Y_Curr >= MEASUREMENT_ERROR_CURRENT_LIMIT || B_Curr >= MEASUREMENT_ERROR_CURRENT_LIMIT)
        {
            Grid_Over_current = 1;
            Errors = MEAURE_ERR;
        }
        else
        {
            Grid_Over_current  = 0;
        }
    }
    
}

void Generator_RPM (void)
{   
    if(Generator_RPM_FLT >= GENERATOR_OVER_SPEED_LIMIT)
    {
        G_RPM_Counter++;
        if(G_RPM_Counter >= 10)
        {
            G_RPM_Counter = 0;
            Generator_Over_Speed = 1;
            Errors = GEN_OS;
        }
    }
    else
    {
        G_RPM_Counter = 0;
        Generator_Over_Speed = 0;
    }
}

void Grid_Minimum_Power (void)
{
    if(KW <= MINIMUM_KW)
    {
        KW_Counter_Max++;
        if(KW_Counter_Max >= 60)
        {
            KW_Counter_Max = 0;
            KW_Minimum_Error = 1;
            Errors = POWER_MIN;
        }
        else
        {
            KW_Minimum_Error = 0;
        }
    }
    else
    {
        KW_Minimum_Error  =0;
        KW_Counter_Max = 0;
    }
}
void Grid_Maximum_Power (void)
{
    if(KW >= MAXIMUM_KW)
    {
        KW_Counter++;
        if(KW_Counter >= 30)
        {
            KW_Counter = 0;
            KW_Maximum_Error = 1;
            Errors = POWER_MAX;
        }
        else
        {
            KW_Maximum_Error  =0;
        }
    }
    else
    {
        KW_Counter = 0;
        KW_Maximum_Error = 0;
    }
}
void Turbine_OverLoaded_Error (void)
{
    if(KW <= TURBINE_OVERLOADED_SET_LIMIT)
    {
        T_Overload_counter++;
        if(T_Overload_counter >=3 )
        {
            T_Overload_counter = 0;
            Tur_OverLoaded_Error = 1;
            Errors = TURBINE_OL; 
        }
        else
        {
            Tur_OverLoaded_Error = 0;
        } 
    }
    else
    {
        Tur_OverLoaded_Error = 0;
        T_Overload_counter = 0;
    }
}
void Grid_Phase_Sequence (void)
{
    if(Phase_Sequence_Ok == 1)
    {
        Grid_Phase_Sequence_Error = 0;
    }
    else if(Phase_Sequence_Ok == 0)
    {
        Grid_Phase_Sequence_Error = 1;
        Errors = PHASE_SEQ;
    }
}
void DC_Bus_Voltage (void)
{   
    if(VFD_Error_No == 3)
    {
        DC_BUS_Low_Counter++;
        if(DC_BUS_Low_Counter >= 1)
        {
            DC_BUS_Low_Counter = 0;
            Errors = DCB_L_H;
            VFD_DC_Bus_Low_Error = 1;
            DC_Bus_Voltage_Flag = 0;
        }
    }
    if(VFD_Error_No == 7)
    {
            Errors = DC_EXT_LOW;
            VFD_DC_EXTREM_LOW_Error = 1;
            DC_Bus_Voltage_Flag = 0;
    }
    if(VFD_Error_No == 3)
    {
        DC_BUS_High_Counter++;
        if(DC_BUS_High_Counter >= 1)
        {
            DC_BUS_High_Counter = 0;
            Errors = DCB_L_H;
            VFD_DC_Bus_High_Error = 1;
            DC_Bus_Voltage_Flag = 0;
        }
    }
    if(VFD_Error_No == 8)
    {
        DC_BUS_Current_Counter++;
        if(DC_BUS_Current_Counter >= 1)
        {
            DC_BUS_Current_Counter = 0;
            Errors = VFD_OC;
            VFD_DC_Bus_Current_Error = 1;
            DC_Bus_Voltage_Flag = 0;
        }
    }
    if(VFD_Error_No == 6)
    {
        Errors = VFD_SHORT_CIRCUIT;
        VFD_SHORT_CIRCUIT_fLAG = 1;
        DC_Bus_Voltage_Flag = 0;
    }
    if(VFD_Error_No == 0)
    {
        VFD_DC_Bus_High_Error = 0;
        VFD_DC_Bus_Low_Error = 0;
        VFD_SHORT_CIRCUIT_fLAG = 0;
        VFD_DC_Bus_Current_Error  = 0;
        DC_Bus_Voltage_Flag = 1;
    }
        
}
  
void Turbine2Wheel_Ratio (void)
{
    if(lc_Avg_Counter < 299)
    {
        lc_Avg_Counter = 0;
        Turbine2Wheel_Ratio_Avg = Gf_Turbine2Wheel_Ratio + Turbine2Wheel_Ratio_Avg;
    }
    else if(lc_Avg_Counter == 300)
    {
        if(Turbine2Wheel_Ratio_Avg >= 8)
        {
            Gc_Turbine2Wheel_Ratio_Error = 1;
            lc_Avg_Counter  = 0;
        }
        else
        {
            Gc_Turbine2Wheel_Ratio_Error = 0;
            lc_Avg_Counter  = 0;
        }
    }
    else
    {
        Gc_Turbine2Wheel_Ratio_Error = 0;
    }
}

void Turbine_RPM_Checking_Rampup (void)  //To Set limit for T.RPM Increase in Ramp-up
{
    lc_Previous_T_RPM = lc_Current_T_RPM;
    Turbine_RPM = lc_Current_T_RPM;
    lc_T_RPM = lc_Current_T_RPM - lc_Previous_T_RPM;
    if(lc_T_RPM >= 5)
    {
        Gc_TRPM_Rampup_Error = 1;
    }
    else
    {
        Gc_TRPM_Rampup_Error  = 0;
    }
}
void VFD_Run_Time_Error (void)
{
    VFD_Run_Time_Counter++;
    if(VFD_Run_Time_Counter >= VFD_RUN_TIME_SECOND)
    {
        VFD_Run_Time_Counter = 0;
        VFD__Run_Time_Error = 1;
        Errors = VFD_RUN_TIME;
    }
    else if(VFD_Run_Time_Counter < VFD_RUN_TIME_SECOND)
    {
        VFD__Run_Time_Error = 0;
    }
}
void Pitch_Feedback (void)
{ 
    if(RB1 == 0 && RB0 == 1)
    {
        Pitch_FB_Error_counter++;
        if(Pitch_FB_Error_counter >= 5)
        {
            Pitch_FB_Error_counter = 0;
            Pitch_FB_Error_Flag = 1;
            Errors = PITCH_FB;
            int_eeprom_write(PITCH_FB_EP_ADD,1);
        }
    }
    else if(RB1 == 1 && RB0 == 1)
    {
        Pitch_FB_Error_counter = 0;
        Pitch_FB_Error_Flag = 0;
        int_eeprom_write(PITCH_FB_EP_ADD,0);
    }
}
void Generator_One_Feedback (void)
{     
    if(RB2 == 0 && RD2 == 1 )        //if contactor connected 
    {
        Generator_One_Feedback_Error = 0;
        Generator_One_Counter = 0;
        int_eeprom_write(GENERATOR_FB_EP_ADD,0);
    }
    else if(RB2 == 1 && RD2 == 1)   //if contactor Not connected 
    {
        Generator_One_Counter++;
        if(Generator_One_Counter > 2)
        {
            Generator_One_Counter  = 0;
            Generator_One_Feedback_Error = 1;
            Errors = GEN_FB;
            int_eeprom_write(GENERATOR_FB_EP_ADD,1);
        } 
    }
}
void VFD_IO_Error (void)
{
    if(RC5 == 1)
    {
        VFD_Error_Flag = 1;
        Errors = VFD_ERROR_IO;
    }
    else
    {
        VFD_Error_Flag = 0;
    }
}
void Start_Stop (void)
{
    if(RE1 == 1)
    {
        Key_Counter++;
        if(Key_Counter >= 3)
        {
            Key_Flag = 1;
            Key_Counter = 0;
        }
    }
    if(RE1 == 0 && Start_Stop_Flag == 0 && Key_Flag == 1)
    {
        S_S_Counter++;
        if(S_S_Counter >= 2)
        {
            S_S_Counter = 0;
            Start_Stop_Flag = 1;
            int_eeprom_write(START_STOP_KEY_ADD,1);
            Key_Flag = 0;
        }
        
    }
    else if(RE1 == 0 && Start_Stop_Flag == 1 && Key_Flag == 1)
    {
        S_S_Counter++;
        if(S_S_Counter >= 2)
        {
            S_S_Counter = 0;
            Start_Stop_Flag = 0;
            int_eeprom_write(START_STOP_KEY_ADD,0);
            Key_Flag = 0;
        }
        
    }
    
    //For LED//
    if(Start_Stop_Flag == 1)
    {   
        RE7 = ~RE7;
        Errors = MANUAL_STOP;        
    }
    else
    {        
        RE7 = 1;
    }
}