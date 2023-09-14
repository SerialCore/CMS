#ifndef CMSDetectorConstruction_h
#define CMSDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;

class CMSDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	CMSDetectorConstruction();
	virtual ~CMSDetectorConstruction();

	virtual G4VPhysicalVolume * Construct();
	G4VPhysicalVolume * ConstructDetector();
	void ConstructMaterials(void);

};

#endif
