#ifndef StelMsgsH
#define StelMsgsH

#ifndef RemoteTypesH
#include "RemoteTypes.h"
#endif

#ifndef InMsgH
#include "InMsg.h"
#endif

#ifndef VehTruthH
#include "VehTruth.h"
#endif

// Input from simulator message id's
//
static const int StelCurTimeMsgId        = 0xfe;
static const int StelCurStatMsgId        = 0xfd;
static const int StelCalParamsMsgId      = 0xfc;
static const int StelSVLookAngleMsgId    = 0xfb;
static const int StelDataExtractionMsgId = 0xf9;
static const int StelMsgRcptStatMsgId    = 0xf8;
static const int StelEphDataMsgId        = 0xf7;
static const int StelAlmParamsMsgId      = 0xf6;
static const int StelPhaseLockMsgId      = 0xf5;

static const int StelNumSimMsgs          = 9;
typedef struct
{
   int MsgId;
   char *Desc;
} TStelMsgIdDesc;

static const TStelMsgIdDesc StelSimMsgIdDesc[StelNumSimMsgs] =
{
   { StelCurTimeMsgId,        "CurTime" },
   { StelCurStatMsgId,        "CurStat" },
   { StelCalParamsMsgId,      "CalParams" },
   { StelSVLookAngleMsgId,    "SVLookAngle" },
   { StelDataExtractionMsgId, "DataExt" },
   { StelMsgRcptStatMsgId,    "MsgStat" },
   { StelEphDataMsgId,        "EphData" },
   { StelAlmParamsMsgId,      "AlmParams" },
   { StelPhaseLockMsgId,      "PhaseLock" }
};

// Output from controller message id's
//
static const unsigned char StelSetTimeMsgId                  = 0;
static const unsigned char StelInitSimMsgId                  = 1;
static const unsigned char StelChannelModeMsgId              = 2;
static const unsigned char StelCalInterChannelBiasesMsgId    = 3;
static const unsigned char StelSetChannelPowerMsgId          = 5;
static const unsigned char StelRangeMaintenanceMsgId         = 6;
static const unsigned char StelEphDataInputMsgId             = 7;
static const unsigned char StelAlmParamsInputMsgId           = 8;
static const unsigned char StelPowerProfileMsgId             = 10;
static const unsigned char StelTrajectoryProfileMsgId        = 11;
static const unsigned char StelStatusReqMsgId                = 13;
static const unsigned char StelTimeReqMsgId                  = 16;
static const unsigned char StelEphDataReqMsgId               = 17;
static const unsigned char StelDataExtractionReqMsgId        = 19;
static const unsigned char StelAlmParamsReqMsgId             = 20;
static const unsigned char StelCalParamsInputMsgId           = 21;
static const unsigned char StelStopSimulationMsgId           = 22;
static const unsigned char StelEphemerisCorruptionInputMsgId = 23;
static const unsigned char StelClockCorruptionInputMsgId     = 24;
static const unsigned char StelPseudorangeNoiseParamsMsgId   = 25;
static const unsigned char StelTroposphericModelParamsMsgId  = 26;
static const unsigned char StelUMGSimulationStartMsgId       = 27;
static const unsigned char StelPlatformAttitudeMsgId         = 28;
static const unsigned char StelAntennaGainPatternMsgId       = 30;
static const unsigned char StelAircraftMaskingTableMsgId     = 31;
static const unsigned char StelInitializeSystemMsgId         = 41;
static const unsigned char StelResetChannelInterfaceMsgId    = 42;
static const unsigned char StelCalChanControllersMsgId       = 43;
static const unsigned char StelPhaseLockStatusReqMsgId       = 44;
static const unsigned char StelCalParamsReqMsgId             = 46;
static const unsigned char StelSatelliteUseMapMsgId          = 47;
static const unsigned char StelFullInitializationMsgId       = 48;
static const unsigned char StelSubframeModificationMsgId     = 49;
static const unsigned char StelSetWeekNumberMsgId            = 50;
static const unsigned char StelChannelAssignmentMsgId        = 51;

static const int StelNumCtlrMsgs = 35;

