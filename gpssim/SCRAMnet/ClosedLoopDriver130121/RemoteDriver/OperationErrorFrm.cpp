#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
//
// $Workfile:: OperationErrorFrm.cpp                                 $
//
// $Revision:: 5                                                     $
//
// $History:: OperationErrorFrm.cpp                                  $
//
//*****************  Version 5  *****************
//User: Michael Wade Date: 10/19/02   Time: 10:41p
//Updated in $/TapMsec
//Enable change of top label
//
//*****************  Version 4  *****************
//User: Michael Wade Date: 7/28/02    Time: 10:00p
//Updated in $/TapMsec
//Added include file guards
//
//*****************  Version 3  *****************
//User: Michael Wade Date: 7/23/02    Time: 7:48p
//Updated in $/TapMsec
//Added Source Safe keywords
//BUILDER_INCLUDES ifdef
//
//
//---------------------------------------------------------------------------

#ifndef OperationErrorFrmH
#include "OperationErrorFrm.h"
#endif
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ovclabel"
#pragma link "RzDlgBtn"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzRadChk"
#pragma resource "*.dfm"
TOperationErrorForm *OperationErrorForm;
//---------------------------------------------------------------------------

static const AnsiString GeneralErrorContinueStr
   (
   "There has been an error in the system.  "
   "This error may or may not render the simulation unrunnable.  "
   "Do you wish to attempt to run the simulation?" );

static const AnsiString GeneralErrorCannotContinueStr
   (
   "There has been an error in the system.  "
   );

__fastcall
TOperationErrorForm::TOperationErrorForm
   (
   TComponent              * Owner,
   const AnsiString        & InErrorSpecificStr,
   const bool                InPromptToContinue
   ) :
   TForm( Owner ),
   ErrorSpecificStr_( InErrorSpecificStr ),
   PromptToContinue_( InPromptToContinue ),
   Continue_( false )
{

   ErrorStr = InErrorSpecificStr;

   if ( !PromptToContinue_ )
   {
      GeneralErrorCaption         = GeneralErrorCannotContinueStr;
      Buttons->CaptionOk          = "OK";
      Buttons->ShowCancelButton   = false;
      Buttons->EnableCancel       = false;
   }
   else
   {
      GeneralErrorCaption         = GeneralErrorContinueStr;
      Buttons->CaptionOk          = "Yes";
      Buttons->ShowCancelButton   = true;
      Buttons->EnableCancel       = true;
   }

}

void
TOperationErrorForm::SetErrorStr
   (
   const AnsiString        & InErrorStr
   )
{

   ErrorSpecificStr_         = InErrorStr;
   ErrorSpecificLbl->Caption = ErrorSpecificStr_;

}

AnsiString const
TOperationErrorForm::GetErrorStr
   (
   ) const
{
   return( ErrorSpecificStr_ );
}   

AnsiString const
TOperationErrorForm::GetGeneralErrorCaption
   (
   ) const
{
   return( GeneralErrorLbl->Caption );
}

void
TOperationErrorForm::SetGeneralErrorCaption
   (
   const AnsiString        & InGeneralErrorCaption
   )
{
   GeneralErrorLbl->Caption = InGeneralErrorCaption;
}

bool const
TOperationErrorForm::GetContinue
   (
   ) const
{

   return( PromptToContinue_ && Continue_ );

}
//---------------------------------------------------------------------------
void __fastcall
TOperationErrorForm::ButtonsClickOk
   (
   TObject *Sender
   )
{

   if ( PromptToContinue_ )
   {
      Continue_ = true;
   }

   ModalResult = mrYes;

}
//---------------------------------------------------------------------------
void __fastcall
TOperationErrorForm::ButtonsClickCancel
   (
   TObject *Sender
   )
{

   ModalResult = mrNo;

}
//---------------------------------------------------------------------------


