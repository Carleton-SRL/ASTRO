#include "pch.h"
#pragma hdrstop

#include "voydefpf.h"

const char *DefaultRunRoot = "c:\\voyager\\runs";
const char *DefaultHostAddr="192.168.7.104";

///////////////////////////////////////////////////////////////////////////////
//  VoyDefProfile
// Profile object for voyager defaults
///////////////////////////////////////////////////////////////////////////////
VoyDefProfile::VoyDefProfile() : TIniFile("VOYAGER.INI")
{ }

_fastcall VoyDefProfile::~VoyDefProfile(){}
///////////////////////////////////////////////////////////////////////////////
//   GetRunsDir(char *RunRoot)
// Fills RunRoot with the run root directory path, including drive.
///////////////////////////////////////////////////////////////////////////////
void
VoyDefProfile::GetRunsDir
   (
   char *RunRoot
   )
{
   AnsiString RunRootStr = ReadString("Defaults","RunsDir",DefaultRunRoot);
   strcpy(RunRoot,RunRootStr.c_str());
}

AnsiString const
VoyDefProfile::GetRunsDir
   (
   )
{
   AnsiString RunRootStr = ReadString("Defaults","RunsDir",DefaultRunRoot);
   return( RunRootStr );
}

bool const
VoyDefProfile::IsGroundTrackEnabled() 
{

   return(ReadInteger("Defaults","GroundTrackEnabled",1));

}


bool const
VoyDefProfile::IsPlotEnabled()
{

   return(ReadInteger("Defaults","PlotEnabled",1));

}


bool
VoyDefProfile::GetDoCodeCalibration()
{
   return(ReadInteger("Defaults","DoCodeCalibration",1));
}

bool
VoyDefProfile::GetDoRTCalibration()
{
   return(ReadInteger("Defaults","DoRTCalibration",1));
}
bool const
VoyDefProfile::IsRemote()
{
   return(ReadInteger("Defaults","IsRT",1));
}

bool const
VoyDefProfile::IsMcAnal05
   (
   )
{

   return(ReadInteger("Defaults","IsMcAnal05",1));

}
bool
VoyDefProfile::GetDoCarrierCalibration()
{
   return(ReadInteger("Defaults","DoCarrierCalibration",1));
}
int const VoyDefProfile::GetScramnetOffset()
{
   return( ReadInteger("Defaults","ScramnetOffset",0) );
}

bool
VoyDefProfile::GetShowCal()
{
   return(ReadInteger("Defaults","ShowCal",1));
}
int
VoyDefProfile::GetTruthTimeDelay()
{
   return(ReadInteger("Defaults","TruthTimeDelay",0));
}
int
VoyDefProfile::GetDisplayUpdateInterval()
{
   return(ReadInteger("Defaults","DisplayUpdateInterval",1000));
}

bool const
VoyDefProfile::IsPcsgIntEnabled
   (
   ) 
{
   bool IntEnabled = false;
   if ( ReadInteger("Defaults","PcsgIntEnabled",0) )
   {
      IntEnabled = true;
   }
   return(IntEnabled);
}


int
VoyDefProfile::GetInterChassisBias
   (
   int ChassisNum
   )
{
   int Value;
   if ( ChassisNum )
   {
      Value = ReadInteger("Defaults","InterChassisBias1",0);
   } else
   {
      Value = ReadInteger("Defaults","InterChassisBias2",0);
   }
   return (Value);
}
///////////////////////////////////////////////////////////////////////////////
//   GetDriverType()
// Returns the type of driver (8 ot 16 bit)
///////////////////////////////////////////////////////////////////////////////
VoyDefProfile::OrbDriverType VoyDefProfile::GetDriverType()
{
   int Value = ReadInteger("Defaults","OrbDriverType",16);
   if ( Value == Orb8 )      return(Orb8);
   else if ( Value == GsIsa )return(GsIsa);
   else if ( Value == GsPci )return(GsPci);
   else return(Orb16);
}

///////////////////////////////////////////////////////////////////////////////
//   GetHostAddr(char *Addr)
///////////////////////////////////////////////////////////////////////////////
void
VoyDefProfile::GetHostAddr
   (
   char *HostAddr
   )
{
   AnsiString HostAddrStr = ReadString("Defaults","HostAddr",DefaultHostAddr);
   strcpy(HostAddr,HostAddrStr.c_str());
}
bool const
VoyDefProfile::IsTestMode
   (
   ) 
{
   return ( ReadInteger("Defaults","TestMode",0));
}
bool const
VoyDefProfile::IsDebugDisp
   (

   )
{
   return( ReadInteger( "LLTest", "DebugDisp", 0 ) );
}

int const
VoyDefProfile::GetLLTestNumChans
   (
   )
{
   return( ReadInteger( "LLTest","NumChans",1 ) );
}

