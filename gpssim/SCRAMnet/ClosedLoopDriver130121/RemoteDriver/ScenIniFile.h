#ifndef ScenIniFileH
#define ScenIniFileH
//---------------------------------------------------------------------------
//
// $Workfile:: ScenIniFile.h                                         $
//
// $Revision:: 14                                                    $
//
// $History:: ScenIniFile.h                                          $
//
//*****************  Version 14  *****************
//User: Michael Wade Date: 11/14/03   Time: 11:49a
//Updated in $/TapMsec
//Raytheon ATB
//
//*****************  Version 13  *****************
//User: Michael Wade Date: 5/29/03    Time: 3:11p
//Updated in $/TapMsec
//Add SyncDateTime
//
//*****************  Version 12  *****************
//User: Michael Wade Date: 5/10/03    Time: 11:40p
//Updated in $/TapMsec
//Add Sync To Sky. Check in for ICSTF.
//
//*****************  Version 11  *****************
//User: Michael Wade Date: 4/29/03    Time: 8:09p
//Updated in $/TapMsec
//Add "AddHWCounter" parameter to ScenIni file.
//
//*****************  Version 10  *****************
//User: Michael Wade Date: 1/20/03    Time: 12:05p
//Updated in $/TapMsec
//Add properties
//
//*****************  Version 9  *****************
//User: Michael Wade Date: 7/28/02    Time: 12:19p
//Updated in $/TapMsec
//Add include guards
//
//*****************  Version 8  *****************
//User: Michael Wade Date: 7/23/02    Time: 8:02p
//Updated in $/TapMsec
//Added Source Safe keywords
//
//
//
//
//
//
//---------------------------------------------------------------------------

#ifndef VehTruthH
#include "VehTruth.h"
#endif

#ifndef SyncToSkyAutoStartPrmsH
#include "SyncToSkyAutoStartPrms.h"
#endif

//---------------------------------------------------------------------------
class TScenIniFile : public TIniFile  {
private:

   //   Display Params

   int const            GetRightPanelWidth();
   void                 SetRightPanelWidth( const int InRightPanelWidth );

   int const            GetRfPanelHeight();
   void                 SetRfPanelHeight( const int InRfPanelHeight );

   bool const           IsSerialEnabled();

   bool const           IsScramnetEnabled();

   bool const           IsSharedMemoryEnabled();

   bool const           GetAntiSpoofFlag();
   void                 SetAntiSpoofFlag( const bool InAntiSpoofFlag );

   bool const           GetWaitForStartPulse();
   void                 SetWaitForStartPulse( const bool Wait );

   bool const           GetAddHWCounterToInitTime();
   void                 SetAddHWCounterToInitTime( const bool InAddHWCounterToInitTime );

   //   SyncToSky Params

   bool const                GetSyncToSkyAutoStart();
   void                      SetSyncToSkyAutoStart( const bool InAuto );

   bool const                GetSyncRemote();
   void                      SetSyncRemote( const bool InRemote );

   AnsiString const          SyncAutoPrmsToStr( const TSyncAutoPrms & Prms ) const;
   TSyncAutoPrms const       SyncAutoStrToPrms( const AnsiString    & Str  ) const;

   TSyncAutoPrms const       GetSyncAutoRefDataValid();
   void                      SetSyncAutoRefDataValid( const TSyncAutoPrms & );

   TSyncAutoPrms const       GetSyncAutoRcv1PPS();
   void                      SetSyncAutoRcv1PPS( const TSyncAutoPrms & );

   TSyncAutoPrms const       GetSyncAuto1PPSValid();
   void                      SetSyncAuto1PPSValid( const TSyncAutoPrms & );

   TSyncAutoPrms const       GetSyncAutoArmReset();
   void                      SetSyncAutoArmReset( const TSyncAutoPrms & );

   TSyncAutoPrms const       GetSyncAutoComplete();
   void                      SetSyncAutoComplete( const TSyncAutoPrms & );

   bool const                GetSyncAutoAllowOverride();
   void                      SetSyncAutoAllowOverride( const bool InAllow );


protected:
public:
   TScenIniFile();

   bool const           IsUseScenFile();

   int const            GetNumPseudolites();
   void                 WriteNumPseudolites(const int NumPseudolites);

   bool const           IsPseudolite();
   void                 WritePseudolite(const bool Pseudolite);

   bool const           IsSyncToSkyUseGps();
   void                 WriteSyncToSkyUseGps( const bool SyncToSkyUseGps );

   bool const           IsSyncToSkyEnabled();
   void                 WriteSyncToSky( const bool SyncToSky );

