#include "pch.h"
#pragma hdrstop

//---------------------------------------------------------------------------
//
// $Workfile:: ChanAssignFrm.cpp                                     $
//
// $Revision:: 1                                                     $
//
// $History:: ChanAssignFrm.cpp                                      $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 11/16/02   Time: 9:31p
//Created in $/RemoteDriver
//
//
//---------------------------------------------------------------------------


#ifndef ChanAssignFrmH
#include "ChanAssignFrm.h"
#endif

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ovclabel"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzRadGrp"
#pragma link "RzSpnEdt"
#pragma resource "*.dfm"
TChanAssignForm *ChanAssignForm;
//---------------------------------------------------------------------------
__fastcall
TChanAssignForm::TChanAssignForm
   (
   TComponent              * Owner,
   TInterface              * InInterface
   ) :
   TForm( Owner ),
   Interface_( InInterface )
{
   ChanAssignFunctionrg->ItemIndex = 0;
   Param3Lbl->Visible              = false;
   Param3Spinner->Visible          = false;
}
//---------------------------------------------------------------------------
void __fastcall
TChanAssignForm::ChanAssignFunctionrgClick
   (
   TObject                 * Sender
   )
{

   TStelChanAssignFunc LocalChanAssignFunc;

   LocalChanAssignFunc.DeassignChanA   = ( ChanAssignFunctionrg->ItemIndex == 0 );
   LocalChanAssignFunc.SwapChanAChanB  = ( ChanAssignFunctionrg->ItemIndex == 1 );
   LocalChanAssignFunc.ChanASvidAssign = ( ChanAssignFunctionrg->ItemIndex == 2 );

   SetParam3( LocalChanAssignFunc );

}

void
TChanAssignForm::SetParam3
   (
   const TStelChanAssignFunc & InStelChanAssignFunc
   )
{

   if ( !( InStelChanAssignFunc.DeassignChanA ) )
   {

      Param3Lbl->Visible     = true;
      Param3Spinner->Visible = true;
      const bool SwapChans   = ( InStelChanAssignFunc.SwapChanAChanB );
      Param3Spinner->Min     = ( SwapChans ? 0 : 1 );
      Param3Spinner->Max     = ( SwapChans ? 13 : 32 );
      Param3Lbl->Caption     = ( SwapChans ? AnsiString( "Channel ID B:" ) : AnsiString( "Satellite ID:" ) );

   }
   else
   {
      Param3Lbl->Visible     = false;
      Param3Spinner->Visible = false;
   }

}

TStelChanAssignData const
TChanAssignForm::GetChanAssignData
   (
   ) const
{

   TStelChanAssignData Data;

   Data.ChanAssignFunc     = ChanAssignFunc;
   Data.ChanA              = ChanA;
   Data.ChanB              = ChanB;
   Data.Svid               = Svid;

   return( Data );

}

void
TChanAssignForm::SetChanAssignData
   (
   const TStelChanAssignData & Data
   )
{

   SetParam3( Data.ChanAssignFunc );

   ChanA                    = Data.ChanA;

   Param3Spinner->Value = Data.ChanAssignFunc.SwapChanAChanB ? Data.ChanB : Data.Svid;

   SetParam3( Data.ChanAssignFunc );

}

TStelChanAssignFunc const
TChanAssignForm::GetChanAssignFunc
   (
   ) const
{
   TStelChanAssignFunc LocalChanAssignFunc;

   LocalChanAssignFunc.DeassignChanA    = ( ChanAssignFunctionrg->ItemIndex == 0 );
   LocalChanAssignFunc.SwapChanAChanB   = ( ChanAssignFunctionrg->ItemIndex == 1 );
   LocalChanAssignFunc.ChanASvidAssign  = ( ChanAssignFunctionrg->ItemIndex == 2 );

   return( LocalChanAssignFunc );

}

int const
TChanAssignForm::GetChanA
   (
   ) const
{
   return( ChanASpinner->Value );
}

void
TChanAssignForm::SetChanA
   (
   const int                 InChanA
   )
{
   ChanASpinner->Value     = InChanA;
}

int const
TChanAssignForm::GetChanB
   (
   ) const
{
   return( Param3Spinner->Value );
}

void
TChanAssignForm::SetChanB
   (
   const int                 InChanB
   )
{
   Param3Spinner->Value    = InChanB;
}

int const
TChanAssignForm::GetSvid
   (
   ) const
{
   return( Param3Spinner->Value );
}

void
TChanAssignForm::SetSvid
   (
   const int                 InSvid
   )
{
   Param3Spinner->Value    = InSvid;
}

TStelOut
TChanAssignForm::GetOutMsg
   (
   )
{

   return( TStelChannelAssignment( ChanAssignData ) );

}

void __fastcall
TChanAssignForm::SendBtnClick
   (
   TObject                 * Sender
   )
{

   TOutMsg LocalOutMsg     = OutMsg;

   Interface_->SendMsgData = LocalOutMsg.MsgData;

}
//---------------------------------------------------------------------------

void __fastcall
TChanAssignForm::CancelBtnClick
   (
   TObject                 * Sender
   )
{
   Visible = false;
}
//---------------------------------------------------------------------------

