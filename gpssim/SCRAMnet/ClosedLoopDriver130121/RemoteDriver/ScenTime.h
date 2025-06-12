#ifndef ScenTimeH
#define ScenTimeH

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

#ifndef ScheduleH
#include "Schedule.h"
#endif

class TScenTime {

private:

   static int                TimeMillisec_;

public:

   TScenTime()
   {
   }

   static void
   SetTimeMillisec
      (
      const long InTimeMillisec
      )
   {
      TimeMillisec_ = InTimeMillisec;
   };

   static long const
   GetTimeMillisec
      (
      )
   {
      TimeMillisec_ = TScheduleSignal::GetTimeMillisec();
      return( TimeMillisec_ );
   };

};

#endif