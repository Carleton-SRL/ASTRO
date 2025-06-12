//---------------------------------------------------------------------------

#ifndef GpibTimeoutH
#define GpibTimeoutH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// $Workfile:: GpibTimeout.h                                         $
//
// $Revision:: 1                                                     $
//
// $History:: GpibTimeout.h                                          $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 10/08/02   Time: 9:04p
//Created in $/TapRci
//
//
//---------------------------------------------------------------------------

class TGpibTimeout {
private:

   int                       DefaultTimeout;

public:
   TGpibTimeout( int InDefaultTimeout );

   int const                 GetTimeout( const AnsiString & TimeoutStr );
   AnsiString const          GetTimeoutStr( const int Timeout );

};   



#endif
 