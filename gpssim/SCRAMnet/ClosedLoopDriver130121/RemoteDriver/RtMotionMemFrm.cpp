//---------------------------------------------------------------------------

#include "pch.h"
#pragma hdrstop

//---------------------------------------------------------------------------
//
// $Workfile:: RtMotionMemFrm.cpp                                    $
//
// $Revision:: 1                                                     $
//
// $History:: RtMotionMemFrm.cpp                                     $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 3/24/04    Time: 4:08p
//Created in $/RemoteDriver
//
//
//---------------------------------------------------------------------------


#ifndef RtMotionMemFrmH
#include "RtMotionMemFrm.h"
#endif

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzSplit"
#pragma link "RzStatus"
#pragma link "RzTabs"
#pragma link "dxNavBar"
#pragma link "dxNavBarBase"
#pragma link "dxNavBarCollns"
#pragma link "ovcbase"
#pragma link "ovcdrpvw"
#pragma link "ovcrptvw"
#pragma link "ovcrvidx"
#pragma link "RzLabel"
#pragma resource "*.dfm"
TRtMotionMemForm *RtMotionMemForm;
//---------------------------------------------------------------------------

static const int RangeReportChanIndex              = 0;
static const int RangeReportSvidIndex              = 1;
static const int RangeReportRangeIndex             = 2;
static const int RangeReportRangeRateIndex         = 3;
static const int RangeReportClockIndex             = 4;
static const int RangeReportL1IonoIndex            = 5;
static const int RangeReportL2IonoIndex            = 6;
static const int RangeReportTropoIndex             = 7;
static const int RangeReportUereIndex              = 8;
static const int RangeReportMultipathIndex         = 9;
static const int RangeReportMultipathRateIndex     = 10;
static const int RangeReportSaIndex                = 11;
static const AnsiString RangeReportDescBase        = "Range Data";


__fastcall
TRtMotionMemForm::TRtMotionMemForm
   (
   TComponent               * Owner,
   const TClosedLoopSimType & InClosedLoopSimType
   ) :
   ClosedLoopSimType( InClosedLoopSimType ),
   TForm( Owner ),
   ScenIni_( NULL ),
   TapMsecPf_( NULL ),
   ScramnetDll_( NULL ),
   FirstRangeReport_( true ),
   InitValid_( false )
{

   ScenIni_                    = new TScenIniFile();

   VehTruthFile                = new TVehicleTruthFile( ClosedLoopSimType.Path, 0 );

   FirstTruth_                 = VehTruthFile->GetFirst();
   LastTruth_                  = VehTruthFile->GetLast();

   FirstTime                   = FirstTruth_.GpsTime;
   LastTime                    = LastTruth_.GpsTime;

   TrajectoryDeltaTimeMillisec = NINT( ( 1.0/ClosedLoopSimType.UpdateRate ) * 1000 );
   LastTrajectoryTimeMillisec  = -TrajectoryDeltaTimeMillisec;



   InitMem();

}
//---------------------------------------------------------------------------


void
TRtMotionMemForm::InitMem
   (
   )
{

   if ( ScenIni_->Scramnet )
   {


      ScramnetDll_            = new TScramnetDll();
      ScramnetDll_->sp_scram_init();

      BaseAddr_               = (unsigned char *) ScramnetDll_->get_base_mem();

   }

   ExtToSimMem_               = (TclExtToSimMem *) ( BaseAddr_ + TapMsecPf_->RtMotionMemExtToSimOffset );
   SimToExtMem_               = (TclSimToExtMem *) ( BaseAddr_ + TapMsecPf_->RtMotionMemSimToExtOffset );


}

TclTimeSvRec const
TRtMotionMemForm::GetTimeSvRec
   (
   )
{

   return( SimToExtMem_->TimeSvRecMem.Which == 1 ? SimToExtMem_->TimeSvRecMem.TimeSvRec1 : SimToExtMem_->TimeSvRecMem.TimeSvRec2 );

}
TclTimeChannelStatus const
TRtMotionMemForm::GetTimeChannelStatus
   (
   )
{

   return( SimToExtMem_->TimeChannelStatusMem.Which == 1 ? SimToExtMem_->TimeChannelStatusMem.TimeChannelStatus1 : SimToExtMem_->TimeChannelStatusMem.TimeChannelStatus2 );

}
TclCurTime const
TRtMotionMemForm::GetCurTime
   (
   )
{

   return( SimToExtMem_->CurTime.Which == 1 ? SimToExtMem_->CurTime.Time1 : SimToExtMem_->CurTime.Time2 );

}


