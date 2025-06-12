//#include "pch.h"
//#pragma hdrstop
//---------------------------------------------------------------------------
//
// $Workfile:: ScenIniFile.cpp                                       $
//
// $Revision:: 14                                                    $
//
// $History:: ScenIniFile.cpp                                        $
//
//*****************  Version 14  *****************
//User: Michael Wade Date: 11/14/03   Time: 11:49a
//Updated in $/TapMsec
//Raytheon ATB
//
//*****************  Version 13  *****************
//User: Michael Wade Date: 5/29/03    Time: 3:11p
//Updated in $/TapMsec
//Add SyncDateTime.  Made RfPanelHeight property.
//
//*****************  Version 12  *****************
//User: Michael Wade Date: 5/10/03    Time: 11:40p
//Updated in $/TapMsec
//Add Sync to Sky
//
//*****************  Version 11  *****************
//User: Michael Wade Date: 4/29/03    Time: 8:09p
//Updated in $/TapMsec
//Add "AddHWCounter" parameter to ScenIni file.
//
//*****************  Version 10  *****************
//User: Michael Wade Date: 1/20/03    Time: 12:05p
//Updated in $/TapMsec
//Add properties.
//Add GPIB
//
//*****************  Version 9  *****************
//User: Michael Wade Date: 7/28/02    Time: 11:54p
//Updated in $/TapMsec
//Added include file guards
//
//*****************  Version 8  *****************
//User: Michael Wade Date: 7/23/02    Time: 8:02p
//Updated in $/TapMsec
//Added Source Safe keywords
//
//
//
//
//
//
//---------------------------------------------------------------------------

#ifndef ScenIniFileH
#include "ScenIniFile.h"
#endif

#ifndef PosVecH
#include "PosVec.h"
#endif

#ifndef WgsConsH
#include "WgsCons.h"
#endif

static const AnsiString ScenIniFileName("\\Scen.ini");
static char  DirBuff[MAX_PATH];


// [DISPLAY]
//
static const AnsiString ScenIniDisplaySection( "DISPLAY" );

static const AnsiString RightPanelWidthKey( "RightPanelWidth" );
static const int        RightPanelWidthDef( 468 );

static const AnsiString RfPanelHeightKey( "RfPanelWidth" );
static const int        RfPanelHeightDef( -1 );

// [CONTROL]
//
static const AnsiString ControlSection( "CONTROL" );
static const AnsiString NumPseudolitesKey( "NumPseudolites" );
static const int        NumPseudolitesDef( 1 );

static const AnsiString PulseKey( "PulseEnabled" );
static const int        PulseDef( 0 );

static const AnsiString SyncToSkyKey( "SyncToSky" );
static const int        SyncToSkyDef( 0 );

static const AnsiString PseudoliteKey( "PseudolitesEnabled" );
static const int        PseudoliteDef( 0 );

static const AnsiString UseScenPTKey( "UseScenPT" );
static const int        UseScenPTDef( 0 );

static const AnsiString UseScenFileKey( "UseScenFile" );
static const int        UseScenFileDef( 0 );

static const AnsiString SyncToSkyUseGpsKey( "SyncToSkyUseGps" );
static const int        SyncToSkyUseGpsDef( 0 );

static const AnsiString LocalKey( "Local" );
static const int        LocalDef( 0 );

static const AnsiString SyncLatKey( "SyncLat" );
static const AnsiString DefSyncLatStr( "34.000000" );

static const AnsiString SyncLonKey( "SyncLon" );
static const AnsiString DefSyncLonStr( "-118.000000" );

static const AnsiString SyncAltKey( "SyncAlt" );
static const AnsiString DefSyncAltStr( "0.00" );

static const AnsiString SyncDateKey( "SyncDate" );
static const AnsiString SyncDateDef( "5/1/2003" );

static const AnsiString SyncTimeKey( "SyncTime" );
static const AnsiString SyncTimeDef( "11:00:00" );

static const AnsiString SyncDateTimeKey( "SyncDateTime" );
static const AnsiString SyncDateTimeDef( "5/1/2003 11:00:00" );

