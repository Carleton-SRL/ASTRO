#ifndef VehStateRecH
#define VehStateRecH

//---------------------------------------------------------------------------
//
// $Workfile:: VehStateRec.h                                         $
//
// $Revision:: 2                                                     $
//
// $History:: VehStateRec.h                                          $
//
//*****************  Version 2  *****************
//User: Michael Wade Date: 7/28/02    Time: 2:42p
//Updated in $/TapMsec
//Original
//Renamed from NavData.h.  Contains the record definition of the
//Truthx.scn files produced by WinVpg
//
//
//---------------------------------------------------------------------------


// Record in the Truthx.scn (Truth1.scn)

#pragma pack(push,1)

class TVehTruthRec;

class TVehStateRec
{
public:

   int                       week;           // GPS week number
   double                    time;           // seconds into GPS week
   double                    EcefPos[3];     // always in meters
   double                    EcefVel[3];     // always in m/s
   double                    EcefAcc[3];     // always in m/s/s
   double                    EcefJerk[3];    // always in m/s/s/s
   double                    attitude[3];    // always in radians
   double                    AngRate[3];     // always in r/s

   TVehStateRec() {}
   
   TVehStateRec & operator=( const TVehTruthRec & );

   TVehStateRec( const TVehTruthRec & );

   friend bifstream & operator >> ( bifstream & In, TVehStateRec & Rec )
   {
      In.Read( &Rec, sizeof( Rec ) );
      return( In );
   }

   friend bofstream & operator << ( bofstream & Out, TVehStateRec & Rec )
   {
      Out.Write( &Rec, sizeof( Rec ) );
      return( Out );
   }

};

#pragma pack(pop)

#endif
