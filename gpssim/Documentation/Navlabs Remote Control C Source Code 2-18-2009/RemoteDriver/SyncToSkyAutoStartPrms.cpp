//---------------------------------------------------------------------------

#include "pch.h"
#pragma hdrstop


//---------------------------------------------------------------------------
//
// $Workfile:: SyncToSkyAutoStartPrms.cpp                            $
//
// $Revision:: 1                                                     $
//
// $History:: SyncToSkyAutoStartPrms.cpp                             $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 3/29/04    Time: 2:23p
//Created in $/RemoteDriver
//
//*****************  Version 2  *****************
//User: Michael Wade Date: 5/10/03    Time: 11:40p
//Updated in $/TapMsec
//Add Sync To Sky. Check in for ICSTF.
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 5/03/03    Time: 1:52p
//Created in $/TapMsec
//Sync To Sky Auto Start.
//
//
//---------------------------------------------------------------------------




#ifndef SyncToSkyAutoStartPrmsH
#include "SyncToSkyAutoStartPrms.h"
#endif

//---------------------------------------------------------------------------

#pragma package(smart_init)







//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//
//   TAutoStartStepControls
//
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

static const int          PassStepGlyphIndex        = 28;
static const int          FailStepGlyphIndex        = 48;

TAutoStartStepControls::TAutoStartStepControls
   (
   TRzStatusBar            * InStatusBar,
   TRzPanel                * InDescPnl,
   TRzGlyphStatus          * InPassFailGlyph,
   TRzGlyphStatus          * InDescLbl,
   TRzGlyphStatus          * InStatGlyph,
   TRzGlyphStatus          * InTimoutLbl,
   TRzStatusPane           * InResetLbl,
   TRzBmpButton            * InResetBtn,
   const TSyncAutoPrms     & InSyncAutoPrms
   ) :
   StatusBar_( InStatusBar ),
   DescPnl_( InDescPnl ),
   PassFailGlyph_( InPassFailGlyph ),
   DescLbl_( InDescLbl ),
   StatGlyph_( InStatGlyph ),
   TimeoutLbl_( InTimoutLbl ),
   ResetLbl_( InResetLbl ),
   ResetBtn_( InResetBtn ),
   SyncAutoPrms_( InSyncAutoPrms ),
   CurTimeIntoTimeout_( 0 ),
   TimeThatTimeoutStarted_( 0 ),
   CurTime_( 0 ),
   StepPassed_( false ),
   StepStarted_( false )
{

   InitParams();

   UpdateDisplay( 0 );

}

void
TAutoStartStepControls::InitParams
   (
   )
{

   DescLbl_->DisabledIndex       = DescLbl_->ImageIndex + 1;

   PassFailGlyph_->DisabledIndex = -1;

   StatGlyph_->DisabledIndex     = StatGlyph_->ImageIndex + 1;

   TimeoutLbl_->DisabledIndex    = TimeoutLbl_->ImageIndex + 1;

}

void
TAutoStartStepControls::InitDisplay
   (
   )
{

   StatGlyph_->Enabled       = SyncAutoPrms_.StepEnabled;

   PassFailGlyph_->Enabled   = SyncAutoPrms_.StepEnabled;

   DescLbl_->Enabled         = SyncAutoPrms_.StepEnabled;

   TimeoutLbl_->Enabled      = SyncAutoPrms_.StepEnabled;

   ResetLbl_->Enabled        = SyncAutoPrms_.StepEnabled;

   StatusBar_->Height        = 40;

}

void
TAutoStartStepControls::UpdateDisplay
   (
   const int                 Time
   )
{

   UpdateConditions( Time );

   if ( SyncAutoPrms_.StepEnabled )
   {

      if ( StepPassed )
      {

         UpdateDisplayStepPassed( Time );

      }
      else
      {

         if ( SyncAutoPrms_.StepTimeoutEnabled )
         {

            UpdateTimeoutDisplay( Time );

         }

      }

   }

}

void
TAutoStartStepControls::UpdateDisplayStepPassed
   (
   const int                 Time
   )
{

   PassFailGlyph_->ImageIndex    = PassGlyphIndex_;

   UpdateTimeoutDisplay( Time );

}

void
TAutoStartStepControls::UpdateTimeoutDisplay
   (
   const int                 Time
   )
{


   if ( !StepPassed && SyncAutoPrms_.StepTimeoutEnabled )
   {

      TimeoutLbl_->Enabled = true;

      if ( !TimeoutExceeded )
      {

         AnsiString TimeoutStr;
         TimeoutStr.sprintf( "Timeout and Abort in: %d (s) ", TimeoutRemaining );

         TimeoutLbl_->Caption = TimeoutStr;

         ResetLbl_->Enabled      = SyncAutoPrms_.StepTimeoutResetEnabled;
         ResetBtn_->Enabled      = SyncAutoPrms_.StepTimeoutResetEnabled;

      }
      else
      {

         TimeoutLbl_->Caption = AnsiString( " Step Timeout! " );

         ResetLbl_->Enabled      = SyncAutoPrms_.StepTimeoutResetEnabled;
         ResetBtn_->Enabled      = SyncAutoPrms_.StepTimeoutResetEnabled;

      }


   }
   else
   {

      TimeoutLbl_->Enabled    = false;
      TimeoutLbl_->Caption    = AnsiString( " (N/A) " );

      ResetLbl_->Enabled      = false;
      ResetBtn_->Enabled      = false;

   }


}

void
TAutoStartStepControls::UpdateConditions
   (
   const int                 Time
   )
{

   CurTime_                = Time;


}

int const
TAutoStartStepControls::GetTimeoutRemaining
   (
   ) const
{

   const int iTimeoutRemaining = TimeoutMax_ - ( CurTime_ - TimeThatTimeoutStarted_ );

   return( iTimeoutRemaining );

}


bool const
TAutoStartStepControls::GetStepPassed
   (
   ) const
{
   return( StepPassed_ );
}

void
TAutoStartStepControls::SetStepPassed
   (
   const bool                InPassed
   )
{
   StepPassed_             = InPassed;
}

bool const
TAutoStartStepControls::GetStepEnabled
   (
   ) const
{
   return( SyncAutoPrms_.StepEnabled );
}

void
TAutoStartStepControls::SetStepEnabled
   (
   const bool                InEnabled
   )
{
   SyncAutoPrms_.StepEnabled           = InEnabled;
}   

bool const
TAutoStartStepControls::GetStepStarted
   (
   ) const
{
   return( StepStarted_ );
}

void
TAutoStartStepControls::SetStepStarted
   (
   const bool                InStarted
   )
{
   StepStarted_            = InStarted;
}


