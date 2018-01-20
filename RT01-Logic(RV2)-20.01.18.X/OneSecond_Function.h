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
 * File:                OneSecond Function
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef OneSecond_Function_H
#define	OneSecond_Function_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define WIND_10_SEC_INITIAL_DELAY (10)

char Delay_counter = 0,One_sec_Delay_Flag = 0,One_Sec_Delay_vab = 0;
unsigned int TEMP_1 = 0;
char Two_Sec_Delay_vab = 0,Two_Delay_counter = 0,Two_sec_Delay_Flag = 0;

char Five_Sec_Delay_vab = 0,Five_Delay_counter = 0,Five_sec_Delay_Flag = 0;

void Timer0_OneSecond_Function(void);
void Turbine_Start_up_1_Second ();
void Turbine_Ramp_up_1_Second ();
void One_Sec_Delay (void);
void Two_Sec_Delay (void) ;
void Five_Sec_Delay (void);
#endif	/* XC_HEADER_TEMPLATE_H */

