//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop

//---------------------------------------------------------------------------
//
// $Workfile:: DataExtractionReqFrm.cpp                              $
//
// $Revision:: 1                                                     $
//
// $History:: DataExtractionReqFrm.cpp                               $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 9/28/02    Time: 7:35p
//Created in $/RemoteDriver
//
//
//---------------------------------------------------------------------------


#include "DataExtractionReqFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ovclabel"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzRadChk"
#pragma resource "*.dfm"
TDataExtractionReqForm *DataExtractionReqForm;
//---------------------------------------------------------------------------
__fastcall
TDataExtractionReqForm::TDataExtractionReqForm
   (
   TComponent        * Owner,
   const bool          InEnabled
   ) :
   TForm( Owner ),
   ReqEnabled_( InEnabled )
{

   Enabledcb->Checked = ReqEnabled_;

}
//---------------------------------------------------------------------------
