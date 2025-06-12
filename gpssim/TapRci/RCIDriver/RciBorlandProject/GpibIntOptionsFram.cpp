#include "pch.h"
#pragma hdrstop

#include "Decl-32.h"
#include "GpibIntOptionsFram.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ovclabel"
#pragma link "RzEdit"
#pragma link "RzSpnEdt"
#pragma link "RzButton"
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
__fastcall TGpibIntOptionsFrame::TGpibIntOptionsFrame(TComponent* Owner)
   : TFrame(Owner)
{
}
//---------------------------------------------------------------------------


TGpibOptions const
TGpibIntOptionsFrame::GetOptions
   (
   ) const
{
   TGpibOptions GpibOptions;
   GpibOptions.BoardIndex  = BoardIndexEdt->Value;
   GpibOptions.PrimaryAddr = PrimaryAddrEdt->Value;

   return( GpibOptions );

}
void __fastcall TGpibIntOptionsFrame::TestBtnClick(TObject *Sender)
{

   ValidInterface = false;

   TGpibOptions GpibOptions = GetOptions();

   AnsiString GpibBoardStr;
   GpibBoardStr.sprintf( "gpib%d", GpibOptions.BoardIndex );

   AnsiString TestResultsDetailStr;

   int Board = ibfind( GpibBoardStr.c_str() );
   if ( Board >= 0 )
   {

      TestResultsDetailsMemo->Lines->Add( GpibBoardStr + AnsiString( " board found. ") );

      ibpad( Board, GpibOptions.PrimaryAddr );

      if ( ibsta & ERR )
      {
         AnsiString ErrStr;

         ErrStr.sprintf( "Unable to set primary address to %d. ibsta = 0x%x iberr = %d (%s)",
                   GpibOptions.PrimaryAddr, ibsta, iberr, ErrorMnemonic[iberr]);

         TestResultsDetailsMemo->Lines->Add( ErrStr );
         ValidInterface = false;

      }
      else
      {

         TestResultsDetailsMemo->Lines->Add( AnsiString( "Primary address set to ") + AnsiString( GpibOptions.PrimaryAddr ) );

         ValidInterface = true;

      }

   }
   else
   {

      AnsiString ErrStr;

      ErrStr.sprintf( "Unable to find board %s. ibsta = 0x%x iberr = %d (%s)",
                GpibBoardStr.c_str(), ibsta, iberr, ErrorMnemonic[iberr]);

      TestResultsDetailsMemo->Lines->Add( ErrStr );
      ValidInterface = false;

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
   Breakpt++;
   //TODO: Add your source code here
}
