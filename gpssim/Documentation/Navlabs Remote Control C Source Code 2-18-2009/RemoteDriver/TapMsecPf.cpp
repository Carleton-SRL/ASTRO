#include "pch.h"
#pragma hdrstop

#ifndef TapMsecPfH
#include "TapMsecPf.h"
#endif

#ifndef Wgs84H
#include "Wgs84.h"
#endif

//---------------------------------------------------------------------------
//
// $Workfile:: TapMsecPf.cpp                                         $
//
// $Revision:: 1                                                     $
//
// $History:: TapMsecPf.cpp                                          $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 3/30/04    Time: 11:55a
//Created in $/RemoteDriver
//
//
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Constants
//

//---------------------------------------------------------------------------
//   [TAPMSEC]
//

static const AnsiString TapMsecSection( "TAPMSEC" );

static const AnsiString AttenIncrementKey( "AttenIncrement" );
static const AnsiString ShowDebugKey( "ShowDebug" );
static const AnsiString LogMissedIntsKey( "LogMissedInts" );

static const AnsiString ExitBadCalKey( "ExitBadCal" );
static const bool       ExitBadCalDef( false );

static const AnsiString SaveReportParamsKey( "SaveReportParams" );
static const bool       SaveReportParamsDef( false );

static const AnsiString CodeSiteEnabledKey( "CodeSiteEnabled" );
static const bool       CodeSiteEnabledDef( false );

static const AnsiString ResetCountersKey( "ResetCounters" );
static const bool       ResetCountersDef( false );

//---------------------------------------------------------------------------
//   [TAPMSECDISPLAY]
//

static const AnsiString TapMsecDisplaySection( "TAPMSECDISPLAY" );

static const AnsiString DispRelativePowerKey( "DispRelativePower" );
static const bool       DispRelativePowerDef( true );

static const AnsiString CreateRcvrAsDialogKey( "CreateRcvrAsDialog" );
static const bool       CreateRcvrAsDialogDef( false );

static const AnsiString ShowVehLftPnlSplitterHotSpotKey( "ShowVehLftPnlSplitterHotSpot" );
static const bool       ShowVehLftPnlSplitterHotSpotDef( false );

static const AnsiString ShowVehRghtPnlSplitterHotSpotKey( "ShowVehRghtPnlSplitterHotSpot" );
static const bool       ShowVehRghtPnlSplitterHotSpotDef( false );

static const AnsiString ShowLLAScaleSplitterHotSpotKey( "ShowLLAScaleSplitterHotSpot" );
static const bool       ShowLLAScaleSplitterHotSpotDef( false );

static const AnsiString UseGpsTimeForXAxisKey( "UseGpsTimeForXAxis" );
static const bool       UseGpsTimeForXAxisDef( false );

static const AnsiString ResetErrPlotOnTimeResetKey( "ResetErrPlotOnTimeReset" );
static const bool       ResetErrPlotOnTimeResetDef( false );

static const AnsiString ResetErrPlotOnFirstNavKey( "ResetErrPlotOnFirstNav" );
static const bool       ResetErrPlotOnFirstNavDef( true );

static const AnsiString ErrorPlotEnabledKey( "ErrorPlotEnabled" );
static const bool       ErrorPlotEnabledDef( true );

static const AnsiString ErrorPlotPointsAppendKey( "ErrorPlotPointsAppend" );
static const bool       ErrorPlotPointsAppendDef( true );

static const AnsiString Gt2DPlotEnabledKey( "Gt2DPlotEnabled" );
static const bool       Gt2DPlotEnabledDef( true );

static const AnsiString Gt3DPlotEnabledKey( "Gt3DPlotEnabled" );
static const bool       Gt3DPlotEnabledDef( true );

static const AnsiString ErrorPlotMaxPointsKey( "ErrorPlotMaxPoints" );
static const int        ErrorPlotMaxPointsDef( 7200 );

//---------------------------------------------------------------------------
//   [NAVSTATEFRAME]
//

namespace NNavStateFrame
{

static const AnsiString NavStateFrameSeciont( "NAVSTATEFRAME" );

static const AnsiString ToolbarClosedKey( "ToolbarClosed" );
static const bool       ToolbarClosedDef( true );

static const AnsiString ToolbarHotSpotVisibleKey( "ToolbarHotSpotVis" );
static const bool       ToolbarHotSpotVisibleDef( true );
};
//---------------------------------------------------------------------------
//   [TAPPTINIT]
//

static const AnsiString PTSection( "TAPPTINIT" );

static const AnsiString PTLatKey( "Lat" );
static const AnsiString PTLatDef( "34.000000" );

static const AnsiString PTLonKey( "Lon" );
static const AnsiString PTLonDef( "-118.000000" );

static const AnsiString PTAltKey( "Alt" );
static const AnsiString PTAltDef( "0.00" );

