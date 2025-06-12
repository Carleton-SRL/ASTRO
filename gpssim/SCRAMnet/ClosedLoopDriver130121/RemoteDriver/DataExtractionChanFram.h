//---------------------------------------------------------------------------


#ifndef DataExtractionChanFramH
#define DataExtractionChanFramH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// $Workfile::                                                       $
//
// $Revision::                                                       $
//
// $History::                                                        $
//
//
//---------------------------------------------------------------------------



//------------------------------------------------------------------------------
#ifndef BUILDERINCLUDES
//------------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ovclabel.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
//---------------------------------------------------------------------------
class TDataExtractionChanFrame : public TFrame
{
__published:	// IDE-managed Components
   TRzPanel *DataChanPnl;
   TOvcLabel *ChanLbl;
   TOvcLabel *SvidLbl;
   TOvcLabel *RangeLbl;
private:

   const int                 ChanNum;
   int                       Svid;
   double                    Range;

public:
   __fastcall TDataExtractionChanFrame( TComponent* Owner, const int InChanNum );

   void                      SetData( const int InSvid, const double InRange );

};
//---------------------------------------------------------------------------
extern PACKAGE TDataExtractionChanFrame *DataExtractionChanFrame;
//---------------------------------------------------------------------------
#endif
