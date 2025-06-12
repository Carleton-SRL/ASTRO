//---------------------------------------------------------------------------
// ClassExplorer Pro generated header file
// Created by Michael Wade on 8/11/99, 10:44:28 AM
//---------------------------------------------------------------------------
#ifndef InMsgH
#define InMsgH

#include "RemoteTypes.h"

//---------------------------------------------------------------------------
class TInMsg {
private:
   bool Valid;
   bool MsgComplete;
   TStringList *Fields;
protected:
   bool const IsChecksumValid(const string &Msg) const;
   bool const MsgHasChecksum(const string &Msg) const;
   unsigned char const ComputeChecksum(const string &Msg) const;
   void ProcessMsg();
public:
   TInMsg();
   TInMsg( const TInMsg & );
   virtual ~TInMsg();
   string MsgStr;
   bool const ProcessByte(const char);
   bool const IsValid() const;
   bool const IsMsgComplete() const { return( MsgComplete ); }
   bool const ProcessData( TMsgData & MoreMsgData );
   void Clear();
   AnsiString const GetMsgId() const;
   AnsiString const GetMsgData() const;
   void GetFields( TStringList * ) const;
   bool const IsTypeFound(const string & HeaderStr) const;

   TInMsg & operator=( const TInMsg & InMsg );

};

typedef queue<TInMsg> TInMsgQueue;
typedef vector<TInMsg> TInMsgArray;

//---------------------------------------------------------------------------
#endif

 