static const AnsiString RolloverPPSCountKey( "RolloverPPSCount" );
static const int        RolloverPPSCountDef( 0 );

static const AnsiString PPSCountKey( "PPSCount" );
static const int        PPSCountDef( 0 );

static const AnsiString CommonRfAttenKey( "CommonRfAtten" );
static const int        CommonRfAttenDef( 0 );

static const AnsiString RefRcvrPortKey( "RefRcvrPort" );
static const int        RefRcvrPortDef( 1 );

static const AnsiString RefRcvrBaudKey( "RefRcvrBaud" );
static const int        RefRcvrBaudDef( 19200 );

static const AnsiString AntiSpoofFlagKey( "AntiSpoofFlag" );
static const int        AntiSpoofFlagDef( 0 );

static const AnsiString WaitForStartPulseKey( "WaitForStartPulse" );
static const int        WaitForStartPulseDef( 0 );

// Single Channel Items
//
static const AnsiString SingleChanSection( "SINGLECHAN" );

static const AnsiString SingleChanKey( "SingleChan" );
static const int        SingleChanDef( 0 );
static const AnsiString LLTestNumChansKey( "NumLLTestChans" );
static const int        LLTestNumChansDef( 1 );
static const AnsiString AutoStartKey( "AutoStart" );
static const int        AutoStartDef( 0 );

// Real Time Message Items
//
static const AnsiString RtMsgSection( "RTMSG" );

static const AnsiString RtMsgWriteDebugKey( "RtMsgWriteDebug" );
static const int        RtMsgWriteDebugDef( 0 );
static const AnsiString RtMsgWriteTrajFileKey( "RtMsgWriteTrajFile" );
static const int        RtMsgWriteTrajFileDef( 0 );
static const AnsiString StelSendSVLookAngleKey( "SvLookAngleEnabled" );
static const int        StelSendSVLookAngleDef( 0 );
static const AnsiString WriteRangeTruthRTKey( "WriteRangeTruthRT" );
static const int        WriteRangeTruthRTDef( 0 );




//---------------------------------------------------------------------------
// Interface Section [INTERFACE]
//
static const AnsiString InterfaceSection("INTERFACE");

static const AnsiString GpibKey( "Gpib" );
static const bool       GpibDef( 0 );
static const AnsiString SerialKey( "Serial" );
static const bool       SerialDef( 0 );
static const AnsiString EthernetKey( "Ethernet" );
static const bool       EthernetDef( 0 );
static const AnsiString ScramnetKey( "Scramnet" );
static const bool       ScramnetDef( 0 );
static const AnsiString SharedMemoryKey( "SharedMemory" );
static const bool       SharedMemoryDef( 0 );


//---------------------------------------------------------------------------
// RT Init Section [RTINIT]
//
static const AnsiString RTInitSection("RTINIT");

static const AnsiString RTInitAddHWCounterToInitTimeKey( "AddHWCounterToInitTime" );
static const bool       RTInitAddHWCounterToInitTimeDef( false );

//---------------------------------------------------------------------------
// Sync To Sky Section [SYNC]
//      Note:  The keys for "SyncToSky" and "SyncToSkyUseGps" are being left
//   in CONTROL but duplicated here for compatibility reasons.
//
static const AnsiString SyncToSkySection( "SYNC" );

static const AnsiString SyncRemoteKey( "SyncRemote" );
static const bool       SyncRemoteDef( false );

namespace nScenIniSyncToSky {

   static const AnsiString AutoStartKey( "AutoStart" );
   static const bool       AutoStartDef( false );

   static const AnsiString AutoStartAllowOverrideKey( "AutoAllowOverride" );
   static const bool       AutoStartAllowOverrideDef( false );


   static const AnsiString AutoRefDataValidKey( "AutoRefDataValid" );
   static const AnsiString AutoRefDataValidDef( "1,0,0,0" );

   static const AnsiString AutoRcv1PPSKey( "AutoRcv1PPS" );
   static const AnsiString AutoRcv1PPSDef( "0,0,0,0" );

