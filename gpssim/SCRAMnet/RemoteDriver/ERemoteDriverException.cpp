#include "pch.h"
#pragma hdrstop

//---------------------------------------------------------------------------
//
// $Workfile:: ERemoteDriverException.cpp                                 $
//
// $Revision:: 1                                                     $
//
// $History:: ERemoteDriverException.cpp                                  $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 10/19/02   Time: 9:26p
//Created in $/RemoteDriver
//
//
//---------------------------------------------------------------------------


#ifndef ERemoteDriverExceptionH
#include "ERemoteDriverException.h"
#endif

#ifndef OperationErrorFrmH
#include "OperationErrorFrm.h"
#endif

bool ERemoteDriverException::ErrorFormShown_ = false;

//---------------------------------------------------------------------------

#pragma package(smart_init)

ERemoteDriverException::ERemoteDriverException
   (
   const AnsiString        & InExcStr,
   const bool                InShowErrorForm
   ) :
   Exception( InExcStr ),
   ExcStr_( InExcStr ),
   ShowErrorForm_( InShowErrorForm )
{

   CodeSite->SendMsg( ExcStr_ );
   
   if ( ShowErrorForm_ && !ErrorFormShown_ )
   {
      ErrorFormShown_                 = true;
      DisplayErrorForm();
   }

}

__fastcall
ERemoteDriverException::~ERemoteDriverException
   (
   )
{
}

void
ERemoteDriverException::DisplayErrorForm
   (
   )
{

   TOperationErrorForm * ErrorForm = new TOperationErrorForm( Application, ExcStr_, false );
   ErrorForm->GeneralErrorCaption  = AnsiString( "Exception Error" );
   ErrorForm->ShowModal();
   delete ErrorForm;

}
 