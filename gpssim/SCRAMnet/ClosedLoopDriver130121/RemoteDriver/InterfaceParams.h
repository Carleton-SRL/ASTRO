#ifndef InterfaceParamsH
#define InterfaceParamsH
using namespace Sysutils;
class TGpibParams {
private:

   bool                      ControllerInCharge_;
   int                       BoardIndex_;
   int                       PrimaryAddress_;
   int                       SecondaryAddress_;
   int                       Timeout_;

public:

   TGpibParams() : ControllerInCharge_( false ), BoardIndex_( 0 ), PrimaryAddress_( 0 ), SecondaryAddress_( 0 ), Timeout_( 0 ) {}
   TGpibParams( const TGpibParams & Source )
   {
      ( *this ) = Source;
   }

   TGpibParams & operator=( const TGpibParams & Source )
   {

      if ( this == & Source ) return( *this );

      ControllerInCharge_  = Source.ControllerInCharge_;
      BoardIndex_          = Source.BoardIndex_;
      PrimaryAddress_      = Source.PrimaryAddress_;
      SecondaryAddress_    = Source.SecondaryAddress_;
      Timeout_             = Source.Timeout_;

      return( *this );

   }

   __property bool           ControllerInCharge     = { read = ControllerInCharge_, write = ControllerInCharge_ };
   __property int            BoardIndex             = { read = BoardIndex_,         write = BoardIndex_         };
   __property int            PrimaryAddress         = { read = PrimaryAddress_,     write = PrimaryAddress_     };
   __property int            SecondaryAddress       = { read = SecondaryAddress_,   write = SecondaryAddress_   };
   __property int            Timeout                = { read = Timeout_,            write = Timeout_            };

};


class TEthernetParams {
private:

   bool                      Server_;
   AnsiString                HostAddress_;
   int                       PortNum_;

   AnsiString const          GetHostAddress()
   {
      TReplaceFlags Flags;
      Flags << rfReplaceAll;
      return( StringReplace( HostAddress_, AnsiString( " " ), AnsiString( "" ), Flags ) );
   }
   void                      SetHostAddress( const AnsiString & InHostAddress )
   {
      TReplaceFlags Flags;
      Flags << rfReplaceAll;
      HostAddress_ = StringReplace( InHostAddress, AnsiString( " " ), AnsiString( "" ), Flags );
   }

   bool const                GetClient() const { return ( !Server_ ); }
   void                      SetClient( const bool InClient ) { Server_ = !InClient; } 

public:

   TEthernetParams() : Server_( false ), PortNum_( 0 ) {}
   TEthernetParams( const TEthernetParams & Source )
   {
      ( *this ) = Source;
   }

   TEthernetParams & operator=( const TEthernetParams & Source )
   {
      if ( this == &Source ) return( *this );

      Server_              = Source.Server_;
      HostAddress_         = Source.HostAddress_;
      PortNum_             = Source.PortNum_;

      return( *this );

   }

   __property bool           Server                 = { read = Server_,         write = Server_        };
   __property bool           Client                 = { read = GetClient,       write = SetClient      };
   __property AnsiString     HostAddress            = { read = GetHostAddress,  write = SetHostAddress };
   __property int            PortNum                = { read = PortNum_,        write = PortNum_       };

};

class TInterfaceParams {
private:

   typedef enum { eUnknown, eGpib, eEthernet } eInterfaceType;

   eInterfaceType            Type_;
   TGpibParams               GpibParams_;
   TEthernetParams           EthernetParams_;

   eInterfaceType const      GetInterfaceType() const { return( Type_ ); }
   void                      SetInterfaceType( const eInterfaceType & InType ) { Type_ = InType; }

   bool const                GetGpib() const { return( Type_ == eGpib ); }
   void                      SetGpib( const bool InGpib ) { Type_ = InGpib ? eGpib : Type_; }

   bool const                GetEthernet() const { return( Type_ == eEthernet ); }
   void                      SetEthernet( const bool InEthernet ) { Type_ = InEthernet ? eEthernet : Type_; }

public:

   TInterfaceParams( const eInterfaceType InType = eUnknown ) : Type_( InType ) {}

   TInterfaceParams( const TInterfaceParams & Source )
   {
      ( *this ) = Source;
   }

   TInterfaceParams & operator=( const TInterfaceParams & Source )
   {

      if ( this == &Source ) return( *this );

      Type_                = Source.Type_;
      GpibParams_          = Source.GpibParams_;
      EthernetParams_      = Source.EthernetParams_;

      return( *this );

   }

   __property eInterfaceType  Type            = { read = Type_                                      };
   __property bool            Gpib            = { read = GetGpib,          write = SetGpib          };
   __property bool            Ethernet        = { read = GetEthernet,      write = SetEthernet      };
   __property TGpibParams     GpibParams      = { read = GpibParams_,      write = GpibParams_      };
   __property TEthernetParams EthernetParams  = { read = EthernetParams_,  write = EthernetParams_  };

};



#endif
