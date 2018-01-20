/*
 * File:   main_Logic.c
 * Created on April 17, 2017, 1:27 PM
 */
// PIC18F65K22 Configuration Bit Settings
// 'C' source line config statement
// CONFIG1L
#pragma config FOSC = INTIO2, MCLRE = ON, WDTEN = OFF, PWRTEN = ON, XINST = OFF,BOREN = NOSLP,BORV = 0
#pragma config SOSCSEL = DIG    // SOSC Power Selection and mode Configuration bits (Digital (SCLKI) mode)

#define _XTAL_FREQ 8000000

#include <xc.h>
#include "IO_Def.h"
#include "RTC.h"
#include "Initialization.h"
#include "RPM_Measurement.h"
#include "UART.h"
#include "ISR.h"
#include "state.h"
#include "ERROR_HANDLING.h"
#include "RAMP_UP.h"
#include "OneSecond_Function.h"
#include "Power_Meter.h"


char Check,Initial_Check = 0;
unsigned int VFD_Temp_counter = 0;

void main(void) 
{
    rtc_t rtc;
    RTC_Init();
    OSCILLATOR();
    Timer1_Initiate();
    Timer7_Init();
    usart_init();
    
    
    Generator_RPM_Initiate();
    Wind_Speed_Initiate();
    Turbine_RPM_Initiate();
    IO_Initiate();               //For Feedback 
    PM_IO_Initialization();
    PM_Timer_Initialization();
    PM_ADC_Initialization();    
    Phase_Sequence();
    
    PEIE=1;                      //Enable Peripheral Interrupt
    GIE=1;                       //Enable INTs globally
    
    EEPROM_Error_Stop();
    
    counter_1 = 0;
//    rtc.hour = 0x17; 
//    rtc.min =  0x46; 
//    rtc.sec =  00;
//
//    rtc.date = 0x12; 
//    rtc.month = 0x12;
//    rtc.year = 0x17;
//    rtc.weekDay = 3; 
//    RTC_SetDateTime(&rtc);  //  10:40:20 am, 1st Jan 2016
    while(1)
    {
                //POWER METER//
        Temp_Read();
        
        if(Volt_Curr_Flag == 1)
        {
            Volt_Curr_Flag = 0;
            Volt_Curr_Read();
            Volt_Curr_Avg();
            
        }
        
        if(Freq_Flag == 1)
        {
            Freq_Flag = 0;
            Freq_Calc();
        }
        
        if(R_PF_Flag == 1)
        {
            R_PF_Flag = 0;
            R_PF_Calc();
            R_PF_Avg();
        }
        
        if(Y_PF_Flag == 1)
        {
            Y_PF_Flag = 0;
            Y_PF_Calc();
            Y_PF_Avg();
        }
        
        if(B_PF_Flag == 1)
        {
            B_PF_Flag = 0;
            B_PF_Calc();
            B_PF_Avg();
        }
        
        Power_Factor();
        Power_Calc();
        Cons_Gene();
//        Lead_Lag_Cal();
                
        
        if (GRPM_Cap)
        {
            Generator_RPM_Cal();
            GRPM_Cap = 0;
        }
        if(TRPM_Cal)
        {
            Turbine_RPM_Cal();
            TRPM_Cal = 0; 
        }
        if (Wind_Cap)
        {
            Wind_Cap = 0;
            Wind_Speed_Cal();
        }
        
        if(Timer1_interrupt_flag)
        {
            Timer1_interrupt_flag = 0;
            RPM_Data_Kill();
        }
          switch(Turbine_state) 
          { 
                case STARTUP_STATE:
                    Desired_Frequency = DEFUALT_FREQUENCY;
                    startup_state_function();
                    Pitch_Counter = 0; 
                    Pitching_FlAG = 0;
                    Two_Delay_counter = 0;
                    Two_Sec_Delay_vab = 0;
                    Two_sec_Delay_Flag = 0;
                    break;

                 case RAMPUP_STATE:
                     Rampup_state_function();
                      break;

                 case RUNNING_STATE:

                       break;

                 case STOPPING_STATE:
                     
                      break;

                 default:
                     break;
          }
          
        if(Timer0_1Sec_Flag)                  //One Seconf Function
        {
            Timer0_1Sec_Flag = 0;
            Timer0_OneSecond_Function();        //One Second Function
            RA4 =  ~RA4;
        }
        RS485_Data_communication();
        
    }
}

