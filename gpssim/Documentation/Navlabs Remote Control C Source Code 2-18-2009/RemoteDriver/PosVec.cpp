#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
//
// $Workfile:: PosVec.cpp                                            $
//
// $Revision:: 2                                                     $
//
// $History:: PosVec.cpp                                             $
//
//*****************  Version 2  *****************
//User: Michael Wade Date: 7/23/02    Time: 7:51p
//Updated in $/TapMsec
//Added Source Safe keywords
//
//
//
//
//
//---------------------------------------------------------------------------

#ifndef WgsConsH
#include "wgscons.h"
#endif

#ifndef PosVecH
#include "PosVec.h"
#endif

//---------------------------------------------------------------------------


void __fastcall
TPosVec::SetLon
   (
   double value
   )
{
   FLon      = value;
   EcefDirty = true;
   FLonDirty = false;


}

void __fastcall
TPosVec::SetLat
   (
   double value
   )
{
   FLat      = value;
   EcefDirty = true;
   FLatDirty = false;

}

void __fastcall
TPosVec::SetAlt
   (
   double value
   )
{

   FAlt      = value;
   EcefDirty = true;
   FAltDirty = false;

}

void __fastcall
TPosVec::Setz
   (
   double value
   )
{

   Ecef[2]     = value;
   GeoDirty    = true;
   FEcefzDirty = false;

}

void __fastcall
TPosVec::Sety
   (
   double value
   )
{

   Ecef[1]     = value;
   GeoDirty    = true;
   FEcefyDirty = false;

}

void __fastcall
TPosVec::Setx
   (
   double value
   )
{

   Ecef[0]     = value;
   GeoDirty    = true;
   FEcefxDirty = false;

}

double __fastcall
TPosVec::GetLon
   (

   ) const
{

   if ( GeoDirty )
   {
      CalcGeo();
   }
   return ( FLon );

}

double __fastcall
TPosVec::GetLat
   (

   ) const
{
   if ( GeoDirty )
   {
      CalcGeo();
   }
   return ( FLat );

}

double __fastcall
TPosVec::GetLonDeg
   (

   ) const
{

   return( GetLon()*R2D );

}

double __fastcall
TPosVec::GetLatDeg
   (

   ) const
{

   return( GetLat()*R2D );

}

double __fastcall
TPosVec::GetAlt
   (

   ) const
{
   if ( GeoDirty )
   {
      CalcGeo();
   }
   return ( FAlt );

}

double __fastcall
TPosVec::Getz
   (

   ) const
{

   if ( EcefDirty )
   {
      CalcEcef();
   }
   return( Ecef[2] );

}

double __fastcall
TPosVec::Gety
   (

   ) const
{

   if ( EcefDirty )
   {
      CalcEcef();
   }
   return( Ecef[1] );

}

double __fastcall
TPosVec::Getx
   (

   ) const
{
   if ( EcefDirty )
   {
      CalcEcef();
   }
   return( Ecef[0] );

}

double __fastcall
TPosVec::GetEcef
   (
   int Index
   ) const
{
   if ( EcefDirty )
   {
      CalcEcef();
   }
   return( Ecef[Index] );
}

void __fastcall
TPosVec::SetEcef
   (
   int    Index,
   double value
   )
{
   Ecef[Index] = value;
   GeoDirty    = true;
}


void
TPosVec::CalcGeo
   (

   ) const
{

#define MIN_ANGLE          ( 0.001745328 )
#define MIN_XYZ_DISTANCE    ( 1.0 )

   if ( Ecef.Mag < MIN_XYZ_DISTANCE )
   {
      FLat = 0.0;
      FLon = 0.0;
      FAlt = -SMA_AXIS;
      GeoDirty = false;
   }
   else
   {

      try
      {

         double eq_proj = Ecef[0]*Ecef[0] + Ecef[1]*Ecef[1];
         double b       = eq_proj/SMA_AXIS_2;
         double c       = (Ecef[2]*Ecef[2])/SMA_AXIS_2;
         double a0      = OMEGA_2*c;
         double a1      = 2.0*a0;
         double a2      = a0 + b - FIRST_E_4;
         double a3      = -2.0*FIRST_E_4;
         double a4      = -FIRST_E_4;


         double q = FIRST_E_2;
         for (int count = 0; count < 3; ++count)
         {
           double q_2 = q*q;
           double q_3 = q*q_2;
           q = q - (a0*q*q_3 + a1*q_3 + a2*q_2 + a3*q + a4)/
                   (4*a0*q_3 + 3*a1*q_2 + 2*a2*q + a3);
         }

         /*      Compute geodetic angles and altitude    */

         double q_plus_1 = q + 1.0;

           /*      Make sure we aren't too close to the poles      */

         if ( eq_proj < ( ( eq_proj + Ecef[2]*Ecef[2] )*MIN_ANGLE*MIN_ANGLE ) )
         {
           FLon = 0.0;     /* Near pole, set longitude to 0.0      */
         }
         else
         {
           FLon = atan2( Ecef[1], Ecef[0] );
         }
         FLat = atan2( ( q_plus_1*Ecef[2] ), sqrt( eq_proj ) );

         double radius = ( 1.0 - ( OMEGA_2/FIRST_E_2 )*q )*SMA_AXIS;

         FAlt = radius*( sqrt( b/( q_plus_1*q_plus_1 ) + c ) );
      }
      catch(...)
      {
         FLat = 0.0;
         FLon = 0.0;
         FAlt = -SMA_AXIS;
      }

      GeoDirty = false;
   }

}

