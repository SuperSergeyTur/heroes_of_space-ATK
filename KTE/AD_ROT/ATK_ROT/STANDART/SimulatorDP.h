#ifndef SIMULATORDP_H
#define SIMULATORDP_H
typedef union 
{
  word all;
  struct
  {
    word Linear :1;
    word UpDown :1;
    word Acceleration :1;
  }_;
} sim_reg;

#define _sim_Linear       0x0001
#define _sim_UpDown       0x0002
#define _sim_Acceleration 0x0004

class Simulator_DP
{
private:
  word * Delta;
  word * dDelta;
  word * Acceleration;
  word DeltaMax;
  word OutMax;
  word Out;
  word SimCounter;
  sim_reg SimReg;
  word Accel_Buf;
public:
  
  void Init(word *rDelta, word *rdDelta, word deltamax, word outmax,word * acceleration, word Reg);
  void Run(void);
  word GetRes(void)
  {
    return Out;
  }
  void Set_reg(word Reg)
  {
   SimReg.all =  Reg;
  }
};
#endif