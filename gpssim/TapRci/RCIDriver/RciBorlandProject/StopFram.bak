#include "pch.h"
#pragma hdrstop

#include "StopFram.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ovclabel"
#pragma resource "*.dfm"
TStopFrame *StopFrame;
//---------------------------------------------------------------------------
__fastcall TStopFrame::TStopFrame(TComponent* Owner)
   : TMsgDataFrame(Owner)
{
}

TMsgData const
TStopFrame::GetSendData()
{

   TStopMsg StopMsg;

   return( StopMsg.GetMsgData() );

}

void
TStopFrame::ProcessCancel()
{
}

//---------------------------------------------------------------------------
