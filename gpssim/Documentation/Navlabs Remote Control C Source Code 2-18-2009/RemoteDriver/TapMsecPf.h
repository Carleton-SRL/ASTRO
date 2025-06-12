#ifndef TapMsecPfH
#define TapMsecPfH


//---------------------------------------------------------------------------
//
// $Workfile:: TapMsecPf.h                                           $
//
// $Revision:: 1                                                     $
//
// $History:: TapMsecPf.h                                            $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 3/30/04    Time: 11:55a
//Created in $/RemoteDriver
//
//
//---------------------------------------------------------------------------


#ifndef PosVecH
#include "PosVec.h"
#endif

#ifndef GpibTimeoutH
#include "GpibTimeout.h"
#endif

//---------------------------------------------------------------------------

class TTapMsecProfile : public TIniFile  {
private:

   AnsiString const          GetHostAddr();

   bool const                GetCrpaLite();
   int  const                GetCrpaLiteNumRfs();

   bool const                GetCreateRcvrAsDialog();
   void                      SetCreateRcvrAsDialog( const bool CreateRcvrAsDialog );

   bool const                GetShowVehLftPnlSplitterHotSpot();
   void                      SetShowVehLftPnlSplitterHotSpot( const bool Show );

   bool const                GetShowVehRghtPnlSplitterHotSpot();
   void                      SetShowVehRghtPnlSplitterHotSpot( const bool Show );

   bool const                GetShowLLAScaleSplitterHotSpot();
   void                      SetShowLLAScaleSplitterHotSpot( const bool Show );

   bool const                GetUseGpsTimeForXAxis();
   void                      SetUseGpsTimeForXAxis( const bool UseXAxis );

   bool const                GetResetErrPlotOnTimeReset();
   void                      SetResetErrPlotOnTimeReset( const bool Reset );

   bool const                GetResetErrPlotOnFirstNav();
   void                      SetResetErrPlotOnFirstNav( const bool Reset );

   double const              GetAttenIncrement();
   void                      SetAttenIncrement( const double AttenIncrement );

   bool const                GetSaveReportParams();
   void                      SetSaveReportParams( const bool SaveReportParams );

   bool const                GetCodeSiteEnabled();
   void                      SetCodeSiteEnabled( const bool CodeSiteEnabled );

   bool const                GetResetCounters();
   void                      SetResetCounters( const bool ResetCounters );

   TDateTime const           GetDate();
   void                      SetDate( const TDateTime & Date );
   TDateTime const           GetTime();
   void                      SetTime( const TDateTime & Time );

   bool const                GetInitFromClock();
   void                      SetInitFromClock( const bool InitFromClock );

   bool const                GetRefLocalTime();
   void                      SetRefLocalTime( const bool RefLocalTime );

   bool const                GetShowDebug();

   bool const                GetDispRelativePower();
   void                      SetDispRelativePower( const bool DispRelativePower );

   bool const                GetBitTestX1();
   bool const                GetBitTestX2();
   bool const                GetBitTestX3();
   bool const                GetBitTestX( const int Index );
   void                      SetBitTestX1( const bool TestX1 );
   void                      SetBitTestX2( const bool TestX2 );
   void                      SetBitTestX3( const bool TestX3 );
   void                      SetBitTestX( const int Index, const bool TestX );

   bool const                GetBitTestInt();
   void                      SetBitTestInt( const bool TestInt );

   TPosVec const             GetPos();
   void                      SetPos( const TPosVec & PosVec );

   bool const                GetExitBadCal();

   // Plot Display
   bool const                GetErrorPlotEnabled();
   void                      SetErrorPlotEnabled( const bool InPlotEnabled );

   bool const                GetErrorPlotPointsAppend();
   void                      SetErrorPlotPointsAppend( const bool InPlotPointsAppend );

   int const                 GetErrorPlotMaxPoints();
   void                      SetErrorPlotMaxPoints( const int InPlotMaxPoints );

   bool const                GetGt2DPlotEnabled();
   void                      SetGt2DPlotEnabled( const bool InPlotEnabled );

   bool const                GetGt3DPlotEnabled();
   void                      SetGt3DPlotEnabled( const bool InPlotEnabled );

   // Output Pulse

   bool    const             GetPPSAlwaysOn();
   void                      SetPPSAlwaysOn( const bool PPSAlwaysOn );

   int     const             GetPPSWidth();
   void                      SetPPSWidth( const int PPSWidth );

   bool    const             GetVariableOutputPulse();
   void                      SetVariableOutputPulse( const bool Enabled );

   int     const             GetVariableOutputPulseRate();
   void                      SetVariableOutputPulseRate( const int Rate );

   int     const             GetVariableOutputPulseWidth();
   void                      SetVariableOutputPulseWidth( const int Width );

   bool    const             GetVariableOutputPulseAlwaysOn();
   void                      SetVariableOutputPulseAlwaysOn( const bool On );

