//---------------------------------------------------------------------------


#ifndef ShutdownFramH
#define ShutdownFramH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ovclabel.hpp"
#include "MsgDataFrame.h"
//---------------------------------------------------------------------------
class TShutdownFrame : public TFrame
{
__published:	// IDE-managed Components
   TOvcLabel *OvcLabel2;
   TOvcLabel *OvcLabel1;
private:	// User declarations
public:		// User declarations
   __fastcall TShutdownFrame(TComponent* Owner);
   TOutMsg const GetOutMsg();
   void ProcessCancel();
};
//---------------------------------------------------------------------------
extern PACKAGE TShutdownFrame *ShutdownFrame;
//---------------------------------------------------------------------------
#endif
