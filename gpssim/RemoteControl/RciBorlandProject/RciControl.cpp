#include "pch.h"
#pragma hdrstop

#include "RciControl.h"
#include "RciDriverMsgs.h"
#pragma package(smart_init)

static const int RciControlUpdateRate = 10;

__fastcall
TRciControl::TRciControl
   (
   ) :
   TThread( true ),
   Valid( false ),
   Interface( NULL ),
   AckEvery( false ),
   SimMode( eSimIdle ),
   CurTimeMillisec( 0 )
{


   ExecutePeriod = NINT( ( 1.0/RciControlUpdateRate ) * 1000 );

   UpdateDeltaTime = 1.0/RciControlUpdateRate;

   CodeSite->SendInteger( "ExecutePeriod ", ExecutePeriod );

   Valid = !InitializeInterface();
   if ( !Valid )
   {
      CodeSite->SendMsg( csmError, "TRciControl::TRciControl InitializeInterface Error" );
      Application->MessageBox( " TRciControl::InitializeInterface failed.", "Fatal Error", MB_OK );
      Application->Terminate();
      Application->ProcessMessages();
   }


   Schedule = new TSchedule( ExecutePeriod, 0, "RCICONTROL" );

   ScheduleSignal = new TScheduleSignal();
   ScheduleSignal->Resume();

}

__fastcall
TRciControl::~TRciControl()
{

   delete Interface;
   delete Schedule;
   delete ScheduleSignal;

}
//---------------------------------------------------------------------------
void __fastcall TRciControl::Execute()
{
//   SetPriorityClass(GetCurrentProcess(),REALTIME_PRIORITY_CLASS);
//   SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_ABOVE_NORMAL);

   while ( !Terminated )
   {

      TWaitResult WaitResult = Schedule->WaitFor();
      if ( WaitResult != wrSignaled )
      {
         break;
      }
      if ( Terminated ) break;

      CurTimeMillisec = TScheduleSignal::GetCurTimeMillisec();

//      CodeSite->SendInteger( "TRciControl::Execute at ", CurTimeMillisec );

      GetControlData();

      TOutMsgQueue OutMsgs;
      TInMsgArray  InMsgArray;

      Interface->GetInputMsgs( InMsgArray );

      ProcessInputMsgs( InMsgArray, OutMsgs );

      Interface->QueueMsgs( OutMsgs );

   }

   if ( Interface )
   {
      Interface->Terminate();
      Interface->WaitFor();
   }
}

void
TRciControl::ProcessInputMsgs
   (
   TInMsgArray &InMsgArray,
   TOutMsgQueue &OutMsgs
   )
{

   for ( unsigned int i=0; i<InMsgArray.size(); ++i )
   {
      ProcessInputMsg( InMsgArray[i], OutMsgs );
   }

}

void
TRciControl::ProcessInputMsg
   (
   const TInMsg  &InMsg,
   TOutMsgQueue  &OutMsgs
   )
{

   AnsiString MsgId =( InMsg.GetMsgId() ).UpperCase();

   CodeSite->SendMsg( AnsiString( "Received external message: " ) + MsgId );
   if ( MsgId == SimModeMsgId )
   {
      ProcessSimModeMsg( InMsg );
   }
   else if ( MsgId == ChanStatMsgId )
   {
      ProcessChanStatMsg( InMsg );
   }
   else if ( MsgId == BitResultsMsgId )
   {
      ProcessStartLocalMsg( InMsg );
   }
   else if ( MsgId == AckMsgId )
   {
      ProcessSetSvidMsg( InMsg );
   }
   else if ( MsgId == SetPowerMsgId )
   {
      ProcessSetPowerMsg( InMsg, OutMsgs );
   }
   else if ( MsgId == StopMsgId )
   {
      ProcessStopMsg( InMsg, OutMsgs );
   }
   else if ( MsgId == ShutdownMsgId )
   {
      ProcessShutdownMsg( InMsg, OutMsgs );
   }
   else if ( MsgId == QueryMsgId )
   {
      ProcessQueryMsg( InMsg, OutMsgs );
   }
   else
   {
      ProcessUnknownMsg( InMsg, OutMsgs );
   }

}

