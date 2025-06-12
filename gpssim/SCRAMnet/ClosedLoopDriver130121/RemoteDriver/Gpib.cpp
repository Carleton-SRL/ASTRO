#include "pch.h"
#pragma hdrstop

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


#ifndef GpibH
#include "Gpib.h"
#endif

#ifndef ThreadInfH
#include "ThreadInf.h"
#endif

#ifndef GpibTimeoutH
#include "GpibTimeout.h"
#endif

#ifndef ScenTimeH
#include "ScenTime.h"
#endif

#include "ni488.h"

//---------------------------------------------------------------------------
// Debug Data
//
#ifndef DebugUtilsH
#include "DebugUtils.h"
using namespace DebugUtils;
#endif
//---------------------------------------------------------------------------
// Debug Data
//
#if(1)
static   TTimeInterval ExecuteInterval;
static   double        MinExecuteIntervalms = 10000.0;
static   double        MaxExecuteIntervalms = 0.0;
static   int           WaitRead             = 0;
static   int           WaitWrite            = 0;
static   int           WaitTimer            = 0;
static   int           WaitTimeout          = 0;
static   int           WaitAbandoned        = 0;
#endif


//---------------------------------------------------------------------------

static char ErrorMnemonic[21][5] =
{
   "EDVR", "ECIC", "ENOL", "EADR", "EARG", "ESAC", "EABO", "ENEB", "EDMA", "",
   "EOIP", "ECAP", "EFSO", ""    , "EBUS", "ESTB", "ESRQ", ""    , ""    , "",
   "ETAB"
};

static const int             MAX_GPIB_BYTES_TO_READ          = 1000;
static const int             GPIB_EXECUTE_TIMER_MS           = 50;
static const AnsiString      EventSendDataGpibName           = AnsiString( "TGpibSendDataEvent" );



//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TGpibThread
// Thread that does the actual GPIB communication.  Separate
// from the TRtMsgProcessor thread.
//
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

#if(0)
static int NumCallbacks = 0;
int __stdcall GpibThreadNotifyCallback
   (
   int                       LocalUd,
   int                       LocalIbsta,
   int                       LocalIberr,
   long                      LocalIbcntl,
   void                    * RefData
   )
{

   AnsiString Str;
//   if ( !( LocalIbsta & LACS ) || ( LocalIbsta & ERR ) )
//   {
      Str.sprintf( " NotifyCallback.  Ud = %d LocalIbsta = 0x%4.4X LocalIberr = 0x%4.4X LocalIbcntl = %d ", LocalUd, LocalIbsta, LocalIberr, LocalIbcntl );
      CodeSite->SendMsg( AnsiString( TScenTime::GetTimeMillisec() ) + Str );
//   }
   if ( ( ++NumCallbacks % 10 ) == 0 )
   {
      CodeSite->SendInteger( "NumCallbacks ", NumCallbacks );
   }

   TGpibThreadCallbackData * Data = (TGpibThreadCallbackData *) RefData;

   if ( !( LocalIbsta & ATN ) && ( LocalIbsta & LACS ) )
   {

      unsigned char ucData[MAX_GPIB_BYTES_TO_READ];

      ibrd( Data->BoardDev, ucData, MAX_GPIB_BYTES_TO_READ );
      int Count = ThreadIbcntl();

      if ( ThreadIbsta() & ERR )
      {
         AnsiString ErrStr;
         ErrStr.sprintf( " ibsta = 0x%x iberr = %d (%s)", ThreadIbsta(), ThreadIberr(), ErrorMnemonic[iberr] );
         CodeSite->SendMsg( AnsiString( "Callback ibrd error " ) + ErrStr );
      }
      else
      {
         TMsgData InData;
         for ( int i=0; i<Count; ++i )
         {
            InData.push_back( ucData[i] );
         }
         Data->ThreadDataCom->ReceivedData = InData;

      }
   }

   return( LACS );

}

#endif

