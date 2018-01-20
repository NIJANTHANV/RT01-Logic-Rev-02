/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef Power_Meter_H
#define	Power_Meter_H

#include <xc.h> // include processor files - each processor file is guarded.  

#include <math.h>


#define KV_Constant (0.92557)//(0.89172) // 60Hz(0.727749)
#define KC_Constant (0.03785)

#define V_Shifted_Bits (2034)
#define C_Shifted_Bits (2034)

#define Temperature_Constant (0.122589)

#define Phase_Shift_120 (1666.667)  // For 120degree ==> ((120*20)/360)=6.67ms, 65535/262.14ms = 250.13 ==> (6.67* 250.13) = 1666.667

#define SD_Phase_Shift (0.523599)   // SD Phase shift degree ==> ((360*1.67ms))/20)) = 30degree = 0.523599 in radian

#define PM_Error_LED_ON (RF7 = 1)
#define PM_Error_LED_OFF (RF7 = 0)

unsigned int Temp_Sensor = 0;
float Temprature = 0,Temp_Arr[6],Temperature_Avg = 0;

unsigned short int R_V = 0,Y_V = 0,B_V = 0,R_C = 0,Y_C = 0,B_C = 0;
float R_V_Max = 0,R_C_Max = 0,Y_V_Max = 0,Y_C_Max = 0,B_V_Max = 0,B_C_Max = 0;
char i = 0,Case_Call = 1,Volt_Curr_Flag = 0;
float R_V_Arr[3],R_C_Arr[3],Y_V_Arr[3],Y_C_Arr[3],B_V_Arr[3],B_C_Arr[3];
float R_V_Avg_Steps = 0,R_Volt = 0,R_C_Avg_Steps = 0,R_Curr = 0;
float Y_V_Avg_Steps = 0,Y_Volt = 0,Y_C_Avg_Steps = 0,Y_Curr = 0;
float B_V_Avg_Steps = 0,B_Volt = 0,B_C_Avg_Steps = 0,B_Curr = 0;
float Avg_RYB_Voltage = 0,Avg_RYB_Current = 0;

unsigned short int RV_PS = 0,YV_PS = 0,BV_PS = 0,RV_PS_Max = 0,YV_PS_Max = 0,BV_PS_Max = 0,R_Peak = 0,Y_Peak = 0,B_Peak = 0;
char PS = 0,Phase_Sequence_Ok = 0,Consumption = 0;

float R_V_Old = 0,R_V_New = 0,Time_Diff = 0,Time_New = 0,Time_Old = 0,Frequency = 0;
char Freq_Flag = 0;

float Y_V_Old = 0,Y_V_New = 0;
float B_V_Old = 0,B_V_New = 0;

float Rcurr_Old = 0,Rcurr_New = 0,Rcurr_V_Old = 0,Rcurr_V_New = 0;
float Ycurr_Old = 0,Ycurr_New = 0,Ycurr_V_Old = 0,Ycurr_V_New = 0;
float Bcurr_Old = 0,Bcurr_New = 0,Bcurr_V_Old = 0,Bcurr_V_New = 0;
float R_V_Gap = 0,R_C_Gap = 0,R_Gap_Ratio = 0,R_Deg = 0,R_Rad = 0,R_Power_Factor = 0;
float Y_V_Gap = 0,Y_C_Gap = 0,Y_Gap_Ratio = 0,Y_Deg = 0,Y_Rad = 0,Y_Power_Factor = 0;
float B_V_Gap = 0,B_C_Gap = 0,B_Gap_Ratio = 0,B_Deg = 0,B_Rad = 0,B_Power_Factor = 0,Total_Power_Factor = 0;
char R_PF_Flag = 0,Y_PF_Flag = 0,B_PF_Flag = 0,PF_Lead_Lag = 0;
float RGR_Arr[30],YGR_Arr[30],BGR_Arr[30],RGR_Arr_1[5],YGR_Arr_1[5],BGR_Arr_1[5];
float RGR_Avg = 0,YGR_Avg = 0,BGR_Avg = 0,RGR_Avg_1 = 0,YGR_Avg_1 = 0,BGR_Avg_1 = 0;

float KW = 0,KVA = 0,KVAr = 0,Avg_Voltage = 0,Avg_Current = 0,Y_KW = 0;

void PM_IO_Initialization(void);
void PM_Timer_Initialization(void);
void PM_ADC_Initialization(void);
unsigned int Read_Adc(unsigned char ch);

void Temp_Read(void);

void Volt_Curr_Read(void);
void Volt_Curr_Avg(void);
void Phase_Sequence(void);
void Cons_Gene(void);

void Freq_Calc(void);

void R_PF_Calc(void);
void Y_PF_Calc(void);
void B_PF_Calc(void);

void R_PF_Avg(void);
void Y_PF_Avg(void);
void B_PF_Avg(void);

void Power_Factor(void);

void Power_Calc(void);

//void Lead_Lag_Cal(void);
void PM_Error_Led(void);
void Capacitor_Adding (void);

#endif	/* XC_HEADER_TEMPLATE_H */