void
TRtMotionMemForm::UpdateSvRecData
   (
   )
{

   TclTimeSvRec TimeSvRec        = GetTimeSvRec();


   RangeReportView->BeginUpdate();

   RangeReportView->Items->Clear();

   for ( unsigned int i=0; i<ClosedLoopMem::MaxChannels; ++i )
   {

      TclSvRec & SvRec                                 = TimeSvRec.SvRec[i];

      TOvcDataRvItem * Item                            = RangeReportView->Items->Add();

      Item->AsInteger[RangeReportChanIndex]            = ( i + 1 );

      if ( SvRec.Svid )
      {

         AnsiString Str;

         Item->AsString[RangeReportSvidIndex]          = AnsiString( SvRec.Svid );

         Str.sprintf( "%11.2lf", SvRec.Range );
         Item->AsString[RangeReportRangeIndex]         = Str;

         Str.sprintf( "%11.2lf", SvRec.RangeRate );
         Item->AsString[RangeReportRangeRateIndex]     = Str;

         Str.sprintf( "%11.2lf", SvRec.Clock );
         Item->AsString[RangeReportClockIndex]         = Str;

         Str.sprintf( "%6.2lf", SvRec.L1Iono );
         Item->AsString[RangeReportL1IonoIndex]        = Str;

         Str.sprintf( "%6.2lf", SvRec.L2Iono );
         Item->AsString[RangeReportL2IonoIndex]        = Str;

         Str.sprintf( "%6.2lf", SvRec.Tropo );
         Item->AsString[RangeReportTropoIndex]         = Str;

         Str.sprintf( "%6.2lf", SvRec.Uere );
         Item->AsString[RangeReportUereIndex]          = Str;

         Str.sprintf( "%6.2lf", SvRec.SwMpRange );
         Item->AsString[RangeReportMultipathIndex]     = Str;

         Str.sprintf( "%6.3lf", SvRec.SwMpRate );
         Item->AsString[RangeReportMultipathRateIndex] = Str;

         Str.sprintf( "%6.2lf", SvRec.Sa );
         Item->AsString[RangeReportSaIndex]            = Str;

      }
   }

   RangeReportView->EndUpdate();

   if ( FirstRangeReport_ )
   {
      RangeReportView->ScaleColumnWidths();
      FirstRangeReport_ = false;
   }

}

void
TRtMotionMemForm::UpdateTime
   (
   )
{

   TclCurTime CurTimecl          = GetCurTime();
   TGpsTime Time( CurTimecl.GpsTime.Week, CurTimecl.GpsTime.Seconds );

   TDateTime CurDateTime         = Time.ToTDateTime();
   AnsiString GpsTimeStr;
   GpsTimeStr.sprintf( "%d %8.1lf" , Time.Week, Time.Seconds );
   GpsTimeVal->Caption           = GpsTimeStr;

   DateTimeVal->Caption          = CurDateTime.DateString() + AnsiString( " " ) + CurDateTime.TimeString();

}

void
TRtMotionMemForm::InitFromVehTruthRec
   (
   TVehTruthRec            & Rec
   )
{

   InitRec_                = Rec;

   AnsiString StartTapStr;

   TclInitialization InitData;

   FillVehicleState( &InitData.InitialVehicleState.VehicleState, InitRec_ );

   InitData.InitialVehicleState.GpsTime.Week    = InitRec_.GpsTime.Week;
   InitData.InitialVehicleState.GpsTime.Seconds = InitRec_.GpsTime.Seconds;

   InitData.Valid                               = false;

   memcpy( &( ExtToSimMem_->Initialization ), &( InitData ), sizeof( TclInitialization ) );

   ExtToSimMem_->Initialization.Valid           = true;

   InitValid_                                   = true;

   StartTapStr.sprintf( "Starting simulation at %d:%lf", InitRec_.GpsTime.Week, InitRec_.GpsTime.Seconds );
   CodeSite->SendMsg( StartTapStr );

}

void
TRtMotionMemForm::FillVehicleState
   (
   TclVehicleState         * VehState,
   TVehTruthRec            & VehStateRec
   )
{

   for ( int i=0; i<3; ++i )
   {

      VehState->PosEcef[i] = VehStateRec.PosEcef[i];
      VehState->VelEcef[i] = VehStateRec.VelEcef[i];
      VehState->AccEcef[i] = VehStateRec.AccEcef[i];
      VehState->JrkEcef[i] = VehStateRec.JerkEcef[i];
      VehState->Att[i]     = VehStateRec.Attitude[i];
      VehState->AngRate[i] = VehStateRec.AngRate[i];

   }

}

void
TRtMotionMemForm::SetVehicleState
   (
   )
{

      if ( ++VehTruthTimerCount > VehTruthFileCount )
      {

         TVehTruthRec Rec;
         VehTruthStream >> Rec;

         ++VehTruthFileCount;

         TclTimeVehicleState State;

         FillVehicleState( &( State.VehicleState ), Rec );

         State.GpsTime.Week    = Rec.GpsTime.Week;
         State.GpsTime.Seconds = Rec.GpsTime.Seconds;

         if ( clMem->ExtToSimMem.TimeVehicleStateMem.Which == 1 )
         {
            memcpy( &( clMem->ExtToSimMem.TimeVehicleStateMem.State2 ), &State, sizeof( State ) );
            clMem->ExtToSimMem.TimeVehicleStateMem.Which = 2;
         }
         else
         {
            memcpy( &( clMem->ExtToSimMem.TimeVehicleStateMem.State1 ), &State, sizeof( State ) );
            clMem->ExtToSimMem.TimeVehicleStateMem.Which = 1;
         }

      }

}