static const TStelMsgIdDesc StelCtlrMsgIdDesc[StelNumCtlrMsgs] =
{
   { StelSetTimeMsgId,                    "SetTime" },
   { StelInitSimMsgId,                    "InitSim" },
   { StelChannelModeMsgId,                "ChanMode" },
   { StelCalInterChannelBiasesMsgId,      "CalInterChannelBiases" },
   { StelSetChannelPowerMsgId,            "SetChannelPower" },
   { StelRangeMaintenanceMsgId,           "RangeMaintenance" },
   { StelEphDataInputMsgId,               "EphDataInput"},
   { StelAlmParamsInputMsgId,             "AlmParamsInput"},
   { StelPowerProfileMsgId,               "PowerProfile"},
   { StelTrajectoryProfileMsgId,          "TrajProfile"},
   { StelStatusReqMsgId,                  "StatusReq"},
   { StelTimeReqMsgId,                    "TimeReq"},
   { StelEphDataReqMsgId,                 "EphDataReq"},
   { StelDataExtractionReqMsgId,          "DataExtReq"},
   { StelAlmParamsReqMsgId,               "AlmParamsReq"},
   { StelCalParamsInputMsgId,             "CalParamsInp"},
   { StelStopSimulationMsgId,             "StopSim"},
   { StelEphemerisCorruptionInputMsgId,   "EphCorrupt"},
   { StelClockCorruptionInputMsgId,       "ClkCorrupt"},
   { StelPseudorangeNoiseParamsMsgId,     "PseudoRangeNoise"},
   { StelTroposphericModelParamsMsgId,    "TropoModel"},
   { StelUMGSimulationStartMsgId,         "UMGSimStart"},
   { StelPlatformAttitudeMsgId,           "PlatAttitude"},
   { StelAntennaGainPatternMsgId,         "AntGain"},
   { StelAircraftMaskingTableMsgId,       "AirMask"},
   { StelInitializeSystemMsgId,           "InitSys"},
   { StelResetChannelInterfaceMsgId,      "ResetChan"},
   { StelCalChanControllersMsgId,         "CalChanCtlrs"},
   { StelPhaseLockStatusReqMsgId,         "PhaseLockStat"},
   { StelCalParamsReqMsgId,               "CalParamsReq"},
   { StelSatelliteUseMapMsgId,            "SatUseMap"},
   { StelFullInitializationMsgId,         "FullInit"},
   { StelSubframeModificationMsgId,       "SubframeMod"},
   { StelSetWeekNumberMsgId,              "SetWeek"},
   { StelChannelAssignmentMsgId,          "ChanAssign"}
};

// Input Messages to Sim Controller
//

// 0xFE
// Simulation Time

class TStelTimeMsg {
private:

   int                       TimeMillisec_;

public:

   TStelTimeMsg( const TInMsg & InMsec );
   TStelTimeMsg & operator=( const TInMsg & InMsg );

   __property int      TimeMillisec = { read = TimeMillisec_    };

};

// 0xFB
// SV Look Angle
//
class TStelSvLookAngle {
private:
   TSvLookAngleArray SvLookAngleArray;
   int               CurSystemTime;
   bool              NewEph;

   static double const ScaleEl( unsigned char UnScaledEl );
   static double const ScaleAz( unsigned char UnScaledAz );
public:
   TStelSvLookAngle( const TInMsg & );
   TStelSvLookAngle & operator=( const TInMsg & );
   TSvLookAngleArray const GetSvLookAngleArray() const { return( SvLookAngleArray ); }
   int const GetCurSystemTime() const { return( CurSystemTime ); }
   bool const GetNewEph() const { return( NewEph ); }
};

// 0xF8
// Message Reception Status Message
//
class TStelMsgRcptnStatMsg {
private:
   unsigned char   RcvdMsgId;
   unsigned char   Status;
public:
   TStelMsgRcptnStatMsg();
   TStelMsgRcptnStatMsg( const TInMsg &InMsg );
   TStelMsgRcptnStatMsg & operator=( const TInMsg &InMsg );
   unsigned char const GetRcvdMsgId() const { return( RcvdMsgId ); }
   bool const IsMsgChecksumValid() const;
   bool const IsResourceOwnershipValid() const;
   bool const IsSimulationModeValid() const;
   bool const IsMsgIdValid() const;
   bool const IsMsgSizeValid() const;
};


// Output Messages to Simulator
//

class TStelOut {
protected:

   TMsgBody                  MsgBody;
   unsigned char             MsgId;

public:

   TMsgBody const            GetMsgBody() const { return( MsgBody ); }
   unsigned char const       GetMsgId()   const { return( MsgId ); }

};

// 1
// Initialize Simulation
//
static const           int SizeInitSimBody  = 19;

class TStelInitSim : public TStelOut {

private:

   TVehTruthRec  Init;

public:

   TStelInitSim( const TVehTruthRec &InVehTruthRec );
   TStelInitSim & operator=( const TVehTruthRec &InVehTruthRec );

};

