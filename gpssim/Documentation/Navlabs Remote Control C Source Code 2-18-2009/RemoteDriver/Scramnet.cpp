#include "pch.h"
#include "TapMsecPchHeaders.h"
#pragma hdrstop
//---------------------------------------------------------------------------
//
// $Workfile:: Scramnet.cpp                                          $
//
// $Revision:: 3                                                     $
//
// $History:: Scramnet.cpp                                           $
//
//*****************  Version 3  *****************
//User: Michael Wade Date: 11/14/03   Time: 11:49a
//Updated in $/TapMsec
//Use shared memory.
//
//*****************  Version 2  *****************
//User: Michael Wade Date: 1/20/03    Time: 6:33p
//Updated in $/TapMsec
//Initial release.
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 12/11/02   Time: 11:22p
//Created in $/TapMsec
//
//
//---------------------------------------------------------------------------

#ifndef ScramnetH
#include "Scramnet.h"
#endif

#ifndef ScenIniFileH
#include "ScenIniFile.h"
#endif

#ifndef TapMsecPfH
#include "TapMsecPf.h"
#endif

#ifndef ThreadInfH
#include "ThreadInf.h"
#endif

#ifndef ScenTimeH
#include "ScenTime.h"
#endif

#ifndef RfParamsH
#include "RfParams.h"
#endif

//---------------------------------------------------------------------------

#pragma package(smart_init)


TScramnet::TScramnet
   (
   TRtControl              * InRtControl
   ) :
   TRtMotionMem( InRtControl ),
   ScramnetDll_( NULL ),
   Report_( NULL ),
   BaseAddr_( NULL )
{

   Report_                 = new TReportError( "Scramnet" );
}

unsigned char *
TScramnet::GetBaseMemAddr
   (
   )
{   

   ScramnetDll_            = new TScramnetDll();
   ScramnetDll_->sp_scram_init();

   BaseAddr_               = (unsigned char *) ScramnetDll_->get_base_mem();

   return( BaseAddr_ );

}

__fastcall
TScramnet::~TScramnet
   (
   )
{

   delete ScramnetDll_;
   ScramnetDll_            = NULL;

   delete Report_;
   Report_                 = NULL;

}

#if(0)

TScramnet::TScramnet
   (
   TRtControl              * InRtControl
   ) :
   BaseAddr_( NULL ),
   StopRcvd_( false ),
   StopProcessed_( false ),
   Rt_( false ),
   RangeTruthFile_( NULL ),
   SimMode_( eSimModeIdle ),
   ExtToSimOffset_( 0 ),
   SimToExtOffset_( 0 ),
   ClearDataAtStart_( false ),
   Report_( NULL ),
   VehicleTruth( NULL ),
   ReportedInvalidTruthRec( false ),
   Valid_( true ),
   LastTimeVehicleStateMemWhich( 0 ),
   TruthQCritSec( NULL ),
   NumChannels_( 0 ),
   RtControl( InRtControl ),
   InitValid_( false ),
   WaitableTimer( 10 ),
   ScramnetDll_( NULL )
{

   Report_                 = new TReportError( "Scramnet" );


   ScramnetDll_            = new TScramnetDll();
   ScramnetDll_->sp_scram_init();

   BaseAddr_               = (unsigned char *) ScramnetDll_->get_base_mem();

   TTapMsecProfile * Prof  = new TTapMsecProfile();
   ExtToSimOffset_         = Prof->RtMotionMemExtToSimOffset;
   SimToExtOffset_         = Prof->RtMotionMemSimToExtOffset;
   ClearDataAtStart_       = Prof->RtMotionMemClearDataAtStart;
   delete Prof;

   TScenIniFile * ScenIni  = new TScenIniFile();
   Rt_                     = ScenIni->Rt;
   delete ScenIni;

   InitializeMem();
   if ( !Rt_ )
   {
      RangeTruthFile_      = new TRangeTruthFile( 0 );   // Only 1 RF supported for SCRAMNet
   }

   VehicleTruth            = new TVehicleTruthRt();

   TruthQCritSec           = new TCriticalSection();

   Valid_ = true;

}

__fastcall
TScramnet::~TScramnet
   (
   )
{
   delete ScramnetDll_;
   delete Report_;
   delete RangeTruthFile_;
}

