//---------------------------------------------------------------------------


#ifndef InterfaceAcceptFramH
#define InterfaceAcceptFramH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// $Workfile:: InterfaceAcceptFram.h                                 $
//
// $Revision:: 1                                                     $
//
// $History:: InterfaceAcceptFram.h                                  $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 10/03/02   Time: 9:14p
//Created in $/RciDriver
//Add ethernet and Monte Carlo trials
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 9/29/02    Time: 6:54p
//Created in $/TapRci
//Initial check in
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
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "ovclabel.hpp"
#include "RzButton.hpp"
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------

#ifndef AcceptInterfaceOptionsH
#include "AcceptInterfaceOptions.h"
#endif


//---------------------------------------------------------------------------
class TInterfaceAcceptFrame : public TFrame
{
__published:
   TRzPanel *InterfaceAcceptPnl;
   TOvcLabel *AcceptLbl;
   TRzBitBtn *AcceptInterfaceBtn;
   TRzBitBtn *CancelInterfaceBtn;
   TTimer *InterfaceAcceptOptionsTimer;
   void __fastcall AcceptInterfaceBtnClick(TObject *Sender);
   void __fastcall CancelInterfaceBtnClick(TObject *Sender);
   void __fastcall InterfaceAcceptOptionsTimerTimer(TObject *Sender);
private:

   IAcceptInterfaceOptions * AcceptInterfaceOptions_;

   IAcceptInterfaceOptions * GetAcceptInterfaceOptions() { return( AcceptInterfaceOptions_ ); }
   void                      SetAcceptInterfaceOptions( IAcceptInterfaceOptions * InAcceptInterfaceOptions )
   {
      AcceptInterfaceOptions_              = InAcceptInterfaceOptions;
      InterfaceAcceptOptionsTimer->Enabled = ( AcceptInterfaceOptions_ != NULL );
   }

public:

   __fastcall TInterfaceAcceptFrame( TComponent * Owner );

   __property IAcceptInterfaceOptions * AcceptInterfaceOptions = { read = GetAcceptInterfaceOptions, write = SetAcceptInterfaceOptions };

};
//---------------------------------------------------------------------------
extern PACKAGE TInterfaceAcceptFrame *InterfaceAcceptFrame;
//---------------------------------------------------------------------------
#endif