   bool const           IsPulse();
   bool const           IsUseScenPT();
   void                 WritePulse(const bool Pulse);
   void                 WriteUseScenPT( const bool UseScenPT );
   void                 WriteLocal( const bool Local );
   void                 GetSyncPos( double &Lat, double &Lon, double &Alt );
   TDateTime const      GetSyncDate( );
   TDateTime const      GetSyncTime( );
   TDateTime const      GetSyncDateTime( );
   void                 SetSyncPos( double Lat, double Lon, double Alt );
   void                 SetSyncDate( const TDateTime &Date );
   void                 SetSyncTime( const TDateTime &Time );
   void                 SetSyncDateTime( const TDateTime &Time );
   int const            GetRefRcvrPort( );
   int const            GetRefRcvrBaud( );
   TVehTruthRec const   GetInitialSyncState( );
   int const            GetCommonRfAtten(const int RfNum=0);
   void                 WriteCommonRfAtten( const int Atten, const int RfNum = 0 );
   void                 WritePPSCounter( const int RolloverPPSCount, const int PPSCount );
   void                 GetPPSCounter( int &RolloverPPSCount, int &PPSCount );
   bool const           IsGpibEnabled();
   bool const           IsRtMsgWriteDebug();
   bool const           IsRtMsgWriteTrajFile();
   bool const           IsSingleChan();
   bool const           IsEthernetEnabled();
   bool const           IsFileBased();
   bool const           IsRemote();
   bool const           IsLocal();
   bool const           IsRt();
   bool const           IsSingleChanAutoStart();
   void                 WriteSingleChanAutoStart( const bool AutoStart );
   bool const           IsStelSendSvLookAngle();
   bool const           IsWriteRangeTruthRT();

   __property int            RfPanelHeight                 = { read = GetRfPanelHeight,             write = SetRfPanelHeight     };
   __property int            RightPanelWidth               = { read = GetRightPanelWidth,           write = SetRightPanelWidth   };
   __property bool           Remote                        = { read = IsRemote,                                                  };
   __property bool           Rt                            = { read = IsRt                                                       };
   __property bool           Pseudolite                    = { read = IsPseudolite,                 write = WritePseudolite      };
   __property int            NumPseudolites                = { read = GetNumPseudolites,            write = WriteNumPseudolites  };
   __property bool           SyncToSkyUseGps               = { read = IsSyncToSkyUseGps,            write = WriteSyncToSkyUseGps };
   __property bool           SyncToSkyEnabled              = { read = IsSyncToSkyEnabled,           write = WriteSyncToSky       };
   __property bool           SingleChan                    = { read = IsSingleChan                                               };
   __property bool           WriteRangeTruthRT             = { read = IsWriteRangeTruthRT                                        };
   __property bool           Ethernet                      = { read = IsEthernetEnabled                                          };
   __property bool           Gpib                          = { read = IsGpibEnabled                                              };
   __property bool           Serial                        = { read = IsSerialEnabled                                            };
   __property bool           Scramnet                      = { read = IsScramnetEnabled                                          };
   __property bool           SharedMemory                  = { read = IsSharedMemoryEnabled                                      };
   __property bool           AntiSpoofFlag                 = { read = GetAntiSpoofFlag,             write = SetAntiSpoofFlag     };
   __property bool           FileBased                     = { read = IsFileBased                                                };
   __property bool           Local                         = { read = IsLocal,                      write = WriteLocal           };
   __property bool           WaitForStartPulse             = { read = GetWaitForStartPulse,         write = SetWaitForStartPulse };
   __property TVehTruthRec   InitialSyncState              = { read = GetInitialSyncState                                        };
   __property bool           AddHWCounterToInitTime        = { read = GetAddHWCounterToInitTime,    write = SetAddHWCounterToInitTime   };
   __property bool           SyncRemote                    = { read = GetSyncRemote,                write = SetSyncRemote        };
   __property TDateTime      SyncDate                      = { read = GetSyncDate,                  write = SetSyncDate          };
   __property TDateTime      SyncTime                      = { read = GetSyncTime,                  write = SetSyncTime          };
   __property TDateTime      SyncDateTime                  = { read = GetSyncDateTime,              write = SetSyncDateTime      };


   __property bool            SyncToSkyAutoStart           = { read = GetSyncToSkyAutoStart,               write = SetSyncToSkyAutoStart       };

   __property bool            SyncAutoAllowOverride        = { read = GetSyncAutoAllowOverride,  write = SetSyncAutoAllowOverride       };

   __property TSyncAutoPrms   SyncAutoRefDataValid         = { read = GetSyncAutoRefDataValid,                 write = SetSyncAutoRefDataValid                      };
   __property TSyncAutoPrms   SyncAutoRcv1PPS              = { read = GetSyncAutoRcv1PPS,                      write = SetSyncAutoRcv1PPS                           };
   __property TSyncAutoPrms   SyncAuto1PPSValid            = { read = GetSyncAuto1PPSValid,                    write = SetSyncAuto1PPSValid                         };
   __property TSyncAutoPrms   SyncAutoArmReset             = { read = GetSyncAutoArmReset,                     write = SetSyncAutoArmReset                          };
   __property TSyncAutoPrms   SyncAutoComplete             = { read = GetSyncAutoComplete,                     write = SetSyncAutoComplete                          };

};

//---------------------------------------------------------------------------
#endif