void
TRciControl::ProcessUnknownMsg
   (
   const TInMsg &InMsg,
   TOutMsgQueue &OutMsgs
   )
{
   OutMsgs.push( TAckMsg( InMsg.GetMsgId(), false, true ) );
}   

void
TRciControl::ProcessInitGeoMsg
   (
   const TInMsg &InMsg,
   TOutMsgQueue &OutMsgs
   )
{

   TInitGeoMsg InitGeoMsg = InMsg;

   bool ShouldSendAck = !InitGeoMsg.IsValid() || AckEvery;

   if ( InitGeoMsg.IsValid() )
   {
      TapMsecProfile->SetPos( InitGeoMsg.GetLat(), InitGeoMsg.GetLon(), InitGeoMsg.GetAlt() );
      TapMsecProfile->SetDate( InitGeoMsg.GetDate() );
      TapMsecProfile->SetTime( InitGeoMsg.GetTime() );
   }

   AnsiString CsStr;
   if ( InitGeoMsg.IsValid() )
   {
      CsStr.sprintf("InitGeo: Lat = %lf Lon = %lf, Alt = %d ", InitGeoMsg.GetLat(), InitGeoMsg.GetLon(), InitGeoMsg.GetAlt() );
      CsStr += AnsiString( " D = " ) + InitGeoMsg.GetDate() + AnsiString( "T = " ) + InitGeoMsg.GetTime();
      CodeSite->SendMsg( CsStr );
   }
   else
   {
      CodeSite->SendMsg( "InitGeo: Invalid Message ");
   }

   if ( ShouldSendAck )
   {
      OutMsgs.push( TAckMsg( InitGeoMsgId, InitGeoMsg.IsValid(), true ) );
   }

}
//---------------------------------------------------------------------------
bool const
TRciControl::InitializeInterface()
{

   bool iError                   = false;

   int BoardIndex                = TapRciProfile->GetGpibBoardIndex();
   int PrimaryAddress            = TapRciProfile->GetGpibPrimaryAddress();

   TGpibOptions GpibOptions;
   GpibOptions.BoardIndex  = BoardIndex;
   GpibOptions.PrimaryAddr = PrimaryAddress;

   Interface = new TGpib( GpibOptions );
   if ( Interface->IsValidInterface() )
   {
      Interface->Resume();
   }
   else
   {
      iError = true;
   }

   return( iError );

}

TTapMsecStat const
TRciControl::GetCurrentTapMsecStat
   (
   )
{
   return( TapMsecStatMem->GetCurrent() );
}

void
TRciControl::ProcessStartScenMsg
   (
   const TInMsg &InMsg,
   TOutMsgQueue &OutMsgs
   )
{

   TStartScenMsg StartScenMsg = InMsg;

   bool MsgValid = StartScenMsg.IsValid();
   bool SimModeValid = ( SimMode == eSimIdle );

   if ( SimMode == eSimIdle )
   {
      AnsiString ScenName        = StartScenMsg.GetScenName();

      AnsiString ScenarioPath    = AnsiString( "\\" ) + ScenName;

      if ( IsValidScenario( ScenarioPath ) )
      {

         AnsiString Parameters  = ScenarioPath + AnsiString( " 1 0 " );
         RunStartScen( ScenarioPath, Parameters );
         SimMode = eSimScen;

      }
      else
      {
         MsgValid = false;
      }
   }

   bool ShouldSendAck = !MsgValid || AckEvery || !SimModeValid;
   if ( ShouldSendAck )
   {
      OutMsgs.push( TAckMsg( StartScenMsgId, MsgValid, SimModeValid ) );
   }

}

void
TRciControl::ProcessStartLocalMsg
   (
   const TInMsg &InMsg,
   TOutMsgQueue &OutMsgs
   )
{


   bool MsgValid     = true;
   bool SimModeValid = ( SimMode == eSimIdle );

   if ( SimMode == eSimIdle )
   {

      AnsiString ScenarioPath  = TapRciProfile->GetRemoteScn();

      if ( IsValidScenario( ScenarioPath ) )
      {

         AnsiString Parameters  = ScenarioPath + AnsiString( " 1 0 " );
         RunStartScen( ScenarioPath, Parameters );
         SimMode = eSimLocal;

      }
      else
      {
         MsgValid = false;
      }
   }

   bool ShouldSendAck = !MsgValid || AckEvery || !SimModeValid;
   if ( ShouldSendAck )
   {
      OutMsgs.push( TAckMsg( StartScenMsgId, MsgValid, SimModeValid ) );
   }

}


