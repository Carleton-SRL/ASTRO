#include "pch.h"
#pragma hdrstop

#include "StartScenFram.h"
#include "RciDriverMsgs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ovcbase"
#pragma link "ovcef"
#pragma link "ovclabel"
#pragma link "ovcsf"
#pragma resource "*.dfm"
TStartScenFrame *StartScenFrame;
//---------------------------------------------------------------------------

AnsiString TStartScenFrame::DefaultScen;

__fastcall
TStartScenFrame::TStartScenFrame
   (
   TComponent* Owner
   ) :
   TFrame(Owner)

{
   ScenNameEdt->Text = DefaultScen;
}

TOutMsg const
TStartScenFrame::GetOutMsg()
{

   DefaultScen = ScenNameEdt->Text;

   TStartScenMsg StartScenMsg( DefaultScen );

   return( StartScenMsg );

}

void
TStartScenFrame::ProcessCancel()
{
   ScenNameEdt->Text = DefaultScen;
}

//---------------------------------------------------------------------------
