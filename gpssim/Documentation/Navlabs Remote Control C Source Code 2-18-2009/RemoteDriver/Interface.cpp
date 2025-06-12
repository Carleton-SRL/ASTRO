#include "pch.h"
#pragma hdrstop

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

#ifndef InterfaceH
#include "Interface.h"
#endif

#ifndef GpibH
#include "Gpib.h"
#endif

#ifndef EthernetH
#include "Ethernet.h"
#endif

TInterface::TInterface
   (
   const TInterfaceParams  & InInterfaceParams
   ) :
   ValidInterface_( false ),
   InterfaceThread_( NULL ),
   Thread_( NULL ),
   InterfaceParams_( InInterfaceParams )
{

   ThreadDataCom_                             = new TThreadDataCom( 10, 10, "Interface" );

   if ( InterfaceParams_.Gpib )
   {
      TGpibThread * pGpib                     = new TGpibThread( InterfaceParams_.GpibParams, ThreadDataCom_ );
      InterfaceThread_                        = pGpib;
      Thread_                                 = pGpib;
      Thread_->Resume();
   }
   else if ( InterfaceParams_.Ethernet )
   {
      TEthernetParams EthernetParams          = InterfaceParams_.EthernetParams;
      if ( EthernetParams.Client )
      {
         TEthernetClientThread * pEthernetClient = new TEthernetClientThread( InterfaceParams_.EthernetParams, ThreadDataCom_ );
         InterfaceThread_                        = pEthernetClient;
         Thread_                                 = pEthernetClient;
         Thread_->Resume();
      }
      else
      {
         TEthernetServer * pEthernetServer       = new TEthernetServer( InterfaceParams_.EthernetParams, ThreadDataCom_ );
         InterfaceThread_                        = pEthernetServer;
         Thread_                                 = NULL;
      }
   }

   ValidInterface_                            = InterfaceThread_->Valid;

}

AnsiString const
TInterface::GetStatusStr
   (
   )
{
   return( ( InterfaceThread_ ? InterfaceThread_->StatusStr : AnsiString() ) );
}

AnsiString const
TInterface::GetParametersStr
   (
   )
{
   return( ( InterfaceThread_ ? InterfaceThread_->ParametersStr : AnsiString() ) );
}

bool const
TInterface::InitCommunication
   (
   )
{

   return( InterfaceThread_->InitCommunication() );

}

void
TInterface::SendData
   (
   const TMsgData          & Data
   )
{

   if ( Data.size() )
   {

      ThreadDataCom_->SendData = Data;

   }

}

TMsgData const
TInterface::GetData
   (
   )
{

   return( ThreadDataCom_->ReceivedData );

}

__fastcall
TInterface::~TInterface
   (

   )
{
   if ( Thread_ )
   {
      Thread_->Terminate();
      Thread_->WaitFor();
   }
   if ( InterfaceThread_ )
   {
      delete InterfaceThread_;
      InterfaceThread_ = NULL;
   }
   delete ThreadDataCom_;
   ThreadDataCom_  = NULL;

}

bool const
TInterface::IsValid
   (
   ) const
{
   return( ValidInterface_ );
}   

__fastcall IInterfaceThread::~IInterfaceThread()
{
}

