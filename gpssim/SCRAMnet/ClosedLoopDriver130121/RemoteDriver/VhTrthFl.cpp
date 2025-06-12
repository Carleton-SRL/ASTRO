#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
//
// $Workfile:: VhTrthFl.cpp                                          $
//
// $Revision:: 4                                                     $
//
// $History:: VhTrthFl.cpp                                           $
//
//*****************  Version 4  *****************
//User: Michael Wade Date: 7/29/02    Time: 12:09a
//Updated in $/TapMsec
//Added include file guards
//
//*****************  Version 3  *****************
//User: Michael Wade Date: 7/23/02    Time: 8:09p
//Updated in $/TapMsec
//Added Source Safe keywords
//
//
//
//---------------------------------------------------------------------------

#ifndef VhTrthFlH
#include "VhTrthFl.h"
#endif

#ifndef VehStateRecH
#include "VehStateRec.h"
#endif

#ifndef ScenTimeH
#include "ScenTime.h"
#endif

TVehicleTruthFile::TVehicleTruthFile
   (
   const int                 InVehNum,
   bool                      InDoInterpolation
   ) :
   DoInterpolation( InDoInterpolation ),
   VehNum( InVehNum )
{

   AnsiString Filename;
   Filename.sprintf( "TRUTH%1d.SCN", VehNum + 1 );

   Init( Filename );

}

TVehicleTruthFile::TVehicleTruthFile
   (
   const AnsiString & Path,
   const int          InVehNum
   ) :
   VehNum( InVehNum )
{

   AnsiString Filename;
   Filename.sprintf( "\\TRUTH%1d.SCN", VehNum + 1 );

   Filename = Path + Filename;

   Init( Filename );

}

void
TVehicleTruthFile::Init
   (
   const AnsiString & Filename
   )
{

   VehicleStream.open( Filename );
   if ( !VehicleStream.good() ) return;


   //   Read the first two records in to get current and previous records.
   //
   VehicleStream >> Previous;
   CheckForWeekRollover( Previous.GpsTime );

   VehicleStream >> Current;
   CheckForWeekRollover( Current.GpsTime );

   First = Previous;
   VehicleStream.clear();

   VehicleStream.seekg(-(long)( sizeof( TVehStateRec )*(std::streampos)1),std::ios::end);
   VehicleStream.clear();

   VehicleStream >> Last;
   CheckForWeekRollover( Last.GpsTime );

   VehicleStream.seekg((std::streampos)0,std::ios::beg);
   VehicleStream.clear();

   Valid = true;

}

TVehicleTruthFile::~TVehicleTruthFile()
{
   VehicleStream.close();
}

#if(0)
TVehTruthRec const
TVehicleTruthFile::GetTruth
   (
   )
{
   return( GetTruth( TScenTime::GetCurTime() ) );
}
#endif


TVehTruthRec const
TVehicleTruthFile::GetTruth
   (
   const TGpsTime & ReqTime
   )
{
   TVehTruthRec Truth;
   if ( DoInterpolation )
   {
      GetTruthByInterpolation( ReqTime, &Truth );
   }
   else
   {
      GetTruthByExtrapolation( ReqTime, & Truth );
   }

   return( Truth );

}

bool const
TVehicleTruthFile::GetTruth
   (
   const TGpsTime    & ReqTime,
   TVehTruthRec      * Truth
   )
{
   if ( DoInterpolation )
   {
      return( GetTruthByInterpolation( ReqTime, Truth ) );
   }
   else
   {
      return( GetTruthByExtrapolation( ReqTime, Truth ) );
   }
}
///////////////////////////////////////////////////////////////////////////////
//   bool error = GetTruthByInterpolation(GPSTime &ReqTime, VehTruthRec *Truth)
// This function seeks through the vehicle truth file for two records that
// bracket the requested GPSTime, then interpolate to get the truth record.
// If the requested time is not within the truth file, an error bool is
// returned.
///////////////////////////////////////////////////////////////////////////////

