#include "pch.h"
#pragma hdrstop

#include "Schedule.h"
#include "ScenTime.h"
#include "RemoteTypes.h"
#ifndef ThreadInfH
#include "ThreadInf.h"
#endif

//---------------------------------------------------------------------------

#pragma package(smart_init)

TEventArray TSchedule::Events;

static const char *EVENT_NAME = "TapMsecEvent";
static const int   EVENT_TIMEOUT = 100000;   // Timeout for events in millisecs

static bool ScheduleCritInitialized   = false;
static TCriticalSection *ScheduleCrit = NULL;

TIntArr SignalTimes;


TSchedule::TSchedule
   (
   const int                 PeriodMsec,
   const int                 StartTimeMsec,
   const AnsiString        & UserName
   ) :
   Event( NULL )
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
//---------------------------------------------------------------------------
// TScheduleSignal
//
bool               TScheduleSignal::SimTimeReceived_;
LARGE_INTEGER      TScheduleSignal::StartCount_;
LARGE_INTEGER      TScheduleSignal::lFrequency_;
double             TScheduleSignal::Frequency_;
int                TScheduleSignal::RcvdSimTimeMillisec_;
int                TScheduleSignal::CurTimeMillisec_;

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

   hTimer             = CreateWaitableTimer( NULL, FALSE, NULL );

   LARGE_INTEGER   liDueTime;
   liDueTime.LowPart  = (DWORD) ( 0 );
   liDueTime.HighPart = (LONG)  ( 0 );

   BOOL bSuccess =
   SetWaitableTimer
      (
           hTimer,                 // Handle to the timer object.
           &liDueTime,             // When timer will become signaled.
           1,                      // Periodic timer interval millisecs.
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

   TThreadInf TThreadInf( "TScheduleSignalThread" );
   SetThreadPriority( GetCurrentThread(),THREAD_PRIORITY_TIME_CRITICAL );

   QueryPerformanceFrequency( &lFrequency_ );
   Frequency_              = lFrequency_.QuadPart;

   while ( !Terminated )
   {

      DWORD WaitResult     = WaitForSingleObjectEx( hTimer, 100, FALSE );

      if ( WaitResult != WAIT_OBJECT_0 )
      {
         CodeSite->SendInteger( "TScheduleSignal::Execute error. WaitResult ", WaitResult );
      }
      if ( Terminated )
      {
         break;
      }


      CurTimeMillisec_ = GetTimeMillisec();

      if ( SimTimeReceived_ )
      {

         TSchedule::SignalEvents( CurTimeMillisec_ );

      }

   }

}

int const
TScheduleSignal::GetTimeMillisec
   (
   )
{

   if ( SimTimeReceived_ )
   {
      LARGE_INTEGER CurCount;
      QueryPerformanceCounter( &CurCount);

      const double DeltaTime        = ( CurCount.QuadPart - StartCount_.QuadPart )/Frequency_;
      CurTimeMillisec_              = NINT( DeltaTime * 1000.0 ) + RcvdSimTimeMillisec_;
      TScenTime::SetTimeMillisec( CurTimeMillisec_ );
   }
   else
   {
      CurTimeMillisec_ = 0;
   }

   return( CurTimeMillisec_ );

}

void
TScheduleSignal::ResetStartCount
   (
   const int                 InSimTimeMillisec
   )
{

   QueryPerformanceCounter( &StartCount_ );
   RcvdSimTimeMillisec_ = 0;
   SimTimeReceived_     = true;

}




