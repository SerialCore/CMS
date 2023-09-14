#include "CMSDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

CMSDetectorConstruction::CMSDetectorConstruction() 
: G4VUserDetectorConstruction() { ; }
CMSDetectorConstruction::~CMSDetectorConstruction() { ; }

// Material
G4Material * Vacuum;
G4Material * Al6061;
G4Material * Al_Honeycomb;
G4Material * MLImat;
G4Material * Ti_Alloy;
G4Material * AuPt_Alloy;
G4Material * ULEGlass;
G4Material * foam;
G4Material * SiGlass;
G4Material * TiGlass;
G4Material * SHAPAL;
G4Material * SiC;
G4Material * Scell;
G4Material * Molybdenum;
G4Material * Gold;
G4Material * CFRP;
G4Material * carbon;
G4Material * CFRP_Honeycomb;

G4VPhysicalVolume * CMSDetectorConstruction::Construct()
{
	ConstructMaterials();

	return ConstructDetector();
}

G4VPhysicalVolume * CMSDetectorConstruction::ConstructDetector()
{
        // for G4Tubs
        G4double pRMin; //inner R
        G4double pRMax; //outer R
        G4double pDz;  //half of the hight
	G4double pSPhi; //start Phi
	G4double pDPhi; //end Phi

        // for G4Box
        G4double pX; //half of the x
        G4double pY; //half of the y
        G4double pZ; //half of the z

        // rotation of component
        G4RotationMatrix * rotate;

	// Define world volume
	pRMin = 0. * mm;
	pRMax = 1260. * mm;
        pDz = 1000. * mm;
	pSPhi = 0. * deg;
	pDPhi = 360. * deg;

	G4Tubs * World_sol = new G4Tubs("World", pRMin, pRMax, pDz, pSPhi, pDPhi);
	G4LogicalVolume * World_log = new G4LogicalVolume(World_sol, Vacuum, "World");
	G4VPhysicalVolume * World_phys = new G4PVPlacement(0, G4ThreeVector(), World_log, "World", 0, false, 0, true);

        // Define Solar Panels
	pRMin = 1250. * mm;
	pRMax = 1250.5 * mm;
        pDz = 1000. * mm;
	pSPhi = 0. * deg;
	pDPhi = 360. * deg;
        rotate = new G4RotationMatrix();
        rotate->rotateX(90 * deg);

	G4Tubs * Solar_Panels_sol = new G4Tubs("Solar_Panels", pRMin, pRMax, pDz, pSPhi, pDPhi);
	G4LogicalVolume * Solar_Panels_log = new G4LogicalVolume(Solar_Panels_sol, Scell, "Solar_Panels");
	new G4PVPlacement(rotate, G4ThreeVector(), Solar_Panels_log, "Solar_Panels", World_log, false, 0, true);

        // Define Spacecraft
	pRMin = 1240. * mm;
	pRMax = 1250. * mm;
        pDz = 1000. * mm;
	pSPhi = 0. * deg;
	pDPhi = 360. * deg;
        rotate = new G4RotationMatrix();
        rotate->rotateX(90 * deg);

	G4Tubs * Spacecraft_sol = new G4Tubs("Spacecraft", pRMin, pRMax, pDz, pSPhi, pDPhi);
	G4LogicalVolume * Spacecraft_log = new G4LogicalVolume(Spacecraft_sol, CFRP, "Spacecraft");
	new G4PVPlacement(rotate, G4ThreeVector(), Spacecraft_log, "Spacecraft", World_log, false, 0, true);

        // Define Thermal Shield
	pRMin = 1198.2 * mm;
	pRMax = 1240. * mm;
        pDz = 1000. * mm;
	pSPhi = 0. * deg;
	pDPhi = 360. * deg;
        rotate = new G4RotationMatrix();
        rotate->rotateX(90 * deg);

	G4Tubs * Thermal_Shield_sol = new G4Tubs("Thermal_Shield", pRMin, pRMax, pDz, pSPhi, pDPhi);
	G4LogicalVolume * Thermal_Shield_log = new G4LogicalVolume(Thermal_Shield_sol, CFRP, "Thermal_Shield");
	new G4PVPlacement(rotate, G4ThreeVector(), Thermal_Shield_log, "Thermal_Shield", World_log, false, 0, true);

        // Define Upper Deck
	pRMin = 0. * mm;
	pRMax = 1240. * mm;
        pDz = 15. * mm;
	pSPhi = 0. * deg;
	pDPhi = 360. * deg;
        rotate = new G4RotationMatrix();
        rotate->rotateX(90 * deg);

	G4Tubs * Upper_Deck_sol = new G4Tubs("Upper_Deck", pRMin, pRMax, pDz, pSPhi, pDPhi);
	G4LogicalVolume * Upper_Deck_log = new G4LogicalVolume(Upper_Deck_sol, CFRP, "Upper_Deck");
	new G4PVPlacement(rotate, G4ThreeVector(0, 1000, 0), Upper_Deck_log, "Upper_Deck", World_log, false, 0, true);

        // Define Lower Deck
	pRMin = 0. * mm;
	pRMax = 1240. * mm;
        pDz = 15. * mm;
	pSPhi = 0. * deg;
	pDPhi = 360. * deg;
        rotate = new G4RotationMatrix();
        rotate->rotateX(90 * deg);

	G4Tubs * Lower_Deck_sol = new G4Tubs("Lower_Deck", pRMin, pRMax, pDz, pSPhi, pDPhi);
	G4LogicalVolume * Lower_Deck_log = new G4LogicalVolume(Lower_Deck_sol, CFRP, "Lower_Deck");
	new G4PVPlacement(rotate, G4ThreeVector(0, -1000, 0), Lower_Deck_log, "Lower_Deck", World_log, false, 0, true);

        // Define MLI-blanket
	pRMin = 0. * mm;
	pRMax = 1240. * mm;
        pDz = 0.5 * mm;
	pSPhi = 0. * deg;
	pDPhi = 360. * deg;
        rotate = new G4RotationMatrix();
        rotate->rotateX(90 * deg);

	G4Tubs * MLI_blanket_sol = new G4Tubs("MLI-blanket", pRMin, pRMax, pDz, pSPhi, pDPhi);
	G4LogicalVolume * MLI_blanket_log = new G4LogicalVolume(MLI_blanket_sol, MLImat, "MLI-blanket");
	new G4PVPlacement(rotate, G4ThreeVector(0, -1000, 0), MLI_blanket_log, "MLI-blanket", World_log, false, 0, true);

        // Define Payload Shield
	pRMin = 295. * mm;
	pRMax = 300. * mm;
        pDz = 500. * mm;
	pSPhi = 0. * deg;
	pDPhi = 360. * deg;

	G4Tubs * Payload_Shield_sol = new G4Tubs("Payload_Shield", pRMin, pRMax, pDz, pSPhi, pDPhi);
	G4LogicalVolume * Payload_Shield_log = new G4LogicalVolume(Payload_Shield_sol, CFRP, "Payload_Shield");
	new G4PVPlacement(0, G4ThreeVector(), Payload_Shield_log, "Payload_Shield", World_log, false, 0, true);

        // Define Optical Bench
        pX = 175. * mm;
        pY = 100. * mm;
        pZ = 20. * mm;

	G4Box * Optical_Bench_sol = new G4Box("Optical_Bench", pX, pY, pZ);
	G4LogicalVolume * Optical_Bench_log = new G4LogicalVolume(Optical_Bench_sol, ULEGlass, "Optical_Bench");
	new G4PVPlacement(0, G4ThreeVector(), Optical_Bench_log, "Optical_Bench", World_log, false, 0, true);

        // Define Ti House
	pRMin = 57.5 * mm;
	pRMax = 62.5 * mm;
        pDz = 112. * mm;
	pSPhi = 0. * deg;
	pDPhi = 360. * deg;
        rotate = new G4RotationMatrix();
        rotate->rotateX(90 * deg);

	G4Tubs * Ti_House_sol = new G4Tubs("Ti_House", pRMin, pRMax, pDz, pSPhi, pDPhi);
	G4LogicalVolume * Ti_House_log = new G4LogicalVolume(Ti_House_sol, Ti_Alloy, "Ti_House");
	new G4PVPlacement(rotate, G4ThreeVector(), Ti_House_log, "Ti_House", World_log, false, 0, true);

        // Define Mo House
        pX = 37.5 * mm;
        pY = 37.5 * mm;
        pZ = 37.5 * mm;

	G4Box * Mo_House_sol = new G4Box("Mo_House", pX, pY, pZ);
	G4LogicalVolume * Mo_House_log = new G4LogicalVolume(Mo_House_sol, Molybdenum, "Mo_House");
	new G4PVPlacement(0, G4ThreeVector(), Mo_House_log, "Mo_House", World_log, false, 0, true);

        // Define Test Mass
        pX = 25. * mm;
        pY = 25. * mm;
        pZ = 17.5 * mm;

	G4Box * Test_Mass_sol = new G4Box("Test_Mass", pX, pY, pZ);
	G4LogicalVolume * Test_Mass_log = new G4LogicalVolume(Test_Mass_sol, AuPt_Alloy, "Test_Mass");
	new G4PVPlacement(0, G4ThreeVector(), Test_Mass_log, "Test_Mass", World_log, false, 0, true);

        // Define Plate
	pRMin = 0. * mm;
	pRMax = 175. * mm;
        pDz = 5. * mm;
	pSPhi = 0. * deg;
	pDPhi = 360. * deg;

	G4Tubs * Plate_sol = new G4Tubs("Plate", pRMin, pRMax, pDz, pSPhi, pDPhi);
	G4LogicalVolume * Plate_log = new G4LogicalVolume(Plate_sol, CFRP, "Plate");
	new G4PVPlacement(0, G4ThreeVector(), Plate_log, "Plate", World_log, false, 0, true);

        // Define Telescope Shield
	pRMin = 280. * mm;
	pRMax = 285. * mm;
        pDz = 430. * mm;
	pSPhi = 0. * deg;
	pDPhi = 360. * deg;

	G4Tubs * Telescope_Shield_sol = new G4Tubs("Telescope_Shield", pRMin, pRMax, pDz, pSPhi, pDPhi);
	G4LogicalVolume * Telescope_Shield_log = new G4LogicalVolume(Telescope_Shield_sol, CFRP, "Telescope_Shield");
	new G4PVPlacement(0, G4ThreeVector(), Telescope_Shield_log, "Telescope_Shield", World_log, false, 0, true);

        // Define PCDU
        pX = 175. * mm;
        pY = 100. * mm;
        pZ = 150. * mm;

	G4Box * PCDU_sol = new G4Box("PCDU", pX, pY, pZ);
	G4LogicalVolume * PCDU_log = new G4LogicalVolume(PCDU_sol, Al6061, "PCDU");
	new G4PVPlacement(0, G4ThreeVector(-100, -300, -900), PCDU_log, "PCDU", World_log, false, 0, true);

        // Define Transponser
        pX = 110. * mm;
        pY = 92. * mm;
        pZ = 89. * mm;

	G4Box * Transponser_sol = new G4Box("Transponser", pX, pY, pZ);
	G4LogicalVolume * Transponser_log = new G4LogicalVolume(Transponser_sol, Al6061, "Transponser");
	new G4PVPlacement(0, G4ThreeVector(-600, -500, -900), Transponser_log, "Transponser", World_log, false, 0, true);

        // Define CPS
        pX = 120. * mm;
        pY = 178. * mm;
        pZ = 70. * mm;

	G4Box * CPS_sol = new G4Box("CPS", pX, pY, pZ);
	G4LogicalVolume * CPS_log = new G4LogicalVolume(CPS_sol, Al6061, "CPS");
	new G4PVPlacement(0, G4ThreeVector(-800, -300, -500), CPS_log, "CPS", World_log, false, 0, true);

        // Define Interferometer
        pX = 100. * mm;
        pY = 100. * mm;
        pZ = 75. * mm;

	G4Box * Interferometer_sol = new G4Box("Interferometer", pX, pY, pZ);
	G4LogicalVolume * Interferometer_log = new G4LogicalVolume(Interferometer_sol, Al6061, "Interferometer");
	new G4PVPlacement(0, G4ThreeVector(), Interferometer_log, "Interferometer", World_log, false, 0, true);

        // Define Gyroscope
	pRMin = 0. * mm;
	pRMax = 42.5 * mm;
        pDz = 44.5 * mm;
	pSPhi = 0. * deg;
	pDPhi = 360. * deg;

	G4Tubs * Gyroscope_sol = new G4Tubs("Gyroscope", pRMin, pRMax, pDz, pSPhi, pDPhi);
	G4LogicalVolume * Gyroscope_log = new G4LogicalVolume(Gyroscope_sol, Al6061, "Gyroscope");
	new G4PVPlacement(0, G4ThreeVector(300, -500, -300), Gyroscope_log, "Gyroscope", World_log, false, 0, true);

        // Define RFDU
        pX = 80. * mm;
        pY = 30. * mm;
        pZ = 40. * mm;

	G4Box * RFDU_sol = new G4Box("RFDU", pX, pY, pZ);
	G4LogicalVolume * RFDU_log = new G4LogicalVolume(RFDU_sol, Al6061, "RFDU");
	new G4PVPlacement(0, G4ThreeVector(500, 100, -300), RFDU_log, "RFDU", World_log, false, 0, true);

	return World_phys;
}

