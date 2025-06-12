//---------------------------------------------------------------------------


#ifndef StartScenFramH
#define StartScenFramH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ovcbase.hpp"
#include "ovcef.hpp"
#include "ovclabel.hpp"
#include "ovcsf.hpp"

#include "MsgDataFrame.h"
//---------------------------------------------------------------------------
class TStartScenFrame : public TFrame
{
__published:	// IDE-managed Components
   TOvcLabel *OvcLabel2;
   TOvcLabel *OvcLabel1;
   TEdit *ScenNameEdt;
private:	// User declarations
   static AnsiString DefaultScen;
public:		// User declarations
   __fastcall TStartScenFrame(TComponent* Owner);
   TOutMsg const GetOutMsg();
   void ProcessCancel();
};
//---------------------------------------------------------------------------
extern PACKAGE TStartScenFrame *StartScenFrame;
//---------------------------------------------------------------------------
#endif
