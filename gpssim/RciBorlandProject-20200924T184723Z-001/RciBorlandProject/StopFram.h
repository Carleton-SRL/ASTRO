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
class TStopFrame : public TFrame
{
__published:	// IDE-managed Components
   TOvcLabel *OvcLabel1;
   TOvcLabel *OvcLabel2;
private:	// User declarations
public:		// User declarations
   __fastcall TStopFrame(TComponent* Owner);
   TOutMsg const GetOutMsg();
   void ProcessCancel();
};
//---------------------------------------------------------------------------
extern PACKAGE TStopFrame *StopFrame;
//---------------------------------------------------------------------------
#endif
