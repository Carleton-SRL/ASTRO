//---------------------------------------------------------------------------


#ifndef SetPowerFramH
#define SetPowerFramH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ovclabel.hpp"
#include "RzEdit.hpp"
#include "RzPanel.hpp"
#include "RzSpnEdt.hpp"
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include "MsgDataFrame.h"
//---------------------------------------------------------------------------
class TSetPowerFrame : public TFrame
{
__published:	// IDE-managed Components
   TOvcLabel *OvcLabel2;
   TRzPanel *NumChanPnl;
   TOvcLabel *OvcLabel1;
   TRzSpinEdit *NumChansEdt;
   TRzPanel *LeftPnl;
   TOvcLabel *ChanLbl1;
   TOvcLabel *PowerLbl1;
   TRzSpinEdit *ChEdt0;
   TRzSpinEdit *PowerEdt0;
   TRzSpinEdit *ChEdt1;
   TRzSpinEdit *PowerEdt1;
   TRzSpinEdit *ChEdt2;
   TRzSpinEdit *PowerEdt2;
   TRzSpinEdit *ChEdt3;
   TRzSpinEdit *PowerEdt3;
   TRzSpinEdit *ChEdt4;
   TRzSpinEdit *PowerEdt4;
   TRzSpinEdit *ChEdt5;
   TRzSpinEdit *PowerEdt5;
   TRzPanel *ClientPnl;
   TOvcLabel *ChanLbl2;
   TOvcLabel *PowerLbl2;
   TRzSpinEdit *ChEdt6;
   TRzSpinEdit *PowerEdt6;
   TRzSpinEdit *ChEdt7;
   TRzSpinEdit *PowerEdt7;
   TRzSpinEdit *ChEdt8;
   TRzSpinEdit *PowerEdt8;
   TRzSpinEdit *ChEdt9;
   TRzSpinEdit *PowerEdt9;
   TRzSpinEdit *ChEdt10;
   TRzSpinEdit *PowerEdt10;
   TRzSpinEdit *ChEdt11;
   TRzSpinEdit *PowerEdt11;
   void __fastcall FrameResize(TObject *Sender);
   void __fastcall NumChansEdtChange(TObject *Sender);
private:	// User declarations
   static const int NumChansInFrame = ( 12 );
   class TChanPowerEdt {
   public:
      TRzSpinEdit *Chan;
      TRzSpinEdit *Power;
   };
   TChanPowerEdt   ChanPowerEdtArray[NumChansInFrame];


   static TChanPowerArray DefChanPowerArray;
   static bool            MinMaxPowerInitialized;
   static int             MaxPower;
   static int             MinPower;

   void SetDisp( const TChanPowerArray & ChanPowerArray );
   void SetVisible(const int NumChans);
public:		// User declarations
   __fastcall TSetPowerFrame(TComponent* Owner);
   TOutMsg const GetOutMsg();
   void ProcessCancel();
   static void SetMinMaxPower( const int InMinPower, const int InMaxPower );
};
//---------------------------------------------------------------------------
extern PACKAGE TSetPowerFrame *SetPowerFrame;
//---------------------------------------------------------------------------
#endif