TGpibThread::TGpibThread
   (
   const TGpibParams       & InGpibParams,
   TThreadDataCom          * InThreadDataCom
   ) :
   TThread( true ),
   GpibParams_( InGpibParams ),
   ValidInterface_( false ),
   StrCriticalSection( NULL ),
   Timeout_( T100ms ),
   RequestedService_( false ),
   ThreadDataCom_( InThreadDataCom )
{


   CodeSite->EnterMethod( "TGpibThread" );

   ValidInterface_                 = false;
   BoardIndex_                     = GpibParams_.BoardIndex;
   PrimaryAddress_                 = GpibParams_.PrimaryAddress;
   Timeout_                        = GpibParams_.Timeout;
   ControllerInCharge_             = GpibParams_.ControllerInCharge;


   AnsiString GpibBoardStr;
   GpibBoardStr.sprintf( "gpib%d", BoardIndex_ );

   CodeSite->SendMsg( AnsiString( "GpibBoardStr " ) + GpibBoardStr );

   StrCriticalSection              = new TCriticalSection();

   Board_                          = ibfind( GpibBoardStr.c_str() );

   if ( Board_ >= 0 )
   {

      CodeSite->SendMsg( GpibBoardStr + AnsiString( " board found. ") );

      ibconfig( Board, IbcCICPROT, ControllerInCharge_ );

      if ( ibsta & ERR )
      {

         CodeSite->SendInteger( AnsiString( "Unable to set CIC " ), ControllerInCharge_ );
         ValidInterface_           = false;

      }
      else
      {

         CodeSite->SendInteger( AnsiString( "Set CIC "),  ControllerInCharge_ );

         ValidInterface_           = true;

      }

      ibpad( Board, PrimaryAddress_ );

      if ( ibsta & ERR )
      {

         CodeSite->SendInteger( AnsiString( "Unable to set primary address " ), PrimaryAddress_ );
         ValidInterface_           = false;

      }
      else
      {

         CodeSite->SendInteger( AnsiString( "Primary address set "), PrimaryAddress_ );

         ValidInterface_           = true;

      }

   }
   else
   {

      CodeSite->SendMsg( AnsiString( "Unable to find board " ) + GpibBoardStr );
      ValidInterface_              = false;

   }

   ibtmo( Board, Timeout_ );

   if ( ThreadIbsta() & ERR )
   {

      CodeSite->SendInteger( AnsiString( "Unable to set timeout" ), Timeout_ );
      ValidInterface_              = false;

   }
   else
   {

      TGpibTimeout GpibTime( T100ms );
      CodeSite->SendMsg( AnsiString( "Timeout set to ") + GpibTime.GetTimeoutStr( Timeout ) );
      ValidInterface_              = true;

   }

   ibeot( Board, true );

   if ( ThreadIbsta() & ERR )
   {
      AnsiString ErrStr;
      ErrStr.sprintf( " ibsta = 0x%x iberr = %d (%s)", ThreadIbsta(), ThreadIberr(), ErrorMnemonic[iberr] );
      CodeSite->SendMsg( AnsiString( "TGpibThread unable to set ibeot" ) + ErrStr );
   }

   ibeos( Board, false );

   if ( ThreadIbsta() & ERR )
   {
      AnsiString ErrStr;
      ErrStr.sprintf( " ibsta = 0x%x iberr = %d (%s)", ThreadIbsta(), ThreadIberr(), ErrorMnemonic[iberr] );
      CodeSite->SendMsg( AnsiString( "TGpibThread unable to set ibeos" ) + ErrStr );
   }

#if(0)
   CallbackData.ThreadDataCom      = ThreadDataCom_;
   CallbackData.BoardDev           = Board;
   ibnotify( Board, LACS, GpibThreadNotifyCallback, ( void * ) &CallbackData );

   if ( ThreadIbsta() & ERR || ibsta & ERR )
   {
      AnsiString ErrStr;
      ErrStr.sprintf( " ibsta = 0x%x iberr = %d (%s)", ThreadIbsta(), ThreadIberr(), ErrorMnemonic[iberr] );
      CodeSite->SendMsg( AnsiString( "TGpibThread unable to set ibnotify" ) + ErrStr );
   }
#endif

   if ( ValidInterface_ )
   {

      CodeSite->SendMsg( csmNote, " GPIB Interface valid." );

   }
   else
   {

      CodeSite->SendMsg( csmError, " GPIB Interface failed." );

   }


   CodeSite->ExitMethod( "TGpibThread" );

}

