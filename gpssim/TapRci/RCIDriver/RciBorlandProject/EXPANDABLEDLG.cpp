#include "pch.h"
#pragma hdrstop

#include "ExpandableDlg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

static const int DLG_WIDTH_EDGE  = 8;
static const int DLG_HEIGHT_EDGE = 34;

TExpandableDialog *ExpandableDialog;
//---------------------------------------------------------------------------
__fastcall TExpandableDialog::TExpandableDialog(TComponent* Owner)
   : TForm(Owner)
{
   TopPanelWidth  = Width - DLG_WIDTH_EDGE;
   DoorPanelWidth = TopPanelWidth/2 + 1;

   BottomPanelHeight = ( Height - DLG_HEIGHT_EDGE ) - TopPanel->Height;

   expanded = true;
   Expanded = false;
}

//---------------------------------------------------------------------------
void __fastcall TExpandableDialog::DetailsBtnClick(TObject *Sender)
{

   Expanded = !Expanded;

}

void __fastcall
TExpandableDialog::SetExpanded
   (
   bool expand
   )
{

   if ( expanded == expand ) return;

   if ( expanded )
   {

      for ( int i = 1; i <= DoorPanelWidth; ++i )
      {

         RightPanel->Width = i;
         LeftPanel->Width  = i;
         Application->ProcessMessages();

      }

      for ( int i = BottomPanelHeight; i >= 0; --i )
      {

         BottomPanel->Height = i;
         Application->ProcessMessages();

      }
      AutoSize = false;
      AutoSize = true;
   }
   else
   {

      for ( int i = 1; i <= BottomPanelHeight; ++i )
      {

         BottomPanel->Height = i;
         Application->ProcessMessages();

      }

      for ( int i = DoorPanelWidth; i>= 0; --i )
      {

         RightPanel->Width = i;
         LeftPanel->Width  = i;
         Application->ProcessMessages();

      }

   }
   expanded = expand;
//   BottomPanel->Visible = expanded;
   DetailsBtn->Caption = Expanded ? "&Details <<" : "&Details >>";

//   AutoSize = true;

}

//---------------------------------------------------------------------------