void __fastcall
TScramnet::Execute
   (
   )
{

   TThreadInf TThreadInf( "Scramnet" );
   Priority = PriorityRtMsg;

   try
   {

      while( !Terminated )
      {

         Sleep( 10 );
//         Wait...

         ProcessInputData();

         FillOutput();

      }

   }
   catch ( const ETapMsecException & Exc )
   {

      Report_->ReportErrorStr(  AnsiString( "Scramnet::Execute TapMsecException caught. Exception message = " ) + Exc.ExcStr );
      throw( ETapMsecException( AnsiString( "Scramnet::Execute TapMsecException caught. Exception message = " ) + Exc.ExcStr ) );

   }
   catch ( const Exception & Exc )
   {

      Report_->ReportErrorStr(  AnsiString( "Scramnet::Execute Exception caught. Exception message = " ) + Exc.Message );
      throw( ETapMsecException( AnsiString( "Scramnet::Execute Exception caught. Exception message = " ) + Exc.Message ) );

   }

}

void
TScramnet::ProcessInputData
   (
   )
{

   if ( ExtToSim->Stop.Stop )
   {
      StopRcvd_     = true;
   }

   if ( SimModeIdle )
   {
      if ( ExtToSim->Initialization.Valid )
      {
         ProcessInitialize();
      }
   }

   if ( SimModeArmed )
   {

      if ( TScenTime::GetTimeMillisec() > 0 )
      {
         SimMode_ = eSimModeRunning;
      }

   }

   ProcessVehicleState();

   if ( SimModeRunning )
   {
      TGpsTime CurTime              = InitTime_ + ( 0.001 )*TScenTime::GetTimeMillisec();
      TTimeSvRec TimeSvRec          = Rt_ ? TRtControl::RtControlPtr()->TimeSvRec : RangeTruthFile_->GetTimeSvRec( CurTime );
   }

}

void
TScramnet::ProcessVehicleState
   (
   )
{

   if ( ExtToSim->TimeVehicleStateMem.Which != LastTimeVehicleStateMemWhich )
   {

      LastTimeVehicleStateMemWhich         = ExtToSim->TimeVehicleStateMem.Which;
      TclTimeVehicleState TimeVehicleState = LastTimeVehicleStateMemWhich  == 1 ? ExtToSim->TimeVehicleStateMem.State1 : ExtToSim->TimeVehicleStateMem.State2;

      TVehTruthRec TruthRec                = ClTimeVehicleStateToVehTruthRec( TimeVehicleState );

      if ( TruthRec.GpsTime.Week == 0 && TruthRec.GpsTime.Seconds < 0.5 )
      {
         TruthRec.GpsTime                  = InitTruth_.GpsTime + ( 0.001 )*( TScenTime::GetTimeMillisec() );
      }

      AddTruthRec( TruthRec );

   }

}

void
TScramnet::ProcessSvOverride
   (
   )
{

   if ( ExtToSim->SvOverride.NewData )
   {

      TclSvOverride SvOverride      = ExtToSim->SvOverride;
      ExtToSim->SvOverride.NewData  = false;

      for ( int i=0; i<NumChannels_; ++i )
      {
         if ( SvOverride.SvOverride[i] < 33 )
         {
            RtControl->RtAssignedSv[i] = SvOverride.SvOverride[i];
         }
      }

   }

}

void
TScramnet::ProcessInitialize
   (
   )
{

   TclInitialization LocalInit = ExtToSim->Initialization;

   if ( LocalInit.Valid )
   {

      InitTruth_               = ClTimeVehicleStateToVehTruthRec( LocalInit.InitialVehicleState );

      AddTruthRec( InitTruth_ );

      SimMode_                 = eSimModeArmed;

      InitValid_               = true;

   }

}

void
TScramnet::FillOutput
   (
   )
{

   FillCurTime();

   FillVehicleState();

}

void
TScramnet::FillVehicleState
   (
   )
{

   TruthQCritSec->Enter();

   TclTimeVehicleState TimeVehicleState = VehTruthRecToClTimeVehicleState( PrevTruthRec );

   TruthQCritSec->Leave();

   if ( SimToExt->TimeVehicleStateMem.Which == 1 )
   {
      SimToExt->TimeVehicleStateMem.State2 = TimeVehicleState;
      SimToExt->TimeVehicleStateMem.Which  = 2;
   }
   else
   {
      SimToExt->TimeVehicleStateMem.State1 = TimeVehicleState;
      SimToExt->TimeVehicleStateMem.Which  = 1;
   }

}

void
TScramnet::FillCurTime
   (
   )
{
   TclCurTime CurTime;

   CurTime.TimeMillisec          = TScenTime::GetTimeMillisec();
   CurTime.GpsTime               = InitTime_ + ( 0.001 )*TScenTime::GetTimeMillisec();

   if ( SimToExt->CurTime.Which == 2 )
   {
      SimToExt->CurTime.Time1 = CurTime;
      SimToExt->CurTime.Which = 1;
   }
   else
   {
      SimToExt->CurTime.Time2 = CurTime;
      SimToExt->CurTime.Which = 2;
   }

}

