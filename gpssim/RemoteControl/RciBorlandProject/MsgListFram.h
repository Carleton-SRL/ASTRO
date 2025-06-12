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
   TPanel *MsgListPanel;
   TStatusBar *MsgListsb;
   TPanel *MsgListTopPanel;
   TRzLabel *RzLabel2;
   TRzLabel *RzLabel3;
   TRzTabbedListBox *MsgListBox;
   TRzLabel *RzLabel1;
private:	// User declarations
public:		// User declarations
   __fastcall TMsgListFrame(TComponent* Owner);
   void AddMsg( const TMsgDispData &MsgDispData );

};
//---------------------------------------------------------------------------
extern PACKAGE TMsgListFrame *MsgListFrame;
//---------------------------------------------------------------------------
#endif
