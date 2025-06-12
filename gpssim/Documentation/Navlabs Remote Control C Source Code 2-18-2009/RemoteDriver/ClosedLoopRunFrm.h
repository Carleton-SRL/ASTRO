//---------------------------------------------------------------------------

#ifndef ClosedLoopRunFrmH
#define ClosedLoopRunFrmH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// $Workfile::                                                       $
//
// $Revision::                                                       $
//
// $History::                                                        $
//
//
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
#include "RzSplit.hpp"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Chart.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Menus.hpp>
#include "TeePolar.hpp"
#include <Series.hpp>
#include <ComCtrls.hpp>
#include "MsgListFram.h"
#include <ScktComp.hpp>
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------

#ifndef RemoteTypesH
#include "RemoteTypes.h"
#endif

#ifndef MsgListFramH
#include "MsgListFram.h"
#endif

#ifndef ClosedLoopSimTypeH
#include "ClosedLoopSimType.h"
#endif

#ifndef VhTrthFlH
#include "VhTrthFl.h"
#endif

#ifndef InterfaceOptionsH
#include "InterfaceOptions.h"
#endif

#ifndef CLControlH
#include "CLControl.h"
#endif

#ifndef StelMsgsH
#include "StelMsgs.h"
#endif

#ifndef DataExtractionChanFramH
#include "DataExtractionChanFram.h"
#endif

#ifndef SendMsgsFrmH
#include "SendMsgsFrm.h"
#endif

typedef vector<TDataExtractionChanFrame *> TDataExtractionChanFrameArray;
//---------------------------------------------------------------------------
class TClosedLoopRunForm : public TForm
{
__published:	// IDE-managed Components
   TRzToolbar *MainToolbar;
   TRzStatusBar *RzStatusBar1;
   TRzToolbarButton *BtnStop;
   TRzSizePanel *TopPnl;
   TRzPanel *MainClientPnl;
   TRzSizePanel *LeftMainPnl;
   TRzPanel *RightMainPnl;
   TMsgListFrame *MsgListFrame;
   TMainMenu *ClosedLoopMenu;
   TMenuItem *Options;
   TMenuItem *DispOptionsMenu;
   TMenuItem *HelpMenu;
   TMenuItem *AboutMenu;
   TTimer *CLCTimer;
   TPageControl *MainPageCtrl;
   TTabSheet *VehSheet;
   TChart *GtChart;
   TTabSheet *SatSheet;
   TRzSizePanel *MainRightSizePnl;
   TRzPanel *SvLookAnglePnl;
   TRzPanel *DataExtractionPnl;
   TRzPanel *DataTopPnl;
   TOvcLabel *DataExtractionTitleLbl;
   TRzPanel *DataExtractionHeaderPnl;
   TOvcLabel *OvcLabel7;
   TOvcLabel *DataExtractionTimeLbl;
   TScrollBox *DataExtractionScrollBox;
   TOvcLabel *ChanLbl;
   TOvcLabel *OvcLabel8;
   TOvcLabel *OvcLabel9;
   TChart *SatelliteChart;
   TPolarSeries *SatelliteSeries;
   TRzSplitter *TopSplitter;
   TRzPanel *RightTopPnl;
   TRzPanel *InterfaceStatusPnl;
   TRzSplitter *InterfaceStatusDisplaySplitter;
   TRzPanel *InterfaceLeftPnl;
   TOvcLabel *OvcLabel1;
   TOvcLabel *OvcLabel2;
   TOvcLabel *NumMsgsSentLbl;
   TOvcLabel *NumMsgsRcvdLbl;
   TOvcLabel *OvcLabel5;
   TOvcLabel *NumMsgsRcvdExceptStatLbl;
   TRzBitBtn *SendMsgBtn;
   TRzPanel *InterfaceStatusDisplayPnl;
   TOvcLabel *InterfaceStatusStrLbl;
   TRzPanel *InterfaceStatusDisplayTitlePnl;
   TOvcLabel *InterfaceStatusDisplayTitleLbl;
   TRzPanel *SimulationStatusTitlePnl;
   TOvcLabel *SimulationStatusTitleLbl;
   TRzPanel *SimulationStatusDisplayPnl;
   TOvcLabel *OvcLabel4;
   TOvcLabel *SimulatorTimeLbl;
   TOvcLabel *LastMsgLbl;
   TOvcLabel *OvcLabel10;
   TRzBitBtn *SendTrajBtn;
   TRzBitBtn *StartSimBtn;
   void __fastcall AboutMenuClick(TObject *Sender);
   void __fastcall CLCTimerTimer(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall BtnStopClick(TObject *Sender);
   void __fastcall SendMsgBtnClk(TObject *Sender);
   void __fastcall StartSimBtnClk(TObject *Sender);
   void __fastcall SendTrajBtnClick(TObject *Sender);

private:

   TClosedLoopSimType                  ClosedLoopSimType;
   TIntOptions                       * IntOptions;
   TGpibOptions                        GpibOptions;
   TVehTruthRec                        CurTruth;
   TInMsgArray                         InMsgs;
   TMsgTrafficArray                    MsgTrafficArray;
   TDataExtractionChanFrameArray       DataExtractionChanArray;
   TCLControl                        * CLControl;
   bool                                InTimer;
   TLineSeries                       * GtSeries;
   TStelMsgDescMap                     StelInMsgDescMap;
   TStelMsgDescMap                     StelOutMsgDescMap;
   TSendMsgsForm                     * SendMsgsForm;
   TOutMsgQ                            OutMsgs;


   void                                AddPlotPoint( const TVehTruthRec & Truth );
   void                                CreateMsgDescMap();
   void                                ProcessMsgTrafficArray( TMsgTrafficArray & Msgs);
   void                                ProcessInputMsgs( TInMsgArray & InMsgs );
   void                                ProcessSVLookAngle( const TInMsg & InMsg );
   void                                ProcessTime( const TInMsg & InMsg );
   void                                Terminate();

public:

   __fastcall TClosedLoopRunForm
      (
      TComponent               * Owner,
      const TClosedLoopSimType & ClosedLoopSimType
      );

   __fastcall ~TClosedLoopRunForm();
   void SetupVehiclePlot();

};
//---------------------------------------------------------------------------
extern PACKAGE TClosedLoopRunForm *ClosedLoopRunForm;
//---------------------------------------------------------------------------
#endif
