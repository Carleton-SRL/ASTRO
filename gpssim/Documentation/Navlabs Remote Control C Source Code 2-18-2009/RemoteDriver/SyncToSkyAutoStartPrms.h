//---------------------------------------------------------------------------

#ifndef SyncToSkyAutoStartPrmsH
#define SyncToSkyAutoStartPrmsH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// $Workfile:: SyncToSkyAutoStartPrms.h                              $
//
// $Revision:: 1                                                     $
//
// $History:: SyncToSkyAutoStartPrms.h                               $
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

class TSyncToSkyAutoStartStepPrms {
private:

   bool                      StepEnabled_;
   bool                      StepTimeoutEnabled_;
   bool                      StepTimeoutResetEnabled_;
   int                       StepTimeout_;

public:

   TSyncToSkyAutoStartStepPrms::TSyncToSkyAutoStartStepPrms
      (
      ) :
      StepEnabled_( false ), StepTimeoutEnabled_( false ), StepTimeoutResetEnabled_( false ), StepTimeout_( 100 )
   {}

   TSyncToSkyAutoStartStepPrms( const TSyncToSkyAutoStartStepPrms & Source )
   {
      ( *this ) = Source;
   }

   TSyncToSkyAutoStartStepPrms & operator=( const TSyncToSkyAutoStartStepPrms & Source )
   {
      if ( this == &Source ) return( *this );

      StepEnabled_              = Source.StepEnabled_;
      StepTimeoutEnabled_       = Source.StepTimeoutEnabled_;
      StepTimeoutResetEnabled_  = Source.StepTimeoutResetEnabled_;
      StepTimeout_              = Source.StepTimeout_;

      return( *this );

   }

   __property bool                      StepEnabled                  = { read = StepEnabled_,                write = StepEnabled_                    };
   __property bool                      StepTimeoutEnabled           = { read = StepTimeoutEnabled_,         write = StepTimeoutEnabled_             };
   __property bool                      StepTimeoutResetEnabled      = { read = StepTimeoutResetEnabled_,    write = StepTimeoutResetEnabled_        };
   __property int                       StepTimeout                  = { read = StepTimeout_,                write = StepTimeout_                    };

};

typedef TSyncToSkyAutoStartStepPrms TSyncAutoPrms;


//---------------------------------------------------------------------------



class TAutoStartStepControls {
private:

   TRzStatusBar            * StatusBar_;
   TRzPanel                * DescPnl_;
   TRzGlyphStatus          * PassFailGlyph_;
   TRzGlyphStatus          * DescLbl_;
   TRzGlyphStatus          * StatGlyph_;

   TRzGlyphStatus          * TimeoutLbl_;
   TRzStatusPane           * ResetLbl_;
   TRzBmpButton            * ResetBtn_;

   TSyncAutoPrms             SyncAutoPrms_;

   int                       PassGlyphIndex_;
   int                       FailGlyphIndex_;
   int                       StepStatPassIndex_;
   int                       StepStatFailIndex_;
   int                       StepDescLblEnabledIndex_;

   int                       CurTime_;
   int                       TimeoutMax_;
   int                       CurTimeIntoTimeout_;
   int                       TimeThatTimeoutStarted_;
   bool                      StepPassed_;
   bool                      StepStarted_;

   void                      InitDisplay();
   void                      UpdateDisplay( const int Time );
   void                      UpdateConditions( const int Time );
   void                      UpdateDisplayStepPassed( const int Time );
   void                      UpdateTimeoutDisplay( const int Time );

   void                      InitParams();


   void                      TimeoutResetClicked();

   bool const                GetTimeoutExceeded();
   void                      SetTimeoutExceeded( const bool InTimeoutExceeded );

   bool const                GetStepPassed() const;
   void                      SetStepPassed( const bool InPassed );

   bool const                GetStepEnabled() const;
   void                      SetStepEnabled( const bool InEnabled );

   bool const                GetStepStarted() const;
   void                      SetStepStarted( const bool InStarted );

   int const                 GetTimeoutRemaining() const;
public:

   TAutoStartStepControls
      (
      TRzStatusBar            * InStatusBar                    = NULL,
      TRzPanel                * InDescPnl                      = NULL,
      TRzGlyphStatus          * InPassFailGlyph                = NULL,
      TRzGlyphStatus          * InDescLbl                      = NULL,
      TRzGlyphStatus          * InStatGlyph                    = NULL,
      TRzGlyphStatus          * InTimoutLb                     = NULL,
      TRzStatusPane           * InResetLb                      = NULL,
      TRzBmpButton            * InResetBt                      = NULL,
      const TSyncAutoPrms     & InSyncAutoPrms                 = TSyncAutoPrms()
      );

   void                      Update( const int Time );


   __property int            TimeoutRemaining         = { read = GetTimeoutRemaining                               };
   __property bool           TimeoutExceeded          = { read = GetTimeoutExceeded,    write = SetTimeoutExceeded };
   __property bool           StepPassed               = { read = GetStepPassed,         write = SetStepPassed      };
   __property bool           StepStarted              = { read = GetStepStarted,        write = SetStepStarted     };
   __property TSyncAutoPrms  SyncAutoPrms             = { read = SyncAutoPrms_,         write = SyncAutoPrms_      };

};
#if(0)
typedef std::set

class TAutoStartStepReady {
private:

   TIntArr                   PrevRqrdSteps_;

public:

   __property bool PrevRqrdStepsDone              = { read = GetPrevRqrdStepsDone,   write = SetPrevRqrdStepsDone    };

};
#endif
//---------------------------------------------------------------------------
#endif
