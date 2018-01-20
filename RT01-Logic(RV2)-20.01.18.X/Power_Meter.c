/*
 * File:   Power_Meter.c
 * Author: nijanthan.v
 *
 * Created on October 16, 2017, 2:39 PM
 */


#include <xc.h>
#include "Power_Meter.h"
#include "ERROR_HANDLING.h"
#include "Initialization.h"
#include "ISR.h"
#include "state.h"

void PM_IO_Initialization(void) 
{
    //////////////////// R,Y,B - Volt,Curr ////////////////////
    
    TRISAbits.TRISA0 = 1;      // RA0 for Temp_sensor set as input
    
    TRISAbits.TRISA1 = 1;      // RA1 for R_Volt set as input
    TRISAbits.TRISA2 = 1;      // RA2 for Y_Volt set as input
    TRISAbits.TRISA3 = 1;      // RA3 for B_Volt set as input
    
    TRISFbits.TRISF4 = 1;      // RF4 for R_Curr set as input
    TRISFbits.TRISF5 = 1;      // RF5 for Y_Curr set as input
    TRISFbits.TRISF6 = 1;      // RF6 for B_Curr set as input
    
    
    ANSEL0 = 1;      // AN0 Configured as Analog Channel 
    
    ANSEL1 = 1;      // AN1 Configured as Analog Channel
    ANSEL2 = 1;      // AN2 Configured as Analog Channel
    ANSEL3 = 1;      // AN3 Configured as Analog Channel
    
    ANSEL9 = 1;      // AN9 Configured as Analog Channel
    ANSEL10 = 1;     // AN10 Configured as Analog Channel
    ANSEL11 = 1;     // AN11 Configured as Analog Channel
    
    ////////////////////////////////////////////////////////////
    
    ////////////////// Power Meter Error LED ///////////////////
    
    TRISFbits.TRISF7 = 0;
    PM_Error_LED_OFF;
    
    ////////////////////////////////////////////////////////////
        
    
    ///////////////// Power Factor (R,Y,B-Voltage,Current ZCD) /////////////////
    
    TRISEbits.TRISE2 = 1;            // CCP10(RE2) for set as input
    CCP10CON = 0x04;                 // Capture mode every falling edge
    CCP10IE = 1;                     // Enable interrupt capture
    CCP10IF = 0;                     // Clear CCP flag

    TRISCbits.TRISC1 = 1;           // CCP2(RC1) for set as input
    CCP2CON = 0x04;                 // Capture mode every falling edge
    CCP2IE = 1;                     // Enable interrupt capture
    CCP2IF = 0;                     // Clear CCP flag
    
    TRISCbits.TRISC2 = 1;           // CCP1(RC2) for set as input
    CCP1CON = 0x04;                 // Capture mode every falling edge
    CCP1IE = 1;                     // Enable interrupt capture
    CCP1IF = 0;                     // Clear CCP flag
    
    TRISGbits.TRISG0 = 1;           // ECCP3(RG0) for set as input
    CCP3CON = 0x04;                 // Capture mode every falling edge
    CCP3IE = 1;                     // Enable interrupt capture
    CCP3IF = 0;                     // Clear CCP flag

    TRISGbits.TRISG3 = 1;           // CCP4(RG3) for set as input
    ANSEL17 = 0;                    // AN17 Configured as Digital channel
    CCP4CON = 0x04;                 // Capture mode every falling edge
    CCP4IE = 1;                     // Enable interrupt capture
    CCP4IF = 0;                     // Clear CCP flag
    
    TRISGbits.TRISG4 = 1;           // CCP5(RG4) for set as input
    ANSEL16 = 0;                    // AN16 Configured as Digital channel
    CCP5CON = 0x04;                 // Capture mode every falling edge
    CCP5IE = 1;                     // Enable interrupt capture
    CCP5IF = 0;                     // Clear CCP flag
    
    ////////////////////////////////////////////////////////////////////
}

void PM_Timer_Initialization(void)
{
    T0CON = 0b11000111;         // 8-bit ,Prescale-256

    TMR0IE = 1;                 // Enable TIMER0 Interrupt
    TMR0IF = 0;                 // Set initial zero the Flag
    
//    T1CON = 0b00110101;         // 16-bit timer3 with 8 Prescale
    
}

