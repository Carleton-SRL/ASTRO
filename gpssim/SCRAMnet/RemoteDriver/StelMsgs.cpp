#include "pch.h"
#pragma hdrstop

#include "StelMsgs.h"


//-----------------------------------------------------------------------------
// Output Messages
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// TStelMsgRcptnStatMsg
//

TStelMsgRcptnStatMsg::TStelMsgRcptnStatMsg
   (
   ) :
   RcvdMsgId( 0 ),
   Status( 0 )
{
}

TStelMsgRcptnStatMsg::TStelMsgRcptnStatMsg
   (
   const TInMsg &InMsg
   )
{
   (*this) = InMsg;
}

TStelMsgRcptnStatMsg &
TStelMsgRcptnStatMsg::operator=
   (
   const TInMsg &InMsg
   )
{

   TMsgData MsgData = InMsg.MsgData;
   RcvdMsgId        = MsgData[2];
   Status           = MsgData[3];

   return( *this );

}
bool const
TStelMsgRcptnStatMsg::IsMsgChecksumValid() const
{
   return( !(Status & 0x01) );
}
bool const
TStelMsgRcptnStatMsg::IsResourceOwnershipValid() const
{
   return( !(Status & 0x02) );
}
bool const
TStelMsgRcptnStatMsg::IsSimulationModeValid() const
{
   return( !(Status & 0x04) );
}
bool const
TStelMsgRcptnStatMsg::IsMsgIdValid() const
{
   return( !(Status & 0x08) );
}
bool const
TStelMsgRcptnStatMsg::IsMsgSizeValid() const
{
   return( !(Status & 0x10) );
}

//-----------------------------------------------------------------------------
// TStelTime
// 0xFE
//

TStelTimeMsg::TStelTimeMsg
   (
   const TInMsg            & InMsg
   )
{
   ( *this ) = InMsg;
}

TStelTimeMsg &
TStelTimeMsg::operator=
   (
   const TInMsg            & InMsg
   )
{

   TMsgBody MsgBody = InMsg.MsgBody;

   TimeMillisec_    = (int) *( &MsgBody[0] );

   return( *this );

}


//-----------------------------------------------------------------------------
// TStelSvLookAngle
//
TStelSvLookAngle::TStelSvLookAngle
   (
   const TInMsg &InMsg
   )
{
   ( *this ) = InMsg;
}

TStelSvLookAngle &
TStelSvLookAngle::operator=
   (
   const TInMsg &InMsg
   )
{

   TMsgBody MsgBody = InMsg.MsgBody;

   CurSystemTime    = (unsigned int) *( &MsgBody[0] );

   int NumChannels  = ( MsgBody.size()-5 )/4;

   int Index        = 4;

   for ( int i=0; i<NumChannels; ++i )
   {

      int Chan      = MsgBody[Index++];
      int Svid      = MsgBody[Index++];
      double El     = ScaleEl( MsgBody[Index++] );
      double Az     = ScaleAz( MsgBody[Index++] );

      TSvLookAngle SvLookAngle( Chan, Svid, El, Az );

      SvLookAngleArray.push_back( SvLookAngle );

   }

   NewEph = MsgBody[Index] != 0;

   return( *this );

}
double const
TStelSvLookAngle::ScaleEl
   (
   unsigned char UnScaledEl
   )
{
   return( ( -75.0 + (double) UnScaledEl )*0.5 );
}
double const
TStelSvLookAngle::ScaleAz
   (
   unsigned char UnScaledAz
   )
{
   return( ( (double) UnScaledAz )*360.0/256.0 );
}



//-----------------------------------------------------------------------------
// Output Messages
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// TStelInitSim
//

TStelInitSim::TStelInitSim
   (
   const TVehTruthRec &InVehTruthRec
   ) :
   Init( InVehTruthRec )
{
   (*this) = InVehTruthRec;
}

TStelInitSim &
TStelInitSim::operator=
   (
   const TVehTruthRec &InVehTruthRec
   )
{

   MsgId = StelInitSimMsgId;
   Init  = InVehTruthRec;

   MsgBody.resize( SizeInitSimBody );

   MsgBody[0] = 0; // Trajectory mode

   unsigned long  Time = Init.GpsTime.Seconds;
   unsigned short Week = (unsigned short) Init.GpsTime.Week;
   memcpy( &MsgBody[1], &Time, sizeof( Time ) );
   memcpy( &MsgBody[5], &Week, sizeof( Week ) );

   long Posx = Init.PosEcef[0]*100;
   long Posy = Init.PosEcef[1]*100;
   long Posz = Init.PosEcef[2]*100;
   memcpy( &MsgBody[7],  &Posx, sizeof( Posx ) );
   memcpy( &MsgBody[11], &Posy, sizeof( Posy ) );
   memcpy( &MsgBody[15], &Posz, sizeof( Posz ) );

   return( *this );

}


