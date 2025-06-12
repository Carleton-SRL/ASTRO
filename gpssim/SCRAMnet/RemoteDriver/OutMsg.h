//---------------------------------------------------------------------------
// ClassExplorer Pro generated header file
// Created by Michael Wade on 2/4/2002, 10:01:40 PM
//---------------------------------------------------------------------------
#ifndef OutMsgH
#define OutMsgH

#include "StelMsgs.h"
//---------------------------------------------------------------------------
class TOutMsg {
private:

   unsigned char             MsgId_;
   TMsgData                  MsgData_;

   TMsgData const            GetMsgData() const { return( MsgData_ ); }

protected:

   void                      AddChecksum();

public:

   TOutMsg( const TStelOut &StelOut );
   TOutMsg();
   TOutMsg( const TMsgData & InMsgData );
   TOutMsg( const int MsgId, const TMsgBody &MsgBody );
   TOutMsg & operator =(const TMsgData & InMsgData);
   TOutMsg & operator =( const TStelOut & InStelOut );
   void Clear();


   static unsigned char const ComputeChecksum( const TMsgData & Data );

   __property unsigned char MsgId    = { read = MsgId_                };
   __property TMsgData      MsgData  = { read = GetMsgData            };

};
typedef std::queue<TOutMsg>    TOutMsgQueue;

class TOutMsgQ {
private:

   TOutMsgQueue              OutMsgQueue_;
   TMsgData                  MsgData_;

public:

   TOutMsgQ() {}

   void push( const TOutMsg & OutMsg )
   {
      OutMsgQueue_.push( OutMsg );
      TMsgData OutMsgData = OutMsg.MsgData;
      MsgData_.insert( MsgData_.end(), OutMsgData.begin(), OutMsgData.end() );
   }

   TOutMsg const front()
   {
      return( OutMsgQueue_.front() );
   }

   unsigned int const size() const
   {
      return( OutMsgQueue_.size() );
   }

   void pop()
   {
      OutMsgQueue_.pop();
   }

   __property TMsgData   MsgData     = { read = MsgData_             };

};


//---------------------------------------------------------------------------
#endif
