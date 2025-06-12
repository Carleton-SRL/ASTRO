#include "pch.h"
#pragma hdrstop

#include "RciDriverFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "o32flxbn"
#pragma link "ovclabel"
#pragma link "CSIntf"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzSplit"
#pragma resource "*.dfm"
TRciDriverForm *RciDriverForm;
//---------------------------------------------------------------------------
__fastcall
TRciDriverForm::TRciDriverForm
   (
   TComponent* Owner
   ) :
   TForm(Owner),
   IntType( eIntGpib )

{
}
//---------------------------------------------------------------------------
void __fastcall TRciDriverForm::CancelBtnClick(TObject *Sender)
{
   Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TRciDriverForm::InterfaceFlexBtnItemChange(TObject *Sender,
      int &OldItem, int &NewItem)
{
   eIntType NewIntType = GetIntTypeFromItem( NewItem );

   SetIntType( NewIntType );

}

eIntType const
TRciDriverForm::GetIntTypeFromItem
   (
   const int ItemIndex
   ) const
{
   return( (eIntType) ItemIndex );
}


void
TRciDriverForm::SetIntType
   (
   const eIntType NewIntType
   )
{
   if ( NewIntType == eIntGpib )
   {
      SetIntTypeGpib();
   }
   else if ( NewIntType == eIntSerial )
   {
      SetIntTypeSerial();
   }
   else if ( NewIntType == eIntEthernet )
   {
      SetIntTypeEthernet();
   }

}


void
TRciDriverForm::SetIntTypeGpib
   (

   )
{

   delete IntOptionsFrame;
   IntOptionsFrame          = new TGpibIntOptionsFrame( this );
   IntOptionsFrame->Parent  = RightPnl;
   IntOptionsFrame->Visible = true;
   IntOptionsFrame->Align   = alClient;
   IntOptionsFrame->Name    = "GpibOptionsFrame1";

}


void
TRciDriverForm::SetIntTypeSerial
   (

   )
{
   //TODO: Add your source code here
}


void
TRciDriverForm::SetIntTypeEthernet
   (

   )
{
   //TODO: Add your source code here
}

//---------------------------------------------------------------------------
void __fastcall TRciDriverForm::StartBtnClick(TObject *Sender)
{
   TIntOptions *IntOptions;
   switch ( IntType )
   {
      case eIntGpib:
      {
         TGpibIntOptionsFrame *pGpibIntOptionsFrame = dynamic_cast<TGpibIntOptionsFrame*>( IntOptionsFrame );
         if ( pGpibIntOptionsFrame )
         {
            TGpibOptions GpibOptions = pGpibIntOptionsFrame->GetOptions();
            IntOptions  = &GpibOptions;
         }
         else
         {
            Application->MessageBox( "TRemoteMainForm dynamic_cast failed on TIntOptionsFrame", "Error", MB_OK );
            Application->Terminate();
            Application->ProcessMessages();
         }
      }
      break;
      case eIntEthernet:
      {
         Application->MessageBox( "TRemoteMainForm dynamic_cast failed on TIntOptionsFrame.  Ethernet not yet supported", "Fatal Error", MB_OK );
         Application->Terminate();
         Application->ProcessMessages();
      }
      break;
      case eIntSerial:
      {
         Application->MessageBox( "TRemoteMainForm dynamic_cast failed on TIntOptionsFrame.  Serial not yet supported", "Fatal Error", MB_OK );
         Application->Terminate();
         Application->ProcessMessages();
      }
      break;
      default:
      {
         Application->MessageBox( "TRemoteMainForm dynamic_cast failed on TIntOptionsFrame.  Unknown interface type", "Fatal Error", MB_OK );
         Application->Terminate();
         Application->ProcessMessages();
      }

   }

   RciRunForm          = new TRciRunForm( this, IntOptions );
   RciRunForm->Visible = true;
   Visible             = false;

}
//---------------------------------------------------------------------------
