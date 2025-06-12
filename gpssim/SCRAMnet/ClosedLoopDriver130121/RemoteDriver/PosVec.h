#ifndef PosVecH
#define PosVecH
//---------------------------------------------------------------------------
//
// $Workfile:: PosVec.h                                              $
//
// $Revision:: 2                                                     $
//
// $History:: PosVec.h                                               $
//
//*****************  Version 2  *****************
//User: Michael Wade Date: 7/23/02    Time: 7:51p
//Updated in $/TapMsec
//Added Source Safe keywords
//
//
//
//
//
//---------------------------------------------------------------------------

#ifndef DcmH
#include "Dcm.h"
#endif

#ifndef Vector3dH
#include "Vector3d.h"
#endif

#define TPOSVEC_EPSILON  ( 0.0001 )

//---------------------------------------------------------------------------
class TPosVec {
public:

   mutable TVector           Ecef;
   mutable double            FLon;
   mutable double            FAlt;
   mutable double            FLat;
   mutable bool              FLatDirty;
   mutable bool              FLonDirty;
   mutable bool              FAltDirty;
   mutable bool              FEcefxDirty;
   mutable bool              FEcefyDirty;
   mutable bool              FEcefzDirty;

   double __fastcall         GetLon() const;
   double __fastcall         GetLat() const;
   double __fastcall         GetAlt() const;
   double __fastcall         Getz() const;
   double __fastcall         Gety() const;
   double __fastcall         Getx() const;
   double __fastcall         GetEcef( int Index ) const;
   void   __fastcall         SetEcef( int Index, double value );
   void   __fastcall         Setx( double value );
   void   __fastcall         Sety( double value );
   void   __fastcall         Setz( double value );
   void   __fastcall         SetAlt( double value );
   void   __fastcall         SetLat( double value );
   void   __fastcall         SetLon( double value );
   double __fastcall         GetLatDeg() const;
   double __fastcall         GetLonDeg() const;

   TDcm                      GetCen( ) const;
   TDcm                      GetCne( ) const;

   bool __fastcall           GetEcefDirty() const { return( FEcefxDirty || FEcefyDirty || FEcefzDirty ); }
   bool __fastcall           GetGeoDirty()  const { return( FLatDirty   || FLonDirty   || FAltDirty   ); }
   void __fastcall           SetEcefDirty( const bool EcefIsDirty ) const { FEcefxDirty = EcefIsDirty; FEcefyDirty = EcefIsDirty; FEcefzDirty = EcefIsDirty; }
   void __fastcall           SetGeoDirty( const bool GeoIsDirty ) const   { FLatDirty   = GeoIsDirty;  FLonDirty   = GeoIsDirty;  FAltDirty   = GeoIsDirty;  }

protected:

   void                      CalcGeo()  const;
   void                      CalcEcef() const;

public:

   TPosVec();
    __property double  Lon =                { read = GetLon,       write = SetLon          };
    __property double  Lat =                { read = GetLat,       write = SetLat          };
    __property double  Alt =                { read = GetAlt,       write = SetAlt          };
    __property double  z =                  { read = Getz,         write = Setz            };
    __property double  y =                  { read = Gety,         write = Sety            };
    __property double  x =                  { read = Getx,         write = Setx            };
    __property double  PosEcef[int Index] = { read = GetEcef,      write = SetEcef         };
    __property TDcm    Cen                = { read = GetCen                                };
    __property TDcm    Cne                = { read = GetCne                                };
    __property TVector EcefVec            = { read = GetEcefVec,   write = SetEcefVec      };
    __property double  LonDeg             = { read = GetLonDeg,                            };
    __property double  LatDeg             = { read = GetLatDeg,                            };
    __property bool    GeoDirty           = { read = GetGeoDirty,  write = SetGeoDirty     };
    __property bool    EcefDirty          = { read = GetEcefDirty, write = SetEcefDirty    };

   friend bool const operator== ( const TPosVec &P1, const TPosVec &P2 )
   {
      for ( int i=0; i<3; ++i )
      {
         if ( fabs( P1.GetEcef( i ) - P2.GetEcef( i ) ) > TPOSVEC_EPSILON ) return( false );
      }
      return( true );
   }

   friend bool const operator!= ( const TPosVec & P1, const TPosVec &P2 )
   {
      return( !( P1 == P2 ) );
   }

   TPosVec & operator =( const double * const PosEcef );
   TPosVec( const double * const PosEcef );

   TPosVec( const TVector & PosVec );
   TPosVec & operator =( const TVector & PosVec );

   TPosVec( const TValArray & PosVec );
   TPosVec & operator =( const TValArray & PosVec );

   TPosVec( const TPosVec & Source );
   TPosVec & operator =( const TPosVec & Source );

    TVector const GetEcefVec() const
    {
       if ( EcefDirty )
       {
          CalcEcef();
       }
       return( Ecef );
    }

    void SetEcefVec( const TVector & Vector )
    {
       Ecef      = Vector;
       EcefDirty = false;
       GeoDirty  = true;
    }

    double const operator[]( const int Index ) const
    {
       if ( EcefDirty )
       {
          CalcEcef();
       }
       return( Ecef[Index] );
    }

    double & operator[]( const int Index )
    {
       if ( EcefDirty )
       {
          CalcEcef();
       }
       return( Ecef[Index] );
    }


};

//---------------------------------------------------------------------------
#endif
