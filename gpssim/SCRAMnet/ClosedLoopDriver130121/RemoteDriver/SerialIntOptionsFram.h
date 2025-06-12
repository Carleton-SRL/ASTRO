//---------------------------------------------------------------------------


#ifndef SerialIntOptionsFramH
#define SerialIntOptionsFramH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// $Workfile:: SerialIntOptionsFram.h                                $
//
// $Revision:: 1                                                     $
//
// $History:: SerialIntOptionsFram.h                                 $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 10/09/02   Time: 4:27p
//Created in $/RemoteDriver
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 10/03/02   Time: 10:11p
//Created in $/RciDriver
//Add ethernet
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 9/30/02    Time: 4:56p
//Created in $/TapRci
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
#include "RzEdit.hpp"
#include "RzSpnEdt.hpp"
#include <Mask.hpp>
#include <Graphics.hpp>
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------

#ifndef RemoteDriverPfH
#include "RemoteDriverPf.h"
#endif

#ifndef AcceptInterfaceOptionsH
#include "AcceptInterfaceOptions.h"
#endif


//---------------------------------------------------------------------------
class TSerialIntOptionsFrame : public TFrame, public IAcceptInterfaceOptions
{
__published:
   TRzPanel *SerialTopPnl;
   TOvcLabel *SerialTitle;
   TRzPanel *SerialMainPnl;
   TOvcLabel *SerialPortDescLbl;
   TRzSpinEdit *SerialPortSpinEdit;
   TOvcLabel *SerialStopBitsDescLbl;
   TRzSpinEdit *SerialStopBitsSpinEdit;
   TOvcLabel *SerialBaudDescLbl;
   TComboBox *SerialBaudcbox;
   TImage *Image1;
private:

   TRemoteDriverPf         * RemoteDriverPf;

   void                      SetDisplayFromProfile();
   void                      SetProfileFromDisplay();


public:

   __fastcall                TSerialIntOptionsFrame( TComponent* Owner );
   virtual __fastcall       ~TSerialIntOptionsFrame();

   void                      DoNewOptions( const bool Accept );
   bool const                GetOptionsChanged();

};
//---------------------------------------------------------------------------
extern PACKAGE TSerialIntOptionsFrame *SerialIntOptionsFrame;
//---------------------------------------------------------------------------
#endif