   static const AnsiString Auto1PPSValidKey( "Auto1PPSValid" );
   static const AnsiString Auto1PPSValidDef( "1,0,0,0" );

   static const AnsiString AutoArmResetKey( "AutoArmReset" );
   static const AnsiString AutoArmResetDef( "1,0,0,0" );

   static const AnsiString AutoCompleteKey( "AutoComplete" );
   static const AnsiString AutoCompleteDef( "1,0,0,0" );

};


TScenIniFile::TScenIniFile
   (
   ) :
   TIniFile( AnsiString( getcwd( DirBuff, MAX_PATH ) ) + ScenIniFileName )
{
}

int const
TScenIniFile::GetRightPanelWidth()
{

   return( ReadInteger( ScenIniDisplaySection, RightPanelWidthKey, RightPanelWidthDef ) );

}

void
TScenIniFile::SetRightPanelWidth
   (
   const int                 InRightPanelWidth
   )
{

   WriteInteger( ScenIniDisplaySection, RightPanelWidthKey, InRightPanelWidth );

}

int const
TScenIniFile::GetRfPanelHeight()
{

   return( ReadInteger( ScenIniDisplaySection, RfPanelHeightKey, RfPanelHeightDef ) );

}

void
TScenIniFile::SetRfPanelHeight
   (
   const int                 InRfPanelHeight
   )
{

   WriteInteger( ScenIniDisplaySection, RfPanelHeightKey, InRfPanelHeight );

}



int const
TScenIniFile::GetNumPseudolites
   (

   )
{
   return( ReadInteger( ControlSection, NumPseudolitesKey, NumPseudolitesDef ) );
}


void
TScenIniFile::WriteNumPseudolites
   (
   const int NumPseudolites
   )
{
   WriteInteger( ControlSection, NumPseudolitesKey, NumPseudolites );
}


bool const
TScenIniFile::IsPulse
   (

   )
{
   return( ReadInteger( ControlSection, PulseKey, PulseDef ) );
}


void
TScenIniFile::WritePulse
   (
   const bool Pulse
   )
{
   WriteInteger( ControlSection, PulseKey, Pulse );
}


bool const
TScenIniFile::IsSyncToSkyEnabled
   (

   )
{
   return( ReadInteger( ControlSection, SyncToSkyKey, SyncToSkyDef ) );
}


void
TScenIniFile::WriteSyncToSky
   (
   const bool                SyncToSky
   )
{
   WriteInteger( ControlSection, SyncToSkyKey, SyncToSky );
}

bool const
TScenIniFile::IsSyncToSkyUseGps
   (

   )
{
   return( ReadInteger( ControlSection, SyncToSkyUseGpsKey, SyncToSkyUseGpsDef ) );
}


void
TScenIniFile::WriteSyncToSkyUseGps
   (
   const bool                SyncToSkyUseGps
   )
{
   WriteInteger( ControlSection, SyncToSkyUseGpsKey, SyncToSkyUseGps );
}


bool const
TScenIniFile::IsPseudolite
   (

   )
{
   return( ReadInteger( ControlSection, PseudoliteKey, PseudoliteDef ) );
}


void
TScenIniFile::WritePseudolite
   (
   const bool Pseudolite
   )
{
   WriteInteger( ControlSection, PseudoliteKey, Pseudolite );
}

bool const
TScenIniFile::IsUseScenPT
   (

   )
{
   return( ReadInteger( ControlSection, UseScenPTKey, UseScenPTDef ) );
}

bool const
TScenIniFile::IsUseScenFile
   (

   )
{
   return( ReadInteger( ControlSection, UseScenFileKey, UseScenFileDef ) );
}


void
TScenIniFile::WriteUseScenPT
   (
   const bool UseScenPT
   )
{
   WriteInteger( ControlSection, UseScenPTKey, UseScenPT );
}

bool const
TScenIniFile::IsLocal
   (

   )
{
   return( ReadInteger( ControlSection, LocalKey, LocalDef ) );
}


