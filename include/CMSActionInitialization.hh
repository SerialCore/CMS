#ifndef CMSActionInitialization_h
#define CMSActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class CMSActionInitialization : public G4VUserActionInitialization
{
public:
	CMSActionInitialization();
	virtual ~CMSActionInitialization();

	virtual void BuildForMaster() const;
	virtual void Build() const;
};

#endif

