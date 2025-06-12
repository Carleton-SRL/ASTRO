//---------------------------------------------------------------------------


#ifndef InitGeoFramH
#define InitGeoFramH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ovcbase.hpp"
#include "ovcef.hpp"
#include "ovclabel.hpp"
#include "ovcnf.hpp"
#include "ovcpb.hpp"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------

#include "MsgDataFrame.h"

class TInitGeoData {
public:
   TDateTime Date;
   TDateTime Time;
   double    LatDeg;
   double    LonDeg;
   double    Alt;
public:
   TInitGeoData() : LatDeg( 0 ), LonDeg( 0 ), Alt( 0 ) {}
};

class TInitGeoFrame : public TFrame
{
__published:	// IDE-managed Components
   TDateTimePicker *DatePicker;
   TOvcLabel *OvcLabel2;
   TOvcLabel *OvcLabel1;
   TDateTimePicker *TimePicker;
   TOvcLabel *OvcLabel3;
   TOvcLabel *OvcLabel4;
   TOvcNumericField *LatEdt;
   TOvcLabel *OvcLabel5;
   TOvcNumericField *LonEdt;
   TOvcLabel *OvcLabel6;
   TOvcNumericField *AltEdt;
private:	// User declarations
   static TInitGeoData  DefInitGeoData;
   void SetDisp( const TInitGeoData & InitGeoData );
public:		// User declarations
   __fastcall TInitGeoFrame( TComponent* Owner );
   TOutMsg const GetOutMsg();
   void ProcessCancel();
};
//---------------------------------------------------------------------------
extern PACKAGE TInitGeoFrame *InitGeoFrame;
//---------------------------------------------------------------------------
#endif
