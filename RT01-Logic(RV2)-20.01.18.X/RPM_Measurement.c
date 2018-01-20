/*
 * File:   RPM_Measurement.c
 * Created on April 18, 2017, 10:00 AM
 */


#include <xc.h>
#include <pic18f65k22.h>
#include "RPM_Measurement.h"
#include "Initialization.h"
#include "ISR.h"
#include "ERROR_HANDLING.h"
#include "state.h"
#include "OneSecond_Function.h"

void Turbine_RPM_Cal(void)
{
    if(TRPM_Cal)
    {
        TRPM_Cal = 0;
        CCP7IE = 0;
        if(TRPM_Cap_New > TRPM_Cap_Old)
        {
            RPM_PWM =    (TRPM_Cap_New - TRPM_Cap_Old + 1) ;
            RPM_Time =  (Timer1_OF_counter_New - Timer1_OF_counter_Old);
            Flag_temp = 0;
        }
        else
        {
            RPM_PWM =    (TRPM_Cap_New - TRPM_Cap_Old + 1) + 65536;
            RPM_Time =  (Timer1_OF_counter_New - Timer1_OF_counter_Old);
            RPM_Time = RPM_Time -1;
            Flag_temp = 1;
        }
        PWM_Temp = (0.000004 * RPM_PWM);
        
        TRPM_Time = PWM_Temp + (0.262 * RPM_Time);
        
        TRPM_Frequency = 1/TRPM_Time; 
        
        if(RPM_counter < 2)
        {
            RPM_counter++;
        }   
        
       if(RPM_counter == 2)
        {
            Turb_RPM = (60 * TRPM_Frequency) / 1;
            Turbine_RPM_Old = Turbine_RPM_New;
            Turbine_RPM_New = Turb_RPM;
            
            if(Turbine_state == RAMPUP_STATE || Turbine_state == RUNNING_STATE)
            {
                if( Turbine_RPM_New > (Turbine_RPM_Old + 10)  || (Turbine_RPM_New <  (Turbine_RPM_Old - 10)  ) ) //if( Turbine_RPM_New > (Turbine_RPM_Old + 10) )
                {
                    Turbine_RPM = Turbine_RPM_Old;
                    Turbine_RPM_New = Turbine_RPM_Old;
                }
                else
                {
                    Turbine_RPM = Turbine_RPM_New;
                }
            }
            else if(Turbine_state == STARTUP_STATE || Turbine_state == STOPPING_STATE)
            {
                Turbine_RPM = Turbine_RPM_New;
            }
            
            
        }
        if(Turbine_state == RAMPUP_STATE)
        {
            if(Pitch_Counter < 2)
            {
                Pitch_Counter++;
            }
        }
        else if(Turbine_state != RAMPUP_STATE)
        {
            Pitch_Counter = 0;
            
        }
        if(Pitch_Counter == 2)
        {
            Pitching_FlAG = 1;
        }
        
        Timer1_OF_counter_Turbine = 0;
        RPM_Time_1 = RPM_Time;
        
        RPM_PWM = 0;
        RPM_Time = 0;
        TRPM_Frequency = 0;
        TRPM_Time = 0;
        CCP7IE = 1; // enable interrupt
        CCP7IF = 0;
    }

}
void Generator_RPM_Cal(void)
{
    CCP8IE = 0;
        if(GRPM_Cap_New > GRPM_Cap_Old)
        {
            GRPM_Pulse_width =    (GRPM_Cap_New - GRPM_Cap_Old + 1) ;
            GRPM_Counter =  (Timer1_OF_counter_Generator_New - Timer1_OF_counter_Generator_Old);
        }
        else
        {
            GRPM_Pulse_width =    (GRPM_Cap_New - GRPM_Cap_Old + 1) + 65536;
            GRPM_Counter =  (Timer1_OF_counter_Generator_New - Timer1_OF_counter_Generator_Old);
            GRPM_Counter = GRPM_Counter -1;
        }
        GRPM_Time = (0.000004 * GRPM_Pulse_width);
        
        GRPM_Time_1 = GRPM_Time + (0.262 * GRPM_Counter);
        
        GRPM_Time_1 = GRPM_Time_1 / 4;
        
        GRPM_Frequency = 1/GRPM_Time_1; 
        
        if(G_RPM_counter < GRPM_NO_OF_SENSING_POINTS)
        {
            G_RPM_counter++;
        }   
        if(G_RPM_counter == GRPM_NO_OF_SENSING_POINTS)
        {
            Generator_RPM_Old = Generator_RPM_New;
            Generator_RPM_New = ((60 * GRPM_Frequency) / GRPM_NO_OF_SENSING_POINTS);            
            
        }
        ///**20%***///
        if(Turbine_state == RUNNING_STATE)
        {
            if ( (Generator_RPM_Old > (Generator_RPM_New * 0.8)) && (Generator_RPM_Old < (Generator_RPM_New * 1.2)) )
            {
                Generator_RPM_FLT = Generator_RPM_New;
            }
            else
            {
                Generator_RPM_FLT = Generator_RPM_Old;
                Generator_RPM_New = Generator_RPM_Old;
            }
        }
        else
        {
            Generator_RPM_FLT = Generator_RPM_New;
        }
        Generator_RPM_INT = Generator_RPM_FLT;
        ///////////////
        
        Timer1_OF_counter_Generator = 0;
        GRPM_Pulse_width = 0;
        GRPM_Frequency = 0;
        GRPM_Time = 0;
        GRPM_Time_1 = 0;
        
        CCP8IE = 1; // enable interrupt
        CCP8IF = 0;
}


