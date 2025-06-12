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
   : TFrame(Owner)
{
}

TOutMsg const
TStopFrame::GetOutMsg()
{

   TStopMsg StopMsg;

   return( StopMsg );

}

void
TStopFrame::ProcessCancel()
{
}

//---------------------------------------------------------------------------