void PM_ADC_Initialization(void)
{
    ADCON1 = 0b01000000;        // VSS,VDD ref and special trigger from CTMU
    ADCON2 = 0b10001101;        // ADCON2 setup: Right justified, Tacq=2Tad, Tad=Fosc/16 
}

unsigned int Read_Adc(unsigned char ch)
{
    ADCON0 = 0b00000000;            // Initial AN0 selection
    ADCON0 = (ch<<2);               // Select ADC Channel
    ADON = 1;                       // Switch on the adc module
    GODONE = 1;                     // Start conversion
    while(GODONE);                  // Wait for the conversion to finish
    ADON = 0;                       // Switch off adc
    return ((ADRESH << 8) | ADRESL);
}


void Temp_Read(void)
{
    Temp_Sensor = Read_Adc(0);
    Temprature = (Temp_Sensor * Temperature_Constant);      // For mV we multiply 1000,10mV = 1 degree so,we divide by 10,Totally we multiply with 100 
                                                            // = ((5.02v / 4095)*100 = 0.122589)
    
    Temp_Arr[5] = Temp_Arr[4]; 
    Temp_Arr[4] = Temp_Arr[3];
    Temp_Arr[3] = Temp_Arr[2]; 
    Temp_Arr[2] = Temp_Arr[1]; 
    Temp_Arr[1] = Temp_Arr[0];
    Temp_Arr[0] = Temprature;
    
    Temperature_Avg = ((Temp_Arr[0] + Temp_Arr[1] + Temp_Arr[2] + Temp_Arr[3] + Temp_Arr[4] + Temp_Arr[5]) / 6);

}

void Volt_Curr_Read(void)
{
    
switch (Case_Call)                //At Initial "Case_Call" will be "1"
    {
        case 1:                   //It takes 30 ms for execution

        Case_Call = 2;

        R_V_Max = 0; 
        R_C_Max = 0;

        for(i=0; i<70; i++)  
        {
            R_V = Read_Adc(1);
            R_C = Read_Adc(9);

            if(R_V_Max < R_V)
            {
               R_V_Max = R_V;
            }

            if(R_C_Max < R_C)
            {
               R_C_Max = R_C;
            } 
        }

        R_V_Arr[2] = R_V_Arr[1]; 
        R_V_Arr[1] = R_V_Arr[0];
        R_V_Arr[0] = R_V_Max;

        R_C_Arr[2] = R_C_Arr[1];
        R_C_Arr[1] = R_C_Arr[0];
        R_C_Arr[0] = R_C_Max;

        break;

        case 2:

        Case_Call = 3;

        Y_V_Max = 0;
        Y_C_Max = 0;

        for(i=0; i<70; i++)
        {
            Y_V = Read_Adc(2);
            Y_C = Read_Adc(10);

            if(Y_V_Max < Y_V)
            {
               Y_V_Max = Y_V;
            }

            if(Y_C_Max < Y_C)
            {
               Y_C_Max = Y_C;
            } 
         }

        Y_V_Arr[2] = Y_V_Arr[1];
        Y_V_Arr[1] = Y_V_Arr[0];
        Y_V_Arr[0] = Y_V_Max;

        Y_C_Arr[2] = Y_C_Arr[1];
        Y_C_Arr[1] = Y_C_Arr[0];
        Y_C_Arr[0] = Y_C_Max;

        break;

        case 3:

        Case_Call = 1;

        B_V_Max=0;
        B_C_Max=0;
        
        for(i=0; i<70; i++)
        {
            B_V = Read_Adc(3);
            B_C = Read_Adc(11);

            if(B_V_Max < B_V)
            {
               B_V_Max = B_V;
            }

            if(B_C_Max < B_C)
            {
               B_C_Max = B_C;
            } 
        }

        B_V_Arr[2] = B_V_Arr[1];
        B_V_Arr[1] = B_V_Arr[0]; 
        B_V_Arr[0] = B_V_Max;

        B_C_Arr[2] = B_C_Arr[1];
        B_C_Arr[1] = B_C_Arr[0];
        B_C_Arr[0] = B_C_Max;

        break; 
    }
}

