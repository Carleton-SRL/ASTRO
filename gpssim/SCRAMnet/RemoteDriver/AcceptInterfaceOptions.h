#ifndef AcceptInterfaceOptionsH
#define AcceptInterfaceOptionsH

//---------------------------------------------------------------------------
//
// $Workfile:: AcceptInterfaceOptions.h                              $
//
// $Revision:: 1                                                     $
//
// $History:: AcceptInterfaceOptions.h                               $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 9/29/02    Time: 9:34p
//Created in $/TapRci
//Initial check in
//
//
//---------------------------------------------------------------------------


__interface IAcceptInterfaceOptions {

public:

   virtual void              DoNewOptions( const bool Accept )             = 0;
   virtual bool const        GetOptionsChanged()                           = 0;

   __property bool           OptionsChanged    = { read = GetOptionsChanged         };

};


#endif
