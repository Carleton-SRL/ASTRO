#ifndef InterfaceOptionsH
#define InterfaceOptionsH

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


class TIntOptions {
public:
   bool ValidInterface;
public:
   TIntOptions() {}
   virtual ~TIntOptions() {}
};

class TGpibOptions : public TIntOptions {
public:
   int BoardIndex;
   int PrimaryAddr;
public:
   TGpibOptions(): BoardIndex( 0 ), PrimaryAddr( 0 ) {}
   TGpibOptions( const int InBoardIndex, const int InPrimaryAddr ) :
      BoardIndex( InBoardIndex ), PrimaryAddr( InPrimaryAddr ) {}

};

class TEthernetOptions : public TIntOptions {
private:

   AnsiString HostAddr_;
   int        Port_;
   bool       Client_;

   bool const GetServer()
   {
      return( !Client_ );
   }
   void       SetServer( const bool InServer )
   {
      Client_ = !InServer;
   }
   void       SetClient( const bool InClient )
   {
      Client_ = InClient;
   }

public:

   TEthernetOptions() : Port_( 0 ) {}
   TEthernetOptions( const AnsiString & InHostAddr, const int InPort ) : HostAddr_( InHostAddr ), Port_( InPort ) {}

   TEthernetOptions & operator=( const TEthernetOptions & Source )
   {
      if ( this == & Source )
      {
         return( *this );
      }

      HostAddr_ = Source.HostAddr_;
      Port_     = Source.Port_;
      Client_   = Source.Client_;

      return( *this );

   }

   TEthernetOptions( const TEthernetOptions & Source )
   {
      ( *this ) = Source;
   }

   static TIntArr const ConvertHostAddrToNumbers( const AnsiString HostAddrStr )
   {
      TIntArr HostAddrNums;
      TStringList * Fields = new TStringList;
      ExtractTokensL( HostAddrStr, AnsiString( "." ), '\'', true, Fields );
      for ( int i=0; i<Fields->Count; ++i )
      {
         HostAddrNums.push_back( Fields->Strings[i].ToInt() );
      }
      for ( int i=Fields->Count; i<4; ++i )
      {
         HostAddrNums.push_back( 0 );
      }
      return( HostAddrNums );
   }

   static AnsiString const ConvertHostAddrNumbersToStr( const TIntArr HostAddrNums )
   {
      AnsiString Str;
      Str.sprintf( "%d.%d.%d.%d", HostAddrNums[0], HostAddrNums[1], HostAddrNums[2], HostAddrNums[3] );
      return( Str );
   }

   __property AnsiString HostAddr = { read = HostAddr_,    write = HostAddr_ };
   __property int        Port     = { read = Port_,        write = Port_     };
   __property bool       Client   = { read = Client_,      write = SetClient };
   __property bool       Server   = { read = GetServer,    write = SetServer };


};

#endif
 