#ifndef ClosedLoopMemH
#define ClosedLoopMemH

#ifdef __BORLANDC__
#pragma pack(push,1)
#endif

//---------------------------------------------------------------------------
//
// $Workfile:: ClosedLoopMem.h                                       $
//
// $Revision:: 2                                                     $
//
// $History:: ClosedLoopMem.h                                        $
//
//*****************  Version 2  *****************
//User: Michael Wade Date: 11/14/03   Time: 11:48a
//Updated in $/TapMsec
//Modify for shared memory.
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 1/20/03    Time: 9:26p
//Created in $/TapMsec
//SCRAMNet
//
//
//---------------------------------------------------------------------------

#define RTSHAREDMEMNAME "RTSHAREDMEMNAME"

namespace ClosedLoopMem
{

static const int             MaxChannels = 16;


typedef enum { eSimModeIdle=1, eSimModeArmed=2, eSimModeRunning=3 } eSimMode;

// TclVehicleState
//   Vehicle State
// PosEcef        - Vehicle position in ECEF in m
// VelEcef        - Vehicle velocity in ECEF in m/s
// AccEcef        - Vehicle acceleration in ECEF in m/s/s
// JrkEcef        - Vehicle jerk in Ecef in m/s/s/s
// Att            - Vehicle attitude Euler angles: Roll, Pitch and Heading in radians
// AngRate        - Vehicle attitude rate.  Time rate of change of att in rad/s
//

typedef struct {

   double                    PosEcef[3];
   double                    VelEcef[3];
   double                    AccEcef[3];
   double                    JrkEcef[3];
   double                    Att[3];
   double                    AngRate[3];

} TclVehicleState;

// TclGpsTime
//   GPS Time
// Week                    - GPS week number
// Seconds                 - GPS seconds into week
//

typedef struct {

   int                       Week;
   double                    Seconds;

} TclGpsTime;

typedef struct {

   TclGpsTime                GpsTime;
   TclVehicleState           VehicleState;

} TclTimeVehicleState;

typedef struct {

   int                       Which;
   TclTimeVehicleState       State1;
   TclTimeVehicleState       State2;

} TclTimeVehicleStateMem;

typedef struct {

   bool                      Valid;
   TclTimeVehicleState       InitialVehicleState;

} TclInitialization;

typedef struct {

   bool                      NewData;
   int                       SvOverride[MaxChannels];

} TclSvOverride;

typedef struct {

   bool                      NewData;
   double                    Atten[MaxChannels];

} TclAttenOverride;

typedef struct {

   bool                      NewData;
   double                    Power[MaxChannels];

} TclPowerOverride;

typedef struct {

   bool                      Stop;

} TclStop;

typedef struct {

   bool                      NewData;
   TclInitialization         Initialization;
   TclTimeVehicleStateMem    TimeVehicleStateMem;
   TclSvOverride             SvOverride;
   TclAttenOverride          AttenOverride;
   TclPowerOverride          PowerOverride;
   TclStop                   Stop;

} TclExtToSimMem;

// From the simulator to the external motion generator
//

typedef struct {

   int                       Svid;
   double                    Range;
   double                    RangeRate;
   double                    RangeAcc;
   double                    RangeJrk;
   double                    Clock;
   double                    El;
   double                    Az;
   double                    Atten;
   double                    Tropo;
   double                    L1Iono;
   double                    L2Iono;
   double                    Sa;
   double                    Uere;
   double                    IntRamp;
   double                    SwMpRange;
   double                    SwMpRate;
   double                    EarthRotation;

} TclSvRec;

typedef struct {

   TclGpsTime                GpsTime;
   TclSvRec                  SvRec[MaxChannels];

} TclTimeSvRec;

typedef struct {

   int                       Which;
   TclTimeSvRec              TimeSvRec1;
   TclTimeSvRec              TimeSvRec2;

} TclTimeSvRecMem;

typedef struct {

   int                       Svid;
   double                    Atten;                 // db
   double                    Power;                 // dbm
   double                    Az;                    // deg
   double                    El;                    // deg

} TclChannelStatus;

typedef struct {

   TclGpsTime                GpsTime;
   TclChannelStatus          ChannelStatus[MaxChannels];

} TclTimeChannelStatus;

typedef struct {

   int                       Which;
   TclTimeChannelStatus      TimeChannelStatus1;
   TclTimeChannelStatus      TimeChannelStatus2;

} TclTimeChannelStatusMem;

typedef struct {

   eSimMode                  SimMode;               //
   int                       NumChannels;           // Number of actual channels in simulator

} TclSimulatorConfig;

typedef struct {

   int                       TimeMillisec;
   TGpsTime                  GpsTime;

} TclCurTime;

typedef struct {

   int                       Which;
   TclCurTime                Time1;
   TclCurTime                Time2;

} TclCurTimeMem;

typedef struct {

   TclSimulatorConfig        SimConfig;
   TclCurTimeMem             CurTime;
   TclTimeVehicleStateMem    TimeVehicleStateMem;
   TclTimeSvRecMem           TimeSvRecMem;
   TclTimeChannelStatusMem   TimeChannelStatusMem;

} TclSimToExtMem;

typedef struct tagTclMem {

   TclExtToSimMem            ExtToSimMem;
   TclSimToExtMem            SimToExtMem;

} TclMem, *pTclMem;

};

#ifdef __BORLANDC__
#pragma pack(pop)
#endif


#endif

