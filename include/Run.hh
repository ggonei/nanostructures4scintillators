//
//	George O'Neill, University of York 2020
//
//  Make a basic cube that allows for addition of photonic objects
//
//	This governs the bulk of the actual run
//
#ifndef Run_h
#define Run_h 1

//	std libraries
#include <numeric>

//	Geant libraries
#include <G4OpBoundaryProcess.hh>
#include <G4Run.hh>
#include <G4SystemOfUnits.hh>
#include <G4UnitsTable.hh>


//class G4ParticleDefinition;
class Run: public G4Run{

public:
	Run();	//	default constructor
	~Run(){};	//	default destructor

	void SetPrimary( G4ParticleDefinition *particle, G4double energy );	//	set particle up
	void AddAbsorption( void ){	//	increment absorption events
		fBoundaryProcs[Absorption] += 1;
	}
	void AddBackScattering( void ){	//	increment backscattered events
		fBoundaryProcs[BackScattering] += 1;
	}
	void AddDetection( void ){	//	increment detected events
		fBoundaryProcs[Detection] += 1;
	}
	void AddDichroic( void ){	//	increment light beams
		fBoundaryProcs[Dichroic] += 1;
	}
	void AddEtchedAirReflection( void ){	//	increment reflected events
		fBoundaryProcs[EtchedAirReflection] += 1;
	}
	void AddEtchedLumirrorAirReflection( void ){	//	increment reflected events
		fBoundaryProcs[EtchedLumirrorAirReflection] += 1;
	}
	void AddEtchedLumirrorGlueReflection( void ){	//	increment reflected events
		fBoundaryProcs[EtchedLumirrorGlueReflection] += 1;
	}
	void AddEtchedTeflonAirReflection( void ){	//	increment reflected events
		fBoundaryProcs[EtchedTeflonAirReflection] += 1;
	}
	void AddEtchedTiOAirReflection( void ){	//	increment reflected events
		fBoundaryProcs[EtchedTiOAirReflection] += 1;
	}
	void AddEtchedTyvekAirReflection( void ){	//	increment reflected events
		fBoundaryProcs[EtchedTyvekAirReflection] += 1;
	}
	void AddEtchedVM2000AirReflection( void ){	//	increment reflected events
		fBoundaryProcs[EtchedVM2000AirReflection] += 1;
	}
	void AddEtchedVM2000GlueReflection( void ){	//	increment reflected events
		fBoundaryProcs[EtchedVM2000GlueReflection] += 1;
	}
	void AddFresnelReflection( void ){	//	increment reflected events
		fBoundaryProcs[FresnelReflection] += 1;
	}
	void AddFresnelRefraction( void ){	//	increment reflected events
		fBoundaryProcs[FresnelRefraction] += 1;
	}
	void AddGroundAirReflection( void ){	//	increment reflected events
		fBoundaryProcs[GroundAirReflection] += 1;
	}
	void AddGroundLumirrorAirReflection( void ){	//	increment reflected events
		fBoundaryProcs[GroundLumirrorAirReflection] += 1;
	}
	void AddGroundLumirrorGlueReflection( void ){	//	increment reflected events
		fBoundaryProcs[GroundLumirrorGlueReflection] += 1;
	}
	void AddGroundTeflonAirReflection( void ){	//	increment reflected events
		fBoundaryProcs[GroundTeflonAirReflection] += 1;
	}
	void AddGroundTiOAirReflection( void ){	//	increment reflected events
		fBoundaryProcs[GroundTiOAirReflection] += 1;
	}
	void AddGroundTyvekAirReflection( void ){	//	increment reflected events
		fBoundaryProcs[GroundTyvekAirReflection] += 1;
	}
	void AddGroundVM2000AirReflection( void ){	//	increment reflected events
		fBoundaryProcs[GroundVM2000AirReflection] += 1;
	}
	void AddGroundVM2000GlueReflection( void ){	//	increment reflected events
		fBoundaryProcs[GroundVM2000GlueReflection] += 1;
	}
	void AddLambertianReflection( void ){	//	increment reflected events
		fBoundaryProcs[LambertianReflection] += 1;
	}
	void AddLobeReflection( void ){	//	increment reflected events
		fBoundaryProcs[LobeReflection] += 1;
	}
	void AddNoRINDEX( void ){	//	increment no refractive index events
		fBoundaryProcs[NoRINDEX] += 1;
	}
	void AddNotAtBoundary( void ){	//	increment events in material
		fBoundaryProcs[NotAtBoundary] += 1;
	}
	void AddOpAbsorption( void ){	//	increment absorbed events
		fOpAbs += 1;
	}
	void AddOpAbsorptionPrior( void ){	//	increment events absorbed before end
		fOpAbsPrior += 1;
	}
	void AddPolishedAirReflection( void ){	//	increment reflected events
		fBoundaryProcs[PolishedAirReflection] += 1;
	}
	void AddPolishedLumirrorAirReflection( void ){	//	increment reflected events
		fBoundaryProcs[PolishedLumirrorAirReflection] += 1;
	}
	void AddPolishedLumirrorGlueReflection( void ){	//	increment reflected events
		fBoundaryProcs[PolishedLumirrorGlueReflection] += 1;
	}
	void AddPolishedTeflonAirReflection( void ){	//	increment reflected events
		fBoundaryProcs[PolishedTeflonAirReflection] += 1;
	}
	void AddPolishedTiOAirReflection( void ){	//	increment reflected events
		fBoundaryProcs[PolishedTiOAirReflection] += 1;
	}
	void AddPolishedTyvekAirReflection( void ){	//	increment reflected events
		fBoundaryProcs[PolishedTyvekAirReflection] += 1;
	}
	void AddPolishedVM2000AirReflection( void ){	//	increment reflected events
		fBoundaryProcs[PolishedVM2000AirReflection] += 1;
	}
	void AddPolishedVM2000GlueReflection( void ){	//	increment reflected events
		fBoundaryProcs[PolishedVM2000GlueReflection] += 1;
	}
	void AddRayleigh( void ){	//	increment rayleigh scattered events
		fRayleighN += 1;
	}
	void AddSameMaterial( void ){	//	increment event in same material
		fBoundaryProcs[SameMaterial] += 1;
	}
	void AddScintillation( void ){	//	increment scintillated events
		fScintN += 1;
	}
	void AddScintillationEnergy( G4double en ){	//	increment scintillated events
		fScintE += en;
	}
	void AddSpikeReflection( void ){	//	increment reflected events
		fBoundaryProcs[SpikeReflection] += 1;
	}
	void AddStepTooSmall( void ){	//	increment insignificant events
		fBoundaryProcs[StepTooSmall] += 1;
	}
	void AddTotalInternalReflection( void ){	//	increment no refraction because of reflection events
		fBoundaryProcs[TotalInternalReflection] += 1;
	}
	void AddTotalSurf( void ){	//	increment total surface events
		fTotSurf += 1;
	}
	void AddTransmission( void ){	//	increment transmitted events
		fBoundaryProcs[Transmission] += 1;
	}

	virtual void Merge( const G4Run * );	//	merge two particles
	void EndOfRun();	//	method to run at end of tracking

private:
	G4ParticleDefinition *fParticle;	//	particle
	G4double fEk;	//	kinetic energy of particle
	G4double fScintE;	//	scintillator particle events
	G4int fOpAbs;	//	absorption not at boundary
	G4int fOpAbsPrior;	//	absorption prior to boundary
	G4int fRayleighN;//	number of rayleigh events
	G4int fScintN;	//	number of scintillator particles
	G4int fTotSurf;	//	total surface events
	std::vector<G4int> fBoundaryProcs;	//	vector of events at edge

};	//	end Run{}
#endif