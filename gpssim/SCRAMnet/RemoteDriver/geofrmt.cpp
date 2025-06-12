#include "pch.h"
#pragma hdrstop

using namespace std;

#include "wgs84.h"
#include "GeoFrmt.h"
#include "GeoFmtPf.h"

GeoFormat::GeoFormat
   (
   const DegFormat InDegFormat,
   const AltFormat InAltFmt,
   const VelFormat InVelFmt
   ) :
   DegFmt(InDegFormat),
   AltFmt(InAltFmt),
   LatPos("N"),
   LatNeg("S"),
   LonPos("E"),
   LonNeg("W")
{ }
GeoFormat::GeoFormat()
 :  LatPos("N"),LatNeg("S"),LonPos("E"),LonNeg("W")
{
   GeoFrmtProfile *FmtP = new GeoFrmtProfile();
   DegFmt = FmtP->GetDegFormat();
   AltFmt = FmtP->GetAltFormat();
   VelFmt = FmtP->GetVelFormat();
   FmtP->GetFmtDeg(FmtDegStr);
   FmtP->GetFmtDegMin(FmtDegMinStr);
   FmtP->GetFmtDegMinSec(FmtDegMinSecStr);
   FmtP->GetFmtAlt(FmtAltStr);
   FmtP->GetFmtVel(FmtVelStr);

   delete FmtP;

}

GeoFormat::~GeoFormat(){}

AnsiString GeoFormat::LattoStr(const double Lat)
{
   return(GeotoStr(Lat,LatPos,LatNeg));
}
AnsiString GeoFormat::LontoStr(const double Lon)
{
   return(GeotoStr(Lon,LonPos,LonNeg));
}
AnsiString
GeoFormat::GeotoStr
   (
   double Geo,
   const AnsiString Pos,
   const AnsiString Neg
   )
{
   char s[100];
   AnsiString Ret;
   switch ( DegFmt )
   {
      case FmtDeg:
      {
         if ( Geo < 0 )
         {
            Ret = Neg;
            Geo = fabs(Geo);
         } else
         {
            Ret = Pos;
         }
         sprintf(s,FmtDegStr.c_str(),Geo);
         Ret += s;
      }
      break;
      case FmtDegMin:
      {
         if ( Geo < 0 )
         {
            Ret = Neg;
            Geo = fabs(Geo);
         } else
         {
            Ret = Pos;
         }
         int deg = (int) Geo;
         double min = (Geo - deg)*60;
         if ( min > 59.9999 )
         {
            ++deg;
            min = 0;
         }
         sprintf(s,FmtDegMinStr.c_str(),deg,min);
         Ret += s;
      }
      break;
      case FmtDegMinSec:
      {
         if ( Geo < 0 )
         {
            Ret = Neg;
            Geo = fabs(Geo);
         } else
         {
            Ret = Pos;
         }
         int deg = (int) Geo;
         int min = (int)((Geo - deg)*60.0);
         double sec = (Geo - deg - (double)min/60.0)*3600;
         if ( sec > 59.99 )
         {
            ++min;
            sec = 0;
            if ( min >= 60 )
            {
               min = 0;
               ++deg;
            }
         }
         if ( min == 60 )
         {
            ++deg;
            min = 0;
         }
         sprintf(s,FmtDegMinSecStr.c_str(),deg,min,sec);
         Ret += s;
      }
      break;
   }
   return(Ret);
}

AnsiString
GeoFormat::GetLatLonUnits
   (
   ) const
{
   AnsiString Ret;
   switch ( DegFmt )
   {
      case FmtDeg:
      {
         Ret = "(deg)";
      }
      break;
      case FmtDegMin:
      {
         Ret = "(dd mm.mm)";
      }
      break;
      case FmtDegMinSec:
      {
         Ret = "(dd mm ss.ss)";
      }
      break;
   }
   return(Ret);
}

AnsiString
GeoFormat::AlttoStr
   (
   const double Alt,
   const bool   AddUnits
   )
{
   AnsiString Ret;
   switch ( AltFmt )
   {
      case FmtF:
      {
         char s[100];
         sprintf(s,FmtAltStr.c_str(),Alt*FEET_PER_METER);
         Ret = s;
      }
      break;
      case FmtM:
      {
         char s[100];
         sprintf(s,FmtAltStr.c_str(),Alt);
         Ret = s;
      }
      break;
   }
   if ( AddUnits )
   {
      Ret += GetDistUnits();
   }
   return(Ret);
}

AnsiString
GeoFormat::DisttoStr
   (
   const double Dist,
   const bool   AddUnits
   )
{
   return(AlttoStr(Dist,AddUnits));
}

AnsiString
GeoFormat::GetDistUnits
   (
   ) const
{
   AnsiString Ret;
   switch ( AltFmt )
   {
      case FmtF:
      {
         Ret = " ft";
      }
      break;
      case FmtM:
      {
         Ret = " m";
      }
      break;
   }
   return(Ret);
}

