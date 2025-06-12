#include "pch.h"
#pragma hdrstop

//---------------------------------------------------------------------------
//
// $Workfile:: EthernetIntOptionsFram.cpp                            $
//
// $Revision:: 1                                                     $
//
// $History:: EthernetIntOptionsFram.cpp                             $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 9/29/02    Time: 6:34p
//Created in $/TapRci
//Initial checkin from RemoteDriver
//
//
//---------------------------------------------------------------------------


#ifndef EthernetIntOptionsFramH
#include "EthernetIntOptionsFram.h"
#endif

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ovcbase"
#pragma link "ovcef"
#pragma link "ovcpb"
#pragma link "ovcpf"
#pragma link "ovclabel"
#pragma link "ovcnf"
#pragma link "RzPanel"
#pragma link "RzRadGrp"
#pragma link "RzButton"
#pragma resource "*.dfm"

TEthernetIntOptionsFrame *EthernetIntOptionsFrame;
//---------------------------------------------------------------------------
__fastcall
TEthernetIntOptionsFrame::TEthernetIntOptionsFrame
   (
   TComponent              * Owner
   ) :
   TFrame( Owner ),
   RemoteDriverPf( NULL )
{

   RemoteDriverPf               = new TRemoteDriverPf();

   SetDisplayFromProfile();

}

__fastcall
TEthernetIntOptionsFrame::~TEthernetIntOptionsFrame
   (
   )
{
   delete RemoteDriverPf;
}

void
TEthernetIntOptionsFrame::SetProfileFromDisplay
   (
   )
{


   RemoteDriverPf->EthernetHostAddress =
      HostAddr1->GetStrippedEditString() + AnsiString( "." ) +
      HostAddr2->GetStrippedEditString() + AnsiString( "." ) +
      HostAddr3->GetStrippedEditString() + AnsiString( "." ) +
      HostAddr4->GetStrippedEditString();

   RemoteDriverPf->EthernetPortNum    = Port->GetStrippedEditString().ToInt();
   RemoteDriverPf->EthernetServer     = ClientServerRadioGroup->ItemIndex == 1;

}

void
TEthernetIntOptionsFrame::SetDisplayFromProfile
   (
   )
{

   TIntArr HostAddrNumbers             = ConvertHostAddrToNumbers( RemoteDriverPf->EthernetHostAddress );

   HostAddr1->AsInteger                = HostAddrNumbers[0];
   HostAddr2->AsInteger                = HostAddrNumbers[1];
   HostAddr3->AsInteger                = HostAddrNumbers[2];
   HostAddr4->AsInteger                = HostAddrNumbers[3];

   Port->AsInteger                     = RemoteDriverPf->EthernetPortNum;

   ClientServerRadioGroup->ItemIndex   = RemoteDriverPf->EthernetServer ? 1 : 0;

   if ( ClientServerRadioGroup->ItemIndex < EthernetImageList->Count )
   {
      EthernetImageList->GetBitmap( ClientServerRadioGroup->ItemIndex, EthernetImage->Picture->Bitmap );
   }
   EthernetImage->Repaint();

}

void
TEthernetIntOptionsFrame::SetNumericFieldFocus
   (
   TOvcNumericField * NumericField
   )
{

   NumericField->SetFocus();
   NumericField->SelectAll();

}



void __fastcall
TEthernetIntOptionsFrame::HostAddrEnter
   (
   TObject *Sender
   )
{

   TOvcNumericField * NumericField = dynamic_cast<TOvcNumericField *>( Sender );
   if ( NumericField )
   {
      NumericField->SelectAll();
   }

}
//---------------------------------------------------------------------------

void __fastcall
TEthernetIntOptionsFrame::HostAddrChange
   (
   TObject * Sender
   )
{

   static const int NumHostNumericFields = 4;
   TOvcNumericField * HostFields[NumHostNumericFields] = { HostAddr1, HostAddr2, HostAddr3, HostAddr4 };

   TOvcNumericField * HostNumericField = dynamic_cast<TOvcNumericField *>( Sender );

   if ( HostNumericField )
   {
      for ( int i=0; i<NumHostNumericFields; ++i )
      {
         if ( HostNumericField == HostFields[i] )
         {
            AnsiString Str = HostNumericField->GetStrippedEditString();
            if ( Str.Length() == 3 && HostNumericField->CurrentPos == 2 )
            {
               if ( i < NumHostNumericFields-1 )
               {
                  SetNumericFieldFocus( HostFields[i+1] );
               }
               else if ( i == NumHostNumericFields-1 )
               {
                  SetNumericFieldFocus( Port );
               }
            }
         }
      }
   }

}
//---------------------------------------------------------------------------

void __fastcall
TEthernetIntOptionsFrame::ClientServerRadioGroupClick
   (
   TObject * Sender
   )
{

   EnableHostAddrDisplay( ClientServerRadioGroup->ItemIndex == 0 );

   if ( ClientServerRadioGroup->ItemIndex < EthernetImageList->Count )
   {
      EthernetImageList->GetBitmap( ClientServerRadioGroup->ItemIndex, EthernetImage->Picture->Bitmap );
   }
   EthernetImage->Repaint();

}
//---------------------------------------------------------------------------

void
TEthernetIntOptionsFrame::EnableHostAddrDisplay
   (
   const bool                HostAddrEnabled
   )
{

   static const int   NumHostNumericFields             = 4;
   TOvcNumericField * HostFields[NumHostNumericFields] = { HostAddr1, HostAddr2, HostAddr3, HostAddr4 };

   static const int   NumDotLbls                       = 3;
   TOvcLabel        * DotLbls[NumDotLbls]              = { Dot1, Dot2, Dot3 };

   for ( int i=0; i<NumHostNumericFields; ++i )
   {
      HostFields[i]->Enabled   = HostAddrEnabled;
   }

   for ( int i=0; i<NumDotLbls; ++i )
   {
      DotLbls[i]->Font->Color  = HostAddrEnabled ? clBlack : clGray;
   }

   HostAddrLbl->Font->Color    = HostAddrEnabled ? clBlack : clGray;

}

void
TEthernetIntOptionsFrame::DoNewOptions
   (
   const bool                Accept
   )
{

   if ( Accept )
   {
      SetProfileFromDisplay();
   }
   else
   {
      SetDisplayFromProfile();
   }

}

bool const
TEthernetIntOptionsFrame::GetOptionsChanged
   (
   )
{

   bool Changed      = false;

   try
   {

      TIntArr HostAddrNumbers             = ConvertHostAddrToNumbers( RemoteDriverPf->EthernetHostAddress );

      Changed       |= HostAddr1->AsInteger != HostAddrNumbers[0];
      Changed       |= HostAddr2->AsInteger != HostAddrNumbers[1];
      Changed       |= HostAddr3->AsInteger != HostAddrNumbers[2];
      Changed       |= HostAddr4->AsInteger != HostAddrNumbers[3];

      Changed       |= ( Port->AsInteger != RemoteDriverPf->EthernetPortNum );

      Changed       |= ( ClientServerRadioGroup->ItemIndex != RemoteDriverPf->EthernetServer ? 1 : 0 );

   }
   catch(...)
   {
      CodeSite->SendMsg( csmError, "TEthernetIntOptionsFrame::GetOptionsChanged exception" );
   }

   return( Changed );

}
