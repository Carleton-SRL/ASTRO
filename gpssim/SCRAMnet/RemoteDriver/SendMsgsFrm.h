//---------------------------------------------------------------------------

#ifndef SendMsgsFrmH
#define SendMsgsFrmH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// $Workfile:: SendMsgsFrm.h                                         $
//
// $Revision:: 1                                                     $
//
// $History:: SendMsgsFrm.h                                          $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 11/17/02   Time: 10:04a
//Created in $/RemoteDriver
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
#include "RemoteTypes.h"
#include "ovclabel.hpp"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "RzLabel.hpp"
#include <ImgList.hpp>
#include "dxNavBar.hpp"
#include "dxNavBarBase.hpp"
#include "dxNavBarCollns.hpp"
#include "dxNavBarStyles.hpp"
#include "RzSplit.hpp"
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------

#ifndef OutMsgH
#include "OutMsg.h"
#endif

#ifndef InterfaceH
#include "Interface.h"
#endif

#ifndef ChanAssignFrmH
#include "ChanAssignFrm.h"
#endif


#if(0)
class TSendMsgsParams {
private:

   bool                      DataExtractionReqEnabled_;


public:

   TSendMsgsParams() : DataExtractionReqEnabled_( false ) {}

   __property bool          DataExtractionReqEnabled = { read = DataExtractionReqEnabled_, write = DataExtractionReqEnabled_ };

};      

static const int MAX_REMOTE_MSGS = 52;
//---------------------------------------------------------------------------
class TRemoteMsgDef {
public:
   int        Id;
   AnsiString Desc;
   bool       Idle;
   bool       Test;
   bool       Traj;
   bool       Umg;
public:
   TRemoteMsgDef() : Id(0), Idle(false), Test(false), Traj(false), Umg(false) {}
   TRemoteMsgDef
      (
      const int        InId,
      const AnsiString &InDesc,
      const bool       InIdle,
      const bool       InTest,
      const bool       InTraj,
      const bool       InUmg
      ) :
      Id( InId ), Desc( InDesc), Idle( InIdle ), Test( InTest ), Traj( InTraj ), Umg( InUmg ) {}
   TRemoteMsgDef
      (
      const int        InId,
      const AnsiString &InDesc,
      const int        ValidModes
      ) :
      Id( InId ), Desc( InDesc)
      {
         Idle = ValidModes & ( (int) eIdle );
         Test = ValidModes & ( (int) eTest );
         Traj = ValidModes & ( (int) eTraj );
         Umg  = ValidModes & ( (int) eUmg );
      }
      bool const IsValidAnyMode() const
      {
         return( Idle | Test | Traj );
      }

};
#endif

//---------------------------------------------------------------------------
class TSendMsgsForm : public TForm
{
__published:
   TRzPanel *TopPnl;
   TRzPanel *ClientPnl;
   TRzPanel *BottomPnl;
   TRzBitBtn *DataExtractionReqBtn;
   TRzBitBtn *CloseBtn;
   TImage *Image1;
   TRzBitBtn *ChannelModeBtn;
   TRzBitBtn *ChanAssignBtn;
   TImageList *ButtonImages28x28;
   TImageList *Images128;
   TRzLabel *TopLbl;
   TRzLabel *SimModeLbl;
   TRzLabel *SimModeDesc;
   TRzBitBtn *ChanPwrBtn;
   TRzPanel *RemotMsgsTotalPnl;
   TRzSizePanel *NavBarSizePnl;
   TRzPanel *NavBarPnl;
   TdxNavBar *MessageNavBar;
   TdxNavBarGroup *ChanGrp;
   TdxNavBarGroup *RequestGrp;
   TdxNavBarGroup *EphAlmGrp;
   TdxNavBarGroup *ModelsGrp;
   TdxNavBarGroup *AtmoGrp;
   TdxNavBarGroup *SatVisGrp;
   TdxNavBarItem *SetTimeItm;
   TdxNavBarItem *InitializeSimulationItm;
   TdxNavBarItem *ChannelModeItm;
   TdxNavBarItem *CalInterchannelBiasesItm;
   TdxNavBarItem *SetChanPwrItm;
   TdxNavBarItem *RangeMaintItm;
   TdxNavBarItem *EphDataInputItm;
   TdxNavBarItem *AlmParamsInputItm;
   TdxNavBarItem *PowerProfileItm;
   TdxNavBarItem *TrajectoryItm;
   TdxNavBarItem *StatusReqItm;
   TdxNavBarItem *TimeReqItm;
   TdxNavBarItem *EphReqItm;
   TdxNavBarItem *DataExtReqItm;
   TdxNavBarItem *AlmReqItm;
   TdxNavBarItem *CalInputItm;
   TdxNavBarItem *StopSimItm;
   TdxNavBarItem *EphCorruptionItm;
   TdxNavBarItem *ClkCorruptionItm;
   TdxNavBarItem *PRangeNoiseItm;
   TdxNavBarItem *TropoParamsItm;
   TdxNavBarItem *UMGSimStartItm;
   TdxNavBarItem *PlatAttItm;
   TdxNavBarItem *AntGainPttrnItem;
   TdxNavBarItem *AircraftMaskItm;
   TdxNavBarItem *InitSysItm;
   TdxNavBarItem *ResetChanInterfaceItm;
   TdxNavBarItem *CalChannelControllersItm;
   TdxNavBarItem *PhaseLockStatReqItm;
   TdxNavBarItem *CalParamsReqItm;
   TdxNavBarItem *SatUseMapItm;
   TdxNavBarItem *FullInitItm;
   TdxNavBarItem *SubframeModItm;
   TdxNavBarItem *SetWeekItm;
   TdxNavBarItem *ChanAssignItm;
   TdxNavBarGroup *InitGrp;
   TdxNavBarGroup *StateUpdateGrp;
   TdxNavBarGroup *CalGrp;
   TdxNavBarGroup *SimHWGrp;
   TImageList *NavBarSmallImageList16x16;
   TImageList *NavBarLargeImageList32x32;
   TdxNavBarStyleItem *GroupGradientBackgroundStyle;
   void __fastcall DataExtractionReqBtnClick(TObject *Sender);
   void __fastcall ChanAssignBtnClick(TObject *Sender);
   void __fastcall ChannelModeBtnClick(TObject *Sender);

private:

   TInterface              * Interface_;
   TChanAssignForm         * ChanAssignForm;


public:

   __fastcall TSendMsgsForm( TComponent* Owner, TInterface * Interface );

   __fastcall ~TSendMsgsForm();


};
//---------------------------------------------------------------------------
extern PACKAGE TSendMsgsForm *SendMsgsForm;
//---------------------------------------------------------------------------
#endif
