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
   TEvent *Event;
   void AddEvent(const int PeriodMsec, const int StartTimeMsec=0, const AnsiString &UserName="");
   int EventArrayIndex;
   AnsiString EventName;
public:
   TSchedule(const int PeriodMsec,const int StartTimeMsec=0, const AnsiString &UserName="");
   ~TSchedule();

   TWaitResult WaitFor();

   void SignalEvent();

   static void SignalEvents(const int TimeMillisec);
   static void SignalAllEvents();
   static void Destroy();

   static TEventArray Events;

};

class TScheduleSignal : public TThread {
private:

   HANDLE                  hTimer;


   void _fastcall Execute();
   void SetupTimer();
   static int CurTimeMillisec;
public:
   TScheduleSignal();
   virtual _fastcall ~TScheduleSignal();

   static int const GetCurTimeMillisec() { return( CurTimeMillisec ); }

};

//---------------------------------------------------------------------------
#endif
