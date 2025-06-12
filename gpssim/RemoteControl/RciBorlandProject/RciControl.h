//---------------------------------------------------------------------------

#ifndef RciControlH
#define RciControlH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
#include "Schedule.h"
#include "TapMsecRci.h"
#include "Gpib.h"
#include "TapRciPf.h"
#include "TapMsecPf.h"
#include "RciMsgs.h"
#include "VoyDefPf.h"
#include "UserQuery.h"


typedef TUserQuery<eRciSimMode>    TSimModeQuery;
typedef TUserQuery<TTapBitResults> TTapBitResultsQuery;
typedef TUserQuery<TChanStatArray> TChanStatQuery;
typedef TUserQuery<TSysCfg>        TSysCfgQuery;

typedef deque<TTapMsecCommand> TTapMsecCommandQueue;

class TRciControl : public TThread
{
private:
   TTapMsecStatMem      *TapMsecStatMem;
   TTapMsecStat         TapMsecStat;
   TInterface           *Interface;
   bool                 Valid;
   TSchedule            *Schedule;
   TScheduleSignal      *ScheduleSignal;
   int                  ExecutePeriod;
   double               UpdateDeltaTime;
   bool                 AckEvery;
   TTapRciProfile       *TapRciProfile;
   TTapMsecProfile      *TapMsecProfile;
   VoyDefProfile        *Vdp;
   AnsiString           RunsDir;
   eRciSimMode          SimMode;
   TOutMsgQueue         OutMsgQueue;
   TTapMsecCommandQueue TapMsecCommandQueue;
   TTapBitResults       TapBitResults;
   TChanStatArray       ChanStatArray;
   TSysCfg              SysCfg;

   // Queries
   TSimModeQuery        SimModeQuery;
   TTapBitResultsQuery  BitResultsQuery;
   TChanStatQuery       ChanStatQuery;
   TSysCfgQuery         SysCfgQuery;
   PROCESS_INFORMATION  TapMsecProcInfo;

   void RunStartScen( const AnsiString & ScenarioPath, const AnsiString & Parameters );
   eRciSimMode const GetCurrentSimMode();
   void ClearTapMsecProcInfo();
   void GetControlData();
   int  CurTimeMillisec;
protected:

   void __fastcall Execute();
   bool const InitializeInterface();
   void ProcessInputMsgs( TInMsgArray &InMsgArray, TOutMsgQueue &OutMsgs );
   void ProcessInputMsg( const TInMsg &InMsg, TOutMsgQueue &OutMsgs );
   void ProcessInitGeoMsg( const TInMsg &InMsg, TOutMsgQueue &OutMsgs );
   void ProcessStartScenMsg( const TInMsg &InMsg, TOutMsgQueue &OutMsgs );
   void ProcessStartLocalMsg( const TInMsg &InMsg, TOutMsgQueue &OutMsgs );
   void ProcessSetSvidMsg( const TInMsg &InMsg, TOutMsgQueue &OutMsgs );
   void ProcessSetPowerMsg( const TInMsg &InMsg, TOutMsgQueue &OutMsgs );
   void ProcessStopMsg( const TInMsg &InMsg, TOutMsgQueue &OutMsgs );
   void ProcessShutdownMsg( const TInMsg &InMsg, TOutMsgQueue &OutMsgs );
   void ProcessQueryMsg( const TInMsg &InMsg, TOutMsgQueue &OutMsgs );
   void ProcessUnknownMsg( const TInMsg &InMsg, TOutMsgQueue &OutMsgs );

   void SendCommandToTapMsec();
   void ProcessQueries(TOutMsgQueue & OutMsgs);
   void SendSimMode( TOutMsgQueue & OutMsgs );
   void SendChanStat( TOutMsgQueue & OutMsgs );
   void SendBitResults( TOutMsgQueue & OutMsgs );
   void SendSysCfg( TOutMsgQueue & OutMsgs );
   void PerformBit();
   void ReportErrorAndTerminate(const AnsiString & ErrorStr);
   void GetSysCfg();

public:

   __fastcall TRciControl();
   virtual __fastcall ~TRciControl();
   bool const IsValid() const { return( Valid ); }
   TTapMsecStat const GetCurrentTapMsecStat();
   TMsgTrafficArray const GetMsgTrafficArray();

};
//---------------------------------------------------------------------------
#endif
