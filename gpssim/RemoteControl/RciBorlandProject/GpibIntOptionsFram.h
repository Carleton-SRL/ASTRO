//---------------------------------------------------------------------------


#ifndef GpibIntOptionsFramH
#define GpibIntOptionsFramH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ovclabel.hpp"
#include "RzEdit.hpp"
#include "RzSpnEdt.hpp"
#include <Mask.hpp>
#include "RzButton.hpp"

#include "InterfaceOptions.h"
//---------------------------------------------------------------------------
class TGpibIntOptionsFrame : public TFrame
{
__published:	// IDE-managed Components
   TOvcLabel *OvcLabel1;
   TOvcLabel *OvcLabel2;
   TRzSpinEdit *BoardIndexEdt;
   TOvcLabel *OvcLabel3;
   TRzSpinEdit *PrimaryAddrEdt;
   TRzButton *TestBtn;
   TOvcLabel *OvcLabel4;
   TOvcLabel *TestResultsLbl;
   TRzMemo *TestResultsDetailsMemo;
   void __fastcall TestBtnClick(TObject *Sender);
private:	// User declarations
   bool ValidInterface;
public:
   TGpibOptions const GetOptions() const;		// User declarations
   __fastcall TGpibIntOptionsFrame(TComponent* Owner);
   virtual __fastcall ~TGpibIntOptionsFrame();
};
//---------------------------------------------------------------------------
extern PACKAGE TGpibIntOptionsFrame *GpibIntOptionsFrame;
//---------------------------------------------------------------------------
#endif
