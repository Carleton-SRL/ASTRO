//---------------------------------------------------------------------------

#ifndef ExpandableDlgH
#define ExpandableDlgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TExpandableDialog : public TForm
{
__published:	// IDE-managed Components
   TPanel *TopPanel;
   TPanel *BottomPanel;
   TButton *OKBtn;
   TButton *DetailsBtn;
   TPanel *LeftPanel;
   TPanel *RightPanel;
   void __fastcall DetailsBtnClick(TObject *Sender);
private:	// User declarations
   void __fastcall SetExpanded( bool expand );
   bool expanded;
   int TopPanelWidth;
   int DoorPanelWidth;
   int BottomPanelHeight;
public:		// User declarations
   __fastcall TExpandableDialog(TComponent* Owner);
   __property bool Expanded = { read = expanded, write = SetExpanded };


};
//---------------------------------------------------------------------------
extern PACKAGE TExpandableDialog *ExpandableDialog;
//---------------------------------------------------------------------------
#endif
