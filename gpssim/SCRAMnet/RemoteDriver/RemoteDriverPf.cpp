#include "pch.h"
#pragma hdrstop

#ifndef RemoteDriverPfH
#include "RemoteDriverPf.h"
#endif

#ifndef GpibTimeoutH
#include "GpibTimeout.h"
#endif

#include "Decl-32.h"

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


#pragma package(smart_init)


//---------------------------------------------------------------------------
// Interface Section [INTERFACE]
//
static const AnsiString InterfaceSection("INTERFACE");

static const AnsiString GpibKey( "Gpib" );
static const int        GpibDef( 0 );
static const AnsiString SerialKey( "Serial" );
static const int        SerialDef( 0 );
static const AnsiString EthernetKey( "Ethernet" );
static const int        EthernetDef( 0 );


//---------------------------------------------------------------------------
// GPIB Section [GPIB]
//
static const AnsiString GpibSection("GPIB");

static const AnsiString GpibPrimaryAddressKey( "PrimaryAddress" );
static const int        GpibPrimaryAddressDef( 15 );
static const AnsiString GpibBoardIndexKey( "BoardIndex" );
static const int        GpibBoardIndexDef( 0 );
static const AnsiString GpibTimeoutKey( "TimeOut" );
static const int        GpibTimeoutIntDef( T100ms );
static const AnsiString GpibTimeoutDef( "T100ms" );

//---------------------------------------------------------------------------
// Serial Section [SERIAL]
//
static const AnsiString SerialSection("SERIAL");

static const AnsiString SerialComPortKey( "ComPort" );
static const int        SerialComPortDef( 1 );
static const AnsiString SerialBaudKey( "Baud" );
static const int        SerialBaudDef( 19200 );
static const AnsiString SerialStopBitsKey( "StopBits" );
static const int        SerialStopBitsDef( 1 );

//---------------------------------------------------------------------------
// Ethernet Section [ETHERNET]
//
static const AnsiString EthernetSection("ETHERNET");

static const AnsiString EthernetServerKey( "Server" );
static const bool       EthernetServerDef( 0 );
static const AnsiString EthernetHostAddressKey( "HostAddress" );
static const AnsiString EthernetHostAddressDef( "000.000.000.000" );
static const AnsiString EthernetPortNumKey( "PortNum" );
static const int        EthernetPortNumDef( 5000 );

//---------------------------------------------------------------------------
// CodeSite Section [CODESITE]
//
static const AnsiString CodeSiteSection("CODESITE");

static const AnsiString CodeSiteEnabledKey( "Enabled" );
static const bool       CodeSiteEnabledDef( 1 );
static const AnsiString CodeSiteUseAliasKey( "UseAlias" );
static const bool       CodeSiteUseAliasDef( 0 );
static const AnsiString CodeSiteAliasKey( "Alias" );
static const AnsiString CodeSiteAliasDef( "CSViewer" );

TRemoteDriverPf::TRemoteDriverPf
   (
   ) :
   TIniFile( "RemoteDriver.ini" )
{
}

eIntType const
TRemoteDriverPf::GetIntType
   (
   )
{
   eIntType RetIntType = eIntEthernet;

   if ( Gpib )
   {
      RetIntType = eIntGpib;
   }
   else if ( EthernetServer )
   {
      RetIntType = eIntEthernet;
   }
   else if ( Serial )
   {
      RetIntType = eIntSerial;
   }

   return( RetIntType );

}

void
TRemoteDriverPf::SetIntType
   (
   const eIntType InIntType
   )
{

   bool IntGpib           = false;
   bool IntEthernet       = false;
   bool IntSerial         = false;

   if ( InIntType == eIntGpib )
   {
      IntGpib           = true;
   }
   else if ( InIntType == eIntEthernet )
   {
      IntEthernet       = true;
   }
   else if ( InIntType == eIntSerial )
   {
      IntSerial         = true;
   }

   Gpib           = IntGpib;
   Ethernet       = IntEthernet;
   Serial         = IntSerial;

}

bool const
TRemoteDriverPf::GetGpib
   (

   )
{
   return( ReadInteger( InterfaceSection, GpibKey, GpibDef ) );
}

void
TRemoteDriverPf::SetGpib
   (
   const bool Gpib
   )
{
   WriteInteger( InterfaceSection, GpibKey, Gpib );
}

bool const
TRemoteDriverPf::GetSerial
   (

   )
{
   return( ReadInteger( InterfaceSection, SerialKey, SerialDef ) );
}

void
TRemoteDriverPf::SetSerial
   (
   const bool Serial
   )
{
   WriteInteger( InterfaceSection, SerialKey, Serial );
}

bool const
TRemoteDriverPf::GetEthernet
   (

   )
{
   return( ReadInteger( InterfaceSection, EthernetKey, EthernetDef ) );
}

void
TRemoteDriverPf::SetEthernet
   (
   const bool Ethernet
   )
{
   WriteInteger( InterfaceSection, EthernetKey, Ethernet );
}

int const
TRemoteDriverPf::GetGpibPrimaryAddress
   (

   )
{
   return( ReadInteger( GpibSection, GpibPrimaryAddressKey, GpibPrimaryAddressDef ) );
}