AnsiString const
TGpibThread::GetStatusStr
   (
   )
{
   AnsiString Str;

   return( Str );

}

void
TGpibThread::SetStatusStr
   (
   const AnsiString        & /*NewStatusStr*/
   )
{
}

AnsiString const
TGpibThread::GetParametersStr
   (
   )
{

   AnsiString Str;
   StrCriticalSection->Acquire();
   Str = AnsiString( "Board Index : " ) + AnsiString( BoardIndex_ ) + AnsiString( "   PrimaryAddress : " ) + AnsiString( PrimaryAddress_ )
      + AnsiString( "  SecondaryAddress : " ) + AnsiString( SecondaryAddress_ );
   StrCriticalSection->Release();

   return( Str );

}

void
TGpibThread::SetParametersStr
   (
   const AnsiString        & /*NewParametersStr*/
   )
{
}

bool const
TGpibThread::InitCommunication
   (
   )
{
   return( true );
}



void __fastcall
TGpibThread::Execute
   (
   )
{

   TThreadInf TThreadInf( "GpibThread" );
   Priority = PriorityRtMsg;

   // DEBUG
   ExecuteInterval.ResetStart();

   while( !Terminated )
   {

      const TDataComWaitResults WaitResult  = ThreadDataCom_->WaitForWrite();

      WaitDebugProcessing( WaitResult );
      try
      {

         // There can be times that data is ready to be written out, but the remote controller wants to be serviced.
         // So continue in this loop until no more data needs to be written or give up.
         //
         bool      AllDataWritten  = false;
         int       NumRetries      = 0;
         const int MaxRetries      = 10;
         while( !Terminated && !AllDataWritten && ( NumRetries < MaxRetries ) )
         {

            TMsgData NewOutData = ThreadDataCom_->SendData;
            OutData_.insert( OutData_.end(), NewOutData.begin(), NewOutData.end() );
            if ( !Send( OutData_ ) )
            {
               AllDataWritten           = false;
               ++NumRetries;
            }
            else
            {
               OutData_.clear();
               AllDataWritten           = true;
            }

            TMsgData InData;
            Read( InData );

            if ( InData.size() )
            {
               ThreadDataCom_->ReceivedData = InData;
            }

         }

      }
      catch( const Exception & Exc )
      {
         AnsiString ExcStr     = AnsiString( "TGpibThread::Execute Exception caught.  " ) + Exc.Message;
         CodeSite->SendMsg( ExcStr );
         throw( Exception( ExcStr ) );
      }

   }

}


bool const
TGpibThread::Send
   (
   const TMsgData          & Data
   )
{

   if ( Data.empty() ) return( true );

   bool Sent = false;


   try
   {
      const int MaxSendAttempts = 10;
      int       SendTimes       = 0;

      while ( !Sent && ++SendTimes < MaxSendAttempts )
      {

         // Request Service
         //
         if ( !RequestedService_ )
         {

            ibrsv( Board, 0x40 );
            RequestedService_ = true;

            if ( ThreadIbsta() & ERR )
            {

               CodeSite->SendMsg( csmError, AnsiString( "ibrsv error. " ) );

            }

         }

         // Update ibsta
         //
         ibwait( Board, 0 );

         int LocalStatus = ThreadIbsta();

         // Talker
         //
         if ( !( LocalStatus & ATN ) && ( LocalStatus & TACS ) )
         {

            ibwrt( Board, (void *) &Data[0], Data.size() );
            if ( ThreadIbsta() & ERR )
            {
               AnsiString ErrStr;
               ErrStr.sprintf( " ibsta = 0x%x iberr = %d (%s)", ThreadIbsta(), ThreadIberr(), ErrorMnemonic[iberr] );
               CodeSite->SendMsg( AnsiString( "Error on ibwrt " ) + ErrStr );
            }
            else
            {
               Sent              = true;
               RequestedService_ = false;
            }

         }
      }
   }
   catch ( const Exception & Exc )
   {
      CodeSite->SendMsg( csmError, AnsiString( "TGpibThread::SendMsgData Exception caught. Exception message = " ) + Exc.Message );
   }

   return( Sent );

}