void
TScenIniFile::WriteLocal
   (
   const bool Local
   )
{
   WriteInteger( ControlSection, LocalKey, Local );
}

void
TScenIniFile::GetSyncPos
   (
   double &Lat,
   double &Lon,
   double &Alt
   )
{

   AnsiString LatStr = ReadString(ControlSection,SyncLatKey,DefSyncLatStr);
   AnsiString LonStr = ReadString(ControlSection,SyncLonKey,DefSyncLonStr);
   AnsiString AltStr = ReadString(ControlSection,SyncAltKey,DefSyncAltStr);

   Lat = LatStr.ToDouble();
   Lon = LonStr.ToDouble();
   Alt = AltStr.ToDouble();

}

TDateTime const
TScenIniFile::GetSyncDate
   (
   )
{


   AnsiString DateStr = ReadString( ControlSection, SyncDateKey, TDateTime::CurrentDate().DateString() );
   if ( !DateStr.Length() )
   {
      DateStr = TDateTime::CurrentDate().DateString();
   }

   return ( StrToDate( DateStr ) );

}

TDateTime const
TScenIniFile::GetSyncTime
   (
   )
{

   AnsiString TimeStr = ReadString( ControlSection, SyncTimeKey, TDateTime::CurrentTime().TimeString() );

   return ( StrToTime( TimeStr ) );

}


TDateTime const
TScenIniFile::GetSyncDateTime
   (
   )
{


   AnsiString DateStr = ReadString( ControlSection, SyncDateTimeKey, TDateTime::CurrentDate().DateTimeString() );

   return ( StrToDateTime( DateStr ) );

}

void
TScenIniFile::SetSyncPos
   (
   double Lat,
   double Lon,
   double Alt
   )
{

   char Str[100];
   sprintf(Str,"%12.7lf",Lat);
   WriteString( ControlSection, SyncLatKey, AnsiString(Str) );

   sprintf(Str,"%12.7lf",Lon);
   WriteString( ControlSection, SyncLonKey, AnsiString(Str) );

   sprintf(Str,"%10.2lf",Alt);
   WriteString( ControlSection, SyncAltKey, AnsiString(Str) );

}

void
TScenIniFile::SetSyncDate
   (
   const TDateTime &Date
   )
{

   WriteString( ControlSection, SyncDateKey, Date.DateString() );

}

void
TScenIniFile::SetSyncTime
   (
   const TDateTime &Time
   )
{

   WriteString( ControlSection, SyncTimeKey, Time.TimeString() );

}

void
TScenIniFile::SetSyncDateTime
   (
   const TDateTime &InDateTime
   )
{

   WriteString( ControlSection, SyncDateTimeKey, DateTimeToStr( InDateTime ) );

}
int const
TScenIniFile::GetRefRcvrPort()
{
   return( ReadInteger( ControlSection, RefRcvrPortKey, RefRcvrPortDef ) );
}

int const
TScenIniFile::GetRefRcvrBaud()
{
   return( ReadInteger( ControlSection, RefRcvrBaudKey, RefRcvrBaudDef ) );
}

VehTruthRec const
TScenIniFile::GetInitialSyncState
   (
   )
{

   VehTruthRec TruthRec;

   double Lat;
   double Lon;
   double Alt;
   GetSyncPos( Lat, Lon, Alt );
   TDateTime Date = GetSyncDate();
   Date = (int) Date;
   TDateTime Time = GetSyncTime();

   int iTime      = (int) Time;
   double dTime   = (double) Time;
   double tTime   = dTime - iTime;

   TDateTime DateTime = Date + tTime;

   TruthRec.GpsTime = DateTime;

   TPosVec PosVec;
   PosVec.Lat = Lat;
   PosVec.Lon = Lon;
   PosVec.Alt = Alt;

   for ( int i=0; i<3; ++i )
   {
      TruthRec.PosEcef[i] = PosVec.PosEcef[i];
   }

   return( TruthRec );

}


