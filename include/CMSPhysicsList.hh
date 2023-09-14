#ifndef CMSPhysicsList_h
#define CMSPhysicsList_h 1

#include "G4VUserPhysicsList.hh"

class CMSPhysicsList : public G4VUserPhysicsList
{
public:
	CMSPhysicsList();
	virtual ~CMSPhysicsList();

	virtual void ConstructParticle();
        virtual void ConstructProcess();
        virtual void AddTransportation();
        virtual void ElectromagneticPhysics();
        virtual void HadronicPhysics();
	virtual void SetCuts();

	void  ConstructAllBosons();
	void  ConstructAllLeptons();
	void  ConstructAllMesons();
	void  ConstructAllBaryons();
	void  ConstructAllIons();
	void  ConstructAllShortLiveds();

};

#endif
