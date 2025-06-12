//---------------------------------------------------------------------------

#ifndef ERemoteDriverExceptionH
#define ERemoteDriverExceptionH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// $Workfile:: ERemoteDriverException.h                                   $
//
// $Revision:: 1                                                     $
//
// $History:: ERemoteDriverException.h                                    $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 10/19/02   Time: 9:26p
//Created in $/RemoteDriver
//
//
//---------------------------------------------------------------------------

class ERemoteDriverException : public Exception {
private:

   bool                      ShowErrorForm_;
   AnsiString                ExcStr_;

   static bool               ErrorFormShown_;

   void                      DisplayErrorForm();

public:

   ERemoteDriverException
      (
      const AnsiString     & InExcStr,
      const bool             InShowErrorForm = true
      );
   virtual __fastcall ~ERemoteDriverException();

   __property AnsiString ExcStr    = { read = ExcStr_            };

};

#endif
 