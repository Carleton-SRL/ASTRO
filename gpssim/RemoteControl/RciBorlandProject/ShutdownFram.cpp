#include "pch.h"
#pragma hdrstop

#include "ShutdownFram.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ovclabel"
#pragma resource "*.dfm"
TShutdownFrame *ShutdownFrame;
//---------------------------------------------------------------------------
__fastcall TShutdownFrame::TShutdownFrame(TComponent* Owner)
   : TFrame(Owner)
{
}

TOutMsg const
TShutdownFrame::GetOutMsg()
{

   TShutdownMsg ShutdownMsg;

   return( ShutdownMsg );

}

void
TShutdownFrame::ProcessCancel()
{
}


//---------------------------------------------------------------------------