int const
TScenIniFile::GetCommonRfAtten
   (
   const int RfNum
   )
{
   AnsiString CommonRfAttenKeyStr = CommonRfAttenKey;
   CommonRfAttenKeyStr += RfNum;
   return( ReadInteger( ControlSection, CommonRfAttenKeyStr, CommonRfAttenDef ) );
}


void
TScenIniFile::WriteCommonRfAtten
   (
   const int Atten,
   const int RfNum
   )
{

   AnsiString CommonRfAttenKeyStr  = CommonRfAttenKey;
   CommonRfAttenKeyStr            += RfNum;
   WriteInteger( ControlSection, CommonRfAttenKeyStr, Atten );

}




void
TScenIniFile::WritePPSCounter
   (
   const int RolloverPPSCount,
   const int PPSCount
   )
{

   WriteInteger( ControlSection, RolloverPPSCountKey, RolloverPPSCount );
   WriteInteger( ControlSection, PPSCountKey, PPSCount );

}

void
TScenIniFile::GetPPSCounter
   (
   int & RolloverPPSCount,
   int & PPSCount
   )
{

   RolloverPPSCount = ReadInteger( ControlSection, RolloverPPSCountKey, RolloverPPSCountDef );
   PPSCount         = ReadInteger( ControlSection, PPSCountKey, PPSCountDef );

}

bool const
TScenIniFile::IsSingleChan
   (
   )
{

   return( ReadInteger( SingleChanSection, SingleChanKey, SingleChanDef ) );

}

bool const
TScenIniFile::IsSingleChanAutoStart
   (
   )
{

   return( ReadInteger( SingleChanSection, AutoStartKey, AutoStartDef ) );

}

void
TScenIniFile::WriteSingleChanAutoStart
   (
   const bool AutoStart
   )
{

   WriteInteger( SingleChanSection, AutoStartKey, AutoStart );

}

bool const
TScenIniFile::IsGpibEnabled
   (

   )
{

   return( ReadBool( InterfaceSection, GpibKey, GpibDef ) );

}

bool const
TScenIniFile::IsSerialEnabled
   (

   )
{

   return( ReadBool( InterfaceSection, SerialKey, SerialDef ) );

}

bool const
TScenIniFile::IsRtMsgWriteDebug
   (

   )
{

   return( ReadInteger( RtMsgSection, RtMsgWriteDebugKey, RtMsgWriteDebugDef ) );

}

bool const
TScenIniFile::IsStelSendSvLookAngle
   (

   )
{

   return( ReadInteger( RtMsgSection, StelSendSVLookAngleKey, StelSendSVLookAngleDef ) );

}

bool const
TScenIniFile::IsWriteRangeTruthRT
   (

   )
{

   return( ReadInteger( RtMsgSection, WriteRangeTruthRTKey, WriteRangeTruthRTDef ) );

}



bool const
TScenIniFile::IsRtMsgWriteTrajFile
   (

   )
{

   return( ReadInteger( RtMsgSection, RtMsgWriteTrajFileKey, RtMsgWriteTrajFileDef ) );

}

bool const
TScenIniFile::IsEthernetEnabled
   (

   )
{

   return( ReadBool( InterfaceSection, EthernetKey, EthernetDef ) );

}

bool const
TScenIniFile::IsScramnetEnabled
   (

   )
{

   return( ReadBool( InterfaceSection, ScramnetKey, ScramnetDef ) );

}

bool const
TScenIniFile::IsSharedMemoryEnabled
   (

   )
{

   return( ReadBool( InterfaceSection, SharedMemoryKey, SharedMemoryDef ) );

}

bool const
TScenIniFile::IsFileBased
   (

   )
{

   const bool IsGpib          = IsGpibEnabled();
   const bool IsSyncToSky     = IsSyncToSkyEnabled();
   const bool IsEthernet      = IsEthernetEnabled();
   const bool IsSerial        = IsSerialEnabled();
   const bool IsScramnet      = IsScramnetEnabled();
   const bool IsSharedMemory  = IsSharedMemoryEnabled();
   const bool IsSingleChannel = IsSingleChan();
   const bool IsLocalb        = IsLocal();

   const bool FileBased       = !( IsGpib || IsSyncToSky || IsEthernet || IsScramnet || IsSharedMemory || IsSingleChannel || IsLocalb || IsSerial );

   return( FileBased );

}

