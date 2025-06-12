#include "pch.h"
#pragma hdrstop

//---------------------------------------------------------------------------
//
// $Workfile:: Ethernet.cpp                                          $
//
// $Revision:: 1                                                     $
//
// $History:: Ethernet.cpp                                           $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 10/09/02   Time: 11:13a
//Created in $/TapMsec
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 10/03/02   Time: 8:27p
//Created in $/TapMsec
//Add ethernet
//
//
//---------------------------------------------------------------------------


#ifndef EthernetH
#include "Ethernet.h"
#endif

#ifndef OutMsgH
#include "OutMsg.h"
#endif

#ifndef ThreadInfH
#include "ThreadInf.h"
#endif

#ifndef ERemoteDriverExceptionH
#include "ERemoteDriverException.h"
#endif

#ifndef ScenTimeH
#include "ScenTime.h"
#endif

#ifndef DebugUtilsH
#include "DebugUtils.h"
using namespace DebugUtils;
#endif

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
// Constants
//
static const int             SOCKET_TIMEOUT_MSECS            = 10;
static const int             SOCKET_WAIT_TIMEOUT_MSECS       = 10;
static const int             MAX_WRITE_ATTEMPTS              = 4;
static const int             MAX_ETHERNET_BYTES_TO_READ      = 1000;
static const int             SOCKET_INIT_SLEEP_MSECS         = 100;
static const int             ETHERNETCLIENT_EXECUTE_TIMER_MS = 10;

//---------------------------------------------------------------------------
// Static Data
//


//---------------------------------------------------------------------------
// Debug Data
//
#if(1)
namespace EthernetDebug
{
   static   TTimeInterval ExecuteInterval;
   static   double        MinExecuteIntervalms = 10000.0;
   static   double        MaxExecuteIntervalms = 0.0;
   static   double        AvgExecuteIntervalms = 0.0;
   static   int           NumExecuteIntervalms = 0;
   static   int           WaitRead             = 0;
   static   int           WaitWrite            = 0;
   static   int           WaitTimer            = 0;
   static   int           WaitTimeout          = 0;
   static   int           WaitAbandoned        = 0;
};
using namespace EthernetDebug;
#endif

#pragma package(smart_init)

//---------------------------------------------------------------------------
// TEthernetClientThread
// Thread that does the actual ethernet communication for the client.  Separate
// from the TRtMsgProcessor thread.
//

TEthernetClientThread::TEthernetClientThread
   (
   const TEthernetParams   & InEthernetParams,
   TThreadDataCom          * InThreadDataCom
   ) :
   TThread( true ),
   NumInitCommunicationAttempts( 0 ),
   ValidInterface_( false ),
   ClientSocketInitialized_( false ),
   StrCriticalSection( NULL ),
   ThreadDataCom_( InThreadDataCom ),
   EthernetParams_( InEthernetParams )
{

   PortNum_                  = EthernetParams_.PortNum;
   HostAddr_                 = EthernetParams_.HostAddress;

   StrCriticalSection        = new TCriticalSection();

   ClientSocket              = new TClientSocket( Application );
   ClientSocket->Address     = HostAddr_;
   ClientSocket->Port        = PortNum_;
   ClientSocket->ClientType  = ctBlocking;

   ValidInterface_           = true;

   CodeSite->SendMsg( AnsiString( "HostAddr = " ) + HostAddr_ );
   CodeSite->SendInteger( "PortNum ", PortNum_ );

}

AnsiString const
TEthernetClientThread::GetStatusStr
   (
   )
{
   AnsiString Str;

   if ( !ClientSocketInitialized )
   {
      StrCriticalSection->Acquire();
      Str = AnsiString( "Connection Attempts: " ) + NumInitCommunicationAttempts + AnsiString( ".  " ) + InitializeSocketStatusStr;
      StrCriticalSection->Release();
   }

   return( Str );

}

AnsiString const
TEthernetClientThread::GetParametersStr
   (
   )
{

   AnsiString Str;
   StrCriticalSection->Acquire();
   Str = AnsiString( "Host Addr : " ) + HostAddr_ + AnsiString( "   Port : " ) + AnsiString( PortNum_ );
   StrCriticalSection->Release();

   return( Str );

}



bool const
TEthernetClientThread::InitCommunication
   (
   )
{


   try
   {
      ++NumInitCommunicationAttempts;
      ClientSocket->Open();

      AnsiString OpenStr        = AnsiString( "ClientSocket->Open().  Port = " ) + AnsiString( PortNum_ ) + AnsiString( " Host Addr = " ) + HostAddr;
      CodeSite->SendMsg( OpenStr );

      WinSocketStream           = new TWinSocketStream( ClientSocket->Socket, SOCKET_TIMEOUT_MSECS );

      return( true );
   }
   catch( Exception & Exc )
   {
      InitializeSocketStatusStr = Exc.Message;
      return( false );
   }

}