// 2
//
// CodeControl
//   From STel interface
//   0  0  0  0  0  c  c  c
//                  |  |  |
//                  |  |  - Data on/off
//                  |  ---- Code on/off
//                  ------- Carrier on/off

class TStelCodeControl {
private:

   unsigned char             Control_;

   unsigned char const       GetControl() const                             { return( Control_ ); }
   void                      SetControl( const unsigned char InControl )    { Control_ = InControl; }
   bool const                GetDataOn()    const                           { return( Control_ & 0x01 ); }
   void                      SetDataOn( const bool InDataOn )               { Control_ |= 0x01; }
   bool const                GetCodeOn()    const                           { return( Control_ & 0x02 ); }
   void                      SetCodeOn( const bool InCodeOn )               { Control_ |= 0x02; }
   bool const                GetCarrierOn() const                           { return( Control_ & 0x04 ); }
   void                      SetCarrierOn( const bool InCarrierOn )         { Control_ |= 0x04; }

public:

   TStelCodeControl( unsigned char InControl=0 ) : Control_( InControl ) {}
   ~TStelCodeControl() {}

   __property bool          DataOn         = { read = GetDataOn,       write = SetDataOn        };
   __property bool          CodeOn         = { read = GetCodeOn,       write = SetCodeOn        };
   __property bool          CarrierOn      = { read = GetCarrierOn,    write = SetCarrierOn     };
   __property unsigned char Control        = { read = GetControl,      write = SetControl       };

};

// Clock Control
//   From STel interface
//   0  0  0  0  0  0  c  c
//                     |  |
//                     |  - 0 = Normal, 1 = Clock/2, 2=Clock/4
//                     ---- "

class TStelClockControl {
private:

   unsigned char             Control_;

   bool const                GetNormal()       const { return( Control_ == 0 ); }
   bool const                GetClockHalf()    const { return( Control_ == 1 ); }
   bool const                GetClockQuarter() const { return( Control_ == 2 ); }

   unsigned char const       GetControl()     const { return( Control_ ); }

   void                      SetNormal( const bool InNormal )             { Control_ = InNormal       ? 0 : Control_; }
   void                      SetClockHalf( const bool InClockHalf )       { Control_ = InClockHalf    ? 1 : Control_; }
   void                      SetClockQuarter( const bool InClockQuarter ) { Control_ = InClockQuarter ? 2 : Control_; }

   void                      SetControl( const unsigned char InControl )  { Control_ = InControl; }

public:

   TStelClockControl( unsigned char InControl = 0 ) : Control_( InControl ) {}

   __property unsigned char Control       = { read = GetControl,      write = SetControl        };
   __property bool          Normal        = { read = GetNormal,       write = SetNormal         };
   __property bool          ClockHalf     = { read = GetClockHalf,    write = SetClockHalf      };
   __property bool          ClockQuarter  = { read = GetClockQuarter, write = SetClockQuarter   };

};

// PRN Index Control
//   From STel interface
//   0  0  0  0  0  0  0  c
//                        |
//                        - Index Control on/off
//                          ( 0 = off, 1 = on )

class TStelPRNIndexControl {
private:

   unsigned char             Control_;

   bool const                GetIndexOn() const { return( Control_ & 0x01 ); }
   void                      SetIndexOn( const bool InIndexOn ) { Control_ = InIndexOn ? 1 : 0; }

   unsigned char const       GetControl() const { return( Control_ ); }
   void                      SetControl( const unsigned char InControl ) { Control_ = InControl; }

public:

   TStelPRNIndexControl(unsigned char InControl=0) : Control( InControl ) {}

   __property unsigned char Control        = { read = GetControl,     write = SetControl       };
   __property bool          IndexOn        = { read = GetIndexOn,     write = SetIndexOn       };

};

class TStelFreqControl {
private:

   TStelCodeControl          CACodeControl_;
   TStelCodeControl          PCodeControl_;
   TStelClockControl         ClockControl_;
   TStelPRNIndexControl      PRNIndexControl_;

public:

   TStelFreqControl() {};

   __property TStelCodeControl     CACodeControl     = { read = CACodeControl_,    write = CACodeControl_      };
   __property TStelCodeControl     PCodeControl      = { read = PCodeControl_,     write = PCodeControl_       };
   __property TStelPRNIndexControl PRNIndexControl   = { read = PRNIndexControl_,  write = PRNIndexControl_    };
   __property TStelClockControl    ClockControl      = { read = ClockControl_,     write = ClockControl_       };

};

class TStelChannelMode : public TStelOut {
private:

   int                       Chan_;
   TStelFreqControl          L1Control_;
   TStelFreqControl          L2Control_;

public:

