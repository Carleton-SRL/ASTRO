//---------------------------------------------------------------------------

#ifndef ThreadDataComH
#define ThreadDataComH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// $Workfile:: ThreadDataCom.h                                       $
//
// $Revision:: 1                                                     $
//
// $History:: ThreadDataCom.h                                        $
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

#ifndef RemoteTypesH
#include "RemoteTypes.h"
#endif

class TProtectedMsgData {
private:

   TMsgData                  Data_;
   TCriticalSection        * CriticalSection_;

   int const                 GetDataSize()
   {
      CriticalSection_->Acquire();
      const int RetSize = (int) Data_.size();
      CriticalSection_->Release();
      return( RetSize );
   }


public:

   TProtectedMsgData()
   {
      CriticalSection_     = new TCriticalSection();
   }

   ~TProtectedMsgData()
   {
      delete CriticalSection_;
   }

   void AddData( const TMsgData & InData )
   {
      CriticalSection_->Acquire();
      if ( Data_.empty() )
      {
         Data_ = InData;
      }
      else
      {
         Data_.insert( Data_.end(), InData.begin(), InData.end() );
      }
      CriticalSection_->Release();
   }

   TMsgData const GetData()
   {
      CriticalSection_->Acquire();
      TMsgData OutData = Data_;
      Data_.clear();
      CriticalSection_->Release();
      return( OutData );
   }

   __property TMsgData  Data    = { read = GetData, write = AddData            };
   __property int       Size    = { read = GetDataSize                         };

};



class TDataComWaitResults {
private:

   bool                      ReadSignaled_;
   bool                      WriteSignaled_;
   bool                      TimerSignaled_;
   bool                      ReadAbandoned_;
   bool                      WriteAbandoned_;
   bool                      TimerAbandoned_;
   bool                      WaitTimeout_;

   bool const                GetWaitAbandoned() const { return( ReadAbandoned_ || WriteAbandoned_ || TimerAbandoned_ ); }
   bool const                GetWaitSignaled()  const { return( ReadSignaled_ || WriteSignaled_ || TimerSignaled_ ); }

public:

   TDataComWaitResults() : ReadSignaled_( false ), WriteSignaled_( false ), TimerSignaled_( false ), ReadAbandoned_( false ), WriteAbandoned_( false ), TimerAbandoned_( false ), WaitTimeout_( false ) {}

   void                      ProcessWaitResults( const int WaitResult, const int NumSyncObjects, const int ReadIndex, const int WriteIndex, const int TimerIndex )
   {

      ReadSignaled_   = false;
      ReadSignaled_   = false;
      TimerSignaled_  = false;

      ReadAbandoned_  = false;
      WriteAbandoned_ = false;
      TimerAbandoned_ = false;

      WaitTimeout_    = false;

      if ( WaitResult == WAIT_TIMEOUT )
      {
         WaitTimeout_ = true;
      }
      else if ( ( WaitResult >= WAIT_ABANDONED_0 ) && ( WaitResult <= (int) ( WAIT_ABANDONED_0 + NumSyncObjects - 1 ) ) )
      {

         const int WaitAbandonedIndex = WaitResult - WAIT_ABANDONED_0;

         ReadAbandoned_               = ( WaitAbandonedIndex == ReadIndex );
         WriteAbandoned_              = ( WaitAbandonedIndex == WriteIndex );
         TimerAbandoned_              = ( WaitAbandonedIndex == TimerIndex );

      }
      else if ( ( WaitResult >= WAIT_OBJECT_0 ) && ( WaitResult <= (int) ( WAIT_OBJECT_0 + NumSyncObjects - 1 ) ) )
      {

         const int WaitSignaledIndex = WaitResult - WAIT_OBJECT_0;

         ReadSignaled_               = ( WaitSignaledIndex == ReadIndex );
         WriteSignaled_              = ( WaitSignaledIndex == WriteIndex );
         TimerSignaled_              = ( WaitSignaledIndex == TimerIndex );

      }

   }

   __property bool ReadSignaled   = { read = ReadSignaled_       };
   __property bool WriteSignaled  = { read = WriteSignaled_      };
   __property bool TimerSignaled  = { read = TimerSignaled_      };
   __property bool ReadAbandoned  = { read = ReadAbandoned_      };
   __property bool WriteAbandoned = { read = WriteAbandoned_     };
   __property bool TimerAbandoned = { read = TimerAbandoned_     };
   __property bool WaitTimeout    = { read = WaitTimeout_        };
   __property bool WaitAbandoned  = { read = GetWaitAbandoned    };
   __property bool WaitSignaled   = { read = GetWaitSignaled     };

};

