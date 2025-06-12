//---------------------------------------------------------------------------

#ifndef AttVecH
#define AttVecH
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//
// $Workfile:: AttVec.h                                              $
//
// $Revision:: 1                                                     $
//
// $History:: AttVec.h                                               $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 9/07/02    Time: 12:52p
//Created in $/RemoteDriver
//
//
//---------------------------------------------------------------------------

#ifndef DcmH
#include "Dcm.h"
#endif

#ifndef Vector3dH
#include "Vector3d.h"
#endif

#define TATTVEC_EPSILON  ( 0.00001 )

class TAttVec {
private:

   TVector                   FAttitude;
   mutable TDcm              FCnb;
   mutable bool              CnbDirty;

   double const              GetRoll()    const { return( FAttitude[0] ); }
   double const              GetPitch()   const { return( FAttitude[1] ); }
   double const              GetHeading() const { return( FAttitude[2] ); }
   void                      SetRoll( const double InRoll )       { FAttitude[0] = InRoll; CnbDirty = true; }
   void                      SetPitch( const double InPitch )     { FAttitude[1] = InPitch; CnbDirty = true; }
   void                      SetHeading( const double InHeading ) { FAttitude[2] = InHeading; CnbDirty = true; }

   TVector GetVector() const { return( FAttitude ); }
   void    SetVector( const TVector & NewAttitude ) { FAttitude = NewAttitude; CnbDirty  = true; }


   TDcm const                GetCnb() const
   {
      if ( CnbDirty )
      {
         CalcCnb();
      }
      return( FCnb );
   }

   void CalcCnb() const
   {
      FCnb     = EulerToCnb( FAttitude[0], FAttitude[1], FAttitude[2] );
      CnbDirty = false;
   }

public:

   TAttVec( ) : CnbDirty( true ) { }

   TAttVec & operator =( const double * const pAttitude );
   TAttVec( const double * const pAttitude );

   TAttVec( const TVector & AttVec );
   TAttVec & operator =( const TVector & AttVec );

   TAttVec( const TAttVec & Source );
   TAttVec & operator =( const TAttVec & Source );

   TAttVec( const TDcm & Cnb );
   TAttVec & operator =( const TDcm & Cnb );

   TAttVec( const TValArray & Source );
   TAttVec & operator = ( const TValArray & Source );

   double const operator[]( const int Index ) const
   {
      return( FAttitude[Index] );
   }

   double & operator[]( const int Index )
   {
      CnbDirty = true;
      return( FAttitude[Index] );
   }

   TAttVec & operator += ( const TAttVec & v2 )
   {
      FAttitude += v2.FAttitude;
      CnbDirty   = true;
      return( *this );
   }

   friend TAttVec operator + ( const TAttVec & v1, const TAttVec & v2 )
   {
      return( TAttVec( v1 ) += v2 );
   }

   friend bool const operator== ( const TAttVec &P1, const TAttVec &P2 )
   {
      for ( int i=0; i<3; ++i )
      {
         if ( fabs( P1[i] - P2[i] ) > TATTVEC_EPSILON ) return( false );
      }
      return( true );
   }

   friend bool const operator!= ( const TAttVec & P1, const TAttVec &P2 )
   {
      return( !( P1 == P2 ) );
   }

   // Static members
   //
   static void
   CnbToEuler
      (
      const TDcm   & Cnb,
      double       & Roll,
      double       & Pitch,
      double       & Heading
      );

   static TDcm const
   EulerToCnb
      (
      const double   Roll,
      const double   Pitch,
      const double   Heading
      );

   __property double    Roll          = { read = GetRoll,       write = SetRoll      };
   __property double    Pitch         = { read = GetPitch,      write = SetPitch     };
   __property double    Heading       = { read = GetHeading,    write = SetHeading   };
   __property TDcm      Cnb           = { read = GetCnb                              };
   __property TVector   Vector        = { read = GetVector,     write = SetVector    };

};

#endif
