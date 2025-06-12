#include "pch.h"
#pragma hdrstop

#include "QueryFram.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ovclabel"
#pragma link "RzCmboBx"
#pragma link "RzEdit"
#pragma link "RzSpnEdt"
#pragma resource "*.dfm"
TQueryFrame *QueryFrame;
//---------------------------------------------------------------------------
// static data
//
TExtQuery   TQueryFrame::DefExtQuery;

__fastcall TQueryFrame::TQueryFrame(TComponent* Owner)
   : TFrame(Owner)
{

   SetDisp( DefExtQuery );

}

//---------------------------------------------------------------------------


void
TQueryFrame::SetDisp
   (
   const TExtQuery & ExtQuery
   )
{
   if ( ExtQuery.QueryType == eQUERY_SIM_MODE )
   {
      Messagecbox->ItemIndex = 0;
   }
   else if ( ExtQuery.QueryType == eQUERY_CHAN_STAT )
   {
      Messagecbox->ItemIndex = 1;
   }
   else if ( ExtQuery.QueryType == eQUERY_BIT_RESULTS )
   {
      Messagecbox->ItemIndex = 2;
   }
   else if ( ExtQuery.QueryType == eQUERY_SYS_CFG )
   {
      Messagecbox->ItemIndex = 3;
   }

   if ( ExtQuery.QueryTransRate == eQUERY_OFF )
   {
      QueryWhencbox->ItemIndex = 0;
   }
   else if ( ExtQuery.QueryTransRate == eQUERY_ONCE )
   {
      QueryWhencbox->ItemIndex = 1;
   }
   else if ( ExtQuery.QueryTransRate == eQUERY_ON_CHANGE )
   {
      QueryWhencbox->ItemIndex = 2;
   }
   else if ( ExtQuery.QueryTransRate == eQUERY_RATE )
   {
      QueryWhencbox->ItemIndex = 3;
   }

   IntervalEdt->Visible = ( ExtQuery.QueryTransRate == eQUERY_RATE );

   IntervalEdt->Value = max( 1, ExtQuery.Interval );

}

TOutMsg const
TQueryFrame::GetOutMsg()
{
   int QueryTypes[4]      = { eQUERY_SIM_MODE, eQUERY_CHAN_STAT, eQUERY_BIT_RESULTS, eQUERY_SYS_CFG };
   int QueryTransRates[4] = { eQUERY_OFF, eQUERY_ONCE, eQUERY_ON_CHANGE, eQUERY_RATE };

   DefExtQuery.QueryType      = ( eQUERYTYPE )  QueryTypes[ Messagecbox->ItemIndex ];
   DefExtQuery.QueryTransRate = ( eQUERYTRANS ) QueryTransRates[ QueryWhencbox->ItemIndex ];
   DefExtQuery.Interval       = IntervalEdt->IntValue;

   TQueryMsg QueryMsg( DefExtQuery );

   SetDisp( DefExtQuery );

   return( QueryMsg );

}

void
TQueryFrame::ProcessCancel()
{
   SetDisp( DefExtQuery );
}


void __fastcall TQueryFrame::QueryWhencboxChange(TObject *Sender)
{
   IntervalEdt->Visible = ( QueryWhencbox->ItemIndex == 3 );
}
//---------------------------------------------------------------------------

