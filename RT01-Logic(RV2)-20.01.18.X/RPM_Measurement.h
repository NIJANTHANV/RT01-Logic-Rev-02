/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef RPM_Measurement_H
#define	RPM_Measurement_H

#include <xc.h>        // include processor files - each processor file is guarded.  
#define TRPM_NO_OF_SENSING_POINTS (4)

#define GRPM_NO_OF_SENSING_POINTS (2)

#define Wind_NO_OF_SENSING_POINTS (6)


unsigned int Gi_TRPM_Cap = 0,Gi_TRPM_Pulse_width = 0,G_RPM_counter_1 = 0;
float Gf_TRPM_Time = 0,Gf_TRPM_Time_1 = 0,Gf_TRPM_Frequency = 0,Turbine_RPM = 0,Wind = 0;

float Wind_Speed_10 = 0,Wind_Speed_9 = 0,Wind_Speed_8 = 0,Wind_Speed_7 = 0,Wind_Speed_6 = 0,Wind_Speed_Avg = 0;
float Wind_Speed_5 = 0,Wind_Speed_4 = 0,Wind_Speed_3 = 0,Wind_Spd_2 = 0,Wind_Speed_1 = 0,Wind_Speed_0 = 0;


float Wind_Speed_2 = 0 , Wind_Speed_10_2 = 0,Wind_Speed_9_2 = 0,Wind_Speed_8_2 = 0,Wind_Speed_7_2 = 0,Wind_Speed_6_2 = 0,Wind_Speed_Avg_2 = 0;
float Wind_Speed_5_2 = 0,Wind_Speed_4_2 = 0,Wind_Speed_3_2 = 0,Wind_Speed_2_2 = 0,Wind_Speed_1_2 = 0,Wind_Speed_0_2 = 0;

float Gf_Turbine_RPM_1 = 0,Turbine_RPM_New = 0,Gf_Turbine_RPM_Prev = 0;
float Turb_RPM = 0, Turbine_RPM_Old = 0;
unsigned int Generator_RPM_INT = 0;
unsigned int WRPM_Counter_1 = 0, WRPM_Counter = 0;

unsigned int GRPM_Cap = 0,GRPM_Pulse_width = 0,Pitching_FlAG = 0;
float GRPM_Time = 0,GRPM_Time_1 = 0,GRPM_Frequency = 0,Generator_RPM_FLT = 0;

unsigned int Wind_Cap = 0,Wind_Pulse_width = 0;
float Wind_Time = 0,Wind_Time_1 = 0,Wind_Frequency = 0,Wind_Speed = 0;

unsigned int Wind_Cap_2 = 0,Wind_Pulse_width_2 = 0,Pitch_Counter = 0;
float Wind_Time_2 = 0,wind_Time_1_2 = 0,wind_Frequency_2 = 0, wind_2=0;

char T_RPM_counter = 0,G_RPM_counter = 0,Timer1_interrupt_flag = 0,Ten_Sec_Counter_2 = 0,Ten_Sec_Counter = 0;


unsigned int TRPM_Cap_New = 0,TRPM_Cap_Old = 0,Gi_Timer1_OF_counter = 0;
unsigned int Timer1_OF_counter_New = 0,Timer1_OF_counter_Old = 0;
char TRPM_Cal = 0,RPM_counter = 0,wind_1_Temp_flag = 0,wind_2_Temp_flag = 0;

unsigned int RPM_Time = 0,RPM_PWM = 0,RPM_Time_1 = 0,Flag_temp = 0;
float TRPM_Time = 0,TRPM_Frequency = 0,PWM_Temp = 0;

float  Generator_RPM_0 = 0, Generator_RPM_5 = 0, Generator_RPM_4 = 0, Generator_RPM_3 = 0, Generator_RPM_2 = 0, Generator_RPM_1 = 0; 
float  Generator_RPM_10 = 0,Generator_RPM_9 = 0, Generator_RPM_8 = 0, Generator_RPM_7 = 0, Generator_RPM_6 = 0;
float Generator_RPM_Old = 0, Generator_RPM_New = 0;

void Turbine_RPM_Initiate (void);
void Turbine_RPM_Cal(void);
void Generator_RPM_Cal(void);
void Wind_Speed_Cal(void);
void Wind_Average (void);
void RPM_Data_Kill (void);
#endif	/* XC_HEADER_TEMPLATE_H */

