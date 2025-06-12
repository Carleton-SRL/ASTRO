#ifndef VoyDefPfH
#define VoyDefPfH

class VoyDefProfile : public TIniFile {
public:
enum OrbDriverType { Orb16=16, Orb8=8, GsIsa=17, GsPci=18 };
   static const int Orb8Bit = 1;
   static const int Orb16Bit = 2;
   VoyDefProfile();
    _fastcall virtual ~VoyDefProfile();
   void GetRunsDir(char *RunRoot);
   AnsiString const GetRunsDir();
   void GetHostAddr(char *HostAddr);
//   void GetRemoteDir(char *RunRemote);
   bool GetDoCodeCalibration();
   bool GetDoRTCalibration();
   bool GetDoCarrierCalibration();
   bool GetShowCal();
   int GetTruthTimeDelay();
   int GetDisplayUpdateInterval();
   int const GetScramnetOffset();
   int GetInterChassisBias(int ChassisNum);
   bool const IsRemote();
   bool const IsMcAnal05();
   bool const IsTestMode();
   OrbDriverType GetDriverType();
   bool const IsPcsgIntEnabled();
   bool const IsGroundTrackEnabled();
   bool const IsPlotEnabled();
   bool const IsDebugDisp();
   int const  GetLLTestNumChans();
};
#endif