void
TPosVec::CalcEcef
   (

   ) const
{
   double sin_lat = sin(FLat);
   double cos_lat = cos(FLat);
   double r       = SMA_AXIS / sqrt(1.0 - FIRST_E_2*sin_lat*sin_lat);

   Ecef[0]        = (r + FAlt)*cos_lat*cos(FLon);
   Ecef[1]        = (r + FAlt)*cos_lat*sin(FLon);
   Ecef[2]        = (r*(1.0 - FIRST_E_2) + FAlt)*sin_lat;

   EcefDirty = false;

}

TDcm
TPosVec::GetCen
   (
   ) const
{
   if ( GeoDirty )
   {
      CalcGeo( );
   }

   double clat = 0.0;
   double slat = 1.0;

   if ( Lat < PI/2.0 )
   {
      clat = cos( FLat );
      slat = sin( FLat );
   }

   const double clon = cos( FLon );
   const double slon = sin( FLon );

   TDcm CenLocal;

   CenLocal( 0, 0 ) = -clon*slat;
   CenLocal( 1, 0 ) = -slon;
   CenLocal( 2, 0 ) = -clon*clat;
   CenLocal( 0, 1 ) = -slon*slat;
   CenLocal( 1, 1 ) =  clon;
   CenLocal( 2, 1 ) = -slon*clat;
   CenLocal( 0, 2 ) =  clat;
   CenLocal( 1, 2 ) =  0.0;
   CenLocal( 2, 2 ) = -slat;

   return( CenLocal );

}

TDcm
TPosVec::GetCne
   (
   ) const
{
   TDcm CenLocal = GetCen();
   return( ~CenLocal );
}


TPosVec &
TPosVec::operator =
   (
   const double * const PosEcef
   )
{

   Ecef[0]   = PosEcef[0];
   Ecef[1]   = PosEcef[1];
   Ecef[2]   = PosEcef[2];

   GeoDirty  = true;
   EcefDirty = false;

   return(*this);

}

TPosVec::TPosVec
   (
   const double * const InPosEcef
   )
{
   ( *this ) = InPosEcef;
}

TPosVec &
TPosVec::operator =
   (
   const TVector & VectorEcef
   )
{

   Ecef[0]   = VectorEcef[0];
   Ecef[1]   = VectorEcef[1];
   Ecef[2]   = VectorEcef[2];

   GeoDirty  = true;
   EcefDirty = false;

   return( *this );

}

TPosVec::TPosVec
   (
   const TVector & VectorEcef
   )
{
   ( *this ) = VectorEcef;
}

TPosVec &
TPosVec::operator =
   (
   const TValArray & ValArrayEcef
   )
{

   Ecef[0]   = ValArrayEcef[0];
   Ecef[1]   = ValArrayEcef[1];
   Ecef[2]   = ValArrayEcef[2];

   GeoDirty  = true;
   EcefDirty = false;

   return( *this );

}

TPosVec::TPosVec
   (
   const TValArray & ValArrayEcef
   )
{
   ( *this ) = ValArrayEcef;
}

TPosVec::TPosVec
   (
   const TPosVec & Source
   )
{
   ( *this ) = Source;
}

TPosVec &
TPosVec::operator =
   (
   const TPosVec & Source
   )
{

   if ( this == & Source ) return( *this );

   Ecef      = Source.Ecef;
   FLon      = Source.FLon;
   FLat      = Source.FLat;
   FAlt      = Source.FAlt;
   EcefDirty = Source.EcefDirty;
   GeoDirty  = Source.GeoDirty;

   return( *this );

}






TPosVec::TPosVec
   (

   )
{
   Ecef[0] = 0.0;
   Ecef[1] = 0.0;
   Ecef[2] = 0.0;
   FLat    = 0.0;
   FLon    = 0.0;
   FAlt    = 0.0;

   GeoDirty  = true;

   EcefDirty = false;

//   CalcGeo();

}

