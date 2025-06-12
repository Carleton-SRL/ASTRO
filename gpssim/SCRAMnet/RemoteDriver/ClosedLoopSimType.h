#ifndef ClosedLoopSimTypeH
#define ClosedLoopSimTypeH

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


#ifndef RemoteTypesH
#include "RemoteTypes.h"
#endif

//---------------------------------------------------------------------------
class TClosedLoopSimType {
private:
   eSelType                  FSelType;
   eIntType                  FIntType;
   int                       FUpdateRate;
   AnsiString                FPath;
   double                    FPreloadTime;
   eIntProtocol              FProtocol;
   AnsiString const __fastcall GetVehicleTruthPath() const;
public:

   TClosedLoopSimType( const eSelType InSelType, const eIntType IntType, const int UpdateRate, const AnsiString &Path,
      const double PreloadTime, const eIntProtocol InIntProtocol);

    __property eIntType      IntType          = { read = FIntType,             write = FIntType };
    __property AnsiString    Path             = { read = FPath,                write = FPath };
    __property double        PreloadTime      = { read = FPreloadTime,         write = FPreloadTime };
    __property eIntProtocol  Protocol         = { read = FProtocol,            write = FProtocol };
    __property eSelType      SelType          = { read = FSelType,             write = FSelType };
    __property int           UpdateRate       = { read = FUpdateRate,          write = FUpdateRate };
    __property AnsiString    VehicleTruthPath = { read = GetVehicleTruthPath                       };

};

//---------------------------------------------------------------------------
#endif
