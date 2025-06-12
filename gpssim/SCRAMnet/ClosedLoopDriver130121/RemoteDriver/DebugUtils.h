//---------------------------------------------------------------------------

#ifndef DebugUtilsH
#define DebugUtilsH
//---------------------------------------------------------------------------

// This is only for debug.  The namespace DebugUtils contains classes, global data
// static data used for debugging only
//
namespace DebugUtils {

class TTimeInterval {
private:

   LARGE_INTEGER             StartCount_;
   double                    Frequency_;

   void                      Init();
   double const              GetTimeInterval() const;
   double const              GetTimeIntervalms() const;

public:
   TTimeInterval();

   void                      ResetStart();
   void                      Reportms( const AnsiString & CodeSiteLineId )
   {
      CodeSite->WriteFloat( CodeSiteLineId, TimeIntervalms );
   }
   void                      Report( const AnsiString & CodeSiteLineId )
   {
      CodeSite->WriteFloat( CodeSiteLineId, TimeInterval );
   }


   __property double TimeInterval   = { read = GetTimeInterval              };
   __property double TimeIntervalms = { read = GetTimeIntervalms            };
   __property double Frequency      = { read = Frequency_                   };

};

class TSequence {
private:

   AnsiString                IdentStr_;
   int                       SequenceNumber_;

public:

   TSequence( const AnsiString & InIdentStr ) : SequenceNumber_( -1 ), IdentStr_( InIdentStr ) {}

   void Report
      (
      const AnsiString     & Str
      )
   {
      CodeSite->SendMsg( AnsiString( ++SequenceNumber_ ) + AnsiString( " : " ) + IdentStr_ + Str );
   }

};   

}; // End namespace


#endif