void
TGpibThread::Read
   (
   TMsgData                & MsgData
   )
{

   unsigned char Data[MAX_GPIB_BYTES_TO_READ];

   ibwait( Board, 0 );

   int LocalWaitIbsta = ThreadIbsta();

   // Listener
   //
   if ( !( LocalWaitIbsta & ATN ) && ( LocalWaitIbsta & LACS ) )
   {

      ibrd( Board, Data, MAX_GPIB_BYTES_TO_READ );

      const int LocalRdIbsta = ThreadIbsta();

      if ( LocalRdIbsta & ERR )
      {

         CodeSite->SendMsg( csmError, "ibrd error" );

      }

      const int Count = ThreadIbcntl();
      for ( int i=0; i<Count; ++i )
      {
         MsgData.push_back( Data[i] );
      }
      if ( Count ) //!= 5 )
      {
         CodeSite->SendInteger( AnsiString( TScenTime::GetTimeMillisec() ) + AnsiString( "TGpib::ReadMsg ibcntl " ), Count );
      }

   }

}

void
TGpibThread::WaitDebugProcessing
   (
   const TDataComWaitResults      WaitResults
   )
{
#if(0)
   if ( WaitResults.WaitTimeout )
   {
      CodeSite->WriteInteger( "WaitTimeout", ++WaitTimeout );
   }
   else if ( WaitResults.WaitAbandoned )
   {
      CodeSite->WriteInteger( "WaitAbandoned", ++WaitAbandoned );
      AnsiString Str( "WaitAbandoned. " );
      Str += WaitResults.ReadAbandoned  ? AnsiString( "ReadAbandoned " )  : AnsiString();
      Str += WaitResults.WriteAbandoned ? AnsiString( "WriteAbandoned " ) : AnsiString();
      Str += WaitResults.TimerAbandoned ? AnsiString( "TimerAbandoned " ) : AnsiString();
      CodeSite->SendMsg( Str );
   }
   else if ( WaitResults.WaitSignaled )
   {
      if ( WaitResults.ReadSignaled )
      {
         CodeSite->WriteInteger( "WaitRead", ++WaitRead );
      }
      if ( WaitResults.WriteSignaled )
      {
         CodeSite->WriteInteger( "WaitWrite", ++WaitWrite );
      }
      if ( WaitResults.TimerSignaled )
      {
         CodeSite->WriteInteger( "WaitTimer", ++WaitTimer );
      }
   }

   if ( TScenTime::GetTimeMillisec() > 1000 )
   {
      MinExecuteIntervalms = std::min( ExecuteInterval.TimeIntervalms, MinExecuteIntervalms );
      MaxExecuteIntervalms = std::max( ExecuteInterval.TimeIntervalms, MaxExecuteIntervalms );
   }
   CodeSite->WriteFloat( "ExecuteMinms", MinExecuteIntervalms );
   CodeSite->WriteFloat( "ExecuteMaxms", MaxExecuteIntervalms );
   ExecuteInterval.Reportms( "TGpibThreadExecutems" );
   ExecuteInterval.ResetStart();
#endif
}

__fastcall
TGpibThread::~TGpibThread
   (

   )
{

   ibonl( Board, 0 );
   delete StrCriticalSection;

}




