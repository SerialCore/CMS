// 首先调用物理过程的库函数和基本粒子的库函数
#include "CMSPhysicsList.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4ios.hh"
#include <iomanip>

// 定义物理过程的类别：并给出它的Verbose级别
CMSPhysicsList::CMSPhysicsList() : G4VUserPhysicsList()
{
        SetVerboseLevel(1);
}

CMSPhysicsList::~CMSPhysicsList()
{
}

// 调用Geant4定义的六类粒子库函数
#include "G4LeptonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4ShortLivedConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4Proton.hh"

void CMSPhysicsList::ConstructParticle()
{
        // In this method, static member functions should be called
        // for all particles which you want to use.
        // This ensures that objects of these particle types will be
        // created in the program. 

        // and what we should learn is once we execute the gps command,
        // the proton will be contained in the particle list, instead of
        // aborting for the unknowned particle input. That is the reason
        // why we should separate the particle construct functions within
        // the ConstructParticle() just like ConstructProcess() case.
        // The principle maybe due to the virtual functions in G4VUserPhysicsList.
        ConstructAllBosons();
        ConstructAllLeptons();
        ConstructAllMesons();
        ConstructAllBaryons();
        ConstructAllIons();
        ConstructAllShortLiveds();
}

void CMSPhysicsList::ConstructAllBosons()
{
        // Construct all bosons
        G4BosonConstructor pConstructor;
        pConstructor.ConstructParticle();
}

void CMSPhysicsList::ConstructAllLeptons()
{
        // Construct all leptons
        G4LeptonConstructor pConstructor;
        pConstructor.ConstructParticle();
}

void CMSPhysicsList::ConstructAllMesons()
{
        //  Construct all mesons
        G4MesonConstructor pConstructor;
        pConstructor.ConstructParticle();
}

void CMSPhysicsList::ConstructAllBaryons()
{
        //  Construct all barions
        G4BaryonConstructor pConstructor;
        pConstructor.ConstructParticle();
}

void CMSPhysicsList::ConstructAllIons()
{
        //  Construct light ions
        G4IonConstructor pConstructor;
        pConstructor.ConstructParticle();  
}

void CMSPhysicsList::ConstructAllShortLiveds()
{
        //  Construct  resonaces and quarks
        G4ShortLivedConstructor pConstructor;
        pConstructor.ConstructParticle();  
}

void CMSPhysicsList::ConstructProcess()
{
        AddTransportation();

	ElectromagneticPhysics();

	HadronicPhysics();
}

// Transportation
void CMSPhysicsList::AddTransportation()
{
	G4VUserPhysicsList::AddTransportation();
}

#include "G4RayleighScattering.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4hMultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hIonisation.hh"

void CMSPhysicsList::ElectromagneticPhysics()
{
        auto theParticleIterator = GetParticleIterator();
	theParticleIterator->reset();
	while ((*theParticleIterator)())
	{
		G4ParticleDefinition * particle = theParticleIterator->value();
		G4ProcessManager * pmanager = particle->GetProcessManager();
		G4String particleName = particle->GetParticleName();
		G4String particleType = particle->GetParticleType();
		G4double particleCharge = particle->GetPDGCharge();
		if (particleName == "gamma")
		{
			//pmanager->AddDiscreteProcess(new G4RayleighScattering());

                        pmanager->AddDiscreteProcess(new G4GammaConversion());
                        pmanager->AddDiscreteProcess(new G4ComptonScattering());
			pmanager->AddDiscreteProcess(new G4PhotoElectricEffect());
		}
		else if (particleName == "e—")
		{
			pmanager->AddProcess(new G4eMultipleScattering(), -1, 1, 1);
			pmanager->AddProcess(new G4eIonisation(), -1, 2, 2);
			pmanager->AddProcess(new G4eBremsstrahlung(), -1, -1, 3);
		}
		else if (particleName == "e+")
		{
			pmanager->AddProcess(new G4eMultipleScattering(), -1, 1, 1);
			pmanager->AddProcess(new G4eIonisation(), -1, 2, 2);
			pmanager->AddProcess(new G4eBremsstrahlung(), -1, -1, 3);
			pmanager->AddProcess(new G4eplusAnnihilation(), 0, -1, 4);
		}
		else if (particleName == "mu+" || particleName == "mu-")
		{
			pmanager->AddProcess(new G4MuMultipleScattering(), -1, 1, 1);
			pmanager->AddProcess(new G4MuIonisation(), -1, 2, 2);
			pmanager->AddProcess(new G4MuBremsstrahlung(), -1, -1, 3);
			pmanager->AddProcess(new G4MuPairProduction(), -1, -1, 4);
		}
		else if (particleName == "GenericIon")
		{
			pmanager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
			pmanager->AddProcess(new G4hIonisation(), -1, 2, 2);
		}
		else if (!particle->IsShortLived() && particleCharge != 0.0 && particleName != "chargedgeantino")
		{
			// 其他所有稳定的带电粒子
			pmanager->AddProcess(new G4hMultipleScattering(), -1, 1, 1);
			pmanager->AddProcess(new G4hIonisation(), -1, 2, 2);
		}
	}
}