bool
TVehicleTruthFile::GetTruthByInterpolation
   (
   const TGpsTime    & ReqTime,
   VehTruthRec      * Truth
   )
{

   //   If the requested time is less than the first time or greater than the last
   //   time, return an error.
   //
   if ( ReqTime < First.GpsTime )
   {
      *Truth         = First;
      Truth->GpsTime = ReqTime;
      return( true );

   }
   else if ( ReqTime > Last.GpsTime )
   {

      *Truth         = Last;
      Truth->GpsTime = ReqTime;
      return( false );

   }

   //   If the requested time is after the current time, read until
   //   the current time is greater.
   //
   while ( Current.GpsTime < ReqTime && !VehicleStream.eof() && VehicleStream.good() )
   {

      Previous = Current;
      VehicleStream >> Current;
      CheckForWeekRollover( Current.GpsTime );

   }

   //   If the requested time is before the previous time, backup until
   //   the previous is before the requested.
   //
   while ( Previous.GpsTime > ReqTime && VehicleStream.good() )
   {

      Current = Previous;
      VehicleStream.seekg(-(long)( sizeof( TVehStateRec )*(std::streampos)2),std::ios::cur);
      VehicleStream >> Previous;
      CheckForWeekRollover( Previous.GpsTime );

   }

   if ( VehicleStream.fail() )
   {

      Reset( );
      return( true );

   }

   //   Previous and Current now bracket the requested time.  Interpolate
   //   to get the best position.
   //
   Truth->GpsTime             = ReqTime;

   double InterpolationFactor = (ReqTime - Previous.GpsTime)/(Current.GpsTime - Previous.GpsTime);

   Truth->Pos          = Previous.Pos.EcefVec   + ( Current.Pos.EcefVec   - Previous.Pos.EcefVec   )*InterpolationFactor;
   Truth->VelEcefVec   = Previous.VelEcefVec    + ( Current.VelEcefVec    - Previous.VelEcefVec    )*InterpolationFactor;
   Truth->AccEcefVec   = Previous.AccEcefVec    + ( Current.AccEcefVec    - Previous.AccEcefVec    )*InterpolationFactor;
   Truth->JerkEcefVec  = Previous.JerkEcefVec   + ( Current.JerkEcefVec   - Previous.JerkEcefVec   )*InterpolationFactor;
   Truth->AttVec       = Previous.AttVec.Vector + ( Current.AttVec.Vector - Previous.AttVec.Vector )*InterpolationFactor;
   Truth->AngRateVec   = Previous.AngRateVec    + ( Current.AngRateVec    - Previous.AngRateVec    )*InterpolationFactor;

   return( false );
}
///////////////////////////////////////////////////////////////////////////////
//  bool error = GetTruthRecByExtrapolation(TGpsTime &ReqTime, VehTruthRec *Truth
// This function seeks through the truth file to find the record immediately
// preceding the requested time and then extrapolates to the requested time.
// If the requested time is not within the truth file, an error is returned.
///////////////////////////////////////////////////////////////////////////////
bool
TVehicleTruthFile::GetTruthByExtrapolation
   (
   const TGpsTime    & ReqTime,
   TVehTruthRec      * Truth
   )
{

   //   If the requested time is less than the first time or greater than the last
   //   time, return an error.
   //
   if ( ReqTime <= First.GpsTime )
   {

      *Truth = First;
      Truth->GpsTime = ReqTime;
      return( false );

   }
   else if ( ReqTime > Last.GpsTime )
   {

      *Truth         = Last;
      Truth->GpsTime = ReqTime;
      return( false );

   }

   //   If the requested time is after the current time, read until
   //   the current time is greater.
   //
   while ( Current.GpsTime < ReqTime && !VehicleStream.eof() && VehicleStream.good() )
   {

      Previous = Current;
      VehicleStream >> Current;
      CheckForWeekRollover( Current.GpsTime );

   }

   //   If the requested time is before the previous time, backup until
   //   the previous is before the requested.
   //
   while ( Previous.GpsTime > ReqTime && VehicleStream.good() )
   {

      Current = Previous;
      int seeksize           = ( -(long)( sizeof( TVehStateRec )*( std::streampos ) 2 ) );
      VehicleStream.seekg( seeksize, std::ios::cur );
      VehicleStream >> Previous;
      CheckForWeekRollover( Previous.GpsTime );

   }

   if ( VehicleStream.fail() )
   {

      VehicleStream.clear();
      VehicleStream.seekg((std::streampos)0,std::ios::beg);
      VehicleStream >> Previous >> Current;
      CheckForWeekRollover( Previous.GpsTime );
      CheckForWeekRollover( Current.GpsTime );
      return( true );

   }

   //   Previous and Current now bracket the requested time.  Extrapolate
   //   to get the best position.
   //   Note that Delta t is always positive.
   //
   const double DeltaT         = ReqTime - Previous.GpsTime;
   const double DeltaT2        = DeltaT*DeltaT*0.5;
   const double DeltaT3        = DeltaT*DeltaT*DeltaT/6.0;

   Truth->GpsTime              = ReqTime;

   Truth->Pos.EcefVec          = Previous.Pos.EcefVec  + DeltaT*Previous.VelEcefVec  + DeltaT2*Previous.AccEcefVec + DeltaT3*Previous.JerkEcefVec;
   Truth->VelEcefVec           = Previous.VelEcefVec   + DeltaT*Previous.AccEcefVec  + DeltaT2*Previous.JerkEcefVec;
   Truth->AccEcefVec           = Previous.AccEcefVec   + DeltaT*Previous.JerkEcefVec;
   Truth->JerkEcefVec          = Previous.JerkEcefVec;
   Truth->AttVec               = Previous.AttVec       + Previous.AngRateVec*DeltaT;

   return( false );

}

void
TVehicleTruthFile::Reset()
{

   VehicleStream.clear();

   VehicleStream.seekg((std::streampos)0,std::ios::beg);

   VehicleStream >> Previous >> Current;

   CheckForWeekRollover( Previous.GpsTime );
   CheckForWeekRollover( Current.GpsTime );

}

void
TVehicleTruthFile::CheckForWeekRollover
   (
   TGpsTime & Time
   )
{
   while ( Time.Seconds > SECONDS_PER_WEEK )
   {
      Time.Seconds -= SECONDS_PER_WEEK;
      ++Time.Week;
   }

}