AnsiString
GeoFormat::VeltoStr
   (
   const double Vel,
   const bool   AddUnits
   )
{
   AnsiString Ret;
   switch ( VelFmt )
   {
      case FmtMps:
      {
         char s[100];
         sprintf(s,FmtVelStr.c_str(),VelConvert(Vel));
         Ret = s;
      }
      break;
      case FmtMph:
      {
         char s[100];
         sprintf(s,FmtVelStr.c_str(),VelConvert(Vel));
         Ret = s;
      }
      break;
      case FmtKph:
      {
         char s[100];
         sprintf(s,FmtVelStr.c_str(),VelConvert(Vel));
         Ret = s;
      }
      break;
   }
   if ( AddUnits )
   {
      Ret += GetVelUnits();
   }
   return(Ret);
}
AnsiString
GeoFormat::GetVelUnits
   (
   ) const
{
   AnsiString Ret;
   switch ( VelFmt )
   {
      case FmtMps:
      {
         Ret = " m/s";
      }
      break;
      case FmtMph:
      {
         Ret = " mph";
      }
      break;
      case FmtKph:
      {
         Ret = " kph";
      }
      break;
   }
   return(Ret);
}


double
GeoFormat::StrtoLat
   (
   const AnsiString &LatStr
   )
{
   return(StrtoGeo(LatStr,LatPos,LatNeg));
}
double
GeoFormat::StrtoLon
   (
   const AnsiString &LonStr
   )
{
   return(StrtoGeo(LonStr,LonPos,LonNeg));
}
double
GeoFormat::StrtoAlt
   (
   const AnsiString &AltStr
   )
{
   double Alt=0.0;
   switch ( AltFmt )
   {
      case FmtM:
      {
         char Str[100];
         strcpy(Str,AltStr.c_str());
         istrstream In(Str);
         In >> Alt;
      }
      break;
      case FmtF:
      {
         char Str[100];
         strcpy(Str,AltStr.c_str());
         istrstream In(Str);
         In >> Alt;
         Alt /= FEET_PER_METER;
      }
      break;
   }
   return(Alt);
}



double GeoFormat::StrtoGeo
   (
   const AnsiString InGeoStr,
   const AnsiString Pos,
   const AnsiString Neg
   )
{
   AnsiString GeoStr = InGeoStr;
   double Geo=0;
   switch ( DegFmt )
   {
      case FmtDeg:
      {
         sscanf(GeoStr.c_str(),FmtDegStr.c_str(),&Geo);
      }
      break;
      case FmtDegMin:
      {

         unsigned int Index = GeoStr.Pos(Neg);
         if ( Index )
         {
            GeoStr.Delete(Index,Neg.Length());
            GeoStr = GeoStr.Trim();
            int    deg=0;
            double min=0;
            char   Str[100];
            strcpy(Str,GeoStr.c_str());
            istrstream In(Str);
            In >> deg >> min;
            Geo = -(deg + min/60.0);
         } else if ( (Index=GeoStr.Pos(Pos)) != 0 )
         {
            GeoStr.Delete(Index,Pos.Length());
            GeoStr = GeoStr.Trim();
            int    deg=0;
            double min=0;
            char   Str[100];
            strcpy(Str,GeoStr.c_str());
            istrstream In(Str);
            In >> deg >> min;
            Geo = deg + min/60.0;
         }
      }
      break;
      case FmtDegMinSec:
      {
         unsigned int Index;
         bool ResNeg = false;
         if ( (Index=GeoStr.Pos(Neg)) != 0 )
         {
            GeoStr.Delete(Index,Neg.Length());
            GeoStr = GeoStr.Trim();
            ResNeg = true;
         } else if ( (Index=GeoStr.Pos(Pos)) != 0 )
         {
            GeoStr.Delete(Index,Pos.Length());
            GeoStr = GeoStr.Trim();
            ResNeg = false;
         }
         int    deg=0;
         int    min=0;
         double sec=0;
         char   Str[100];
         strcpy(Str,GeoStr.c_str());
         istrstream In(Str);
         In >> deg >> min >> sec;
         Geo = deg + min/60.0 + sec/3600.0;
         if ( ResNeg ) Geo = -Geo;
      }
      break;
   }
   return(Geo);
}

GeoFormat::GeoFormat(const GeoFormat &Source)
{
   (*this) = Source;
}
GeoFormat &GeoFormat::operator=(const GeoFormat &Source)
{

   if ( this == &Source )
   {
      return(*this);
   }
   
   FmtDegStr       = Source.FmtDegStr;
   FmtDegMinSecStr = Source.FmtDegMinSecStr;
   FmtDegMinStr    = Source.FmtDegMinStr;
   FmtAltStr       = Source.FmtAltStr;
   FmtVelStr       = Source.FmtVelStr;
   DegFmt          = Source.DegFmt;
   AltFmt          = Source.AltFmt;
   VelFmt          = Source.VelFmt;

   LatPos          = Source.LatPos;
   LatNeg          = Source.LatNeg;
   LonPos          = Source.LonPos;
   LonNeg          = Source.LonNeg;

   return(*this);
}
AnsiString
GeoFormat::GetInputFmt
   (
   const AnsiString &OutputFmt
   )
{

   AnsiString Fmt = "";
   for ( int i=0; i<OutputFmt.Length(); ++i )
   {
      if ( (OutputFmt[i] >= '9' || OutputFmt[i] <= '1') && OutputFmt[i] != '.' )
         Fmt += OutputFmt[i];
   }
   return(Fmt);
}



double const
GeoFormat::VelConvert
   (
   const double Vel
   ) const
{

   double RetVel = Vel;
   switch ( VelFmt )
   {
      case FmtMps:
      {
         RetVel = Vel;
      }
      break;
      case FmtMph:
      {
         RetVel = Vel/MPH2MS;
      }
      break;
      case FmtKph:
      {
         RetVel = Vel/KPH2MS;
      }
      break;
   }
   return(RetVel);
}

