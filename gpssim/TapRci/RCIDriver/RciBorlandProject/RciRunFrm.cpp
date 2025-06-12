#include "pch.h"
#pragma hdrstop

#include "RciRunFrm.h"
#include "StartScenFram.h"
#include "StartLocalFram.h"
#include "InitGeoFram.h"
#include "StopFram.h"
#include "ShutdownFram.h"
#include "SetSvidFram.h"
#include "SetPowerFram.h"
#include "QueryFram.h"
#include "Gpib.h"
#include "AboutDlg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MsgListFram"
#pragma link "ovclabel"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzSplit"
#pragma link "RzLstBox"
#pragma link "SsBase"
#pragma link "StAbout"
#pragma link "StBrowsr"
#pragma resource "*.dfm"
TRciRunForm *RciRunForm;
//---------------------------------------------------------------------------
__fastcall
TRciRunForm::TRciRunForm
   (
   TComponent*  Owner,
   TIntOptions *InIntOptions
   ) :
   TForm(Owner),
   MsgDataFrame( NULL ),
   Interface( NULL ),
   IntOptions( InIntOptions ),
   InTimer( false )
{

   MsgListFrame->MsgListBox->Items->Clear();
   InitializeInterface( IntOptions );
   Timer->Enabled = true;

}
//---------------------------------------------------------------------------
void __fastcall TRciRunForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TRciRunForm::StartScenBtnClick(TObject *Sender)
{

   delete MsgDataFrame;
   MsgDataFrame       = new TStartScenFrame( this );
   MsgDataFrame->Name = "StartScenFram";

   SetMsgDataFrame( MsgDataFrame );

}
//---------------------------------------------------------------------------
void __fastcall TRciRunForm::TimerTimer(TObject *Sender)
{
   if ( InTimer ) return;
   InTimer = true;

   SendBtn->Enabled   = ( MsgDataFrame != NULL );
   CancelBtn->Enabled = ( MsgDataFrame != NULL );

   Interface->QueueMsgs( OutMsgs );

   TInMsgArray InMsgArray;
   Interface->GetInputMsgs( InMsgArray );

   ProcessInputMsgs( InMsgArray );

   TMsgTrafficArray MsgTrafficArray = Interface->GetMsgTrafficArray();
   ProcessMsgTrafficArray( MsgTrafficArray );

   UpdateStatusBar();


   InTimer = false;

}

void
TRciRunForm::ProcessMsgTrafficArray
   (
   TMsgTrafficArray &Msgs
   )
{

   for ( unsigned int i=0; i<Msgs.size(); ++i )
   {
      TMsgTraffic &Msg = Msgs[i];
      AnsiString Str;
      Str.sprintf("%6.2lf", Msg.GetTimeMillisec()*0.001 );
      if ( Msg.GetSource() == eMSG_SOURCE_SIM )
      {
         Str += AnsiString( "\tSIM\t" );
      }
      else
      {
         Str += AnsiString( "\tCTLR\t" );
      }
      Str += Msg.GetMsgStr();
      MsgListFrame->MsgListBox->Items->Add( Str );

   }

}

//---------------------------------------------------------------------------


