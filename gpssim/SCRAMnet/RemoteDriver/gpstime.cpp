#include "pch.h"
#pragma hdrstop

#ifndef GpsTimeH
#include "GpsTime.h"
#endif

#ifndef DateUtilsHPP
#include <DateUtils.hpp>
#endif

//---------------------------------------------------------------------------
//
// $Workfile:: gpstime.cpp                                           $
//
// $Revision:: 2                                                     $
//
// $History:: gpstime.cpp                                            $
//
//*****************  Version 2  *****************
//User: Michael Wade Date: 7/23/02    Time: 7:40p
//Updated in $/TapMsec
//Added Source Safe keywords
//
//
//
//
//
//
//---------------------------------------------------------------------------


static const TDateTime GpsStartDateTime( 1980, 1, 6 );
static const double    SecondsPerDay( 60*60*24 );

bifstream &
operator>>
   (
   bifstream & InStream,
   TGpsTime  & Time
   )
{

   InStream >> Time.Week_;
   InStream >> Time.Seconds_;
   //   DEBUG:  Handle Truthstream not doing week rollover.
   //
   while ( Time.Seconds >= SECONDS_PER_WEEK )
   {
      Time.Seconds -= SECONDS_PER_WEEK;
      Time.Week++;
   }

   return( InStream );

}

bofstream &
operator<<
   (
   bofstream      & OutStream,
   TGpsTime       & Time
   )
{

   OutStream << Time.Week;
   OutStream << Time.Seconds;

   return( OutStream );
}

std::ostream&
operator<<
   (
   std::ostream        & OutStream,
   const TGpsTime      & Time
   )
{

   OutStream << Time.Week << " " << Time.Seconds << " ";

   return( OutStream );
}

bool const operator<
   (
   const TGpsTime & Time1,
   const TGpsTime & Time2
   )
{
   if ( Time1.Week < Time2.Week )
   {
      return( true );
   }
   else if ( Time1.Week > Time2.Week )
   {
      return( false );
   }

   //   Weeks are the same.
   //
   return( Time1.Seconds < Time2.Seconds );

}

bool const operator<=
   (
   const TGpsTime & Time1,
   const TGpsTime & Time2
   )
{
   if ( Time1.Week < Time2.Week )
   {
      return( true );
   }
   else if ( Time1.Week > Time2.Week )
   {
      return( false );
   }

   //   Weeks are the same.
   //
   return( Time1.Seconds <= Time2.Seconds );

}

bool const operator>
   (
   const TGpsTime & Time1,
   const TGpsTime & Time2
   )
{
   if ( Time1.Week > Time2.Week )
   {
      return( true );
   }
   else if ( Time1.Week < Time2.Week )
   {
      return( false );
   }

   //   Weeks are the same.
   //
   return ( Time1.Seconds > Time2.Seconds );

}

bool const
operator>=
   (
   const TGpsTime & Time1,
   const TGpsTime & Time2
   )
{

   if ( Time1.Week > Time2.Week )
   {
      return( true );
   }
   else if ( Time1.Week < Time2.Week )
   {
      return( false );
   }

   //   Weeks are the same.
   //
   return ( Time1.Seconds >= Time2.Seconds );

}

bool const operator==
   (
   const TGpsTime &Time1,
   const TGpsTime &Time2
   )
{

   return( ( Time1.Week == Time2.Week ) && ( Time1.Seconds == Time2.Seconds ) );

}
bool const operator!=
   (
   const TGpsTime &Time1,
   const TGpsTime &Time2
   )
{

   return( (Time1.Week != Time2.Week) || (Time1.Seconds != Time2.Seconds) );

}

TGpsTime &
TGpsTime::operator=
   (
   const TGpsTime &Source
   )
{
   if ( this == &Source )
   {
      return( *this);
   }

   Week_     = Source.Week;
   Seconds_  = Source.Seconds;

   return( *this );

}

TGpsTime const
operator+
   (
   const TGpsTime & Source,
   const double     InSeconds
   )
{

   return( TGpsTime( Source ) += InSeconds );

}

