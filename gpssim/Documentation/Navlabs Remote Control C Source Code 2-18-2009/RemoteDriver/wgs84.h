#ifndef Wgs84H
#define Wgs84H


//---------------------------------------------------------------------------
//
// $Workfile:: wgs84.h                                               $
//
// $Revision:: 1                                                     $
//
// $History:: wgs84.h                                                $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 9/03/02    Time: 7:29p
//Created in $/RemoteDriver
//
//
//---------------------------------------------------------------------------

/****************************************************************************/
/*  wgs84.h                                                                 */
/*                                                                          */
/*           Copyright KBN Services 1988, all rights reserved               */
/*                                                                          */
/*  Global constants (based on WGS-84)                                      */
/****************************************************************************/

#define  PI         3.1415926535898    /* The value of PI              */
#define  PI_OVER_2  (PI/2.0)
#define  TWO_PI     (2.0*PI)
#define  DPH2RPS    (D2R/3600.0)       /* degrees/hour -> rad/sec      */
#define  UG2MKS     1.0e-5             /* ug's to meters/sec/sec       */
#define  PPM2NO     1.e-6              /* PPM to dimensionless units   */
#define  MR2RAD     0.001              /* millirad to radians          */
#define  MIN2SEC    (1.0/60.0)         /* minutes to seconds           */
#define  SMA_AXIS   6378137.           /* The semi major axis of the   */

#define  R2D   180.0/PI 
#define  D2R   PI/180.0 

                                       /* reference ellipsoid          */
#define  SMA_AXIS_2 (SMA_AXIS*SMA_AXIS)
#define  FLATTEN    0.00335281066474   /* The flattening coefficient   */
                                       /* of the reference ellipsoid   */
#define  FIRST_E_2  (FLATTEN*(2.0-FLATTEN)) /* First eccentricity squared*/
#define  FIRST_E_4  (FIRST_E_2*FIRST_E_2)
#define  OMEGA_2    (1.0 - FIRST_E_2)
#define  EARTH_RATE 7.2921151467e-5    /* Earth rotation rate          */
#define  EQ_GRAV    9.7803267714       /* Gravitational acceleration   */
                                       /* at the equator on the ellipsoid*/
#define  GRAVITY_MKS  EQ_GRAV
#define  FEET_PER_METER 3.2808399      /* Number of feet in a meter    */
#define  GRAVITY_ENGLISH EQ_GRAV*FEET_PER_METER
#define  METERS_PER_FOOT 1.0/FEET_PER_METER

#define  GRAV_RATIO 0.00344978600313   /* Ratio of rotational to       */
                                       /* gravitational accelerations  */
#define  SPEED_LIGHT 299792458.0       /* Speed of light               */

#define  WGS84_J2  1.082639e-3
#define  WGS84_J3 -2.565e-6 
#define  WGS84_J4 -1.608e-6
#define  WGS84_GCONSTANT 3.986031937e14  /* Newtons constant * Me (m^3/s^2)*/

#define  MPH2MS (5280.0/FEET_PER_METER/3600.0)
#define  KPH2MS (1000.0/3600.0)
#define  KNOT2MS (6000.0/FEET_PER_METER/3600.0)
#define  KPS2MS (1000.0)
#define  GRAVITY_ENGLISH EQ_GRAV*FEET_PER_METER
#define  MILE2M (5280.0*METERS_PER_FOOT)
#define  GRAV_RATIO 0.00344978600313   /* Ratio of rotational to       */


#endif
