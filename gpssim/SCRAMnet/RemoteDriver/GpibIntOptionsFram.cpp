#include "pch.h"
#pragma hdrstop


//---------------------------------------------------------------------------
//
// $Workfile::                                                       $
//
// $Revision::                                                       $
//
// $History::                                                        $
//
//
//---------------------------------------------------------------------------


#include "Decl-32.h"

#ifndef GpibIntOptionsFramH
#include "GpibIntOptionsFram.h"
#endif

#ifndef RemoteDriverPfH
#include "RemoteDriverPf.h"
#endif

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ovclabel"
#pragma link "RzEdit"
#pragma link "RzSpnEdt"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"


static int Breakpt;

static char ErrorMnemonic[21][5] =
{
   "EDVR", "ECIC", "ENOL", "EADR", "EARG", "ESAC", "EABO", "ENEB", "EDMA", "",
   "EOIP", "ECAP", "EFSO", ""    , "EBUS", "ESTB", "ESRQ", ""    , ""    , "",
   "ETAB"
};

TGpibIntOptionsFrame *GpibIntOptionsFrame;
//---------------------------------------------------------------------------


__fastcall
TGpibIntOptionsFrame::TGpibIntOptionsFrame
   (
   TComponent    * Owner
   ) :
   TFrame( Owner ),
   ValidInterface_( false ),
   RemoteDriverPf( NULL )
{

   RemoteDriverPf                 = new TRemoteDriverPf();
   SetDisplayFromProfile();

}
//---------------------------------------------------------------------------


void
TGpibIntOptionsFrame::SetProfileFromDisplay
   (
   )
{

   RemoteDriverPf->GpibBoardIndex     = BoardIndexSpinEdit->Value;
   RemoteDriverPf->GpibPrimaryAddress = PrimaryAddrSpinEdit->Value;

}

void
TGpibIntOptionsFrame::SetDisplayFromProfile
   (
   )
{

   BoardIndexSpinEdit->Value         = RemoteDriverPf->GpibBoardIndex;
   PrimaryAddrSpinEdit->Value        = RemoteDriverPf->GpibPrimaryAddress;

}


void __fastcall
TGpibIntOptionsFrame::TestBtnClick
   (
   TObject * Sender
   )
{

   ValidInterface_          = false;

   AnsiString GpibBoardStr;
   GpibBoardStr.sprintf( "gpib%d", BoardIndexSpinEdit->Value );

   AnsiString TestResultsDetailStr;

   int Board = ibfind( GpibBoardStr.c_str() );
   if ( Board >= 0 )
   {

      TestResultsDetailsMemo->Lines->Add( GpibBoardStr + AnsiString( " board found. ") );

      ibpad( Board, PrimaryAddrSpinEdit->Value );

      if ( ibsta & ERR )
      {
         AnsiString ErrStr;

         ErrStr.sprintf( "Unable to set primary address to %d. ibsta = 0x%x iberr = %d (%s)",
                   PrimaryAddrSpinEdit->Value, ibsta, iberr, ErrorMnemonic[iberr]);

         TestResultsDetailsMemo->Lines->Add( ErrStr );
         ValidInterface_ = false;

      }
      else
      {

         TestResultsDetailsMemo->Lines->Add( AnsiString( "Primary address set to ") + AnsiString( (int) PrimaryAddrSpinEdit->Value ) );

         ValidInterface_ = true;

      }

   }
   else
   {

      AnsiString ErrStr;

      ErrStr.sprintf( "Unable to find board %s. ibsta = 0x%x iberr = %d (%s)",
                GpibBoardStr.c_str(), ibsta, iberr, ErrorMnemonic[iberr]);

      TestResultsDetailsMemo->Lines->Add( ErrStr );
      ValidInterface_ = false;

   }

   if ( ValidInterface )
   {

      TestResultsLbl->Caption = " PASSED ";
      TestResultsLbl->Font->Color = clGreen;

   }
   else
   {

      TestResultsLbl->Caption = " FAILED ";
      TestResultsLbl->Font->Color = clRed;

   }


}
//---------------------------------------------------------------------------


__fastcall
TGpibIntOptionsFrame::~TGpibIntOptionsFrame
   (

   )
{

   delete RemoteDriverPf;
   RemoteDriverPf = NULL;

   Breakpt++;

}

void
TGpibIntOptionsFrame::DoNewOptions
   (
   const bool Accept
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
TGpibIntOptionsFrame::GetOptionsChanged
   (
   )
{

   bool Changed     = false;

   try
   {

      Changed      |= BoardIndexSpinEdit->Value  != RemoteDriverPf->GpibBoardIndex;
      Changed      |= PrimaryAddrSpinEdit->Value != RemoteDriverPf->GpibPrimaryAddress;

   }
   catch(...)
   {
      CodeSite->SendMsg( csmError, "TGpibIntOptionsFrame::GetOptionsChanged exception" );
   }

   return( Changed );

}   




