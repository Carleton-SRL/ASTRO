#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
// ClassExplorer Pro generated source file
// Created by Michael Wade on 2/4/2002, 10:01:40 PM
//---------------------------------------------------------------------------

#include "RemoteTypes.h"
#include "OutMsg.h"

//---------------------------------------------------------------------------



TOutMsg::TOutMsg
   (

   )
{
   Clear();
}

TOutMsg::TOutMsg
   (
   const TStelOut & StelOut
   )
{

   ( *this ) = StelOut;

}

TOutMsg &
TOutMsg::operator=
   (
   const TStelOut & StelOut
   )
{

   Clear();
   MsgId_           = StelOut.GetMsgId();
   TMsgBody MsgBody = StelOut.GetMsgBody();

   MsgData_.push_back( MsgId_ );
   MsgData_.push_back( MsgBody.size() + 3 );
   MsgData_.insert( MsgData_.end(), MsgBody.begin(), MsgBody.end() );
   AddChecksum();

   return( *this );

}

TOutMsg::TOutMsg
   (
   const TMsgData & InMsgData
   )
{

   ( *this ) = InMsgData;

}

TOutMsg &
TOutMsg::operator =
   (
   const TMsgData          & InMsgData
   )
{

   if ( InMsgData.empty() )
   {
      Clear();
   }
   else
   {

      MsgData_ = InMsgData;
      MsgId_   = MsgData_[0];
      AddChecksum();

   }

   return( *this );

}
TOutMsg::TOutMsg
   (
   const int                 InMsgId,
   const TMsgBody          & MsgBody
   )
{

   Clear();
   MsgId_ = InMsgId;
   MsgData_.push_back( MsgId_ );
   MsgData_.push_back( MsgBody.size() + 3 );
   MsgData_.insert( MsgData_.end(), MsgBody.begin(), MsgBody.end() );
   AddChecksum();

}

void
TOutMsg::AddChecksum
   (

   )
{

   MsgData_.push_back( ComputeChecksum( MsgData_ ) );

}

unsigned char const
TOutMsg::ComputeChecksum
   (
   const TMsgData          & Data
   )
{
   unsigned char sum = 0;

   for ( unsigned int i=0; i<Data.size(); ++i )
   {
      sum = (unsigned char) ( sum + Data[i] );
   }
   sum = (unsigned char)(-sum);

   return ( sum );
}

void
TOutMsg::Clear
   (

   )
{
   MsgId_    = 0;
   MsgData_.clear();
}


