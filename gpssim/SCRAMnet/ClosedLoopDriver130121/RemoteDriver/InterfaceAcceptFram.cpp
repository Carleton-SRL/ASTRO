#include "pch.h"
#pragma hdrstop

//---------------------------------------------------------------------------
//
// $Workfile:: InterfaceAcceptFram.cpp                               $
//
// $Revision:: 1                                                     $
//
// $History:: InterfaceAcceptFram.cpp                                $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 10/03/02   Time: 9:14p
//Created in $/RciDriver
//Add ethernet and Monte Carlo trials
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 9/29/02    Time: 6:54p
//Created in $/TapRci
//Initial check in
//
//
//---------------------------------------------------------------------------


#ifndef InterfaceAcceptFramH
#include "InterfaceAcceptFram.h"
#endif


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "ovclabel"
#pragma link "RzButton"
#pragma resource "*.dfm"
TInterfaceAcceptFrame *InterfaceAcceptFrame;
//---------------------------------------------------------------------------
__fastcall
TInterfaceAcceptFrame::TInterfaceAcceptFrame
   (
   TComponent              * Owner
   ) :
   TFrame( Owner ),
   AcceptInterfaceOptions( NULL )
{
   InterfaceAcceptOptionsTimer->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall
TInterfaceAcceptFrame::AcceptInterfaceBtnClick
   (
   TObject                 * Sender
   )
{

   if ( AcceptInterfaceOptions_ )
   {
      AcceptInterfaceOptions_->DoNewOptions( true );
   }

}
//---------------------------------------------------------------------------
void __fastcall
TInterfaceAcceptFrame::CancelInterfaceBtnClick
   (
   TObject                 * Sender
   )
{

   if ( AcceptInterfaceOptions_ )
   {
      AcceptInterfaceOptions_->DoNewOptions( false );
   }

}
//---------------------------------------------------------------------------
void __fastcall
TInterfaceAcceptFrame::InterfaceAcceptOptionsTimerTimer
   (
   TObject                 * Sender
   )
{
   AcceptInterfaceBtn->Enabled = AcceptInterfaceOptions_ ? AcceptInterfaceOptions_->OptionsChanged : false;
   CancelInterfaceBtn->Enabled = AcceptInterfaceOptions_ ? AcceptInterfaceOptions_->OptionsChanged : false;
}
//---------------------------------------------------------------------------
