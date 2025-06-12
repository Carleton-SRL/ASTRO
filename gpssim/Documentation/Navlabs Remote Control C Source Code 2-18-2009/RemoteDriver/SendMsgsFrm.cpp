#include "pch.h"
#pragma hdrstop

#ifndef SendMsgsFrmH
#include "SendMsgsFrm.h"
#endif

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ovclabel"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzLabel"
#pragma link "dxNavBar"
#pragma link "dxNavBarBase"
#pragma link "dxNavBarCollns"
#pragma link "dxNavBarStyles"
#pragma link "RzSplit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
// Message Descriptions
//
#if(0)
static const int RemoteModeValidity[MAX_REMOTE_MSGS] =
{
   eIdle,                               // 0 - Set Time
   eIdle,                               // 1 - Initialize Simulation
   eIdle | eTest | eTraj | eUmg,        // 2 - ChannelMode
   eIdle,                               // 3 - Calibrate Interchannel Biases
   0,                                   // 4 - (Unused)
   eIdle | eTest | eTraj | eUmg,        // 5 - Set Channel Power
   eIdle | eTest,                       // 6 - Range Maintenance
   eIdle | eTest | eTraj | eUmg,        // 7 - Ephemeris Data Input
   eIdle,                               // 8 - Almanac Parameters Input
   0,                                   // 9 - (Unused)
   eIdle | eTest | eTraj | eUmg,        // 10 - Power Profile
                   eTraj       ,        // 11 - Trajactory Profile
   0,                                   // 12 - (Unused)
   eIdle | eTest | eTraj | eUmg,        // 13 - Status Request
   0,                                   // 14 - (Unused)
   0,                                   // 15 - (Unused)
   eIdle | eTest | eTraj | eUmg,        // 16 - Time Request
   eIdle | eTest | eTraj | eUmg,        // 17 - Ephemeris Data Request
   0,                                   // 18 - (Unused)
   eIdle | eTest | eTraj | eUmg,        // 19 - Data Extraction Request
   eIdle |         eTraj | eUmg,        // 20 - Almanac Parameters Request
   eIdle,                               // 21 - Calibrate Parameters Input
           eTest | eTraj | eUmg,        // 22 - Stop Simulation
   eIdle |         eTraj | eUmg,        // 23 - Ephemeris Corruption Input
   eIdle,                               // 24 - Clock Corruption Input
   eIdle,                               // 25 - Pseudorange Noise Parameters
   eIdle,                               // 26 - Tropospheric Model Parameters
   eIdle,                               // 27 - UMG Simulation Start
                   eTraj       ,        // 28 - Platform Attitude
   0,                                   // 29 - (Unused)
   eIdle,                               // 30 - Antenna Gain Pattern
   eIdle,                               // 31 - Aircraft Masking Table
   0,                                   // 32 - (Unused)
   0,                                   // 33 - (Unused)
   0,                                   // 34 - (Unused)
   0,                                   // 35 - (Unused)
   0,                                   // 36 - (Unused)
   0,                                   // 37 - (Unused)
   0,                                   // 38 - (Unused)
   0,                                   // 39 - (Unused)
   0,                                   // 40 - (Unused)
   eIdle,                               // 41 - Initialize System
   eIdle,                               // 42 - Reset Channel Interface
   eIdle,                               // 43 - Calibrate Channel Controllers
   eIdle | eTest | eTraj | eUmg,        // 44 - Phase Lock Status Request
   0,                                   // 45 - (Unused)
   eIdle | eTest | eTraj | eUmg,        // 46 - Calibration Parameters Request
   eIdle | eTest | eTraj | eUmg,        // 47 - Satellite Use Map
   eIdle,                               // 48 - Full Initialization
   eIdle | eTest | eTraj | eUmg,        // 49 - Subframe Modifcation
   eIdle,                               // 50 - Set Week Number
   eIdle | eTest | eTraj | eUmg,        // 51 - Channel Assignment
};

static const char *RemoteMsgDesc[MAX_REMOTE_MSGS] =
{
   "Set Time"
   "Initialize Simulation",
   "ChannelMode",
   "Calibrate Interchannel Biases",
   "",
   "Set Channel Power",
   "Range Maintenance",
   "Ephemeris Data Input",
   "Almanac Parameters Input",
   "",
   "Power Profile",
   "Trajactory Profile",
   ""
   "Status Request",
   "",
   "",
   "Time Request",
   "Ephemeris Data Request",
   "",
   "Data Extraction Request",
   "Almanac Parameters Request",
   "Calibrate Parameters Input",
   "Stop Simulation",
   "Ephemeris Corruption Input",
   "Clock Corruption Input",
   "Pseudorange Noise Parameters",
   "Tropospheric Model Parameters",
   "UMG Simulation Start",
   "Platform Attitude",
   "",
   "Antenna Gain Pattern",
   "Aircraft Masking Table",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "Initialize System",
   "Reset Channel Interface",
   "Calibrate Channel Controllers",
   "Phase Lock Status Request",
   "",
   "Calibration Parameters Request",
   "Satellite Use Map",
   "Full Initialization",
   "Subframe Modifcation",
   "Set Week Number",
   "Channel Assignment"
};
//---------------------------------------------------------------------------
#endif


TSendMsgsForm *SendMsgsForm;
//---------------------------------------------------------------------------
__fastcall
TSendMsgsForm::TSendMsgsForm
   (
   TComponent              * Owner,
   TInterface              * InInterface
   ) :
   TForm( Owner ),
   Interface_( InInterface )
{

   ChanAssignForm = new TChanAssignForm( this, Interface_ );

}

void __fastcall
TSendMsgsForm::ChanAssignBtnClick
   (
   TObject                 * Sender
   )
{

   ChanAssignForm->Visible = true;

}

void __fastcall
TSendMsgsForm::ChannelModeBtnClick
   (
   TObject                 * Sender
   )
{

//   ChanAssignForm->Visible = true;

}


void __fastcall TSendMsgsForm::DataExtractionReqBtnClick(TObject *Sender)
{
#if(0)
   DataExtractionReqForm * Req = new TDataExtractionReqForm( this, SendMsgsParams.DataExtractionEnabled );
   Req->ShowModal();
   if ( Req->ModalResult == mrOk )
   {
      TStel
   }
   delete Req;
#endif
}

__fastcall
TSendMsgsForm::~TSendMsgsForm
   (
   )
{

   delete ChanAssignForm;

}


//---------------------------------------------------------------------------


