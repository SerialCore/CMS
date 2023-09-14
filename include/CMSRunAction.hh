#ifndef CMSRunAction_h
#define CMSRunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"

class G4Run;

class CMSRunAction : public G4UserRunAction
{
public:
        CMSRunAction();
        virtual ~CMSRunAction();

        void BeginOfRunAction(const G4Run* aRun);
        void EndOfRunAction(const G4Run* aRun);

};

#endif
