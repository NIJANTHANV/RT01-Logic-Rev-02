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
 * File:                UART    
 * Author:              
 * Comments:            Initiate
 * Revision history:    00
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef UART_H
#define	UART_H

#include <xc.h> // include processor files - each processor file is guarded.  

unsigned int Serial_No,digit1,digit2,digit3,digit4,digit5;
unsigned char Communication_OTP = 0;
char GcHour,GcMin,GcSec, GcDate,GcMonth,GcYear;
char Phase_Angle = 0;
float Frequency_1;
float R_Current = 0,Y_Current = 0,B_Current = 0,R_Current_1 = 0,Y_Current_1 = 0,B_Current_1 = 0;


int GiHours,GiMinutes,GiSeconds,GiData,GiMonth,GiYear,GiDay;
extern char Check;
float KW_1,KW,KVA,KVA_1,KVAr_1,KVAr,Total_Pf_1,Total_Pf;
unsigned char VFD_Frequency = 0,VFD_Error_No = 0;
float DC_Bus_Current = 0;
char KVA_Sign = 0;
float Temp_sign;
unsigned int VFD_Bus_Voltage = 0;
typedef enum someName
 {
    INT_DATA_TYPE = 0,
    FLOAT_DATA_TYPE,
    DOUBLE_DATA_TYPE,
    STRING_DATA_TYPE
} ;

void usart_str(const char*str);
void usart_init();
void usart_str_1(const char str);
void usart2_init();
void UART_Data (void);
void vDisplayAscii (float Data, int Storage_Type);
void putch2(char data);
void putch1(char data);
void usart2_str(const char*str);
void usart_str_2(const char str);
void Power_Meter_RS485_Data_Cal (void);
void VFD_RS485_Data (void);
void UART_Data_String (void);
void VFD_RS485_Data_filter (void);
#endif	/* XC_HEADER_TEMPLATE_H */