//-----------------------------------------------------------------------------
// TStelTrajectory
//

TStelTrajectory::TStelTrajectory
   (
   const TVehTruthRec &InVehTruthRec
   ) :
   Truth( InVehTruthRec )
{
   (*this) = InVehTruthRec;
}

TStelTrajectory &
TStelTrajectory::operator=
   (
   const TVehTruthRec &InVehTruthRec
   )
{

   MsgId                   = StelTrajectoryProfileMsgId;
   Truth = InVehTruthRec;

   MsgBody.resize( SizeTrajectoryBody );

   unsigned long Time      = (unsigned long)( ( Truth.GpsTime.Seconds )*1000 );
   memcpy( &MsgBody[0], &Time, sizeof( Time ) );

   long Posx               = Truth.PosEcef[0]*100;
   long Posy               = Truth.PosEcef[1]*100;
   long Posz               = Truth.PosEcef[2]*100;
   memcpy( &MsgBody[4],  &Posx, sizeof( Posx ) );
   memcpy( &MsgBody[8],  &Posy, sizeof( Posy ) );
   memcpy( &MsgBody[12], &Posz, sizeof( Posz ) );

   long Velx               = Truth.VelEcef[0]*1e5;
   long Vely               = Truth.VelEcef[1]*1e5;
   long Velz               = Truth.VelEcef[2]*1e5;
   memcpy( &MsgBody[16], &Velx, sizeof( Velx ) );
   memcpy( &MsgBody[20], &Vely, sizeof( Vely ) );
   memcpy( &MsgBody[24], &Velz, sizeof( Velz ) );

   short Accx              = Truth.AccEcef[0]*1e2;
   short Accy              = Truth.AccEcef[1]*1e2;
   short Accz              = Truth.AccEcef[2]*1e2;
   memcpy( &MsgBody[28], &Accx, sizeof( Accx ) );
   memcpy( &MsgBody[30], &Accy, sizeof( Accy ) );
   memcpy( &MsgBody[32], &Accz, sizeof( Accz ) );

   short Jrkx              = Truth.JerkEcef[0]*1e2;
   short Jrky              = Truth.JerkEcef[1]*1e2;
   short Jrkz              = Truth.JerkEcef[2]*1e2;
   memcpy( &MsgBody[34], &Jrkx, sizeof( Jrkx ) );
   memcpy( &MsgBody[36], &Jrky, sizeof( Jrky ) );
   memcpy( &MsgBody[38], &Jrkz, sizeof( Jrkz ) );

   return( *this );

}

//-----------------------------------------------------------------------------
// TStelDataExtractionReq
// 19

TStelDataExtractionReq::TStelDataExtractionReq
   (
   const bool                DataExtractionEnabled
   )
{

   MsgId = StelDataExtractionReqMsgId;

   MsgBody.clear();
   MsgBody.push_back( DataExtractionEnabled );

}   


//-----------------------------------------------------------------------------
// TStelStop
// 22

TStelStop::TStelStop
   (
   )
{

   MsgId = StelStopSimulationMsgId;

}


//-----------------------------------------------------------------------------
// TStelChannelAssignment
// 51
//

TStelChannelAssignment::TStelChannelAssignment
   (
   const TStelChanAssignData & InChanAssignData
   )
{
   ( *this ) = InChanAssignData;
}


TStelChannelAssignment &
TStelChannelAssignment::operator=
   (
   const TStelChanAssignData & InChanAssignData
   )
{

   ChanAssignData_ = InChanAssignData;
   MsgId           = StelChannelAssignmentMsgId;

   MsgBody.clear();

   unsigned char ucChanAssignFunc;
   unsigned char Byte3;
   if ( ChanAssignData_.ChanAssignFunc.DeassignChanA )
   {
      ucChanAssignFunc = 1;
      Byte3            = ( unsigned char ) 0;
   }
   else if ( ChanAssignData_.ChanAssignFunc.SwapChanAChanB )
   {
      ucChanAssignFunc = 2;
      Byte3            = ( unsigned char ) ChanAssignData_.ChanB;
   }
   else
   {
      ucChanAssignFunc = 3;
      Byte3            = ( unsigned char ) ChanAssignData_.Svid;
   }

   MsgBody.push_back( ucChanAssignFunc );

   MsgBody.push_back( ChanAssignData_.ChanA );

   MsgBody.push_back( Byte3 );

   return( *this );

}

//-----------------------------------------------------------------------------
// TStelChannelMode
// 2
//





