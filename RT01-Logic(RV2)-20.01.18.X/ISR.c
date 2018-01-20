/*
 * File:   ISR.c
 * Author: nijanthan.v
 *
 * Created on April 19, 2017, 3:05 PM
 */


#include <xc.h>
#include "ISR.h"
#include "UART.h"
#include "RPM_Measurement.h"
#include "Initialization.h"
#include "state.h"
#include "Power_Meter.h"
#define _XTAL_FREQ 8000000

void interrupt ISR()
{
    if(TMR7IF)
    {
        TMR7IF = 0;
        Error_Checking_Interrupt_Overflow();
        Timer1_counter++;
        if(Timer1_counter == 15)
        {
            Timer0_Falg2 = 1; 
        }
        if(Timer1_counter == 30 && One_Sec_Flag == 0)
        {
            Timer1_counter = 0;
            Timer0_1Sec_Flag = 1;
            One_Sec_Flag = 1;
        }
        if(Timer1_counter == 31 && One_Sec_Flag == 1)
        {
            Timer1_counter = 0;
            Timer0_1Sec_Flag = 1;
            One_Sec_Flag = 0;
        }
    }
    if(TMR0IF)
    {
        TMR0IF = 0;
        Volt_Curr_Flag = 1;
        PM_Error_Led();
        Timer0_counter++;
    }
    
    if(CCP10IF)          //R-Voltage ZCD
    {
        CCP10IF = 0;
        CCP10IE = 1;     // enable interrupt
        Freq_Flag = 1;
        R_V_Old = R_V_New;
        R_V_New = ((CCPR10H << 8) | CCPR10L);
    }
    
    if(CCP2IF)           //Y-Voltage ZCD
    {
        CCP2IF = 0;
        CCP2IE = 1;      // enable interrupt
        Y_V_Old = Y_V_New;
        Y_V_New = ((CCPR2H << 8) | CCPR2L);
    }
    
    if(CCP1IF)           //B-Voltage ZCD
    {
        CCP1IF = 0;
        CCP1IE = 1;     // enable interrupt
        B_V_Old = B_V_New;
        B_V_New = ((CCPR1H << 8) | CCPR1L);
    }
    
    if(CCP3IF)          //R-Current ZCD
    {
        CCP3IF = 0;
        CCP3IE = 1;     // enable interrupt
        R_PF_Flag = 1;
        Rcurr_Old = Rcurr_New;                  
        Rcurr_New = ((CCPR3H << 8) | CCPR3L);  
        Rcurr_V_Old = R_V_Old;             
        Rcurr_V_New = R_V_New;  
    }
    
    if(CCP4IF)          //Y-Current ZCD
    {
        CCP4IF = 0;
        CCP4IE = 1;     // enable interrupt
        Y_PF_Flag = 1;
        Ycurr_Old = Ycurr_New;                  
        Ycurr_New = ((CCPR4H << 8) | CCPR4L);   
        Ycurr_V_Old = Y_V_Old;             
        Ycurr_V_New = Y_V_New;  
    }
    
    if(CCP5IF)          //B-Current ZCD
    {
        CCP5IF = 0;
        CCP5IE = 1;     // enable interrupt
        B_PF_Flag = 1;
        Bcurr_Old = Bcurr_New;                  
        Bcurr_New = ((CCPR5H << 8) | CCPR5L); 
        Bcurr_V_Old = B_V_Old;             
        Bcurr_V_New = B_V_New;  
    }
    
    if(TMR1IF)
    {
        TMR1IF = 0;
        Gi_Timer1_OF_counter++;
        Timer1_OF_counter_Turbine++;
        /////////////////
        Timer1_OF_counter_Generator++;
        Gi_Timer1_OF_counter_Generator_Temp++;
        /////////////////
        Timer1_OF_counter_Wind++;
        Timer1_OF_counter_Wind_temp++;
        ////////////////
        Timer1_OF_counter_Wind_2++;
        Timer1_OF_counter_Wind_2_temp++;
        ////////////////
        Timer1_interrupt_flag = 1;
        
    }
    
    if(CCP7IF)
    {
        CCP7IF = 0;
        TRPM_Cap_Old = TRPM_Cap_New;
        TRPM_Cap_New = (256*CCPR7H)+CCPR7L;      //Capture Time Stamp
        Timer1_OF_counter_Old = Timer1_OF_counter_New;
        Timer1_OF_counter_New = Gi_Timer1_OF_counter;
        TRPM_Cal = 1;
        
    }
    if(CCP8IF)
    {
        CCP8IF = 0;
        GRPM_Cap_Old = GRPM_Cap_New;
        GRPM_Cap_New = ((256*CCPR8H)+CCPR8L);      //Capture Time Stamp
        Timer1_OF_counter_Generator_Old = Timer1_OF_counter_Generator_New;
        Timer1_OF_counter_Generator_New = Gi_Timer1_OF_counter_Generator_Temp;
        GRPM_Cap = 1;
    }
    
    if(CCP6IF)
    {
        CCP6IF = 0;
        Wind_Cap_Old = Wind_Cap_New;
        Wind_Cap_New = ((256*CCPR6H)+CCPR6L);      //Capture Time Stamp
        Timer1_OF_counter_Wind_temp_Old = Timer1_OF_counter_Wind_temp_New;
        Timer1_OF_counter_Wind_temp_New = Timer1_OF_counter_Wind_temp;
        Wind_Cap = 1;
    }
    
    if(PIR3bits.RC2IF)
    {
        if(RCSTA2bits.OERR==1)
        {
            RCSTA2bits.CREN=0;
            RCSTA2bits.CREN=1;
        }
        if(RS485_Data_Flag == 1)
        {
            Data_1[counter_1] = RCREG2;
            if(Data_1[0] == 0x20)
            {
                if(counter_1 < 10)
                {
                    counter_1++;
                }
            }
        }
         PIR3bits.RC2IF = 0;
    }
    
}