void
TRciRunForm::SetMsgDataFrame
   (
   TFrame * NewMsgDataFrame
   )
{

   if ( NewMsgDataFrame )
   {
      NewMsgDataFrame->Parent  = MsgDataPnl;
      NewMsgDataFrame->Align   = alClient;
      NewMsgDataFrame->Visible = true;
   }

}
void __fastcall TRciRunForm::InitGeoBtnClick(TObject *Sender)
{

   delete MsgDataFrame;
   MsgDataFrame       = new TInitGeoFrame( this );
   MsgDataFrame->Name = "InitGeoFram";

   SetMsgDataFrame( MsgDataFrame );

}
//---------------------------------------------------------------------------
void __fastcall TRciRunForm::StartLocalBtnClick(TObject *Sender)
{

   delete MsgDataFrame;
   MsgDataFrame       = new TStartLocalFrame( this );
   MsgDataFrame->Name = "StartLocalFram";

   SetMsgDataFrame( MsgDataFrame );

}
//---------------------------------------------------------------------------
void __fastcall TRciRunForm::SetSvidBtnClick(TObject *Sender)
{

   delete MsgDataFrame;
   MsgDataFrame       = new TSetSvidFrame( this );
   MsgDataFrame->Name = "SetSvidFram";

   SetMsgDataFrame( MsgDataFrame );

}
//---------------------------------------------------------------------------
void __fastcall TRciRunForm::SetPowerBtnClick(TObject *Sender)
{

   delete MsgDataFrame;
   MsgDataFrame       = new TSetPowerFrame( this );
   MsgDataFrame->Name = "SetPowerFram";

   SetMsgDataFrame( MsgDataFrame );

}
//---------------------------------------------------------------------------
void __fastcall TRciRunForm::StopBtnClick(TObject *Sender)
{

   delete MsgDataFrame;
   MsgDataFrame       = new TStopFrame( this );
   MsgDataFrame->Name = "StopFram";

   SetMsgDataFrame( MsgDataFrame );

}
//---------------------------------------------------------------------------
void __fastcall TRciRunForm::ShutdownBtnClick(TObject *Sender)
{

   delete MsgDataFrame;
   MsgDataFrame       = new TShutdownFrame( this );
   MsgDataFrame->Name = "ShutdownFram";

   SetMsgDataFrame( MsgDataFrame );

}
//---------------------------------------------------------------------------
void __fastcall TRciRunForm::QueryBtnClick(TObject *Sender)
{

   delete MsgDataFrame;
   MsgDataFrame       = new TQueryFrame( this );
   MsgDataFrame->Name = "QueryFram";

   SetMsgDataFrame( MsgDataFrame );

}
//---------------------------------------------------------------------------
void __fastcall TRciRunForm::SendBtnClick(TObject *Sender)
{
   TOutMsg OutMsg;

   TStartScenFrame *StartScen = dynamic_cast<TStartScenFrame*>( MsgDataFrame );
   if ( StartScen )
   {
      OutMsg = StartScen->GetOutMsg();
   }

   TInitGeoFrame *InitGeo = dynamic_cast<TInitGeoFrame*>( MsgDataFrame );
   if ( InitGeo )
   {
      OutMsg = InitGeo->GetOutMsg();
   }

   TStartLocalFrame *StartLocal = dynamic_cast<TStartLocalFrame*>( MsgDataFrame );
   if ( StartLocal )
   {
      OutMsg = StartLocal->GetOutMsg();
   }

   TSetSvidFrame *SetSvid = dynamic_cast<TSetSvidFrame*>( MsgDataFrame );
   if ( SetSvid )
   {
      OutMsg = SetSvid->GetOutMsg();
   }

   TSetPowerFrame *SetPower = dynamic_cast<TSetPowerFrame*>( MsgDataFrame );
   if ( SetPower )
   {
      OutMsg = SetPower->GetOutMsg();
   }

   TStopFrame *Stop = dynamic_cast<TStopFrame*>( MsgDataFrame );
   if ( Stop )
   {
      OutMsg = Stop->GetOutMsg();
   }

   TShutdownFrame *Shutdown = dynamic_cast<TShutdownFrame*>( MsgDataFrame );
   if ( Shutdown )
   {
      OutMsg = Shutdown->GetOutMsg();
   }

   TQueryFrame *Query = dynamic_cast<TQueryFrame*>( MsgDataFrame );
   if ( Query )
   {
      OutMsg = Query->GetOutMsg();
   }

   OutMsgs.push( OutMsg );


}

void
TRciRunForm::InitializeInterface
   (
   TIntOptions *IntOptions
   )
{

#if( 0 )
   TGpibOptions *pGpibOptions = dynamic_cast<TGpibOptions *>( IntOptions );
   if ( !pGpibOptions )
   {
      CodeSite->SendMsg( csmError, " dynamic_cast for GPIB Options ." );
      Application->MessageBox( " TCLControl::InitializeInterface failed.  Unable to cast GPIB Options", "Fatal Error", MB_OK );
      Application->Terminate();
      Application->ProcessMessages();
   }
   else
   {
      TGpibOptions GpibOptions = *pGpibOptions;
      Interface = new TGpib( GpibOptions );
      Interface->Resume();
   }
#else
   TGpibOptions GpibOptions;
   GpibOptions.BoardIndex  = 0;
   GpibOptions.PrimaryAddr = 15;
   Interface = new TGpib( GpibOptions );
   Interface->Resume();
#endif

}

void
TRciRunForm::ProcessInputMsgs
   (
   const TInMsgArray & InMsgArray
   )
{

   for ( unsigned int i=0; i<InMsgArray.size(); ++i )
   {
      ProcessInputMsg( InMsgArray[i] );
   }

}

