#include "pch.h"
#pragma hdrstop

#ifndef DebugUtilsH
#include "DebugUtils.h"
#endif

//---------------------------------------------------------------------------
// This is a debug unit containing debug global data, class methods, etc.

#pragma package(smart_init)

namespace DebugUtils {

TTimeInterval::TTimeInterval
   (
   )
{

   Init();

}

void
TTimeInterval::Init
   (
   )
{

   LARGE_INTEGER       lFrequency;
   QueryPerformanceFrequency( &lFrequency );
   Frequency_        = lFrequency.QuadPart;

   QueryPerformanceCounter( &StartCount_ );

}

void
TTimeInterval::ResetStart
   (
   )
{

   QueryPerformanceCounter( &StartCount_ );

}

double const
TTimeInterval::GetTimeInterval
   (
   ) const
{

   LARGE_INTEGER       CurCount;
   QueryPerformanceCounter( &CurCount );

   const double DeltaTime    = ( CurCount.QuadPart - StartCount_.QuadPart )/Frequency;

   return( DeltaTime );

}

double const
TTimeInterval::GetTimeIntervalms
   (
   ) const
{

   return( GetTimeInterval()*1000.0 );

}

};
