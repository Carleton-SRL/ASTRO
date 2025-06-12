#ifndef InterfaceParametersH
#define InterfaceParametersH

class TGpibParameters {
private:

   bool                      ControllerInCharge_;
   int                       BoardIndex_;
   int                       PrimaryAddress_;
   int                       SecondaryAddress_;
   int                       Timeout_;

public:

   TGpibParameters() : ControllerInCharge_( false ), BoardIndex_( 0 ), PrimaryAddress_( 0 ), SecondaryAddress_( 0 ), Timeout_( 0 ) {}
   TGpibParameters( const TGpibParameters & Source )
   {
      ( *this ) = Source;
   }
   TGpibParameters & operator=( const TGpibParameters & Source )
   {
      if ( this == & Source ) return( *this );

      ControllerInCharge_  = Source.ControllerInCharge_;
      BoardIndex_          = Source.BoardIndex_;
      PrimaryAddres_       = Source.PrimaryAddress_;
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


class TEthernetParameters {
private:

   bool                      Server_;
   AnsiString                HostAddress_;
   int                       PortNum_;

public:

   TEthernetParameters() : Server_( false ), PortNum_( 0 ) {}
   TEthernetParameters( const TEthernetParameters & Source )
   {
      ( *this ) = Source;
   }

   TEthernetParameters & operator=( const TEthernetParameters & Source )
   {
      if ( this == &Source ) return( *this );

      Server_              = Source.Server_;
      HostAddress_         = Source.HostAddress_;
      PortNum_             = Source.PortNum_;

      return( *this );

   }

   __property bool           Server                 = { read = Server_,      write = Server_      };
   __property AnsiString     HostAddress            = { read = HostAddress_, write = HostAddress_ };
   __property int            PortNum                = { read = PortNum_,     write = PortNum_     };

};                  

#endif
