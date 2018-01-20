/*
 * File:   UART.c
 * Created on April 17, 2017, 5:14 PM
 */


#include <xc.h>
#include "ISR.h"
#include "UART.h"
#include "stdlib.h"
#include "stdio.h"
#include "RTC.h"
#include "Initialization.h"
#include "RPM_Measurement.h"
#include "ERROR_HANDLING.h"
#include "state.h"
#include "RAMP_UP.h"
#include "SLIP_CALCULATIONS.h"
#include "Power_Meter.h"
#include "EEPROM.h"

void UART_Data (void)
{
    if(Serial_No == 3)
    {
        UART_Data_String();
    }
    
    printf("%u",Serial_No);
    usart_str_1(','); 
    
    printf("%s","RT01 Rv3 KAVANOOR");
    usart_str_1(',');
          
    printf("%4.02f",Wind_Speed);
    usart_str_1(',');
    
    printf("%4.02f",Wind_Speed_Avg);
    usart_str_1(',');
    
    printf("%4.02f",Wind_Speed_2);
    usart_str_1(',');
    
    printf("%4.02f",Wind_Speed_Avg_2);
    usart_str_1(',');
    
    printf("%4.02f",Turbine_RPM);
    usart_str_1(',');
    
    printf("%d",Generator_RPM_INT);
    usart_str_1(',');
    
    printf("%4.02f",Motor_slip);
    usart_str_1(',');
    
    printf("%4.02f",Rotor_slip);
    usart_str_1(',');
    
    printf("%d",Desired_Frequency);
    usart_str_1(',');
    
    printf("%d",VFD_Bus_Voltage);
    usart_str_1(',');
    
    printf("%4.01f",DC_Bus_Current);
    usart_str_1(',');
    
    printf("%4.0f",R_Volt);
    usart_str_1(',');
    
    printf("%4.0f",Y_Volt);
    usart_str_1(',');
    
    printf("%4.0f",B_Volt);
    usart_str_1(',');
    
    printf("%4.01f",R_Curr);
    usart_str_1(',');
    
    printf("%4.01f",Y_Curr);
    usart_str_1(',');
    
    printf("%4.01f",B_Curr);
    usart_str_1(',');
    
    printf("%4.02f",KW);
    usart_str_1(',');
    
    printf("%4.02f",Y_KW);
    usart_str_1(',');
    
    printf("%4.02f",KVA);
    usart_str_1(',');
    
    printf("%4.02f",KVAr);
    usart_str_1(',');
    
    printf("%4.02f",Total_Power_Factor);
    usart_str_1(',');
    
    printf("%4.02f",Y_Power_Factor);
    usart_str_1(',');
    
    printf("%4.02f",Frequency);
    usart_str_1(',');
    
    printf("%d",Phase_Sequence_Ok);
    usart_str_1(',');   
    
    printf("%d",VFD_Error_No);
    usart_str_1(',');
    
    printf("%d",Initial_Delay_Second);
    usart_str_1(',');
    
    printf("%d",Errors);
    usart_str_1(',');
    
    switch(Errors) 
    { 
          case NO_ERROR:
          printf("%s","NO_ERROR");
          usart_str_1(',');
          break;
          
          case WS_MIN_MAX:
          printf("%s","WS_MIN_MAX");
          usart_str_1(',');
          break;
          
          case VOLT_HIGH:
          printf("%s","VOLT_HIGH");
          usart_str_1(',');
          break;
          
          case VOLT_LOW:
          printf("%s","VOLT_LOW");
          usart_str_1(',');
          break;
          
          case VFD_SHORT_CIRCUIT:
          printf("%s","VFD_SHORT_CIRCUIT");
          usart_str_1(',');
          break;
          
          case PHASE_SEQ:
          printf("%s","PHASE_SEQ");
          usart_str_1(',');
          break;
          
          case FREQ:
          printf("%s","FREQ");
          usart_str_1(',');
          break;
          
          case TURBINE_NR:
          printf("%s","TURBINE_NR");
          usart_str_1(',');
          break;
          
          case VFD_RUN_TIME:
          printf("%s","VFD_RUN_TIME");
          usart_str_1(',');
          break;
          
          case DCB_L_H:
          printf("%s","DCB_L_H");
          usart_str_1(',');
          break;
          
          case VFD_OC:
          printf("%s","VFD_OC");
          usart_str_1(',');
          break;
          
          case ROTOR_SLIP:
          printf("%s","ROTOR_SLIP");
          usart_str_1(',');
          break;
          
          case MOTOR_SLIP:
          printf("%s","MOTOR_SLIP");
          usart_str_1(',');
          break;
                    
          case TURBINE_US_OS:
          printf("%s","TURBINE_US_OS");
          usart_str_1(',');
          break;
          
          case GEN_OS:
          printf("%s","GEN_OS");
          usart_str_1(',');
          break;
          
          case CURRENT_H:
          printf("%s","CURRENT_H");
          usart_str_1(',');
          break;
          
          case POWER_MAX:
          printf("%s","POWER_MAX");
          usart_str_1(',');
          break;
          
          case POWER_MIN:
          printf("%s","POWER_MIN");
          usart_str_1(',');
          break;
          
          case TURBINE_OL:
          printf("%s","TURBINE_OL");
          usart_str_1(',');
          break;
          
          case DC_EXT_LOW:
          printf("%s","DC_EXT_LOW");
          usart_str_1(',');
          break;
          
          case PITCH_FB:
          printf("%s","PITCH_FB");
          usart_str_1(',');
          break;
          
          case GEN_FB:
          printf("%s","GEN_FB");
          usart_str_1(',');
          break;
          
          case MANUAL_STOP:
          printf("%s","MANUAL_STOP");
          usart_str_1(',');
          break;
          
          case VFD_COMMU_ERR:
          printf("%s","VFD_COMMU_ERR");
          usart_str_1(',');
          break;
          
          case MEAURE_ERR:
          printf("%s","MEAURE_ERR");
          usart_str_1(',');
          break;
          
          case VFD_ERROR_IO:
          printf("%s","VFD_ERROR_IO");
          usart_str_1(',');
          break;
    }
    
    switch(Turbine_state) 
    { 
          case STARTUP_STATE:
          printf("%s","STARTUP");
          usart_str_1(',');
          break;
          
          case RAMPUP_STATE:
          printf("%s","RAMPUP");
          usart_str_1(',');
          break;
          
          case RUNNING_STATE:
          printf("%s","RUNNING");
          usart_str_1(',');
          break;
          
          case STOPPING_STATE:
          printf("%s","STOPPING");
          usart_str_1(',');
          break;
    }
    
    /**************RTC******************/
    RTC_GetDateTime(&rtc);
    GiHours = BCDtoI(rtc.hour);   
    GiMinutes = BCDtoI(rtc.min);
    GiSeconds = BCDtoI(rtc.sec);
    GiData = BCDtoI(rtc.date);
    GiMonth = BCDtoI(rtc.month);
    GiYear = BCDtoI(rtc.year); 
    GiDay = BCDtoI(rtc.weekDay);
    
    printf("%d",GiData);
    usart_str_1('-');
    printf("%d",GiMonth);
    usart_str_1('-');
    printf("%d",GiYear);
    usart_str_1(',');
    
    printf("%d",GiHours);
    usart_str_1(':');
    printf("%d",GiMinutes);
    usart_str_1(':');
    printf("%d",GiSeconds);
    usart_str_1(',');
    
    printf("%4.01f",Temprature);
    usart_str_1(',');
    
    /******To Display Last Five Error*******/
    printf("%d",Errors1);
    usart_str_1('.');
    printf("%d",Errors2);
    usart_str_1('.');
    printf("%d",Errors3);
    usart_str_1('.');
    printf("%d",Errors4);
    usart_str_1('.');
    printf("%d",Errors5);
    usart_str_1(',');
    /****************************************/
    
    
    printf("%d",PORTD);
    usart_str_1(',');
    
    printf("%d",VFD_RAMP);
    usart_str_1(',');
    
    printf("%d",VFD_Run_Time_Counter);
    usart_str_1(',');
        
    printf("%d",Slip_Error_Counter);
    usart_str_1(',');
    
    printf("%d",Slip_Error_Counter_1);
    usart_str_1(',');
    
    printf("%d",Data_1[1]);       //VFD Counter
    usart_str_1(',');
    
    printf("%d",Data_1[7]);       //VFD Counter
    usart_str_1(',');
    
    printf("%d",Communication_OTP);
    usart_str_1(',');
    
    printf("%d",Data_1[9]);
    usart_str_1(',');
    
    printf("%d",Gen_EP_Err_Flag);
    usart_str_1(',');
    
    printf("%d",Pitch_EP_Err_Flag);
    usart_str_1(',');    
    
    printf("%d",Total_Min);
    usart_str_1(',');
    
    printf("%d",EEPROM_Error_Flag);
    usart_str_1(',');     
    
    /******To Display Last Five Error*******/
    printf("%d",EP_Errors1);
    usart_str_1('.');
    printf("%d",EP_Errors2);
    usart_str_1('.');
    printf("%d",EP_Errors3);
    usart_str_1(',');
    /****************************************/
    printf("%d",VFD_Error_Flag);
    usart_str_1(',');

    printf("%d",wind_1_Temp_flag);
    usart_str_1(',');
    
    printf("%d",wind_2_Temp_flag);
    
    usart_str("\r");
    usart_str("\n");
}
void UART_Data_String (void)
{
    usart_str("\r");
    usart_str("\n");
    
    printf("%s","Serial No");
    usart_str_1(','); 
    
    printf("%s","TURBINE ID");
    usart_str_1(',');
    
    printf("%s","WIND_INSTANT");
    usart_str_1(',');
    
    printf("%s","WIND AVG");
    usart_str_1(',');
    
    printf("%s","WIND 2 INSTANT");
    usart_str_1(',');
    
    printf("%s","WIND 2 AVG");
    usart_str_1(',');
    
    printf("%s","TURBINE RPM");
    usart_str_1(',');
    
    printf("%s","GENERATOR RPM");
    usart_str_1(',');
    
    printf("%s","MOTOR SLIP RPM");
    usart_str_1(',');
    
    printf("%s","ROTOR SLIP RPM");
    usart_str_1(',');
    
    printf("%s","VFD Hz");
    usart_str_1(',');
    
    printf("%s","DC BUS VOLTAGE");
    usart_str_1(',');
    
    printf("%s","DC BUS CURRENT");
    usart_str_1(',');
    
    printf("%s","R VOLT");
    usart_str_1(',');
    
    printf("%s","Y VOLT");
    usart_str_1(',');
    
    printf("%s","B VOLT");
    usart_str_1(',');
    
    printf("%s","R CURRENT");
    usart_str_1(',');
    
    printf("%s","Y CURRENT");
    usart_str_1(',');
    
    printf("%s","B CURRENT");
    usart_str_1(',');
    
    printf("%s","KW");
    usart_str_1(',');
    
    printf("%s","Y-KW");
    usart_str_1(',');
    
    printf("%s","KVA");
    usart_str_1(',');
    
    printf("%s","KVAR");
    usart_str_1(',');
    
    printf("%s","TOAL POWER FACTOR");
    usart_str_1(',');
    
    printf("%s","Y-POWER FACTOR");
    usart_str_1(',');
    
    printf("%s","FREQUENCY");
    usart_str_1(',');
    
    printf("%s","PHASE ANGLE");
    usart_str_1(',');
    
    printf("%s","VFD ERROR");
    usart_str_1(',');
    
    printf("%s","INITAL DELAY");
    usart_str_1(',');
    
    printf("%s","ERROR NO");
    usart_str_1(',');
    
    printf("%s","ERROR IN STRING");
    usart_str_1(',');
    
    printf("%s","TURBINE STATE");
    usart_str_1(',');
    
    printf("%s","DATE");
    usart_str_1(',');
    
    printf("%s","TIME");
    usart_str_1(',');
    
    printf("%s","TEMPERATURE");
    usart_str_1(',');
    
    printf("%s","LAST 5 ERROR");
    usart_str_1(',');
    
    printf("%s","CONTACTOR");
    usart_str_1(',');
    
    printf("%s","RAMP UP LOOP");
    usart_str_1(',');
    
    printf("%s","VFD RUN TIME ERROR COUNTER");
    usart_str_1(',');
        
    printf("%s","ROTOR SLIP COUNTER");
    usart_str_1(',');
    
    printf("%s","MOTOR SLIP COUNTER");
    usart_str_1(',');
    
    printf("%s","VFD TOP CT");
    usart_str_1(',');
    
    printf("%s","VFD BOTTOM CT");
    usart_str_1(',');
    
    printf("%s","LOGIC OTP");
    usart_str_1(',');
    
    printf("%s","VFD OTP");
    usart_str_1(',');
    
    printf("%s","GEN EEPROM FLAG");
    usart_str_1(',');
    
    printf("%s","PITCH EEPROM FLAG");
    usart_str_1(',');
    
    printf("%s","EEPROM ERROR TIME");
    usart_str_1(',');
    
    printf("%s","EEPROM ERROR FLAG");
    usart_str_1(',');
    
    printf("%s","EEPROM LAST THREE ERROR");
    usart_str_1(',');
    
    printf("%s","VFD IO ERROR FLAG");
    usart_str_1(',');
    
    printf("%s","WIND 1 TEMP FLAG");
    usart_str_1(',');
    
    printf("%s","WIND 2 TEMP FLAG");
    usart_str_1(',');
    
    usart_str("\r");
    usart_str("\n");
}
void usart_init()
{
    
    TXSTAbits.SYNC = 0;
	TXSTAbits.BRGH = 1;
	BAUDCONbits.BRG16 = 0;
	TRISCbits.TRISC6 = 1;
	TRISCbits.TRISC7 = 1;
	TXSTAbits.TXEN = 1;
	RCSTAbits.CREN = 0;
	RCSTAbits.SPEN = 1;
    SPBRG1=8;
   
    PIR1bits.RC1IF = 0; 
    PIE1bits.RC1IE = 0;  
      
}

