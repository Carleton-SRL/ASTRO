#ifndef VhTrthFlH
#define VhTrthFlH
//---------------------------------------------------------------------------
//
// $Workfile:: VhTrthFl.h                                            $
//
// $Revision:: 4                                                     $
//
// $History:: VhTrthFl.h                                             $
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

///////////////////////////////////////////////////////////////////////////////
//   VehTruthFile
// This object reads data from the TRUTHx.SCN file.  This file contains the
// NVDATA structure.  This object also will return a truth record matching
// a given GPS time, either through interpolation or extrapolotion.
///////////////////////////////////////////////////////////////////////////////



#ifndef VehTruthH
#include "VehTruth.h"
#endif

#pragma pack(push,1)


class TVehicleTruthFile : public TVehicleTruth {
private:

   const int                 VehNum;
   VehTruthRec               Current;
   VehTruthRec               Previous;
   VehTruthRec               First;
   VehTruthRec               Last;
   bifstream                 VehicleStream;
   bool                      DoInterpolation;

   bool                      GetTruthByInterpolation( const TGpsTime &ReqTime, VehTruthRec *Truth );
   bool                      GetTruthByExtrapolation( const TGpsTime &ReqTime, VehTruthRec *Truth );
   void                      CheckForWeekRollover( TGpsTime &Time );

public:

   TVehicleTruthFile( const int VehNum, bool DoInterpolation = false );
   TVehicleTruthFile( const AnsiString & Path, const int VehNum );

   void Init( const AnsiString & Filename );

   ~TVehicleTruthFile( );

   bool const         GetTruth( const TGpsTime & ReqTime, TVehTruthRec *Truth );

   TVehTruthRec const GetTruth( const TGpsTime & ReqTime );
//   TVehTruthRec const GetTruth();
   TVehTruthRec const GetFirst() { return( First ); }
   TVehTruthRec const GetLast()  { return( Last ); }

   void Reset();

};

typedef TVehicleTruthFile VehicleTruthFile;

#pragma pack(pop)

#endif