   TStelChannelMode( const int InChan, const TStelFreqControl & InL1Control, const TStelFreqControl & InL2Control );

};
// 11
// Trajectory Message
//
static const           int SizeTrajectoryBody  = 40;

class TStelTrajectory : public TStelOut {

private:

   TVehTruthRec  Truth;

public:

   TStelTrajectory( const TVehTruthRec &InVehTruthRec );
   TStelTrajectory & operator=( const TVehTruthRec &InVehTruthRec );

};

// 19
// Data Extraction Message
//
class TStelDataExtractionReq : public TStelOut {

private:

public:

   TStelDataExtractionReq( const bool InDataExtractionEnabled );


};

// 22
// Stop Message
//
class TStelStop : public TStelOut {

private:

public:

   TStelStop();

};

// 51
// Channel Assignment
//

class TStelChanAssignFunc {
private:

   bool                      DeassignChanA_;
   bool                      SwapChanAChanB_;
   bool                      ChanASvidAssign_;

   bool const                GetDeassignChanA() const { return( DeassignChanA_ ); }
   void                      SetDeassignChanA( const bool InDeassignChanA )
   {
      DeassignChanA_     = InDeassignChanA;
      SwapChanAChanB_    = InDeassignChanA ? false : SwapChanAChanB_;
      ChanASvidAssign_   = InDeassignChanA ? false : ChanASvidAssign_;
   }

   bool const                GetSwapChanAChanB() const { return( SwapChanAChanB_ ); }
   void                      SetSwapChanAChanB( const bool InSwapChanAChanB )
   {
      SwapChanAChanB_     = InSwapChanAChanB;
      DeassignChanA_      = InSwapChanAChanB ? false : DeassignChanA_;
      ChanASvidAssign_    = InSwapChanAChanB ? false : ChanASvidAssign_;
   }

   bool const                GetChanASvidAssign() const { return( ChanASvidAssign_ ); }
   void                      SetChanASvidAssign( const bool InChanASvidAssign )
   {
      ChanASvidAssign_    = InChanASvidAssign;
      SwapChanAChanB_     = InChanASvidAssign ? false : SwapChanAChanB_;
      DeassignChanA_      = InChanASvidAssign ? false : DeassignChanA_;
   }

public:

   TStelChanAssignFunc() : DeassignChanA_( false ), SwapChanAChanB_( false ), ChanASvidAssign_( false ) {}

   __property bool     DeassignChanA       = { read = GetDeassignChanA,     write = SetDeassignChanA       };
   __property bool     SwapChanAChanB      = { read = GetSwapChanAChanB,    write = SetSwapChanAChanB      };
   __property bool     ChanASvidAssign     = { read = GetChanASvidAssign,   write = SetChanASvidAssign     };

};   

class TStelChanAssignData {
private:


   TStelChanAssignFunc       ChanAssignFunc_;
   int                       ChanA_;
   int                       ChanB_;
   int                       Svid_;

public:

   TStelChanAssignData( const TStelChanAssignFunc InChanAssignFunc = TStelChanAssignFunc(), const int InChanA = 0, const int InChanB = 0, const int InSvid = 0 ) :
      ChanAssignFunc_( InChanAssignFunc ),  ChanA_( InChanA ), ChanB_( InChanB ), Svid_( InSvid )
   {}

   TStelChanAssignData( const TStelChanAssignData & Source )
   {
      ( *this ) = Source;
   }

   TStelChanAssignData & operator=( const TStelChanAssignData & rhs )
   {
      if ( this == & rhs ) return ( *this );

      ChanAssignFunc_     = rhs.ChanAssignFunc_;
      ChanA_              = rhs.ChanA_;
      ChanB_              = rhs.ChanB_;
      Svid_               = rhs.Svid_;

      return( *this );

   }

   __property TStelChanAssignFunc ChanAssignFunc        = { read = ChanAssignFunc_,     write = ChanAssignFunc_     };
   __property int                 ChanA                 = { read = ChanA_,              write = ChanA_              };
   __property int                 ChanB                 = { read = ChanB_,              write = ChanB_              };
   __property int                 Svid                  = { read = Svid_,               write = Svid_               };

};

static const           int SizeChanAssignBody  = 3;
class TStelChannelAssignment : public TStelOut {
private:

   TStelChanAssignData       ChanAssignData_;

public:

   TStelChannelAssignment( const TStelChanAssignData & InChanAssignData );
   TStelChannelAssignment & operator=( const TStelChanAssignData & InChanAssignData );

};


typedef std::map<int,AnsiString> TStelMsgDescMap;


#endif
