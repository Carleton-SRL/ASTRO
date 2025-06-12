#include "pch.h"
#pragma hdrstop

#include "MsgListFram.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzLabel"
#pragma link "RzLstBox"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TMsgListFrame *MsgListFrame;
//---------------------------------------------------------------------------
__fastcall TMsgListFrame::TMsgListFrame(TComponent* Owner)
   : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
