#ifndef RCIDRIVERMSGS_H
#define RCIDRIVERMSGS_H

#include "InMsg.h"
#include "OutMsg.h"
//-----------------------------------------------------------------------------
// From external to simulator
//
static const AnsiString StartScenMsgId( "STARTSCEN" );
static const AnsiString InitGeoMsgId( "INITGEO" );
static const AnsiString StartLocalMsgId( "STARTLOCAL" );
static const AnsiString SetSvidMsgId( "SETSVID" );
static const AnsiString SetPowerMsgId( "SETPOWER" );
static const AnsiString StopMsgId( "STOP" );
static const AnsiString ShutdownMsgId( "SHUTDOWN" );
static const AnsiString QueryMsgId( "QUERY" );

//-----------------------------------------------------------------------------
// From simulator to external
//
static const AnsiString SimModeMsgId( "SIMMODE" );
static const AnsiString ChanStatMsgId( "CHANSTAT" );
static const AnsiString BitResultsMsgId( "BITRESULTS" );
static const AnsiString AckMsgId( "ACK" );
static const AnsiString SysCfgMsgId( "SYSCFG" );


//-----------------------------------------------------------------------------
// Simulator to External Base
//
class TSimToExt {
protected:
   TStringList *Fields;
   bool        Valid;
public:
   TSimToExt( const TInMsg &InMsg );
   TSimToExt & operator=( const TInMsg &InMsg );
   virtual ~TSimToExt();
   bool const IsValid() const { return( Valid ); }
};


//-----------------------------------------------------------------------------
// Start Scen
//
class TStartScenMsg : public TOutMsg {
private:
   const AnsiString MsgId;
public:
   TStartScenMsg( const AnsiString & ScenName );

};

//-----------------------------------------------------------------------------
// Init Geo
//
class TInitGeoMsg : public TOutMsg {
private:
   const AnsiString MsgId;
public:
   TInitGeoMsg( const TDateTime & DateTime, const double LatDeg, const double LonDeg, const double Alt );

};

//-----------------------------------------------------------------------------
// Start Local
//
class TStartLocalMsg : public TOutMsg {
private:
   const AnsiString MsgId;
public:
   TStartLocalMsg( );

};

//-----------------------------------------------------------------------------
// Set Svid
//
class TChanSvid {
private:

   int Chan;
   int Svid;
public:

   TChanSvid( const int InChan=-1, const int InSvid=0 ) : Chan( InChan ), Svid( InSvid ) {}
   int const GetChan() const { return( Chan ); }
   int const GetSvid() const { return( Svid ); }

};

typedef vector<TChanSvid> TChanSvidArray;

class TSetSvidMsg : public TOutMsg {
private:
   const AnsiString MsgId;
public:
   TSetSvidMsg( const TChanSvidArray ChanSvidArray );
};

//-----------------------------------------------------------------------------
// Set Power
//
class TChanPower {
public:
   int    Chan;
   double Power;
public:
   TChanPower( const int InChan=-1, const double InPower=0 ) : Chan( InChan ), Power( InPower ) {}
   int const GetChan() const { return( Chan ); }
   int const GetPower() const { return( Power ); }

};

typedef vector<TChanPower> TChanPowerArray;

class TSetPowerMsg : public TOutMsg {
private:
   const AnsiString MsgId;
public:
   TSetPowerMsg( const TChanPowerArray ChanPowerArray );
};

//-----------------------------------------------------------------------------
// Stop
//
class TStopMsg : public TOutMsg {
private:
   const AnsiString MsgId;
public:
   TStopMsg( );

};

//-----------------------------------------------------------------------------
// Shutdown
//
class TShutdownMsg : public TOutMsg {
private:
   const AnsiString MsgId;
public:
   TShutdownMsg( );

};

//-----------------------------------------------------------------------------
// Query
//
typedef enum { eQUERY_SIM_MODE, eQUERY_CHAN_STAT, eQUERY_BIT_RESULTS, eQUERY_SYS_CFG } eQUERYTYPE;
typedef enum {  eQUERY_OFF=-2, eQUERY_ONCE=-1, eQUERY_ON_CHANGE=0, eQUERY_RATE } eQUERYTRANS;
class TExtQuery {
public:
   eQUERYTYPE   QueryType;
   eQUERYTRANS  QueryTransRate;
   int          Interval;
public:
   TExtQuery( const eQUERYTYPE InQueryType=eQUERY_SIM_MODE, const eQUERYTRANS InQueryTransRate=eQUERY_OFF, const int InInterval=0 ) :
      QueryType( InQueryType ), QueryTransRate( InQueryTransRate ), Interval( InInterval ) {}

};

