//---------------------------------------------------------------------------

#ifndef RemoteDriverPfH
#define RemoteDriverPfH
//---------------------------------------------------------------------------

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

#ifndef InterfaceOptionsH
#include "InterfaceOptions.h"
#endif

#ifndef RemoteTypesH
#include "RemoteTypes.h"
#endif

class TRemoteDriverPf : public TIniFile {
private:


   // Interface
   bool const                GetGpib();
   void                      SetGpib( const bool Gpib );
   bool const                GetSerial();
   void                      SetSerial( const bool Serial );
   bool const                GetEthernet();
   void                      SetEthernet( const bool Ethernet );
   eIntType const            GetIntType();
   void                      SetIntType( const eIntType InIntType );

   // Gpib
   int const                 GetGpibPrimaryAddress();
   void                      SetGpibPrimaryAddress( const int GpibPrimaryAddress );
   int const                 GetGpibBoardIndex();
   void                      SetGpibBoardIndex( const int GpibBoardIndex );
   int const                 GetGpibTimeout();
   void                      SetGpibTimeout( const int Timeout );

   // Ethernet
   bool const                GetEthernetServer();
   void                      SetEthernetServer( const bool IsServer );
   bool const                GetEthernetClient();
   void                      SetEthernetClient( const bool IsClient );
   AnsiString const          GetEthernetHostAddress();
   void                      SetEthernetHostAddress( const AnsiString &HostAddr );
   int const                 GetEthernetPortNum();
   void                      SetEthernetPortNum( const int PortNum );

   // Serial
   int const                 GetSerialComPort();
   void                      SetSerialComPort( const int ComPort );
   int const                 GetSerialBaud();
   void                      SetSerialBaud( const int Baud );
   int const                 GetSerialStopBits();
   void                      SetSerialStopBits( const int StopBits );

   // CodeSite
   bool const                GetCodeSiteEnabled();
   void                      SetCodeSiteEnabled( const bool InCodeSiteEnabled );
   bool const                GetCodeSiteUseAlias();
   void                      SetCodeSiteUseAlias( const bool InCodeSiteUseAlias );
   AnsiString const          GetCodeSiteAlias();
   void                      SetCodeSiteAlias( const AnsiString & InCodeSiteAlias );

public:

   TRemoteDriverPf();

   __property bool        Gpib                     = { read = GetGpib,                   write = SetGpib                   };
   __property bool        Serial                   = { read = GetSerial,                 write = SetSerial                 };
   __property bool        Ethernet                 = { read = GetEthernet,               write = SetEthernet               };
   __property int         GpibPrimaryAddress       = { read = GetGpibPrimaryAddress,     write = SetGpibPrimaryAddress     };
   __property int         GpibBoardIndex           = { read = GetGpibBoardIndex,         write = SetGpibBoardIndex         };
   __property int         GpibTimeout              = { read = GetGpibTimeout,            write = SetGpibTimeout            };
   __property bool        EthernetServer           = { read = GetEthernetServer,         write = SetEthernetServer         };
   __property bool        EthernetClient           = { read = GetEthernetClient,         write = SetEthernetClient         };
   __property AnsiString  EthernetHostAddress      = { read = GetEthernetHostAddress,    write = SetEthernetHostAddress    };
   __property int         EthernetPortNum          = { read = GetEthernetPortNum,        write = SetEthernetPortNum        };
   __property int         SerialComPort            = { read = GetSerialComPort,          write = SetSerialComPort          };
   __property int         SerialBaud               = { read = GetSerialBaud,             write = SetSerialBaud             };
   __property int         SerialStopBits           = { read = GetSerialStopBits,         write = SetSerialStopBits         };
   __property eIntType    IntType                  = { read = GetIntType,                write = SetIntType                };
   __property bool        CodeSiteEnabled          = { read = GetCodeSiteEnabled,        write = SetCodeSiteEnabled        };
   __property bool        CodeSiteUseAlias         = { read = GetCodeSiteUseAlias,       write = SetCodeSiteUseAlias       };
   __property AnsiString  CodeSiteAlias            = { read = GetCodeSiteAlias,          write = SetCodeSiteAlias          };         

};         


#endif
