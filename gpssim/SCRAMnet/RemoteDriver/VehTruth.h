#ifndef VehTruthH
#define VehTruthH
//---------------------------------------------------------------------------
//
// $Workfile:: VehTruth.h                                            $
//
// $Revision:: 3                                                     $
//
// $History:: VehTruth.h                                             $
//
//*****************  Version 3  *****************
//User: Michael Wade Date: 7/23/02    Time: 8:09p
//Updated in $/TapMsec
//Added Source Safe keywords
//
//
//
//---------------------------------------------------------------------------

#ifndef GpsTimeH
#include "GpsTime.h"
#endif

#ifndef PosVecH
#include "PosVec.h"
#endif

#ifndef AttVecH
#include "AttVec.h"
#endif

#ifndef VehStateRecH
#include "VehStateRec.h"
#endif

#pragma pack(push,1)

class TVehTruthRec {
private:

   TGpsTime                  GpsTime_;
   TPosVec                   Pos_;
   TVector                   VelEcef_;
   TVector                   AccEcef_;
   TVector                   JerkEcef_;
   TAttVec                   Attitude_;
   TVector                   AngRate_;

   double const GetPosEcef( const int Index ) const { return( Pos_[Index] ); }
   double const GetVelEcef( const int Index ) const { return( VelEcef_[Index] ); }
   double const GetAccEcef( const int Index ) const { return( AccEcef_[Index] ); }
   double const GetJerkEcef( const int Index ) const { return( JerkEcef_[Index] ); }
   double const GetAttitude( const int Index ) const { return( Attitude_[Index] ); }
   double const GetAngRate( const int Index ) const { return( AngRate_[Index] ); }

   void SetPosEcef( const int Index, const double Value ) { Pos_.PosEcef[Index] = Value; }
   void SetVelEcef( const int Index, const double Value ) { VelEcef_[Index] = Value; }
   void SetAccEcef( const int Index, const double Value ) { AccEcef_[Index] = Value; }
   void SetJerkEcef( const int Index, const double Value ) { JerkEcef_[Index] = Value; }
   void SetAttitude( const int Index, const double Value ) { Attitude_[Index] = Value; }
   void SetAngRate( const int Index, const double Value ) { AngRate_[Index] = Value; }

   TGpsTime const GetGpsTime()  const { return( GpsTime_ ); }
   TPosVec  const GetPosVec()      { return( Pos_ ); }
   TVector  const GetVelEcefVec()  const { return( VelEcef_ ); }
   TVector  const GetAccEcefVec()  const { return( AccEcef_ ); }
   TVector  const GetJerkEcefVec() const { return( JerkEcef_ ); }
   TAttVec  const GetAttitudeVec() const { return( Attitude_ ); }
   TVector  const GetAngRateVec()  const { return( AngRate_ ); }

   void           SetGpsTime( const TGpsTime & InGpsTime )  { GpsTime_  = InGpsTime; }
   void           SetPosVec( const TPosVec & InPosVec )        { Pos_      = InPosVec; }
   void           SetVelEcefVec( const TVector & InVelEcef )   { VelEcef_  = InVelEcef; }
   void           SetAccEcefVec( const TVector & InAccEcef )   { AccEcef_  = InAccEcef; }
   void           SetJerkEcefVec( const TVector & InJerkEcef ) { JerkEcef_ = InJerkEcef; }
   void           SetAttitudeVec( const TAttVec & InAttitude ) { Attitude_ = InAttitude; }
   void           SetAngRateVec( const TVector & InAngRate )   { AngRate_  = InAngRate; }

   double const GetLat() const { return( Pos_.Lat ); }
   double const GetLon() const { return( Pos_.Lon ); }
   double const GetAlt() const { return( Pos_.Alt ); }
   TDcm   const GetCnb() const { return( Attitude_.Cnb ); }
   TDcm   const GetCbe() const
   {
      return( ~( Pos_.Cen*Attitude_.Cnb ) );
   }

   TVector const GetVelNedVec() const
   {
      return( Pos_.Cen * VelEcef_ );
   }

   double const GetVelNed( const int Index ) const
   {
      return( GetVelNedVec()[Index] );
   }

public:

   TVehTruthRec()
   { }

   ~TVehTruthRec() { }

   TVehTruthRec( const TVehTruthRec & Source )
   {
      ( *this ) = Source;
   }

   TVehTruthRec & operator=( const TVehTruthRec &Source )
   {

      if ( this == &Source ) return(*this);

      GpsTime_  = Source.GpsTime;

      Pos_      = Source.Pos_;
      VelEcef_  = Source.VelEcef_;
      AccEcef_  = Source.AccEcef_;
      JerkEcef_ = Source.JerkEcef_;
      Attitude_ = Source.Attitude_;
      AngRate_  = Source.AngRate_;

      return( *this );

   }