static const AnsiString PTDateKey( "Date" );
static const AnsiString PTDateDef( "1/30/2001" );

static const AnsiString PTTimeKey( "Time" );
static const AnsiString PTTimeDef( "12:00:00" );

static const AnsiString PTInitFromClockKey( "InitFromClock" );
static const bool       PTInitFromClockDef( true );

static const AnsiString PTRefLocalTimeKey("RefLocalTime");
static const bool       PTRefLocalTimeDef( true );

static const int        DefShowDebug(0);
static const int        DefLogMissedInts(0);

static const AnsiString SyncToSkySection("SYNCTOSKY");

//---------------------------------------------------------------------------
// PPS Section [PPS]
//
static const AnsiString PPSSection( "PPS" );

static const AnsiString PPSWidthKey( "PPSWidth" );
static const int        PPSWidthDef( 1 );

static const AnsiString PPSAlwaysOnKey( "PPSAlwaysOn" );
static const bool       PPSAlwaysOnDef( false );

static const AnsiString VariableOutputPulseKey( "VariableOutputPulse" );
static const bool       VariableOutputPulseDef( 0 );

static const AnsiString VariableOutputPulseRateKey( "VariableOutputPulseRate" );
static const int        VariableOutputPulseRateDef( 256 );

static const AnsiString VariableOutputPulseWidthKey( "VariableOutputPulseWidth" );
static const int        VariableOutputPulseWidthDef( 1 );

static const AnsiString VariableOutputPulseAlwaysOnKey( "VariableOutputPulseAlwaysOn" );
static const bool       VariableOutputPulseAlwaysOnDef( 0 );

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
// GPIB Section [GPIB]
//
static const AnsiString GpibSection( "GPIB" );

static const AnsiString GpibPrimaryDeviceAddressKey( "PrimaryDeviceAddress" );
static const int        GpibPrimaryDeviceAddressDef( 15 );
static const AnsiString GpibSecondaryDeviceAddressKey( "SecondaryDeviceAddress" );
static const int        GpibSecondaryDeviceAddressDef( 0 );
static const AnsiString GpibBoardIndexKey( "BoardIndex" );
static const int        GpibBoardIndexDef( 0 );
static const AnsiString GpibWriteErrorKey( "WriteError" );
static const int        GpibWriteErrorDef( 0 );
static const AnsiString GpibStartDelayKey( "StartDelay" );
static const int        GpibStartDelayDef( 15 );
static const AnsiString GpibControllerKey( "Controller" );
static const int        GpibControllerDef( 1 );
static const AnsiString GpibTimeoutKey( "TimeOut" );
static const int        GpibTimeoutIntDef( T100ms );
static const AnsiString GpibTimeoutDef( "T100ms" );


//---------------------------------------------------------------------------
// RtMotionMem Section [RTMOTIONMEM]
//
static const AnsiString RtMotionMemSection( "RTMOTIONMEM" );

static const AnsiString RtMotionMemExtToSimOffsetKey( "ExtToSimOffset" );
static const int        RtMotionMemExtToSimOffsetDef( 0 );
static const AnsiString RtMotionMemSimToExtOffsetKey( "SimToExtOffset" );
static const int        RtMotionMemSimToExtOffsetDef( 2048 );
static const AnsiString RtMotionMemClearDataAtStartKey( "ClearDataAtStart" );
static const bool       RtMotionMemClearDataAtStartDef( true );

//---------------------------------------------------------------------------
// BIT Section
//
static const AnsiString BitSection( "BIT" );

static const int NUM_XILINX_TO_TEST = 3;

static const AnsiString TestX1Key( "TestX1" );
static const int        TestX1Def( 1 );
static const AnsiString TestX2Key( "TestX2" );
static const int        TestX2Def( 0 );
static const AnsiString TestX3Key( "TestX3" );
static const int        TestX3Def( 1 );
static const AnsiString TestIntKey( "TestInt" );
static const int        TestIntDef( 0 );

//---------------------------------------------------------------------------
// REPORT Section
//
static const AnsiString ReportSection( "REPORT" );

static const AnsiString ReportEnabledKey( "Enabled" );
static const int        ReportEnabledDef( 1 );
static const AnsiString ReportAppendKey( "Append" );
static const int        ReportAppendDef( 0 );
static const AnsiString ReportPrependDateTimeKey( "PrependDateTime" );
static const int        ReportPrependDateTimeDef( 0 );
static const AnsiString ReportUseCodeSiteKey( "UseCodeSite" );
static const int        ReportUseCodeSiteDef( 1 );
static const AnsiString ReportWriteDebugKey( "WriteDebug" );
static const int        ReportWriteDebugDef( 0 );
static const AnsiString ReportShowErrorFormKey( "ShowErrorForm" );
static const int        ReportShowErrorFormDef( 0 );

