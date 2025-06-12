//---------------------------------------------------------------------------

#ifndef RciRunFrmH
#define RciRunFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MsgListFram.h"
#include "ovclabel.hpp"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include "RzSplit.hpp"
#include <ExtCtrls.hpp>

#include "InterfaceOptions.h"
#include <ComCtrls.hpp>
#include "MsgDataFrame.h"
#include "Interface.h"
#include "OutMsg.h"
#include "RzLstBox.hpp"
#include "SsBase.hpp"
#include "StAbout.hpp"
#include "StBrowsr.hpp"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TRciRunForm : public TForm
{
__published:	// IDE-managed Components
   TRzSizePanel *TopSizePnl;
   TRzPanel *MainPnl;
   TRzSizePanel *LeftSizePnl;
   TRzPanel *LeftPnl;
   TMsgListFrame *MsgListFrame;
   TRzPanel *RightClientPnl;
   TRzPanel *RzPanel1;
   TOvcLabel *IntLbl;
   TOvcLabel *SimModeLbl;
   TOvcLabel *OvcLabel1;
   TRzPanel *RzPanel2;
   TRzPanel *RzPanel3;
   TRzBitBtn *StartScenBtn;
   TRzBitBtn *InitGeoBtn;
   TRzBitBtn *StartLocalBtn;
   TRzBitBtn *SetSvidBtn;
   TRzBitBtn *SetPowerBtn;
   TRzBitBtn *StopBtn;
   TRzBitBtn *ShutdownBtn;
   TRzBitBtn *QueryBtn;
   TOvcLabel *OvcLabel2;
   TRzPanel *MsgDataPnl;
   TRzPanel *RzPanel5;
   TOvcLabel *CommandDataLbl;
   TRzPanel *RzPanel6;
   TRzButton *SendBtn;
   TRzButton *CancelBtn;
   TPageControl *SimMsgsPageCtrl;
   TTabSheet *AckSheet;
   TTabSheet *ChanStatSheet;
   TTabSheet *BitResultsSheet;
   TTabSheet *SysCfgSheet;
   TTimer *Timer;
   TRzSizePanel *RzSizePanel1;
   TRzPanel *RzPanel4;
   TRzPanel *AckRightPnl;
   TRzTabbedListBox *AckListBox;
   TOvcLabel *OvcLabel3;
   TOvcLabel *OvcLabel4;
   TOvcLabel *AckTimeRcvdLbl;
   TOvcLabel *AckMsgValidLbl;
   TOvcLabel *AckMsgIdLbl;
   TOvcLabel *AckSimModeValidLbl;
   TOvcLabel *OvcLabel5;
   TOvcLabel *OvcLabel6;
   TOvcLabel *OvcLabel7;
   TOvcLabel *OvcLabel8;
   TOvcLabel *ChanStatCh0;
   TOvcLabel *ChanStatCh1;
   TOvcLabel *ChanStatCh2;
   TOvcLabel *ChanStatCh3;
   TOvcLabel *ChanStatCh4;
   TOvcLabel *ChanStatCh5;
   TOvcLabel *ChanStatCh6;
   TOvcLabel *ChanStatCh7;
   TOvcLabel *ChanStatCh8;
   TOvcLabel *ChanStatCh9;
   TOvcLabel *ChanStatCh10;
   TOvcLabel *ChanStatCh11;
   TOvcLabel *ChanStatCh12;
   TOvcLabel *ChanStatCh13;
   TOvcLabel *ChanStatSvidLbl0;
   TOvcLabel *ChanStatSvidLbl1;
   TOvcLabel *ChanStatSvidLbl2;
   TOvcLabel *ChanStatSvidLbl3;
   TOvcLabel *ChanStatSvidLbl4;
   TOvcLabel *ChanStatSvidLbl5;
   TOvcLabel *ChanStatSvidLbl6;
   TOvcLabel *ChanStatSvidLbl7;
   TOvcLabel *ChanStatSvidLbl8;
   TOvcLabel *ChanStatSvidLbl9;
   TOvcLabel *ChanStatSvidLbl10;
   TOvcLabel *ChanStatSvidLbl11;
   TOvcLabel *ChanStatSvidLbl12;
   TOvcLabel *ChanStatSvidLbl13;
   TOvcLabel *ChanStatPower0;
   TOvcLabel *ChanStatPower1;
   TOvcLabel *ChanStatPower2;
   TOvcLabel *ChanStatPower3;
   TOvcLabel *ChanStatPower4;
   TOvcLabel *ChanStatPower5;
   TOvcLabel *ChanStatPower6;
   TOvcLabel *ChanStatPower7;
   TOvcLabel *ChanStatPower8;
   TOvcLabel *ChanStatPower9;
   TOvcLabel *ChanStatPower10;
   TOvcLabel *ChanStatPower11;
   TOvcLabel *ChanStatPower12;
   TOvcLabel *ChanStatPower13;
   TOvcLabel *OvcLabel9;
   TOvcLabel *OvcLabel10;
   TOvcLabel *OvcLabel11;
   TOvcLabel *OvcLabel12;
   TOvcLabel *Bitx1Lbl;
   TOvcLabel *Bitx2Lbl;
   TOvcLabel *Bitx3Lbl;
   TOvcLabel *OvcLabel13;
   TOvcLabel *OvcLabel14;
   TOvcLabel *OvcLabel15;
   TOvcLabel *BitIntLbl;
   TOvcLabel *BitOcxoLbl;
   TOvcLabel *BitPllLbl;
   TOvcLabel *OvcLabel16;
   TOvcLabel *OvcLabel17;
   TOvcLabel *SysCfgNumChansLbl;
   TOvcLabel *OvcLabel18;
   TOvcLabel *SysCfgL2CapableLbl;
   TOvcLabel *OvcLabel19;
   TOvcLabel *SysCfgMinPowerLbl;
   TOvcLabel *SysCfgMaxPowerLbl;
   TOvcLabel *OvcLabel21;
   TOvcLabel *OvcLabel22;
   TOvcLabel *OvcLabel20;
   TOvcLabel *BitDateLbl;
   TOvcLabel *BitTimeLbl;
   TStBrowser *StBrowser1;
   TStatusBar *StatusBar;
   TMainMenu *MainMenu1;
   TMenuItem *Help1;
   TMenuItem *AboutMenu;
   TOvcLabel *OvcLabel23;
   TOvcLabel *OvcLabel24;
   TOvcLabel *OvcLabel25;
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall StartScenBtnClick(TObject *Sender);
   void __fastcall TimerTimer(TObject *Sender);
   void __fastcall InitGeoBtnClick(TObject *Sender);
   void __fastcall StartLocalBtnClick(TObject *Sender);
   void __fastcall SetSvidBtnClick(TObject *Sender);
   void __fastcall SetPowerBtnClick(TObject *Sender);
   void __fastcall StopBtnClick(TObject *Sender);
   void __fastcall ShutdownBtnClick(TObject *Sender);
   void __fastcall QueryBtnClick(TObject *Sender);
   void __fastcall SendBtnClick(TObject *Sender);
   void __fastcall AboutMenuClick(TObject *Sender);
private:	// User declarations
   TFrame        *MsgDataFrame;
   bool          InTimer;
   TInterface    *Interface;
   TOutMsgQueue  OutMsgs;
   eRciSimMode   SimMode;
   TIntOptions   *IntOptions;

   void SetMsgDataFrame(TFrame * NewMsgDataFrame);
   void InitializeInterface( TIntOptions * );
   void ProcessInputMsgs(const TInMsgArray & );
   void ProcessInputMsg( const TInMsg & );
   void ProcessMsgTrafficArray(TMsgTrafficArray &Msgs);
   void ProcessAckMsg(const TInMsg & InMsg);
   void ProcessSimModeMsg(const TInMsg & InMsg);
   void ProcessChanStatMsg(const TInMsg & InMsg);
   void ProcessBitResultsMsg(const TInMsg & InMsg);
   void ProcessSysCfgMsg(const TInMsg & InMsg);
   void ProcessUnknownMsg( const TInMsg & InMsg );
   void UpdateStatusBar();
public:		// User declarations
   __fastcall TRciRunForm(TComponent* Owner, TIntOptions *IntOptions);
};
//---------------------------------------------------------------------------
extern PACKAGE TRciRunForm *RciRunForm;
//---------------------------------------------------------------------------
#endif
