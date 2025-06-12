#ifndef NavDataH
#define NavDataH

//---------------------------------------------------------------------------
//
// $Workfile:: NavData.h                                             $
//
// $Revision:: 1                                                     $
//
// $History:: NavData.h                                              $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 9/03/02    Time: 7:21p
//Created in $/RemoteDriver
//
//
//---------------------------------------------------------------------------


// NavData.h;  Voyager Navigation Truth Data definition
//
// Defines the navigation data structure filled by the various user motion
// routines. NavData is used by the display funcions and utilities as
// read only.
// Only the user motion routines write to the NavData structure..

#pragma pack(push,1)

typedef struct {

   int           week;               // GPS week number
   double        time;               // seconds into GPS week
   double        EcefPos[3];         // always in meters
   double        EcefVel[3];         // always in m/s
   double        EcefAcc[3];         // always in m/s/s
   double        EcefJerk[3];        // always in m/s/s/s
   double        attitude[3];        // always in radians
   double        AngRate[3];         // always in r/s

} NVDATA;

#pragma pack(pop)
#endif