//---------------------------------------------------------------------------
// CRPA Lite Section
//
static const AnsiString CrpaLiteSection( "CRPALITE" );

static const AnsiString CrpaLiteEnabledKey( "Enabled" );
static const int        CrpaLiteEnabledDef( 0 );
static const AnsiString CrpaLiteNumRfsKey( "NumRfs" );
static const int        CrpaLiteNumRfsDef( 1 );

//---------------------------------------------------------------------------
// Remote Section
//
static const AnsiString RemoteSection( "REMOTE" );

static const AnsiString RemoteCompensateTimeKey( "CompensateTime" );
static const int        RemoteCompensateTimeDef( 0 );

static const AnsiString RemoteCompensateTimeDeltaKey( "CompensateTimeDelta" );
static const int        RemoteCompensateTimeDeltaDef( 2 );

static const AnsiString RemoteWriteDebugWaitResultsKey( "WriteDebugWaitResults" );
static const bool       RemoteWriteDebugWaitResultsDef( false );

static const AnsiString RemoteStoreTruthTimeDeltaKey( "StoreTruthTimeDelta" );
static const double     RemoteStoreTruthTimeDeltaDef( 5.0 );

//---------------------------------------------------------------------------
// MFIO Section
//
static const AnsiString MfioSection( "MFIO" );

static const AnsiString TestModeMfioKey( "TestMode" );
static const bool       TestModeMfioDef( false );

//---------------------------------------------------------------------------
// VPGMSECINTERFACE Section
//
static const AnsiString VpgMsecInterfaceSection( "VPGMSECINTERFACE" );

static const AnsiString RangeTruthFileRateKey( "RangeTruthFileRate" );
static const int        RangeTruthFileRateDef( 10 );

TTapMsecProfile::TTapMsecProfile
   (
   ) :
   TIniFile( "Voyager.ini" )
{}

double const
TTapMsecProfile::GetAttenIncrement
   (
   )
{
   return( ReadFloat( TapMsecSection, AttenIncrementKey, 0.5 ) );
}

void
TTapMsecProfile::SetAttenIncrement
   (
   const double AttenIncrement
   )
{
   WriteFloat(TapMsecSection,AttenIncrementKey,AttenIncrement);
}

bool const
TTapMsecProfile::GetCreateRcvrAsDialog
   (

   )
{
   return( ReadBool( TapMsecDisplaySection, CreateRcvrAsDialogKey, false ) );
}

void
TTapMsecProfile::SetCreateRcvrAsDialog
   (
   const bool                CreateRcvrAsDialog
   )
{
   WriteBool( TapMsecDisplaySection, CreateRcvrAsDialogKey, CreateRcvrAsDialogDef );
}

bool const
TTapMsecProfile::GetShowVehLftPnlSplitterHotSpot
   (
   )
{
   return( ReadBool( TapMsecDisplaySection, ShowVehLftPnlSplitterHotSpotKey, ShowVehLftPnlSplitterHotSpotDef ) );
}
void
TTapMsecProfile::SetShowVehLftPnlSplitterHotSpot
   (
   const bool                Show
   )
{
   WriteBool( TapMsecDisplaySection, ShowVehLftPnlSplitterHotSpotKey, Show );
}

bool const
TTapMsecProfile::GetShowVehRghtPnlSplitterHotSpot
   (
   )
{
   return( ReadBool( TapMsecDisplaySection, ShowVehRghtPnlSplitterHotSpotKey, ShowVehRghtPnlSplitterHotSpotDef ) );
}

void
TTapMsecProfile::SetShowVehRghtPnlSplitterHotSpot
   (
   const bool                Show
   )
{
   WriteBool( TapMsecDisplaySection, ShowVehRghtPnlSplitterHotSpotKey, Show );
}

bool const
TTapMsecProfile::GetShowLLAScaleSplitterHotSpot
   (
   )
{
   return( ReadBool( TapMsecDisplaySection, ShowLLAScaleSplitterHotSpotKey, ShowLLAScaleSplitterHotSpotDef ) );
}

void
TTapMsecProfile::SetShowLLAScaleSplitterHotSpot
   (
   const bool                Show
   )
{
   WriteBool( TapMsecDisplaySection, ShowLLAScaleSplitterHotSpotKey, Show );
}

bool const
TTapMsecProfile::GetUseGpsTimeForXAxis
   (

   )
{
   return( ReadBool( TapMsecDisplaySection, UseGpsTimeForXAxisKey, UseGpsTimeForXAxisDef ) );
}

void
TTapMsecProfile::SetUseGpsTimeForXAxis
   (
   const bool                UseGpsTime
   )
{
   WriteBool( TapMsecDisplaySection, UseGpsTimeForXAxisKey, UseGpsTime );
}

bool const
TTapMsecProfile::GetResetErrPlotOnTimeReset
   (

   )
{
   return( ReadInteger( TapMsecDisplaySection, ResetErrPlotOnTimeResetKey, ResetErrPlotOnTimeResetDef ) );
}

