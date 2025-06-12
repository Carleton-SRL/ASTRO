#include "pch.h"
#pragma hdrstop

#include "InitGeoFram.h"
#include "RciDriverMsgs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ovcbase"
#pragma link "ovcef"
#pragma link "ovclabel"
#pragma link "ovcnf"
#pragma link "ovcpb"
#pragma resource "*.dfm"
TInitGeoFrame *InitGeoFrame;
//---------------------------------------------------------------------------

TInitGeoData TInitGeoFrame::DefInitGeoData;

__fastcall
TInitGeoFrame::TInitGeoFrame
   (
   TComponent* Owner
   )
   : TFrame(Owner)
{

   if ( (int) DefInitGeoData.Date == 0 )
   {
      DefInitGeoData.Date = TDateTime::CurrentDateTime();
      DefInitGeoData.Time = TDateTime::CurrentDateTime();
   }

   SetDisp( DefInitGeoData );

}

void
TInitGeoFrame::SetDisp
   (
   const TInitGeoData & InitGeoData
   )
{

   DatePicker->Date = InitGeoData.Date;
   TimePicker->Time = InitGeoData.Time;
   LatEdt->AsFloat  = InitGeoData.LatDeg;
   LonEdt->AsFloat  = InitGeoData.LonDeg;
   AltEdt->AsFloat  = InitGeoData.Alt;

}


TOutMsg const
TInitGeoFrame::GetOutMsg()
{

   TDateTime Date = DatePicker->Date;
   Date           = (int) Date;
   TDateTime Time = TimePicker->Time;
   int iTime      = (int) Time;
   double dTime   = (double) Time;
   double tTime   = dTime - iTime;

   TDateTime DateTime = Date + tTime;

   double LatDeg = LatEdt->AsFloat;
   double LonDeg = LonEdt->AsFloat;
   double Alt    = AltEdt->AsFloat;

   DefInitGeoData.Date = DatePicker->Date;
   DefInitGeoData.Time = TimePicker->Time;
   DefInitGeoData.LatDeg = LatDeg;
   DefInitGeoData.LonDeg = LonDeg;
   DefInitGeoData.Alt    = Alt;

   TInitGeoMsg InitGeoMsg( DateTime, LatDeg, LonDeg, Alt );

   return( InitGeoMsg );

}

void
TInitGeoFrame::ProcessCancel()
{

   SetDisp( DefInitGeoData );

}



//---------------------------------------------------------------------------