void Volt_Curr_Avg(void)
{
    R_V_Avg_Steps = ((R_V_Arr[0] + R_V_Arr[1] + R_V_Arr[2] ) / 3);
    R_Volt = ((R_V_Avg_Steps - V_Shifted_Bits) * KV_Constant) * 0.707106781;
    
    R_C_Avg_Steps = ((R_C_Arr[0]+R_C_Arr[1] + R_C_Arr[2] ) / 3);
    R_Curr = ((R_C_Avg_Steps - C_Shifted_Bits) * KC_Constant) * 0.707106781;

    Y_V_Avg_Steps = ((Y_V_Arr[0] + Y_V_Arr[1] + Y_V_Arr[2] ) / 3);
    Y_Volt = ((Y_V_Avg_Steps - V_Shifted_Bits) * KV_Constant) * 0.707106781;
    
    Y_C_Avg_Steps = ((Y_C_Arr[0] + Y_C_Arr[1] + Y_C_Arr[2] ) / 3);
    Y_Curr = ((Y_C_Avg_Steps - C_Shifted_Bits) * KC_Constant) * 0.707106781;
  
    B_V_Avg_Steps = ((B_V_Arr[0] + B_V_Arr[1] + B_V_Arr[2] ) / 3);
    B_Volt = ((B_V_Avg_Steps - V_Shifted_Bits) * KV_Constant) * 0.707106781;
    
    B_C_Avg_Steps = ((B_C_Arr[0] + B_C_Arr[1] + B_C_Arr[2] ) / 3);
    B_Curr = ((B_C_Avg_Steps - C_Shifted_Bits) * KC_Constant) * 0.707106781;
    
    Avg_RYB_Voltage = ((R_Volt + Y_Volt + B_Volt) / 3);
    Avg_RYB_Current = ((R_Curr + Y_Curr + B_Curr) / 3);
}

void Phase_Sequence(void)
{
    RV_PS_Max = 0;
    YV_PS_Max = 0;
    BV_PS_Max = 0;
    R_Peak = 0;
    Y_Peak = 0;
    B_Peak = 0;
   
    for(PS = 0; PS < 70; PS++)
    {
        RV_PS = Read_Adc(1);
        YV_PS = Read_Adc(2);
        BV_PS = Read_Adc(3);
        
        if(RV_PS_Max < RV_PS)
        {
            RV_PS_Max = RV_PS;
            R_Peak = PS;
        }
        
        if(YV_PS_Max < YV_PS)
        {
            YV_PS_Max = YV_PS;
            Y_Peak = PS;
        }

        if(BV_PS_Max < BV_PS)
        {
            BV_PS_Max = BV_PS;
            B_Peak = PS;
        }
    }
   
    if( ((R_Peak > B_Peak) && (B_Peak > Y_Peak)) || ((Y_Peak > R_Peak) && (R_Peak > B_Peak)) || ((B_Peak > Y_Peak) && (Y_Peak > R_Peak)) )
    {
        Phase_Sequence_Ok = 1;
    }

    else
    {
        Phase_Sequence_Ok = 0;        
    }
}

void Cons_Gene(void)
{
    if((R_V_Max > V_Shifted_Bits) && (R_C_Max > C_Shifted_Bits))        // Consumption condition
    {
       Consumption = 0;
       KW = ((-1) * KW);
       Y_KW = ((-1) * Y_KW);
    }
    else if((R_V_Max > V_Shifted_Bits) && (R_C_Max < C_Shifted_Bits))   // Generation condition
    {
        Consumption = 1;
    }
}

void Freq_Calc(void)
{
    if(R_V_New > R_V_Old)
    {
        Time_Diff = (R_V_New - R_V_Old + 1);     // Calculate length of pulse from falling edge to falling edge
    }
    else
    {
        Time_Diff = ((R_V_New - R_V_Old + 1) + 65536);
    }

    Time_Old = Time_New; 
    Time_New = (0.000004 * Time_Diff);        //TIMER3 / PRESCALE VALUE ==> 8MHz / 4==> 2/4(prescale) => 4USec
    
    if ( (Time_Old > (Time_New * 0.8)) && (Time_Old < (Time_New * 1.2)))
    {
        Frequency = (1 / Time_New);
    }
}

