#ifndef GpsTimeH
#define GpsTimeH

//---------------------------------------------------------------------------
//
// $Workfile:: gpstime.h                                             $
//
// $Revision:: 3                                                     $
//
// $History:: gpstime.h                                              $
//
//*****************  Version 3  *****************
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


#define SECONDS_PER_WEEK (604800.0)


class TGpsTime
{
private:

   int           Week_;
   double        Seconds_;

public:
   TGpsTime(): Week_( 0 ), Seconds_( 0.0 ) {}

   TGpsTime( const TDateTime &DateTime );

   TGpsTime
      (
      const int      Year,
      const int      Month,
      const int      Day,
      const int      Hour,
      const int      Minute,
      const double   Seconds
      );

   TGpsTime
      (
      const unsigned long InWeek,
      const double        InSeconds
      ) :
      Week_( InWeek ),
      Seconds_( InSeconds )
   {}

   TGpsTime
      (
      const TGpsTime &Source
      )
   {
      Week_     = Source.Week;
      Seconds_  = Source.Seconds;
   }

   TGpsTime &          operator =   ( const TGpsTime & Source );
   TGpsTime &          operator +=  ( const double InSeconds );
   TGpsTime &          operator -=  ( const double InSeconds );

   friend double const operator -   ( const TGpsTime & Time1, const TGpsTime & Time2 );
   friend bool const   operator <   ( const TGpsTime & Time1, const TGpsTime & Time2 );
   friend bool const   operator <=  ( const TGpsTime & Time1, const TGpsTime & Time2 );
   friend bool const   operator >   ( const TGpsTime & Time1, const TGpsTime & Time2 );
   friend bool const   operator >=  ( const TGpsTime & Time1, const TGpsTime & Time2 );
   friend bool const   operator ==  ( const TGpsTime & Time1, const TGpsTime & Time2 );
   friend bool const   operator !=  ( const TGpsTime & Time1, const TGpsTime & Time2 );

   friend bifstream &  operator >>  ( bifstream& InStream, TGpsTime &Time );
   friend bofstream &  operator <<  ( bofstream& OutStream, TGpsTime &Time );
   friend std::ostream &    operator <<  ( std::ostream& OutStream, const TGpsTime &Time );

   void            FromTDateTime( const TDateTime &DateTime );
   TDateTime const ToTDateTime() const;

   friend TGpsTime const DateToGpsTime(const int Year, const int Month, const int Day,
      const int Hour, const int Minute, const int Seconds);

   void JulianDateTime( int &Year, int &Month, int &Day, int &Hour, int &Minute, double &secs) const;

   __property int       Week       = { read = Week_,       write = Week_      };
   __property double    Seconds    = { read = Seconds_,    write = Seconds_   };
   __property TDateTime DateTime   = { read = ToTDateTime, write = FromTDateTime };


};

const TGpsTime operator+( const TGpsTime& Source, const double sec );
const TGpsTime operator-( const TGpsTime& Source, const double sec );

typedef TGpsTime GPSTime;


#endif

