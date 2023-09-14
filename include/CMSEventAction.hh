#ifndef CMSEventAction_h
#define CMSEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class CMSRunAction;

class CMSEventAction : public G4UserEventAction
{
public:
        CMSEventAction();
        virtual ~CMSEventAction();

        void BeginOfEventAction(const G4Event*);
        void EndOfEventAction(const G4Event*);

};
    
#endif
