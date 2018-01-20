/*
 * File:   RTC.c
 * Author: nijanthan.v
 *
 * Created on April 17, 2017, 1:35 PM
 */


#include <xc.h>
#include "RTC.h"
#include "IO_Def.h"

unsigned int BCDtoI(unsigned int BCD)
{
unsigned int result;
    result=(BCD>>12)*1000;
    result+=((BCD>>8)&0x0f)*100;
    result+=((BCD>>4)&0x0f)*10;
    result+=((BCD)&0x0f);
    return result;
}    
void RTC_Init(void)
{
    I2C_Init();                             // Initialize the I2c module.
    I2C_Start();                            // Start I2C communication

    I2C_Write(C_Ds1307WriteMode_U8);        // Connect to DS1307 by sending its ID on I2c Bus
    I2C_Write(C_Ds1307ControlRegAddress_U8);// Select the Ds1307 ControlRegister to configure Ds1307

    I2C_Write(0x00);                        // Write 0x00 to Control register to disable SQW-Out

    I2C_Stop();                             // Stop I2C communication after initializing DS1307
}

void RTC_SetDateTime(rtc_t *rtc)
{
    I2C_Start();                          // Start I2C communication

    I2C_Write(C_Ds1307WriteMode_U8);      // connect to DS1307 by sending its ID on I2c Bus
    I2C_Write(C_Ds1307SecondRegAddress_U8); // Request sec RAM address at 00H

    I2C_Write(rtc->sec);                    // Write sec from RAM address 00H
    I2C_Write(rtc->min);                    // Write min from RAM address 01H
    I2C_Write(rtc->hour);                    // Write hour from RAM address 02H
    I2C_Write(rtc->weekDay);                // Write weekDay on RAM address 03H
    I2C_Write(rtc->date);                    // Write date on RAM address 04H
    I2C_Write(rtc->month);                    // Write month on RAM address 05H
    I2C_Write(rtc->year);                    // Write year on RAM address 06h

    I2C_Stop();                              // Stop I2C communication after Setting the Date
}
    
void RTC_GetDateTime(rtc_t *rtc)
{
    I2C_Start();                            // Start I2C communication

    I2C_Write(C_Ds1307WriteMode_U8);        // connect to DS1307 by sending its ID on I2c Bus
    I2C_Write(C_Ds1307SecondRegAddress_U8); // Request Sec RAM address at 00H

    I2C_Stop();                                // Stop I2C communication after selecting Sec Register

    I2C_Start();                            // Start I2C communication
    I2C_Write(C_Ds1307ReadMode_U8);            // connect to DS1307(Read mode) by sending its ID

    rtc->sec = I2C_Read(1);                // read second and return Positive ACK
    rtc->min = I2C_Read(1);                 // read minute and return Positive ACK
    rtc->hour= I2C_Read(1);               // read hour and return Negative/No ACK
    rtc->weekDay = I2C_Read(1);           // read weekDay and return Positive ACK
    rtc->date= I2C_Read(1);              // read Date and return Positive ACK
    rtc->month=I2C_Read(1);            // read Month and return Positive ACK
    rtc->year =I2C_Read(0);             // read Year and return Negative/No ACK

    I2C_Stop();                              // Stop I2C communication after reading the Date
}
void I2C_Init()
{
	SCL_Direction = 1;
	SDA_Direction = 1;

	SSP1STAT |= 0x80;  /* Slew rate disabled */
	SSP1CON1 = 0x28;    /* SSPEN = 1, I2C Master mode, clock = FOSC/(4 * (SSPADD + 1)) */
	SSP1ADD = 24;      /* 100Khz @ 20Mhz Fosc */
}
void I2C_Restart()
{
	SSP1CON2bits.RSEN = 1;        /* Repeated start enabled */
	while(SSP1CON2bits.RSEN);     /* wait for condition to finish */
}
uint8_t I2C_Read(uint8_t v_ackOption_u8)
{
	uint8_t  v_i2cData_u8=0x00;

	SSP1CON2bits.RCEN = 1;                   /* Enable data reception */
	while(SSP1STATbits.BF==0);               /* wait for data to be received */
	v_i2cData_u8 = SSP1BUF;    /* copy the received data */
	i2c_WaitForIdle();          /* wait till current operation is complete*/
	      
	if(v_ackOption_u8==1)     /*Send the Ack/NoAck depending on the user option*/
	{
		i2c_Ack();
	}
	else
	{
		i2c_NoAck();
	}

	return v_i2cData_u8;       /* Finally return the received Byte */
}
void I2C_Write(uint8_t v_i2cData_u8)
{


    SSP1BUF = v_i2cData_u8;  /* Copy the data to be transmitted into SSPBUF */
    while(SSP1STATbits.BF==1);             /* wait till the data is transmitted */
    i2c_WaitForIdle();        /* wait till current operation is complete*/
}
static void i2c_WaitForIdle()
{
    while ( (SSP1CON2bits.SEN == 1) || (SSP1CON2bits.RSEN == 1) || (SSP1CON2bits.PEN == 1) || (SSP1CON2bits.RCEN == 1) || (SSP1STATbits.R_W == 1) );
    /* wait till I2C module completes previous operation and becomes idle */
}								
static void i2c_NoAck()
{
	SSP1CON2bits.ACKDT = 1;            /* Acknowledge data bit, 1 = NAK/NoAK */
	SSP1CON2bits.ACKEN = 1;            /* Ack data enabled */
	while(SSP1CON2bits.ACKEN == 1);    /* wait for ack data to send on bus */
}
static void i2c_Ack()
{
	SSP1CON2bits.ACKDT = 0;            /* Acknowledge data bit, 0 = ACK */
	SSP1CON2bits.ACKEN = 1;            /* Ack data enabled */
	while(SSP1CON2bits.ACKEN == 1);    /* wait for ack data to send on bus */
}
void I2C_Start()
{
	SSP1CON2bits.SEN = 1;              /* trigger the Start condition and wait till its completed*/
	while(SSP1CON2bits.SEN == 1);      /* automatically cleared by hardware once start condition is completed */

}
void I2C_Stop(void)
{
	SSP1CON2bits.PEN = 1;              /* Trigger stop condition, Wait till stop condition to finished*/
	while(SSP1CON2bits.PEN == 1);      /* PEN automatically cleared by hardware once stop condition is finished*/
}