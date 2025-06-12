#ifndef GEOFRMT_HPP
#define GEOFRMT_HPP

#include <system.hpp>

#pragma pack(push,1)

class GeoFormat {
public:
   enum DegFormat { FmtDeg, FmtDegMin, FmtDegMinSec  };
   enum AltFormat { FmtM, FmtF };
   enum VelFormat { FmtMps, FmtMph, FmtKph };
   AnsiString FmtDegStr;
   AnsiString FmtDegMinSecStr;
   AnsiString FmtDegMinStr;
   AnsiString FmtAltStr;
   AnsiString FmtVelStr;
   DegFormat  DegFmt;
   AltFormat  AltFmt;
   VelFormat  VelFmt;
   AnsiString LatPos;
   AnsiString LatNeg;
   AnsiString LonPos;
   AnsiString LonNeg;
public:
   GeoFormat(const DegFormat InDegFmt, const AltFormat, const VelFormat);
	GeoFormat(const GeoFormat &Source);
   GeoFormat();
   ~GeoFormat();

	GeoFormat &operator=(const GeoFormat& Source);

   AnsiString GeotoStr(double Geo,const AnsiString Pos="", const AnsiString Neg="");
   AnsiString LontoStr(const double Lon);
   AnsiString LattoStr(const double Lat);
   AnsiString AlttoStr(const double Alt, const bool AddUnits=false);
   AnsiString DisttoStr(const double Alt, const bool AddUnits=false);
   AnsiString VeltoStr(const double Vel, const bool AddUnits=false);
   AnsiString GetVelUnits() const;
   AnsiString GetDistUnits() const;
   AnsiString GetLatLonUnits() const;
   double StrtoLon(const AnsiString &LonStr);
   double StrtoLat(const AnsiString &LatStr);
   double StrtoAlt(const AnsiString &AltStr);
   double StrtoVel(const AnsiString &VelStr);
   double StrtoGeo(const AnsiString GeoStr,const AnsiString Pos, const AnsiString Neg);
   AnsiString GetInputFmt(const AnsiString &OutputFmt);
   DegFormat GetDegFmt(){return(DegFmt);}
   AltFormat GetAltFmt(){return(AltFmt);}
   VelFormat GetVelFmt(){return(VelFmt);}
   double const VelConvert(const double Vel) const;

//   double StrtoGeo(const AnsiString Str);
};
#pragma pack(pop)

#endif


