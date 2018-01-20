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
#ifndef Initialization_H
#define	Initialization_H

#include <xc.h> // include processor files - each processor file is guarded.  

////////******************************////////////
#define INITIAL_DELAY                (120)
#define VFD_PS_DELAY                 (INITIAL_DELAY - 20)
#define PITCH_PS_CUT_IN_WIND         (4) // m/sec0
#define PITCH_PS_OFF_DELAY           (80) // m/sec

#define CUT_IN_WIND                 (4.5) // m/sec
#define CUT_Out_WIND                (15) //m/sec

#define WIND_1_CD_FACTOR            (143)
#define WIND_2_CD_FACTOR            (143)

#define OVER_VOLTAGE_LIMIT          (450)
#define UNDER_VOLTAGE_LIMIT         (370)
#define GRID_OVER_CURRENT_LIMIT     (12)
#define MEASUREMENT_ERROR_CURRENT_LIMIT (0.7)
#define FREQUENCY_LOW_LIMIT         (47.5)
#define FREQUENCY_HIGH_LIMIT         (52.5)

#define TURBINE_OVER_SPEED_LIMIT    (63)
#define TURBINE_UNDER_SPEED_LIMIT   (47)


#define MINIMUM_KW                   (-5.0)
#define MAXIMUM_KW                   (6.0)
#define TURBINE_OVERLOADED_SET_LIMIT (-5.0)

#define VFD_RUN_TIME_SECOND          (300)
#define DEFUALT_FREQUENCY            (8)

#define TURBINE_2_WHEEL_RATIO        (17.54)
#define NO_OF_POLE                   (6)
#define GENERATOR_OVER_SPEED_LIMIT   (1060)

#define WIND_10_SEC_INITIAL_DELAY    (10)

#define ROTOR_SLIP_PERCENTAGE        (-9.0)
#define MOTOR_SLIP_PERCENTAGE        (-8.0)
#define SLIP_ERROR_TIME_DELAY        (60)

#define RAMPUP_INITIAL_DELAY         (10)

#define EEPROM_LAST_3_ERROR_TIME_DELAY (15)

///********PIN********///
#define VFD_IN_ON  (RD0 = 1)
#define VFD_IN_OFF (RD0 = 0)

#define VFD_OUT_ON  (RD1 = 1)
#define VFD_OUT_OFF (RD1 = 0)

#define GRID_ON  (RD2 = 1)
#define GRID_OFF (RD2 = 0)

#define PITCH_ENABLE (RB0 = 1)
#define PITCH_DISABLE (RB0 = 0)

#define VFD_PS_ON  (RB4 = 1)
#define VFD_PS_OFF (RB4 = 0)

#define PITCH_PS_ON  (RB5 = 1)
#define PITCH_PS_OFF (RB5 = 0)

#define CAP_ON  (RF1 = 1)
#define CAP_OFF (RF1 = 0)


unsigned int T1;
float Timer_1_OverFlow_Time = 0, Timer1_Time_per_Count = 0;
void OSCILLATOR ( void);
void Timer1_Initiate(void);

void Pitch_Solenoid_init();
void VFD_Contactor_IO_init();
void Generator_IO_init();
void VFD_Error_IO (void);
void Power_Meter_Error_IO (void);
void Timer7_Init(void);
#endif	/* XC_HEADER_TEMPLATE_H */