void
TRciRunForm::ProcessInputMsg
   (
   const TInMsg & InMsg
   )
{

   AnsiString MsgId =( InMsg.GetMsgId() ).UpperCase();

   CodeSite->SendMsg( AnsiString( "Received external message: " ) + MsgId );
   if ( MsgId == AckMsgId )
   {
      ProcessAckMsg( InMsg );
   }
   else if ( MsgId == ChanStatMsgId )
   {
      ProcessChanStatMsg( InMsg );
   }
   else if ( MsgId == SimModeMsgId )
   {
      ProcessSimModeMsg( InMsg );
   }
   else if ( MsgId == BitResultsMsgId )
   {
      ProcessBitResultsMsg( InMsg );
   }
   else if ( MsgId == SysCfgMsgId )
   {
      ProcessSysCfgMsg( InMsg );
   }
   else
   {
      ProcessUnknownMsg( InMsg );
   }

}

void
TRciRunForm::ProcessUnknownMsg
   (
   const TInMsg & InMsg
   )
{

}

void
TRciRunForm::ProcessAckMsg
   (
   const TInMsg & InMsg
   )
{
   TAckMsg AckMsg = InMsg;

   TAck       Ack = AckMsg.GetAck();

   AckTimeRcvdLbl->Caption = AnsiString( (int) NINT( TScheduleSignal::GetCurTimeMillisec()*0.001 ) );

   AckMsgIdLbl->Caption    = Ack.MsgId;

   if ( Ack.MsgValid )
   {

      AckMsgValidLbl->Caption     = AnsiString( "Passed" );
      AckMsgValidLbl->Font->Color = clGreen;

   }
   else
   {

      AckMsgValidLbl->Caption     = AnsiString( "Failed" );
      AckMsgValidLbl->Font->Color = clRed;

   }

   if ( Ack.SimModeValid )
   {

      AckSimModeValidLbl->Caption     = AnsiString( "Passed" );
      AckSimModeValidLbl->Font->Color = clGreen;

   }
   else
   {

      AckSimModeValidLbl->Caption     = AnsiString( "Failed" );
      AckSimModeValidLbl->Font->Color = clRed;

   }

}

void
TRciRunForm::ProcessChanStatMsg
   (
   const TInMsg & InMsg
   )
{

#define NUM_CHANS_IN_CHAN_STAT_DISP (14)
   typedef struct {
      TOvcLabel *Chan;
      TOvcLabel *Svid;
      TOvcLabel *Power;
   } TChanStatDisp;
   TChanStatDisp ChanStatDisp[ NUM_CHANS_IN_CHAN_STAT_DISP ] =
   {
      { ChanStatCh0,  ChanStatSvidLbl0,  ChanStatPower0  },
      { ChanStatCh1,  ChanStatSvidLbl1,  ChanStatPower1  },
      { ChanStatCh2,  ChanStatSvidLbl2,  ChanStatPower2  },
      { ChanStatCh3,  ChanStatSvidLbl3,  ChanStatPower3  },
      { ChanStatCh4,  ChanStatSvidLbl4,  ChanStatPower4  },
      { ChanStatCh5,  ChanStatSvidLbl5,  ChanStatPower5  },
      { ChanStatCh6,  ChanStatSvidLbl6,  ChanStatPower6  },
      { ChanStatCh7,  ChanStatSvidLbl7,  ChanStatPower7  },
      { ChanStatCh8,  ChanStatSvidLbl8,  ChanStatPower8  },
      { ChanStatCh9,  ChanStatSvidLbl9,  ChanStatPower9  },
      { ChanStatCh10, ChanStatSvidLbl10, ChanStatPower10  },
      { ChanStatCh11, ChanStatSvidLbl11, ChanStatPower11  },
      { ChanStatCh12, ChanStatSvidLbl12, ChanStatPower12  },
      { ChanStatCh13, ChanStatSvidLbl13, ChanStatPower13  }
   };

   TChanStatMsg ChanStatMsg = InMsg;

   TChanStatArray ChanStatArray = ChanStatMsg.GetChanStatArray();

   for ( unsigned int i=0; i<min( (unsigned int) NUM_CHANS_IN_CHAN_STAT_DISP, ChanStatArray.size() ); ++i )
   {
      ChanStatDisp[i].Chan->Caption  = ChanStatArray[i].GetChan();
      ChanStatDisp[i].Svid->Caption  = ChanStatArray[i].GetSvid();
      ChanStatDisp[i].Power->Caption = ChanStatArray[i].GetL1Power();
   }

   for ( unsigned int i=ChanStatArray.size(); i<(unsigned int) NUM_CHANS_IN_CHAN_STAT_DISP; ++i )
   {
      ChanStatDisp[i].Chan->Visible  = false;
      ChanStatDisp[i].Svid->Visible  = false;
      ChanStatDisp[i].Power->Visible = false;
   }

}

