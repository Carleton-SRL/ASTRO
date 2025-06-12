#ifndef RtTypesH
#define RtTypesH
//---------------------------------------------------------------------------
//
// $Workfile:: RTTypes.h                                             $
//
// $Revision:: 7                                                     $
//
// $History:: RTTypes.h                                              $
//
//*****************  Version 7  *****************
//User: Michael Wade Date: 7/28/02    Time: 8:45p
//Updated in $/TapMsec
//Removed TpUtils.h file
//
//*****************  Version 6  *****************
//User: Michael Wade Date: 7/28/02    Time: 1:02p
//Updated in $/TapMsec
//Used std:: instead of global using namespace std
//Added include guards
//
//*****************  Version 5  *****************
//User: Michael Wade Date: 7/23/02    Time: 7:58p
//Updated in $/TapMsec
//Added Source Safe keywords
//
//
//
//
//---------------------------------------------------------------------------

#ifndef GpsTimeH
#include "GpsTime.h"
#endif

#ifndef TSub45H
#include "tsub45.h"
#endif

#ifndef TpMapH
#include "TpMap.h"
#endif

#ifndef SvUtilsH
#include "SvUtils.h"
#endif

typedef TUCharArr            TMsgData;

typedef std::queue<TMsgData> TMsgDataQueue;

typedef TUCharArr            TMsgBody;

typedef TDoubleArr           TSvBiasArray;

typedef TIntArr TAttenArray;

class TAssignedSv {
private:
   int  Chan;
   bool Override;
   int  Svid;
public:
   TAssignedSv( const int InChan=-1, const bool InOverride = false, const int InSvid=0 )
   : Chan( InChan ), Override( InOverride ), Svid( InSvid ) {}
   int  const GetChan() const { return( Chan ); }
   int  const GetSvid() const { return( Svid ); }
   bool const GetOverride() const { return( Override ); }
};

typedef std::vector<TAssignedSv> TAssignedSvArray;

// CodeControl
//   From STel interface
//   0  0  0  0  0  c  c  c
//                  |  |  |
//                  |  |  - Data on/off
//                  |  ---- Code on/off
//                  ------- Carrier on/off

class TStelCodeControl {
private:

   unsigned char Control;
public:

   TStelCodeControl( unsigned char InControl=0 ) : Control( InControl ) {}
   ~TStelCodeControl() {}
   void SetControl(const unsigned char StelControl) { Control = StelControl; }
   bool const IsDataOn()    const { return(Control & 0x01); }
   bool const IsCodeOn()    const { return(Control & 0x02); }
   bool const IsCarrierOn() const { return(Control & 0x04); }
};

class TCodeControl {
private:

   CODECTRL CodeCtrl;
public:

   TCodeControl()
   {
      CodeCtrl.CACodeEnabled  = 0;
      CodeCtrl.PCodeEnabled   = 0;
      CodeCtrl.NavBitsEnabled = 0;
      CodeCtrl.CarEnabled     = 0;
      CodeCtrl.WaasEnabled    = 0;
   }
   TCodeControl( const CODECTRL &InCodeCtrl ) : CodeCtrl( InCodeCtrl ) {}

   TCodeControl( const TStelCodeControl StelCACodeControl, const TStelCodeControl StelPCodeControl)
   {
      CodeCtrl.CACodeEnabled   = StelCACodeControl.IsCodeOn();
      CodeCtrl.PCodeEnabled    = StelPCodeControl.IsCodeOn();
      CodeCtrl.NavBitsEnabled  = StelCACodeControl.IsDataOn() | StelPCodeControl.IsDataOn();
      CodeCtrl.CarEnabled      = StelCACodeControl.IsCarrierOn() | StelPCodeControl.IsCarrierOn();
   }

   TCodeControl & operator = ( const CODECTRL &InCodeCtrl )
   {
      CodeCtrl = InCodeCtrl;
      return( *this );
   }
   ~TCodeControl() {}
   void SetFromStelControl
      (
      const TStelCodeControl StelCACodeControl,
      const TStelCodeControl StelPCodeControl
      )
   {
      CodeCtrl.CACodeEnabled   = StelCACodeControl.IsCodeOn();
      CodeCtrl.PCodeEnabled    = StelPCodeControl.IsCodeOn();
      CodeCtrl.NavBitsEnabled  = StelCACodeControl.IsDataOn() | StelPCodeControl.IsDataOn();
      CodeCtrl.CarEnabled      = StelCACodeControl.IsCarrierOn() | StelPCodeControl.IsCarrierOn();
   }
   void SetCarrier( const bool On )  { CodeCtrl.CarEnabled      = On; }
   void SetCACode( const bool On )   { CodeCtrl.CACodeEnabled   = On; }
   void SetPCode( const bool On )    { CodeCtrl.PCodeEnabled    = On; }
   void SetNavBits( const bool On )  { CodeCtrl.NavBitsEnabled  = On; }
   void SetWaas( const bool On )     { CodeCtrl.WaasEnabled     = On; }