void usart2_init()
{
    
    ANSEL18 = 0; 
    ANSEL19 = 0; 
    TRISGbits.TRISG2 = 1;
	TRISGbits.TRISG1 = 0;
    TXSTA2bits.SYNC = 0;
	TXSTA2bits.BRGH = 1;
	BAUDCON2bits.BRG16 = 0;
	TXSTA2bits.TXEN = 1;
	RCSTA2bits.CREN = 1;
	RCSTA2bits.SPEN = 1;
    SPBRG2=51;
   
    PIR3bits.RC2IF = 0; 
    PIE3bits.RC2IE = 1;    
}
void usart_str(const char*str)
{
    while((*str)!='\0')
    {
        while(!TXIF);
        TXREG=(*str);
        str++;
    }
}
void usart_str_1(const char str)
{
        while(!TXIF);
        TXREG=(str);
}
void putch(char data)
{
 while( ! TX1IF)
 continue;
 TXREG1 = data;
} 

void putch2(char data)
{
 while( ! TX2IF)
 continue;
 TXREG2 = data;
}
void usart_str_2(const char str)
{
        while(!TX2IF);
        TXREG2=(str);
}
void usart2_str(const char*str)
{
    while((*str)!='\0')
    {
        while(!TX2IF);
        TXREG2=(*str);
        str++;
    }
}