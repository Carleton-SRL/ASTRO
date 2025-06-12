/****************************************************************************/
/*  icd200.h                                                                */
/*                                                                          */
/*           Copyright KBN Services 1988, all rights reserved               */
/*                                                                          */
/*  Global constants (based on ICD-GPS-200)                                 */
/****************************************************************************/

#define  MU         3.986005e14        /* Earth's gravitational cons.  */
#define  SQRT_MU    19964981.843217
#define  REL_F      (-4.442807633e-10) /* Relativistic clock correction*/
                                       /* coefficient                  */
#define  ICD_200_PI 3.1415926535898    /* PI defined in ICD-GPS-200    */

#define  SECS_PER_WEEK       604800.0
#define  TWO_4     (16.0)
#define  TWO_5     (32.0)
#define  TWO_8     (256.0)
#define  TWO_9     (512.0)
#define  TWO_10    (1024.0)
#define  TWO_11    (2048.0)
#define  TWO_12    (4096.0)
#define  TWO_14    (16384.0)
#define  TWO_15    (32768.0)
#define  TWO_16    (65536.0)
#define  TWO_19    (524288.0)
#define  TWO_20    (1048576.0)
#define  TWO_21    (2097152.0)
#define  TWO_23    (8388608.0)
#define  TWO_24    (16777216.0)
#define  TWO_25    (33554432.0)
#define  TWO_27    (134217728.0)
#define  TWO_28    (268435456.0)
#define  TWO_29    (536870912.0)
#define  TWO_30    (1073741824.0)
#define  TWO_31    (2147483648.0)
#define  TWO_33    (8589934592.0)
#define  TWO_38    (274877906944.0)
#define  TWO_43    (8796093022208.0)
#define  TWO_55    (36028797018963968.0)

#define  TWO_50    (TWO_20*TWO_30)

#define  TWO_M11   (1.0/TWO_11)
#define  TWO_M20   (1.0/TWO_20)
#define  TWO_M21   (1.0/TWO_21)
#define  TWO_M23   (1.0/TWO_23)
#define  TWO_M55   (1.0/TWO_55)
#define  TWO_M43   (1.0/TWO_43)
#define  TWO_M31   (1.0/TWO_31)
#define  TWO_M38   (1.0/TWO_38)
#define  TWO_M5    (1.0/TWO_5)
#define  TWO_M29   (1.0/TWO_29)
#define  TWO_M33   (1.0/TWO_33)
#define  TWO_M19   (1.0/TWO_19)

#define  RAD_PER_SEMI  (3.1415926535898)

#define NAV_TGD_SF            (TWO_M31)
#define NAV_TOC_SF            (TWO_4)
#define NAV_AF2_SF            (TWO_M55)
#define NAV_AF1_SF            (TWO_M43)
#define NAV_AF0_SF            (TWO_M31)
#define NAV_CRS_SF            (TWO_M5)
#define NAV_DELTAN_SF         (TWO_M43*RAD_PER_SEMI)
#define NAV_M0_SF             (TWO_M31*RAD_PER_SEMI)
#define NAV_CUC_SF            (TWO_M29)
#define NAV_ECC_SF            (TWO_M33)
#define NAV_CUS_SF            (TWO_M29)
#define NAV_SQRTA_SF          (TWO_M19)
#define NAV_TOE_SF            (TWO_4)
#define NAV_CIC_SF            (TWO_M29)
#define NAV_OMEGA0_SF         (TWO_M31*RAD_PER_SEMI)
#define NAV_CIS_SF            (TWO_M29)
#define NAV_I0_SF             (TWO_M31*RAD_PER_SEMI)
#define NAV_CRC_SF            (TWO_M5)
#define NAV_ARGOFPERIGEE_SF   (TWO_M31*RAD_PER_SEMI)
#define NAV_OMEGADOT_SF       (TWO_M43*RAD_PER_SEMI)
#define NAV_IDOT_SF           (TWO_M43*RAD_PER_SEMI)

#define ALM_ECC_SF            (TWO_M21)
#define ALM_TOA_SF            (TWO_12)
#define ALM_DELTAI_SF         (TWO_M19*RAD_PER_SEMI)
#define ALM_OMEGADOT_SF       (TWO_M38*RAD_PER_SEMI)
#define ALM_SQRTA_SF          (TWO_M11)
#define ALM_OMEGA0_SF         (TWO_M23*RAD_PER_SEMI)
#define ALM_ARGOFPERIGEE_SF   (TWO_M23*RAD_PER_SEMI)
#define ALM_M0_SF             (TWO_M23*RAD_PER_SEMI)
#define ALM_AF0_SF            (TWO_M20)
#define ALM_AF1_SF            (TWO_M38)


