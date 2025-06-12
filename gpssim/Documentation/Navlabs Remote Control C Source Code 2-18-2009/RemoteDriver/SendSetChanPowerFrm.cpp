#include "pch.h"
#pragma hdrstop

#include "SendSetChanPowerFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzBckgnd"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TSendSetChanPowerForm *SendSetChanPowerForm;
//---------------------------------------------------------------------------
__fastcall TSendSetChanPowerForm::TSendSetChanPowerForm(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
