#ifndef ThreadInfH
#define ThreadInfH

#pragma pack(push,1)


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// Thread priorities
//
static const TThreadPriority PriorityLLCtrl    = tpTimeCritical;

static const TThreadPriority PriorityPseudo    = tpHighest;
static const TThreadPriority PrioritySatMotion = tpHighest;
static const TThreadPriority PriorityRtMsg     = tpHighest;

static const TThreadPriority PriorityComIn     = tpHigher;
static const TThreadPriority PriorityRcvr      = tpHigher;
static const TThreadPriority PriorityComOut    = tpHigher;
static const TThreadPriority PrioritySatSelect = tpHigher;
static const TThreadPriority PriorityAuxSensor = tpHigher;

static const TThreadPriority PriorityComBuf    = tpNormal;

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
//   TTpThreadInfo
//
// Sets the name of a thread.  Must be instantiated within the "Execute" method
// of a thread, as the constructor is still executing in the context of the
// calling thread.
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

class TThreadInf {

private:

typedef struct tagTHREADNAME_INFO
{
   DWORD dwType;     // must be 0x1000
   LPCSTR szName;    // pointer to name (in user addr space)
   DWORD dwThreadID; // thread ID (-1=caller thread)
   DWORD dwFlags;    // reserved for future use, must be zero
} THREADNAME_INFO;

public:

   THREADNAME_INFO ThreadNameInfo;


   TThreadInf( const AnsiString & ThreadName )
   {
      ThreadNameInfo.dwType     = 0x1000;
      ThreadNameInfo.szName     = ThreadName.c_str();
      ThreadNameInfo.dwThreadID = -1;
      ThreadNameInfo.dwFlags    = 0;

      __try
      {
          RaiseException( 0x406D1388, 0, sizeof(ThreadNameInfo)/sizeof(DWORD),(DWORD*)&ThreadNameInfo );
      }
      __except (EXCEPTION_CONTINUE_EXECUTION)
      {
      }

   }

};

#pragma pack(pop)

#endif

