#include "pch.h"
#pragma hdrstop

//---------------------------------------------------------------------------
//
// $Workfile:: GpibTimeout.cpp                                       $
//
// $Revision:: 1                                                     $
//
// $History:: GpibTimeout.cpp                                        $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 10/08/02   Time: 9:04p
//Created in $/TapRci
//
//
//---------------------------------------------------------------------------


#ifndef GpibTimeoutH
#include "GpibTimeout.h"
#endif

#include "Decl-32.h"

//---------------------------------------------------------------------------
// These timeouts are described in Decl-32.h, a header file distributed by
// National Instruments.  If that file changes, then these values should
// be modified.
//
#define NUM_GPIB_TIMEOUTS   ( 18 )
static const AnsiString GpibTimeoutStr[NUM_GPIB_TIMEOUTS] =
{
   "TNONE",
   "T10us",
   "T30us",
   "T100us",
   "T300us",
   "T1ms",
   "T3ms",
   "T10ms",
   "T30ms",
   "T100ms",
   "T300ms",
   "T1s",
   "T3s",
   "T10s",
   "T30s",
   "T100s",
   "T300s",
   "T1000s"
};

#pragma package(smart_init)
TGpibTimeout::TGpibTimeout
   (
   const int                 InDefaultTimeout
   ) :
   DefaultTimeout( InDefaultTimeout )
{
   if ( DefaultTimeout < 0 || DefaultTimeout >= NUM_GPIB_TIMEOUTS )
   {
      DefaultTimeout = T100ms;
   }
}

int const
TGpibTimeout::GetTimeout
   (
   const AnsiString        & TimeoutStr
   )
{
   AnsiString Str = TimeoutStr.Trim();
   Str            = Str.UpperCase();

   for ( int i=0; i<NUM_GPIB_TIMEOUTS; ++i )
   {
      if ( Str.AnsiCompareIC( GpibTimeoutStr[i].UpperCase() ) == 0 )
      {
         return( i );
      }
   }

   return( DefaultTimeout );

}

AnsiString const
TGpibTimeout::GetTimeoutStr
   (
   const int Timeout
   )
{
   if ( Timeout >= 0 && Timeout < NUM_GPIB_TIMEOUTS )
   {
      return( GpibTimeoutStr[Timeout] );
   }
   return( GpibTimeoutStr[DefaultTimeout] );
}



