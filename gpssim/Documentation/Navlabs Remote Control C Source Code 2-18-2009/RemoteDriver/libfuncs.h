#ifndef CLIBS_H
#define CLIBS_H
//#include "svstruct.h"
#pragma option -a1

//////////////////////////////////////////////////////////////////////////
//////////////   Library functions declarations and prototypes  //////////
//////////////////////////////////////////////////////////////////////////
#if(0)
extern "C" void GetSvRecord(double time,int vehicle,SVStruct *SVD);

extern "C" void ConstructSVRecord(int Week,double SecIntoWeek,double EcefPos[3],
						  unsigned char AprioriStatus[32],SVStruct *SVData,
						  int Criteria,int Mask,int NumInDop,int IgnoreHealth,
						  int MaxChans);
#endif                    
extern "C"  int  MyCopyFile(char *source,char *dest);

extern "C" char txpos_tg(int satnum,double time, double pos[3]);
extern "C" int tsvdata (double InitTime);

extern "C" int matinv(double mat[4][4],double wrk[4][4],int num1,int num,double I[4][4]);
extern "C" void lib_ecef_geo(double Ecef[3],double *Lat, double *Lon, double *Alt);
extern "C" void lib_geo_ecef(double Lat, double Lon, double Alt,double Ecef[3]);
extern "C" void lib_cpe_2lev(double cpe[9],double *latitude,double *longitude);
extern "C" void lib_cpe_2ecef(double cpe[3][3],double smaxis,double ecc,double alt,          /* ellipsoidal altitude + down  */
								 double pos_ecef[3]);
extern "C" void lib_cpe_make(double lat,double lon,double wander,double cpe[3][3]);
extern "C" void lib_cpe_wep(double cpe_l[3][3],double altitude,double velocity[3],
								 double wep_p[3]);

extern "C" void lib_cep_make(double lat,double lon,double wander,double cep[3][3]);
extern "C" void lib_cbp_make(double roll,double pitch,double head,double cbp[3][3]);
extern "C" void lib_coi_make(double declination,double ra,double coi[3][3]);
extern "C" void lib_cie_make(double time,double cie[3][3]);
extern "C" void lib_dcm_rot(double cab[3][3],double delta,double wabb[3]);
extern "C" void lib_mat_unpack(double b[3],double a[3][3]);
extern "C" void lib_mat_pack(double a[3][3],double b[3]);
extern "C" long int lib_mth_nint( double value);
extern "C" double gauss(void);
extern "C" double seeded_gauss(unsigned int *seed);
extern "C" void lib_add_m2m(double a[3][3],double b[3][3],double c[3][3]);
extern "C" void lib_add_v2v(double a[3],double b[3],double c[3]);
extern "C" void lib_mul_sxv(double s,double a[3],double b[3]);
extern "C" void lib_cpy_m2m(double a[3][3],double b[3][3]);
extern "C" void lib_mul_mxm(double a[3][3],double b[3][3],double c[3][3]);
extern "C" void lib_mul_mtxm(double a[3][3],double b[3][3],double c[3][3]);
extern "C" void lib_cpy_v2v(double a[3],double b[3]);
extern "C" void lib_mul_mxv(double a[3][3],double b[3],double c[3]);
extern "C" void lib_mul_mtxv(double a[3][3],double b[3],double c[3]);
extern "C" void lib_mul_mvxv(double a[9],double b[3],double c[3]);
extern "C" void lib_mat_v2m(double a[3],double b[3][3]);
extern "C" void lib_mat_mt(double a[3][3],double b[3][3]);
extern "C" void lib_mat_zero(double a[3][3]);
extern "C" void lib_vec_zero(double a[3]);
extern "C" void lib_mul_adotb(double a[3],double b[3],double *value);
extern "C" void lib_mul_axb(double a[3],double b[3],double c[3]);
extern "C" void lib_vec_mag(double a[3],double *value);
extern "C" void lib_vec_unit(double a[3],double b[3]);
extern "C" void lib_vec_aob(double a[3],double b[3],double ab[3][3]);
extern "C" void lib_dtog(int Y,int MO,int D,int H,int MI,int S,int  *WEEK,double *SECS );
extern "C" void lib_gtod(int gpsweek,double sec_into_week,int  *y,int  *mo,int *day,int *h,
				  int *mi,double *secs);
extern "C" void lib_lat2dms(double lat,int *deg,int *min,double *sec,char *ns);
extern "C" void lib_lon2dms(double lon,int *deg,int *min,double *sec,char *ew);
extern "C" void lib_dms2lat(char ns,int deg,int min,double sec,double *latitude);
extern "C" void lib_dms2lon(char ew,int deg,int min,double sec,double *longitude);
extern "C" void lib_NED_vec(double pos[3],double N[3],double E[3],double V[3]);
extern "C" int  GetGeneratedSats(int VehNum,double time,double *Gdop,int *Num,
											int SvId[32],short SvEl[32],short SvAz[32]);

//extern "C" void ComputeDop(SVStruct *SV,double Mask,int Num,int Criter,int Best[32]);
extern "C" void GetBestFour(int Num,int Criteria,int SVs[32],double H[32][4],
								 int Best[32],double *Gdop,double *Pdop, double *Hdop);
extern "C" void GetBestFive(int Num,int Criteria,int SVs[32],double H[32][4],
									 int Best[32],double *Gdop,double *Pdop, double *Hdop);
extern "C" void GetBestSix(int Num,int Criteria,int SVs[32],double H[32][4],
									int Best[32],double *Gdop,double *Pdop, double *Hdop);
extern "C" void GetBestEight(int Num,int Criteria,int SVs[32],double H[32][4],
									  int Best[32],double *Gdop,double *Pdop, double *Hdop);
extern "C" void GetBestTen(int Num,int Criteria,int SVs[32],double H[32][4],
									int Best[32],double *Gdop,double *Pdop, double *Hdop);
extern "C" void D_X_R_2Eci(double PosEci[3],double VelEci[3],double coi[3][3]);
#pragma option -a.

#endif
