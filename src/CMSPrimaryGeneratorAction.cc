#include "CMSPrimaryGeneratorAction.hh"

#include "G4GeneralParticleSource.hh"

CMSPrimaryGeneratorAction::CMSPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction()
{
        fParticleGun  = new G4GeneralParticleSource();
}

CMSPrimaryGeneratorAction::~CMSPrimaryGeneratorAction()
{
        delete fParticleGun;
}

void CMSPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
        G4int iEvent = anEvent->GetEventID() ;
        if ( iEvent == 0 )
        {
        G4cout << fParticleGun->GetParticleDefinition()->GetParticleName()           << " " ;
        G4cout << fParticleGun->GetCurrentSource()->GetEneDist()->GetEnergyDisType() << " " ;
        G4cout << fParticleGun->GetCurrentSource()->GetPosDist()->GetPosDisType()    << G4endl ;
        }
        fParticleGun->GeneratePrimaryVertex(anEvent);
}
