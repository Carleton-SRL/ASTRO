//---------------------------------------------------------------------------

#ifndef Vector3dH
#define Vector3dH
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


#if(1)

#define TVECTOR_EPSILON  ( 0.0001 )

class TVector : public TValArray {
private:

   double const mag() const
   {
      return( sqrt( ( ( *this )* (*this) ).sum() ) );
   }

   TVector const GetUnitVec() const
   {

      TVector Res = ( *this );

      const double VecMag = mag();
      if ( VecMag > 0 )
      {
         Res /= VecMag;
      }
      return( Res );
   }


public:

   TVector() : TValArray( 0.0, 3 ) {}

   TVector( const TVector & Source ) : TValArray( 0.0, 3 )
   {

      ( *this ) = Source;

   }

   TVector & operator = ( const TVector & Source )
   {

      TValArray::operator = ( Source );

      return( *this );

   }

   TVector( const TValArray & ValArray ) : TValArray( 0.0, 3 )
   {
      TValArray::operator= ( ValArray );
   }

   TVector & operator = ( const TValArray & Source )
   {
      if ( this == & Source )
      {
         return( *this );
      }

      TValArray::operator= ( Source );

      return( *this );

   }

   TVector
      (
      const double * const DoubleArr
      ) :
      TValArray( DoubleArr, 3 )
   {
   }

   TVector & operator =
      (
      const double * const DoubleArr
      )
   {
      ( *this )[0] = DoubleArr[0];
      ( *this )[1] = DoubleArr[1];
      ( *this )[2] = DoubleArr[2];

      return( *this );
   }

   friend bool const operator== ( const TVector &P1, const TVector &P2 )
   {
      for ( int i=0; i<3; ++i )
      {
         if ( fabs( P1[i] - P2[i] ) > TVECTOR_EPSILON ) return( false );
      }
      return( true );
   }

   friend bool const operator!= ( const TVector & P1, const TVector &P2 )
   {
      return( !( P1 == P2 ) );
   }


   double const Dot( const TVector & v2 )
   {
      return( ( ( *this ) * v2 ).sum() );
   }

   // Dot product
   //
   friend double const Dot ( const TVector & v1, const TVector & v2 )
   {
      return(  ( v1 * v2 ).sum() );
   }

   __property  double  Mag         = { read = mag                     };
   __property  TVector Unit        = { read = GetUnitVec               };


};

#else

class TVector {
private:

   TValArray FValArray;

   double const mag() const
   {
      double Res           = 0;
      const double Squared =
         FValArray[0]*FValArray[0] +
         FValArray[1]*FValArray[1] +
         FValArray[2]*FValArray[2];

      if ( Squared > 0 )
      {
         Res               = sqrt( Squared );
      }

      return( Res );

   }

   TVector const GetUnitVec() const
   {

      TVector Res = ( *this );

      const double VecMag = mag();
      if ( VecMag > 0 )
      {
         Res /= VecMag;
      }
      return( Res );
   }

public:

   TVector() : FValArray( 0.0, 3 ) {}

   TVector
      (
      const TVector & Source
      ) :
      FValArray( 0.0, 3 )
   {
      FValArray = Source.ValArray;
   }

   TVector & operator= ( const TVector & Source )
   {

      if ( this == &Source ) return ( *this );

      FValArray = Source.FValArray;

      return( *this );

   }


   TVector & operator= ( const double * const DoubleArr )
   {

      FValArray[0] = DoubleArr[0];
      FValArray[1] = DoubleArr[1];
      FValArray[2] = DoubleArr[2];

      return( *this );

   }

   TVector
      (
      const double * const DoubleArr
      ) :
      FValArray( 0.0, 3 )
   {
      FValArray[0] = DoubleArr[0];
      FValArray[1] = DoubleArr[1];
      FValArray[2] = DoubleArr[2];
   }

   TVector
      (
      const TValArray & Source
      ) :
      FValArray( 0.0, 3 )
   {
      FValArray = Source;
   }

   TVector &
   operator =
      (
      const TValArray & Source
      )
   {

      FValArray = Source;

      return( *this );

   }

   TVector & operator += ( const TVector rhs )
   {
      FValArray[0] += rhs[0];
      FValArray[1] += rhs[1];
      FValArray[2] += rhs[2];

      return( *this );

   }

   TVector & operator -= ( const TVector rhs )
   {
      FValArray[0] -= rhs[0];
      FValArray[1] -= rhs[1];
      FValArray[2] -= rhs[2];

      return( *this );

   }

   TVector & operator /= ( const double Scale )
   {
      FValArray /= Scale;

      return( *this );
   }

   TVector & operator *= ( const double Scale )
   {
      FValArray *= Scale;

      return( *this );
   }

   friend TVector const operator-( const TVector & v1, const TVector & v2 )
   {
      return( TVector( v1 ) -= v2 );

   }

   friend TVector const operator+( const TVector & v1, const TVector & v2 )
   {
      return( TVector( v1 ) += v2 );

   }

   friend TVector const operator* ( const TVector & v1, const double Scale )
   {
      return( TVector( v1 ) *= Scale );

   }

   // Dot product
   //
   friend double const operator* ( const TVector & v1, const TVector & v2 )
   {
      return(  v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2] );
   }

   double const operator[]( const int Index ) const
   {
      return( FValArray[Index] );
   }

   double & operator[]( const int Index )
   {
      return( FValArray[Index] );
   }


   __property double  Mag         = { read = mag                      };
   __property TVector Unit        = { read = GetUnitVec               };
   __property TValArray ValArray  = { read = FValArray                };

};

#endif

#endif
