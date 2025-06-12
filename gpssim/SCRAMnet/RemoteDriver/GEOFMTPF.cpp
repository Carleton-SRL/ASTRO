#include "pch.h"
#pragma hdrstop

#include "GeoFmtpf.h"

#define MAX_FORMAT_STR (100)

static const char *DegFmtStr = "DDD.DDDD";
static const char *DegMinFmtStr = "DDD MM.MMMM";
static const char *DegMinSecFmtStr = "DDD MM SS.SSSS";
static const char *AltMFmtStr = "M";
static const char *AltFFmtStr = "F";
static const char *VelMpsFmtStr = "m/s";
static const char *VelMphFmtStr = "mph";
static const char *VelKphFmtStr = "kph";
///////////////////////////////////////////////////////////////////////////////
//  GeoFrmtProfile
// Profile object for geo format
///////////////////////////////////////////////////////////////////////////////
GeoFrmtProfile::GeoFrmtProfile
   (
   )
   : TIniFile("Voyager.INI")
{ }

_fastcall GeoFrmtProfile::~GeoFrmtProfile(){}
///////////////////////////////////////////////////////////////////////////////
//   GetDegFormat()
// Returns the deg format (deg, deg min.min, deg min sec.sec);
///////////////////////////////////////////////////////////////////////////////
GeoFormat::DegFormat
GeoFrmtProfile::GetDegFormat()
{
//   const char *DefaultFmtDeg = DegMinFmtStr;
   AnsiString FmtStr = ReadString("GeoFormat","DegFormat",DegMinFmtStr);

   if ( FmtStr.Pos(DegFmtStr) )
      return(GeoFormat::FmtDeg);
   else if ( FmtStr.Pos(DegMinFmtStr) )
      return(GeoFormat::FmtDegMin);
   else if ( FmtStr.Pos(DegMinSecFmtStr) )
      return(GeoFormat::FmtDegMinSec);
   else
      return(GeoFormat::FmtDegMin);
}
///////////////////////////////////////////////////////////////////////////////
//   GetAltFormat()
// Returns the alt format ( m, f);
///////////////////////////////////////////////////////////////////////////////
GeoFormat::AltFormat
GeoFrmtProfile::GetAltFormat()
{
   AnsiString FmtStr = ReadString("GeoFormat","AltFormat",AltFFmtStr);
   if ( FmtStr.Pos(AltMFmtStr) )
      return(GeoFormat::FmtM);
   else if ( FmtStr.Pos(AltFFmtStr) )
      return(GeoFormat::FmtF);
   else
      return(GeoFormat::FmtM);
}
///////////////////////////////////////////////////////////////////////////////
//   GetVelFormat()
// Returns the vel format ( m/s, mph, kph)
///////////////////////////////////////////////////////////////////////////////
GeoFormat::VelFormat
GeoFrmtProfile::GetVelFormat()
{
   AnsiString FmtStr = ReadString("GeoFormat","VelFormat",VelMpsFmtStr);
   if ( FmtStr.Pos(VelMpsFmtStr) )
      return(GeoFormat::FmtMps);
   else if ( FmtStr.Pos(VelMphFmtStr) )
      return(GeoFormat::FmtMph);
   else
      return(GeoFormat::FmtKph);
}
///////////////////////////////////////////////////////////////////////////////
// WriteDegFormat
//   Writes the degree format to the initialization file
///////////////////////////////////////////////////////////////////////////////
void
GeoFrmtProfile::WriteDegFormat
   (
   const GeoFormat::DegFormat &Fmt
   )
{
   switch ( Fmt )
   {
      case GeoFormat::FmtDeg:
         WriteString("GeoFormat","DegFormat",DegFmtStr);
      break;
      case GeoFormat::FmtDegMin:
         WriteString("GeoFormat","DegFormat",DegMinFmtStr);
      break;
      case GeoFormat::FmtDegMinSec:
         WriteString("GeoFormat","DegFormat",DegMinSecFmtStr);
      break;
      default:
         WriteString("GeoFormat","DegFormat",DegMinFmtStr);
      break;
   }
}
///////////////////////////////////////////////////////////////////////////////
// WriteAltFormat
//   Writes the altitude format to the initialization file
///////////////////////////////////////////////////////////////////////////////
void
GeoFrmtProfile::WriteAltFormat
   (
   const GeoFormat::AltFormat &Fmt
   )
{
   switch ( Fmt )
   {
      case GeoFormat::FmtM:
         WriteString("GeoFormat","AltFormat",AltMFmtStr);
      break;
      case GeoFormat::FmtF:
         WriteString("GeoFormat","AltFormat",AltFFmtStr);
      break;
   }
}

///////////////////////////////////////////////////////////////////////////////
// WriteVelFormat
//   Writes the velocity format to the initialization file
///////////////////////////////////////////////////////////////////////////////
void
GeoFrmtProfile::WriteVelFormat
   (
   const GeoFormat::VelFormat &Fmt
   )
{
   switch ( Fmt )
   {
      case GeoFormat::FmtMps:
         WriteString("GeoFormat","VelFormat",VelMpsFmtStr);
      break;
      case GeoFormat::FmtMph:
         WriteString("GeoFormat","VelFormat",VelMphFmtStr);
      break;
      case GeoFormat::FmtKph:
         WriteString("GeoFormat","VelFormat",VelKphFmtStr);
      break;
   }
}

///////////////////////////////////////////////////////////////////////////////
//   GetFmtDeg(string &FmtDeg)
// Fills FmtDeg with the format of geo data in ddd.ddddd
///////////////////////////////////////////////////////////////////////////////
void GeoFrmtProfile::GetFmtDeg
   (
   AnsiString &FmtDeg
   )
{
   FmtDeg = ReadString("GeoFormat","FmtDeg",DefaultFmtDeg);
}
///////////////////////////////////////////////////////////////////////////////
//   GetFmtAlt(string &FmtAlt)
// Fills FmtAlt with the format of geo data in ddd.ddddd
///////////////////////////////////////////////////////////////////////////////
void
GeoFrmtProfile::GetFmtAlt
   (
   AnsiString &FmtAlt
   )
{

   FmtAlt = ReadString("GeoFormat","FmtAlt",DefaultFmtAlt);

}

///////////////////////////////////////////////////////////////////////////////
//   GetFmtVel(string &FmtVel)
// Fills FmtVel with the format of vel
///////////////////////////////////////////////////////////////////////////////
void
GeoFrmtProfile::GetFmtVel
   (
   AnsiString &FmtVel
   )
{

   FmtVel = ReadString("GeoFormat","FmtVel",DefaultFmtVel);

}
///////////////////////////////////////////////////////////////////////////////
//   GetFmtDegMin(string &FmtDegMin)
// Fills FmtDegMin with the format of geo data in ddd mm.mmmm
///////////////////////////////////////////////////////////////////////////////
void
GeoFrmtProfile::GetFmtDegMin
   (
   AnsiString &FmtDegMin
   )
{

   FmtDegMin = ReadString("GeoFormat","FmtDegMin",DefaultFmtDegMin);

}
///////////////////////////////////////////////////////////////////////////////
//   GetFmtDegMinSec(string &FmtDegMinSet)
// Fills FmtDegMinSec with the format of geo data in ddd mm ss.ssss
///////////////////////////////////////////////////////////////////////////////
void
GeoFrmtProfile::GetFmtDegMinSec
   (
   AnsiString &FmtDegMinSec
   )
{

   FmtDegMinSec = ReadString("GeoFormat","FmtDegMinSec",DefaultFmtDegMinSec);

}

