#ifndef RemoteTypesH
#define RemoteTypesH

//---------------------------------------------------------------------------
//
// $Workfile:: RemoteTypes.h                                         $
//
// $Revision:: 1                                                     $
//
// $History:: RemoteTypes.h                                          $
//
//*****************  Version 1  *****************
//User: Michael Wade Date: 9/03/02    Time: 4:29p
//Created in $/RemoteDriver
//
//
//---------------------------------------------------------------------------


#define NUM_DISP_CHANS ( 14 )

typedef enum { eSelScen=0, eSelVehFile=1 } eSelType;

typedef enum { eIntGpib=0, eIntSerial=1, eIntEthernet=2, eIntScramnet=3, eIntSharedMem=4 } eIntType;

typedef enum { eIdle=0x01, eTest=0x02, eTraj=0x04, eUmg=0x08 } eSimMode;

typedef enum { eProtSTel7224=0, eProtStel7200=1, eProtNavLabs=2 } eIntProtocol;

typedef std::vector<unsigned char>     TMsgData;

typedef std::queue<TMsgData>           TMsgDataQueue;

typedef std::vector<unsigned char>     TMsgBody;

typedef std::vector<TThread *>         ThreadArray;

typedef std::vector<HANDLE>            THandleArray;

class TSvLookAngle {

private:

   int    Chan;
   int    Svid;
   double El;
   double Az;
   bool   NewEph;

public:

   TSvLookAngle( const int InChan, const int InSvid, const double InEl, const double InAz, const bool InNewEph=false ) :
      Chan( InChan ), Svid( InSvid ), El( InEl ), Az( InAz ), NewEph( InNewEph ) {}
   int const GetChan() const { return( Chan ); }
   int const GetSvid() const { return( Svid ); }
   int const GetEl() const { return( El ); }
   int const GetAz() const { return( Az ); }
   int const GetNewEph() const { return( NewEph ); }

   friend bool const operator==( const TSvLookAngle &lhs, const TSvLookAngle &rhs )
   {
      bool Same = true;
      if ( lhs.Chan       != rhs.Chan       ) Same = false;
      if ( lhs.Svid       != rhs.Svid       ) Same = false;
      if ( NINT( lhs.El ) != NINT( rhs.El ) ) Same = false;
      if ( NINT( lhs.Az ) != NINT( rhs.Az ) ) Same = false;
      if ( lhs.NewEph     != rhs.NewEph     ) Same = false;

      return( Same );

   }

};

typedef std::vector<TSvLookAngle> TSvLookAngleArray;


#endif
 