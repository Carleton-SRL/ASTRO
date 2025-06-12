#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
// ClassExplorer Pro generated source file
// Created by Michael Wade on 2/3/2002, 8:14:32 PM
//---------------------------------------------------------------------------
#include "InMsg.h"

//---------------------------------------------------------------------------


TInMsg::TInMsg
   (

   ) :
   ValidMsg_( false ),
   BadMsg_( false ),
   MsgId_( 0 ),
   MsgByteCount_( 0 )
{
   Clear();
}

void
TInMsg::Clear()
{
   ValidMsg_     = false;
   BadMsg_       = false;
   MsgId_        = 0;
   MsgByteCount_ = 0;
   MsgData_.clear();
}

TInMsg::TInMsg
   (
   const TInMsg            & InMsg
   )
{
   ( *this ) = InMsg;
}

TInMsg &
TInMsg::operator=
   (
   const TInMsg            & InMsg
   )
{
   if ( this == &InMsg ) return( *this );

   ValidMsg_               = InMsg.ValidMsg_;
   BadMsg_                 = InMsg.BadMsg_;
   MsgId_                  = InMsg.MsgId_;
   MsgByteCount_           = InMsg.MsgByteCount_;
   MsgData_                = InMsg.MsgData_;

   return( *this );

}

bool const
TInMsg::IsMsgValid
   (

   ) const
{
   return( ValidMsg_ );
}

bool const
TInMsg::IsMsgBad
   (

   ) const
{
   return( BadMsg_ );
}

bool const
TInMsg::IsMsgComplete
   (

   ) const
{
   return( IsMsgValid() || IsMsgBad() );
}


void
TInMsg::GetMsg
   (
   TMsgData & Msg
   )
{
   Msg = MsgData_;
}

TMsgBody const
TInMsg::GetMsgBody
   (
   ) const
{
   TMsgBody MsgBody;

   MsgBody.assign( (TMsgBody::iterator) ( MsgData_.begin() + 2 ), (TMsgBody::iterator) ( MsgData_.end() - 1 ) );

   return( MsgBody );
}


bool const
TInMsg::ProcessData
   (
   TMsgData                & NewMsgData
   )
{

   if ( !NewMsgData.empty() )
   {
                                                                                  
      // Add a byte at a time, checking for valid or bad message each byte.
      // Remove each byte as it is used.
      //
      unsigned int i; // Outside loop as needed to erase used bytes

      for ( i=0; i<NewMsgData.size() && !IsMsgComplete(); ++i )
      {

         AddByte( NewMsgData[i] ); // Checks for end/bad message

      }

      // Erase used bytes
      //
      TMsgData::iterator LastUsed = ( NewMsgData.begin() + i );
      NewMsgData.erase( NewMsgData.begin(), LastUsed );

   }

   return( IsMsgComplete() );

}

void
TInMsg::AddByte
   (
   const unsigned char Byte
   )
{
   MsgData_.push_back( Byte );

   MsgId_ = MsgData_[0];

   if ( MsgData_.size() > 1 )
   {

      MsgByteCount_ = MsgData_[1];

      if ( (int) MsgData_.size() == MsgByteCount_ )
      {
         ValidMsg_ = IsChecksumValid();
         BadMsg_   = !ValidMsg_;
      }

   }

}

bool const
TInMsg::IsChecksumValid
   (
   ) const
{

   if ( MsgData_.empty() ) return( false );

   // All bytes including checksum should add to 0
   //
   unsigned char Sum=0;
   for ( unsigned int i=0; i<MsgData_.size()-1; ++i )
   {
      Sum += MsgData_[i];
   }
   Sum += (char) MsgData_[ MsgData_.size()-1 ];

   return( Sum == 0 );

}


unsigned char const
TInMsg::ComputeChecksum
   (
   const TMsgData          & Data
   )
{
   unsigned char sum=0;

   for ( unsigned int i=0; i<Data.size(); ++i )
   {
      sum = (unsigned char) ( sum + Data[i] );
   }
   sum = (unsigned char)(-sum);

   return ( sum );
}

