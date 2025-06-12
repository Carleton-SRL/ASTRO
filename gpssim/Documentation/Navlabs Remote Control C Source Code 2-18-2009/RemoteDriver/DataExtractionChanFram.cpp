#include "pch.h"
#pragma hdrstop

#ifndef DataExtractionChanFramH
#include "DataExtractionChanFram.h"
#endif

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



//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ovclabel"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TDataExtractionChanFrame *DataExtractionChanFrame;
//---------------------------------------------------------------------------


__fastcall
TDataExtractionChanFrame::TDataExtractionChanFrame
   (
   TComponent              * Owner,
   const int                 InChanNum
   ) :
   TFrame( Owner ),
   ChanNum( InChanNum ),
   Svid( 0 ),
   Range( 0 )
{

   ChanLbl->Caption  = ChanNum;
   SvidLbl->Caption  = "";
   RangeLbl->Caption = "";

}

void
TDataExtractionChanFrame::SetData
   (
   const int        InSvid,
   const double     InRange
   )
{

   Svid                      = InSvid;
   Range                     = InRange;

   SvidLbl->Visible          = ( Svid != 0 );
   RangeLbl->Visible         = ( Svid != 0 );

   SvidLbl->Caption          = Svid;

   AnsiString RangeStr;
   RangeStr.sprintf( "%12.2lf", Range );

   RangeLbl->Caption         = RangeStr;

}   

//---------------------------------------------------------------------------