void R_PF_Calc(void)
{
    if(Rcurr_V_New < Rcurr_V_Old)
    {
        R_V_Gap = ((Rcurr_V_New - Rcurr_V_Old + 1) + 65536);
    }

    else if((Rcurr_New + 100) < Rcurr_V_New)
    {
        R_C_Gap = ((Rcurr_New - Rcurr_V_New + 1) + 65536);
    }
    
    else
    {
        R_C_Gap = (Rcurr_New - Rcurr_V_New);
        R_V_Gap = (Rcurr_V_New - Rcurr_V_Old);
    }
    
    R_Gap_Ratio = (R_C_Gap / R_V_Gap);                   
    R_Deg = R_Gap_Ratio * 360;                  // Degrees
    
    RGR_Arr_1[4] = RGR_Arr_1[3];
    RGR_Arr_1[3] = RGR_Arr_1[2]; 
    RGR_Arr_1[2] = RGR_Arr_1[1]; 
    RGR_Arr_1[1] = RGR_Arr_1[0];
    RGR_Arr_1[0] = R_Gap_Ratio;
          
}

void R_PF_Avg(void)
{
    RGR_Avg_1 = ((RGR_Arr_1[4] + RGR_Arr_1[3] + RGR_Arr_1[2] + RGR_Arr_1[1] + RGR_Arr_1[0]) / 5);
    
    
    RGR_Arr[29] = RGR_Arr[28]; 
    RGR_Arr[28] = RGR_Arr[27];
    RGR_Arr[27] = RGR_Arr[26]; 
    RGR_Arr[26] = RGR_Arr[25];
    RGR_Arr[25] = RGR_Arr[24]; 
    RGR_Arr[24] = RGR_Arr[23]; 
    RGR_Arr[23] = RGR_Arr[22];
    RGR_Arr[22] = RGR_Arr[21]; 
    RGR_Arr[21] = RGR_Arr[20];
    RGR_Arr[20] = RGR_Arr[19]; 
    RGR_Arr[19] = RGR_Arr[18];
    RGR_Arr[18] = RGR_Arr[17]; 
    RGR_Arr[17] = RGR_Arr[16]; 
    RGR_Arr[16] = RGR_Arr[15];
    RGR_Arr[15] = RGR_Arr[14];
    RGR_Arr[14] = RGR_Arr[13]; 
    RGR_Arr[13] = RGR_Arr[12];
    RGR_Arr[12] = RGR_Arr[11]; 
    RGR_Arr[11] = RGR_Arr[10];
    RGR_Arr[10] = RGR_Arr[9]; 
    RGR_Arr[9] = RGR_Arr[8]; 
    RGR_Arr[8] = RGR_Arr[7];
    RGR_Arr[7] = RGR_Arr[6]; 
    RGR_Arr[6] = RGR_Arr[5];
    RGR_Arr[5] = RGR_Arr[4]; 
    RGR_Arr[4] = RGR_Arr[3];
    RGR_Arr[3] = RGR_Arr[2]; 
    RGR_Arr[2] = RGR_Arr[1]; 
    RGR_Arr[1] = RGR_Arr[0];

    
    if( (RGR_Avg_1 > (R_Gap_Ratio * 0.8)) && (RGR_Avg_1 < (R_Gap_Ratio * 1.2)) )
    {
        RGR_Arr[0] = R_Gap_Ratio; 
    }
    
    RGR_Avg = (RGR_Arr[29] + RGR_Arr[28] + RGR_Arr[27] + RGR_Arr[26] + RGR_Arr[25] + RGR_Arr[24] + RGR_Arr[23] + RGR_Arr[22] 
                + RGR_Arr[21] + RGR_Arr[20] + RGR_Arr[19] + RGR_Arr[18] + RGR_Arr[17] + RGR_Arr[16] + RGR_Arr[15] 
                + RGR_Arr[14] + RGR_Arr[13] + RGR_Arr[12] + RGR_Arr[11] + RGR_Arr[10] + RGR_Arr[9] + RGR_Arr[8] + RGR_Arr[7] 
                + RGR_Arr[6] + RGR_Arr[5] + RGR_Arr[4] + RGR_Arr[3] + RGR_Arr[2] + RGR_Arr[1] + RGR_Arr[0] );
    
    RGR_Avg = (RGR_Avg / 30);
    R_Rad = ((RGR_Avg * 2 * 3.1412) - SD_Phase_Shift);          // Radians
    R_Power_Factor = (cos(R_Rad));                              // Power Factor 
    
//    if(R_Power_Factor < 0)
//    {
//        R_Power_Factor = ((-1) * R_Power_Factor);
//    }
    
}

