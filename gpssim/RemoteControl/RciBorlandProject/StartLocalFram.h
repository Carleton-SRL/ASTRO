//---------------------------------------------------------------------------


#ifndef StartLocalFramH
#define StartLocalFramH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ovclabel.hpp"

#include "MsgDataFrame.h"
//---------------------------------------------------------------------------
class TStartLocalFrame : public TFrame
{
__published:	// IDE-managed Components
   TOvcLabel *OvcLabel2;
   TOvcLabel *OvcLabel1;
private:	// User declarations
public:		// User declarations
   __fastcall TStartLocalFrame(TComponent* Owner);
   TOutMsg const GetOutMsg();
   void ProcessCancel();
};
//---------------------------------------------------------------------------
extern PACKAGE TStartLocalFrame *StartLocalFrame;
//---------------------------------------------------------------------------
#endif
