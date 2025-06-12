#include "pch.h"
#pragma hdrstop

#include "AboutDlg.h"
#include "StStrL.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "EXPANDABLEDLG"
#pragma link "RzAnimtr"
#pragma link "RzLabel"
#pragma link "StBase"
#pragma link "StVInfo"
#pragma link "StBase"
#pragma resource "*.dfm"
TAboutDialog *AboutDialog;
//---------------------------------------------------------------------------
__fastcall TAboutDialog::TAboutDialog(TComponent* Owner)
   : TExpandableDialog(Owner)
{

   CurVersionInfo->FileName = Application->ExeName;

   FileNameLbl->Caption     = Application->ExeName;

   VersionLbl->Caption = CurVersionInfo->FileVersion;

   Caption = AnsiString( "About " ) + JustNameL( ParamStr(0) );

   WIN32_FIND_DATA FindFileData;
   HANDLE FHandle = FindFirstFile(ParamStr(0).c_str(),&FindFileData);

   if ( FHandle != INVALID_HANDLE_VALUE )
   {

      FILETIME LocalFileTime;
      SYSTEMTIME SystemTime;
      FileTimeToLocalFileTime(&FindFileData.ftLastWriteTime,&LocalFileTime);
      FileTimeToSystemTime(&LocalFileTime,&SystemTime);

      TDateTime FileDate = SystemTimeToDateTime(SystemTime);
      DateLbl->Caption   = FileDate.DateString();

   } else
   {

      DateLbl->Visible   = false;
      DateLabel->Visible = false;

   }

}
//---------------------------------------------------------------------------