TVehTruthRec const
TScramnet::ClTimeVehicleStateToVehTruthRec
   (
   const TclTimeVehicleState & clVehRec
   ) const
{

   TVehTruthRec Truth;

   Truth.GpsTime.Week    = clVehRec.GpsTime.Week;
   Truth.GpsTime.Seconds = clVehRec.GpsTime.Seconds;

   for ( int i=0; i<3; ++i )
   {

      Truth.PosEcef[i]   = clVehRec.VehicleState.PosEcef[i];
      Truth.VelEcef[i]   = clVehRec.VehicleState.VelEcef[i];
      Truth.AccEcef[i]   = clVehRec.VehicleState.AccEcef[i];
      Truth.JerkEcef[i]  = clVehRec.VehicleState.JrkEcef[i];
      Truth.Attitude[i]  = clVehRec.VehicleState.Att[i];
      Truth.AngRate[i]   = clVehRec.VehicleState.AngRate[i];

   }

   return( Truth );

}

TclTimeVehicleState const
TScramnet::VehTruthRecToClTimeVehicleState
   (
   const TVehTruthRec      & Truth
   ) const
{

   TclTimeVehicleState clVehRec;

   clVehRec.GpsTime.Week     = Truth.GpsTime.Week;
   clVehRec.GpsTime.Seconds  = Truth.GpsTime.Seconds;

   for ( int i=0; i<3; ++i )
   {

      clVehRec.VehicleState.PosEcef[i]   = Truth.PosEcef[i];
      clVehRec.VehicleState.VelEcef[i]   = Truth.VelEcef[i];
      clVehRec.VehicleState.AccEcef[i]   = Truth.AccEcef[i];
      clVehRec.VehicleState.JrkEcef[i]   = Truth.JerkEcef[i];
      clVehRec.VehicleState.Att[i]       = Truth.Attitude[i];
      clVehRec.VehicleState.AngRate[i]   = Truth.AngRate[i];

   }

   return( clVehRec );

}

TGpsTime const
TScramnet::GetInitTime
   (
   ) const
{
   return( InitTruth_.GpsTime );
}

void
TScramnet::AddTruthRec
   (
   const TVehTruthRec & NewRec
   )
{

   // Guard Data
   //
   TruthQCritSec->Enter();

   TruthQ.push( NewRec );

   // Release Data
   //
   TruthQCritSec->Leave();

}


bool const
TScramnet::GetTruth
   (
   const TGpsTime          & Time,
   TVehTruthRec            & Rec
   )
{
   if ( !InitValid && !TruthQ.size() )
   {
      AnsiString Str;
      Str.sprintf( "TScramnet::GetTruth Invalid.  IsInitValid = %d TruthQ.size() = %d", InitValid, TruthQ.size() );
      CodeSite->SendMsg( csmError, Str );
      return( false );
   }

   if ( Stopped )
   {
      Rec         = TVehTruthRec();
      Rec.GpsTime = Time;
      return( false );
   }

   bool ValidRec = false;

   // Guard Data
   //
   TruthQCritSec->Enter();

   if ( TruthQ.size() )
   {

      PrevTruthRec = TruthQ.front();
      NextTruthRec = PrevTruthRec;

      ValidRec     = true;

      while ( TruthQ.size() && ( NextTruthRec.GpsTime < Time ) )
      {

         PrevTruthRec = NextTruthRec;

         NextTruthRec = TruthQ.front();

         if ( NextTruthRec.GpsTime < Time )
         {

            TruthQ.pop();

         }

      }

   }

//   const int TruthQSize = TruthQ.size();

   // Release Data
   //
   TruthQCritSec->Leave();

//   CodeSite->WriteInteger( "TruthQSize", TruthQSize );
   if ( ValidRec )
   {
      PropagateTruth( Time, PrevTruthRec, NextTruthRec , Rec );
      VehicleTruthRt::AddTruth( Rec );
   }
   else
   {
      if ( !ReportedInvalidTruthRec )
      {
         CodeSite->SendMsg( csmError, AnsiString( "TRtMsg::GetTruth Invalid truth rec " ) + AnsiString( TScenTime::GetTimeMillisec() ) );
         ReportedInvalidTruthRec = true;
      }
      VehicleTruth->GetTruth( Time, &Rec );
   }


   return( true );

}

