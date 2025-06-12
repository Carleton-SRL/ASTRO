//---------------------------------------------------------------------------

#ifndef AboutDlgH
#define AboutDlgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "EXPANDABLEDLG.h"
#include <ExtCtrls.hpp>
#include "RzAnimtr.hpp"
#include "RzLabel.hpp"
#include "StVInfo.hpp"
#include <ImgList.hpp>
#include "StBase.hpp"
//---------------------------------------------------------------------------
class TAboutDialog : public TExpandableDialog
{
__published:	// IDE-managed Components
   TRzAnimator *RzAnimator1;
   TImageList *LogoAnim;
   TRzLabel *FileNameLbl;
   TRzLabel *DateLbl;
   TRzLabel *VersionLbl;
   TRzLabel *RzLabel1;
   TRzLabel *RzLabel2;
   TRzLabel *DateLabel;
   TStVersionInfo *CurVersionInfo;
private:	// User declarations
public:		// User declarations
   __fastcall TAboutDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutDialog *AboutDialog;
//---------------------------------------------------------------------------
#endif
