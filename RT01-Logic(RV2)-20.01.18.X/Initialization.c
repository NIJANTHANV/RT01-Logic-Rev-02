/*
 * File:   initialization.c
 * Created on April 17, 2017, 3:12 PM
 */


#include <xc.h>
#include "Initialization.h"
#include "OneSecond_Function.h"
#include "RPM_Measurement.h"

void OSCILLATOR (void)
{
    OSCCON = 0b11101110;  //INTERNAL OSCILLATOR 8MHz
}

void Timer1_Initiate(void)
{
    //T1CON = 0b00110001;
    T1CKPS1= 1;
    T1CKPS0 = 1;
    T1CONbits.RD16 = 0;
    TMR1ON = 1;
    TMR1IF = 0;
    TMR1IE = 1;
}
void Timer7_Init(void)
{
   T7CON = 0b00000101;       //16bit timer7 with 8 Prescale

    TMR7IE = 1;             //Enable TIMER3 Interrupt
    TMR7IF = 0;             //Set initial zero the Flag
}
void Turbine_RPM_Initiate (void)    //CCP7
{
    TRISEbits.TRISE5=1;
    CCP7CON = 0x04;      // Capture mode every rising edge
    CCP7IE = 1;          // enable interrupt capture
    CCP7IF = 0;          //clear CCP flag
}
void Generator_RPM_Initiate (void)
{
    TRISEbits.TRISE4=1;
    CCP8CON = 0x06;      // Capture mode every rising edge
    CCP8IE = 1;          // enable interrupt capture
    CCP8IF = 0;          //clear CCP flag
}

void Wind_Speed_Initiate (void) //CCP6
{
    TRISEbits.TRISE6=1;
    CCP6CON = 0x04;      // Capture mode every rising edge
    CCP6IE = 1;          // enable interrupt capture
    CCP6IF = 0;          //clear CCP flag
}
void IO_Initiate (void)
{
    TRISE0 = 0; //RS485 Enable
    RE0 = 0;   
    
    TRISA5 = 0; //LOGIC ERROR
    ANSEL4 = 0;
    RA5 = 0;
    
    Pitch_Solenoid_init();
    VFD_Contactor_IO_init();
    Generator_IO_init();
    VFD_Error_IO();
    Power_Meter_Error_IO();
    
    TRISA4 = 0; //ONE SECOND LED
    RA4 = 0;
    
    TRISE1 = 1; //Turbine Start-stop 
    
    TRISE7 = 0; //Start-stop LED
    RE7 = 0;
    
    TRISC5 = 1; //VFD ERROR IO
    
    TRISB4 = 0; //VFD PS Relay
    RB4 = 0; 
    
    TRISB5 = 0; //Pitch PS Relay
    RB5 = 1; 
    
    TRISF1 = 0; //POWER FACTOR CAPACITOR 
    ANSEL6 = 0;
    RF1 = 0;
    
    TRISC0 = 1;
}


void Pitch_Solenoid_init()       ///FOR pitch status Init code 
{
    TRISB0 = 0;  
    RB0 = 0;
    
    TRISB1 = 1; //Pitch Coil Feedback
}
void VFD_Contactor_IO_init()
{
    TRISD0 = 0;
    TRISD1 = 0;
    RD0 = 0; RD1 = 0;
}
void Generator_IO_init()
{
    TRISD2 = 0;
    RD2 = 0; 
    
    TRISB2 = 1; //Generator 1 Feedback
}
void VFD_Error_IO (void)
{
    TRISE3 = 1;
    TRISF3 = 0;
    ANSEL8 = 0;
    RF3 = 0;
}
void Power_Meter_Error_IO (void)
{
    TRISC2 = 1;
    TRISF4 = 0;
    ANSEL9  = 0;
}