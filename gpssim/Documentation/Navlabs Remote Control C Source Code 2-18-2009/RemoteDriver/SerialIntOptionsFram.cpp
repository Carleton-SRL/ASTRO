#include "pch.h"
#pragma hdrstop

//---------------------------------------------------------------------------
//
// $Workfile:: SerialIntOptionsFram.cpp                              $
//
// $Revision:: 1                                                     $
//
// $History:: SerialIntOptionsFram.cpp                               $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 10/09/02   Time: 4:27p
//Created in $/RemoteDriver
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 10/03/02   Time: 10:11p
//Created in $/RciDriver
//Add ethernet
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 9/30/02    Time: 4:56p
//Created in $/TapRci
//
//
//---------------------------------------------------------------------------


#ifndef SerialIntOptionsFramH
#include "SerialIntOptionsFram.h"
#endif

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ovclabel"
#pragma link "RzPanel"
#pragma link "RzEdit"
#pragma link "RzSpnEdt"
#pragma resource "*.dfm"
TSerialIntOptionsFrame *SerialIntOptionsFrame;
//---------------------------------------------------------------------------

static const int NumSerialBaudRates                  = 12;
static const int SerialBaudRates[NumSerialBaudRates] = { 1200, 2400, 4800, 9600, 14400, 19200, 38400, 56000, 57600, 115200, 128000, 256000 };

__fastcall
TSerialIntOptionsFrame::TSerialIntOptionsFrame
   (
   TComponent              * Owner
   ) :
   TFrame( Owner ),
   RemoteDriverPf( NULL )
{

   RemoteDriverPf                  = new TRemoteDriverPf();

   SetDisplayFromProfile();

}

__fastcall
TSerialIntOptionsFrame::~TSerialIntOptionsFrame
   (
   )
{
   delete RemoteDriverPf;
}

void
TSerialIntOptionsFrame::SetDisplayFromProfile
   (
   )
{

   SerialPortSpinEdit->Value     = RemoteDriverPf->SerialComPort;
   SerialStopBitsSpinEdit->Value = RemoteDriverPf->SerialStopBits;
   int Baud                      = RemoteDriverPf->SerialBaud;
   for ( int i=0; i<NumSerialBaudRates; ++i )
   {
      if ( SerialBaudRates[i] == Baud )
      {
         SerialBaudcbox->ItemIndex     = i;
         break;
      }
   }

}   

void
TSerialIntOptionsFrame::SetProfileFromDisplay
   (
   )
{

   RemoteDriverPf->SerialComPort       = SerialPortSpinEdit->Value;
   RemoteDriverPf->SerialStopBits      = SerialStopBitsSpinEdit->Value;
   RemoteDriverPf->SerialBaud          = SerialBaudRates[ SerialBaudcbox->ItemIndex ];

}

void
TSerialIntOptionsFrame::DoNewOptions
   (
   const bool                Accept
   )
{

   if ( Accept )
   {
      SetProfileFromDisplay();
   }
   else
   {
      SetDisplayFromProfile();
   }

}   

bool const
TSerialIntOptionsFrame::GetOptionsChanged
   (
   )
{

   bool Changed         = false;
   try
   {

      Changed          |= RemoteDriverPf->SerialComPort  != SerialPortSpinEdit->Value;
      Changed          |= RemoteDriverPf->SerialStopBits != SerialStopBitsSpinEdit->Value;
      Changed          |= RemoteDriverPf->SerialBaud     != SerialBaudRates[ SerialBaudcbox->ItemIndex ];

   }
   catch(...)
   {
      CodeSite->SendMsg( csmError, "TSerialIntOptionsFrame::GetOptionsChanged exception" );
   }

   return( Changed );

}   


 