#ifndef InterfaceH
#define InterfaceH

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



#ifndef RemoteTypesH
#include "RemoteTypes.h"
#endif

#ifndef InMsgH
#include "InMsg.h"
#endif

#ifndef OutMsgH
#include "OutMsg.h"
#endif

#ifndef ThreadDataComH
#include "ThreadDataCom.h"
#endif

#ifndef InterfaceParamsH
#include "InterfaceParams.h"
#endif


__interface IInterfaceThread {
private:

   virtual AnsiString const  GetParametersStr()                                  = 0;
   virtual void              SetParametersStr( const AnsiString & )              = 0;

   virtual AnsiString const  GetStatusStr()                                      = 0;
   virtual void              SetStatusStr( const AnsiString & InStatusStr )      = 0;

   virtual bool const        IsValid()                                           = 0;

public:

   __fastcall virtual        ~IInterfaceThread()                                 = 0;

   virtual bool const        InitCommunication()                                 = 0;

   __property bool           Valid                 = { read = IsValid                                      };
   __property AnsiString     ParametersStr         = { read = GetParametersStr,  write = SetParametersStr  };
   __property AnsiString     StatusStr             = { read = GetStatusStr,      write = SetStatusStr      };

};

class TInterface {
private:

   TInterfaceParams          InterfaceParams_;
   IInterfaceThread        * InterfaceThread_;
   TThread                 * Thread_;
   TThreadDataCom          * ThreadDataCom_;
   bool                      ValidInterface_;

   AnsiString const          GetStatusStr();
   AnsiString const          GetParametersStr();
   bool const                IsValid() const;
   bool const                InitCommunication();
   TMsgData const            GetData();
   void                      SendData( const TMsgData & );
   int const                 GetUnsentDataSize() { return( ThreadDataCom_->UnsentDataSize ); }


public:

   TInterface( const TInterfaceParams & InInterfaceParams );
   virtual __fastcall       ~TInterface();

   TDataComWaitResults const WaitForRead() { return( ThreadDataCom_->WaitForRead() ); }

   __property bool                Valid              = { read = IsValid                                          };
   __property AnsiString          StatusStr          = { read = GetStatusStr                                     };
   __property AnsiString          ParametersStr      = { read = GetParametersStr                                 };
   __property TThreadDataCom    * ThreadDataCom      = { read = ThreadDataCom_                                   };
   __property TMsgData            ReceivedMsgData    = { read = GetData                                          };
   __property TMsgData            SendMsgData        = {                             write = SendData            };
   __property int                 UnsentDataSize     = { read = GetUnsentDataSize                                };


};

//---------------------------------------------------------------------------
#endif

