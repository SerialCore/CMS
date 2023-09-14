#include "CMSEventAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4ios.hh"

CMSEventAction::CMSEventAction()
: G4UserEventAction()
{;}

CMSEventAction::~CMSEventAction(){;}

void CMSEventAction::BeginOfEventAction(const G4Event* )
{

}

void CMSEventAction::EndOfEventAction(const G4Event* event)
{
        // periodic printing
        G4int eventID = event->GetEventID();
        if ( eventID < 100 || eventID % 1000 == 0)
        {
                G4cout << ">>> Event: " << eventID  << G4endl;
        }
}