bool const
TScenIniFile::IsRemote
   (

   )
{
   const bool IsGpib          = IsGpibEnabled();
   const bool IsEthernet      = IsEthernetEnabled();
   const bool IsScramnet      = IsScramnetEnabled();
   const bool IsSharedMemory  = IsSharedMemoryEnabled();
   const bool IsSerial        = IsSerialEnabled();

   const bool Remote      = ( IsGpib || IsEthernet || IsScramnet || IsSharedMemory || IsSerial );

   return( Remote );

}

bool const
TScenIniFile::IsRt
   (

   )
{

   bool Rt = IsLocal() || IsRemote();

   return( Rt );

}

bool const
TScenIniFile::GetAntiSpoofFlag
   (
   )
{
   return( ReadInteger( ControlSection, AntiSpoofFlagKey, AntiSpoofFlagDef ) );
}

void
TScenIniFile::SetAntiSpoofFlag
   (
   const bool                InAntiSpoofFlag
   )
{
   WriteInteger( ControlSection, AntiSpoofFlagKey, InAntiSpoofFlag );
}

bool const
TScenIniFile::GetWaitForStartPulse
   (
   )
{
   return( ReadBool( ControlSection, WaitForStartPulseKey, WaitForStartPulseDef ) );
}

void
TScenIniFile::SetWaitForStartPulse
   (
   const bool                Wait
   )
{
   WriteBool( ControlSection, WaitForStartPulseKey, Wait );
}

void
TScenIniFile::SetAddHWCounterToInitTime
   (
   bool                      InAddHWCounterToInitTime
   )
{

   WriteBool( RTInitSection, RTInitAddHWCounterToInitTimeKey, InAddHWCounterToInitTime );

}

bool const
TScenIniFile::GetAddHWCounterToInitTime
   (
   )
{

   return( ReadBool( RTInitSection, RTInitAddHWCounterToInitTimeKey, RTInitAddHWCounterToInitTimeDef ) );

}


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//
//   SyncToSky - Auto Start Parameters
//
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------




bool const
TScenIniFile::GetSyncToSkyAutoStart
   (
   )
{

   return( ReadBool( SyncToSkySection, nScenIniSyncToSky::AutoStartKey, nScenIniSyncToSky::AutoStartDef ) );

}
void
TScenIniFile::SetSyncToSkyAutoStart
   (
   const bool InAutoStart
   )
{
   WriteBool( SyncToSkySection, nScenIniSyncToSky::AutoStartKey, InAutoStart );
}

bool const
TScenIniFile::GetSyncAutoAllowOverride
   (
   )
{

   return( ReadBool( SyncToSkySection, nScenIniSyncToSky::AutoStartAllowOverrideKey, nScenIniSyncToSky::AutoStartAllowOverrideDef ) );

}
void
TScenIniFile::SetSyncAutoAllowOverride
   (
   const bool InAutoStartAllowOverride
   )
{
   WriteBool( SyncToSkySection, nScenIniSyncToSky::AutoStartAllowOverrideKey, InAutoStartAllowOverride );
}

using namespace nScenIniSyncToSky;

TSyncAutoPrms const
TScenIniFile::SyncAutoStrToPrms
   (
   const AnsiString        & PrmsStr
   ) const
{

   TStringList * Fields    = new TStringList();

   ExtractTokensL( PrmsStr, AnsiString( "," ), '\'', true, Fields );

   TSyncAutoPrms     Prms;

   if ( Fields->Count == 4 )
   {
      Prms.StepEnabled                 = (bool) Fields->Strings[0].ToIntDef( 0 );
      Prms.StepTimeoutEnabled          = (bool) Fields->Strings[1].ToIntDef( 0 );
      Prms.StepTimeoutResetEnabled     = (bool) Fields->Strings[2].ToIntDef( 0 );
      Prms.StepTimeout                 = (int)  Fields->Strings[3].ToIntDef( 100 );
   }

   delete Fields;

   return( Prms );

}

