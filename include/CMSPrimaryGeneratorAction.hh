#ifndef CMSPrimaryGeneratorAction_h
#define CMSPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

class CMSPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
        CMSPrimaryGeneratorAction();
        virtual ~CMSPrimaryGeneratorAction();

        virtual void GeneratePrimaries(G4Event*);

private:
        G4GeneralParticleSource * fParticleGun;
};

#endif
