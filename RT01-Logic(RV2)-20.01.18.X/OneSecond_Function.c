/*
 * File:   OneSecond_Function.c
 * Created on April 17, 2017, 5:51 PM
 */


#include <xc.h>
#include "OneSecond_Function.h"
#include "RPM_Measurement.h"
#include "Initialization.h"
#include "UART.h"
#include "stdlib.h"
#include "state.h"
#include "stdio.h"
#include "ISR.h"
#include "UART.h"
#include "RAMP_UP.h"
#include "ERROR_HANDLING.h"
#include "EEPROM.h"

#define _XTAL_FREQ 8000000
void Timer0_OneSecond_Function(void)
{
    
    ///*********RS485*VFD Received Data*********************///zzz
    if(Data_1[8] == 0x40)
    {
        VFD_RS485_Data();
    }  
    VFD_RS485_Data_filter();
    //////////////////////////////////////////////////////        
    Error_Checking_One_Second();
    //****START UP ONE SECOND FUNCTION ***********/
    if(Turbine_state == STARTUP_STATE)
    {
        Turbine_Start_up_1_Second();        
    }
    //****RAMP UP ONE SECOND FUNCTION ***********/
    if(Turbine_state == RAMPUP_STATE)
    {
        Turbine_Ramp_up_1_Second();        
    }
    //****RUNNING ONE SECOND FUNCTION ***********/
    if(Turbine_state == RUNNING_STATE)
    {
        Error_Scan_Running();  
        Two_Sec_Delay();    
    }  
    /********************************************/
    if(Turbine_state == STOPPING_STATE)
    {
        Stopping_state_function();        
    } 
    ///***Rampup 10Sec Delay***///
    if(Timer0_RAMPUP_Counter < RAMPUP_INITIAL_DELAY && Turbine_state == RAMPUP_STATE)
    {
        Timer0_RAMPUP_Counter++;   
    }
    else if(Turbine_state != RAMPUP_STATE )
    {
        Ten_Sec_RampUp_Flag = 0;
        Timer0_RAMPUP_Counter = 0;
    }
    if(Timer0_RAMPUP_Counter == RAMPUP_INITIAL_DELAY && Turbine_state == RAMPUP_STATE)              //30 for 1 Sec Timer delay
    {
        Ten_Sec_RampUp_Flag = 1;
    }
    else if(Ten_Sec_RampUp_Flag < RAMPUP_INITIAL_DELAY || Turbine_state != RAMPUP_STATE) 
    {
        Ten_Sec_RampUp_Flag = 0;
    }
    ///////////////////////////////
    Last_Five_Error(); 
    Wind_Average();
    EEPROM_Error_Monitor();
    //CSV Data//
    Serial_No = Serial_No + 1; 
    if(Serial_No > 2)
    {
        UART_Data();
    }
    
    
    ///////////
    
}
void Turbine_Start_up_1_Second ()
{
    Error_Scan_start_up();
    VFD_Data_Kill();
}
void Turbine_Ramp_up_1_Second ()
{    
    Error_Scan_Ramp_up();
    One_Sec_Delay();
    Two_Sec_Delay();
    Five_Sec_Delay();
}
void One_Sec_Delay (void)       //Used to create 1Sec Delay for Contactor in Ramp-up
{
    if(One_Sec_Delay_vab)
    {
        Delay_counter++;
        if(Delay_counter == 1)
        {
            Delay_counter = 0;
            One_Sec_Delay_vab = 0;
            One_sec_Delay_Flag = 1;
        }
    }
}

void Two_Sec_Delay (void)       //Used to create 1Sec Delay for Contactor in Ramp-up
{
    if(Two_Sec_Delay_vab)
    {
        Two_Delay_counter++;
        if(Two_Delay_counter == 2)
        {
            Two_Delay_counter = 0;
            Two_Sec_Delay_vab = 0;
            Two_sec_Delay_Flag = 1;
        }
    }
}
void Five_Sec_Delay (void)       //Used to create 1Sec Delay for Contactor in Ramp-up
{
    if(Five_Sec_Delay_vab)
    {
        Five_Delay_counter++;
        if(Five_Delay_counter == 5)
        {
            Five_Delay_counter = 0;
            Five_Delay_counter = 0;
            Five_sec_Delay_Flag = 1;
        }
    }
}