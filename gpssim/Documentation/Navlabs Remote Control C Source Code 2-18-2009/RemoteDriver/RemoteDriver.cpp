#include "pch.h"
#pragma hdrstop

//---------------------------------------------------------------------------
//
// $Workfile::                                                       $
//
// $Revision::                                                       $
//
// $History::                                                        $
//
//
//---------------------------------------------------------------------------



USEFORM("RemoteMainFrm.cpp", RemoteMainForm);
USEFORM("EtherFram.cpp", EtherFrame); /* TFrame: File Type */
USEFORM("NavStateFram.cpp", NavStateFrame); /* TFrame: File Type */
USEFORM("GpibIntOptionsFram.cpp", GpibIntOptionsFrame); /* TFrame: File Type */
USEFORM("ClosedLoopRunFrm.cpp", ClosedLoopRunForm);
USEFORM("MsgListFram.cpp", MsgListFrame); /* TFrame: File Type */
USEFORM("EXPANDABLEDLG.cpp", ExpandableDialog);
USEFORM("AboutDlg.cpp", AboutDialog);
USEFORM("DataExtractionChanFram.cpp", DataExtractionChanFrame); /* TFrame: File Type */
USEFORM("EthernetIntOptionsFram.cpp", EthernetIntOptionsFrame); /* TFrame: File Type */
USEFORM("DataExtractionReqFrm.cpp", DataExtractionReqForm);
USEFORM("InterfaceAcceptFram.cpp", InterfaceAcceptFrame); /* TFrame: File Type */
USEFORM("SerialIntOptionsFram.cpp", SerialIntOptionsFrame); /* TFrame: File Type */
USEFORM("OperationErrorFrm.cpp", OperationErrorForm);
USEFORM("ChanAssignFrm.cpp", ChanAssignForm);
USEFORM("SendMsgsFrm.cpp", SendMsgsForm);
USEFORM("SendSetChanPowerFrm.cpp", SendSetChanPowerForm);
USEFORM("RtMotionMemFrm.cpp", RtMotionMemForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
       Application->Initialize();
       Application->Title = "TapRealTimeControl";
       Application->CreateForm(__classid(TRemoteMainForm), &RemoteMainForm);
       Application->CreateForm(__classid(TOperationErrorForm), &OperationErrorForm);
       Application->CreateForm(__classid(TChanAssignForm), &ChanAssignForm);
       Application->CreateForm(__classid(TSendSetChanPowerForm), &SendSetChanPowerForm);
       Application->CreateForm(__classid(TRtMotionMemForm), &RtMotionMemForm);
       Application->Run();
   }
   catch (Exception &exception)
   {
       Application->ShowException(&exception);
   }
   return 0;
}
//---------------------------------------------------------------------------