void Wind_Speed_Cal(void)
{
        //Modified on 21.12.17//
        Timer1_OF_counter_Wind = 0;
        Wind_Frequency = 0;
        Wind_Time_1 = 0;
        Wind_Time = 0;
        Wind_Pulse_width = 0;
        ///////////////////////
        if(Wind_Cap_New > Wind_Cap_Old)
        {
            Wind_Pulse_width =    (Wind_Cap_New - Wind_Cap_Old + 1) ;
            WRPM_Counter =  (Timer1_OF_counter_Wind_temp_New - Timer1_OF_counter_Wind_temp_Old);
        }
        else
        {
            Wind_Pulse_width =    (Wind_Cap_New - Wind_Cap_Old + 1) + 65536;
            WRPM_Counter =  (Timer1_OF_counter_Wind_temp_New - Timer1_OF_counter_Wind_temp_Old);
            WRPM_Counter = WRPM_Counter -1;
        }
    
        Wind_Time = 0.000004 * Wind_Pulse_width; //TIMER1 / PRESCALE VALUE ==> 2MHz / 8 =>4USec
        
        Wind_Time_1 = Wind_Time + (0.262 * WRPM_Counter);
        
        Wind_Frequency = (1/Wind_Time_1);
        Wind = (Wind_Frequency / 6);
        Wind_Speed = ((Wind * WIND_1_CD_FACTOR)/100);
}