AnsiString const
TEthernetClientThread::GetInitializeSocketStatusStr
   (
   )
{

   StrCriticalSection->Acquire();
   AnsiString Str = InitializeSocketStatusStr_;
   StrCriticalSection->Release();

   return( Str );

}

void
TEthernetClientThread::SetInitializeSocketStatusStr
   (
   const AnsiString        & Str
   )
{
   StrCriticalSection->Acquire();
   InitializeSocketStatusStr_ = Str;
   StrCriticalSection->Release();
}


void __fastcall
TEthernetClientThread::Execute
   (
   )
{

   TThreadInf TThreadInf( "EthernetClientThread" );
   Priority = PriorityRtMsg;

   // DEBUG
   ExecuteInterval.ResetStart();

   while( !Terminated )
   {

      if ( !ClientSocketInitialized )
      {

         ClientSocketInitialized_ = InitCommunication();
         if ( !ClientSocketInitialized ) Sleep( SOCKET_INIT_SLEEP_MSECS );

      }
      else
      {


         TDataComWaitResults WaitResults = ThreadDataCom_->WaitForWrite();

         WaitDebugProcessing( WaitResults );

         try
         {

            TMsgData OutData = ThreadDataCom_->SendData;
            if ( OutData.size() && Send( OutData ) )
            {
               ThreadDataCom_->SendData = OutData;
               CodeSite->SendMsg( csmError, "TEthernetClientThread::Execute error on Send" );
            }

            TMsgData InData;
            Read( InData );

            if ( InData.size() )
            {
               ThreadDataCom_->ReceivedData = InData;
            }

         }
         catch( const ERemoteDriverException & RemoteDriverException )
         {
            AnsiString ExcStr     = AnsiString( "TEthernetClientThread::Execute Exception caught.  " ) + RemoteDriverException.ExcStr;
            CodeSite->SendMsg( ExcStr );
            throw( ERemoteDriverException( ExcStr ) );
         }
         catch( const Exception & Exc )
         {
            AnsiString ExcStr     = AnsiString( "TEthernetClientThread::Execute Exception caught.  " ) + Exc.Message;
            CodeSite->SendMsg( ExcStr );
            throw( ERemoteDriverException( ExcStr ) );
         }
      }

   }

}


bool const
TEthernetClientThread::Send
   (
   const TMsgData          & Data
   )
{

   if ( Data.empty() ) return( false );

   bool Sent                 = false;
   bool WriteError           = false;

   int TotalBytesWritten     = 0;
   int WriteAttempts         = 0;

   try
   {

      while ( !Sent && !WriteError )
      {

         int BytesWritten    = WinSocketStream->Write( (void *) &Data[TotalBytesWritten], Data.size() - TotalBytesWritten );
         TotalBytesWritten  += BytesWritten;

         if ( TotalBytesWritten == (int) Data.size() )
         {
            Sent             = true;
            WriteError       = false;
         }
         else
         {
            CodeSite->SendMsg( "EthernetClientThread::Send write failed" );
            if ( ++WriteAttempts > MAX_WRITE_ATTEMPTS )
            {
               Sent          = false;
               WriteError    = true;
               CodeSite->SendMsg( "EthernetClientThread::Send too many WriteAttempts" );
            }
         }

      }
      // DEBUG
      // Determine time between received traj and sent msgstat
      //
//      TrajTimeInterval.Reportms( "TEthernetClientThread::Send" );

   }
   catch ( Exception & Exc )
   {
      CodeSite->SendMsg( AnsiString( "TEthernetClientThread::Send Exception caught. Exception message = " ) + Exc.Message );
   }

   return( !Sent );

}

void
TEthernetClientThread::Read
   (
   TMsgData                & MsgData
   )
{

   unsigned char             Data[MAX_ETHERNET_BYTES_TO_READ];

   bool Done                      = false;

   while ( !Done && ClientSocket->Socket->Connected )
   {

      unsigned int NumBytesToRead = ClientSocket->Socket->ReceiveLength();

      if ( NumBytesToRead )
      {

         const int NumBytesRead   = WinSocketStream->Read( Data, NumBytesToRead );

         for ( int i=0; i<NumBytesRead; ++i )
         {

            MsgData.push_back( Data[i] );

         }

      }
      else
      {

         Done = true;

      }

   }

}

