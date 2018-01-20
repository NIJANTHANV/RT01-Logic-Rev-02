/*
 * File:   RS485_COMMUNICATION.c
 * Author: nijanthan.v
 *
 * Created on August 19, 2017, 1:01 PM
 */


#include <xc.h>
#include "ISR.h"
#include "UART.h"
#include "stdlib.h"
#include "stdio.h"
#include "RTC.h"
#include "Initialization.h"
#include "RPM_Measurement.h"
#include "ERROR_HANDLING.h"
#include "state.h"
#include "RAMP_UP.h"
#include "SLIP_CALCULATIONS.h"
#include "RS485_COMMUNICATION.h"
#include "Power_Meter.h"
#define _XTAL_FREQ 8000000

void RS485_Data_communication (void)
{
    if(Serial_No == 8)
    {
        usart2_init();
    }
    if(Timer0_Falg2 == 1 && Serial_No > 8)// && VFD_ON_Flag != 0)            //VFD
    {        
        Timer0_Falg2 = 0;
        Communication_OTP++;
        if(Communication_OTP == 0 || Communication_OTP == 255)
        {
            Communication_OTP = 1;
        }
        RE0 = 1;
        RS485_Data_Flag = 1;
        counter_1  = 0;
        Data_1[0] = 0;

        __delay_ms(15);
        usart_str_2(0x07);              //Slave Address     //0 
        usart_str_2(VFD_On_Off);        //Start/Stop        //1
        usart_str_2(Desired_Frequency); //Frequency         //2
        usart_str_2(0x30);                                  //3
        usart_str_2(Communication_OTP);                                  //4
        __delay_ms(15);
        RE0 = 0; 

    }
}

void VFD_RS485_Data (void)
{
    
    
    VFD_Frequency = Data_1[2];
    VFD_Bus_Voltage = Data_1[3] + (Data_1[4] * 256);
    DC_Bus_Current = Data_1[5];
    DC_Bus_Current = DC_Bus_Current / 10;
    
    VFD_Error_No = Data_1[6];
}
void VFD_RS485_Data_filter (void)
{
    if(Data_1[1] == Data_1[7])
    {
        VFD_RS485_Data();
        
    }
    else 
    {
        Data_1[0] = 0; Data_1[1] = 0; Data_1[2] = 0; Data_1[3] = 0; Data_1[9] = 0;
        Data_1[4] = 0; Data_1[5] = 0; Data_1[6] = 0; Data_1[7] = 0; Data_1[8] = 0;
    }
}

void Communication_Error (void)
{
    if(VFD_ON_Flag == 1)
    {
        if(Communication_OTP != Data_1[9])
        {
            VFD_communication_Error_Counter++;
            if(VFD_communication_Error_Counter == 10)
            {
                VFD_communication_Error_Counter = 0;
                VFD_communication_Error_Flag = 1;
                Errors = VFD_COMMU_ERR;
            }
            else
            {
                VFD_communication_Error_Flag = 0;
            }
        }
        else
        {
            VFD_communication_Error_Flag = 0;
            VFD_communication_Error_Counter = 0;
        }
    }
    else
    {
        VFD_communication_Error_Counter = 0;
        VFD_communication_Error_Flag = 0;
    }
}