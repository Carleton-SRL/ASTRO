#include "pch.h"
#pragma hdrstop

#ifndef AttVecH
#include "AttVec.h"
#endif

//---------------------------------------------------------------------------
//
// $Workfile:: AttVec.cpp                                            $
//
// $Revision:: 1                                                     $
//
// $History:: AttVec.cpp                                             $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 9/07/02    Time: 12:52p
//Created in $/RemoteDriver
//
//
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

#pragma package(smart_init)


TAttVec::TAttVec
   (
   const double * const pAttitude
   )
{

   ( *this ) = pAttitude;

}

TAttVec &
TAttVec::operator =
   (
   const double * const pAttitude
   )
{
   CnbDirty = true;

   for ( int i=0; i<3; ++i )
   {
      FAttitude[i] = pAttitude[i];
   }

   return( *this );

}

TAttVec::TAttVec
   (
   const TVector & AttVec
   )
{
   ( *this ) = AttVec;
}

TAttVec &
TAttVec::operator =
   (
   const TVector & AttVec
   )
{

   CnbDirty = true;

   FAttitude = AttVec;

   return( *this );

}


TAttVec::TAttVec
   (
   const TAttVec & Source
   )
{
   ( *this ) = Source;
}

TAttVec &
TAttVec::operator =
   (
   const TAttVec & Source
   )
{

   FAttitude = Source.FAttitude;
   FCnb      = Source.FCnb;
   CnbDirty  = Source.CnbDirty;

   return( *this );

}

TAttVec::TAttVec
   (
   const TValArray & Source
   )
{
   ( *this ) = Source;
}

TAttVec &
TAttVec::operator =
   (
   const TValArray & Source
   )
{
   FAttitude = Source;
   CnbDirty  = true;

   return( *this );
   
}




TAttVec::TAttVec
   (
   const TDcm & Cnb
   )
{
   ( *this ) = Cnb;
}

TAttVec &
TAttVec::operator =
   (
   const TDcm & InCnb
   )
{

   FCnb     = Cnb;
   CnbDirty = false;
   CnbToEuler( Cnb, FAttitude[0], FAttitude[1], FAttitude[2] );

   return( *this );

}


void
TAttVec::CnbToEuler
   (
   const TDcm   & Cnb,
   double       & Roll,
   double       & Pitch,
   double       & Heading
   )
{

   double SinePitch = -Cnb(0,2);
   SinePitch        = ( SinePitch < -1.0 ) ? -1.0 : SinePitch;
   SinePitch        = ( SinePitch >  1.0 ) ?  1.0 : SinePitch;
   Pitch            = asin( SinePitch );

   if (
         (
            ( Cnb(1,2) != 0.0 ) || ( Cnb(2,2) != 0.0 )
         ) &&
         (
            ( Cnb(0,1) != 0.0 ) || ( Cnb(0,0) != 0.0 )
         )
      )
   {

      Roll    = atan2( Cnb(1,2), Cnb(2,2) );
      Heading = atan2( Cnb(0,1), Cnb(0,0) );

   }
   else
   {

      Roll    = 0.0;
      Heading = 0.0;
      if ( ( Cnb(2,1) != 0.0 ) || ( Cnb(1,1) != 0.0 ) )
      {
         Roll = atan2( -Cnb(2,1), Cnb(1,1) ) + Heading*SinePitch;
      }

   }

}

TDcm const
TAttVec::EulerToCnb
   (
   const double   Roll,
   const double   Pitch,
   const double   Heading
   )
{

   return( ( TDcm::Rotx( Roll ) * TDcm::Roty( Pitch ) ) * TDcm::Rotz( Heading ) );

}

