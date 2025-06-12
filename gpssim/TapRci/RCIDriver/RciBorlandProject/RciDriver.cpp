#include "pch.h"
#pragma hdrstop
USERES("RciDriver.res");
USEFORM("RciDriverFrm.cpp", RciDriverForm);
USEFORM("GpibIntOptionsFram.cpp", GpibIntOptionsFrame); /* TFrame: File Type */
USEOBJ("BorlandC_gpib-32.obj");
USEFORM("RciRunFrm.cpp", RciRunForm);
USEFORM("MsgListFram.cpp", MsgListFrame); /* TFrame: File Type */
USEFORM("StartScenFram.cpp", StartScenFrame); /* TFrame: File Type */
USEUNIT("RciDriverMsgs.cpp");
USEUNIT("OutMsg.cpp");
USEFORM("InitGeoFram.cpp", InitGeoFrame); /* TFrame: File Type */
USEFORM("StartLocalFram.cpp", StartLocalFrame); /* TFrame: File Type */
USEFORM("SetSvidFram.cpp", SetSvidFrame); /* TFrame: File Type */
USEFORM("SetPowerFram.cpp", SetPowerFrame); /* TFrame: File Type */
USEFORM("ShutdownFram.cpp", ShutdownFrame); /* TFrame: File Type */
USEFORM("QueryFram.cpp", QueryFrame); /* TFrame: File Type */
USEFORM("StopFram.cpp", StopFrame); /* TFrame: File Type */
USEUNIT("Interface.cpp");
USEUNIT("Gpib.cpp");
USEUNIT("InMsg.cpp");
USEUNIT("Schedule.cpp");
USEUNIT("Utilities.cpp");
USEFORM("EXPANDABLEDLG.cpp", ExpandableDialog);
USEFORM("AboutDlg.cpp", AboutDialog);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
       Application->Initialize();
       Application->CreateForm(__classid(TRciDriverForm), &RciDriverForm);
       Application->CreateForm(__classid(TRciRunForm), &RciRunForm);
       Application->CreateForm(__classid(TAboutDialog), &AboutDialog);
       Application->Run();
   }
   catch (Exception &exception)
   {
       Application->ShowException(&exception);
   }
   return 0;
}
//---------------------------------------------------------------------------
