#include "pch.h"
#pragma hdrstop

#include "RciDriverMsgs.h"

static const AnsiString Comma( "," );

static const AnsiString SimModeIdleStr( "IDLE" );
static const AnsiString SimModeRunScenStr( "RUNSCEN" );
static const AnsiString SimModeRunLocalStr( "RUNLOCAL" );

static const AnsiString AckMsgValidStr( "MSGVALID" );
static const AnsiString AckMsgInvalidStr( "MSGINVALID" );
static const AnsiString AckSimModeValidStr( "SIMMODEVALID" );
static const AnsiString AckSimModeInvalidStr( "SIMMODEINVALID" );

static const AnsiString SysCfgL1OnlyStr( "L1" );
static const AnsiString SysCfgL2CapableStr( "L1/L2" );

//-----------------------------------------------------------------------------
// Start Scen
//
TStartScenMsg::TStartScenMsg
   (
   const AnsiString & ScenName
   ) :
   MsgId( StartScenMsgId )
{

   AnsiString Msg = AnsiString( "$" ) + MsgId + Comma;

   Msg += ScenName;

   SetBody( string( Msg.c_str() ) );

}

//-----------------------------------------------------------------------------
// Init Geo
//
TInitGeoMsg::TInitGeoMsg
   (
   const TDateTime & DateTime,
   const double LatDeg,
   const double LonDeg,
   const double Alt
   ) :
   MsgId( InitGeoMsgId )
{

   AnsiString Msg = AnsiString( "$" ) + MsgId + Comma;

   AnsiString LatStr;
   LatStr.sprintf("%10.7lf,", fabs( LatDeg ) );
   Msg += LatStr;

   AnsiString LatRefStr( "N," );
   if ( LatDeg < 0 )
   {
      LatRefStr = "S,";
   }
   Msg += LatRefStr;

   AnsiString LonStr;
   LonStr.sprintf("%11.7lf,", fabs( LonDeg ) );
   Msg += LonStr;

   AnsiString LonRefStr( "E," );
   if ( LonDeg < 0 )
   {
      LonRefStr = "W,";
   }
   Msg += LonRefStr;

   AnsiString AltStr;
   AltStr.sprintf( "%9.4lf,", Alt );

   Msg += AltStr;

   unsigned short Hour, Min, Sec, Millisec;
   DateTime.DecodeTime( &Hour, &Min, &Sec, &Millisec );

   unsigned short Day, Month, Year;
   DateTime.DecodeDate( &Year, &Month, &Day );

   AnsiString TimeStr;
   TimeStr.sprintf( "%2.2d%2.2d%2.2d,", Hour, Min, Sec );

   Msg += TimeStr;

   AnsiString DateStr;
   DateStr.sprintf( "%2.2d%2.2d%4.4d,", Day, Month, Year );

   Msg += DateStr;

   SetBody( string( Msg.c_str() ) );

}

//-----------------------------------------------------------------------------
// Start Local
//
TStartLocalMsg::TStartLocalMsg
   (
   ) :
   MsgId( StartLocalMsgId )
{

   AnsiString Msg = AnsiString( "$" ) + MsgId;

   SetBody( string( Msg.c_str() ) );

}

//-----------------------------------------------------------------------------
// Set Svid
//
TSetSvidMsg::TSetSvidMsg
   (
   const TChanSvidArray ChanSvidArray
   ) :
   MsgId( SetSvidMsgId )
{
   AnsiString Msg = AnsiString( "$" ) + MsgId + Comma;

   for ( unsigned int i=0; i<ChanSvidArray.size(); ++i )
   {
      Msg += AnsiString( ChanSvidArray[i].GetChan() ) + Comma;
      Msg += AnsiString( ChanSvidArray[i].GetSvid() );
      if ( i != ChanSvidArray.size()-1 )
      {
         Msg += Comma;
      }
   }

   SetBody( string( Msg.c_str() ) );

}