   bool const                GetRemoteCompensateTime();
   void                      SetRemoteCompensateTime( const bool Compensate );

   int  const                GetRemoteCompensateTimeDelta();
   void                      SetRemoteCompensateTimeDelta( const int CompensateDelta );

   bool const                GetRemoteWriteDebugWaitResults();
   void                      SetRemoteWriteDebugWaitResults( const bool Wait );

   double const              GetRemoteStoreTruthTimeDelta();
   void                      SetRemoteStoreTruthTimeDelta( const double TimeDelta );
   // Ethernet

   bool const                GetEthernetServer();
   void                      SetEthernetServer( const bool IsServer );

   bool const                GetEthernetClient();
   void                      SetEthernetClient( const bool IsClient );

   AnsiString const          GetEthernetHostAddress();
   void                      SetEthernetHostAddress( const AnsiString &HostAddr );

   int const                 GetEthernetPortNum();
   void                      SetEthernetPortNum( const int PortNum );

   // Gpib

   int  const                GetGpibBoardIndex( );
   int  const                GetGpibPrimaryDeviceAddress( );
   int  const                GetGpibSecondaryDeviceAddress( );
   bool const                GetGpibWriteError();
   int  const                GetGpibStartDelay( );
   bool const                GetGpibController( );
   int const                 GetGpibTimeout();
   void                      SetGpibTimeout( const int Timeout );

   // RtMotionMem

   int  const                GetRtMotionMemExtToSimOffset();
   int  const                GetRtMotionMemSimToExtOffset();
   bool const                GetRtMotionMemClearDataAtStart();

   void                      SetRtMotionMemExtToSimOffset( const int Offset );
   void                      SetRtMotionMemSimToExtOffset( const int Offset );
   void                      SetRtMotionMemClearDataAtStart( const bool Clear );

   // MFIO

   bool const                GetTestModeMfio();
   void                      SetTestModeMfio( const bool InTestModeMfio );

   // VPGMSECINTERFACE

   int  const                GetRangeTruthFileRate();
   void                      SetRangeTruthFileRate( const int InRate );

protected:
public:

   TTapMsecProfile();

   TTapMsecProfile( const TTapMsecProfile & Source ) : TIniFile("Voyager.ini")
   {
      ( *this ) = Source;
   }

   TTapMsecProfile & operator = ( const TTapMsecProfile & Source )
   {
      return( *this );
   }

   void                      GetReportParams( const AnsiString & Module, bool &Enabled, bool &Append, bool &PrependDateTime, bool &UseCodeSite, bool &WriteDebug, bool &ShowErrorForm );
   void                      SetReportParams( const AnsiString & Module, const bool Enabled, const bool Append, const bool PrependDateTime, const bool UseCodeSite, const bool WriteDebug, const bool ShowErrorForm );

