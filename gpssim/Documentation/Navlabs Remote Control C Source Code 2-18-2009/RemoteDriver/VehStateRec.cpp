#include "pch.h"
#pragma hdrstop

#ifndef VehStateRecH
#include "VehStateRec.h"
#endif

#ifndef VehTruthH
#include "VehTruth.h"
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

TVehStateRec::TVehStateRec
   (
   const TVehTruthRec & Source
   )
{
   ( *this ) = Source;
}   


TVehStateRec &
TVehStateRec::operator =
   (
   const TVehTruthRec & TruthRec
   )
{

   week             = TruthRec.GpsTime.Week;
   time             = TruthRec.GpsTime.Seconds;
   for ( int i=0; i<3; ++i )
   {
      EcefPos[i]    = TruthRec.PosEcef[i];
      EcefVel[i]    = TruthRec.VelEcef[i];
      EcefAcc[i]    = TruthRec.AccEcef[i];
      EcefJerk[i]   = TruthRec.JerkEcef[i];
      attitude[i]   = TruthRec.Attitude[i];
      AngRate[i]    = TruthRec.AngRate[i];
   }

   return( *this );

}