//-----------------------------------------------------------------------------
// Set Power
//
TSetPowerMsg::TSetPowerMsg
   (
   const TChanPowerArray ChanPowerArray
   ) :
   MsgId( SetPowerMsgId )
{
   AnsiString Msg = AnsiString( "$" ) + MsgId + Comma;

   for ( unsigned int i=0; i<ChanPowerArray.size(); ++i )
   {
      Msg += AnsiString( ChanPowerArray[i].GetChan() ) + Comma;
      Msg += AnsiString( ChanPowerArray[i].GetPower() );
      if ( i != ChanPowerArray.size()-1 )
      {
         Msg += Comma;
      }
   }

   SetBody( string( Msg.c_str() ) );

}

//-----------------------------------------------------------------------------
// Stop
//
TStopMsg::TStopMsg
   (
   ) :
   MsgId( StopMsgId )
{

   AnsiString Msg = AnsiString( "$" ) + MsgId;

   SetBody( string( Msg.c_str() ) );

}

//-----------------------------------------------------------------------------
// Shutdown
//
TShutdownMsg::TShutdownMsg
   (
   ) :
   MsgId( ShutdownMsgId )
{

   AnsiString Msg = AnsiString( "$" ) + MsgId;

   SetBody( string( Msg.c_str() ) );

}

