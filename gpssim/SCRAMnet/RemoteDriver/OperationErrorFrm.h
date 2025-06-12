//---------------------------------------------------------------------------

#ifndef OperationErrorFrmH
#define OperationErrorFrmH
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//
// $Workfile:: OperationErrorFrm.h                                   $
//
// $Revision:: 5                                                     $
//
// $History:: OperationErrorFrm.h                                    $
//
//*****************  Version 5  *****************
//User: Michael Wade Date: 10/19/02   Time: 10:41p
//Updated in $/TapMsec
//Enable change of top label
//
//*****************  Version 4  *****************
//User: Michael Wade Date: 7/28/02    Time: 11:20a
//Updated in $/TapMsec
//Use #ifndef instead of #ifdef for BUILDER_INCLUDES
//
//*****************  Version 3  *****************
//User: Michael Wade Date: 7/23/02    Time: 7:48p
//Updated in $/TapMsec
//Added Source Safe keywords
//BUILDER_INCLUDES ifdef
//
//
//---------------------------------------------------------------------------
//------------------------------------------------------------------------------
#ifndef BUILDER_INCLUDES
//------------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ovclabel.hpp"
#include "RzDlgBtn.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzButton.hpp"
#include "RzRadChk.hpp"
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
//---------------------------------------------------------------------------
class TOperationErrorForm : public TForm
{
__published:
   TRzPanel *BottomPnl;
   TRzPanel *TopClientPnl;
   TRzDialogButtons *Buttons;
   TRzPanel *TopPnl;
   TRzLabel *RzLabel1;
   TOvcLabel *GeneralErrorLbl;
   TRzPanel *ClientPnl;
   TScrollBox *ErrorStrScrollBox;
   TOvcLabel *ErrorSpecificLbl;
   void __fastcall ButtonsClickOk(TObject *Sender);
   void __fastcall ButtonsClickCancel(TObject *Sender);
private:

   AnsiString                ErrorSpecificStr_;
   const bool                PromptToContinue_;
   bool                      Continue_;

   AnsiString const          GetGeneralErrorCaption() const;
   void                      SetGeneralErrorCaption( const AnsiString & InGeneralErrorCaption );
   AnsiString const          GetErrorStr() const;
   void                      SetErrorStr( const AnsiString & ErrorStr );
   bool const                GetContinue() const;

public:

   __fastcall TOperationErrorForm
      (
      TComponent           * Owner,
      const AnsiString     & InErrorSpecificStr    = "",
      const bool             PromptToContinue      = false
      );

   __property AnsiString GeneralErrorCaption      = { read = GetGeneralErrorCaption, write = SetGeneralErrorCaption  };
   __property AnsiString ErrorStr                 = { read = GetErrorStr,            write = SetErrorStr             };
   __property bool       Continue                 = { read = GetContinue                                             };

};
//---------------------------------------------------------------------------
extern PACKAGE TOperationErrorForm *OperationErrorForm;
//---------------------------------------------------------------------------
#endif