   bool const IsCarrier() const { return( CodeCtrl.CarEnabled ); }
   bool const IsCACode()  const { return( CodeCtrl.CACodeEnabled ); }
   bool const IsPCode()   const { return( CodeCtrl.PCodeEnabled ); }
   bool const IsNavBits() const { return( CodeCtrl.NavBitsEnabled ); }
   bool const IsWaas()    const { return( CodeCtrl.WaasEnabled ); }
   CODECTRL const GetCodeControl() const { return( CodeCtrl ); };
   void SetCodeControl( const CODECTRL &InCodeCtrl ) { CodeCtrl = InCodeCtrl; }

   friend bool const operator == ( const TCodeControl &lhs, const TCodeControl &rhs )
   {
      return( !( lhs != rhs ) );
   }
   friend bool const operator != ( const TCodeControl &lhs, const TCodeControl &rhs )
   {
      bool Same = true;
      if ( lhs.CodeCtrl.CarEnabled != rhs.CodeCtrl.CarEnabled ) Same = false;
      if ( lhs.CodeCtrl.CACodeEnabled != rhs.CodeCtrl.CACodeEnabled ) Same = false;
      if ( lhs.CodeCtrl.PCodeEnabled != rhs.CodeCtrl.PCodeEnabled ) Same = false;
      if ( lhs.CodeCtrl.NavBitsEnabled != rhs.CodeCtrl.NavBitsEnabled ) Same = false;
      if ( lhs.CodeCtrl.WaasEnabled != rhs.CodeCtrl.WaasEnabled ) Same = false;

      return( !Same );

   }
};


//-----------------------------------------------------------------------------
// Control classes for real time control
//-----------------------------------------------------------------------------

static const int TRAJ_MODE = 0;
class TInitRec {
public:   // Data
   GPSTime  StartTime;
   int      SimMode;
   bool     ResetTime;
   double   PosEcef[3];
public:   // Methods
   TInitRec() : StartTime(0,0.0), SimMode(0)
      {PosEcef[0]=PosEcef[1]=PosEcef[2]=0.0;}
   TInitRec(const TInitRec &Source) { *this = Source; };

   ~TInitRec(){}
   TInitRec &operator=(const TInitRec &Source)
   {
      if ( this == &Source ) return(*this);
      StartTime  = Source.StartTime;
      SimMode    = Source.SimMode;
      ResetTime  = Source.ResetTime;
      PosEcef[0] = Source.PosEcef[0];
      PosEcef[1] = Source.PosEcef[1];
      PosEcef[2] = Source.PosEcef[2];
      return(*this);
   }
};

class TAlmData {
public:
   int      Svid;
   int      Week;
   double   Ecc;
   int      Toa;
   double   DeltaI;
   double   OmegaDot;
   double   RootA;
   double   Omega0;
   double   w;
   double   M0;
   double   Af0;
   double   Af1;
   int      Health;
public:
   TAlmData() : Svid(0), Week(0), Ecc(0.0), Toa(0), DeltaI(0.0), OmegaDot(0.0),
      RootA(0.0), Omega0(0.0), w(0.0), M0(0.0),Af0(0.0), Af1(0.0), Health(0) {}
   TAlmData( const int Svid, const SUB_45 &Sub45Data );
};

class TPowerOverride {

private:

   int ChannelId;
   int PowerL1;
   int PowerL2;

public:

   TPowerOverride( const int InChannelId=-1, const int InPowerL1=-80, const int InPowerL2=-80 ) :
      ChannelId( InChannelId ), PowerL1( InPowerL1 ), PowerL2( InPowerL2 ) {}
   int const GetChannelId() const { return( ChannelId ); }
   int const GetPowerL1() const { return( PowerL1 ); }
   int const GetPowerL2() const { return( PowerL2 ); }

};
typedef std::vector<TPowerOverride> TPowerOverrideArray;


class TPowerOverrideAll {

private:
   bool                  PowerOverride;
   int                   PowerL1;
   int                   PowerL2;

public:

   TPowerOverrideAll( const bool InPowerOverride=false, const int InPowerL1=0, const int InPowerL2=0 ) :
      PowerOverride( InPowerOverride ), PowerL1( InPowerL1 ), PowerL2( InPowerL2 ) {}

   bool const IsPowerOverride() const { return( PowerOverride ); }
   int  const GetL1Power() const { return( PowerL1 ); }
   int  const GetL2Power() const { return( PowerL2 ); }
   void ResetPowerOverride() { PowerOverride = false; }

};

class TAttenOverride {

private:

   int ChannelId;
   int AttenL1;
   int AttenL2;

public:

   TAttenOverride( const int InChannelId=-1, const int InAttenL1=-80, const int InAttenL2=-80 ) :
      ChannelId( InChannelId ), AttenL1( InAttenL1 ), AttenL2( InAttenL2 ) {}
   int const GetChannelId() const { return( ChannelId ); }
   int const GetAttenL1() const { return( AttenL1 ); }
   int const GetAttenL2() const { return( AttenL2 ); }

};
typedef std::vector<TAttenOverride> TAttenOverrideArray;


