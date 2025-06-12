#ifndef CLControlH
#define CLControlH

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




#ifndef VhTrthFlH
#include "VhTrthFl.h"
#endif

#ifndef ClosedLoopSimTypeH
#include "ClosedLoopSimType.h"
#endif

#ifndef ScheduleH
#include "Schedule.h"
#endif

#ifndef StelMsgsH
#include "StelMsgs.h"
#endif

#ifndef InterfaceH
#include "Interface.h"
#endif

#ifndef RemoteDriverPfH
#include "RemoteDriverPf.h"
#endif

#ifndef ThreadDataComH
#include "ThreadDataCom.h"
#endif

#ifndef MsgTrafficH
#include "MsgTraffic.h"
#endif

//---------------------------------------------------------------------------
class TCLControl : public TThread  {
private:

   TVehicleTruthFile       * VehTruthFile;
   TScheduleSignal         * ScheduleSignal;
   TClosedLoopSimType        ClosedLoopSimType;
   TInterface              * Interface_;
   TInMsg                    InMsg;

   TVehTruthRec              FirstTruth_;
   TVehTruthRec              LastTruth_;
   TVehTruthRec              CurTruth_;

   TGpsTime                  CurTime;
   TGpsTime                  FirstTime;
   TGpsTime                  LastTime;
   int                       UpdateIndex;
   int                       TrajectoryDeltaTimeMillisec;
   TIntOptions             * IntOptions;
   TGpibOptions              GpibOptions;
   TEthernetOptions          EthernetOptions;
   bool                      SendStop;
   bool                      StopSent_;
   bool                      StopQueued;
   TRemoteDriverPf         * RemoteDriverPf;
   int                       NumMsgsSent_;
   int                       NumMsgsRcvd_;
   int                       NumMsgsRcvdExceptStat_;
   TMsgTrafficArray          MsgTrafficArray_;
   TInMsgArray               InMsgArray_;
   TCriticalSection        * MsgCriticalSection_;
   int                       LastTrajectoryTimeMillisec;

   void _fastcall            Execute();
   TStelTrajectory const     GetTrajectory();
   bool const                InitializeInterface();
   void                      ReadMsgData();
   void                      ProcessInMsg( const TInMsg & );
   bool const                ShouldSendTrajectory();
   TGpsTime const            GetUpdateTime();
   void                      SendMsg( const TOutMsg & );
   void                      SendMsgData( const TMsgData & );
   void                      SendMsgs( TOutMsgQ & );

   TInMsgArray const         GetInputMsgs();
   TMsgTrafficArray const    GetMsgTrafficArray();
   TVehTruthRec const        GetCurTruth() const { return( CurTruth_ ); }
   AnsiString const          GetInterfaceStatusStr() { return( Interface_ ? Interface_->StatusStr : AnsiString() ); }

public:
   virtual __fastcall ~TCLControl();
   TCLControl( const TClosedLoopSimType &ClosedLoopSimType );

   void                      TerminateSim();
   void                      ProcessTimeMsg( const int TimeMillisec );
   void                      Send1Traj();
   void                      InitializeSim();

   __property bool             StopSent                 = { read = StopSent_                    };
   __property int              NumMsgsSent              = { read = NumMsgsSent_                 };
   __property int              NumMsgsRcvd              = { read = NumMsgsRcvd_                 };
   __property int              NumMsgsRcvdExceptStat    = { read = NumMsgsRcvdExceptStat_       };
   __property TInMsgArray      InMsgArray               = { read = GetInputMsgs                 };
   __property TMsgTrafficArray MsgTrafficArray          = { read = GetMsgTrafficArray           };
   __property TVehTruthRec     CurTruth                 = { read = GetCurTruth                  };
   __property AnsiString       InterfaceStatusStr       = { read = GetInterfaceStatusStr        };
   __property TInterface     * Interface                = { read = Interface_                   };

};

//---------------------------------------------------------------------------
#endif
