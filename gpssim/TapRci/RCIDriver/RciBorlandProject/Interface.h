//---------------------------------------------------------------------------
// ClassExplorer Pro generated header file
// Created by Michael Wade on 2/3/2002, 5:57:09 PM
//---------------------------------------------------------------------------
#ifndef InterfaceH
#define InterfaceH

#include "RemoteTypes.h"
#include "InterfaceOptions.h"
#include "InMsg.h"
#include "OutMsg.h"
#include "Schedule.h"

typedef enum { eMSG_SOURCE_SIM, eMSG_SOURCE_CTLR } eMSG_SOURCE;
class TMsgTraffic {
private:
   AnsiString  MsgStr;
   int         TimeMillisec;
   eMSG_SOURCE MsgSource;
public:
   TMsgTraffic() : TimeMillisec( 0 ), MsgSource( eMSG_SOURCE_SIM ) {}
   TMsgTraffic( const int InTimeMillisec, const AnsiString &InMsgStr, const eMSG_SOURCE InMsgSource ) :
      TimeMillisec( InTimeMillisec ), MsgStr( InMsgStr ), MsgSource( InMsgSource ) {}
   AnsiString const GetMsgStr()  const { return( MsgStr ); }
   int const GetTimeMillisec()   const { return( TimeMillisec ); }
   eMSG_SOURCE const GetSource() const { return( MsgSource ); }
};

typedef vector<TMsgTraffic> TMsgTrafficArray;
//---------------------------------------------------------------------------
class TInterface : public TThread {
private:
   TOutMsgQueue            OutMsgQueue;
   TMsgTrafficArray        MsgTrafficArray;

   TInMsg                  InMsg;
   TInMsgArray             InMsgArray;

   TMsgData                RcvdData;

   TSchedule               *Schedule;

   int                     NumMsgsSent;
   int                     NumMsgsRcvd;
   int                     NumMsgsRcvdExceptStat;


   // Pure virtual implemented by derived classes (TGpib, etc)
   //
   virtual bool const SendMsg(const TMsgData & Data) = 0;
   virtual void ReadMsg(TMsgData & Data) = 0;

   static TCriticalSection *IntCriticalSection;
   static bool              IntCriticalSectionInitialized;
   static void InitializeCriticalSection();
protected:
   bool ValidInterface;
   bool IntError;
   TScheduleSignal *ScheduleSignal;
   bool const IsIntError() const { return( IntError ); }
   void ClearIntError() { IntError = false; }
   void _fastcall Execute();
   void ProcessReadMsgData( const TMsgData &MsgData );
   void ProcessOutputMsg();
   void IncNumMsgsRcvd( const TInMsg & );
public:

   TInterface( );
   virtual __fastcall ~TInterface();
   bool const IsValidInterface() const { return( ValidInterface ); }

   TMsgTrafficArray const GetMsgTrafficArray();
   void QueueMsgs( TOutMsgQueue & OutQueue );

   int const GetNumMsgsSent() const { return( NumMsgsSent ); }
   int const GetNumMsgsRcvd() const { return( NumMsgsRcvd ); }
   int const GetNumMsgsRcvdExceptStat() const { return( NumMsgsRcvdExceptStat ); }
   void GetInputMsgs( TInMsgArray &InMsgArray );
   int const GetOutputQueueSize() const;

};

//---------------------------------------------------------------------------
#endif