class TAttenOverrideAll {

private:
   bool                  AttenOverride;
   int                   AttenL1;
   int                   AttenL2;

public:

   TAttenOverrideAll( const bool InAttenOverride=false, const int InAttenL1=0, const int InAttenL2=0 ) :
      AttenOverride( InAttenOverride ), AttenL1( InAttenL1 ), AttenL2( InAttenL2 ) {}

   bool const IsAttenOverride() const { return( AttenOverride ); }
   int  const GetL1Atten() const { return( AttenL1 ); }
   int  const GetL2Atten() const { return( AttenL2 ); }
   void ResetAttenOverride() { AttenOverride = false; }

};

// Clock Control
//   From STel interface
//   0  0  0  0  0  0  c  c
//                     |  |
//                     |  - 0 = Normal, 1 = Clock/2, 2=Clock/4
//                     ---- "

class TStelClockControl {
private:

   unsigned char Control;

public:

   TStelClockControl(unsigned char InControl=0) : Control( InControl ) {}
   void SetControl( const unsigned char InControl ) { Control = InControl; }
   bool const IsNormal() const { return( Control == 0 ); }
   bool const IsClockHalf() const { return( Control == 1 ); }
   bool const IsClockQuarter() const { return( Control == 2 ); }
};

// PRN Index Control
//   From STel interface
//   0  0  0  0  0  0  0  c
//                        |
//                        - Index Control on/off
//                          ( 0 = off, 1 = on )

class TStelPRNIndexControl {
private:

   unsigned char Control;

public:

   TStelPRNIndexControl(unsigned char InControl=0) : Control( InControl ) {}
   void SetControl( const unsigned char InControl ) { Control = InControl; }
   bool const IsIndexOn() const { return( Control & 0x01 ); }
};

class TSetMomASFlag {

private:

   bool AntiSpoof;
   bool MomAlert;
   bool New;

public:

   TSetMomASFlag( const bool InNew=false, const bool InAntiSpoof=false, const bool InMomAlert=false ) :
      New( InNew ), AntiSpoof( InAntiSpoof ), MomAlert( InMomAlert ) {}
   bool const IsNew() const { return( New ); }
   bool const IsAntiSpoof() const { return( AntiSpoof ); }
   bool const IsMomAlert() const { return( MomAlert ); }
};

typedef std::vector<TSetMomASFlag> TSetMomASFlagArray;

class TSvLookAngle {

private:

   int    Chan;
   int    Svid;
   double El;
   double Az;
   bool   NewEph;

public:

   TSvLookAngle( const int InChan, const int InSvid, const double InEl, const double InAz, const bool InNewEph=false ) :
      Chan( InChan ), Svid( InSvid ), El( InEl ), Az( InAz ), NewEph( InNewEph ) {}
   int const GetChan() const { return( Chan ); }
   int const GetSvid() const { return( Svid ); }
   int const GetEl() const { return( El ); }
   int const GetAz() const { return( Az ); }
   int const GetNewEph() const { return( NewEph ); }

   friend bool const operator==( const TSvLookAngle &lhs, const TSvLookAngle &rhs )
   {
      bool Same = true;
      if ( lhs.Chan       != rhs.Chan       ) Same = false;
      if ( lhs.Svid       != rhs.Svid       ) Same = false;
      if ( NINT( lhs.El ) != NINT( rhs.El ) ) Same = false;
      if ( NINT( lhs.Az ) != NINT( rhs.Az ) ) Same = false;
      if ( lhs.NewEph     != rhs.NewEph     ) Same = false;

      return( Same );

   }

};

typedef std::vector<TSvLookAngle> TSvLookAngleArray;

class TChanRangeStatus {

private:

   int    Svid;
   double L1Range;
   double L2Range;

public:

   TChanRangeStatus( const int InSvid = 0, const double InL1Range=0, const double InL2Range=0 )
      : Svid( InSvid ), L1Range( InL1Range ), L2Range( InL2Range ) {}

   double const GetL1Range() const { return( L1Range ); }
   double const GetL2Range() const { return( L2Range ); }
   int    const GetSvid()    const { return( Svid ); }

};

typedef std::vector<TChanRangeStatus> TChanRangeStatusArray;

class TChanRangeTimeStatus {

private:

   GPSTime GpsTime;
   TChanRangeStatusArray ChanRangeStatusArray;

public:
   TChanRangeTimeStatus( ) {};
   TChanRangeTimeStatus( const GPSTime &InGpsTime, const TChanRangeStatusArray &InChanRangeStatusArray ) :
      GpsTime( InGpsTime ), ChanRangeStatusArray( InChanRangeStatusArray ) {}
   GPSTime const GetGpsTime() const { return( GpsTime ); }
   TChanRangeStatusArray const GetChanRangeStatusArray() const { return( ChanRangeStatusArray ); }

};


#endif
