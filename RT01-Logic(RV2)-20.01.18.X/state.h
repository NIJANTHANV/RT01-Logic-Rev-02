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
 * File: STATE HANDLE   
 * Author: R.VIMAL
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef STATE_H
#define	STATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

typedef enum
{
    STARTUP_STATE,
    RAMPUP_STATE,
    RUNNING_STATE,
    STOPPING_STATE        
}state_h; 

state_h Turbine_state = STARTUP_STATE;
float GfR_volt,GfY_volt,GfB_volt,GfR_current,GfY_current,GfB_current,GfKw,GfKva,GfKvar = 0;
float GfT_rpm,GfG_rpm,Gfwind = 0;
unsigned char GCT_rpm_flag,GCG_rpm_flag,GCR_phasev_flag,GCY_phasev_flag,GCB_phasev_flag,GCWind_flag,GCphase_flag = 0;
unsigned char GCvfd_curr_flag,GCM_slip_flag,GCR_slip_flag,GCDc_low_flag,GCDc_high_flag = 0;
char VFD_On_Off = 0,Desired_Frequency = 0,Stopping_Counter = 0;

void startup_state_function();
void Rampup_state_function();
void Running_state_function();
void Stopping_state_function();


#endif	/* XC_HEADER_TEMPLATE_H */