void
TTapMsecProfile::SetResetErrPlotOnTimeReset
   (
   const bool                Reset
   )
{
   WriteInteger( TapMsecDisplaySection, ResetErrPlotOnTimeResetKey, Reset );
}

bool const
TTapMsecProfile::GetResetErrPlotOnFirstNav
   (

   )
{
   return( ReadBool( TapMsecDisplaySection, ResetErrPlotOnFirstNavKey, ResetErrPlotOnFirstNavDef ) );
}
void
TTapMsecProfile::SetResetErrPlotOnFirstNav
   (
   const bool                Reset
   )
{
   WriteBool( TapMsecDisplaySection, ResetErrPlotOnFirstNavKey, Reset );
}

bool const
TTapMsecProfile::GetErrorPlotEnabled
   (

   )
{
   return( ReadBool( TapMsecDisplaySection, ErrorPlotEnabledKey, ErrorPlotEnabledDef ) );
}
void
TTapMsecProfile::SetErrorPlotEnabled
   (
   const bool                InPlotEnabled
   )
{
   WriteBool( TapMsecDisplaySection, ErrorPlotEnabledKey, InPlotEnabled );
}


bool const
TTapMsecProfile::GetErrorPlotPointsAppend
   (

   )
{
   return( ReadBool( TapMsecDisplaySection, ErrorPlotPointsAppendKey, ErrorPlotPointsAppendDef ) );
}
void
TTapMsecProfile::SetErrorPlotPointsAppend
   (
   const bool                InPlotPointsAppend
   )
{
   WriteBool( TapMsecDisplaySection, ErrorPlotPointsAppendKey, InPlotPointsAppend );
}


int const
TTapMsecProfile::GetErrorPlotMaxPoints
   (

   )
{
   return( ReadInteger( TapMsecDisplaySection, ErrorPlotMaxPointsKey, ErrorPlotMaxPointsDef ) );
}

void
TTapMsecProfile::SetErrorPlotMaxPoints
   (
   const int                 InPlotMaxPoints
   )
{
   WriteInteger( TapMsecDisplaySection, ErrorPlotMaxPointsKey, InPlotMaxPoints );
}

bool const
TTapMsecProfile::GetGt2DPlotEnabled
   (

   )
{
   return( ReadBool( TapMsecDisplaySection, Gt2DPlotEnabledKey, Gt2DPlotEnabledDef ) );
}
void
TTapMsecProfile::SetGt2DPlotEnabled
   (
   const bool                InPlotEnabled
   )
{
   WriteBool( TapMsecDisplaySection, Gt2DPlotEnabledKey, InPlotEnabled );
}


bool const
TTapMsecProfile::GetGt3DPlotEnabled
   (

   )
{
   return( ReadBool( TapMsecDisplaySection, Gt3DPlotEnabledKey, Gt3DPlotEnabledDef ) );
}

void
TTapMsecProfile::SetGt3DPlotEnabled
   (
   const bool                InPlotEnabled
   )
{
   WriteBool( TapMsecDisplaySection, Gt3DPlotEnabledKey, InPlotEnabled );
}

TDateTime const
TTapMsecProfile::GetDate
   (
   )
{


   AnsiString DateStr = ReadString(PTSection,PTDateKey,TDateTime::CurrentDate().DateString());
   if ( !DateStr.Length() )
   {
      DateStr = TDateTime::CurrentDate().DateString();
   }

   return ( StrToDate( DateStr ) );

}

TDateTime const
TTapMsecProfile::GetTime
   (
   )
{

   AnsiString TimeStr = ReadString(PTSection,PTTimeKey,TDateTime::CurrentTime().TimeString());

   return ( StrToTime( TimeStr ) );

}

bool const
TTapMsecProfile::GetInitFromClock
   (
   )
{

   return( ReadBool( PTSection, PTInitFromClockKey, PTInitFromClockDef ) );

}

#if(0)

void
TTapMsecProfile::GetPos
   (
   double &Lat,
   double &Lon,
   double &Alt
   )
{

   AnsiString LatStr = ReadString( PTSection, PTLatKey, PTLatDef );
   AnsiString LonStr = ReadString( PTSection, PTLonKey, PTLonDef );
   AnsiString AltStr = ReadString( PTSection, PTAltKey, PTAltDef );

   Lat = LatStr.ToDouble();
   Lon = LonStr.ToDouble();
   Alt = AltStr.ToDouble();

}

void
TTapMsecProfile::SetPos
   (
   double Lat,
   double Lon,
   double Alt
   )
{

   char Str[100];
   sprintf(Str,"%12.7lf",Lat);
   WriteString( PTSection, PTLatKey, AnsiString(Str) );

   sprintf(Str,"%12.7lf",Lon);
   WriteString( PTSection, PTLonKey, AnsiString(Str) );

   sprintf(Str,"%10.2lf",Alt);
   WriteString( PTSection, PTAltKey, AnsiString(Str) );

}
#endif