void Y_PF_Calc(void)
{
    if(Ycurr_V_New < Ycurr_V_Old)
    {
        Y_V_Gap = ((Ycurr_V_New - Ycurr_V_Old + 1) + 65536);
    }

    else if((Ycurr_New + 100) < Ycurr_V_New)
    {
        Y_C_Gap = ((Ycurr_New - Ycurr_V_New + 1) + 65536);
    }
    
    else
    {
        Y_C_Gap = (Ycurr_New - Ycurr_V_New);
        Y_V_Gap = (Ycurr_V_New - Ycurr_V_Old);
    }
    
    Y_Gap_Ratio = (Y_C_Gap / Y_V_Gap);                   
    Y_Deg = Y_Gap_Ratio * 360;                  // Degrees
    
    YGR_Arr_1[4] = YGR_Arr_1[3];
    YGR_Arr_1[3] = YGR_Arr_1[2]; 
    YGR_Arr_1[2] = YGR_Arr_1[1]; 
    YGR_Arr_1[1] = YGR_Arr_1[0];
    YGR_Arr_1[0] = Y_Gap_Ratio;
          
}

void Y_PF_Avg(void)
{
    YGR_Avg_1 = ((YGR_Arr_1[4] + YGR_Arr_1[3] + YGR_Arr_1[2] + YGR_Arr_1[1] + YGR_Arr_1[0]) / 5);
    
    
    YGR_Arr[29] = YGR_Arr[28]; 
    YGR_Arr[28] = YGR_Arr[27];
    YGR_Arr[27] = YGR_Arr[26]; 
    YGR_Arr[26] = YGR_Arr[25];
    YGR_Arr[25] = YGR_Arr[24]; 
    YGR_Arr[24] = YGR_Arr[23]; 
    YGR_Arr[23] = YGR_Arr[22];
    YGR_Arr[22] = YGR_Arr[21]; 
    YGR_Arr[21] = YGR_Arr[20];
    YGR_Arr[20] = YGR_Arr[19]; 
    YGR_Arr[19] = YGR_Arr[18];
    YGR_Arr[18] = YGR_Arr[17]; 
    YGR_Arr[17] = YGR_Arr[16]; 
    YGR_Arr[16] = YGR_Arr[15];
    YGR_Arr[15] = YGR_Arr[14];
    YGR_Arr[14] = YGR_Arr[13]; 
    YGR_Arr[13] = YGR_Arr[12];
    YGR_Arr[12] = YGR_Arr[11]; 
    YGR_Arr[11] = YGR_Arr[10];
    YGR_Arr[10] = YGR_Arr[9]; 
    YGR_Arr[9] = YGR_Arr[8]; 
    YGR_Arr[8] = YGR_Arr[7];
    YGR_Arr[7] = YGR_Arr[6]; 
    YGR_Arr[6] = YGR_Arr[5];
    YGR_Arr[5] = YGR_Arr[4]; 
    YGR_Arr[4] = YGR_Arr[3];
    YGR_Arr[3] = YGR_Arr[2]; 
    YGR_Arr[2] = YGR_Arr[1]; 
    YGR_Arr[1] = YGR_Arr[0];

    
    if( (YGR_Avg_1 > (Y_Gap_Ratio * 0.8)) && (YGR_Avg_1 < (Y_Gap_Ratio * 1.2)) )
    {
        YGR_Arr[0] = Y_Gap_Ratio; 
    }
    
    YGR_Avg = (YGR_Arr[29] + YGR_Arr[28] + YGR_Arr[27] + YGR_Arr[26] + YGR_Arr[25] + YGR_Arr[24] + YGR_Arr[23] + YGR_Arr[22] 
                + YGR_Arr[21] + YGR_Arr[20] + YGR_Arr[19] + YGR_Arr[18] + YGR_Arr[17] + YGR_Arr[16] + YGR_Arr[15] 
                + YGR_Arr[14] + YGR_Arr[13] + YGR_Arr[12] + YGR_Arr[11] + YGR_Arr[10] + YGR_Arr[9] + YGR_Arr[8] + YGR_Arr[7] 
                + YGR_Arr[6] + YGR_Arr[5] + YGR_Arr[4] + YGR_Arr[3] + YGR_Arr[2] + YGR_Arr[1] + YGR_Arr[0]);

    YGR_Avg = (YGR_Avg / 30);
    Y_Rad = ((YGR_Avg * 2 * 3.1412) - SD_Phase_Shift);          //Radians
    Y_Power_Factor = (cos(Y_Rad));                              //Power Factor 
    
//    if(Y_Power_Factor < 0)
//    {
//        Y_Power_Factor = ((-1) * Y_Power_Factor);
//    }
}

