#include "simulatordp.h"

void Simulator_DP::Init(word *rDelta, word *rdDelta, word deltamax, word outmax,word * acceleration, word Reg)
{
  Delta = rDelta;
  dDelta = rdDelta;
  Acceleration  = acceleration;
  SimReg.all = Reg;
  DeltaMax = deltamax;
  OutMax = outmax;
  Out = 0;
  SimCounter = 0;
  Accel_Buf = 0;  
}

void Simulator_DP::Run(void)
{
   word ax;
  if (SimReg._.Linear)
  {
     Out += *Delta;
  }
  if (SimReg._.UpDown)
  {
    if (SimCounter == 1)
    {
      Out += *dDelta;
    }
    else if (SimCounter == 2)
    {         
      if (Out > *dDelta )
      {
        Out -= *dDelta;
      }
      else
      {
        Out = Out + OutMax - *dDelta;
      }
      //
    }
    
    if (++SimCounter > 2)  
    {
      SimCounter = 0;
    }
  }
  if (SimReg._.Acceleration)
  {
    ax = *Delta+ Accel_Buf;
    if (ax > DeltaMax)
    {
      ax = DeltaMax;
    }
    else
    {
      Accel_Buf += *Acceleration;
    }
    Out += ax;        
  }
  
  if ( (sw)Out > OutMax )
  {
    Out = Out - OutMax ;
  }
  
}