void
TEthernetClientThread::WaitDebugProcessing
   (
   const TDataComWaitResults      & WaitResults
   )
{
#if(1)
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
      MinExecuteIntervalms  = std::min( ExecuteInterval.TimeIntervalms, MinExecuteIntervalms );
      MaxExecuteIntervalms  = std::max( ExecuteInterval.TimeIntervalms, MaxExecuteIntervalms );
      AvgExecuteIntervalms = ( ( AvgExecuteIntervalms * NumExecuteIntervalms ) + ExecuteInterval.TimeIntervalms )/( NumExecuteIntervalms + 1 );
      ++NumExecuteIntervalms;
      CodeSite->WriteFloat( "ExecuteMinms", MinExecuteIntervalms );
      CodeSite->WriteFloat( "ExecuteMaxms", MaxExecuteIntervalms );
      CodeSite->WriteFloat( "ExecuteAvgms", AvgExecuteIntervalms );
   }
   ExecuteInterval.Reportms( "TEthernetClientThreadExecutems" );
   ExecuteInterval.ResetStart();
#endif
}

void
TEthernetClientThread::SetStatusStr
   (
   const AnsiString        &
   )
{
}

void
TEthernetClientThread::SetParametersStr
   (
   const AnsiString        &
   )
{
}

bool const
TEthernetClientThread::IsValid
   (
   )
{
   return( ValidInterface_ );
}


__fastcall
TEthernetClientThread::~TEthernetClientThread
   (

   )
{

   ClientSocket->Close();
   delete WinSocketStream;
   delete ClientSocket;
   delete StrCriticalSection;

}



//---------------------------------------------------------------------------
// TEthernetServer
// Does the listen and accept
//

TEthernetServer::TEthernetServer
   (
   const TEthernetParams   & InEthernetParams,
   TThreadDataCom          * InThreadDataCom
   ) :
   ServerSocket( NULL ),
   ActiveClientThread( NULL ),
   PortNum_( InEthernetParams.PortNum ),
   EthernetParams_( InEthernetParams ),
   ThreadDataCom_( InThreadDataCom )
{

   ValidInterface_                     = false;

   ServerSocket                        = new TServerSocket( NULL );

   ServerSocket->OnGetThread           = GetThread;

   ServerSocket->OnThreadEnd           = ThreadEnd;

   ServerSocket->OnClientDisconnect    = ClientDisconnect;

   ServerSocket->Port                  = EthernetParams_.PortNum;

   ServerSocket->ServerType            = stThreadBlocking;

   ServerSocket->Open();

   ValidInterface_                     = true;

}

void __fastcall
TEthernetServer::GetThread
   (
   TObject                    *    Sender,
   TServerClientWinSocket     *    ClientSocket,
   TServerClientThread        * &  SocketThread
   )
{

   TEthernetServerClientThread * NewThread       = new TEthernetServerClientThread( ClientSocket, ThreadDataCom_ );
   SocketThread                                  = NewThread;

   ActiveClientThread                            = ActiveClientThread ? ActiveClientThread : NewThread;

   SocketThread->Resume();

}

void __fastcall
TEthernetServer::ThreadEnd
   (
   TObject                  * Sender,
   TServerClientThread      * Thread
   )
{

   CodeSite->SendMsg( "TEthernetServer::ThreadEnd" );

   if ( Thread == ActiveClientThread )
   {

      CodeSite->SendMsg( "ActiveClientThread has ended." );
      ActiveClientThread = NULL;

   }

}

void __fastcall
TEthernetServer::ClientDisconnect
   (
   TObject                  * Sender,
   TCustomWinSocket         * Socket
   )
{

   CodeSite->SendMsg( csmInfo, "TEthernetServer::ClientDisconnect" );

}

AnsiString const
TEthernetServer::GetParametersStr
   (
   )
{
   AnsiString Str = AnsiString( "Ethernet Server.  No host address required.  Port number = " ) + AnsiString( EthernetParams_.PortNum );
   return( Str );
}

void
TEthernetServer::SetParametersStr
   (
   const AnsiString &
   )
{
}

AnsiString const
TEthernetServer::GetStatusStr
   (
   )
{
   AnsiString Str( "Ethernet Server.  " );

   if ( ActiveClientThread )
   {
      Str += AnsiString( "Client connection has been accepted. " );
   }
   else
   {
      Str = AnsiString( "No client connection has been accepted. " );
   }

   return( Str );

}

void
TEthernetServer::SetStatusStr
   (
   const AnsiString &
   )
{
}

bool const
TEthernetServer::InitCommunication
   (
   )
{
   return( ActiveClientThread != NULL );
}

bool const
TEthernetServer::IsValid
   (
   )
{
   return( ValidInterface_ );
}


__fastcall
TEthernetServer::~TEthernetServer
   (

   )
{

   if ( ActiveClientThread )
   {
      ActiveClientThread->Terminate();
      ActiveClientThread->WaitFor();
      delete ActiveClientThread;
      ActiveClientThread = NULL;
   }
//   delete ServerSocket;

}

