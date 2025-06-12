#include "pch.h"
#pragma hdrstop

#include "Utilities.h"


///////////////////////////////////////////////////////////////////////////////
// IsValidScenario
//   This function returns true if the given scenario is valid.
///////////////////////////////////////////////////////////////////////////////
bool const
IsValidScenario
   (
   const AnsiString &ScenarioRoot
   )
{
   char CurrentDir[MAX_PATH];
   bool CurrentDirValid = (getcwd(CurrentDir,MAX_PATH) != NULL);
   chdir(ScenarioRoot.c_str());
   ifstream ValidBuild("ValidBld.scn");
   int ValidScen=0;
   ValidBuild >> ValidScen;
   if ( CurrentDirValid )
   {
      chdir(CurrentDir);
   }
   ValidBuild.close();
   return(ValidScen != 0 && ValidBuild.good());
}


 