#include "pch.h"
#pragma hdrstop

#include "ThreadDataCom.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// $Workfile:: ThreadDataCom.cpp                                     $
//
// $Revision:: 1                                                     $
//
// $History:: ThreadDataCom.cpp                                      $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 11/09/02   Time: 2:02p
//Created in $/RemoteDriver
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 11/01/02   Time: 12:25p
//Created in $/TapMsec
//
//
//---------------------------------------------------------------------------

static int Breakpt;
#pragma package(smart_init)

TThreadDataCom::TThreadDataCom
   (
   const int                 InReadTimerWaitIntervalMs,
   const int                 InWriteTimerWaitIntervalMs,
   const AnsiString        & InDebugOwnerStr
   ) :
   ReadTimer_( InReadTimerWaitIntervalMs ),
   WriteTimer_( InReadTimerWaitIntervalMs ),
   DebugOwnerStr( InDebugOwnerStr ),
   ReadEvent_( NULL ),
   WriteEvent_( NULL )
{

   ReadEvent_                = new TEvent( NULL, false, false, NULL );
   WriteEvent_               = new TEvent( NULL, false, false, NULL );

}

TThreadDataCom::~TThreadDataCom
   (
   )
{

   delete ReadEvent_;
   delete WriteEvent_;

}

void
TThreadDataCom::FillSyncObjects
   (
   const bool                WaitForRead,
   const bool                WaitForWrite,
   int                     & ReadSyncIndex,
   int                     & WriteSyncIndex,
   int                     & TimerSyncIndex,
   THandleArray            & SyncObjects
   )
{

   ReadSyncIndex                    = -1;
   WriteSyncIndex                   = -1;
   TimerSyncIndex                   = -1;

   SyncObjects.clear();

   if ( WaitForRead )
   {
      ReadSyncIndex                 = SyncObjects.size();
      SyncObjects.push_back( (void *) ReadEvent_->Handle );
      TimerSyncIndex                = SyncObjects.size();
      SyncObjects.push_back( ReadTimer_.hTimer );
   }

   if ( WaitForWrite )
   {
      WriteSyncIndex                = SyncObjects.size();
      SyncObjects.push_back( (void *) WriteEvent->Handle );
      TimerSyncIndex                = SyncObjects.size();
      SyncObjects.push_back( WriteTimer_.hTimer );
   }

}

void
TThreadDataCom::SetWriteEventName
   (
   const AnsiString        & InWriteEventName
   )
{

   WriteEventName_          = InWriteEventName;

   delete WriteEvent_;
   WriteEvent_              = new TEvent( NULL, false, false, WriteEventName_ );

}

AnsiString const
TThreadDataCom::GetWriteEventName
   (
   ) const
{
   return( WriteEventName_ );
}

void
TThreadDataCom::SetReadEventName
   (
   const AnsiString        & InReadEventName
   )
{

   ReadEventName_          = InReadEventName;

   delete ReadEvent_;
   ReadEvent_              = new TEvent( NULL, false, false, ReadEventName_ );

}

AnsiString const
TThreadDataCom::GetReadEventName
   (
   ) const
{
   return( ReadEventName_ );
}

TDataComWaitResults const
TThreadDataCom::Wait
   (
   const bool                WaitForRead,
   const bool                WaitForWrite
   )
{

   int                       ReadSyncIndex  = -1;
   int                       WriteSyncIndex = -1;
   int                       TimerSyncIndex = -1;
   THandleArray              SyncObjects;

   FillSyncObjects( WaitForRead, WaitForWrite, ReadSyncIndex, WriteSyncIndex, TimerSyncIndex, SyncObjects );

   const int WaitTimeout   = 2*std::max( ReadTimerMs, WriteTimerMs );
   const int WaitResult    = WaitForMultipleObjects( SyncObjects.size(), &( SyncObjects[0] ), FALSE, WaitTimeout );

   TDataComWaitResults WaitResults;
   WaitResults.ProcessWaitResults( WaitResult, SyncObjects.size(), ReadSyncIndex, WriteSyncIndex, TimerSyncIndex );

   return( WaitResults );

}

TDataComWaitResults const
TThreadDataCom::WaitForRead
   (
   )
{
   return( Wait( true, false ) );
}

TDataComWaitResults const
TThreadDataCom::WaitForWrite
   (
   )
{
   return( Wait( false, true ) );
}      

void
TThreadDataCom::ReportErrorStr
   (
   const AnsiString        & InErrorStr
   )
{
   CodeSite->SendMsg( csmError, AnsiString( "TThreadDataCom " ) + DebugOwnerStr + AnsiString( " " ) + InErrorStr );
}

void
TThreadDataCom::QueueReceivedData
   (
   const TMsgData          & MsgData
   )
{

   if ( MsgData.size() )
   {

      ReadData_.Data = MsgData;

      SignalReceivedData();

   }

}

TMsgData const
TThreadDataCom::GetReceivedData
   (
   )
{

   return( ReadData_.Data );

}

void
TThreadDataCom::QueueSendData
   (
   const TMsgData          & MsgData
   )
{

   if ( MsgData.size() )
   {

      WriteData_.Data = MsgData;

      SignalSendData();

   }

}

TMsgData const
TThreadDataCom::GetDataToSend
   (
   )
{
   return( WriteData_.Data );
}

inline void
TThreadDataCom::SignalSendData
   (
   )
{
   WriteEvent_->SetEvent();
}

inline void
TThreadDataCom::SignalReceivedData
   (
   )
{
   ReadEvent_->SetEvent();
}


