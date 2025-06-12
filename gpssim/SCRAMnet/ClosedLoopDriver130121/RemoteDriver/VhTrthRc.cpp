#include "pch.h"
#pragma hdrstop

#include "libfuncs.h"
#include "VehTruth.h"
#include "wgs84.h"


void
VehTruthRec::ConvertECEFtoGeo
   (
   VehTruthRec &TruthRec,
   double PosGeo[3],
   double VelNed[3]
   )
{
   double cep[3][3];
   lib_ecef_geo(TruthRec.PosEcef,&PosGeo[0],&PosGeo[1],&PosGeo[2]);
   lib_cep_make(PosGeo[0],PosGeo[1],0.0,cep);
   lib_mul_mxv(cep,TruthRec.VelEcef,VelNed);
}

void
VehTruthRec::PosToGeo
   (
   double &Latitude,
   double &Longitude,
   double &Altitude
   ) const
{
#define MIN_ANGLE       0.001745328     /* Polar guard angle (sine of .1 deg)*/

	 const double EqProj = PosEcef[0]*PosEcef[0] + PosEcef[1]*PosEcef[1];
	 const double b      = EqProj/SMA_AXIS_2;
    const double c      = (PosEcef[2]*PosEcef[2])/SMA_AXIS_2;
    const double a0     = OMEGA_2*c;
	 const double a1     = 2.0*a0;
	 const double a2     = a0 + b - FIRST_E_4;
	 const double a3     = -2.0*FIRST_E_4;
	 const double a4     = -FIRST_E_4;


	 double q = FIRST_E_2;
    for ( int count = 0; count < 3; count++ )
    {
		  const double q_2 = q*q;
		  const q_3        = q*q_2;
		  q   = q - (a0*q*q_3 + a1*q_3 + a2*q_2 + a3*q + a4)/
                (4*a0*q_3 + 3*a1*q_2 + 2*a2*q + a3);
    }

	 const double q_plus_1 = q + 1.0;

        /*      Make sure we aren't too close to the poles      */

	 if ( EqProj < ((EqProj + PosEcef[2]*PosEcef[2])*MIN_ANGLE*MIN_ANGLE))
    {
		  Longitude = 0.0;
	 } else {
		  Longitude = atan2(PosEcef[1],PosEcef[0]);
	 }
	 Latitude            = atan2((q_plus_1*PosEcef[2]), sqrt(EqProj));

    const double radius = (1.0 - (OMEGA_2/FIRST_E_2)*q)*SMA_AXIS;
	 Altitude            = radius*(sqrt(b/(q_plus_1*q_plus_1) + c));

}


VehTruthRec &VehTruthRec::operator=(const VehTruthRec &Source)
{
   if ( this == &Source )
   {
      return(*this);
   }
   GpsTime = Source.GpsTime;
   for ( int i=0; i<3; ++i )
   {
      PosEcef[i]   = Source.PosEcef[i];
      VelEcef[i]   = Source.VelEcef[i];
      AccEcef[i]   = Source.AccEcef[i];
      JerkEcef[i]  = Source.JerkEcef[i];
      Attitude[i]  = Source.Attitude[i];
      AngRate[i]   = Source.AngRate[i];
   }
   return(*this);
}
int operator ==
   (
   const VehTruthRec &Data1,
   const VehTruthRec &Data2
   )
{
   return((Data1.GpsTime == Data2.GpsTime));
}

VehTruthRec::VehTruthRec
   (
   const VehTruthRec &Source
   )
{

   *this = Source;
}
///////////////////////////////////////////////////////////////////////////////
//   bfstream& operator<<(bfstream& OutStream, VehTruthRec &Truth)
// Writes a truth record to the given output stream.
///////////////////////////////////////////////////////////////////////////////
bofstream& operator<<( bofstream& OutStream, VehTruthRec &Truth) {

   OutStream << Truth.GpsTime;
   OutStream << (Truth.PosEcef[0]);
   OutStream << Truth.PosEcef[1];
   OutStream << Truth.PosEcef[2];
   OutStream << Truth.VelEcef[0] << Truth.VelEcef[1] << Truth.VelEcef[2];
   OutStream << Truth.AccEcef[0] << Truth.AccEcef[1] << Truth.AccEcef[2];
   OutStream << Truth.JerkEcef[0] << Truth.JerkEcef[1] << Truth.JerkEcef[2];
   OutStream << Truth.Attitude[0] << Truth.Attitude[1] << Truth.Attitude[2];
   OutStream << Truth.AngRate[0] << Truth.AngRate[1] << Truth.AngRate[2];

   return(OutStream);
}
///////////////////////////////////////////////////////////////////////////////
//   bfstream& operator>>( bfstream& InStream, VehTruthRec &Truth);
// Reads a truth record from the given input stream.
///////////////////////////////////////////////////////////////////////////////
bifstream& operator>>( bifstream& InStream, VehTruthRec &Truth) {

   InStream >> Truth.GpsTime;
   InStream >> Truth.PosEcef[0] >> Truth.PosEcef[1] >> Truth.PosEcef[2];
   InStream >> Truth.VelEcef[0] >> Truth.VelEcef[1] >> Truth.VelEcef[2];
   InStream >> Truth.AccEcef[0] >> Truth.AccEcef[1] >> Truth.AccEcef[2];
   InStream >> Truth.JerkEcef[0] >> Truth.JerkEcef[1] >> Truth.JerkEcef[2];
   InStream >> Truth.Attitude[0] >> Truth.Attitude[1] >> Truth.Attitude[2];
   InStream >> Truth.AngRate[0] >> Truth.AngRate[1] >> Truth.AngRate[2];

   return(InStream);
}

