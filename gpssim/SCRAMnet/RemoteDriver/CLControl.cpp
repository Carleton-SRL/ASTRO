#include "pch.h"
#pragma hdrstop

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


#ifndef CLControlH
#include "CLControl.h"
#endif

#ifndef ScenTimeH
#include "ScenTime.h"
#endif

#ifndef OutMsgH
#include "OutMsg.h"
#endif

#ifndef GpibH
#include "Gpib.h"
#endif
#ifndef EthernetH
#include "Ethernet.h"
#endif

#ifndef ThreadInfH
#include "ThreadInf.h"
#endif

//---------------------------------------------------------------------------
static const int             CLCControlUpdateRate              = 10;
static const int             CLCONTROL_EXECUTE_TIMER_MS        = 100;

TCLControl::TCLControl
   (
   const TClosedLoopSimType    & InClosedLoopSimType
   ) :
   TThread( true ),
   ClosedLoopSimType( InClosedLoopSimType ),
   UpdateIndex( 0 ),
   TrajectoryDeltaTimeMillisec( 0 ),
   Interface_( NULL ),
   SendStop( false ),
   StopSent_( false),
   StopQueued( false ),
   NumMsgsRcvdExceptStat_( 0 ),
   NumMsgsRcvd_( 0 ),
   NumMsgsSent_( 0 ),
   MsgCriticalSection_( NULL ),
   LastTrajectoryTimeMillisec( -100 )
{

   CodeSite->EnterMethod( "TCLControl" );
   CodeSite->SendMsg( AnsiString( "VehPath " ) + ClosedLoopSimType.VehicleTruthPath );

   RemoteDriverPf              = new TRemoteDriverPf();

   VehTruthFile                = new TVehicleTruthFile( ClosedLoopSimType.Path, 0 );

   FirstTruth_                 = VehTruthFile->GetFirst();
   LastTruth_                  = VehTruthFile->GetLast();

   FirstTime                   = FirstTruth_.GpsTime;
   LastTime                    = LastTruth_.GpsTime;

   TrajectoryDeltaTimeMillisec = NINT( ( 1.0/ClosedLoopSimType.UpdateRate ) * 1000 );
   LastTrajectoryTimeMillisec  = -TrajectoryDeltaTimeMillisec;

   ScheduleSignal              = new TScheduleSignal();
   ScheduleSignal->Resume();

   MsgCriticalSection_         = new TCriticalSection();

   InitializeInterface();

   CodeSite->ExitMethod( "TCLControl" );

}

void _fastcall
TCLControl::Execute
   (
   )
{

   TThreadInf TThreadInf( "TCLControlThread" );

   SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL );

   while ( !( Terminated && StopSent_ ) )
   {

      const TDataComWaitResults WaitResult  = Interface_->WaitForRead();

      if ( Terminated ) break;

      if ( !Interface_->Valid ) return;

      ReadMsgData();

      TOutMsgQ OutMsgs;

      if ( SendStop )
      {

         OutMsgs.push( TStelStop() );

         StopQueued                         = true;
         SendStop                           = false;

      }

      if ( ShouldSendTrajectory() )
      {
         TStelTrajectory Traj = GetTrajectory();
         OutMsgs.push( TOutMsg( Traj ) );
//         AnsiString Str;
//         Str.sprintf( "TCLControl::Execute Sent Traj at %d.  LastTrajectoryTimeMillisec = %d.  TrajectoryDeltaTimeMillisec = %d",
//            TScenTime::GetTimeMillisec(), LastTrajectoryTimeMillisec, TrajectoryDeltaTimeMillisec );
//         CodeSite->SendMsg( Str );
      }

      SendMsgs( OutMsgs );

      StopSent_ |= StopQueued && ( Interface_->UnsentDataSize == 0 );
      if ( StopSent_ )
      {
         Sleep( 1000 );
         Terminate();
      }
   }

   delete Interface_;
   Interface_ = NULL;

}

void
TCLControl::SendMsgs
   (
   TOutMsgQ                & OutMsgs
   )
{

   Interface_->SendMsgData = OutMsgs.MsgData;

   MsgCriticalSection_->Acquire();

   while ( OutMsgs.size() )
   {

      TOutMsg OutMsg = OutMsgs.front();

      MsgTrafficArray_.push_back( TMsgTraffic( TScenTime::GetTimeMillisec(), OutMsg.MsgId, eMSG_SOURCE_CTLR ) );

      OutMsgs.pop();

   }

   MsgCriticalSection_->Release();

}

void
TCLControl::SendMsg
   (
   const TOutMsg & OutMsg
   )
{
   SendMsgData( OutMsg.MsgData );
}

void
TCLControl::SendMsgData
   (
   const TMsgData & MsgData
   )
{
   Interface_->SendMsgData = MsgData;
}   

void
TCLControl::ReadMsgData
   (
   )
{

   TMsgData RcvdData = Interface_->ReceivedMsgData;
   while ( !RcvdData.empty() )
   {

      InMsg.ProcessData( RcvdData );

      if ( InMsg.MsgComplete )
      {

         ProcessInMsg( InMsg );

         InMsg.Clear();

      }

   }

}

