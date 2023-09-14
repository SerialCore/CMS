#include "CMSActionInitialization.hh"

#include "CMSPrimaryGeneratorAction.hh"
#include "CMSRunAction.hh"
#include "CMSEventAction.hh"

CMSActionInitialization::CMSActionInitialization()
: G4VUserActionInitialization()
{}

CMSActionInitialization::~CMSActionInitialization()
{}

void CMSActionInitialization::BuildForMaster() const
{
	SetUserAction(new CMSRunAction);
}

void CMSActionInitialization::Build() const
{
	SetUserAction(new CMSPrimaryGeneratorAction);
	SetUserAction(new CMSRunAction);
	SetUserAction(new CMSEventAction);
}

