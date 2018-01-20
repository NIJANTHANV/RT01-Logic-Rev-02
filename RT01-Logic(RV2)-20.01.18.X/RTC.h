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
 * File:                RTC 
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef RTC_H
#define	RTC_H

#include <xc.h> // include processor files - each processor file is guarded.  
typedef signed char     sint8_t;
typedef unsigned char   uint8_t;

typedef signed int      sint16_t;
typedef unsigned int    uint16_t;

typedef signed long int    sint32_t;
typedef unsigned long int  uint32_t;

typedef struct
{
  uint8_t sec;
  uint8_t min;
  uint8_t hour;
  uint8_t weekDay;
  uint8_t date;
  uint8_t month;
  uint8_t year;  
}rtc_t;


#define C_Ds1307ReadMode_U8   0xD1u  // DS1307 ID
#define C_Ds1307WriteMode_U8  0xD0u  // DS1307 ID

#define C_Ds1307SecondRegAddress_U8   0x00u   // Address to access Ds1307 SEC register
#define C_Ds1307DateRegAddress_U8     0x04u   // Address to access Ds1307 DATE register
#define C_Ds1307ControlRegAddress_U8  0x07u   // Address to access Ds1307 CONTROL register


#define SCL RC3		//SCL Connected to PORTC.3
#define SDA RC4 	//SDA Connected to PORTC.4

#define SCL_Direction TRISC3
#define SDA_Direction TRISC4

rtc_t rtc;

static void i2c_WaitForIdle();
static void i2c_Ack();
static void i2c_NoAck();
void I2C_Init();
void I2C_Start();
void I2C_Stop(void);
void I2C_Write(uint8_t );
uint8_t I2C_Read(uint8_t);
void I2C_Restart();
unsigned int BCDtoI(unsigned int BCD);
void RTC_Init(void);
void RTC_SetDateTime(rtc_t *rtc);
void RTC_GetDateTime(rtc_t *rtc);
#endif	/* XC_HEADER_TEMPLATE_H */

