//---------------------------------------------------------------------------

#ifndef SendSetChanPowerFrmH
#define SendSetChanPowerFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzBckgnd.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSendSetChanPowerForm : public TForm
{
__published:	// IDE-managed Components
   TRzPanel *TopPnl;
   TRzSeparator *TopSep;
   TRzPanel *MainPnl;
private:	// User declarations
public:		// User declarations
   __fastcall TSendSetChanPowerForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSendSetChanPowerForm *SendSetChanPowerForm;
//---------------------------------------------------------------------------
#endif
