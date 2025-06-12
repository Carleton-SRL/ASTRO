//---------------------------------------------------------------------------


#ifndef NavStateFramH
#define NavStateFramH
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//
// $Workfile:: NavStateFram.h                                        $
//
// $Revision:: 3                                                     $
//
// $History:: NavStateFram.h                                         $
//
//*****************  Version 3  *****************
//User: Michael Wade Date: 7/28/02    Time: 10:41p
//Updated in $/TapMsec
//Use PosVec
//
//*****************  Version 2  *****************
//User: Michael Wade Date: 7/23/02    Time: 7:47p
//Updated in $/TapMsec
//Added Source Safe keywords
//BUILDER_INCLUDES ifdef
//Added vehicle number to top label
//
//
//---------------------------------------------------------------------------
//------------------------------------------------------------------------------
#ifndef BUILDER_INCLUDES
//------------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "OvcLabel.hpp"
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "ovclabel.hpp"
#include "RzPanel.hpp"
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
#ifndef GeoFrmtH
#include "GeoFrmt.h"
#endif

#ifndef VehTruthH
#include "VehTruth.h"
#endif
//---------------------------------------------------------------------------
class TNavStateFrame : public TFrame
{
__published:	// IDE-managed Components
   TPanel *NavPanel;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   TLabel *Label4;
   TLabel *Label5;
   TLabel *Label6;
   TLabel *LatLbl;
   TLabel *Label7;
   TLabel *LonLbl;
   TLabel *Label11;
   TLabel *AltLbl;
   TLabel *Label8;
   TLabel *Label12;
   TLabel *SpeedLbl;
   TLabel *Label13;
   TLabel *VelNorthLbl;
   TLabel *Label15;
   TLabel *VelEastLbl;
   TLabel *Label17;
   TLabel *VelDownLbl;
   TLabel *Label19;
   TLabel *HeadingLbl;
   TLabel *Label14;
   TLabel *Label16;
   TLabel *Label18;
   TLabel *PosEcefXLbl;
   TLabel *Label21;
   TLabel *PosEcefYLbl;
   TLabel *Label23;
   TLabel *PosEcefZLbl;
   TLabel *Label25;
   TLabel *VelEcefXLbl;
   TLabel *Label27;
   TLabel *VelEcefYLbl;
   TLabel *Label29;
   TLabel *VelEcefZLbl;
   TImage *Image1;
   TImage *Image2;
   TStaticText *DateTxt;
   TStaticText *TimeTxt;
   TStaticText *GpsWeekTxt;
   TStaticText *GpsSecTxt;
   TStaticText *LatTxt;
   TStaticText *LonTxt;
   TStaticText *AltTxt;
   TStaticText *SpeedTxt;
   TStaticText *VelNorthTxt;
   TStaticText *VelEastTxt;
   TStaticText *VelDownTxt;
   TStaticText *HeadingTxt;
   TStaticText *PosEcefXTxt;
   TStaticText *PosEcefYTxt;
   TStaticText *PosEcefZTxt;
   TStaticText *VelEcefXTxt;
   TStaticText *VelEcefYTxt;
   TStaticText *VelEcefZTxt;
   TRzPanel *TopPnl;
   TRzPanel *RzPanel1;
   TImage *NacStateImage;
   TRzPanel *TopClientPnl;
   TOvcLabel *NavStateLbl;
private:	// User declarations
   GeoFormat *pGeoFormat;
public:
   void SetNavState( const VehTruthRec & TruthRec );
   __fastcall TNavStateFrame( TComponent* Owner );
   __fastcall ~TNavStateFrame();
   void SetNewGeoFormat();
   void SetVehicleNumber( const int VehNum );
};
//---------------------------------------------------------------------------
extern PACKAGE TNavStateFrame *NavStateFrame;
//---------------------------------------------------------------------------
#endif
