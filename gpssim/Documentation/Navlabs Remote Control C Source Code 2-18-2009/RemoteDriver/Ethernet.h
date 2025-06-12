//---------------------------------------------------------------------------

#ifndef EthernetH
#define EthernetH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// $Workfile:: Ethernet.h                                            $
//
// $Revision:: 1                                                     $
//
// $History:: Ethernet.h                                             $
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


#ifndef InterfaceH
#include "Interface.h"
#endif

#ifndef ThreadDataComH
#include "ThreadDataCom.h"
#endif

#ifndef InterfaceH
#include "Interface.h"
#endif


class TEthernetClientThread : public TThread, public IInterfaceThread {
private:

   TClientSocket           * ClientSocket;
   TWinSocketStream        * WinSocketStream;
   int                       PortNum_;
   AnsiString                HostAddr_;
   bool                      ValidInterface_;
   int                       NumInitCommunicationAttempts;
   bool                      ClientSocketInitialized_;
   TCriticalSection        * StrCriticalSection;
   AnsiString                InitializeSocketStatusStr_;
   TThreadDataCom          * ThreadDataCom_;
   TEthernetParams           EthernetParams_;

   void                      Read( TMsgData & );
   bool const                Send( const TMsgData & );
   AnsiString const          GetStatusStr();
   void                      SetStatusStr( const AnsiString & InStatusStr );
   AnsiString const          GetParametersStr();
   void                      SetParametersStr( const AnsiString & InParametersStr );
   bool const                IsValid();

   AnsiString const          GetInitializeSocketStatusStr();
   void                      SetInitializeSocketStatusStr( const AnsiString & InInitializeSocketStatusStr );
   void                      WaitDebugProcessing( const TDataComWaitResults & );

protected:

   void __fastcall           Execute();

public:

   TEthernetClientThread( const TEthernetParams & InEthernetParams, TThreadDataCom * ThreadDataCom );
   __fastcall ~TEthernetClientThread();

   bool const                InitCommunication();

   __property int            PortNum                   = { read = PortNum_,                     write = PortNum_                     };
   __property AnsiString     HostAddr                  = { read = HostAddr_,                    write = HostAddr_                    };
   __property bool           Valid                     = { read = ValidInterface_                                                    };
   __property bool           ClientSocketInitialized   = { read = ClientSocketInitialized_,                                          };
   __property AnsiString     StatusStr                 = { read = GetStatusStr,                 write = SetStatusStr                 };
   __property AnsiString     ParametersStr             = { read = GetParametersStr,             write = SetParametersStr             };
   __property AnsiString     InitializeSocketStatusStr = { read = GetInitializeSocketStatusStr, write = SetInitializeSocketStatusStr };

};
//---------------------------------------------------------------------------

class TEthernetServerClientThread : public TServerClientThread {
private:

   TServerClientWinSocket  * ServerClientWinSocket;
   TWinSocketStream        * WinSocketStream;
   bool                      ActiveClient_;
   TThreadDataCom          * ThreadDataCom_;

protected:

   void __fastcall           ClientExecute();
   void                      Read( TMsgData & );
   bool const                Send( const TMsgData & );

public:

   TEthernetServerClientThread( TServerClientWinSocket * ServerClientWinSocket, TThreadDataCom * InThreadDataCom );
   virtual __fastcall ~TEthernetServerClientThread();

};

typedef std::vector<TEthernetServerClientThread *> TEthernetServerClientThreadArray;

//---------------------------------------------------------------------------

class TEthernetServer : public IInterfaceThread {
private:

   TEthernetServerClientThread         * ActiveClientThread;
   TEthernetServerClientThreadArray      ClientThreadArray;

   TServerSocket           * ServerSocket;
   int                       PortNum_;
   bool                      ValidInterface_;
   TThreadDataCom          * ThreadDataCom_;
   TEthernetParams           EthernetParams_;

   AnsiString const          GetParametersStr();
   void                      SetParametersStr( const AnsiString & );

   AnsiString const          GetStatusStr();
   void                      SetStatusStr( const AnsiString & InStatusStr );

   bool const                IsValid();

public:

   bool const                InitCommunication();

   void __fastcall GetThread
      (
      TObject                  *   Sender,
      TServerClientWinSocket   *   ClientSocket,
      TServerClientThread      * & SocketThread
      );

   void __fastcall ThreadEnd
      (
      TObject                  * Sender,
      TServerClientThread      * Thread
      );

   void __fastcall ClientDisconnect
      (
      TObject                  * Sender,
      TCustomWinSocket         * Socket
      );

public:

   TEthernetServer( const TEthernetParams & InEthernetParams, TThreadDataCom * ThreadDataCom );
   virtual __fastcall ~TEthernetServer();

   __property int            PortNum               = { read = PortNum_,   write = PortNum_                 };
   __property bool           Valid                 = { read = IsValid                                      };
   __property AnsiString     ParametersStr         = { read = GetParametersStr,  write = SetParametersStr  };
   __property AnsiString     StatusStr             = { read = GetStatusStr,      write = SetStatusStr      };

};
//---------------------------------------------------------------------------


#endif

