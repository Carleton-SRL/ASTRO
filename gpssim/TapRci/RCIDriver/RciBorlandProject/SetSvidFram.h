//---------------------------------------------------------------------------


#ifndef SetSvidFramH
#define SetSvidFramH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "MsgDataFrame.h"
#include "ovclabel.hpp"
#include "RzEdit.hpp"
#include "RzPanel.hpp"
#include "RzSpnEdt.hpp"
#include <ExtCtrls.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TSetSvidFrame : public TFrame
{
__published:	// IDE-managed Components
   TOvcLabel *OvcLabel2;
   TRzPanel *NumChanPnl;
   TRzSpinEdit *NumChansEdt;
   TOvcLabel *OvcLabel1;
   TRzPanel *LeftPnl;
   TRzPanel *ClientPnl;
   TOvcLabel *OvcLabel3;
   TOvcLabel *OvcLabel4;
   TRzSpinEdit *ChEdt0;
   TRzSpinEdit *SvidEdt0;
   TRzSpinEdit *ChEdt1;
   TRzSpinEdit *SvidEdt1;
   TRzSpinEdit *ChEdt2;
   TRzSpinEdit *SvidEdt2;
   TRzSpinEdit *ChEdt3;
   TRzSpinEdit *SvidEdt3;
   TRzSpinEdit *ChEdt4;
   TRzSpinEdit *SvidEdt4;
   TRzSpinEdit *ChEdt5;
   TRzSpinEdit *SvidEdt5;
   TOvcLabel *ChanLbl2;
   TOvcLabel *SvidLbl2;
   TRzSpinEdit *ChEdt6;
   TRzSpinEdit *SvidEdt6;
   TRzSpinEdit *ChEdt7;
   TRzSpinEdit *SvidEdt7;
   TRzSpinEdit *ChEdt8;
   TRzSpinEdit *SvidEdt8;
   TRzSpinEdit *ChEdt9;
   TRzSpinEdit *SvidEdt9;
   TRzSpinEdit *ChEdt10;
   TRzSpinEdit *SvidEdt10;
   TRzSpinEdit *ChEdt11;
   TRzSpinEdit *SvidEdt11;
   void __fastcall FrameResize(TObject *Sender);
   void __fastcall NumChansEdtChange(TObject *Sender);
private:	// User declarations
   static const int NumChansInFrame = ( 12 );
   class TChanSvidEdt {
   public:
      TRzSpinEdit *Chan;
      TRzSpinEdit *Svid;
   };
   TChanSvidEdt   ChanSvidEdtArray[NumChansInFrame];


   static TChanSvidArray DefChanSvidArray;

   void SetDisp( const TChanSvidArray & ChanSvidArray );
   void SetVisible(const int NumChans);
public:		// User declarations
   __fastcall TSetSvidFrame(TComponent* Owner);
   TOutMsg const GetOutMsg();
   void ProcessCancel();
};
//---------------------------------------------------------------------------
extern PACKAGE TSetSvidFrame *SetSvidFrame;
//---------------------------------------------------------------------------
#endif