void B_PF_Calc(void)
{
    if(Bcurr_V_New < Bcurr_V_Old)
    {
        B_V_Gap = ((Bcurr_V_New - Bcurr_V_Old + 1) + 65536);
    }

    else if((Bcurr_New + 100) < Bcurr_V_New)
    {
        B_C_Gap = ((Bcurr_New - Bcurr_V_New + 1) + 65536);
    }
    
    else
    {
        B_C_Gap = (Bcurr_New - Bcurr_V_New);
        B_V_Gap = (Bcurr_V_New - Bcurr_V_Old);
    }
    
    B_Gap_Ratio = (B_C_Gap / B_V_Gap);                   
    B_Deg = B_Gap_Ratio * 360;                  // Degrees
    
    BGR_Arr_1[4] = BGR_Arr_1[3];
    BGR_Arr_1[3] = BGR_Arr_1[2]; 
    BGR_Arr_1[2] = BGR_Arr_1[1]; 
    BGR_Arr_1[1] = BGR_Arr_1[0];
    BGR_Arr_1[0] = B_Gap_Ratio;
          
}

void B_PF_Avg(void)
{
    BGR_Avg_1 = ((BGR_Arr_1[4] + BGR_Arr_1[3] + BGR_Arr_1[2] + BGR_Arr_1[1] + BGR_Arr_1[0]) / 5);
    
    
    BGR_Arr[29] = BGR_Arr[28]; 
    BGR_Arr[28] = BGR_Arr[27];
    BGR_Arr[27] = BGR_Arr[26]; 
    BGR_Arr[26] = BGR_Arr[25];
    BGR_Arr[25] = BGR_Arr[24]; 
    BGR_Arr[24] = BGR_Arr[23]; 
    BGR_Arr[23] = BGR_Arr[22];
    BGR_Arr[22] = BGR_Arr[21]; 
    BGR_Arr[21] = BGR_Arr[20];
    BGR_Arr[20] = BGR_Arr[19]; 
    BGR_Arr[19] = BGR_Arr[18];
    BGR_Arr[18] = BGR_Arr[17]; 
    BGR_Arr[17] = BGR_Arr[16]; 
    BGR_Arr[16] = BGR_Arr[15];
    BGR_Arr[15] = BGR_Arr[14];
    BGR_Arr[14] = BGR_Arr[13]; 
    BGR_Arr[13] = BGR_Arr[12];
    BGR_Arr[12] = BGR_Arr[11]; 
    BGR_Arr[11] = BGR_Arr[10];
    BGR_Arr[10] = BGR_Arr[9]; 
    BGR_Arr[9] = BGR_Arr[8]; 
    BGR_Arr[8] = BGR_Arr[7];
    BGR_Arr[7] = BGR_Arr[6]; 
    BGR_Arr[6] = BGR_Arr[5];
    BGR_Arr[5] = BGR_Arr[4]; 
    BGR_Arr[4] = BGR_Arr[3];
    BGR_Arr[3] = BGR_Arr[2]; 
    BGR_Arr[2] = BGR_Arr[1]; 
    BGR_Arr[1] = BGR_Arr[0];
    
    if( (BGR_Avg_1 > (B_Gap_Ratio * 0.8)) && (BGR_Avg_1 < (B_Gap_Ratio * 1.2)) )
    {
        BGR_Arr[0] = B_Gap_Ratio; 
    }
    
    BGR_Avg = (BGR_Arr[29] + BGR_Arr[28] + BGR_Arr[27] + BGR_Arr[26] + BGR_Arr[25] + BGR_Arr[24] + BGR_Arr[23] + BGR_Arr[22] 
                + BGR_Arr[21] + BGR_Arr[20] + BGR_Arr[19] + BGR_Arr[18] + BGR_Arr[17] + BGR_Arr[16] + BGR_Arr[15] 
                + BGR_Arr[14] + BGR_Arr[13] + BGR_Arr[12] + BGR_Arr[11] + BGR_Arr[10] + BGR_Arr[9] + BGR_Arr[8] + BGR_Arr[7] 
                + BGR_Arr[6] + BGR_Arr[5] + BGR_Arr[4] + BGR_Arr[3] + BGR_Arr[2] + BGR_Arr[1] + BGR_Arr[0]);
    
    BGR_Avg = (BGR_Avg / 30);        
    B_Rad = ((BGR_Avg * 2 * 3.1412) - SD_Phase_Shift);          //radians
    B_Power_Factor = (cos(B_Rad));                              //PowerFactor 
    
//    if(B_Power_Factor < 0)
//    {
//        B_Power_Factor = ((-1) * B_Power_Factor);
//    }
}

