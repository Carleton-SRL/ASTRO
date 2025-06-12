//---------------------------------------------------------------------------

#ifndef RtMotionMemFrmH
#define RtMotionMemFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include "RzSplit.hpp"
#include "RzStatus.hpp"
#include "RzTabs.hpp"
#include <ExtCtrls.hpp>
#include "dxNavBar.hpp"
#include "dxNavBarBase.hpp"
#include "dxNavBarCollns.hpp"
#include <ImgList.hpp>
#include "ovcbase.hpp"
#include "ovcdrpvw.hpp"
#include "ovcrptvw.hpp"
#include "ovcrvidx.hpp"
#include "RzLabel.hpp"
//---------------------------------------------------------------------------

#ifndef ScenIniFileH
#include "ScenIniFile.h"
#endif

#ifndef TapMsecPfH
#include "TapMsecPf.h"
#endif

#ifndef ClosedLoopMemH
#include "ClosedLoopMem.h"
#endif

#ifndef ScramnetDllH
#include "ScramnetDll.h"
#endif

#ifndef ClosedLoopSimTypeH
#include "ClosedLoopSimType.h"
#endif

#ifndef VhTrthFlH
#include "VhTrthFl.h"
#endif



using namespace ClosedLoopMem;

class TRtMotionMemForm : public TForm
{
__published:	// IDE-managed Components
   TRzToolbar *Toolbar;
   TRzStatusBar *StatusBar;
   TRzSizePanel *TopSizePnl;
   TRzPanel *TopPnl;
   TRzPanel *MainClientPnl;
   TRzVersionInfoStatus *VerInfoStatusPane;
   TRzPageControl *RtMotionMemPageCtrl;
   TRzTabSheet *SimStatusTab;
   TRzTabSheet *SvRecTab;
   TRzVersionInfo *VerInfo;
   TRzTabSheet *ExtToSimTab;
   TRzPanel *SimCommandsPnl;
   TRzSizePanel *SimCommandsLeftSizePnl;
   TdxNavBar *ExternalToSimnb;
   TdxNavBarItem *Initialization;
   TdxNavBarGroup *ExternalToSimnbGroup1;
   TImageList *SmallNavBarImages;
   TImageList *LargeNavBarImages;
   TOvcDataReportView *RangeReportView;
   TTimer *RtMotionTimer;
   TRzLabel *DateTimeLbl;
   TRzLabel *DateTimeVal;
   TRzLabel *GpsTimeLbl;
   TRzLabel *GpsTimeVal;
private:

   TScenIniFile            * ScenIni_;
   TTapMsecProfile         * TapMsecPf_;
   TScramnetDll            * ScramnetDll_;
   unsigned char           * BaseAddr_;
   TclExtToSimMem          * ExtToSimMem_;
   TclSimToExtMem          * SimToExtMem_;
   bool                      FirstRangeReport_;
   TVehicleTruthFile       * VehTruthFile;
   TClosedLoopSimType        ClosedLoopSimType;
   int                       TrajectoryDeltaTimeMillisec;
   int                       LastTrajectoryTimeMillisec;

   TVehTruthRec              FirstTruth_;
   TVehTruthRec              LastTruth_;
   TVehTruthRec              CurTruth_;

   TGpsTime                  CurTime;
   TGpsTime                  FirstTime;
   TGpsTime                  LastTime;
   TVehTruthRec              InitRec_;
   bool                      InitValid_;

   TclExtToSimMem          * GetExtToSimMem();
   TclSimToExtMem          * GetSimToExtMem();

   TclTimeSvRec const        GetTimeSvRec();
   TclTimeChannelStatus const GetTimeChannelStatus();
   TclCurTime const       GetCurTime();

   void                      UpdateSvRecData();
   void                      InitMem();
   void                      UpdateTime();
   void                      FillVehicleState( TclVehicleState         * VehState, TVehTruthRec            & VehStateRec );
   void                      InitFromVehTruthRec( TVehTruthRec & Rec );


public:

   __fastcall TRtMotionMemForm( TComponent * Owner, const TClosedLoopSimType & ClosedLoopSimType );

};
//---------------------------------------------------------------------------
extern PACKAGE TRtMotionMemForm *RtMotionMemForm;
//---------------------------------------------------------------------------
#endif
