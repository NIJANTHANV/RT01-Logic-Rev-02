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
#ifndef ISR_H
#define	ISR_H

#include <xc.h> // include processor files - each processor file is guarded.  
unsigned int Timer1_OF_counter_Wind_2 = 0,Timer1_OF_counter_Turbine = 0,Timer1_OF_counter_Generator = 0,Timer1_OF_counter_Wind = 0,Capacitor_Counter = 0;

unsigned int Gi_TRPM_Cap_New = 0,Gi_TRPM_Cap_Old =0,Timer1_counter = 0;

unsigned int GRPM_Cap_Old = 0, GRPM_Cap_New = 0;

unsigned int Wind_Cap_New = 0,Wind_Cap_Old = 0;

unsigned int Gi_Timer1_OF_counter_Generator_Temp = 0,Timer1_OF_counter_Generator_New = 0,Timer1_OF_counter_Generator_Old = 0,GRPM_Counter = 0;
        
unsigned int Wind_Cap_New_2 = 0,Wind_Cap_Old_2 = 0;

unsigned int Dummy = 0, data = 0,Slave_Id, Data[30],Data_1[11],counter =0,VFD_Counter = 24,Timer0_1Sec_Flag = 0,Timer0_counter,Timer0_RS485_flag = 0;
char One_Sec_Flag = 0, Timer0_Falg1 = 0,Timer0_Falg2 = 0,RS485_Data_Flag = 0,counter_1 = 0,Five_Second_flag = 0;

unsigned int Timer1_OF_counter_Wind_2_temp = 0, Timer1_OF_counter_Wind_2_temp_New = 0, Timer1_OF_counter_Wind_2_temp_Old = 0;
unsigned int Timer1_OF_counter_Wind_temp_New = 0, Timer1_OF_counter_Wind_temp_Old = 0, Timer1_OF_counter_Wind_temp = 0;
char Timer0_RAMPUP_Counter = 0,Ten_Sec_RampUp_Flag = 0;
#endif	/* XC_HEADER_TEMPLATE_H */

