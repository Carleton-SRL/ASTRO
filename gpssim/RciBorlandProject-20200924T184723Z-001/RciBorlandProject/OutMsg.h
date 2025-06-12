#ifndef OutMsgH
#define OutMsgH

#include "RemoteTypes.h"
//---------------------------------------------------------------------------
class TOutMsg {
private:
protected:
   AnsiString MsgId;
   string MsgData;
   unsigned char const ComputeChecksum(const string & Str) const;
   void AppendChecksum(string & Str) const;
   void AddEnd( string & Str ) const;

   static bool ShouldAppendChecksum;
public:
   TOutMsg();

   TMsgData const GetMsgData() const;
   void GetBody(string & Out);
   void SetBody(const string & MsgBody);
   AnsiString const GetMsgId() const { return( MsgId ); }
   AnsiString const GetMsgStr() const { return( AnsiString( MsgData.c_str() ) ); }

   static void SetShouldAppendChecksum( const bool InShouldAppendChecksum )
   {
      ShouldAppendChecksum = InShouldAppendChecksum;
   }
   static bool const IsShouldAppendChecksum() { return( ShouldAppendChecksum ); }
};

typedef queue<TOutMsg> TOutMsgQueue;

//---------------------------------------------------------------------------
#endif

 