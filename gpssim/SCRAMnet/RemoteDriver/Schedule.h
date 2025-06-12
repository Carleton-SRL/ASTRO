//---------------------------------------------------------------------------

#ifndef ScheduleH
#define ScheduleH

using namespace std;

class TEventData {
public:
   TEvent *Event;
   int    PeriodMsec;
   int    StartTimeMsec;
   int    LastTimeSignaledMsec;
   AnsiString UserName;
   TEventData
      (
      TEvent *InEvent,
      const int InPeriodMsec,
      const int InStartTimeMsec,
      const int InLastTimeSignaledMsec,
      const AnsiString &InUserName
      ) :
      Event(InEvent),
      PeriodMsec(InPeriodMsec),
      StartTimeMsec(InStartTimeMsec),
      LastTimeSignaledMsec(InLastTimeSignaledMsec),
      UserName(InUserName)
   {}
//   TEventData(){};
   void SetEventData(TEvent *InEvent, const int InPeriodMsec, const int InStartTimeMsec, const int InLastTimeSignaledMsec)
   {
      Event                = InEvent;
      PeriodMsec           = InPeriodMsec;
      StartTimeMsec        = InStartTimeMsec;
      LastTimeSignaledMsec = InLastTimeSignaledMsec;
   }

};

typedef vector<TEventData> TEventArray;


class TSchedule {
private:

   TEvent                  * Event;
   int                       EventArrayIndex;
   AnsiString                EventName;
   void                      AddEvent( const int PeriodMsec, const int StartTimeMsec=0, const AnsiString &UserName="" );

public:

   TSchedule( const int PeriodMsec, const int StartTimeMsec=0, const AnsiString &UserName="" );
   ~TSchedule();

   TWaitResult               WaitFor();
   void                      SignalEvent();

   static void               SignalEvents( const int TimeMillisec );
   static void               SignalAllEvents();
   static void               Destroy();

   static TEventArray        Events;

};

class TScheduleSignal : public TThread {
private:

   HANDLE                    hTimer;

   void _fastcall            Execute();
   void                      SetupTimer();

   static bool               SimTimeReceived_;
   static LARGE_INTEGER      StartCount_;
   static LARGE_INTEGER      lFrequency_;
   static double             Frequency_;
   static int                RcvdSimTimeMillisec_;
   static int                CurTimeMillisec_;

public:

   TScheduleSignal();
   virtual _fastcall ~TScheduleSignal();

   static void               ResetStartCount( const int InSimTimeMillisec );
   static int const          GetTimeMillisec();

};

//---------------------------------------------------------------------------
#endif