TPosVec const
TTapMsecProfile::GetPos
   (
   )
{

   AnsiString LatStr = ReadString( PTSection, PTLatKey, PTLatDef );
   AnsiString LonStr = ReadString( PTSection, PTLonKey, PTLonDef );
   AnsiString AltStr = ReadString( PTSection, PTAltKey, PTAltDef );

   TPosVec PosVec;
   PosVec.Lat = LatStr.ToDouble();
   PosVec.Lon = LonStr.ToDouble();
   PosVec.Alt = AltStr.ToDouble();

   return( PosVec );

}

void
TTapMsecProfile::SetPos
   (
   const TPosVec & PosVec
   )
{

   AnsiString Str;
   Str.sprintf( "%12.7lf", PosVec.Lat*R2D );
   WriteString( PTSection, PTLatKey, Str );

   Str.sprintf( "%12.7lf", PosVec.Lon*R2D );
   WriteString( PTSection, PTLonKey, Str );

   Str.sprintf( "%12.7lf", PosVec.Alt );
   WriteString( PTSection, PTAltKey, Str );

}

void
TTapMsecProfile::SetDate
   (
   const TDateTime         & Date
   )
{

   WriteString( PTSection, PTDateKey, Date.DateString() );

}

void
TTapMsecProfile::SetTime
   (
   const TDateTime           & Time
   )
{

   WriteString( PTSection, PTTimeKey, Time.TimeString() );

}

void
TTapMsecProfile::SetInitFromClock
   (
   bool                      InInitFromClock
   )
{

   WriteBool( PTSection, PTInitFromClockKey, InInitFromClock );

}

void
TTapMsecProfile::SetRefLocalTime
   (
   bool                      InRefLocalTime
   )
{

   WriteBool( PTSection, PTRefLocalTimeKey, InRefLocalTime );

}

bool const
TTapMsecProfile::GetRefLocalTime
   (
   )
{

   return( ReadBool( PTSection, PTRefLocalTimeKey, PTRefLocalTimeDef ) );

}


bool const
TTapMsecProfile::GetShowDebug
   (

   )
{
   return( ReadInteger( TapMsecSection, ShowDebugKey, DefShowDebug ) );
}

bool const
TTapMsecProfile::GetDispRelativePower
   (

   )
{
   return( ReadBool( TapMsecDisplaySection, DispRelativePowerKey, DispRelativePowerDef ) );
}

void
TTapMsecProfile::SetDispRelativePower
   (
   const bool                InDispRelativePower
   )
{
   WriteBool( TapMsecDisplaySection, DispRelativePowerKey, InDispRelativePower );
}

bool const
TTapMsecProfile::GetPPSAlwaysOn()
{
   return( ReadBool( PPSSection, PPSAlwaysOnKey, PPSAlwaysOnDef ) );
}

int const
TTapMsecProfile::GetPPSWidth()
{
   return( ReadInteger( PPSSection, PPSWidthKey, PPSWidthDef ) );
}

void
TTapMsecProfile::SetPPSAlwaysOn
   (
   const bool PPSAlwaysOn
   )
{
   WriteInteger( PPSSection, PPSAlwaysOnKey, PPSAlwaysOn );
}

void
TTapMsecProfile::SetPPSWidth
   (
   const int PPSWidth
   )
{
   WriteInteger( PPSSection, PPSWidthKey, PPSWidth );
}

bool const
TTapMsecProfile::GetVariableOutputPulse
   (
   )
{
   return( ReadBool( PPSSection, VariableOutputPulseKey, VariableOutputPulseDef ) );
}

int const
TTapMsecProfile::GetVariableOutputPulseRate
   (
   )
{
   return( ReadInteger( PPSSection, VariableOutputPulseRateKey, VariableOutputPulseRateDef ) );
}

int const
TTapMsecProfile::GetVariableOutputPulseWidth
   (
   )
{
   return( ReadInteger( PPSSection, VariableOutputPulseWidthKey, VariableOutputPulseWidthDef ) );
}

bool const
TTapMsecProfile::GetVariableOutputPulseAlwaysOn
   (
   )
{
   return( ReadBool( PPSSection, VariableOutputPulseAlwaysOnKey, VariableOutputPulseAlwaysOnDef ) );
}

void
TTapMsecProfile::SetVariableOutputPulse
   (
   const bool                Enabled
   )
{
   WriteBool( PPSSection, VariableOutputPulseKey, Enabled );
}

void
TTapMsecProfile::SetVariableOutputPulseAlwaysOn
   (
   const bool                On
   )
{
   WriteBool( PPSSection, VariableOutputPulseAlwaysOnKey, On );
}