class TWaitableTimer {
private:

   HANDLE                    hTimer_;
   int                       TimerWaitIntervalMs_;

   void                      SetupWaitableTimer()
   {

      hTimer_                 = CreateWaitableTimer( NULL, FALSE,  NULL );

      LARGE_INTEGER   liDueTime;
      liDueTime.LowPart       = (DWORD) ( 0 );
      liDueTime.HighPart      = (LONG)  ( 0 );

      SetWaitableTimer
      (
         hTimer_,                                             // Handle to the timer object.
         &liDueTime,                                          // When timer will become signaled.
         TimerWaitIntervalMs_,                                // Periodic timer interval millisecs.
         NULL,                                                // Completion routine.
         NULL,                                                // Argument to the completion routine.
         FALSE                                                // Do not restore a suspended system.
      );

   }

   TWaitableTimer & operator=( const TWaitableTimer & );
   TWaitableTimer( const TWaitableTimer & );

public:

   TWaitableTimer( const int InTimerWaitIntervalMs ) : TimerWaitIntervalMs_( InTimerWaitIntervalMs )
   {
      SetupWaitableTimer();
   }

   ~TWaitableTimer()
   {
      CloseHandle( hTimer_ );
   }

   __property HANDLE hTimer           = { read = hTimer_              };
   __property int    TimerIntervalMs  = { read = TimerWaitIntervalMs_ };

};



class TThreadDataCom {
private:

   TProtectedMsgData         ReadData_;
   TProtectedMsgData         WriteData_;
   TEvent                  * ReadEvent_;
   TEvent                  * WriteEvent_;
   TWaitableTimer            ReadTimer_;
   TWaitableTimer            WriteTimer_;
   AnsiString                ReadEventName_;
   AnsiString                WriteEventName_;

   // Debug
   AnsiString                DebugOwnerStr;

   void                      FillSyncObjects( const bool WaitForRead, const bool WaitForWrite, int & ReadSyncIndex, int & WriteSyncIndex, int & TimerSyncIndex, THandleArray & SyncObjects );
   void                      ReportErrorStr( const AnsiString & ErrorStr );

   AnsiString const          GetReadEventName() const;
   void                      SetReadEventName( const AnsiString & InReadEventName );
   AnsiString const          GetWriteEventName() const;
   void                      SetWriteEventName( const AnsiString & InWriteEventName );
   TEvent *                  GetReadEvent() { return( ReadEvent_ ); }
   TEvent *                  GetWriteEvent() { return( WriteEvent_ ); }
   TDataComWaitResults const Wait( const bool InWaitForRead, const bool InWaitForWrite );
   int const                 GetReadTimerMs()  const { return( ReadTimer_.TimerIntervalMs );  }
   int const                 GetWriteTimerMs() const { return( WriteTimer_.TimerIntervalMs ); }
   int const                 GetUnsentDataSize() { return( WriteData_.Size ); }

public:

   TThreadDataCom( const int InReadTimerWaitIntervalMs = 1000, const int InWriteTimerWaitIntervalMs = 1000, const AnsiString & InDebugOwnerStr = "" );
   ~TThreadDataCom();


   TDataComWaitResults const WaitForRead();
   TDataComWaitResults const WaitForWrite();

   void                      QueueSendData( const TMsgData & DataToSend );
   void                      QueueReceivedData( const TMsgData & NewReceivedData );

   TMsgData const            GetReceivedData();
   TMsgData const            GetDataToSend();

   void                      SignalReceivedData();
   void                      SignalSendData();


   __property TMsgData   ReceivedData     = { read = GetReceivedData,  write = QueueReceivedData      };
   __property TMsgData   SendData         = { read = GetDataToSend,    write = QueueSendData          };
   __property TEvent   * ReadEvent        = { read = GetReadEvent,                                    };
   __property TEvent   * WriteEvent       = { read = GetWriteEvent,                                   };
   __property AnsiString ReadEventName    = { read = GetReadEventName,  write = SetReadEventName      };
   __property AnsiString WriteEventName   = { read = GetWriteEventName, write = SetWriteEventName     };
   __property int        ReadTimerMs      = { read = GetReadTimerMs                                   };
   __property int        WriteTimerMs     = { read = GetWriteTimerMs                                  };
   __property int        UnsentDataSize   = { read = GetUnsentDataSize                                };

};

#endif
