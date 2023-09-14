#include "CMSRunAction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"

CMSRunAction::CMSRunAction()
: G4UserRunAction()
{
}

CMSRunAction::~CMSRunAction()
{;}

void CMSRunAction::BeginOfRunAction(const G4Run* )
{
}

void CMSRunAction::EndOfRunAction(const G4Run* )
{

}