void
TTapMsecProfile::SetVariableOutputPulseRate
   (
   const int                 Rate
   )
{
   WriteInteger( PPSSection, VariableOutputPulseRateKey, Rate );
}

void
TTapMsecProfile::SetVariableOutputPulseWidth
   (
   const int                 Width
   )
{
   WriteInteger( PPSSection, VariableOutputPulseWidthKey, Width );
}



bool const
TTapMsecProfile::GetBitTestX1()
{
   return( ReadInteger( BitSection, TestX1Key, TestX1Def ) );
}

void
TTapMsecProfile::SetBitTestX1
   (
   const bool TestX1
   )
{
   WriteInteger( BitSection, TestX1Key, TestX1 );
}

bool const
TTapMsecProfile::GetBitTestX2()
{
   return( ReadInteger( BitSection, TestX2Key, TestX2Def ) );
}

void
TTapMsecProfile::SetBitTestX2
   (
   const bool TestX2
   )
{
   WriteInteger( BitSection, TestX2Key, TestX2 );
}

bool const
TTapMsecProfile::GetBitTestX3()
{
   return( ReadInteger( BitSection, TestX3Key, TestX3Def ) );
}

void
TTapMsecProfile::SetBitTestX3
   (
   const bool TestX3
   )
{
   WriteInteger( BitSection, TestX3Key, TestX3 );
}

bool const
TTapMsecProfile::GetBitTestInt()
{
   return( ReadInteger( BitSection, TestIntKey, TestIntDef ) );
}

void
TTapMsecProfile::SetBitTestInt
   (
   const bool TestInt
   )
{
   WriteInteger( BitSection, TestIntKey, TestInt );
}

bool const
TTapMsecProfile::GetBitTestX
   (
   const int Index
   )
{

   const AnsiString TestXKey[NUM_XILINX_TO_TEST] = { TestX1Key, TestX2Key, TestX3Key };
   const int        TestXDef[NUM_XILINX_TO_TEST] = { TestX1Def, TestX2Def, TestX3Def };

   bool TestX                                    = false;

   if ( Index >= 0 && Index < NUM_XILINX_TO_TEST )
   {
      TestX = ReadInteger( BitSection, TestXKey[Index], TestXDef[Index] );
   }

   return( TestX );

}

void
TTapMsecProfile::SetBitTestX
   (
   const int  Index,
   const bool TestX
   )
{

   const AnsiString TestXKey[NUM_XILINX_TO_TEST] = { TestX1Key, TestX2Key, TestX3Key };

   if ( Index >= 0 && Index < NUM_XILINX_TO_TEST )
   {
      WriteInteger( BitSection, TestXKey[Index], TestX );
   }
}

void
TTapMsecProfile::GetReportParams
   (
   const AnsiString        & Module,
   bool                    & Enabled,
   bool                    & Append,
   bool                    & PrependDateTime,
   bool                    & UseCodeSite,
   bool                    & WriteDebug,
   bool                    & ShowErrorForm
   )
{

   const AnsiString Section( ReportSection + Module.UpperCase() );
   Enabled         = ReadBool( Section, ReportEnabledKey, ReportEnabledDef );
   Append          = ReadBool( Section, ReportAppendKey, ReportAppendDef );
   PrependDateTime = ReadBool( Section, ReportPrependDateTimeKey, ReportPrependDateTimeDef );
   UseCodeSite     = ReadBool( Section, ReportUseCodeSiteKey, ReportUseCodeSiteDef );
   WriteDebug      = ReadBool( Section, ReportWriteDebugKey, ReportWriteDebugDef );
   ShowErrorForm   = ReadBool( Section, ReportShowErrorFormKey, ReportShowErrorFormDef );

}
void
TTapMsecProfile::SetReportParams
   (
   const AnsiString        & Module,
   const bool                Enabled,
   const bool                Append,
   const bool                PrependDateTime,
   const bool                UseCodeSite,
   const bool                WriteDebug,
   const bool                ShowErrorForm
   )
{

   const AnsiString Section( ReportSection + Module.UpperCase() );

   WriteBool( Section, ReportEnabledKey, Enabled );
   WriteBool( Section, ReportAppendKey, Append );
   WriteBool( Section, ReportPrependDateTimeKey, PrependDateTime );
   WriteBool( Section, ReportUseCodeSiteKey, UseCodeSite );
   WriteBool( Section, ReportWriteDebugKey, WriteDebug );
   WriteBool( Section, ReportShowErrorFormKey, ShowErrorForm );

}

bool const
TTapMsecProfile::GetSaveReportParams
   (
   )
{
   return( ReadBool( TapMsecSection, SaveReportParamsKey, SaveReportParamsDef ) );
}

void
TTapMsecProfile::SetSaveReportParams
   (
   const bool                InSaveReportParams
   )
{
   WriteBool( TapMsecSection, SaveReportParamsKey, InSaveReportParams );
}