   TVehTruthRec( const TVehStateRec & Source )
   {
      ( *this ) = Source;
   }

   TVehTruthRec & operator = ( const TVehStateRec & Source )
   {
      GpsTime_.Week        = Source.week;
      GpsTime_.Seconds     = Source.time;
      Pos_                 = Source.EcefPos;
      VelEcef_             = Source.EcefVel;
      AccEcef_             = Source.EcefAcc;
      JerkEcef_            = Source.EcefJerk;
      Attitude_            = Source.attitude;
      AngRate_             = Source.AngRate;

      return( *this );

   }

   friend bofstream & operator<< ( bofstream & OutStream, TVehTruthRec &Truth )
   {

      TVehStateRec Rec( Truth );
      OutStream << Rec;

      return( OutStream );

   }

   friend bifstream & operator>> ( bifstream & InStream, TVehTruthRec &Truth)
   {

      TVehStateRec VehStateRec;
      InStream.Read( &VehStateRec, sizeof( VehStateRec ) );

      Truth = VehStateRec;

      return( InStream );

   }

   friend bool const operator== ( const TVehTruthRec &T1, const TVehTruthRec &T2 )
   {
      if ( T1.GpsTime_  != T2.GpsTime_  ) return( false );
      if ( T1.Pos_      != T2.Pos_      ) return( false );
      if ( T1.VelEcef_  != T2.VelEcef_  ) return( false );
      if ( T1.AccEcef_  != T2.AccEcef_  ) return( false );
      if ( T1.JerkEcef_ != T2.JerkEcef_ ) return( false );
      if ( T1.Attitude_ != T2.Attitude_ ) return( false );
      if ( T1.AngRate_  != T2.AngRate_  ) return( false );
      return( true );
   }


   friend bool const operator!= ( const TVehTruthRec &T1, const TVehTruthRec &T2 )
   {
      return( !( T1 == T2 ) );
   }


   friend bool const operator<  ( const TVehTruthRec &T1, const TVehTruthRec &T2 );

   __property TGpsTime GpsTime             = { read = GpsTime_      , write = GpsTime_       };
   __property TPosVec  Pos                 = { read = Pos_          , write = SetPosVec      };
   __property TVector  VelEcefVec          = { read = VelEcef_      , write = SetVelEcefVec  };
   __property TVector  AccEcefVec          = { read = AccEcef_      , write = SetAccEcefVec  };
   __property TVector  JerkEcefVec         = { read = JerkEcef_     , write = SetJerkEcefVec };
   __property TAttVec  AttVec              = { read = Attitude_     , write = SetAttitudeVec };
   __property TVector  AngRateVec          = { read = AngRate_      , write = SetAngRateVec  };
   __property double   PosEcef[int Index]  = { read = GetPosEcef    , write = SetPosEcef  };
   __property double   VelEcef[int Index]  = { read = GetVelEcef    , write = SetVelEcef  };
   __property double   AccEcef[int Index]  = { read = GetAccEcef    , write = SetAccEcef  };
   __property double   JerkEcef[int Index] = { read = GetJerkEcef   , write = SetJerkEcef  };
   __property double   Attitude[int Index] = { read = GetAttitude   , write = SetAttitude  };
   __property double   AngRate[int Index]  = { read = GetAngRate    , write = SetAngRate  };
   __property double   Lat                 = { read = GetLat                              };
   __property double   Lon                 = { read = GetLon                              };
   __property double   Alt                 = { read = GetAlt                              };
   __property TDcm     Cnb                 = { read = GetCnb                              };
   __property TDcm     Cbe                 = { read = GetCbe                              };
   __property TVector  VelNedVec           = { read = GetVelNedVec                        };
   __property double   VelNed[int Index]   = { read = GetVelNed                           };

};

typedef TVehTruthRec VehTruthRec;

class TVehicleTruth {
protected:
   bool         Valid;
public:
   TVehicleTruth() : Valid( false ) { }
   virtual ~TVehicleTruth() { }

   virtual bool const         GetTruth( const TGpsTime &ReqTime, TVehTruthRec *Truth )   = 0;
   virtual TVehTruthRec const GetTruth( const TGpsTime & ReqTime )                       = 0;
//   virtual TVehTruthRec const GetTruth()                                                 = 0;
   virtual TVehTruthRec const GetFirst()                                                 = 0;
   virtual TVehTruthRec const GetLast()                                                  = 0;
   virtual void               Reset() { }

   bool good(){ return(Valid); };
};

typedef TVehicleTruth VehicleTruth;

#pragma pack(pop)

#endif





