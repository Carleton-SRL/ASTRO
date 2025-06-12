#include "pch.h"
#pragma hdrstop

#ifndef ClosedLoopRunFrmH
#include "ClosedLoopRunFrm.h"
#endif

#ifndef AboutDlgH
#include "AboutDlg.h"
#endif

#ifndef ScenTimeH
#include "ScenTime.h"
#endif

#ifndef PosVecH
#include "PosVec.h"
#endif

#ifndef Wgs84H
#include "Wgs84.h"
#endif

#ifndef RemoteTypesH
#include "RemoteTypes.h"
#endif

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ovclabel"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzSplit"
#pragma link "MsgListFram"
#pragma link "TeePolar"
#pragma link "MsgListFram"
#pragma link "MsgListFram"
#pragma link "MsgListFram"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
//
// $Workfile::                                                       $
//
// $Revision::                                                       $
//
// $History::                                                        $
//
//
//---------------------------------------------------------------------------





TClosedLoopRunForm *ClosedLoopRunForm;

extern TIntArr SignalTimes;
//---------------------------------------------------------------------------
__fastcall
TClosedLoopRunForm::TClosedLoopRunForm
   (
   TComponent                        * Owner,
   const TClosedLoopSimType          & InClosedLoopSimType
   ) :
   TForm( Owner ),
   ClosedLoopSimType( InClosedLoopSimType ),
   InTimer( false ),
   GtSeries( NULL )
{

   SatelliteSeries->Clear();

   CreateMsgDescMap();

   MsgListFrame->MsgListBox->Items->Clear();

   SetupVehiclePlot();

   for ( int i=0; i<NUM_DISP_CHANS; ++i )
   {

      TDataExtractionChanFrame *DataExtractionChan = new TDataExtractionChanFrame( this, i+1 );
      DataExtractionChan->Parent                   = DataExtractionScrollBox;
      DataExtractionChan->Align                    = alTop;
      DataExtractionChan->Visible                  = true;
      DataExtractionChan->Name                     = AnsiString( "DataExtractionChan" ) + AnsiString( i );

      DataExtractionChanArray.push_back( DataExtractionChan );

   }


   CLControl                                       = new TCLControl( ClosedLoopSimType );
   CLControl->Resume();


   CLCTimer->Enabled                               = true;

   SendMsgsForm                                    = new TSendMsgsForm( this, CLControl->Interface );
   SendMsgsForm->Visible                           = false;
}
//---------------------------------------------------------------------------
void __fastcall TClosedLoopRunForm::AboutMenuClick(TObject *Sender)
{

   TAboutDialog *AboutDialog = new TAboutDialog( this );

   AboutDialog->ShowModal();

   delete AboutDialog;

}

__fastcall
TClosedLoopRunForm::~TClosedLoopRunForm
   (
   )
{
//
}


//---------------------------------------------------------------------------

void __fastcall
TClosedLoopRunForm::CLCTimerTimer
   (
   TObject                 * Sender
   )
{

   if ( CLControl->StopSent )
   {
      CLCTimer->Enabled = false;
      Terminate();
      return;
   }
   // Set Num Sent/Rcvd
   //
   NumMsgsSentLbl->Caption             = CLControl->NumMsgsSent;
   NumMsgsRcvdLbl->Caption             = CLControl->NumMsgsRcvd;
   NumMsgsRcvdExceptStatLbl->Caption   = CLControl->NumMsgsRcvdExceptStat;

   AnsiString TimeStr = FloatToStrF
      (
         ( TScenTime::GetTimeMillisec() * 0.001 ),
         ffFixed,
         6,
         3
      );
   SimulatorTimeLbl->Caption           = TimeStr;

   InterfaceStatusStrLbl->Caption      = CLControl->InterfaceStatusStr;

   // Add plot point with current truth.  Note that not all points will be
   // plotted.  We just want to give the user an idea of the trajectory
   //
   TVehTruthRec LatestTruth            = CLControl->CurTruth;
   if ( LatestTruth != CurTruth )
   {

      CurTruth = LatestTruth;
      AddPlotPoint( CurTruth );

   }

   MsgTrafficArray                     = CLControl->MsgTrafficArray;
   InMsgs                              = CLControl->InMsgArray;

   ProcessMsgTrafficArray( MsgTrafficArray );
   ProcessInputMsgs( InMsgs );


}
//---------------------------------------------------------------------------

void
TClosedLoopRunForm::Terminate()
{
   if ( CLControl )
   {
      CLCTimer->Enabled = false;
      CLControl->Terminate();
      CLControl->WaitFor();
      delete CLControl;
      CLControl = NULL;
   }
   Application->Terminate();
}

void __fastcall
TClosedLoopRunForm::FormClose
   (
   TObject *Sender,
   TCloseAction &Action
   )
{

   CLCTimer->Enabled = false;
   Terminate();

}
//---------------------------------------------------------------------------
void
TClosedLoopRunForm::SetupVehiclePlot
   (
   )
{

   GtSeries                   = new TLineSeries(this);

   GtSeries->XValues->Order   = loNone;
   GtSeries->YValues->Order   = loNone;
   GtSeries->Pointer->Visible = true;
   GtSeries->ParentChart      = GtChart;

}

