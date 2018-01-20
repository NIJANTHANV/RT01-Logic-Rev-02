
#include <xc.h>
#include <stdio.h>
#include "UART.h"
#include "RPM_Measurement.h"
#include "state.h"
#include "ERROR_HANDLING.h"
#include "RAMP_UP.h"
#include "PITCHING.h"
#include "Initialization.h"
extern state_h Turbine_state;



/////////////////////////////////////////////STARTUP STATE FUNCTION/////////////////////////////////////////////////////////
void startup_state_function()
{
    if(Start_up_Error == 0)
    {
        Turbine_state = RAMPUP_STATE;
        VFD_RAMP = VFD_IN;
    }
    if(Turbine_Restore_Error == 1)
    {
        Turbine_state = STOPPING_STATE;
    }
}

////////////////////////////////////////////RAMP UP STATE FUNCTION///////////////////////////////////////////////////////////
void Rampup_state_function()
{
    RAMP_UP();
}
////////////////////////////////////////////RUNNING STATE FUNCTION////////////////////////////////////////////////////////////
void Running_state_function()
{
    
}
///////////////////////////////////////////ERROR STATE FUNCTION///////////////////////////////////////////////////////////////
void Stopping_state_function()
{
    Desired_Frequency = 0;
     Start_up_Error = 2;
    Initial_Delay_Second = 0;
    VFD_RAMP = VFD_IN; 
    RA5 = 1;    //Logic error io to VFD
    if(Turbine_RPM == 0 && Generator_RPM_FLT <= 60)
    {
        Stopping_Counter++;
        if(Stopping_Counter >= 8)
        {
            Stopping_Counter = 0;
            Turbine_state = STARTUP_STATE;
            Turbine_Restore_Error = 0;
            Errors = 0; Errors1 = 0; Errors2 = 0; Errors3 = 0; Errors4 = 0; Errors = 0;
            RA5 = 0;     //Logic error io to VFD
            Error_Flag_Kill();
            VFD_Data_Kill();
        }
        
    }
    Start_Stop();
    Turbine_Pitching();
    GRID_OFF;            //Grid 
    VFD_Error_No  = 0;
    
    
}




  
    
     