void
TCLControl::InitializeSim
   (
   )
{

   // Need to send init message and first 3 Trajectory messages
   //
   TOutMsgQ OutMsgs;

   TStelInitSim InitSim    = FirstTruth_;

   TOutMsg OutInitMsg      = InitSim;
   OutMsgs.push( OutInitMsg );

   for ( int i=0; i<3; ++i )
   {

      TStelTrajectory Traj = GetTrajectory();
      OutMsgs.push( TOutMsg( Traj ) );

   }

   CodeSite->SendInteger( "TCLControl::InitializeSim NumOutMsgs ", OutMsgs.size() );

   SendMsgs( OutMsgs );

   // DEBUG!  Don't start sim
   TScheduleSignal::ResetStartCount( 0 );

}

TStelTrajectory const
TCLControl::GetTrajectory
   (
   )
{

   TGpsTime TrajTime    = GetUpdateTime();
   VehTruthFile->GetTruth( TrajTime, &CurTruth_ );
   TStelTrajectory Traj = CurTruth_;

   return( Traj );

}


bool const
TCLControl::InitializeInterface
   (
   )
{

   TInterfaceParams InterfaceParams;


   if ( RemoteDriverPf->Gpib )
   {
      InterfaceParams.Gpib                       = true;

      TGpibParams GpibParams;
      GpibParams.BoardIndex                      = RemoteDriverPf->GpibBoardIndex;
      GpibParams.ControllerInCharge              = false;
      GpibParams.PrimaryAddress                  = RemoteDriverPf->GpibPrimaryAddress;
      GpibParams.SecondaryAddress                = 0;
      GpibParams.Timeout                         = RemoteDriverPf->GpibTimeout;

      InterfaceParams.GpibParams                 = GpibParams;

   }
   else if ( RemoteDriverPf->Ethernet )
   {

      InterfaceParams.Ethernet                   = true;

      TEthernetParams EthernetParams;
      EthernetParams.HostAddress                 = RemoteDriverPf->EthernetHostAddress;
      EthernetParams.PortNum                     = RemoteDriverPf->EthernetPortNum;
      EthernetParams.Server                      = RemoteDriverPf->EthernetServer;

      InterfaceParams.EthernetParams             = EthernetParams;

   }

   Interface_                                    = new TInterface( InterfaceParams );

   return( Interface_->Valid );

}

__fastcall
TCLControl::~TCLControl
   (

   )
{

   delete Interface_;
   Interface_ = NULL;

   ScheduleSignal->Terminate();
   ScheduleSignal->WaitFor();
   delete ScheduleSignal;
   delete VehTruthFile;
   delete MsgCriticalSection_;

}

void
TCLControl::TerminateSim()
{

   SendStop = true;

}

TInMsgArray const
TCLControl::GetInputMsgs
   (
   )
{
   TInMsgArray TmpMsgArray;

   MsgCriticalSection_->Acquire();

   TmpMsgArray.swap(  InMsgArray_ );

   MsgCriticalSection_->Release();

   return( TmpMsgArray );

}

TMsgTrafficArray const
TCLControl::GetMsgTrafficArray
   (
   )
{

   TMsgTrafficArray TmpMsgTrafficArray;

   MsgCriticalSection_->Acquire();

   TmpMsgTrafficArray.swap( MsgTrafficArray_ );

   MsgCriticalSection_->Release();

   return( TmpMsgTrafficArray );

}

void
TCLControl::ProcessInMsg
   (
   const TInMsg            & NewInMsg
   )
{

   ++NumMsgsRcvd_;
   if ( InMsg.MsgId != StelMsgRcptStatMsgId )
   {
      ++NumMsgsRcvdExceptStat_;
   }

   MsgCriticalSection_->Acquire();

   InMsgArray_.push_back( NewInMsg );

   MsgTrafficArray_.push_back( TMsgTraffic( TScenTime::GetTimeMillisec(), InMsg.MsgId, eMSG_SOURCE_SIM ) );

   MsgCriticalSection_->Release();

}

bool const
TCLControl::ShouldSendTrajectory
   (
   )
{

   bool ShouldSend                = false;
   if ( TScenTime::GetTimeMillisec() > ( LastTrajectoryTimeMillisec + TrajectoryDeltaTimeMillisec ) )
   {
      ShouldSend                  = true;
      LastTrajectoryTimeMillisec += TrajectoryDeltaTimeMillisec;
   }

   return( ShouldSend );

}

TGpsTime const
TCLControl::GetUpdateTime
   (
   )
{

   return( FirstTime + ( UpdateIndex++ )*TrajectoryDeltaTimeMillisec/1000.0 );

}

void
TCLControl::ProcessTimeMsg
   (
   const int                 TimeMillisec
   )
{

   LastTrajectoryTimeMillisec = TimeMillisec - 3*TrajectoryDeltaTimeMillisec;

}

void
TCLControl::Send1Traj
   (
   )
{

   TOutMsgQ OutMsgs;


   TStelTrajectory Traj = GetTrajectory();
   OutMsgs.push( TOutMsg( Traj ) );

   CodeSite->SendInteger( AnsiString( TScenTime::GetTimeMillisec() ) + AnsiString( " TCLControl::Send1Traj " ), OutMsgs.size() );

   SendMsgs( OutMsgs );

}


