#include "pch.h"
#pragma hdrstop

#include "StartLocalFram.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ovclabel"
#pragma resource "*.dfm"
TStartLocalFrame *StartLocalFrame;
//---------------------------------------------------------------------------
__fastcall
TStartLocalFrame::TStartLocalFrame
   (
   TComponent* Owner
   ) :
   TFrame(Owner)
{
}

TOutMsg const
TStartLocalFrame::GetOutMsg()
{

   TStartLocalMsg StartLocalMsg;

   return( StartLocalMsg );

}

void
TStartLocalFrame::ProcessCancel()
{
}

//---------------------------------------------------------------------------