   __property bool       CrpaLiteEnabled                = { read = GetCrpaLite                                                                       };
   __property int        CrpaLiteNumRfs                 = { read = GetCrpaLiteNumRfs                                                                 };
   __property TDateTime  Date                           = { read = GetDate,                           write = SetDate                                };
   __property TDateTime  Time                           = { read = GetTime,                           write = SetTime                                };
   __property bool       InitFromClock                  = { read = GetInitFromClock,                  write = SetInitFromClock                       };
   __property bool       CreateRcvrAsDialog             = { read = GetCreateRcvrAsDialog,             write = SetCreateRcvrAsDialog                  };
   __property bool       ShowVehLftPnlSplitterHotSpot   = { read = GetShowVehLftPnlSplitterHotSpot,   write = SetShowVehLftPnlSplitterHotSpot        };
   __property bool       ShowVehRghtPnlSplitterHotSpot  = { read = GetShowVehRghtPnlSplitterHotSpot,  write = SetShowVehRghtPnlSplitterHotSpot       };
   __property bool       ShowLLAScaleSplitterHotSpot    = { read = GetShowLLAScaleSplitterHotSpot,    write = SetShowLLAScaleSplitterHotSpot         };
   __property bool       UseGpsTimeForXAxis             = { read = GetUseGpsTimeForXAxis,             write = SetUseGpsTimeForXAxis                  };
   __property bool       ResetErrPlotOnTimeReset        = { read = GetResetErrPlotOnTimeReset,        write = SetResetErrPlotOnTimeReset             };
   __property bool       ResetErrPlotOnFirstNav         = { read = GetResetErrPlotOnFirstNav,         write = SetResetErrPlotOnFirstNav              };
   __property double     AttenIncrement                 = { read = GetAttenIncrement,                 write = SetAttenIncrement                      };
   __property bool       RefLocalTime                   = { read = GetRefLocalTime,                   write = SetRefLocalTime                        };
   __property bool       ShowDebug                      = { read = GetShowDebug                                                                      };
   __property bool       ExitBadCal                     = { read = GetExitBadCal                                                                     };
   __property bool       DispRelativePower              = { read = GetDispRelativePower,              write = SetDispRelativePower                   };
   __property bool       PPSAlwaysOn                    = { read = GetPPSAlwaysOn,                    write = SetPPSAlwaysOn                         };
   __property int        PPSWidth                       = { read = GetPPSWidth,                       write = SetPPSWidth                            };
   __property bool       BitTestX1                      = { read = GetBitTestX1,                      write = SetBitTestX1                           };
   __property bool       BitTestX2                      = { read = GetBitTestX2,                      write = SetBitTestX2                           };
   __property bool       BitTestX3                      = { read = GetBitTestX3,                      write = SetBitTestX3                           };
   __property bool       BitTest[int Index]             = { read = GetBitTestX,                       write = SetBitTestX                            };
   __property TPosVec    Pos                            = { read = GetPos,                            write = SetPos                                 };
   __property bool       RemoteCompensateTime           = { read = GetRemoteCompensateTime,           write = SetRemoteCompensateTime                };
   __property int        RemoteCompensateTimeDelta      = { read = GetRemoteCompensateTimeDelta,      write = SetRemoteCompensateTimeDelta           };
   __property double     RemoteStoreTruthTimeDelta      = { read = GetRemoteStoreTruthTimeDelta,      write = SetRemoteStoreTruthTimeDelta           };
   __property bool       EthernetServer                 = { read = GetEthernetServer,                 write = SetEthernetServer                      };
   __property bool       EthernetClient                 = { read = GetEthernetClient,                 write = SetEthernetClient                      };
   __property AnsiString EthernetHostAddress            = { read = GetEthernetHostAddress,            write = SetEthernetHostAddress                 };
   __property int        EthernetPortNum                = { read = GetEthernetPortNum,                write = SetEthernetPortNum                     };
   __property bool       SaveReportParams               = { read = GetSaveReportParams,               write = SetSaveReportParams                    };
   __property bool       CodeSiteEnabled                = { read = GetCodeSiteEnabled,                write = SetCodeSiteEnabled                     };
   __property bool       ResetCounters                  = { read = GetResetCounters,                  write = SetResetCounters                       };
   __property int        GpibBoardIndex                 = { read = GetGpibBoardIndex                                                                 };
   __property int        GpibPrimaryDeviceAddress       = { read = GetGpibPrimaryDeviceAddress                                                       };
   __property int        GpibSecondaryDeviceAddress     = { read = GetGpibSecondaryDeviceAddress                                                     };
   __property int        GpibWriteError                 = { read = GetGpibWriteError                                                                 };
   __property int        GpibStartDelay                 = { read = GetGpibStartDelay                                                                 };
   __property int        GpibController                 = { read = GetGpibController                                                                 };
   __property int        GpibTimeout                    = { read = GetGpibTimeout,                    write = SetGpibTimeout                         };
   __property int        RtMotionMemExtToSimOffset      = { read = GetRtMotionMemExtToSimOffset,      write = SetRtMotionMemExtToSimOffset           };
   __property int        RtMotionMemSimToExtOffset      = { read = GetRtMotionMemSimToExtOffset,      write = SetRtMotionMemSimToExtOffset           };
   __property bool       RtMotionMemClearDataAtStart    = { read = GetRtMotionMemClearDataAtStart,    write = SetRtMotionMemClearDataAtStart         };
   __property bool       VariableOutputPulse            = { read = GetVariableOutputPulse,            write = SetVariableOutputPulse                 };
   __property int        VariableOutputPulseRate        = { read = GetVariableOutputPulseRate,        write = SetVariableOutputPulseRate             };
   __property int        VariableOutputPulseWidth       = { read = GetVariableOutputPulseWidth,       write = SetVariableOutputPulseWidth            };
   __property bool       TestModeMfio                   = { read = GetTestModeMfio,                   write = SetTestModeMfio                        };
   __property bool       WriteDebugWaitResults          = { read = GetRemoteWriteDebugWaitResults,    write = SetRemoteWriteDebugWaitResults         };
   __property bool       ErrorPlotEnabled               = { read = GetErrorPlotEnabled,               write = SetErrorPlotEnabled                    };
   __property bool       ErrorPlotPointsAppend          = { read = GetErrorPlotPointsAppend,          write = SetErrorPlotPointsAppend               };
   __property int        ErrorPlotMaxPoints             = { read = GetErrorPlotMaxPoints,             write = SetErrorPlotMaxPoints                  };
   __property bool       Gt2DPlotEnabled                = { read = GetGt2DPlotEnabled,                write = SetGt2DPlotEnabled                     };
   __property bool       Gt3DPlotEnabled                = { read = GetGt3DPlotEnabled,                write = SetGt3DPlotEnabled                     };
   __property int        RangeTruthFileRate             = { read = GetRangeTruthFileRate,             write = SetRangeTruthFileRate                  };

};


//---------------------------------------------------------------------------
#endif
