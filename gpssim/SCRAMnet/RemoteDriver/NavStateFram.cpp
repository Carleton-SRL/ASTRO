#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
//
// $Workfile:: NavStateFram.cpp                                      $
//
// $Revision:: 3                                                     $
//
// $History:: NavStateFram.cpp                                       $
//
//*****************  Version 3  *****************
//User: Michael Wade Date: 7/28/02    Time: 10:41p
//Updated in $/TapMsec
//Use PosVec
//Added include file guards
//
//*****************  Version 2  *****************
//User: Michael Wade Date: 7/23/02    Time: 7:47p
//Updated in $/TapMsec
//Added Source Safe keywords
//BUILDER_INCLUDES ifdef
//Added vehicle number to top label
//
//
//---------------------------------------------------------------------------

#ifndef NavStateFramH
#include "NavStateFram.h"
#endif

#ifndef PosVecH
#include "PosVec.h"
#endif

#ifndef Wgs84H
#include "Wgs84.h"
#endif
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "OvcLabel"
#pragma link "ovclabel"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TNavStateFrame *NavStateFrame;
//---------------------------------------------------------------------------
__fastcall
TNavStateFrame::TNavStateFrame
   (
   TComponent  * Owner
   )
   : TFrame(Owner)
{
   pGeoFormat = new GeoFormat();
}

void
TNavStateFrame::SetVehicleNumber
   (
   const int VehicleNumber
   )
{
   AnsiString MainStr;
   MainStr.sprintf( "Navigation State #%d", VehicleNumber + 1 );
   NavStateLbl->Caption = MainStr;
}


__fastcall TNavStateFrame::~TNavStateFrame()
{
   delete pGeoFormat;
}


void
TNavStateFrame::SetNavState
   (
   const VehTruthRec & TruthRec
   )
{

   TGpsTime Time       = TruthRec.GpsTime;
   TDateTime DateTime  = Time.DateTime;

   DateTxt->Caption    = DateTime.DateString();
   TimeTxt->Caption    = DateTime.TimeString();

   AnsiString Str;
   Str.sprintf( "%10.2lf", Time.Seconds );
   GpsSecTxt->Caption  = Str;
   GpsWeekTxt->Caption = Time.Week;

   // Ecef Parameters
   //
   PosEcefXTxt->Caption = pGeoFormat->DisttoStr( TruthRec.Pos.x );
   PosEcefXLbl->Caption = pGeoFormat->GetDistUnits();
   PosEcefYTxt->Caption = pGeoFormat->DisttoStr( TruthRec.Pos.y );
   PosEcefYLbl->Caption = pGeoFormat->GetDistUnits();
   PosEcefZTxt->Caption = pGeoFormat->DisttoStr( TruthRec.Pos.z );
   PosEcefZLbl->Caption = pGeoFormat->GetDistUnits();

   VelEcefXTxt->Caption = pGeoFormat->VeltoStr( TruthRec.VelEcef[0] );
   VelEcefXLbl->Caption = pGeoFormat->GetVelUnits();
   VelEcefYTxt->Caption = pGeoFormat->VeltoStr( TruthRec.VelEcef[1] );
   VelEcefYLbl->Caption = pGeoFormat->GetVelUnits();
   VelEcefZTxt->Caption = pGeoFormat->VeltoStr( TruthRec.VelEcef[2] );
   VelEcefZLbl->Caption = pGeoFormat->GetVelUnits();

   // Geodetic Parameters
   //
   LatTxt->Caption      = pGeoFormat->LattoStr( TruthRec.Lat*R2D );
   LatLbl->Caption      = pGeoFormat->GetLatLonUnits();
   LonTxt->Caption      = pGeoFormat->LontoStr( TruthRec.Lon*R2D );
   LonLbl->Caption      = pGeoFormat->GetLatLonUnits();
   AltTxt->Caption      = pGeoFormat->AlttoStr( TruthRec.Alt );
   AltLbl->Caption      = pGeoFormat->GetDistUnits();

   VelNorthTxt->Caption = pGeoFormat->VeltoStr( TruthRec.VelNed[0] );
   VelNorthLbl->Caption = pGeoFormat->GetVelUnits();
   VelEastTxt->Caption  = pGeoFormat->VeltoStr( TruthRec.VelNed[1] );
   VelEastLbl->Caption  = pGeoFormat->GetVelUnits();
   VelDownTxt->Caption  = pGeoFormat->VeltoStr( TruthRec.VelNed[2] );
   VelDownLbl->Caption  = pGeoFormat->GetVelUnits();

   double Speed         = sqrt( TruthRec.VelNed[0]*TruthRec.VelNed[0] + TruthRec.VelNed[1]*TruthRec.VelNed[1] );
   SpeedTxt->Caption    = pGeoFormat->VeltoStr( Speed );
   SpeedLbl->Caption    = pGeoFormat->GetVelUnits();

   Str.sprintf( "%8.3lf", TruthRec.Attitude[2]*R2D );
   HeadingTxt->Caption = Str;

}

void
TNavStateFrame::SetNewGeoFormat
   (

   )
{

   delete pGeoFormat;
   pGeoFormat = new GeoFormat();

}



