//---------------------------------------------------------------------------

#ifndef DataExtractionReqFrmH
#define DataExtractionReqFrmH
//---------------------------------------------------------------------------


//------------------------------------------------------------------------------
#ifndef BUILDERINCLUDES
//------------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ovclabel.hpp"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include "RzRadChk.hpp"
#include <ExtCtrls.hpp>
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------


//---------------------------------------------------------------------------
class TDataExtractionReqForm : public TForm
{
__published:	// IDE-managed Components
   TRzPanel *TopPnl;
   TRzPanel *BottomPnl;
   TRzBitBtn *OkBtn;
   TRzBitBtn *CancelBtn;
   TRzPanel *MainPnl;
   TRzCheckBox *Enabledcb;
   TOvcLabel *TitleLbl;
private:

   bool                      ReqEnabled_;
public:
   __fastcall TDataExtractionReqForm( TComponent* Owner, const bool InEnabled );

   __property bool           ReqEnabled = { read = ReqEnabled_, write = ReqEnabled_ };
   
};
//---------------------------------------------------------------------------
extern PACKAGE TDataExtractionReqForm *DataExtractionReqForm;
//---------------------------------------------------------------------------
#endif
