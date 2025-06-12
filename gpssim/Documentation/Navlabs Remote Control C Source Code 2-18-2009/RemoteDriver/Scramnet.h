//---------------------------------------------------------------------------

#ifndef ScramnetH
#define ScramnetH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// $Workfile:: Scramnet.h                                            $
//
// $Revision:: 2                                                     $
//
// $History:: Scramnet.h                                             $
//
//*****************  Version 2  *****************
//User: Michael Wade Date: 1/20/03    Time: 6:33p
//Updated in $/TapMsec
//Initial release.
//
//
//---------------------------------------------------------------------------


#ifndef RtMotionH
#include "RtMotion.h"
#endif

#ifndef RtControlH
#include "RtControl.h"
#endif

#ifndef ClosedLoopMemH
#include "ClosedLoopMem.h"
#endif

#ifndef RangeTruthFileH
#include "RangeTruthFile.h"
#endif

#ifndef RtInterfaceH
#include "RtInterface.h"
#endif

#ifndef ReportErrorH
#include "ReportError.h"
#endif

#ifndef VhTrthRtH
#include "VhTrthRt.h"
#endif

#ifndef ThreadDataComH
#include "ThreadDataCom.h"
#endif

#ifndef ScramnetDllH
#include "ScramnetDll.h"
#endif


using namespace ClosedLoopMem;

#ifndef RtMotionMemH
#include "RtMotionMem.h"
#endif

class TScramnet : public TRtMotionMem {
private:


protected:

   TScramnetDll            * ScramnetDll_;
   unsigned char           * BaseAddr_;
   TReportError            * Report_;

   virtual unsigned char *   GetBaseMemAddr();



public:

   TScramnet( TRtControl * InRtControl );
   virtual __fastcall ~TScramnet();


};


#if(0)
class TScramnet : public TRtMotion, public IRtInterface {
private:

   bool                      StopRcvd_;
   bool                      StopProcessed_;
   TVehTruthRec              InitTruth_;
   bool                      InitValid_;
   unsigned char           * BaseAddr_;
   int                       ExtToSimOffset_;
   int                       SimToExtOffset_;
   bool                      ClearDataAtStart_;
   eSimMode                  SimMode_;
   TGpsTime                  InitTime_;
   TReportError            * Report_;
   bool                      Valid_;
   int                       NumChannels_;
   THandleArray              SyncObjs_;

   TclExtToSimMem          * ExtToSim;
   TclSimToExtMem          * SimToExt;

   bool                      Rt_;
   TRangeTruthFile         * RangeTruthFile_;

   TCriticalSection        * TruthQCritSec;
   std::queue<TVehTruthRec>  TruthQ;
   TVehTruthRec              PrevTruthRec;
   TVehTruthRec              NextTruthRec;
   bool                      ReportedInvalidTruthRec;
   TVehicleTruthRt         * VehicleTruth;
   int                       LastTimeVehicleStateMemWhich;
   TRtControl              * RtControl;
   TWaitableTimer            WaitableTimer;
   TScramnetDll            * ScramnetDll_;


   void _fastcall            Execute();
   bool     const            GetStopped()           const { return( StopRcvd_ && StopProcessed_ ); }
   bool     const            GetInitValid()         const { return( InitValid_ ); }
   double   const            GetCompensationTime()  const { return( 0.0 ); }
   bool     const            GetSimModeIdle()       const { return( SimMode_ == eSimModeIdle ); }
   bool     const            GetSimModeRunning()    const { return( SimMode_ == eSimModeRunning ); }
   bool     const            GetSimModeArmed()      const { return( SimMode_ == eSimModeArmed ); }
   void                      PropagateTruth( const TGpsTime & Time, const TVehTruthRec & PrevRec, const TVehTruthRec & NextRec,TVehTruthRec & Rec );

   void                      ProcessInputData();
   void                      ProcessInitialize();
   void                      FillOutput();
   void                      FillCurTime();
   void                      FillVehicleState();
   void                      ProcessVehicleState();
   void                      ProcessSvOverride();
   TVehTruthRec const        ClTimeVehicleStateToVehTruthRec( const TclTimeVehicleState & ) const;
   TclTimeVehicleState const VehTruthRecToClTimeVehicleState( const TVehTruthRec & Truth ) const;
   void                      AddTruthRec( const TVehTruthRec & NewRec );
   void                      InitializeMem();
   void                      InitializeScramnetDLL();


   AnsiString const          GetStatusStr();
   AnsiString const          GetParametersStr();
   bool const                IsValid() const;

   bool const                GetTruth( const TGpsTime & CurSimTime, TVehTruthRec & );
   TGpsTime const            GetInitTime() const;

public:

   TScramnet( TRtControl * InRtControl );
   virtual __fastcall ~TScramnet();

   bool const                InitCommunication() { return( true ); }
   void                      Signal();


   __property bool           Stopped              = { read = GetStopped                       };
   __property bool           InitValid            = { read = GetInitValid                     };
   __property double         CompensationTime     = { read = GetCompensationTime              };
   __property bool           SimModeIdle          = { read = GetSimModeIdle                   };
   __property bool           SimModeRunning       = { read = GetSimModeRunning                };
   __property bool           SimModeArmed         = { read = GetSimModeArmed                  };
   __property bool           Valid                = { read = IsValid                          };
   __property TGpsTime       InitTime             = { read = GetInitTime                      };
   __property AnsiString     StatusStr            = { read = GetStatusStr                     };
   __property AnsiString     ParametersStr        = { read = GetParametersStr                 };


};
#endif


#endif