class TQueryMsg : public TOutMsg {
private:
   const AnsiString MsgId;
public:
   TQueryMsg( const TExtQuery & ExtQuery );

};

//-----------------------------------------------------------------------------
// Sim Mode
//
class TSimModeMsg : public TSimToExt {

private:

   eRciSimMode RciSimMode;

public:

   TSimModeMsg( const TInMsg &InMsg );
   TSimModeMsg & operator=( const TInMsg &InMsg );
   eRciSimMode const GetSimMode() { return( RciSimMode); }
};

//-----------------------------------------------------------------------------
// Chan Stat
//

class TChanStat {
private:
   int Chan;
   int Svid;
   int L1Power;
   int L2Power;
public:
   TChanStat( const int InChan, const int InSvid=0, const int InL1Power=0, const int InL2Power = 0 ) :
      Chan( InChan), Svid( InSvid ), L1Power( InL1Power ), L2Power( InL2Power ) {}
   int const GetChan()    const { return( Chan ); }
   int const GetSvid()    const { return( Svid ); }
   int const GetL1Power() const { return( L1Power ); }
   int const GetL2Power() const { return( L2Power ); }

   friend bool const operator==( const TChanStat &cp1, const TChanStat &cp2 )
   {
      bool Same = true;
      if ( ( cp1.Chan != cp2.Chan ) || ( cp1.Svid != cp2.Svid ) || ( cp1.L1Power!= cp2.L1Power ) || ( cp1.L2Power != cp2.L2Power ) )
      {
         Same = false;
      }
      return( Same );
   }
   friend bool const operator!=( const TChanStat &cp1, const TChanStat &cp2 )
   {
      return( !( cp1 == cp2 ) );
   }
};

typedef vector<TChanStat> TChanStatArray;

class TChanStatMsg : public TSimToExt {

private:

   TChanStatArray ChanStatArray;

public:

   TChanStatMsg( const TInMsg &InMsg );
   TChanStatMsg & operator=( const TInMsg &InMsg );
   TChanStatArray const GetChanStatArray() { return( ChanStatArray ); }
};

//-----------------------------------------------------------------------------
// Bit Results (BITRESULTS)
//
class TBitError {
public:

   AnsiString Date;
   AnsiString Time;
   bool x1;
   bool x2;
   bool x3;
   bool Interrupt;
   bool Ocxo;
   bool Pll;

public:

   TBitError( ) : x1( false ), x2( false ), x3( false ), Interrupt( false ),
      Ocxo( false ), Pll( false ) {};
};

class TBitResultsMsg : public TSimToExt {

private:

   TBitError BitError;

public:

   TBitResultsMsg( const TInMsg &InMsg );
   TBitResultsMsg & operator=( const TInMsg &InMsg );
   TBitError const GetBitResults() { return( BitError ); }
};

//-----------------------------------------------------------------------------
// Ack (ACK)
//
class TAck {
public:

   AnsiString MsgId;
   bool       MsgValid;
   bool       SimModeValid;

public:

   TAck( const AnsiString InMsgId="", const InMsgValid = false, const InSimModeValid = false ) :
      MsgId( InMsgId ), MsgValid( InMsgValid ), SimModeValid( InSimModeValid ) {}
};

class TAckMsg : public TSimToExt {

private:

   TAck     Ack;

public:

   TAckMsg( const TInMsg &InMsg );
   TAckMsg & operator=( const TInMsg &InMsg );
   TAck const GetAck() { return( Ack ); }
};

//-----------------------------------------------------------------------------
// System Configuration (SYSCFG)
//
class TSysCfg {
public:
   int  NumChans;
   bool L2Capable;
   int  MinPower;
   int  MaxPower;

public:
   TSysCfg( ) : NumChans( 0 ), L2Capable( false ), MinPower( 0 ), MaxPower( 0 ) {}
};
      
class TSysCfgMsg : public TSimToExt {

private:

   TSysCfg     SysCfg;

public:

   TSysCfgMsg( const TInMsg &InMsg );
   TSysCfgMsg & operator=( const TInMsg &InMsg );
   TSysCfg const GetSysCfg() { return( SysCfg ); }
};







#endif