void Wind_Speed_2_Cal(void)
{
        //Modified on 21.12.17//
        Timer1_OF_counter_Wind_2 = 0;
        wind_Frequency_2 = 0;
        wind_Time_1_2 = 0;
        Wind_Time_2 = 0;
        Wind_Pulse_width_2 = 0;
        /////////////////////////
        if(Wind_Cap_New_2 > Wind_Cap_Old_2)
        {
            Wind_Pulse_width_2 =    (Wind_Cap_New_2 - Wind_Cap_Old_2 + 1) ;
            WRPM_Counter_1 =  (Timer1_OF_counter_Wind_2_temp_New - Timer1_OF_counter_Wind_2_temp_Old);
        }
        else
        {
            Wind_Pulse_width_2 =    (Wind_Cap_New_2 - Wind_Cap_Old_2 + 1) + 65536;
            WRPM_Counter_1 =  (Timer1_OF_counter_Wind_2_temp_New - Timer1_OF_counter_Wind_2_temp_Old);
            WRPM_Counter_1 = WRPM_Counter_1 -1;
        }
        
        
        Wind_Time_2 = 0.000004 * Wind_Pulse_width_2; //TIMER1 / PRESCALE VALUE ==> 2MHz / 8 =>4USec
        
        wind_Time_1_2 = Wind_Time_2 + (0.262 * WRPM_Counter_1);
        
        wind_Frequency_2 = (1/wind_Time_1_2);
        wind_2 = (wind_Frequency_2 / 6);
        Wind_Speed_2 = ((wind_2 * WIND_2_CD_FACTOR)/100);
        
        
}
void Wind_Average (void)
{
        Wind_Speed_9 = Wind_Speed_8;
        Wind_Speed_8 = Wind_Speed_7;
        Wind_Speed_7 = Wind_Speed_6;
        Wind_Speed_6 = Wind_Speed_5;
        Wind_Speed_5 = Wind_Speed_4;
        Wind_Speed_4 = Wind_Speed_3;
        Wind_Speed_3 = Wind_Spd_2;
        Wind_Spd_2 = Wind_Speed_1;
        Wind_Speed_1 = Wind_Speed_0;
        Wind_Speed_0 = Wind_Speed;
        
        if(Ten_Sec_Counter < WIND_10_SEC_INITIAL_DELAY)
        {
            Ten_Sec_Counter++;
        }
        if(Ten_Sec_Counter == WIND_10_SEC_INITIAL_DELAY)
        {
            Wind_Speed_Avg = (Wind_Speed_9 + Wind_Speed_8 + Wind_Speed_7 + Wind_Speed_6 + Wind_Speed_5 + Wind_Speed_4 + Wind_Speed_3 + Wind_Spd_2 + Wind_Speed_1 + Wind_Speed_0)/WIND_10_SEC_INITIAL_DELAY;
        }
    ///////////////////////
        ////Wind Speed One////
        Wind_Speed_9_2 = Wind_Speed_8_2;
        Wind_Speed_8_2 = Wind_Speed_7_2;
        Wind_Speed_7_2 = Wind_Speed_6_2;
        Wind_Speed_6_2 = Wind_Speed_5_2;
        Wind_Speed_5_2 = Wind_Speed_4_2;
        Wind_Speed_4_2 = Wind_Speed_3_2;
        Wind_Speed_3_2 = Wind_Speed_2_2;
        Wind_Speed_2_2 = Wind_Speed_1_2;
        Wind_Speed_1_2 = Wind_Speed_0_2;
        Wind_Speed_0_2 = Wind_Speed_2;
        
        if(Ten_Sec_Counter_2 < WIND_10_SEC_INITIAL_DELAY)
        {
            Ten_Sec_Counter_2++;
        }
        if(Ten_Sec_Counter_2 == WIND_10_SEC_INITIAL_DELAY)
        {
            Wind_Speed_Avg_2 = (Wind_Speed_9_2 + Wind_Speed_8_2 + Wind_Speed_7_2 + Wind_Speed_6_2 + Wind_Speed_5_2 + Wind_Speed_4_2 + Wind_Speed_3_2 + Wind_Speed_2_2 + Wind_Speed_1_2 + Wind_Speed_0_2)/WIND_10_SEC_INITIAL_DELAY;
        }
    //////////////////////// 
}
void RPM_Data_Kill (void)
{
    
        //*********To Kill Values if RPM INPUT not Comes*****/
        if(Timer1_OF_counter_Turbine > 50)
        {
            Timer1_OF_counter_Turbine = 0;
            Turbine_RPM = 0; 
            RPM_PWM = 0;
            RPM_Time = 0;
            TRPM_Frequency = 0;
            TRPM_Time = 0;
            Turb_RPM = 0; Turbine_RPM_Old = 0; Turbine_RPM_New = 0;
        }
        if(Timer1_OF_counter_Generator > 10)
        {
            Timer1_OF_counter_Generator = 0;
            GRPM_Frequency = 0; GRPM_Cap_New = 0;Generator_RPM_FLT = 0;Generator_RPM_INT = 0;
        }
        if(Timer1_OF_counter_Wind > 10)
        {
            Timer1_OF_counter_Wind = 0;
            Wind_Frequency = 0;Wind_Cap_New = 0;Wind_Speed = 0;
            wind_1_Temp_flag = 1;
        }
        else
        {
            wind_1_Temp_flag = 0;

        }
        if(Timer1_OF_counter_Wind_2 > 10)
        {
            Timer1_OF_counter_Wind_2 = 0;
            wind_Frequency_2 = 0;Wind_Cap_New_2 = 0;Wind_Speed_2 = 0;
            wind_2_Temp_flag = 1;
        }
        else
        {
            wind_2_Temp_flag = 0;

        }
        ////////////*************************************/////
}