void
TRciRunForm::ProcessSimModeMsg
   (
   const TInMsg & InMsg
   )
{
   TSimModeMsg SimModeMsg = InMsg;

   SimMode = SimModeMsg.GetSimMode();

   if ( SimMode == eSimIdle )
   {
      SimModeLbl->Caption = AnsiString( "IDLE" );
      SimModeLbl->Font->Color = clRed;
   }
   else if ( SimMode == eSimLocal )
   {
      SimModeLbl->Caption = AnsiString( "LOCAL" );
      SimModeLbl->Font->Color = clGreen;
   }
   else if ( SimMode == eSimScen )
   {
      SimModeLbl->Caption     = AnsiString( "Scenario" );
      SimModeLbl->Font->Color = clBlue;
   }

}

void
TRciRunForm::ProcessBitResultsMsg
   (
   const TInMsg & InMsg
   )
{

   TBitResultsMsg BitResultsMsg = InMsg;

   TBitError BitError = BitResultsMsg.GetBitResults();

   BitDateLbl->Caption = BitError.Date;
   BitTimeLbl->Caption = BitError.Time;

   if ( BitError.x1 )
   {
      Bitx1Lbl->Caption     = AnsiString( "Failed" );
      Bitx1Lbl->Font->Color = clRed;
   }
   else
   {
      Bitx1Lbl->Caption     = AnsiString( "Passed" );
      Bitx1Lbl->Font->Color = clGreen;
   }

   if ( BitError.x2 )
   {
      Bitx2Lbl->Caption     = AnsiString( "Failed" );
      Bitx2Lbl->Font->Color = clRed;
   }
   else
   {
      Bitx2Lbl->Caption     = AnsiString( "Passed" );
      Bitx2Lbl->Font->Color = clGreen;
   }

   if ( BitError.x3 )
   {
      Bitx3Lbl->Caption     = AnsiString( "Failed" );
      Bitx3Lbl->Font->Color = clRed;
   }
   else
   {
      Bitx3Lbl->Caption     = AnsiString( "Passed" );
      Bitx3Lbl->Font->Color = clGreen;
   }

   if ( BitError.Interrupt )
   {
      BitIntLbl->Caption     = AnsiString( "Failed" );
      BitIntLbl->Font->Color = clRed;
   }
   else
   {
      BitIntLbl->Caption     = AnsiString( "Passed" );
      BitIntLbl->Font->Color = clGreen;
   }

   if ( BitError.Ocxo )
   {
      BitOcxoLbl->Caption     = AnsiString( "Failed" );
      BitOcxoLbl->Font->Color = clRed;
   }
   else
   {
      BitOcxoLbl->Caption     = AnsiString( "Passed" );
      BitOcxoLbl->Font->Color = clGreen;
   }

   if ( BitError.Pll )
   {
      BitPllLbl->Caption     = AnsiString( "Failed" );
      BitPllLbl->Font->Color = clRed;
   }
   else
   {
      BitPllLbl->Caption     = AnsiString( "Passed" );
      BitPllLbl->Font->Color = clGreen;
   }

}

void
TRciRunForm::ProcessSysCfgMsg
   (
   const TInMsg & InMsg
   )
{

   TSysCfgMsg SysCfgMsg = InMsg;

   TSysCfg SysCfg       = SysCfgMsg.GetSysCfg();

   SysCfgNumChansLbl->Caption = SysCfg.NumChans;

   if ( SysCfg.L2Capable )
   {
      SysCfgL2CapableLbl->Caption     = "Yes";
      SysCfgL2CapableLbl->Font->Color = clBlue;
   }
   else
   {
      SysCfgL2CapableLbl->Caption     = "No";
      SysCfgL2CapableLbl->Font->Color = clBlue;
   }

   SysCfgMinPowerLbl->Caption = SysCfg.MinPower;
   SysCfgMaxPowerLbl->Caption = SysCfg.MaxPower;

}   



void
TRciRunForm::UpdateStatusBar
   (
   
   )
{
   StatusBar->Panels->Items[0]->Text = AnsiString( "Time: " ) +
      AnsiString( NINT( TScheduleSignal::GetCurTimeMillisec()*0.001 ) );

   TDateTime DateTime = TDateTime::CurrentDateTime();

   StatusBar->Panels->Items[1]->Text = DateTime.DateString();
   StatusBar->Panels->Items[2]->Text = DateTime.TimeString();

}

void __fastcall TRciRunForm::AboutMenuClick(TObject *Sender)
{

   TAboutDialog *AboutDialog = new TAboutDialog( this );

   AboutDialog->ShowModal();

   delete AboutDialog;

}
//---------------------------------------------------------------------------

