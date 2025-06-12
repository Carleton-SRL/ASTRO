#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
// ClassExplorer Pro generated source file
// Created by Michael Wade on 2/3/2002, 5:57:09 PM
//---------------------------------------------------------------------------
#include "Interface.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
bool TInterface::IntCriticalSectionInitialized    = false;
TCriticalSection * TInterface::IntCriticalSection = NULL;

static const int INTERFACE_PERIOD_MSEC            = 500;
static const int MaxMsgsRcvdNoStat                = 50;

TInterface::TInterface
   (
   ) :
   ValidInterface( false ),
   IntError( false ),
   TThread( true ),
   NumMsgsSent( 0 ),
   NumMsgsRcvd( 0 ),
   NumMsgsRcvdExceptStat( 0 )
{
   if ( !IntCriticalSectionInitialized )
   {
      InitializeCriticalSection();
      IntCriticalSectionInitialized = true;
   }

   Schedule = new TSchedule( INTERFACE_PERIOD_MSEC, 0, "TINTERFACE" );

   ScheduleSignal = new TScheduleSignal();
   ScheduleSignal->Resume();

}

void
TInterface::InitializeCriticalSection
   (
   )
{

   if ( !IntCriticalSectionInitialized )
   {
      IntCriticalSection            = new TCriticalSection();
      IntCriticalSectionInitialized = true;
   }

}


__fastcall
TInterface::~TInterface
   (

   )
{

   delete Schedule;

   ScheduleSignal->Terminate();
   ScheduleSignal->WaitFor();
   delete ScheduleSignal;

   delete IntCriticalSection;

   IntCriticalSection            = NULL;

   IntCriticalSectionInitialized = false;

}

void _fastcall
TInterface::Execute()
{

//   SetPriorityClass(GetCurrentProcess(),REALTIME_PRIORITY_CLASS);
//   SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_ABOVE_NORMAL);

   while ( !Terminated && IsValidInterface() )
   {

      TWaitResult WaitResult = Schedule->WaitFor();
      if ( WaitResult != wrSignaled )
      {
         break;
      }
      if ( Terminated ) break;

//      CodeSite->SendInteger( "TInterface::Execute at ", TScheduleSignal::GetCurTimeMillisec() );

      IntCriticalSection->Enter();

      if ( !OutMsgQueue.empty() )
      {

         ProcessOutputMsg();

      }

      ReadMsg( RcvdData );

      while ( !RcvdData.empty() )
      {

         InMsg.ProcessData( RcvdData );

         if ( InMsg.IsMsgComplete() )
         {

            CodeSite->SendMsg( AnsiString( "TInterface::Execute InMsg.Complete MsgId " ) + InMsg.GetMsgId() );

            MsgTrafficArray.push_back( TMsgTraffic( TScheduleSignal::GetCurTimeMillisec(), InMsg.GetMsgData(), eMSG_SOURCE_SIM ) );
            IncNumMsgsRcvd( InMsg );
            InMsgArray.push_back( InMsg );
            InMsg.Clear();

         }

      }

      IntCriticalSection->Leave();

   }

}

static const int MaxSendAttempts = 4;
void
TInterface::ProcessOutputMsg
   (
   )
{

   AnsiString OutMsgId  = OutMsgQueue.front().GetMsgId();

   int SendTimes = 0;
   bool Sent     = false;

   while ( !Sent && SendTimes < MaxSendAttempts )
   {
      if ( SendMsg( OutMsgQueue.front().GetMsgData() ) )
      {
         ++SendTimes;
         ClearIntError();
      }
      else
      {
         Sent = true;
      }
   }

   if ( Sent )
   {

      MsgTrafficArray.push_back( TMsgTraffic( TScheduleSignal::GetCurTimeMillisec(), OutMsgQueue.front().GetMsgStr(), eMSG_SOURCE_CTLR ) );
      OutMsgQueue.pop();

      ++NumMsgsSent;

   }
   else
   {
      CodeSite->SendMsg( AnsiString( "TInterface::ProcessOutputMsg Error sending msg " ) + OutMsgId );
   }

   if ( IsIntError() )
   {
      CodeSite->SendMsg( "ProcessOutputMsg - Clearing IntError" );
      ClearIntError();
   }
}

void
TInterface::QueueMsgs
   (
   TOutMsgQueue & OutQ
   )
{
   IntCriticalSection->Enter();

   while( OutQ.size() )
   {
      OutMsgQueue.push( OutQ.front() );
      OutQ.pop();
   }

   IntCriticalSection->Leave();

}

TMsgTrafficArray const
TInterface::GetMsgTrafficArray
   (
   )
{

   IntCriticalSection->Enter();

   TMsgTrafficArray NewMsgTrafficArray = MsgTrafficArray;
   MsgTrafficArray.clear();

   IntCriticalSection->Leave();

   return( NewMsgTrafficArray );

}

void
TInterface::IncNumMsgsRcvd
   (
   const TInMsg &Msg
   )
{
   ++NumMsgsRcvd;
}

void
TInterface::GetInputMsgs
   (
   TInMsgArray &OutInMsgArray
   )
{

   IntCriticalSection->Enter();

   OutInMsgArray = InMsgArray;
   InMsgArray.clear();

   IntCriticalSection->Leave();
}
int const
TInterface::GetOutputQueueSize
   (
   ) const
{
   return( (int) OutMsgQueue.size() );
}   