void TRciControl::RunStartScen
   (
   const AnsiString & ScenarioPath,
   const AnsiString & Parameters
   )
{
   AnsiString TapMsecPath = TapRciProfile->GetTapMsecPath();

   AnsiString ExecStr = TapMsecPath;
   ExecStr += AnsiString( " " ) + Parameters;

   CodeSite->SendMsg( AnsiString( "StartScen: " ) + ExecStr );
   char cmd[1000];
   strcpy(cmd,ExecStr.c_str());
   STARTUPINFO Start;
   GetStartupInfo(&Start);

   CreateProcess
      (
      NULL,
      cmd,
      NULL,               // Sec
      NULL,               // Thread
      FALSE,              // Inherit
      CREATE_NEW_CONSOLE, // Creating flags
      NULL,               // Environment
      NULL,               // Current directory
      &Start,             // Startup info
      &TapMsecProcInfo           // Process info
      );

}

void
TRciControl::ProcessSetSvidMsg
   (
   const TInMsg &InMsg,
   TOutMsgQueue &OutMsgs
   )
{

   TSetSvidMsg SetSvidMsg = InMsg;

   bool MsgValid     = SetSvidMsg.IsValid();
   bool SimModeValid = ( SimMode == eSimLocal );

   if ( SimMode == eSimLocal )
   {

      TTapMsecCommand  TapMsecCommand;
      TapMsecCommand.Command       = TTapMsecCommand::eCommandSvid;

      TChanSvidArray ChanSvidArray = SetSvidMsg.GetChanSvidArray();

      int NumChans = min( (int) ChanSvidArray.size(), NUM_CHANS_IN_COMMAND );
      for ( int i=0; i<NumChans; ++i )
      {
         TapMsecCommand.CommandSvid[i] = TTapMsecCommandSvid( ChanSvidArray[i].GetChan(), ChanSvidArray[i].GetSvid() );
      }

      TapMsecCommandQueue.push_back( TapMsecCommand );

   }

   bool ShouldSendAck = !MsgValid || AckEvery || !SimModeValid;
   if ( ShouldSendAck )
   {
      OutMsgs.push( TAckMsg( StartScenMsgId, MsgValid, SimModeValid ) );
   }

}

void
TRciControl::ProcessSetPowerMsg
   (
   const TInMsg &InMsg,
   TOutMsgQueue &OutMsgs
   )
{

   TSetPowerMsg SetPowerMsg = InMsg;

   bool MsgValid     = SetPowerMsg.IsValid();
   bool SimModeValid = ( SimMode == eSimLocal );

   if ( SimMode == eSimLocal )
   {

      TTapMsecCommand  TapMsecCommand;
      TapMsecCommand.Command         = TTapMsecCommand::eCommandPower;

      TChanPowerArray ChanPowerArray = SetPowerMsg.GetChanPowerArray();

      int NumChans = min( (int) ChanPowerArray.size(), NUM_CHANS_IN_COMMAND );
      for ( int i=0; i<NumChans; ++i )
      {
         TapMsecCommand.CommandPower[i] = TTapMsecCommandPower( ChanPowerArray[i].GetChan(), ChanPowerArray[i].GetPower() );
      }

      TapMsecCommandQueue.push_back( TapMsecCommand );

   }

   bool ShouldSendAck = !MsgValid || AckEvery || !SimModeValid;
   if ( ShouldSendAck )
   {
      OutMsgs.push( TAckMsg( StartScenMsgId, MsgValid, SimModeValid ) );
   }

}

void
TRciControl::ProcessStopMsg
   (
   const TInMsg &InMsg,
   TOutMsgQueue &OutMsgs
   )
{

   bool MsgValid     = true;
   bool SimModeValid = true;

   if ( SimMode != eSimLocal )
   {

      TTapMsecCommand  TapMsecCommand;
      TapMsecCommand.Command         = TTapMsecCommand::eCommandStop;

      TapMsecCommandQueue.push_back( TapMsecCommand );

   }

   bool ShouldSendAck = !MsgValid || AckEvery || !SimModeValid;
   if ( ShouldSendAck )
   {
      OutMsgs.push( TAckMsg( StartScenMsgId, MsgValid, SimModeValid ) );
   }

}

