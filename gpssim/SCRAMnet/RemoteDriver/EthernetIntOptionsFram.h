//---------------------------------------------------------------------------


#ifndef EthernetIntOptionsFramH
#define EthernetIntOptionsFramH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// $Workfile:: EthernetIntOptionsFram.h                              $
//
// $Revision:: 1                                                     $
//
// $History:: EthernetIntOptionsFram.h                               $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 9/29/02    Time: 6:34p
//Created in $/TapRci
//Initial checkin from RemoteDriver
//
//
//---------------------------------------------------------------------------


//------------------------------------------------------------------------------
#ifndef BUILDERINCLUDES
//------------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ovcbase.hpp"
#include "ovcef.hpp"
#include "ovcpb.hpp"
#include "ovcpf.hpp"
#include "ovclabel.hpp"
#include "ovcnf.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzRadGrp.hpp"
#include "RzButton.hpp"
#include <ImgList.hpp>
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------

//---------------------------------------------------------------------------

#ifndef RemoteDriverPfH
#include "RemoteDriverPf.h"
#endif

#ifndef AcceptInterfaceOptionsH
#include "AcceptInterfaceOptions.h"
#endif



class TEthernetIntOptionsFrame : public TFrame, public IAcceptInterfaceOptions
{
__published:
   TOvcController *EtherOvcController;
   TRzPanel *TopPnl;
   TOvcLabel *EthernetTitleLbl;
   TRzPanel *MainClientPnl;
   TOvcLabel *HostAddrLbl;
   TOvcNumericField *HostAddr1;
   TOvcLabel *Dot1;
   TOvcNumericField *HostAddr2;
   TOvcLabel *Dot2;
   TOvcNumericField *HostAddr3;
   TOvcNumericField *HostAddr4;
   TOvcLabel *Dot3;
   TOvcLabel *PortLbl;
   TOvcNumericField *Port;
   TRzRadioGroup *ClientServerRadioGroup;
   TImage *EthernetImage;
   TImageList *EthernetImageList;
   void __fastcall HostAddrEnter(TObject *Sender);
   void __fastcall HostAddrChange(TObject *Sender);
   void __fastcall ClientServerRadioGroupClick(TObject *Sender);

private:

   TRemoteDriverPf         * RemoteDriverPf;

   void                      SetNumericFieldFocus( TOvcNumericField * NumericField );
   void                      EnableHostAddrDisplay( const bool HostAddrEnabled );
   void                      SetProfileFromDisplay();
   void                      SetDisplayFromProfile();

public:

   __fastcall TEthernetIntOptionsFrame( TComponent* Owner );
   __fastcall ~TEthernetIntOptionsFrame();

   void                      DoNewOptions( const bool Accept );
   bool const                GetOptionsChanged();

   static TIntArr const ConvertHostAddrToNumbers( const AnsiString HostAddrStr )
   {
      TIntArr HostAddrNums;
      TStringList * Fields = new TStringList;
      ExtractTokensL( HostAddrStr, AnsiString( "." ), '\'', true, Fields );
      for ( int i=0; i<Fields->Count; ++i )
      {
         HostAddrNums.push_back( Fields->Strings[i].ToInt() );
      }
      for ( int i=Fields->Count; i<4; ++i )
      {
         HostAddrNums.push_back( 0 );
      }
      return( HostAddrNums );
   }

   static AnsiString const ConvertHostAddrNumbersToStr( const TIntArr HostAddrNums )
   {
      AnsiString Str;
      Str.sprintf( "%d.%d.%d.%d", HostAddrNums[0], HostAddrNums[1], HostAddrNums[2], HostAddrNums[3] );
      return( Str );
   }

};
//---------------------------------------------------------------------------
extern PACKAGE TEthernetIntOptionsFrame *EthernetIntOptionsFrame;
//---------------------------------------------------------------------------
#endif