// Hadron Processes
#include "G4HadronElasticProcess.hh"
//#include "G4HadronFissionProcess.hh"
//#include "G4HadronCaptureProcess.hh"

//#include "G4PionPlusInelasticProcess.hh"
//#include "G4PionMinusInelasticProcess.hh"
//#include "G4KaonPlusInelasticProcess.hh"
//#include "G4KaonZeroSInelasticProcess.hh"
//#include "G4KaonZeroLInelasticProcess.hh"
//#include "G4KaonMinusInelasticProcess.hh"
//#include "G4ProtonInelasticProcess.hh"
//#include "G4AntiProtonInelasticProcess.hh"
//#include "G4NeutronInelasticProcess.hh"
//#include "G4AntiNeutronInelasticProcess.hh"
//#include "G4LambdaInelasticProcess.hh"
//#include "G4AntiLambdaInelasticProcess.hh"
//#include "G4SigmaPlusInelasticProcess.hh"
//#include "G4SigmaMinusInelasticProcess.hh"
//#include "G4AntiSigmaPlusInelasticProcess.hh"
//#include "G4AntiSigmaMinusInelasticProcess.hh"
//#include "G4XiZeroInelasticProcess.hh"
//#include "G4XiMinusInelasticProcess.hh"
//#include "G4AntiXiZeroInelasticProcess.hh"
//#include "G4AntiXiMinusInelasticProcess.hh"
//#include "G4DeuteronInelasticProcess.hh"
//#include "G4TritonInelasticProcess.hh"
//#include "G4AlphaInelasticProcess.hh"
//#include "G4OmegaMinusInelasticProcess.hh"
//#include "G4AntiOmegaMinusInelasticProcess.hh"

// Low-energy Models
#include "G4HadronElastic.hh"
#include "G4NeutronRadCapture.hh"
#include "G4LFission.hh"

// -- generator models
#include "G4TheoFSGenerator.hh"
#include "G4ExcitationHandler.hh"
#include "G4CompetitiveFission.hh"
#include "G4GeneratorPrecompoundInterface.hh"
#include "G4Fancy3DNucleus.hh"
#include "G4CascadeInterface.hh"
#include "G4StringModel.hh"
#include "G4PreCompoundModel.hh"
#include "G4FTFModel.hh"
#include "G4QGSMFragmentation.hh"
#include "G4LundStringFragmentation.hh"
#include "G4ExcitedStringDecay.hh"
#include "G4QMDReaction.hh"
#include "G4BinaryLightIonReaction.hh"

// Cross sections
#include "G4IonsShenCrossSection.hh"
//#include "G4TripathiCrossSection.hh"
//#include "G4TripathiLightCrossSection.hh"

