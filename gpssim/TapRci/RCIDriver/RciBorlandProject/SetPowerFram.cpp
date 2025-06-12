#include "pch.h"
#pragma hdrstop

#include "SetPowerFram.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ovclabel"
#pragma link "RzEdit"
#pragma link "RzPanel"
#pragma link "RzSpnEdt"
#pragma resource "*.dfm"
TSetPowerFrame *SetPowerFrame;


//---------------------------------------------------------------------------
// static data
//

bool            TSetPowerFrame::MinMaxPowerInitialized = false;
int             TSetPowerFrame::MinPower               = -200;
int             TSetPowerFrame::MaxPower               = -80;
TChanPowerArray TSetPowerFrame::DefChanPowerArray;

//---------------------------------------------------------------------------




__fastcall TSetPowerFrame::TSetPowerFrame(TComponent* Owner)
   : TFrame(Owner)
{

   TChanPowerEdt LocalChanPowerEdt[NumChansInFrame] =
   {
      { ChEdt0,  PowerEdt0 },
      { ChEdt1,  PowerEdt1 },
      { ChEdt2,  PowerEdt2 },
      { ChEdt3,  PowerEdt3 },
      { ChEdt4,  PowerEdt4 },
      { ChEdt5,  PowerEdt5 },
      { ChEdt6,  PowerEdt6 },
      { ChEdt7,  PowerEdt7 },
      { ChEdt8,  PowerEdt8 },
      { ChEdt9,  PowerEdt9 },
      { ChEdt10, PowerEdt10 },
      { ChEdt11, PowerEdt11 }
   };
   for ( int i=0; i<NumChansInFrame; ++i )
   {
      ChanPowerEdtArray[i].Chan        = LocalChanPowerEdt[i].Chan;
      ChanPowerEdtArray[i].Power       = LocalChanPowerEdt[i].Power;
      ChanPowerEdtArray[i].Power->Min  = MinPower;
      ChanPowerEdtArray[i].Power->Max  = MaxPower;
   }

   if ( DefChanPowerArray.empty() )
   {
      DefChanPowerArray.push_back( TChanPower( 1, MaxPower ) );
   }

   SetDisp( DefChanPowerArray );


}
//---------------------------------------------------------------------------

void
TSetPowerFrame::SetDisp
   (
   const TChanPowerArray & ChanPowerArray
   )
{

   int NumChans = max( ChanPowerArray.size(), (unsigned int) 1 );

   SetVisible( NumChans );

   for ( int i=0; i<NumChans; ++i )
   {
      ChanPowerEdtArray[i].Chan->Value  = ChanPowerArray[i].GetChan();
      ChanPowerEdtArray[i].Power->Value = ChanPowerArray[i].GetPower();
   }

}



//---------------------------------------------------------------------------
void __fastcall TSetPowerFrame::FrameResize(TObject *Sender)
{
   LeftPnl->Width = Width/2;
}
//---------------------------------------------------------------------------


void
TSetPowerFrame::SetVisible
   (
   const int NumChans
   )
{
   for ( int i=0; i<NumChansInFrame; ++i )
   {
      bool Visible = ( i < NumChans );
      ChanPowerEdtArray[i].Chan->Visible  = Visible;
      ChanPowerEdtArray[i].Power->Visible = Visible;
   }

   PowerLbl2->Visible = ( NumChans > ( NumChansInFrame/2 ) );
   ChanLbl2->Visible  = ( NumChans > ( NumChansInFrame/2 ) );

}

TOutMsg const
TSetPowerFrame::GetOutMsg()
{

   int NumChans = NumChansEdt->IntValue;

   DefChanPowerArray.clear();

   for ( int i=0; i<NumChans; ++i )
   {
      DefChanPowerArray.push_back
      (
         TChanPower
         (
            ChanPowerEdtArray[i].Chan->IntValue,
            ChanPowerEdtArray[i].Power->IntValue
         )
      );
   }

   TSetPowerMsg SetPowerMsg( DefChanPowerArray );

   return( SetPowerMsg );

}

void
TSetPowerFrame::ProcessCancel()
{
   SetDisp( DefChanPowerArray );
}


void __fastcall TSetPowerFrame::NumChansEdtChange(TObject *Sender)
{

   int NumChans = NumChansEdt->IntValue;
   SetVisible( NumChans );

}

void
TSetPowerFrame::SetMinMaxPower
   (
   const int InMinPower,
   const int InMaxPower
   )
{

   MinPower               = InMinPower;
   MaxPower               = InMaxPower;
   MinMaxPowerInitialized = true;

}
//---------------------------------------------------------------------------