void
TClosedLoopRunForm::AddPlotPoint
   (
   const TVehTruthRec &Truth
   )
{
   GtSeries->AddXY( Truth.Pos.Lon*R2D, Truth.Pos.Lat*R2D, "", clBlue );
}

void
TClosedLoopRunForm::ProcessMsgTrafficArray
   (
   TMsgTrafficArray &Msgs
   )
{

   for ( unsigned int i=0; i<Msgs.size(); ++i )
   {

      TMsgTraffic & Msg = Msgs[i];

      if ( ( ( Msg.MsgId != StelMsgRcptStatMsgId ) && ( Msg.MsgId != StelTrajectoryProfileMsgId ) ) || TScenTime::GetTimeMillisec() < 5000 )
      {

         AnsiString Str;
         Str.sprintf( "%7.3lf", Msg.TimeMillisec*0.001 );
         if ( Msg.MsgSource == eMSG_SOURCE_SIM )
         {
            Str += AnsiString( "\tSIM" );
            Str += AnsiString( "\t" ) + StelInMsgDescMap[ Msg.MsgId ] + AnsiString( "\t" ) + AnsiString( Msg.MsgId );
         }
         else
         {
            Str += AnsiString( "\tCTLR" );
            Str += AnsiString( "\t" ) + StelOutMsgDescMap[ Msg.MsgId ] + AnsiString( "\t" ) + AnsiString( Msg.MsgId );
         }
         LastMsgLbl->Caption = Str;
         if ( ( Str.AnsiPos( "Traj" ) == 0 ) || Msg.TimeMillisec*0.001 < 5 )
         {
            MsgListFrame->MsgListBox->Items->Add( Str );
         }

      }

   }

}


void
TClosedLoopRunForm::CreateMsgDescMap
   (

   )
{

   for ( int i=0; i<StelNumSimMsgs; ++i )
   {

      StelInMsgDescMap[ StelSimMsgIdDesc[i].MsgId ] = AnsiString( StelSimMsgIdDesc[i].Desc );

   }

   for ( int i=0; i<StelNumCtlrMsgs; ++i )
   {

      StelOutMsgDescMap[ StelCtlrMsgIdDesc[i].MsgId ] = AnsiString( StelCtlrMsgIdDesc[i].Desc );

   }

}

void __fastcall TClosedLoopRunForm::BtnStopClick(TObject *Sender)
{
   CLControl->TerminateSim();
}
//---------------------------------------------------------------------------

void
TClosedLoopRunForm::ProcessInputMsgs
   (
   TInMsgArray &InMsgs
   )
{

   for ( unsigned int i=0; i<InMsgs.size(); ++i )
   {
      TInMsg &InMsg = InMsgs[i];

      switch ( InMsg.MsgId )
      {

         case StelSVLookAngleMsgId:
         {
            ProcessSVLookAngle( InMsg );
         }
         break;
         case StelCurTimeMsgId:
         {
            ProcessTime( InMsg );
         }
         break;
         case StelDataExtractionMsgId:
         {
//            ProcessDataExtraction( InMsg );
         }
         break;
         default:
         break;
      }
   }

   InMsgs.clear();

}

void
TClosedLoopRunForm::ProcessTime
   (
   const TInMsg            & InMsg
   )
{

   TStelTimeMsg StelTimeMsg = InMsg;
   TScheduleSignal::ResetStartCount( StelTimeMsg.TimeMillisec );

   CLControl->ProcessTimeMsg( StelTimeMsg.TimeMillisec );

}


void
TClosedLoopRunForm::ProcessSVLookAngle
   (
   const TInMsg & InMsg
   )
{

   TStelSvLookAngle StelSvLookAngle = InMsg;
   TSvLookAngleArray SvLookAngleArray = StelSvLookAngle.GetSvLookAngleArray();

   SatelliteSeries->Clear();

   for ( unsigned int i=0; i<SvLookAngleArray.size(); ++i )
   {
      TSvLookAngle &SvLookAngle = SvLookAngleArray[i];

      if ( SvLookAngle.GetSvid() )
      {
         double El = SvLookAngle.GetEl();
         if (  El > 0 )
         {

            double TmpEl = 90 - El;
            double TmpAz = SvLookAngle.GetAz()*(-1.0) + 90;
            TColor Color = clBlue;

            SatelliteSeries->AddPolar( TmpAz, TmpEl, AnsiString( SvLookAngle.GetSvid() ), Color );

         }

      }

   }

}

void __fastcall
TClosedLoopRunForm::SendMsgBtnClk
   (
   TObject * Sender
   )
{


   SendMsgsForm->Visible = true;

}

void __fastcall
TClosedLoopRunForm::StartSimBtnClk
   (
   TObject * Sender
   )
{

   CLControl->InitializeSim();
   StartSimBtn->Visible = false;

}
//---------------------------------------------------------------------------


void __fastcall TClosedLoopRunForm::SendTrajBtnClick(TObject *Sender)
{
   CLControl->Send1Traj();
}
//---------------------------------------------------------------------------