void
TRciControl::ProcessShutdownMsg
   (
   const TInMsg &InMsg,
   TOutMsgQueue &OutMsgs
   )
{
   HANDLE hToken;
   TOKEN_PRIVILEGES tkp;

   // Get a token for this process.
   //
   if (!OpenProcessToken( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) )
   {
      ReportErrorAndTerminate( "OpenProcessToken" );
   }

   // Get the LUID for the shutdown privilege.
   //
   LookupPrivilegeValue( NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid );

   tkp.PrivilegeCount = 1;  // one privilege to set
   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

   // Get the shutdown privilege for this process.
   //
   AdjustTokenPrivileges( hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0 );

   // Cannot test the return value of AdjustTokenPrivileges.
   //
   if ( GetLastError() != ERROR_SUCCESS )
   {
      ReportErrorAndTerminate( "AdjustTokenPrivileges" );
   }

   // Shut down the system and force all applications to close.
   //
   if ( !ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0 ) )
   {
      ReportErrorAndTerminate( "ExitWindowsEx" );
   }
}

void
TRciControl::ProcessQueryMsg
   (
   const TInMsg &InMsg,
   TOutMsgQueue &OutMsgs
   )
{

   TQueryMsg QueryMsg = InMsg;
   bool MsgValid      = QueryMsg.IsValid();
   bool SimModeValid  = true;

   TExtQuery ExtQuery = QueryMsg.GetExtQuery();


   if ( ExtQuery.QueryType == eQUERY_SIM_MODE )
   {
      SimModeQuery.ProcessExtQuery( ExtQuery );
   }
   else if ( ExtQuery.QueryType == eQUERY_CHAN_STAT )
   {
      ChanStatQuery.ProcessExtQuery( ExtQuery );
   }
   else if ( ExtQuery.QueryType == eQUERY_BIT_RESULTS )
   {
      ChanStatQuery.ProcessExtQuery( ExtQuery );
   }
   else
   {
      MsgValid = false;
   }


   bool ShouldSendAck = !MsgValid || AckEvery || !SimModeValid;
   if ( ShouldSendAck )
   {
      OutMsgs.push( TAckMsg( StartScenMsgId, MsgValid, SimModeValid ) );
   }

}

void
TRciControl::PerformBit()
{

   TTpMapInterface *TpMapInterface    = new TTpMapInterface();
   TapBitResults                      = TpMapInterface->RunBit();
   delete TpMapInterface;
}

void
TRciControl::SendBitResults
   (
   TOutMsgQueue &OutMsgs
   )
{

   OutMsgs.push( TBitResultsMsg( TapBitResults ) );

}


void
TRciControl::ReportErrorAndTerminate
   (
   const AnsiString & ErrorStr
   )
{
   CodeSite->SendMsg( ErrorStr );
   Application->MessageBox( ErrorStr.c_str(), "Fatal Error", MB_OK );
   Application->Terminate();
}

void
TRciControl::ClearTapMsecProcInfo()
{
   TapMsecProcInfo.hProcess    = 0;
   TapMsecProcInfo.hThread     = 0;
   TapMsecProcInfo.dwProcessId = 0;
   TapMsecProcInfo.dwThreadId  = 0;
}

TMsgTrafficArray const
TRciControl::GetMsgTrafficArray()
{
   return( Interface->GetMsgTrafficArray() );
}

void
TRciControl::GetSysCfg()
{

   TPowerCalIni *PowerCalIni = new TPowerCalIni();

   SysCfg.NumChans  = 12;
   SysCfg.L2Capable = false;
   SysCfg.MinPower  = NINT( PowerCalIni->GetL1MaxPower() - PowerCalIni->GetExtAtten() - TP_MAX_ATTEN_DB );
   SysCfg.MaxPower  = NINT( PowerCalIni->GetL1MaxPower() - PowerCalIni->GetExtAtten() );

   delete PowerCalIni;

}

