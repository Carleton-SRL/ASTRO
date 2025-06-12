#include "pch.h"
#pragma hdrstop

#include "SetSvidFram.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ovclabel"
#pragma link "RzEdit"
#pragma link "RzPanel"
#pragma link "RzSpnEdt"
#pragma resource "*.dfm"

TChanSvidArray TSetSvidFrame::DefChanSvidArray;



TSetSvidFrame *SetSvidFrame;
//---------------------------------------------------------------------------
__fastcall TSetSvidFrame::TSetSvidFrame(TComponent* Owner)
   : TFrame(Owner)
{

   TChanSvidEdt LocalChanSvidEdt[NumChansInFrame] =
   {
      { ChEdt0,  SvidEdt0 },
      { ChEdt1,  SvidEdt1 },
      { ChEdt2,  SvidEdt2 },
      { ChEdt3,  SvidEdt3 },
      { ChEdt4,  SvidEdt4 },
      { ChEdt5,  SvidEdt5 },
      { ChEdt6,  SvidEdt6 },
      { ChEdt7,  SvidEdt7 },
      { ChEdt8,  SvidEdt8 },
      { ChEdt9,  SvidEdt9 },
      { ChEdt10, SvidEdt10 },
      { ChEdt11, SvidEdt11 }
   };
   for ( int i=0; i<NumChansInFrame; ++i )
   {
      ChanSvidEdtArray[i].Chan = LocalChanSvidEdt[i].Chan;
      ChanSvidEdtArray[i].Svid = LocalChanSvidEdt[i].Svid;
   }

   if ( DefChanSvidArray.empty() )
   {
      DefChanSvidArray.push_back( TChanSvid( 1, -1 ) );
   }

   SetDisp( DefChanSvidArray );

}

void
TSetSvidFrame::SetDisp
   (
   const TChanSvidArray & ChanSvidArray
   )
{

   int NumChans = ChanSvidArray.size();
   SetVisible( NumChans );

   for ( int i=0; i<NumChans; ++i )
   {
      ChanSvidEdtArray[i].Chan->Value = ChanSvidArray[i].GetChan();
      ChanSvidEdtArray[i].Svid->Value = ChanSvidArray[i].GetSvid();
   }

}



//---------------------------------------------------------------------------
void __fastcall TSetSvidFrame::FrameResize(TObject *Sender)
{
   LeftPnl->Width = Width/2;
}
//---------------------------------------------------------------------------


void
TSetSvidFrame::SetVisible
   (
   const int NumChans
   )
{
   for ( int i=0; i<NumChansInFrame; ++i )
   {
      bool Visible = ( i < NumChans );
      ChanSvidEdtArray[i].Chan->Visible = Visible;
      ChanSvidEdtArray[i].Svid->Visible = Visible;
   }

   SvidLbl2->Visible  = ( NumChans > ( NumChansInFrame/2 ) );
   ChanLbl2->Visible  = ( NumChans > ( NumChansInFrame/2 ) );

}

TOutMsg const
TSetSvidFrame::GetOutMsg()
{

   int NumChans = NumChansEdt->IntValue;

   DefChanSvidArray.clear();

   for ( int i=0; i<NumChans; ++i )
   {
      DefChanSvidArray.push_back
      (
         TChanSvid
         (
            ChanSvidEdtArray[i].Chan->IntValue,
            ChanSvidEdtArray[i].Svid->IntValue
         )
      );
   }

   TSetSvidMsg SetSvidMsg( DefChanSvidArray );

   return( SetSvidMsg );

}

void
TSetSvidFrame::ProcessCancel()
{
   SetDisp( DefChanSvidArray );
}


void __fastcall TSetSvidFrame::NumChansEdtChange(TObject *Sender)
{

   int NumChans = NumChansEdt->IntValue;
   SetVisible( NumChans );

}
//---------------------------------------------------------------------------