AnsiString const
TScenIniFile::SyncAutoPrmsToStr
   (
   const TSyncAutoPrms     & Prms
   ) const
{

   AnsiString Str  = Prms.StepEnabled ? AnsiString( "1" ) : AnsiString( "0" );

   Str            += AnsiString( "," );

   Str            += Prms.StepTimeoutEnabled ? AnsiString( "1" ) : AnsiString( "0" );

   Str            += AnsiString( "," );

   Str            += Prms.StepTimeoutResetEnabled ? AnsiString( "1" ) : AnsiString( "0" );

   Str            += AnsiString( "," );

   Str            += AnsiString( Prms.StepTimeout );

   return( Str );

}

TSyncAutoPrms const
TScenIniFile::GetSyncAutoRefDataValid
   (
   )
{

   const AnsiString Str = ReadString( SyncToSkySection, AutoRefDataValidKey, AutoRefDataValidDef );

   return( SyncAutoStrToPrms( Str ) );

}

void
TScenIniFile::SetSyncAutoRefDataValid
   (
   const TSyncAutoPrms     & InPrms
   )
{

   WriteString( SyncToSkySection, AutoRefDataValidKey, SyncAutoPrmsToStr( InPrms ) );

}

TSyncAutoPrms const
TScenIniFile::GetSyncAutoRcv1PPS
   (
   )
{

   const AnsiString Str = ReadString( SyncToSkySection, AutoRcv1PPSKey, AutoRcv1PPSDef );

   return( SyncAutoStrToPrms( Str ) );

}

void
TScenIniFile::SetSyncAutoRcv1PPS
   (
   const TSyncAutoPrms     & InPrms
   )
{

   WriteString( SyncToSkySection, AutoRcv1PPSKey, SyncAutoPrmsToStr( InPrms ) );

}

TSyncAutoPrms const
TScenIniFile::GetSyncAuto1PPSValid
   (
   )
{

   const AnsiString Str = ReadString( SyncToSkySection, Auto1PPSValidKey, Auto1PPSValidDef );

   return( SyncAutoStrToPrms( Str ) );

}

void
TScenIniFile::SetSyncAuto1PPSValid
   (
   const TSyncAutoPrms     & InPrms
   )
{

   WriteString( SyncToSkySection, Auto1PPSValidKey, SyncAutoPrmsToStr( InPrms ) );

}

TSyncAutoPrms const
TScenIniFile::GetSyncAutoArmReset
   (
   )
{

   const AnsiString Str = ReadString( SyncToSkySection, AutoArmResetKey, AutoArmResetDef );

   return( SyncAutoStrToPrms( Str ) );

}

void
TScenIniFile::SetSyncAutoArmReset
   (
   const TSyncAutoPrms     & InPrms
   )
{

   WriteString( SyncToSkySection, AutoArmResetKey, SyncAutoPrmsToStr( InPrms ) );

}

TSyncAutoPrms const
TScenIniFile::GetSyncAutoComplete
   (
   )
{

   const AnsiString Str = ReadString( SyncToSkySection, AutoCompleteKey, AutoCompleteDef );

   return( SyncAutoStrToPrms( Str ) );

}

void
TScenIniFile::SetSyncAutoComplete
   (
   const TSyncAutoPrms     & InPrms
   )
{

   WriteString( SyncToSkySection, AutoCompleteKey, SyncAutoPrmsToStr( InPrms ) );

}

bool const
TScenIniFile::GetSyncRemote
   (
   )
{
   return( ReadBool( SyncToSkySection, SyncRemoteKey, SyncRemoteDef ) );
}

void
TScenIniFile::SetSyncRemote
   (
   const bool                InSyncRemote
   )
{

   WriteBool( SyncToSkySection, SyncRemoteKey, InSyncRemote );

}