void
TRemoteDriverPf::SetGpibPrimaryAddress
   (
   const int GpibPrimaryAddress
   )
{
   WriteInteger( GpibSection, GpibPrimaryAddressKey, GpibPrimaryAddress );
}

int const
TRemoteDriverPf::GetGpibBoardIndex
   (

   )
{
   return( ReadInteger( GpibSection, GpibBoardIndexKey, GpibBoardIndexDef ) );
}

void
TRemoteDriverPf::SetGpibBoardIndex
   (
   const int GpibBoardIndex
   )
{
   WriteInteger( GpibSection, GpibBoardIndexKey, GpibBoardIndex );
}


int const
TRemoteDriverPf::GetSerialComPort
   (

   )
{
   return( ReadInteger( SerialSection, SerialComPortKey, SerialComPortDef ) );
}

void
TRemoteDriverPf::SetSerialComPort
   (
   const int SerialComPort
   )
{
   WriteInteger( SerialSection, SerialComPortKey, SerialComPort );
}

int const
TRemoteDriverPf::GetSerialBaud
   (

   )
{
   return( ReadInteger( SerialSection, SerialBaudKey, SerialBaudDef ) );
}

void
TRemoteDriverPf::SetSerialBaud
   (
   const int SerialBaud
   )
{
   WriteInteger( SerialSection, SerialBaudKey, SerialBaud );
}

int const
TRemoteDriverPf::GetSerialStopBits
   (

   )
{
   return( ReadInteger( SerialSection, SerialStopBitsKey, SerialStopBitsDef ) );
}

void
TRemoteDriverPf::SetSerialStopBits
   (
   const int SerialStopBits
   )
{
   WriteInteger( SerialSection, SerialStopBitsKey, SerialStopBits );
}

bool const
TRemoteDriverPf::GetEthernetServer
   (

   )
{
   return( ReadInteger( EthernetSection, EthernetServerKey, EthernetServerDef ) );
}

void
TRemoteDriverPf::SetEthernetServer
   (
   const bool IsEthernetServer
   )
{
   WriteInteger( EthernetSection, EthernetServerKey, IsEthernetServer );
}

bool const
TRemoteDriverPf::GetEthernetClient
   (

   )
{
   return( !EthernetServer );
}

void
TRemoteDriverPf::SetEthernetClient
   (
   const bool IsEthernetClient
   )
{
   EthernetServer = !IsEthernetClient;
}      

AnsiString const
TRemoteDriverPf::GetEthernetHostAddress
   (

   )
{
   return( ReadString( EthernetSection, EthernetHostAddressKey, EthernetHostAddressDef ) );
}

void
TRemoteDriverPf::SetEthernetHostAddress
   (
   const AnsiString &EthernetHostAddress
   )
{
   WriteString( EthernetSection, EthernetHostAddressKey, EthernetHostAddress );
}

int const
TRemoteDriverPf::GetEthernetPortNum
   (

   )
{
   return( ReadInteger( EthernetSection, EthernetPortNumKey, EthernetPortNumDef ) );
}

void
TRemoteDriverPf::SetEthernetPortNum
   (
   const int EthernetPortNum
   )
{
   WriteInteger( EthernetSection, EthernetPortNumKey, EthernetPortNum );
}

int const
TRemoteDriverPf::GetGpibTimeout
   (
   )
{
   TGpibTimeout GpibTime( GpibTimeoutIntDef );
   AnsiString GpibTimeoutStr = ReadString( GpibSection, GpibTimeoutKey, GpibTimeoutDef );
   return( GpibTime.GetTimeout( GpibTimeoutStr ) );
}

void
TRemoteDriverPf::SetGpibTimeout
   (
   const int Timeout
   )
{
   TGpibTimeout GpibTime( GpibTimeoutIntDef );
   WriteString( GpibSection, GpibTimeoutKey, GpibTime.GetTimeoutStr( Timeout ) );
}

bool const
TRemoteDriverPf::GetCodeSiteEnabled
   (
   )
{
   return( ReadBool( CodeSiteSection, CodeSiteEnabledKey, CodeSiteEnabledDef ) );
}

void
TRemoteDriverPf::SetCodeSiteEnabled
   (
   const bool                InCodeSiteEnabled
   )
{
   WriteBool( CodeSiteSection, CodeSiteEnabledKey, InCodeSiteEnabled );
}

bool const
TRemoteDriverPf::GetCodeSiteUseAlias
   (
   )
{
   return( ReadBool( CodeSiteSection, CodeSiteUseAliasKey, CodeSiteUseAliasDef ) );
}

void
TRemoteDriverPf::SetCodeSiteUseAlias
   (
   const bool                InCodeSiteUseAlias
   )
{
   WriteBool( CodeSiteSection, CodeSiteUseAliasKey, InCodeSiteUseAlias );
}

AnsiString const
TRemoteDriverPf::GetCodeSiteAlias
   (
   )
{
   return( ReadString( CodeSiteSection, CodeSiteAliasKey, CodeSiteAliasDef ) );
}

void
TRemoteDriverPf::SetCodeSiteAlias
   (
   const AnsiString        & InCodeSiteAlias
   )
{
   WriteString( CodeSiteSection, CodeSiteAliasKey, InCodeSiteAlias );
}
   

