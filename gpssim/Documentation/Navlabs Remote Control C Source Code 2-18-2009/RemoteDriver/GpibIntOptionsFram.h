//---------------------------------------------------------------------------


#ifndef GpibIntOptionsFramH
#define GpibIntOptionsFramH
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
#include "RzEdit.hpp"
#include "RzSpnEdt.hpp"
#include <Mask.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------

#ifndef RemoteDriverPfH
#include "RemoteDriverPf.h"
#endif

#ifndef AcceptInterfaceOptionsH
#include "AcceptInterfaceOptions.h"
#endif

//---------------------------------------------------------------------------
class TGpibIntOptionsFrame : public TFrame, public IAcceptInterfaceOptions
{
__published:
   TRzPanel *GpibTopPnl;
   TOvcLabel *GpibTitle;
   TRzPanel *GpibMainPnl;
   TOvcLabel *BoardIndexDescLbl;
   TRzSpinEdit *BoardIndexSpinEdit;
   TOvcLabel *PrimaryAddrDescLbl;
   TRzSpinEdit *PrimaryAddrSpinEdit;
   TRzButton *TestBtn;
   TOvcLabel *TestResultsDescLbl;
   TOvcLabel *TestResultsLbl;
   TRzMemo *TestResultsDetailsMemo;
   TImage *GpibImage;
   void __fastcall TestBtnClick(TObject *Sender);
private:

   bool                      ValidInterface_;
   TRemoteDriverPf         * RemoteDriverPf;

   void                      SetDisplayFromProfile();
   void                      SetProfileFromDisplay();

public:

   __fastcall                TGpibIntOptionsFrame( TComponent* Owner );
   virtual __fastcall       ~TGpibIntOptionsFrame();

   void                      DoNewOptions( const bool Accept );
   bool const                GetOptionsChanged();


   __property bool     ValidInterface      = { read = ValidInterface_                };

};
//---------------------------------------------------------------------------
extern PACKAGE TGpibIntOptionsFrame *GpibIntOptionsFrame;
//---------------------------------------------------------------------------
#endif
