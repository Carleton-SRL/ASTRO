#ifndef MSGDATAFRAME_H
#define MSGDATAFRAME_H

#include "RemoteTypes.h"
#include "RciDriverMsgs.h"

#if(0)
class TMsgDataFrame : public TFrame {

public:

   __fastcall TMsgDataFrame(TComponent* Owner) : TFrame( Owner ) {};
   virtual __fastcall ~TMsgDataFrame() {};

   virtual TMsgData const GetSendData() = 0;
   virtual void ProcessCancel() = 0;
};
#endif
class TMsgDataInterface {
   virtual TMsgData const GetSendData() = 0;
   virtual void ProcessCancel() = 0;
};

#endif   
 