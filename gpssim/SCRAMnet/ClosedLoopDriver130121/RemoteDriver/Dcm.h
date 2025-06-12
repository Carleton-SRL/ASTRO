//---------------------------------------------------------------------------

#ifndef DcmH
#define DcmH
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

#ifndef Vector3dH
#include "Vector3d.h"
#endif


#if(1)
class TDcm : public TMatrix {
private:

public:

   TDcm( ) : TMatrix( 3, 3 ) {}

   TDcm( const TDcm & Source ) : TMatrix( 3, 3 )
   {

      ( *this ) = Source;

   }


   TDcm & operator=( const TDcm & Source )
   {

      if ( this == &Source ) return ( *this );

      TMatrix::operator = ( Source );

      return( *this );

   }

   TDcm( const TMatrix & Source ) : TMatrix( 3, 3 )
   {
      ( *this ) = Source;
   }

   TDcm & operator = ( const TMatrix & Source )
   {
      TMatrix::operator = ( Source );

      return( *this );

   }



#if(0)
   const double & operator() ( const int Row, const int Col ) const
   {
      return( FMatrix( Row, Col ) );
   }

   double & operator() ( const int Row, const int Col )
   {
      return( FMatrix( Row, Col ) );
   }
#endif

   static TDcm const
   Rotx ( const double     Anglex );

   static TDcm const
   Roty ( const double     Angley );

   static TDcm const
   Rotz ( const double     Anglez );

};
#else
typedef TMatrix TDcm( 3, 3 );

TDcm const Rotx( const double AngleX );
TDcm const Roty( const double AngleY );
TDcm const Rotz( const double AngleZ );

#endif

#endif
