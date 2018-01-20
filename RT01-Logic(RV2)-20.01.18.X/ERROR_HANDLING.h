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
#ifndef ERROR_HANDLING_H
#define	ERROR_HANDLING_H

#include <xc.h> // include processor files - each processor file is guarded.  


typedef enum Errors
{
     NO_ERROR,                //0                 
     WS_MIN_MAX,              //1
     VOLT_LOW,                //2    
     DCB_L_H,                 //3
     VFD_RUN_TIME,            //4
     VFD_COMMU_ERR,           //5
     VFD_SHORT_CIRCUIT,       //6
     DC_EXT_LOW,              //7
     VFD_OC,                  //8
     CURRENT_H,               //9
     TURBINE_US_OS,           //10
     GEN_OS,                  //11
     FREQ,                    //12
     PHASE_SEQ,               //13
     POWER_MAX,               //14
     POWER_MIN,               //15
     MOTOR_SLIP,              //16
     ROTOR_SLIP,              //17
     TURBINE_OL,              //18
     MANUAL_STOP,             //19
     GEN_FB,                  //20
     PITCH_FB,                //21
     MEAURE_ERR,              //22
     TURBINE_NR,              //23
     VOLT_HIGH,               //24
     VFD_ERROR_IO             //25
}ErrorsNo;

ErrorsNo Errors = NO_ERROR;
float Gf_KW;
char OV_Counter = 0, S_S_Counter = 0, Start_Stop_Flag = 0, KW_Minimum_Error = 0,KW_Counter = 0,KW_Maximum_Error = 0,Turbine_Restore_Error = 0;
char Wind_Cut_In_Flag = 0,Wind_Cut_Out_Flag = 0,Gf_Wind_Cut_In_Counter = 0;
float Gf_Red_Phase_Voltage,Gf_Yellow_Phase_Voltage,Gf_Blue_Phase_Voltage,Gf_Grid_Frequency;
char Grid_Ovr_voltage = 0,Grid_Und_voltage = 0,Turbine_Over_Speed_Flag = 0,TRPM_Under_Speed_Counter = 0;
char Turbine_Under_Speed_Flag = 0,Grid_UV_Counter = 0;
char Grid_Ov_Counter = 0, Frequency_Error_counter = 0, Grid_Frequency_Error = 0, Grid_Over_current = 0;
char TRPM_OverSpeed_Counter = 0,Generator_Over_Speed = 0,Tur_OverLoaded_Error = 0,Gc_Grid_Phase_Unbalance_Error = 0,Gc_Grid_Phase_Unbalance  =0;
float Gf_Red_Current,Gf_Yellow_Current,Gf_Blue_Current;
char lc_Avg_Counter = 0,Gc_Turbine2Wheel_Ratio_Error = 0;
float Turbine2Wheel_Ratio_Avg = 0, Gf_Turbine2Wheel_Ratio = 0; 
char Generator_One_Counter = 0,Generator_One_Feedback_Error  = 0,Gc_Generator_One_Fb = 0;
char lc_Pitch_Coil_Counter = 0,Gc_Pitch_Coil_Feedback_Error = 0,Gc_Pitch_Coil_Fb = 0;
float lc_Previous_T_RPM = 0,lc_Current_T_RPM = 0,lc_T_RPM = 0;
char Gc_TRPM_Rampup_Error = 0,Grid_Phase_Sequence_Error = 0,T_Overload_counter = 0;
char VFD__Run_Time_Error = 0,DC_BUS_Low_Counter = 0,DC_BUS_High_Counter = 0,VFD_DC_EXTREM_LOW_Error = 0;
char VFD_DC_Bus_Low_Error = 0,VFD_DC_Bus_High_Error = 0,KW_Counter_Max = 0;
unsigned int VFD_Run_Time_Counter = 0;
char lc_Motor_Slip_Error_Counter = 0,Gc_Motor_Slip_Error = 0,lc_Rotor_Slip_Error_Counter = 0,Gc_Rotor_Slip_Error = 0;
char lcDC_Bus_Counter  =0, Gc_VFD_DC_Bus_Error = 0,Wind_Cut_Out_Counter = 0,DC_BUS_Current_Counter = 0,VFD_DC_Bus_Current_Error = 0;
float Gf_Motor_Slip,Gf_Rotor_Slip,Gf_VFD_DC_Bus_Voltage;
char Start_up_Error = 2,DC_Bus_Voltage_Flag = 0,VFD_Error_Flag = 0,PW_Error_Flag = 0,G_RPM_Counter = 0;
unsigned int Initial_Delay_Second = 0,VFD_SHORT_CIRCUIT_fLAG = 0;
char Errors4 = 0,Errors3 = 0,Errors2 = 0,Errors1 = 0,Errors5 = 0;
char Pitch_FB_Error_counter = 0,Pitch_FB_Error_Flag = 0;
char Key_Counter = 0,Key_Flag = 0;

void Start_Stop (void);
void Error_Checking_Interrupt_Overflow (void);
void Error_Checking_One_Second (void);
void VFD_Run_Time_Error (void);
void Turbine_Restore_Check (void);
void Wind_Speed_Error_Trigger (void);

void Turbine_Over_Speed (void);
void Turbine_Under_speed (void);
void Grid_OV (void);
void Grid_UV (void);
void Grid_Frequency (void);
void Grid_Over_Current (void);
void Generator_RPM (void);
void Grid_Minimum_Power (void);
void Grid_Maximum_Power (void);
void Turbine_OverLoaded_Error (void);
void Grid_Phase_Sequence (void);
void Rotor_Slip (void);
void Motor_Slip (void);
void DC_Bus_Voltage (void);
void Turbine2Wheel_Ratio (void);
void Pitch_Solenoid_Feedback (void);
void Generator_One_Feedback (void);
void Feedback_Check (void);
void Turbine_RPM_Checking_Rampup (void);
void Error_Scan_start_up (void);
void VFD_IO_Error (void);
void PW_Error_IO (void);
void Last_Five_Error (void);
void Pitch_Feedback (void);
#endif	/* XC_HEADER_TEMPLATE_H */

