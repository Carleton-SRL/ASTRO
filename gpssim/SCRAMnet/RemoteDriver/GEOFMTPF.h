#ifndef GEOFMTPF_HPP
#define GEOFMTPF_HPP
#include <inifiles.hpp>
#include "GeoFrmt.h"

#define DefaultFmtDeg        "%9.5lf"
#define DefaultFmtDegMin     "%3d %6.3lf"
#define DefaultFmtDegMinSec  "%3d %2d %4.1lf"
#define DefaultFmtAlt        "%5.1lf"
#define DefaultFmtVel        "%5.2lf"
#pragma option -a1

class GeoFrmtProfile : public TIniFile {
public:
   GeoFrmtProfile();
   _fastcall virtual ~GeoFrmtProfile();
   GeoFormat::DegFormat GetDegFormat();
   GeoFormat::AltFormat GetAltFormat();
   GeoFormat::VelFormat GetVelFormat();
   void WriteDegFormat(const GeoFormat::DegFormat &Fmt);
   void WriteAltFormat(const GeoFormat::AltFormat &Fmt);
   void WriteVelFormat(const GeoFormat::VelFormat &Fmt);
   void GetFmtDeg(AnsiString &FmtDeg);
   void GetFmtDegMin(AnsiString &FmtDegMin);
   void GetFmtDegMinSec(AnsiString &FmtDegMinSec);
   void GetFmtAlt(AnsiString &FmtAlt);
   void GetFmtVel(AnsiString &FmtVel);
};

#pragma option -a.
#endif

                                