bool const
TTapMsecProfile::GetCodeSiteEnabled
   (
   )
{
   return( ReadBool( TapMsecSection, CodeSiteEnabledKey, CodeSiteEnabledDef ) );
}

void
TTapMsecProfile::SetCodeSiteEnabled
   (
   const bool                InCodeSiteEnabled
   )
{
   WriteBool( TapMsecSection, CodeSiteEnabledKey, InCodeSiteEnabled );
}

bool const
TTapMsecProfile::GetExitBadCal
   (
   )
{
   return( ReadInteger( TapMsecSection, ExitBadCalKey, ExitBadCalDef ) );
}

//---------------------------------------------------------------------------
//
//   CRPA Lite Section [CRPALITE]
//
//---------------------------------------------------------------------------

bool const
TTapMsecProfile::GetCrpaLite
   (
   )
{
   return( ReadInteger( CrpaLiteSection, CrpaLiteEnabledKey, CrpaLiteEnabledDef ) );
}

int const
TTapMsecProfile::GetCrpaLiteNumRfs
   (
   )
{
   return( ReadInteger( CrpaLiteSection, CrpaLiteNumRfsKey, CrpaLiteNumRfsDef ) );
}

//---------------------------------------------------------------------------
//
//   Remote Section [REMOTE]
//
//---------------------------------------------------------------------------

bool const
TTapMsecProfile::GetRemoteCompensateTime
   (
   )
{
   return( ReadInteger( RemoteSection, RemoteCompensateTimeKey, RemoteCompensateTimeDef ) );
}

void
TTapMsecProfile::SetRemoteCompensateTime
   (
   const bool                Compensate
   )
{
   WriteInteger( RemoteSection, RemoteCompensateTimeKey, Compensate );
}

int const
TTapMsecProfile::GetRemoteCompensateTimeDelta
   (
   )
{
   return( ReadInteger( RemoteSection, RemoteCompensateTimeDeltaKey, RemoteCompensateTimeDeltaDef ) );
}

void
TTapMsecProfile::SetRemoteCompensateTimeDelta
   (
   const int                 CompensateDelta
   )
{
   WriteInteger( RemoteSection, RemoteCompensateTimeDeltaKey, CompensateDelta );
}

bool const
TTapMsecProfile::GetRemoteWriteDebugWaitResults
   (
   )
{
   return( ReadBool( RemoteSection, RemoteWriteDebugWaitResultsKey, RemoteWriteDebugWaitResultsDef ) );
}

void
TTapMsecProfile::SetRemoteWriteDebugWaitResults
   (
   const bool                InWriteDebug
   )
{
   WriteBool( RemoteSection, RemoteWriteDebugWaitResultsKey, InWriteDebug );
}

double const
TTapMsecProfile::GetRemoteStoreTruthTimeDelta
   (
   )
{
   return( ReadFloat( RemoteSection, RemoteStoreTruthTimeDeltaKey, RemoteStoreTruthTimeDeltaDef ) );
}

void
TTapMsecProfile::SetRemoteStoreTruthTimeDelta
   (
   const double              TimeDelta
   )
{
   WriteFloat( RemoteSection, RemoteStoreTruthTimeDeltaKey, TimeDelta );
}


bool const
TTapMsecProfile::GetResetCounters
   (
   )
{
   return( ReadInteger( TapMsecSection, ResetCountersKey, ResetCountersDef ) );
}

void
TTapMsecProfile::SetResetCounters
   (
   const bool                InResetCounters
   )
{
   WriteInteger( TapMsecSection, ResetCountersKey, InResetCounters );
}

bool const
TTapMsecProfile::GetEthernetServer
   (

   )
{
   return( ReadInteger( EthernetSection, EthernetServerKey, EthernetServerDef ) );
}

void
TTapMsecProfile::SetEthernetServer
   (
   const bool IsEthernetServer
   )
{
   WriteInteger( EthernetSection, EthernetServerKey, IsEthernetServer );
}

bool const
TTapMsecProfile::GetEthernetClient
   (

   )
{
   return( !EthernetServer );
}

void
TTapMsecProfile::SetEthernetClient
   (
   const bool IsEthernetClient
   )
{
   EthernetServer = !IsEthernetClient;
}      

AnsiString const
TTapMsecProfile::GetEthernetHostAddress
   (

   )
{
   return( ReadString( EthernetSection, EthernetHostAddressKey, EthernetHostAddressDef ) );
}

void
TTapMsecProfile::SetEthernetHostAddress
   (
   const AnsiString &EthernetHostAddress
   )
{
   WriteString( EthernetSection, EthernetHostAddressKey, EthernetHostAddress );
}

int const
TTapMsecProfile::GetEthernetPortNum
   (

   )
{
   return( ReadInteger( EthernetSection, EthernetPortNumKey, EthernetPortNumDef ) );
}