void CMSDetectorConstruction::ConstructMaterials(void)
{
	// Elements
        G4Element * Al = new G4Element("Aluminium", "Al", 13., 26.98 * g / mole);
        G4Element * Mg = new G4Element("Magnesium", "Mg", 12., 24.31 * g / mole);
        G4Element * Si = new G4Element("Silicon", "Si", 14., 28.09 * g / mole);
        G4Element * Fe = new G4Element("Iron", "Fe", 26., 55.85 * g / mole);
        G4Element * Ti = new G4Element("Titanium", "Ti", 22., 47.87 * g / mole);
        G4Element * V = new G4Element("Vanadium", "V", 23., 50.94 * g / mole);
        G4Element * Au = new G4Element("Gold", "Au", 79., 196.97 * g / mole);
        G4Element * Pt = new G4Element("Platium", "Pt", 78., 195.08 * g / mole);
        G4Element * Mo = new G4Element("Molybdenum", "Mo", 42., 95.96 * g / mole);
        G4Element * C = new G4Element("Carbon", "C", 6., 12.01 * g / mole);
        G4Element * H = new G4Element("Hydrogen", "H", 1., 1.01 * g / mole);
        G4Element * O = new G4Element("Oxygen", "O", 8., 16.00 * g / mole);
        G4Element * N = new G4Element("Nitrogen", "N", 7., 14.01 * g / mole);

        // Materials
        Vacuum = new G4Material("Vacuum", 1, 1.00794 * g / mole, 1.0E-25 * g / cm3, kStateGas, 0.1 * kelvin, 1.0E-19 * pascal);

        Al6061 = new G4Material("Al6061", 2.70 * g / cm3, 4);
        Al6061->AddElement(Al, 0.98);
        Al6061->AddElement(Mg, 0.01);
        Al6061->AddElement(Si, 0.006);
        Al6061->AddElement(Fe, 0.004);

        Al_Honeycomb = new G4Material("Al_Honeycomb", 0.05 * g / cm3, 4);
        Al_Honeycomb->AddElement(Al, 0.98);
        Al_Honeycomb->AddElement(Mg, 0.001);
        Al_Honeycomb->AddElement(Si, 0.006);
        Al_Honeycomb->AddElement(Fe, 0.004);

        MLImat = new G4Material("MLImat", 1.40 * g / cm3, 3);
        MLImat->AddElement(H, 0.041958);
        MLImat->AddElement(C, 0.625017);
        MLImat->AddElement(O, 0.333025);

        Ti_Alloy = new G4Material("Ti_Alloy", 4.43 * g / cm3, 3);
        Ti_Alloy->AddElement(Ti, 0.90);
        Ti_Alloy->AddElement(Al, 0.06);
        Ti_Alloy->AddElement(V, 0.04);

        AuPt_Alloy = new G4Material("AuPt_Alloy", 19.92 * g / cm3, 2);
        AuPt_Alloy->AddElement(Au, 0.70);
        AuPt_Alloy->AddElement(Pt, 0.30);

        foam = new G4Material("foam", 0.05 * g / cm3, 2);
        foam->AddElement(C, 0.90);
        foam->AddElement(H, 0.10);

        SiGlass = new G4Material("SiGlass", 2.20 * g / cm3, 2);
        SiGlass->AddElement(O, 2);
        SiGlass->AddElement(Si, 1);

        TiGlass = new G4Material("TiGlass", 4.25 * g / cm3, 2);
        TiGlass->AddElement(O, 2);
        TiGlass->AddElement(Ti, 1);

        ULEGlass = new G4Material("ULE_Glass", 2.21 * g / cm3, 2);
        ULEGlass->AddMaterial(SiGlass, 0.925);
        ULEGlass->AddMaterial(TiGlass, 0.075);

        SHAPAL = new G4Material("SHAPAL", 2.90 * g / cm3, 2);
        SHAPAL->AddElement(Al, 2);
        SHAPAL->AddElement(N, 1);

        SiC = new G4Material("SiC", 3.10 * g / cm3, 2);
        SiC->AddElement(Si, 1);
        SiC->AddElement(C, 1);

        Scell = new G4Material("Scell", 7.82 * g / cm3, 1);
        Scell->AddElement(Si, 1);

        Molybdenum = new G4Material("Molybdenum", 10.22 * g / cm3, 1);
        Molybdenum->AddElement(Mo, 1);

        Gold = new G4Material("Gold", 19.32 * g / cm3, 1);
        Gold->AddElement(Au, 1);

        CFRP = new G4Material("CFRP", 1.66 * g / cm3, 1);
        CFRP->AddElement(C, 1);

        carbon = new G4Material("carbon", 2.10 * g / cm3, 1);
        carbon->AddElement(C, 1);

        CFRP_Honeycomb = new G4Material("CFRP_Honeycomb", 0.05 * g / cm3, 1);
        CFRP_Honeycomb->AddElement(C, 1);

}
