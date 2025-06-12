//---------------------------------------------------------------------------


#ifndef QueryFramH
#define QueryFramH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ovclabel.hpp"
#include "MsgDataFrame.h"
#include "RzCmboBx.hpp"
#include "RzEdit.hpp"
#include "RzSpnEdt.hpp"
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TQueryFrame : public TFrame
{
__published:	// IDE-managed Components
   TOvcLabel *OvcLabel2;
   TRzComboBox *Messagecbox;
   TOvcLabel *OvcLabel1;
   TRzComboBox *QueryWhencbox;
   TOvcLabel *OvcLabel3;
   TOvcLabel *OvcLabel4;
   TRzSpinEdit *IntervalEdt;
   void __fastcall QueryWhencboxChange(TObject *Sender);
private:	// User declarations
   static TExtQuery DefExtQuery;
   void SetDisp(const TExtQuery & ExtQuery);
   
public:		// User declarations
   __fastcall TQueryFrame(TComponent* Owner);
   TOutMsg const GetOutMsg();
   void ProcessCancel();
};
//---------------------------------------------------------------------------
extern PACKAGE TQueryFrame *QueryFrame;
//---------------------------------------------------------------------------
#endif