TGpsTime &
TGpsTime::operator+=
   (
   const double InSeconds
   )
{

   Seconds_ += InSeconds;

   while ( Seconds_ > SECONDS_PER_WEEK )
   {
      Seconds_ -= SECONDS_PER_WEEK;
      ++Week_;
   }
   while ( Seconds_ < 0 )
   {
      Seconds_ += SECONDS_PER_WEEK;
      --Week_;
   }

   return( *this );

}

const TGpsTime
operator-
   (
   const TGpsTime & Source,
   const double     InSeconds
   )
{

   return( TGpsTime(Source) -= InSeconds );

}

TGpsTime &
TGpsTime::operator-=
   (
   const double InSeconds
   )
{

   Seconds_ -= InSeconds;
   while ( Seconds_ < 0.0 )
   {
      Seconds_ += SECONDS_PER_WEEK;
      --Week_;
   }
   while ( Seconds_ > SECONDS_PER_WEEK )
   {
      Seconds_ -= SECONDS_PER_WEEK;
      ++Week_;
   }

   return( *this );

}

double const
operator-
   (
   const TGpsTime & Time1,
   const TGpsTime & Time2
   )
{

   double DeltaSeconds = ( Time1.Week - Time2.Week ) * SECONDS_PER_WEEK;

   DeltaSeconds += ( Time1.Seconds - Time2.Seconds );

   return( DeltaSeconds );

}


void
TGpsTime::JulianDateTime
   (
   int    & Year,
   int    & Month,
   int    & Day,
   int    & Hour,
   int    & Minute,
   double & Secs
   ) const
{

   TDateTime DateTime   = GpsStartDateTime + ( Week*SECONDS_PER_WEEK + Seconds )/SecondsPerDay;

   unsigned short sYear, sMonth, sDay;
   unsigned short sHour, sMinute, sSeconds, sMilliseconds;

   DateTime.DecodeDate( &sYear, &sMonth, &sDay );
   DateTime.DecodeTime( &sHour, &sMinute, &sSeconds, &sMilliseconds );

   Year                 = sYear;
   Month                = sMonth;
   Day                  = sDay;
   Hour                 = sHour;
   Minute               = sMinute;
   Secs                 = sSeconds + ( (double)sMilliseconds )*0.001 + fmod( Seconds, 0.001 );


}

TGpsTime::TGpsTime
   (
   const int    Year,
   const int    Month,
   const int    Day,
   const int    Hour,
   const int    Minute,
   const double Secs
   )
{

   const int iSecs      = (int) Secs;
   const int iMillisecs = (int) ( ( Secs - iSecs )*1000.0 );

   TDateTime DateTime   = EncodeDateTime( Year, Month, Day, Hour, Minute, iSecs, iMillisecs );

   Week                 = WeeksBetween( DateTime, GpsStartDateTime );

   TDateTime WeekBegin  = GpsStartDateTime + Week*7;

   Seconds              = SecondsBetween( DateTime, WeekBegin ) + fmod( Secs, 0.001 );

}


TDateTime const
TGpsTime::ToTDateTime
   (
   ) const
{

   int     Year, Month, Day, Hour, Minute;
   double  Seconds;

   JulianDateTime( Year, Month, Day, Hour, Minute, Seconds );

   TDateTime Date( Year, Month, Day );

   int iSeconds = (int) Seconds;
   int Msecs    = 1000*(Seconds - iSeconds);
   TDateTime Time( Hour, Minute, iSeconds, Msecs );

   return( Date + Time );

}

TGpsTime::TGpsTime
   (
   const TDateTime & DateTime
   )
{

   unsigned short Year, Month, Day;
   unsigned short Hour, Minute, sSeconds, Msecs;

   DateTime.DecodeDate( &Year, &Month, &Day );
   DateTime.DecodeTime( &Hour, &Minute, &sSeconds, &Msecs);

   double dSeconds = sSeconds + Msecs*0.001;


   TGpsTime Time( Year, Month, Day, Hour, Minute, dSeconds );
   Week_    = Time.Week;
   Seconds_ = Time.Seconds;

}







