#include "pch.h"
#pragma hdrstop

#include "Schedule.h"
//#include "ScenTime.h"
#include "RemoteTypes.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TEventArray TSchedule::Events;

static const char *EVENT_NAME = "TapRciEvent";
static const int   EVENT_TIMEOUT = 1000;   // Timeout for events in millisecs

static bool ScheduleCritInitialized   = false;
static TCriticalSection *ScheduleCrit = NULL;

int TScheduleSignal::CurTimeMillisec;

TIntArr SignalTimes;


TSchedule::TSchedule
   (
   const int PeriodMsec,
   const int StartTimeMsec,
   const AnsiString &UserName
   ) :
   Event(NULL)
{
   if ( !ScheduleCritInitialized )
   {
      ScheduleCrit            = new TCriticalSection();
      ScheduleCritInitialized = true;
   }
   AddEvent( PeriodMsec, StartTimeMsec, UserName );
}

TSchedule::~TSchedule()
{
   ScheduleCrit->Enter();


   TEventArray::iterator i;
   for ( i=Events.begin(); i<Events.end(); ++i )
   {
      if ( i->UserName == EventName )
      {
         Events.erase( i );
         break;
      }
   }
   delete Event;

   ScheduleCrit->Leave();

   if ( Events.empty() )
   {
      delete ScheduleCrit;
   }
}

void
TSchedule::AddEvent
   (
   const int         PeriodMsec,
   const int         StartTimeMsec,
   const AnsiString &UserName
   )
{

   ScheduleCrit->Enter();


   if ( UserName.Length() )
   {
      EventName = UserName + Events.size();
   }
   else
   {
      EventName = AnsiString(EVENT_NAME) + Events.size();
   }

   Event        = new TEvent( NULL, false, false, EventName );

   TEventData NewEvent( Event, PeriodMsec, StartTimeMsec, StartTimeMsec-PeriodMsec, EventName );

   EventArrayIndex = Events.size();
   Events.push_back( NewEvent );

   ScheduleCrit->Leave();

}

TWaitResult
TSchedule::WaitFor
   (
   )
{
   return(Event->WaitFor(EVENT_TIMEOUT));
}



void
TSchedule::SignalEvents
   (
   const int CurTime
   )
{

   if ( !ScheduleCritInitialized )
   {
      ScheduleCrit            = new TCriticalSection();
      ScheduleCritInitialized = true;
   }

   ScheduleCrit->Enter();
   for ( unsigned int i=0; i<Events.size(); ++i )
   {

      TEventData &CurEvent = Events[i];

      if ( CurTime >= CurEvent.LastTimeSignaledMsec + CurEvent.PeriodMsec )
      {

         CurEvent.LastTimeSignaledMsec += CurEvent.PeriodMsec;
         CurEvent.Event->SetEvent();

      }

   }
   ScheduleCrit->Leave();

}

void
TSchedule::SignalAllEvents
   (
   )
{
   if ( !ScheduleCritInitialized )
   {
      ScheduleCrit            = new TCriticalSection();
      ScheduleCritInitialized = true;
   }
   ScheduleCrit->Enter();
   for ( unsigned int i=0; i<Events.size(); ++i )
   {

      Events[i].Event->SetEvent();

   }
   ScheduleCrit->Leave();
}


void
TSchedule::SignalEvent()
{
   Event->SetEvent();
}


TScheduleSignal::TScheduleSignal
   (
   ) :
   TThread( true )
{

   SetupTimer();

}

void
TScheduleSignal::SetupTimer
   (

   )
{

   hTimer = CreateWaitableTimer( NULL, FALSE, "RCIDRIVERTIMER" );

   __int64         qwDueTime;
   qwDueTime = -5;

   // Copy the relative time into a LARGE_INTEGER.
   LARGE_INTEGER   liDueTime;
   liDueTime.LowPart  = (DWORD) ( qwDueTime & 0xFFFFFFFF );
   liDueTime.HighPart = (LONG)  ( qwDueTime >> 32 );

   BOOL bSuccess =
   SetWaitableTimer
      (
           hTimer,                 // Handle to the timer object.
           &liDueTime,             // When timer will become signaled.
           10,                     // Periodic timer interval millisecs.
           NULL,                   // Completion routine.
           NULL,                   // Argument to the completion routine.
           FALSE                   // Do not restore a suspended system.
      );
  if ( !bSuccess )
  {
     CodeSite->SendMsg( "Error setting waitable timer." );
  }

}
_fastcall
TScheduleSignal::~TScheduleSignal()
{
   CancelWaitableTimer( hTimer );
   CloseHandle( hTimer );
}

void _fastcall
TScheduleSignal::Execute
   (
   )
{

   SetPriorityClass( GetCurrentProcess(),REALTIME_PRIORITY_CLASS );
   SetThreadPriority( GetCurrentThread(),THREAD_PRIORITY_TIME_CRITICAL );

   LARGE_INTEGER  lFrequency;
   LARGE_INTEGER  Count2,Count1;
   double Frequency;

   QueryPerformanceFrequency( &lFrequency );
   Frequency = lFrequency.QuadPart;

   LARGE_INTEGER StartCount;
   QueryPerformanceCounter( &StartCount);

   while ( !Terminated )
   {

      DWORD WaitResult = WaitForSingleObjectEx( hTimer, 1000, FALSE );

      if ( WaitResult != WAIT_OBJECT_0 )
      {
         CodeSite->SendInteger( "TScheduleSignal::Execute error. WaitResult ", WaitResult );
      }
      if ( Terminated )
      {
         break;
      }


      LARGE_INTEGER CurCount;
      QueryPerformanceCounter( &CurCount);

      double DeltaTime = ( CurCount.QuadPart - StartCount.QuadPart )/Frequency;
      CurTimeMillisec = NINT( DeltaTime * 1000.0 );
//      TScenTime::SetTimeMillisec( CurTimeMillisec );

      TSchedule::SignalEvents( CurTimeMillisec );

   }

}




