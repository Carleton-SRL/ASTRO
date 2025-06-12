//---------------------------------------------------------------------------

#ifndef ChanAssignFrmH
#define ChanAssignFrmH

//---------------------------------------------------------------------------
//
// $Workfile:: ChanAssignFrm.h                                       $
//
// $Revision:: 1                                                     $
//
// $History:: ChanAssignFrm.h                                        $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 11/16/02   Time: 9:31p
//Created in $/RemoteDriver
//
//
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef BUILDERINCLUDES
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ovclabel.hpp"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzRadGrp.hpp"
#include "RzSpnEdt.hpp"
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------


#ifndef StelMsgsH
#include "StelMsgs.h"
#endif

#ifndef InterfaceH
#include "Interface.h"
#endif


//---------------------------------------------------------------------------

class TChanAssignForm : public TForm
{
__published:
   TRzPanel *TopPnl;
   TOvcLabel *TitleLbl;
   TRzPanel *BottomPnl;
   TRzBitBtn *SendBtn;
   TRzBitBtn *CancelBtn;
   TRzPanel *MainPnl;
   TRzRadioGroup *ChanAssignFunctionrg;
   TOvcLabel *ChanALbl;
   TOvcLabel *Param3Lbl;
   TRzSpinner *ChanASpinner;
   TRzSpinner *Param3Spinner;
   TImage *Image1;
   void __fastcall ChanAssignFunctionrgClick(TObject *Sender);
   void __fastcall SendBtnClick(TObject *Sender);
   void __fastcall CancelBtnClick(TObject *Sender);
private:

   TInterface              * Interface_;

   void                      SetParam3( const TStelChanAssignFunc & InStelChanAssignFunc );

   TStelChanAssignFunc const GetChanAssignFunc() const;
   void                      SetChanAssignFunc( const TStelChanAssignFunc InChanAssignFunc );

   int const                 GetChanA() const;
   void                      SetChanA( const int InChanA );

   int const                 GetChanB() const;
   void                      SetChanB( const int InChanB );

   int const                 GetSvid() const;
   void                      SetSvid( const int InSvid );

   TStelChanAssignData const GetChanAssignData() const;
   void                      SetChanAssignData( const TStelChanAssignData & InStelChanAssignData );

   TStelOut                  GetOutMsg();

public:
   __fastcall TChanAssignForm( TComponent* Owner, TInterface * InInterface);

   __property TStelChanAssignFunc ChanAssignFunc    = { read = GetChanAssignFunc,     write = SetChanAssignFunc    };
   __property TStelChanAssignData ChanAssignData    = { read = GetChanAssignData,     write = SetChanAssignData    };
   __property int                 ChanA             = { read = GetChanA,              write = SetChanA             };
   __property int                 ChanB             = { read = GetChanB,              write = SetChanB             };
   __property int                 Svid              = { read = GetSvid,               write = SetSvid              };
   __property TStelOut            OutMsg            = { read = GetOutMsg                                           };

};
//---------------------------------------------------------------------------
extern PACKAGE TChanAssignForm *ChanAssignForm;
//---------------------------------------------------------------------------
#endif
