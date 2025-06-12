//---------------------------------------------------------------------------
// ClassExplorer Pro generated header file
// Created by Michael Wade on 2/3/2002, 8:14:32 PM
//---------------------------------------------------------------------------
#ifndef InMsgH
#define InMsgH

#ifndef RemoteTypesH
#include "RemoteTypes.h"
#endif

//---------------------------------------------------------------------------
// TInMsg
//
//   Input message from simulator.  Format:
// Byte              Description
//   0                MsgId
//   1                ByteCount = Total number of bytes including MsgId, ByteCount, and Checksum
//   2..ByteCount-3   Data
//   ByteCount-1      Checksum = Adding all bytes in message and take 2's complete.
//
class TInMsg {
private:
   bool                      ValidMsg_;
   bool                      BadMsg_;
   unsigned char             MsgByteCount_;
   unsigned char             MsgId_;
   TMsgData                  MsgData_;

   void                      AddByte( const unsigned char Byte );
   bool const                IsChecksumValid() const;
   bool const                IsMsgValid()      const;
   bool const                IsMsgBad()        const;
   bool const                IsMsgComplete()   const;
   int const                 GetMsgId() const { return( MsgId_ ); }
   TMsgData const            GetMsgData() const { return( MsgData_ ); }
   TMsgBody const            GetMsgBody() const;

public:
   TInMsg();
   TInMsg( const TInMsg & );

   TInMsg & operator=( const TInMsg & );

   bool const                ProcessData( TMsgData & MoreMsgData );
   void                      GetMsg( TMsgData & Msg );
   void                      Clear();


   static unsigned char const ComputeChecksum(const TMsgData &Data);

   __property bool       MsgValid     = { read = IsMsgValid      };
   __property bool       MsgBad       = { read = IsMsgBad        };
   __property bool       MsgComplete  = { read = IsMsgComplete   };
   __property int        MsgId        = { read = GetMsgId        };
   __property TMsgBody   MsgBody      = { read = GetMsgBody      };
   __property TMsgData   MsgData      = { read = GetMsgData      };

};

typedef std::queue<TInMsg> TInMsgQueue;
typedef std::vector<TInMsg> TInMsgArray;

//---------------------------------------------------------------------------
#endif