TEthernetServerClientThread::TEthernetServerClientThread
   (
   TServerClientWinSocket  * InServerClientWinSocket,
   TThreadDataCom          * InThreadDataCom
   ) :
   TServerClientThread( true, InServerClientWinSocket ),
   ServerClientWinSocket( InServerClientWinSocket ),
   ThreadDataCom_( InThreadDataCom ),
   WinSocketStream( NULL )
{

   WinSocketStream               = new TWinSocketStream( ClientSocket, SOCKET_TIMEOUT_MSECS );

}

__fastcall
TEthernetServerClientThread::~TEthernetServerClientThread
   (
   )
{
   CodeSite->SendMsg( csmInfo, "TEthernetServerClientThread destructor" );
   delete WinSocketStream;
}

void __fastcall
TEthernetServerClientThread::ClientExecute
   (
   )
{


   while( !Terminated && ( ClientSocket && ClientSocket->Connected ) )
   {
      try
      {
         ThreadDataCom_->WaitForWrite();
         TMsgData OutData = ThreadDataCom_->SendData;
         if ( OutData.size() && Send( OutData ) )
         {
            ThreadDataCom_->SendData = OutData;
            AnsiString ExcStr( "TEthernetServerClientThread::Execute error on Send" );
            CodeSite->SendMsg( csmError, ExcStr );
            throw( Exception( ExcStr ) );
         }

         TMsgData InData;
         Read( InData );

         if ( InData.size() )
         {
            ThreadDataCom_->ReceivedData = InData;
         }

      }
      catch( const Exception & Exc )
      {
         AnsiString ExcStr     = AnsiString( "TEthernetServerClientThread::Execute Exception caught.  " ) + Exc.Message;
         CodeSite->SendMsg( ExcStr );
         throw( Exception( ExcStr ) );
      }

   }

   CodeSite->SendMsg( csmInfo, "TEthernetServerClientThread::ClientExecute is ending." );

}

void
TEthernetServerClientThread::Read
   (
   TMsgData                & ReadMsg
   )
{

   ReadMsg.clear();

   if ( WinSocketStream && WinSocketStream->WaitForData( SOCKET_WAIT_TIMEOUT_MSECS ) )
   {

      bool Reading = true;

      while ( Reading )
      {

         try
         {
            if ( WinSocketStream->WaitForData( SOCKET_WAIT_TIMEOUT_MSECS ) )
            {
               unsigned char Byte;
               int BytesRead = WinSocketStream->Read( &Byte, 1 );
               if ( BytesRead )
               {
                  ReadMsg.push_back( Byte );
               }
               else
               {
                  Reading    = false;
                  CodeSite->SendMsg( csmInfo, "TEthernetServerClientThread::Read WaitForData returned true, no bytes read.  Closing ClientSocket." );
                  ClientSocket->Close();
                  Terminate();
               }
            }
            else
            {
               Reading = false;
            }
         }
         catch( const Exception & Exc )
         {
            CodeSite->SendMsg( csmError, AnsiString( "TEthernetServerClientThread::Read exception caught " ) + Exc.Message );
            Reading = false;
//            throw( Exception( AnsiString( "TEthernetServerClientThread::Read exception thrown: " ) + Exc.Message ) ) );
         }

      }

   }

}

bool const
TEthernetServerClientThread::Send
   (
   const TMsgData          & WriteMsgData
   )
{


   if ( !WinSocketStream )     return( true );

   if ( WriteMsgData.empty() ) return( false );

   bool Sent                 = false;
   bool WriteError           = false;
   int  TotalBytesWritten    = 0;
   int  WriteAttempts        = 0;

   while ( !Sent && !WriteError )
   {

      try
      {
         int BytesWritten       = WinSocketStream->Write( (void *) &WriteMsgData[TotalBytesWritten], WriteMsgData.size() - TotalBytesWritten );
         TotalBytesWritten     += BytesWritten;

         if ( TotalBytesWritten == (int) WriteMsgData.size() )
         {
            Sent                = true;
            WriteError          = false;
         }
         else
         {
            CodeSite->SendMsg( "TEthernetServerClientThread::Send write failed" );
            if ( ++WriteAttempts > MAX_WRITE_ATTEMPTS )
            {
               Sent             = false;
               WriteError       = true;
               CodeSite->SendMsg( "TEthernetServerClientThread::Send too many WriteAttempts" );
            }
         }
      }
      catch( const Exception & Exc )
      {
         CodeSite->SendMsg( csmError, AnsiString( "TEthernetServerClientThread::Send exception caught " ) + Exc.Message );
//         throw( Exception( AnsiString( "TEthernetServerClientThread::Send exception thrown: " ) + Exc.Message ) ) );
         Sent       = false;
         WriteError = true;
      }

   }

   return( !Sent );

}

