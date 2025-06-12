#include "pch.h"
#pragma hdrstop
//---------------------------------------------------------------------------
// ClassExplorer Pro generated source file
// Created by Michael Wade on 2/2/2002, 7:26:25 PM
//---------------------------------------------------------------------------
#ifndef ClosedLoopSimTypeH
#include "ClosedLoopSimType.h"
#endif

//---------------------------------------------------------------------------


TClosedLoopSimType::TClosedLoopSimType
   (
   const eSelType     InSelType,
   const eIntType     InIntType,
   const int          InUpdateRate,
   const AnsiString  &InPath,
   const double       InPreloadTime,
   const eIntProtocol InProtocol
   ) :
   FSelType( InSelType ),
   FIntType( InIntType ),
   FUpdateRate( InUpdateRate ),
   FPath( InPath ),
   FPreloadTime( InPreloadTime ),
   FProtocol( InProtocol )
{
}





AnsiString const __fastcall 
TClosedLoopSimType::GetVehicleTruthPath
   (
   
   ) const
{

   AnsiString VehPath = Path;
   if ( SelType != eSelVehFile )
   {
      VehPath += AnsiString( "\\Truth1.scn" );
   }

   return( VehPath );
   
}

