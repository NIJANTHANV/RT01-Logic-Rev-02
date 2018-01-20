/*
 * File:   EEPROM.c
 * Author: nijanthan.v
 *
 * Created on November 4, 2017, 1:04 PM
 */


#include <xc.h>
#include "EEPROM.h"
#include "ERROR_HANDLING.h"
#include "UART.h"
#include "Initialization.h"

void EEPROM_Error_Monitor (void)
{
    Gen_EP_Err_Flag   = int_eeprom_read(GENERATOR_FB_EP_ADD);
    Pitch_EP_Err_Flag = int_eeprom_read(PITCH_FB_EP_ADD);
    EEPROM_Error_Flag = int_eeprom_read(EEPROM_ERROR_ADD);
    Start_Stop_Flag   = int_eeprom_read(START_STOP_KEY_ADD);
    
    //***********************//    
    if(Start_Stop_Flag != 1)
    {
        Start_Stop_Flag = 0;
        int_eeprom_write(START_STOP_KEY_ADD,0);        
    }
    if(Pitch_EP_Err_Flag == 1)
    {
        Feedback_Error = 1;
        Errors = PITCH_FB;
    }
    else
    {
        int_eeprom_write(PITCH_FB_EP_ADD,0); 
    }
    
    if(Gen_EP_Err_Flag == 1)
    {
        Feedback_Error = 1;
        Errors = GEN_FB;
    }
    else
    {
        int_eeprom_write(GENERATOR_FB_EP_ADD,0);
    }
    
    if(EEPROM_Error_Flag == 1)
    {
        Errors = EP_Errors1;
    }
    else
    {
        int_eeprom_write(EEPROM_ERROR_ADD,0);
    }
    //////////////////////////
    if(RC0 == 0)
    {
        Feedback_Error = 0;  
        
        EEPROM_Error_Flag = 0;
        int_eeprom_write(EEPROM_ERROR_ADD,EEPROM_Error_Flag);
        
        Total_Min = 0; Minutes_1 = 0; Minutes = 0;
        
        Pitch_EP_Err_Flag = 0;
        int_eeprom_write(PITCH_FB_EP_ADD,0);  
        
        Gen_EP_Err_Flag = 0;
        int_eeprom_write(GENERATOR_FB_EP_ADD,0);
        
        
        EP_Errors3 = 0;    EP_Errors2 = 0;       EP_Errors1 = 0;

        int_eeprom_write(ERROR3_ADD,EP_Errors3);        
        int_eeprom_write(ERROR2_ADD,EP_Errors2);       
        int_eeprom_write(ERROR1_ADD,EP_Errors1);

        GiMinutes_3 = 0;    GiMinutes_2 = 0;     GiMinutes_1 = 0;

        int_eeprom_write(MINUTE3_ADD,GiMinutes_3);      
        int_eeprom_write(MINUTE2_ADD,GiMinutes_2);     
        int_eeprom_write(MINUTE1_ADD,GiMinutes_1);

        GiHours_3 = 0;      GiHours_2 = 0;       GiHours_1 = 0;

        int_eeprom_write(HOURS3_ADD,GiHours_3);         
        int_eeprom_write(HOURS2_ADD,GiHours_2);        
        int_eeprom_write(HOURS1_ADD,GiHours_1); 
    }
}
void EEPROM_Error_Stop (void)
{       
    if(One_Time_Flag == 0)      //To Prevent FIFO During Initial Read from EEPROM used 1 Time Flag
    {
        GiMinutes_3 = int_eeprom_read(MINUTE3_ADD);
        GiMinutes_2 = int_eeprom_read(MINUTE2_ADD);
        GiMinutes_1 = int_eeprom_read(MINUTE1_ADD);

        GiHours_3 = int_eeprom_read(HOURS3_ADD);
        GiHours_2 = int_eeprom_read(HOURS2_ADD);
        GiHours_1 = int_eeprom_read(HOURS1_ADD);  

        EP_Errors3 = int_eeprom_read(ERROR3_ADD);
        EP_Errors2 = int_eeprom_read(ERROR2_ADD);
        EP_Errors1 = int_eeprom_read(ERROR1_ADD);
        if(EP_Errors3 > 30 || EP_Errors2 > 30 || EP_Errors1 > 30)
        {
            EP_Errors3 = 0; EP_Errors2 = 0; EP_Errors1 = 0;
            int_eeprom_write(ERROR3_ADD,0);
            int_eeprom_write(ERROR2_ADD,0);
            int_eeprom_write(ERROR1_ADD,0);
        }
    }
    if(One_Time_Flag == 1)
    {
        EP_Errors3 = EP_Errors2;
        EP_Errors2 = EP_Errors1;
        EP_Errors1 = Errors;

        int_eeprom_write(ERROR3_ADD,EP_Errors3);
        int_eeprom_write(ERROR2_ADD,EP_Errors2);
        int_eeprom_write(ERROR1_ADD,EP_Errors1);

        GiMinutes_3 = GiMinutes_2;
        GiMinutes_2 = GiMinutes_1;
        GiMinutes_1 = GiMinutes;

        int_eeprom_write(MINUTE3_ADD,GiMinutes_3);
        int_eeprom_write(MINUTE2_ADD,GiMinutes_2);
        int_eeprom_write(MINUTE1_ADD,GiMinutes_1);

        GiHours_3 = GiHours_2;
        GiHours_2 = GiHours_1;
        GiHours_1 = GiHours;

        int_eeprom_write(HOURS3_ADD,GiHours_3);
        int_eeprom_write(HOURS2_ADD,GiHours_2);
        int_eeprom_write(HOURS1_ADD,GiHours_1);
    }
    //Old Error//
    if(EP_Errors3 != 0)     //Minute Calculation Between Error 2 & 3
    {
        
        Hours_1 = GiHours_2 - GiHours_3;
        if(Hours_1 > 0) 
        {
            Minutes = (60 * Hours_1)  + (GiMinutes_2 - GiMinutes_3);
        }
        else
        {
            Minutes = GiMinutes_2 - GiMinutes_3;
        }
    }    
    //Latest Error//
    if(EP_Errors2 != 0)     //Minute Calculation Between Error 1 & 2
    {
        Hours_2 = GiHours_1 - GiHours_2;
        if(Hours_2 > 0)  
        {
            Minutes_1 = (60 * Hours_2) + (GiMinutes_1 - GiMinutes_2);
        }
        else
        {
            Minutes_1 = GiMinutes_1 - GiMinutes_2;
        }
    }    
    Total_Min = Minutes_1 + Minutes;
    
    if(Minutes_1 != 0 && Minutes != 0)
    {
        Last_3_EEPROM_ERROR_Trigger();
    }
    

    
    One_Time_Flag = 1;
} 
void Last_3_EEPROM_ERROR_Trigger (void)
{
    if(Total_Min > EEPROM_LAST_3_ERROR_TIME_DELAY)
    {
            EP_Errors3 = 0; GiMinutes_3 = 0; GiHours_3 = 0;
            int_eeprom_write(ERROR3_ADD,EP_Errors3);
            int_eeprom_write(MINUTE3_ADD,GiMinutes_3);
            int_eeprom_write(HOURS3_ADD,GiHours_3);
            
            EP_Errors2 = 0; GiMinutes_2 = 0; GiHours_2 = 0;
            int_eeprom_write(ERROR2_ADD,EP_Errors2);
            int_eeprom_write(MINUTE2_ADD,GiMinutes_2);
            int_eeprom_write(HOURS2_ADD,GiHours_2);
            
            Total_Min = 0; Minutes_1 = 0; Minutes = 0;
    }
    else
    {
        EEPROM_Error_Flag = 1;
        Errors = EP_Errors1;
        int_eeprom_write(EEPROM_ERROR_ADD,EEPROM_Error_Flag);        
    }
}
unsigned int int_eeprom_read(unsigned int adr) 
{
    unsigned int temp = 0;
    INTCONbits.GIE = 0;
    EECON1bits.EEPGD = 0;
    EEADR = adr;

    EECON1bits.RD = 1;
    while (EECON1bits.RD);
    temp = EEDATA;

    INTCONbits.GIE = 1;
    return (temp);
}

unsigned int int_eeprom_write(unsigned int adr, unsigned int dat) 
{
    EEADR = adr;
    EEDATA = dat;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    INTCONbits.GIE = 0;
    EECON1bits.WREN = 1;

    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    while (EECON1bits.WR);
    EECON1bits.WREN = 0;
    INTCONbits.GIE = 1;
    EECON1bits.RD = 1;
    while (EECON1bits.RD);
    dat = EEDATA;
    return dat;
}
