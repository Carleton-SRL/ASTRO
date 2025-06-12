//---------------------------------------------------------------------------
// ClassExplorer Pro generated header file
// Created by Michael Wade on 2/3/2002, 6:00:54 PM
//---------------------------------------------------------------------------
#ifndef GpibH
#define GpibH

#include "RemoteTypes.h"
#include "Interface.h"

//---------------------------------------------------------------------------
class TGpib : public TInterface  {
private:
   TGpibOptions GpibOptions;
   int Board;
//   int Dev;
   void ReportError( const AnsiString &PreStr );
protected:
   bool const SendMsg( const TMsgData &MsgData );
   void ReadMsg( TMsgData &MsgData );
public:
   TGpib( const TGpibOptions &InGpibOptions );
   virtual __fastcall ~TGpib();
};

//---------------------------------------------------------------------------
#endif
