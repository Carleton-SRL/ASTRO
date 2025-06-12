#include "pch.h"
#pragma hdrstop

#include "InMsg.h"

//---------------------------------------------------------------------------

#define MAX_NMEA_MSG_LENGTH (1000)

TInMsg::TInMsg
   (

   ) :
   Valid( false ),
   MsgComplete( false ),
   Fields( NULL )
{
}

TInMsg::~TInMsg()
{
   delete Fields;
}

TInMsg::TInMsg
   (
   const TInMsg & InMsg
   ) :
   Valid( false ),
   MsgComplete( false ),
   Fields( NULL )
{
   (*this) = InMsg;
}

TInMsg &
TInMsg::operator=
   (
   const TInMsg &rhs
   )
{
   if ( this == &rhs )
   {
      return( *this );
   }

   Valid       = rhs.Valid;
   MsgComplete = rhs.Valid;
   MsgStr      = rhs.MsgStr;

   delete Fields;
   Fields = new TStringList;
   for ( int i=0; i<rhs.Fields->Count; ++i )
   {
      Fields->Add( rhs.Fields->Strings[i] );
   }

   return( *this );

}


bool const
TInMsg::ProcessData
   (
   TMsgData & NewMsgData
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

         ProcessByte( (char) NewMsgData[i] ); // Checks for end/bad message

      }

      // Erase used bytes
      //
      TMsgData::iterator LastUsed = ( NewMsgData.begin() + i );
      NewMsgData.erase( NewMsgData.begin(), LastUsed );

   }

   return( IsMsgComplete() );

}


bool const
TInMsg::ProcessByte
   (
   const char Byte
   )
{

   if ( isascii(Byte) )
   {


      if ( Byte == '$' )
      {

         MsgStr      = "$";

         Valid = false;

      }
      else
      {

         MsgStr += Byte;

         if ( Byte == '\n' )
         {

            ProcessMsg();

         }
         else
         {
            Valid = false;
         }

         if ( MsgStr.length() > MAX_NMEA_MSG_LENGTH )
         {
            MsgStr = "";
            Valid = false;
         }

      }

   }

   return( IsValid() );

}

void
TInMsg::ProcessMsg
   (
   )
{

   if ( MsgHasChecksum( MsgStr ) )
   {
      Valid       = IsChecksumValid( MsgStr );
   }
   else
   {
      Valid = true;
   }

   if ( Valid )
   {
      delete Fields;
      Fields = new TStringList();
      ExtractTokensL( MsgStr.c_str(), AnsiString( ",*" ), '\'', true, Fields );
   }
   MsgComplete = true;

}

bool const
TInMsg::IsChecksumValid
   (
   const string &Msg
   ) const
{

   // Compute checksum of message
   //
   unsigned char Checksum = ComputeChecksum( Msg );

   // Get the checksum sent
   //
   string ChckStr = Msg.substr( Msg.find( '*' ) + 1 );

   unsigned int MsgChecksum=0;

   sscanf( ChckStr.c_str(), "%2X", &MsgChecksum );

   // return true if computed equals sent
   //
   return((unsigned char) MsgChecksum == Checksum);
}

bool const
TInMsg::MsgHasChecksum
   (
   const string &Msg
   ) const
{
   if ( Msg.find('*') < Msg.length() )
      return(true);
   else
      return(false);
}

const unsigned char
TInMsg::ComputeChecksum
   (
   const string &Msg
   ) const
{
   unsigned char Checksum=0;

   // Checksum after '$' and before '*'
   //
   for ( unsigned long i=Msg.find('$')+1; i<(min(Msg.find('*'),Msg.length())); ++i )
   {
      Checksum ^= Msg[i];
   }
   return(Checksum);
}

bool const
TInMsg::IsValid
   (

   ) const
{
   return(Valid);
}


AnsiString const
TInMsg::GetMsgId
   (
   ) const
{


   AnsiString MsgId;

   if ( IsMsgComplete() )
   {
      int FirstFieldLength = Fields->Strings[0].Length() - 1;
      MsgId = Fields->Strings[0].SubString( 2, FirstFieldLength );
   }
   return( MsgId );

}


bool const
TInMsg::IsTypeFound
   (
   const string & HeaderStr
   ) const
{

   bool Found = false;
   if ( MsgStr.find(HeaderStr) != string::npos )
   {

      Found = true;

   }

   return(Found);

}
void
TInMsg::Clear()
{

   MsgStr      = "";
   Valid       = false;
   MsgComplete = false;

}

AnsiString const
TInMsg::GetMsgData
   (
   ) const
{
   return( AnsiString( MsgStr.c_str() ) );
}

void
TInMsg::GetFields
   (
   TStringList *StringList
   ) const
{
   StringList->Clear();

   // Exclude MsgId and checksum
   //
   for ( int i=1; i<Fields->Count-1; ++i )
   {
      StringList->Add( Fields->Strings[i] );
   }
}




