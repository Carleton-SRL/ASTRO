//---------------------------------------------------------------------------


#ifndef StopFramH
#define StopFramH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ovclabel.hpp"

#include "MsgDataFrame.h"
//---------------------------------------------------------------------------
class TStopFrame : public TMsgDataFrame
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
   __fastcall TStopFrame(TComponent* Owner);
   TMsgData const GetSendData();
   void ProcessCancel();
};
//---------------------------------------------------------------------------
extern PACKAGE TStopFrame *StopFrame;
//---------------------------------------------------------------------------
#endif 
