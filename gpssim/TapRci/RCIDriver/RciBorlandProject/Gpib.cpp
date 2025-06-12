#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
// ClassExplorer Pro generated source file
// Created by Michael Wade on 2/3/2002, 6:00:54 PM
//---------------------------------------------------------------------------
#include "Gpib.h"

#include "Decl-32.h"
#include "Schedule.h"
//---------------------------------------------------------------------------

static char ErrorMnemonic[21][5] =
{
   "EDVR", "ECIC", "ENOL", "EADR", "EARG", "ESAC", "EABO", "ENEB", "EDMA", "",
   "EOIP", "ECAP", "EFSO", ""    , "EBUS", "ESTB", "ESRQ", ""    , ""    , "",
   "ETAB"
};

static const int MAX_GPIB_BYTES_TO_READ = 1000;
#define EOTMODE					1		// Enable the END message
#define EOSMODE					0		// Disable the EOS mode

TGpib::TGpib
   (
   const TGpibOptions &InGpibOptions
   ) :
   GpibOptions( InGpibOptions )
{

   CodeSite->EnterMethod( "TGpib::TGpib" );
   ValidInterface = false;

   AnsiString GpibBoardStr;
   GpibBoardStr.sprintf( "gpib%d", GpibOptions.BoardIndex );

   CodeSite->SendMsg( AnsiString( "GpibBoardStr " ) + GpibBoardStr );

   AnsiString TestResultsDetailStr;

   // Open the GPIB board
   //
   Board = ibdev( GpibOptions.BoardIndex, GpibOptions.PrimaryAddr, 0, T100ms, EOTMODE, EOSMODE );
   if ( Board >= 0 )
   {
      ValidInterface = true;
   }


//   Board = ibfind( GpibBoardStr.c_str() );
#if(0)
   if ( Board >= 0 )
   {

      CodeSite->SendMsg( GpibBoardStr + AnsiString( " board found. ") );

      ibpad( Board, GpibOptions.PrimaryAddr );

      if ( ibsta & ERR )
      {

         ReportError( AnsiString( "Unable to set primary address to " ) + AnsiString( GpibOptions.PrimaryAddr ) );
         ValidInterface = false;

      }
      else
      {

         CodeSite->SendMsg( AnsiString( "Primary address set to ") + AnsiString( GpibOptions.PrimaryAddr ) );

         ValidInterface = true;

      }

   }
   else
   {

      ReportError( AnsiString( "Unable to find board " ) + GpibBoardStr );
      ValidInterface = false;

   }
   ibtmo( Board, T1s );

   if ( ibsta & ERR )
   {

      ReportError( AnsiString( "Unable to set timeout" ) );
      ValidInterface = false;

   }
   else
   {

      CodeSite->SendMsg( AnsiString( "Timeout set to 10ms") );
      ValidInterface = true;

   }


   if ( ValidInterface )
   {

      CodeSite->SendMsg( csmNote, " GPIB Interface valid." );

   }
   else
   {

      CodeSite->SendMsg( csmError, " GPIB Interface failed." );

   }
#endif

   CodeSite->ExitMethod( "TGpib::TGpib" );

}

bool const
TGpib::SendMsg
   (
   const TMsgData & Data
   )
{

   bool Err = false;

   ibwrt( Board, (void *) &Data[0], Data.size() );

   if ( ibsta & ERR )
   {
      Err = true;
      ReportError( AnsiString( "Error on write. " ) );
   }

   return( Err );

}

void
TGpib::ReadMsg
   (
   TMsgData &MsgData
   )
{

   ibwait( Board, 0 );

   if ( ibsta & ERR )
   {

      AnsiString ErrStr;
      ErrStr.sprintf("Error on ibwait: t=%d ", TScheduleSignal::GetCurTimeMillisec() );

      ReportError( ErrStr );

      ibclr( Board );

   }

   if ( ibsta & RQS )
   {

      AnsiString ErrStr;
      ErrStr.sprintf("RQS: t=%d ", TScheduleSignal::GetCurTimeMillisec() );
      CodeSite->SendMsg( ErrStr );
      char spr;
      ibrsp( Board, &spr );

      if ( ibsta & ERR )
      {
         AnsiString ErrStr;
         ErrStr.sprintf( "Error on ibrsp t=%d ", TScheduleSignal::GetCurTimeMillisec());

         ReportError( ErrStr );

      }
#define MAX_GPIB_BYTES ( 200 )
      unsigned char Data[MAX_GPIB_BYTES];
      ibrd( Board, Data, MAX_GPIB_BYTES );

      if ( ibsta & ERR )
      {

         ReportError( AnsiString( "Error on read. " ) );

      }
      else
      {
         for ( int i=0; i<ibcntl; ++i )
         {
            MsgData.push_back( (unsigned char) Data[i] );
         }
      }
   }


}

__fastcall
TGpib::~TGpib
   (

   )
{
   ibonl( Board, 0 );
}

void
TGpib::ReportError
   (
   const AnsiString &PreStr
   )
{

   if ( ibsta & ERR )
   {

      AnsiString ErrStr;

      ErrStr.sprintf( " ibsta = 0x%x iberr = %d (%s)",
                ibsta, iberr, ErrorMnemonic[iberr]);

      CodeSite->SendMsg( csmError, PreStr + ErrStr );

   }

}