void CMSPhysicsList::HadronicPhysics()
{
        G4cout << "Hadronic Physics" << G4endl;

        // this will be the model class for high energies
        G4TheoFSGenerator* theTheoModel = new G4TheoFSGenerator();
        G4TheoFSGenerator* antiBHighEnergyModel = new G4TheoFSGenerator();

        // Evaporation logic
        G4ExcitationHandler* theHandler = new G4ExcitationHandler();
        theHandler->SetMinEForMultiFrag(3*MeV);

        // Pre equilibrium stage 
        G4PreCompoundModel* thePreEquilib = new G4PreCompoundModel(theHandler);
        thePreEquilib->SetMaxEnergy(70*MeV);

        // a no-cascade generator-precompound interaface
        G4GeneratorPrecompoundInterface* theCascade = new G4GeneratorPrecompoundInterface();
        theCascade->SetDeExcitation(thePreEquilib);  

        // Bertini cascade
        G4CascadeInterface* bertini = new G4CascadeInterface();
        bertini->SetMaxEnergy(22*MeV);

        // here come the high energy parts
        G4VPartonStringModel* theStringModel;
        theStringModel = new G4FTFModel();
        theTheoModel->SetTransport(theCascade);
        theTheoModel->SetHighEnergyGenerator(theStringModel);
        theTheoModel->SetMinEnergy(0.1*GeV);
        theTheoModel->SetMaxEnergy(100*TeV);

        G4VLongitudinalStringDecay* theFragmentation = new G4QGSMFragmentation();
        G4ExcitedStringDecay* theStringDecay = new G4ExcitedStringDecay(theFragmentation);
        theStringModel->SetFragmentationModel(theStringDecay);

        // high energy model for anti-baryons
        antiBHighEnergyModel = new G4TheoFSGenerator("ANTI-FTFP");
        G4FTFModel* antiBStringModel = new G4FTFModel();
        G4ExcitedStringDecay* stringDecay = new G4ExcitedStringDecay(new G4LundStringFragmentation());
        antiBStringModel->SetFragmentationModel(stringDecay);

        G4GeneratorPrecompoundInterface* antiBCascade = new G4GeneratorPrecompoundInterface();
        G4PreCompoundModel* preEquilib = new G4PreCompoundModel(new G4ExcitationHandler());
        antiBCascade->SetDeExcitation(preEquilib);

        antiBHighEnergyModel->SetTransport(antiBCascade);
        antiBHighEnergyModel->SetHighEnergyGenerator(antiBStringModel);
        antiBHighEnergyModel->SetMinEnergy(0.0);
        antiBHighEnergyModel->SetMaxEnergy(20*TeV);

        // Light ion models
        G4BinaryLightIonReaction* binaryCascade = new G4BinaryLightIonReaction();
        binaryCascade->SetMinEnergy(0.0);
        binaryCascade->SetMaxEnergy(110*MeV);

        G4QMDReaction* qmd = new G4QMDReaction();
        qmd->SetMinEnergy(100*MeV);
        qmd->SetMaxEnergy(10*GeV);

        G4IonsShenCrossSection* shenXS = new G4IonsShenCrossSection();
        //G4TripathiCrossSection* tripXS = new G4TripathiCrossSection();
        //G4TripathiLightCrossSection* tripLightXS = new G4TripathiLightCrossSection();

        // Elastic process
        G4HadronElasticProcess* theElasticProcess = new G4HadronElasticProcess();
        G4HadronElastic* theElasticModel = new G4HadronElastic();
        theElasticProcess->RegisterMe(theElasticModel);

        auto particleIterator=GetParticleIterator();
        particleIterator->reset();
        while ((*particleIterator)())
        {
                G4ParticleDefinition* particle = particleIterator->value();
                G4ProcessManager* pmanager = particle->GetProcessManager();
                G4String particleName = particle->GetParticleName();
/*
                if (particleName == "pi+")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4PionPlusInelasticProcess* theInelasticProcess = new G4PionPlusInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(bertini);
                        //theInelasticProcess->RegisterMe(theTheoModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);
                } 
                else if (particleName == "pi-")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4PionMinusInelasticProcess* theInelasticProcess = new G4PionMinusInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(bertini);
                        //theInelasticProcess->RegisterMe(theTheoModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);
                }
                else if (particleName == "kaon+")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4KaonPlusInelasticProcess* theInelasticProcess = new G4KaonPlusInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(bertini);
                        //theInelasticProcess->RegisterMe(theTheoModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);
                }
                else if (particleName == "kaon0S")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4KaonZeroSInelasticProcess* theInelasticProcess = new G4KaonZeroSInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(bertini);
                        //theInelasticProcess->RegisterMe(theTheoModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);
                }
                else if (particleName == "kaon0L")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4KaonZeroLInelasticProcess* theInelasticProcess = new G4KaonZeroLInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(bertini);
                        //theInelasticProcess->RegisterMe(theTheoModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);
                }
                else if (particleName == "kaon-")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4KaonMinusInelasticProcess* theInelasticProcess = new G4KaonMinusInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(bertini);
                        //theInelasticProcess->RegisterMe(theTheoModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);
                }
                else if (particleName == "proton")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4ProtonInelasticProcess* theInelasticProcess = new G4ProtonInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(bertini);
                        //theInelasticProcess->RegisterMe(theTheoModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);
                }
                else if (particleName == "anti_proton")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4AntiProtonInelasticProcess* theInelasticProcess = new G4AntiProtonInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(antiBHighEnergyModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);

                }
                else if (particleName == "neutron")
                {         
                        // elastic scattering
                        pmanager->AddDiscreteProcess(theElasticProcess);

                        // inelastic scattering
                        //G4NeutronInelasticProcess* theInelasticProcess = new G4NeutronInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(bertini);
                        //theInelasticProcess->RegisterMe(theTheoModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);

                        // fission
                        //G4HadronFissionProcess* theFissionProcess = new G4HadronFissionProcess();
                        //G4LFission* theFissionModel = new G4LFission();
                        //theFissionProcess->RegisterMe(theFissionModel);
                        //pmanager->AddDiscreteProcess(theFissionProcess);

                        // capture
                        //G4HadronCaptureProcess* theCaptureProcess = new G4HadronCaptureProcess();
                        //G4NeutronRadCapture* theCaptureModel = new G4NeutronRadCapture();
                        //theCaptureProcess->RegisterMe(theCaptureModel);
                        //pmanager->AddDiscreteProcess(theCaptureProcess);

                }
                else if (particleName == "anti_neutron")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4AntiNeutronInelasticProcess* theInelasticProcess = new G4AntiNeutronInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(antiBHighEnergyModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);

                }
                else if (particleName == "lambda")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4LambdaInelasticProcess* theInelasticProcess = new G4LambdaInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(bertini);
                        //theInelasticProcess->RegisterMe(theTheoModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);
                }
                else if (particleName == "anti_lambda")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4AntiLambdaInelasticProcess* theInelasticProcess = new G4AntiLambdaInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(antiBHighEnergyModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);
                }
                else if (particleName == "sigma+")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4SigmaPlusInelasticProcess* theInelasticProcess = new G4SigmaPlusInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(bertini);
                        //theInelasticProcess->RegisterMe(theTheoModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);
                }
                else if (particleName == "sigma-")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4SigmaMinusInelasticProcess* theInelasticProcess = new G4SigmaMinusInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(bertini);
                        //theInelasticProcess->RegisterMe(theTheoModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);
                }
                else if (particleName == "anti_sigma+")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4AntiSigmaPlusInelasticProcess* theInelasticProcess = new G4AntiSigmaPlusInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(antiBHighEnergyModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);
                }
                else if (particleName == "anti_sigma-")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4AntiSigmaMinusInelasticProcess* theInelasticProcess = new G4AntiSigmaMinusInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(antiBHighEnergyModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);
                }
                else if (particleName == "xi0")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4XiZeroInelasticProcess* theInelasticProcess = new G4XiZeroInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(bertini);
                        //theInelasticProcess->RegisterMe(theTheoModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);
                }
                else if (particleName == "xi-")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4XiMinusInelasticProcess* theInelasticProcess = new G4XiMinusInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(bertini);
                        //theInelasticProcess->RegisterMe(theTheoModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);
                }
                else if (particleName == "anti_xi0")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4AntiXiZeroInelasticProcess* theInelasticProcess = new G4AntiXiZeroInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(antiBHighEnergyModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);
                }
                else if (particleName == "anti_xi-")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4AntiXiMinusInelasticProcess* theInelasticProcess = new G4AntiXiMinusInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(antiBHighEnergyModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);
                }
                else if (particleName == "deuteron")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4DeuteronInelasticProcess* theInelasticProcess = new G4DeuteronInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(binaryCascade);
                        //theInelasticProcess->RegisterMe(qmd);
                        //theInelasticProcess->AddDataSet(shenXS);
                        //theInelasticProcess->AddDataSet(tripXS);
                        //theInelasticProcess->AddDataSet(tripLightXS);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);
                }
                else if (particleName == "triton")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4TritonInelasticProcess* theInelasticProcess = new G4TritonInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(binaryCascade);
                        //theInelasticProcess->RegisterMe(qmd);
                        //theInelasticProcess->AddDataSet(shenXS);
                        //theInelasticProcess->AddDataSet(tripXS);
                        //theInelasticProcess->AddDataSet(tripLightXS);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);
                }
                else if (particleName == "alpha")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4AlphaInelasticProcess* theInelasticProcess = new G4AlphaInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(binaryCascade);
                        //theInelasticProcess->RegisterMe(qmd);
                        //theInelasticProcess->AddDataSet(shenXS);
                        //theInelasticProcess->AddDataSet(tripXS);
                        //theInelasticProcess->AddDataSet(tripLightXS);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);

                }
                else if (particleName == "omega-")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4OmegaMinusInelasticProcess* theInelasticProcess = new G4OmegaMinusInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(bertini);
                        //theInelasticProcess->RegisterMe(theTheoModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);

                }
                else if (particleName == "anti_omega-")
                {
                        pmanager->AddDiscreteProcess(theElasticProcess);
                        //G4AntiOmegaMinusInelasticProcess* theInelasticProcess = new G4AntiOmegaMinusInelasticProcess("inelastic");
                        //theInelasticProcess->RegisterMe(antiBHighEnergyModel);
                        //pmanager->AddDiscreteProcess(theInelasticProcess);
                }*/
        }
}

// 设置Cuts，给出能量阈
void CMSPhysicsList::SetCuts()
{
	// 最低能量限制250 * eV，最高能量限制100 * GeV
	G4double lowlimit = 250 * eV;
	G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(lowlimit, 100. * GeV);
	// world volume能量阈的缺省值
	G4double cutValue = 2.0 * mm;
	SetCutValue(cutValue, "gamma");
	SetCutValue(cutValue, "e-");
	SetCutValue(cutValue, "e+");

	if (verboseLevel > 0) DumpCutValuesTable();
}
