//---------------------------------------------------------------------------


#ifndef MsgListFramH
#define MsgListFramH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzLabel.hpp"
#include "RzLstBox.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

#include "RemoteTypes.h"
#include "RzPanel.hpp"

class TMsgDispData {
public:
   double UserTime;
   TMsgData MsgData;
public:
   TMsgDispData() : UserTime(0.0) {}
   TMsgDispData(const double &InUserTime, const TMsgData &InMsgData) :
      UserTime( InUserTime ), MsgData( InMsgData ) {}
};          

//---------------------------------------------------------------------------
class TMsgListFrame : public TFrame
{
__published:	// IDE-managed Components
   TRzPanel *TopPnl;
   TRzLabel *RzLabel2;
   TRzLabel *RzLabel3;
   TRzLabel *RzLabel1;
   TRzTabbedListBox *MsgListBox;
   TStatusBar *MsgListsb;
private:	// User declarations
public:		// User declarations
   __fastcall TMsgListFrame(TComponent* Owner);
   void AddMsg( const TMsgDispData &MsgDispData );

};
//---------------------------------------------------------------------------
extern PACKAGE TMsgListFrame *MsgListFrame;
//---------------------------------------------------------------------------
#endif
