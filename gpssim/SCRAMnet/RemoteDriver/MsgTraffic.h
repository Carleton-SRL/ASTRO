#ifndef MsgTrafficH
#define MsgTrafficH


typedef enum { eMSG_SOURCE_SIM, eMSG_SOURCE_CTLR } eMSG_SOURCE;

class TMsgTraffic {
private:

   int                       MsgId_;
   int                       TimeMillisec_;
   eMSG_SOURCE               MsgSource_;

public:

   TMsgTraffic() : TimeMillisec_( 0 ), MsgSource_( eMSG_SOURCE_SIM ) {}
   TMsgTraffic( const int InTimeMillisec, const int &InMsgId, const eMSG_SOURCE InMsgSource ) :
      TimeMillisec_( InTimeMillisec ), MsgId_( InMsgId ), MsgSource_( InMsgSource ) {}

   TMsgTraffic( const TMsgTraffic & InMsgTraffic )
   {
      ( *this ) = InMsgTraffic;
   }

   TMsgTraffic & operator=( const TMsgTraffic & rhs )
   {
      if ( this == & rhs ) return( *this );

      MsgId_               = rhs.MsgId_;
      TimeMillisec_        = rhs.TimeMillisec_;
      MsgSource_           = rhs.MsgSource_;

      return( *this );

   }
      
   __property int            MsgId            = { read = MsgId_               };
   __property int            TimeMillisec     = { read = TimeMillisec_        };
   __property eMSG_SOURCE    MsgSource        = { read = MsgSource_           };

};

typedef std::vector<TMsgTraffic> TMsgTrafficArray;
//---------------------------------------------------------------------------

#endif
 