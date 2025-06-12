#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------

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

#ifndef DcmH
#include "Dcm.h"
#endif

//---------------------------------------------------------------------------

#pragma package(smart_init)


#if(1)

TDcm const
TDcm::Rotx
   (
   const double     Anglex
   )
{

   TDcm Rot;

   const double Sinx = sin( Anglex );
   const double Cosx = cos( Anglex );

   Rot( 0, 0 ) = 1.0;
   Rot( 0, 1 ) = 0.0;
   Rot( 0, 2 ) = 0.0;

   Rot( 1, 0 ) = 0.0;
   Rot( 1, 1 ) = Cosx;
   Rot( 1, 2 ) = Sinx;

   Rot( 2, 0 ) = 0.0;
   Rot( 2, 1 ) = -Sinx;
   Rot( 2, 2 ) = Cosx;

   return( Rot );

}

TDcm const
TDcm::Roty
   (
   const double     Angley
   )
{

   TDcm Rot;

   const double Siny = sin( Angley );
   const double Cosy = cos( Angley );

   Rot( 0, 0 ) = Cosy;
   Rot( 0, 1 ) = 0.0;
   Rot( 0, 2 ) = -Siny;

   Rot( 1, 0 ) = 0.0;
   Rot( 1, 1 ) = 1.0;
   Rot( 1, 2 ) = 0.0;

   Rot( 2, 0 ) = Siny;
   Rot( 2, 1 ) = 0.0;
   Rot( 2, 2 ) = Cosy;

   return( Rot );

}

TDcm const
TDcm::Rotz
   (
   const double     Anglez
   )
{

   TDcm Rot;

   const double Sinz = sin( Anglez );
   const double Cosz = cos( Anglez );

   Rot( 0, 0 ) = Cosz;
   Rot( 0, 1 ) = Sinz;
   Rot( 0, 2 ) = 0.0;

   Rot( 1, 0 ) = -Sinz;
   Rot( 1, 1 ) = Cosz;
   Rot( 1, 2 ) = 0.0;

   Rot( 2, 0 ) = 0.0;
   Rot( 2, 1 ) = 0.0;
   Rot( 2, 2 ) = 1.0;

   return( Rot );

}

#else
TDcm const
TDcm::Rotx
   (
   const double     Anglex
   )
{

   TDcm Rot;

   const double Sinx = sin( Anglex );
   const double Cosx = cos( Anglex );

   Rot( 0, 0 ) = 1.0;
   Rot( 0, 1 ) = 0.0;
   Rot( 0, 2 ) = 0.0;

   Rot( 1, 0 ) = 0.0;
   Rot( 1, 1 ) = Cosx;
   Rot( 1, 2 ) = Sinx;

   Rot( 2, 0 ) = 0.0;
   Rot( 2, 1 ) = -Sinx;
   Rot( 2, 2 ) = Cosx;

   return( Rot );

}

TDcm const
TDcm::Roty
   (
   const double     Angley
   )
{

   TDcm Rot;

   const double Siny = sin( Angley );
   const double Cosy = cos( Angley );

   Rot( 0, 0 ) = Cosy;
   Rot( 0, 1 ) = 0.0;
   Rot( 0, 2 ) = -Siny;

   Rot( 1, 0 ) = 0.0;
   Rot( 1, 1 ) = 1.0;
   Rot( 1, 2 ) = 0.0;

   Rot( 2, 0 ) = Siny;
   Rot( 2, 1 ) = 0.0;
   Rot( 2, 2 ) = Cosy;

   return( Rot );

}

TDcm const
TDcm::Rotz
   (
   const double     Anglez
   )
{

   TDcm Rot;

   const double Sinz = sin( Anglez );
   const double Cosz = cos( Anglez );

   Rot( 0, 0 ) = Cosz;
   Rot( 0, 1 ) = Sinz;
   Rot( 0, 2 ) = 0.0;

   Rot( 1, 0 ) = -Sinz;
   Rot( 1, 1 ) = Cosz;
   Rot( 1, 2 ) = 0.0;

   Rot( 2, 0 ) = 0.0;
   Rot( 2, 1 ) = 0.0;
   Rot( 2, 2 ) = 1.0;

   return( Rot );

}

#endif