void
TTapMsecProfile::SetEthernetPortNum
   (
   const int EthernetPortNum
   )
{
   WriteInteger( EthernetSection, EthernetPortNumKey, EthernetPortNum );
}

bool const
TTapMsecProfile::GetGpibWriteError
   (

   )
{

   return( ReadInteger( GpibSection, GpibWriteErrorKey, GpibWriteErrorDef ) );

}


int const
TTapMsecProfile::GetGpibPrimaryDeviceAddress
   (

   )
{

   return( ReadInteger( GpibSection, GpibPrimaryDeviceAddressKey, GpibPrimaryDeviceAddressDef ) );

}

int const
TTapMsecProfile::GetGpibSecondaryDeviceAddress
   (

   )
{

   return( ReadInteger( GpibSection, GpibSecondaryDeviceAddressKey, GpibSecondaryDeviceAddressDef ) );

}

int const
TTapMsecProfile::GetGpibBoardIndex
   (

   )
{
   return( ReadInteger( GpibSection, GpibBoardIndexKey, GpibBoardIndexDef ) );
}

int const
TTapMsecProfile::GetGpibStartDelay
   (

   )
{
   return( ReadInteger( GpibSection, GpibStartDelayKey, GpibStartDelayDef ) );
}

bool const
TTapMsecProfile::GetGpibController
   (

   )
{
   return( ReadInteger( GpibSection, GpibControllerKey, GpibControllerDef ) );
}

int const
TTapMsecProfile::GetGpibTimeout
   (
   )
{
   TGpibTimeout GpibTime( GpibTimeoutIntDef );
   AnsiString GpibTimeoutStr = ReadString( GpibSection, GpibTimeoutKey, GpibTimeoutDef );
   return( GpibTime.GetTimeout( GpibTimeoutStr ) );
}

void
TTapMsecProfile::SetGpibTimeout
   (
   const int Timeout
   )
{
   TGpibTimeout GpibTime( GpibTimeoutIntDef );
   WriteString( GpibSection, GpibTimeoutKey, GpibTime.GetTimeoutStr( Timeout ) );
}

//---------------------------------------------------------------------------
// RtMotionMem
//---------------------------------------------------------------------------

int const
TTapMsecProfile::GetRtMotionMemExtToSimOffset
   (
   )
{
   return( ReadInteger( RtMotionMemSection, RtMotionMemExtToSimOffsetKey, RtMotionMemExtToSimOffsetDef ) );
}

int const
TTapMsecProfile::GetRtMotionMemSimToExtOffset
   (
   )
{
   return( ReadInteger( RtMotionMemSection, RtMotionMemSimToExtOffsetKey, RtMotionMemSimToExtOffsetDef ) );
}

bool const
TTapMsecProfile::GetRtMotionMemClearDataAtStart
   (
   )
{
   return( ReadBool( RtMotionMemSection, RtMotionMemClearDataAtStartKey, RtMotionMemClearDataAtStartDef ) );
}

void
TTapMsecProfile::SetRtMotionMemExtToSimOffset
   (
   const int                 Offset
   )
{
   WriteInteger( RtMotionMemSection, RtMotionMemExtToSimOffsetKey, Offset );
}

void
TTapMsecProfile::SetRtMotionMemSimToExtOffset
   (
   const int                 Offset
   )
{
   WriteInteger( RtMotionMemSection, RtMotionMemSimToExtOffsetKey, Offset );
}

void
TTapMsecProfile::SetRtMotionMemClearDataAtStart
   (
   const bool                Clear
   )
{
   WriteBool( RtMotionMemSection, RtMotionMemClearDataAtStartKey, Clear );
}

//---------------------------------------------------------------------------
//
//   MFIO Section [MFIO]
//
//---------------------------------------------------------------------------

bool const
TTapMsecProfile::GetTestModeMfio
   (

   )
{
   return( ReadBool( MfioSection, TestModeMfioKey, TestModeMfioDef ) );
}

void
TTapMsecProfile::SetTestModeMfio
   (
   const bool                InTestModeMfio
   )
{
   WriteBool( MfioSection, TestModeMfioKey, InTestModeMfio );
}


//---------------------------------------------------------------------------
//
//   VPGMSECINTERFACE Section [VPGMSECINTERFACE]
//
//---------------------------------------------------------------------------

int const
TTapMsecProfile::GetRangeTruthFileRate
   (

   )
{
   return( ReadInteger( VpgMsecInterfaceSection, RangeTruthFileRateKey, RangeTruthFileRateDef ) );
}

void
TTapMsecProfile::SetRangeTruthFileRate
   (
   const int                 InRangeTruthFileRate
   )
{
   WriteInteger( VpgMsecInterfaceSection, RangeTruthFileRateKey, InRangeTruthFileRate );
}


