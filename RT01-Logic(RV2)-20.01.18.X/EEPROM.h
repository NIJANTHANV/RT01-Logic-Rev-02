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
#ifndef EEPROM_H
#define	EEPROM_H

#include <xc.h> // include processor files - each processor file is guarded. 

#define GENERATOR_FB_EP_ADD (0x01)
#define PITCH_FB_EP_ADD     (0x02)

#define MINUTE1_ADD         (0x11)
#define MINUTE2_ADD         (0x12)
#define MINUTE3_ADD         (0x13)

#define HOURS1_ADD         (0x14)
#define HOURS2_ADD         (0x15)
#define HOURS3_ADD         (0x16)

#define ERROR1_ADD         (0x17)
#define ERROR2_ADD         (0x18)
#define ERROR3_ADD         (0x19)

#define EEPROM_ERROR_ADD   (0x20)

#define START_STOP_KEY_ADD (0x21)

char Gen_EP_Err_Flag = 0,Pitch_EP_Err_Flag = 0,Feedback_Error = 0, One_Time_Flag = 0, EEPROM_Error_Flag = 0;
char Temp_1 = 0, Temp_2 = 0,Temp_3 = 0,Temp_4 = 0,Hours = 0,Minutes = 0,Temp_5 = 0,Temp_6 = 0,Minutes_1 = 0,Total_Min = 0;
char EP_Errors3 = 0, EP_Errors2 = 0, EP_Errors1 = 0,Start_Stop_Flag_1 = 0;
int GiMinutes_3 = 0,GiMinutes_2 = 0,GiMinutes_1 = 0,GiHours_3 = 0,GiHours_2 = 0,GiHours_1 = 0;
int Hours_2 = 0,Hours_1 = 0;

void EEPROM_Error_Stop (void);
unsigned int int_eeprom_read(unsigned int adr) ;
unsigned int int_eeprom_write(unsigned int adr, unsigned int dat);
void EEPROM_Error_Monitor (void);
void Last_3_EEPROM_ERROR_Trigger (void);
#endif	/* XC_HEADER_TEMPLATE_H */

