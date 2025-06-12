#include "pch.h"
#pragma hdrstop

#include "OutMsg.h"

//---------------------------------------------------------------------------


bool TOutMsg::ShouldAppendChecksum = true;

TOutMsg::TOutMsg
   (
   
   )
{
    //TODO: Add your source code here
}

unsigned char const
TOutMsg::ComputeChecksum
   (
   const string & Str
   ) const
{
   unsigned char Checksum=0;

   // Checksum after '$' and before '*'
   //
   for ( unsigned long i=Str.find('$')+1; i<(min(Str.find('*'),Str.length())); ++i )
   {
      Checksum ^= Str[i];
   }
   return(Checksum);
}

void
TOutMsg::AppendChecksum
   (
   string & Str
   ) const
{
   Str += '*';
   unsigned char Checksum = ComputeChecksum(Str);

   char TmpStr[100];
   sprintf(TmpStr,"%2.2X\r\n",Checksum);
   Str += TmpStr;

}


void
TOutMsg::GetBody
   (
   string & Out
   )
{
   Out = MsgData;
}


void
TOutMsg::SetBody
   (
   const string & MsgBody
   )
{
   MsgData = MsgBody;
   if ( ShouldAppendChecksum )
   {
      AppendChecksum( MsgData );
   }
   else
   {
      AddEnd( MsgData );
   }
}

void
TOutMsg::AddEnd
   (
   string & Str
   ) const
{
   char TmpStr[100];
   sprintf( TmpStr, "\r\n" );
   Str += TmpStr;
}   

TMsgData const
TOutMsg::GetMsgData() const
{

   TMsgData OutMsgData;

   for ( unsigned int i=0; i<MsgData.length(); ++i )
   {
      OutMsgData.push_back( MsgData[i] );
   }

   return( OutMsgData );

}


 