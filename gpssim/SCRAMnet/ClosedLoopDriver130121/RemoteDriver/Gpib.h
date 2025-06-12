#ifndef GpibH
#define GpibH

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


#ifndef RemoteDriverPfH
#include "RemoteDriverPf.h"
#endif

#ifndef InterfaceH
#include "Interface.h"
#endif

#if(0)
typedef struct  {
   TThreadDataCom          * ThreadDataCom;
   TCriticalSection        * CritSec;
   int                       BoardDev;
} TGpibThreadCallbackData;
#endif

class TGpibThread : public TThread, public IInterfaceThread {
private:

   bool                      ControllerInCharge_;
   int                       BoardIndex_;
   int                       PrimaryAddress_;
   int                       SecondaryAddress_;
   int                       Timeout_;
   bool                      ValidInterface_;
   int                       Board_;
   TCriticalSection        * StrCriticalSection;
   AnsiString                StatusStr_;
   TThreadDataCom          * ThreadDataCom_;
   TGpibParams               GpibParams_;
   TMsgData                  OutData_;
   bool                      RequestedService_;

   AnsiString const          GetStatusStr();
   void                      SetStatusStr( const AnsiString & InStatusStr );

   AnsiString const          GetParametersStr();
   void                      SetParametersStr( const AnsiString & InParametersStr );

   bool const                IsValid() { return( ValidInterface_ ); }

   void                      WaitDebugProcessing( const TDataComWaitResults WaitResult );

   bool const                Send( const TMsgData & Data );
   void                      Read( TMsgData & Data );

protected:

   void __fastcall           Execute();

public:

   TGpibThread( const TGpibParams & InGpibParams, TThreadDataCom * InThreadDataCom );
   __fastcall ~TGpibThread();

   bool const                InitCommunication();


   __property int            BoardIndex                = { read = BoardIndex_,                  write = BoardIndex_                  };
   __property int            PrimaryAddress            = { read = PrimaryAddress_,              write = PrimaryAddress_              };
   __property int            SecondaryAddress          = { read = SecondaryAddress_,            write = SecondaryAddress_            };
   __property int            Timeout                   = { read = Timeout_,                     write = Timeout_                     };
   __property int            Board                     = { read = Board_,                                                            };
   __property bool           Valid                     = { read = IsValid                                                            };
   __property AnsiString     StatusStr                 = { read = GetStatusStr,                 write = SetStatusStr                 };
   __property AnsiString     ParametersStr             = { read = GetParametersStr,             write = SetParametersStr             };

};



//---------------------------------------------------------------------------

#endif