void Power_Factor(void)
{
    if ( Avg_RYB_Current > 0.5)
    {
        Total_Power_Factor = ((R_Power_Factor + Y_Power_Factor + B_Power_Factor) / 3);
    }
    else
    {
        Total_Power_Factor = 0;
        Y_Power_Factor = 0;
    }
}

//void Lead_Lag_Cal(void)
//{
//    if(Y_C_Gap < (Y_V_Gap/2))
//    {
//        PF_Lead_Lag = 0;    //Lag
//    }
//
//    else if(Y_C_Gap > (Y_V_Gap/2))
//    {
//        PF_Lead_Lag = 1;    //Lead
//    }
//}

void Power_Calc(void)
{
    KW = ((Avg_RYB_Voltage * Avg_RYB_Current * Total_Power_Factor * 1.732) / 1000);
    KVA = (((Avg_RYB_Voltage * Avg_RYB_Current)*1.732) / 1000);
    KVAr = (sqrt ((KVA * KVA)-(KW * KW)));
    Y_KW = ((Avg_RYB_Voltage * Avg_RYB_Current * Y_Power_Factor * 1.732) / 1000);
}
void PM_Error_Led(void)
{
    if ((Phase_Sequence_Ok == 0) || (R_Volt <= UNDER_VOLTAGE_LIMIT) || (Y_Volt <= UNDER_VOLTAGE_LIMIT) || 
            (B_Volt <= UNDER_VOLTAGE_LIMIT) || (R_Volt >= OVER_VOLTAGE_LIMIT) || (Y_Volt >= OVER_VOLTAGE_LIMIT) || 
            (B_Volt >= OVER_VOLTAGE_LIMIT) || (R_Curr >= GRID_OVER_CURRENT_LIMIT) || (Y_Curr >= GRID_OVER_CURRENT_LIMIT) || 
            (B_Curr >= GRID_OVER_CURRENT_LIMIT) || (Frequency <= FREQUENCY_LOW_LIMIT) || (Frequency >= FREQUENCY_HIGH_LIMIT) || (KW <= MINIMUM_KW) || 
            (KW >= MAXIMUM_KW ))
    {
        PM_Error_LED_ON;
    }
    else if ((Phase_Sequence_Ok == 1) && (R_Volt >= UNDER_VOLTAGE_LIMIT) && (Y_Volt >= UNDER_VOLTAGE_LIMIT) && 
            (B_Volt >= UNDER_VOLTAGE_LIMIT) && (R_Volt <= OVER_VOLTAGE_LIMIT) && (Y_Volt <= OVER_VOLTAGE_LIMIT) && 
            (B_Volt <= OVER_VOLTAGE_LIMIT) && (R_Curr <= GRID_OVER_CURRENT_LIMIT) && (Y_Curr <= GRID_OVER_CURRENT_LIMIT) && 
            (B_Curr <= GRID_OVER_CURRENT_LIMIT) && (Frequency >= FREQUENCY_LOW_LIMIT) && (Frequency <= FREQUENCY_HIGH_LIMIT) && (KW >= MINIMUM_KW) && 
            (KW <= MAXIMUM_KW ))
    {
        PM_Error_LED_OFF;
    }
}
void Capacitor_Adding (void)
{
    if(Capacitor_Counter < 40 && Turbine_state == RUNNING_STATE)
    {
        Capacitor_Counter++;   
    }
    if(Turbine_state != RUNNING_STATE )
    {
        CAP_OFF;
        Capacitor_Counter = 0;
    }
    if(Capacitor_Counter == 40 && Turbine_state == RUNNING_STATE)              //30 for 1 Sec Timer delay
    {
        CAP_ON;
        Five_Second_flag = 1;
    }
    else if(Capacitor_Counter < 40 || Turbine_state != RUNNING_STATE) 
    {
        Five_Second_flag = 0;
    }
}