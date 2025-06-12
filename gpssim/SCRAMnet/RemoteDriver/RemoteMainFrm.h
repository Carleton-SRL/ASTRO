//---------------------------------------------------------------------------

#ifndef RemoteMainFrmH
#define RemoteMainFrmH
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
#include "o32flxbn.hpp"
#include <Buttons.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "RzSplit.hpp"
#include "StShlCtl.hpp"
#include "RzEdit.hpp"
#include "RzSpnEdt.hpp"
#include <Mask.hpp>
#include "CSIntf.hpp"
#include "NavStateFram.h"
#include "InterfaceAcceptFram.h"
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------

//---------------------------------------------------------------------------

#ifndef VoyDefPfH
#include "VoyDefPf.h"
#endif

#ifndef NavStateFramH
#include "NavStateFram.h"
#endif

#ifndef VhTrthFlH
#include "VhTrthFl.h"
#endif

#ifndef GpibIntOptionsFramH
#include "GpibIntOptionsFram.h"
#endif

#ifndef EthernetIntOptionsFramH
#include "EthernetIntOptionsFram.h"
#endif

#ifndef SerialIntOptionsFramH
#include "SerialIntOptionsFram.h"
#endif

#ifndef RemoteTypesH
#include "RemoteTypes.h"
#endif

#ifndef ClosedLoopRunFrmH
#include "ClosedLoopRunFrm.h"
#endif

#ifndef RemoteDriverPfH
#include "RemoteDriverPf.h"
#endif

#ifndef InterfaceAcceptFramH
#include "InterfaceAcceptFram.h"
#endif


class TRemoteMainForm : public TForm
{
__published:	// IDE-managed Components
   TStatusBar *SelInterfacesb;
   TRzPanel *BottomPnl;
   TRzButton *CancelBtn;
   TRzButton *OKBtn;
   TRzPanel *ClientPnl;
   TRzSizePanel *InterfaceSizePnl;
   TRzPanel *LeftInterfacePnl;
   TRzPanel *RightInterfacePnl;
   TRzPanel *SelScenTopPnl;
   TOvcLabel *SelTypeLbl;
   TOvcLabel *SelLbl;
   TRzSizePanel *SelScenTreePnl;
   TRzPanel *SelScenListPnl;
   TStShellTreeView *SelScenTreeView;
   TO32FlexButton *SelTypeBtn;
   TOvcLabel *BuiltDispLbl;
   TOvcLabel *BuiltDateTimeLbl;
   TRzSizePanel *ListSizePnl;
   TStShellListView *SelScenListView;
   TRzSizePanel *NavStatePnl;
   TPageControl *NavStatePageCtrl;
   TTabSheet *StartSheet;
   TTabSheet *EndSheet;
   TNavStateFrame *StartNavStateFrame;
   TNavStateFrame *EndNavStateFrame;
   TRzPanel *BottomIntPnl;
   TRzSpinEdit *UpdateRateEdt;
   TOvcLabel *UpdateMsgTypeLbl;
   TRzSpinEdit *PreloadEdt;
   TOvcLabel *OvcLabel2;
   TRzPanel *IntTopPnl;
   TOvcLabel *OvcLabel1;
   TO32FlexButton *InterfaceFlexBtn;
   TOvcLabel *SimModeLbl;
   TO32FlexButton *SimModeBtn;
   TO32FlexButton *IntProtocolBtn;
   TOvcLabel *IntProtocolLbl;
   TCSGlobalObject *CSGlobalObject1;
   TInterfaceAcceptFrame *InterfaceAccept;
   void __fastcall CancelBtnClick(TObject *Sender);
   void __fastcall SelScenTreeViewFolderSelected(TObject *Sender,
          TStShellFolder *Folder);
   void __fastcall SelTypeBtnClick(TObject *Sender, int Item);
   void __fastcall SelTypeBtnItemChange(TObject *Sender, int &OldItem,
          int &NewItem);
   void __fastcall SelTypeBtnMenuClick(TObject *Sender, int &OldItem,
          int &NewItem);
   void __fastcall SelScenListViewItemSelected(TObject *Sender,
          TStShellItem *Item);
   void __fastcall InterfaceFlexBtnItemChange(TObject *Sender,
          int &OldItem, int &NewItem);
   void __fastcall InterfaceFlexBtnClick(TObject *Sender, int Item);
   void __fastcall InterfaceFlexBtnMenuClick(TObject *Sender, int &OldItem,
          int &NewItem);
   void __fastcall OKBtnClick(TObject *Sender);
   void __fastcall SelScenTreeViewDblClick(TObject *Sender);
private:

   TClosedLoopRunForm      * ClosedLoopRunForm;
   AnsiString                ScenVehPath;
   TStShellItem            * VehFileItem;
   TStShellFolder          * ScenFolder;
   bool                      ScenValid;
   bool                      VehFileValid;
   eSelType                  SelType;
   eIntType                  IntType;
   TFrame                  * IntOptionsFrame;
   TVehicleTruthFile       * VehicleTruthFile;
   VoyDefProfile           * VoyProfile;
   TRemoteDriverPf         * RemoteDriverPf;
   IAcceptInterfaceOptions * AcceptOptions;

   void                      ChangeSelVehFile(TStShellItem * Item);
   void                      DispInvalidScenSel();
   void                      DispInvalidVehFile();
   void                      DispSelVehFile(TStShellItem * Item);
   eIntType const            GetIntTypeFromItem(const int Item) const;
   eIntProtocol const        GetIntProtocolFromItem( const int Item ) const;
   bool const                IsScenValid(const AnsiString & ScenPath) const;
   bool const                IsVehFileValid(TStShellItem * VehFileItem);
   void                      SetIntType(const eIntType NewIntType);
   void                      SetNavStates(TVehicleTruthFile * NewVehTruthFile);		// User declarations
   void                      ChangeSelScen(TStShellFolder * NewFolder);
   void                      DispSelScen();
   eSelType const            GetSelTypeFromItem(const int ItemIndex) const;
   bool const                IsSelScen() const;
   bool const                IsSelVehFile() const;
   void                      SetSelType(const eSelType NewSelType);
   void                      SetSelTypeScen();
   void                      SetSelTypeVehFile();
   void                      StartRun();

public:

   __fastcall TRemoteMainForm(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TRemoteMainForm *RemoteMainForm;
//---------------------------------------------------------------------------
#endif