void
TScramnet::PropagateTruth
   (
   const TGpsTime          & Time,
   const TVehTruthRec      & PrevRec,
   const TVehTruthRec      & NextRec,
   TVehTruthRec            & Rec
   )
{

   Rec.GpsTime = Time;
   if ( Time < PrevRec.GpsTime )
   {

      const double dT = Time - PrevRec.GpsTime;

      for ( int i=0; i<3; ++i )
      {

         Rec.PosEcef[i]  = PrevRec.PosEcef[i]
            + PrevRec.VelEcef[i]*dT
            + PrevRec.AccEcef[i]*dT*dT*0.5
            + PrevRec.JerkEcef[i]*dT*dT*dT/6.0;

         Rec.VelEcef[i]  = PrevRec.VelEcef[i]
            + PrevRec.AccEcef[i]*dT
            + PrevRec.JerkEcef[i]*dT*dT*0.5;

         Rec.AccEcef[i]  = PrevRec.AccEcef[i] + PrevRec.JerkEcef[i]*dT;

         Rec.JerkEcef[i] = PrevRec.JerkEcef[i];

      }

   }
   else if ( Time > NextRec.GpsTime )
   {

      const double dT = Time - NextRec.GpsTime;

      for ( int i=0; i<3; ++i )
      {

         Rec.PosEcef[i]  = NextRec.PosEcef[i]
            + NextRec.VelEcef[i]*dT
            + NextRec.AccEcef[i]*dT*dT*0.5
            + NextRec.JerkEcef[i]*dT*dT*dT/6.0;

         Rec.VelEcef[i]  = NextRec.VelEcef[i]
            + NextRec.AccEcef[i]*dT
            + NextRec.JerkEcef[i]*dT*dT*0.5;

         Rec.AccEcef[i]  = NextRec.AccEcef[i] + NextRec.JerkEcef[i]*dT;

         Rec.JerkEcef[i] = NextRec.JerkEcef[i];

      }
   }
   else
   {

      const double RecDeltaT = NextRec.GpsTime - PrevRec.GpsTime;

      if ( fabs( RecDeltaT ) > 0.01 )
      {

         const double InterpolationFactor = (Time - PrevRec.GpsTime)/( RecDeltaT );

         for ( int i=0; i<3; i++ )
         {

            Rec.PosEcef[i]  = PrevRec.PosEcef[i]   + ( NextRec.PosEcef[i]  - PrevRec.PosEcef[i]  )*InterpolationFactor;
            Rec.VelEcef[i]  = PrevRec.VelEcef[i]   + ( NextRec.VelEcef[i]  - PrevRec.VelEcef[i]  )*InterpolationFactor;
            Rec.AccEcef[i]  = PrevRec.AccEcef[i]   + ( NextRec.AccEcef[i]  - PrevRec.AccEcef[i]  )*InterpolationFactor;
            Rec.JerkEcef[i] = PrevRec.JerkEcef[i]  + ( NextRec.JerkEcef[i] - PrevRec.JerkEcef[i] )*InterpolationFactor;
            Rec.Attitude[i] = PrevRec.Attitude[i]  + ( NextRec.Attitude[i] - PrevRec.Attitude[i] )*InterpolationFactor;
            Rec.AngRate[i]  = PrevRec.AngRate[i]   + ( NextRec.AngRate[i]  - PrevRec.AngRate[i]  )*InterpolationFactor;

         }

      }
      else
      {

         Rec         = NextRec;
         Rec.GpsTime = Time;

      }

   }

}

AnsiString const
TScramnet::GetStatusStr
   (
   )
{
   return( AnsiString( "" ) );
}

AnsiString const
TScramnet::GetParametersStr
   (
   )
{
   return( AnsiString( "" ) );
}

bool const
TScramnet::IsValid
   (
   ) const
{
   return( Valid_ );
}   

void
TScramnet::InitializeMem
   (
   )
{

   TRfParams RfParams;

   NumChannels_            = RfParams.RfNumChans[0];       // SCRAMNet only supports 1 RF at this time

   ExtToSim                = (TclExtToSimMem *) ( BaseAddr_ + ExtToSimOffset_ );
   SimToExt                = (TclSimToExtMem *) ( BaseAddr_ + SimToExtOffset_ );

   if ( ClearDataAtStart_ )
   {
      memset( ExtToSim, 0, sizeof( TclExtToSimMem ) );
      memset( SimToExt, 0, sizeof( TclSimToExtMem ) );
   }

   SimToExt->SimConfig.NumChannels = NumChannels_;

}

void
TScramnet::Signal
   (
   )
{

}

#endif