//-----------------------------------------------------------------------------
// Query
//
TQueryMsg::TQueryMsg
   (
   const TExtQuery & ExtQuery
   ) :
   MsgId( QueryMsgId )
{
#define NUM_QUERY_TYPES ( 4 )
   AnsiString QueryTypeStr[NUM_QUERY_TYPES];
   QueryTypeStr[eQUERY_SIM_MODE]    = SimModeMsgId;
   QueryTypeStr[eQUERY_CHAN_STAT]   = ChanStatMsgId;
   QueryTypeStr[eQUERY_BIT_RESULTS] = BitResultsMsgId;
   QueryTypeStr[eQUERY_SYS_CFG]     = SysCfgMsgId;

#define NUM_QUERY_RATE_TYPES ( 4 )
   AnsiString QueryRateStr[NUM_QUERY_RATE_TYPES];
   QueryRateStr[eQUERY_OFF]       = AnsiString( "-2" );
   QueryRateStr[eQUERY_ONCE]      = AnsiString( "-1" );
   QueryRateStr[eQUERY_ON_CHANGE] = AnsiString( "0" );


   AnsiString Msg = AnsiString( "$" ) + MsgId + Comma;

   Msg += QueryTypeStr[ExtQuery.QueryType] + Comma;

   if ( ExtQuery.QueryTransRate == eQUERY_OFF )
   {
      Msg += AnsiString( "-2" );
   }
   else if ( ExtQuery.QueryTransRate == eQUERY_ONCE )
   {
      Msg += AnsiString( "-1" );
   }
   else if ( ExtQuery.QueryTransRate == eQUERY_ON_CHANGE )
   {
      Msg += AnsiString( "0" );
   }
   else
   {
      Msg += AnsiString( ExtQuery.Interval );
   }

   SetBody( string( Msg.c_str() ) );

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// From Simulator
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Simulator to External Base
//
TSimToExt::TSimToExt
   (
   const TInMsg &InMsg
   ) :
   Fields( NULL ),
   Valid( false )
{
   ( *this ) = InMsg;
}

TSimToExt &
TSimToExt::operator=
   (
   const TInMsg &InMsg
   )
{
   Fields = new TStringList();

   InMsg.GetFields( Fields );

   return( *this );
}

TSimToExt::~TSimToExt
   (
   )
{
   delete Fields;
}

//-----------------------------------------------------------------------------
// Sim Mode
//
TSimModeMsg::TSimModeMsg
   (
   const TInMsg &InMsg
   ) :
   TSimToExt( InMsg )
{

   ( *this ) = InMsg;

}

TSimModeMsg &
TSimModeMsg::operator=
   (
   const TInMsg &InMsg
   )
{


   try
   {
      AnsiString SimModeStr = Fields->Strings[0];

      if ( SimModeStr.AnsiCompareIC( SimModeIdleStr ) == 0 )
      {
         RciSimMode = eSimIdle;
      }
      else if ( SimModeStr.AnsiCompareIC( SimModeRunScenStr ) == 0 )
      {
         RciSimMode = eSimScen;
      }
      else if ( SimModeStr.AnsiCompareIC( SimModeRunLocalStr ) == 0 )
      {
         RciSimMode = eSimLocal;
      }
      Valid = true;
   }
   catch(...)
   {
      Valid = false;
   }

   return( *this );

}

//-----------------------------------------------------------------------------
// Channel Status (CHANSTAT)
//
TChanStatMsg::TChanStatMsg
   (
   const TInMsg &InMsg
   ) :
   TSimToExt( InMsg )
{

   ( *this ) = InMsg;

}

TChanStatMsg &
TChanStatMsg::operator=
   (
   const TInMsg &InMsg
   )
{


   try
   {

      for ( int i=0; i<Fields->Count; i += 3 )
      {

         int Chan  = Fields->Strings[i].ToInt();
         int Svid  = Fields->Strings[i+1].ToInt();
         int Power = Fields->Strings[i+2].ToInt();

         ChanStatArray.push_back( TChanStat( Chan, Svid, Power ) );

      }

      Valid = true;

   }
   catch(...)
   {
      Valid = false;
   }

   return( *this );

}

//-----------------------------------------------------------------------------
// BIT Results (BITRESULTS)
//
TBitResultsMsg::TBitResultsMsg
   (
   const TInMsg &InMsg
   ) :
   TSimToExt( InMsg )
{

   ( *this ) = InMsg;

}

TBitResultsMsg &
TBitResultsMsg::operator=
   (
   const TInMsg &InMsg
   )
{


   try
   {

      int FieldIndex = 0;

      BitError.Date      = Fields->Strings[FieldIndex++];
      BitError.Time      = Fields->Strings[FieldIndex++];
      BitError.x1        = Fields->Strings[FieldIndex++].ToInt();
      BitError.x2        = Fields->Strings[FieldIndex++].ToInt();
      BitError.x3        = Fields->Strings[FieldIndex++].ToInt();
      BitError.Interrupt = Fields->Strings[FieldIndex++].ToInt();
      BitError.Ocxo      = Fields->Strings[FieldIndex++].ToInt();
      BitError.Pll       = Fields->Strings[FieldIndex++].ToInt();

      Valid = true;

   }
   catch(...)
   {
      Valid = false;
   }

   return( *this );

}

//-----------------------------------------------------------------------------
// Ack (ACK)
//
TAckMsg::TAckMsg
   (
   const TInMsg &InMsg
   ) :
   TSimToExt( InMsg )
{

   ( *this ) = InMsg;

}

TAckMsg &
TAckMsg::operator=
   (
   const TInMsg &InMsg
   )
{


   try
   {

      int FieldIndex = 0;

      Ack.MsgId         = Fields->Strings[FieldIndex++];
      Ack.MsgValid      = ( Fields->Strings[FieldIndex++].AnsiCompareIC( AckMsgValidStr ) == 0 );
      Ack.SimModeValid  = ( Fields->Strings[FieldIndex++].AnsiCompareIC( AckSimModeValidStr ) == 0 );

      Valid = true;

   }
   catch(...)
   {
      Valid = false;
   }

   return( *this );

}

//-----------------------------------------------------------------------------
// SysCfg (ACK)
//
TSysCfgMsg::TSysCfgMsg
   (
   const TInMsg &InMsg
   ) :
   TSimToExt( InMsg )
{

   ( *this ) = InMsg;

}

TSysCfgMsg &
TSysCfgMsg::operator=
   (
   const TInMsg &InMsg
   )
{


   try
   {

      int FieldIndex = 0;

      SysCfg.NumChans      = Fields->Strings[FieldIndex++].ToInt();
      SysCfg.L2Capable     = ( Fields->Strings[FieldIndex++].AnsiCompareIC( SysCfgL2CapableStr ) == 0 );
      SysCfg.MinPower      = Fields->Strings[FieldIndex++].ToInt();
      SysCfg.MaxPower      = Fields->Strings[FieldIndex++].ToInt();

      Valid = true;

   }
   catch(...)
   {
      Valid = false;
   }

   return( *this );

}

