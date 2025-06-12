#include "pch.h"
#pragma hdrstop

#include "EtherFram.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEtherFrame *EtherFrame;
//---------------------------------------------------------------------------
__fastcall TEtherFrame::TEtherFrame(TComponent* Owner)
   : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
